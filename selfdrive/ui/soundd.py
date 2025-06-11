import math
import numpy as np
import time
import wave

from pathlib import Path

from cereal import car, messaging
from openpilot.common.basedir import BASEDIR
from openpilot.common.filter_simple import FirstOrderFilter
from openpilot.common.realtime import Ratekeeper
from openpilot.common.retry import retry
from openpilot.common.swaglog import cloudlog

from openpilot.system import micd

from openpilot.selfdrive.frogpilot.frogpilot_variables import ACTIVE_THEME_PATH, ERROR_LOGS_PATH, RANDOM_EVENTS_PATH, get_frogpilot_toggles, params_memory

SAMPLE_RATE = 48000
SAMPLE_BUFFER = 4096 # (approx 100ms)
MAX_VOLUME = 1.0
MIN_VOLUME = 0.1
CONTROLS_TIMEOUT = 5 # 5 seconds
FILTER_DT = 1. / (micd.SAMPLE_RATE / micd.FFT_SAMPLES)

AMBIENT_DB = 30 # DB where MIN_VOLUME is applied
DB_SCALE = 30 # AMBIENT_DB + DB_SCALE is where MAX_VOLUME is applied

AudibleAlert = car.CarControl.HUDControl.AudibleAlert


sound_list: dict[int, tuple[str, int | None, float]] = {
  # AudibleAlert, file name, play count (none for infinite)
  AudibleAlert.engage: ("engage.wav", 1, MAX_VOLUME),
  AudibleAlert.disengage: ("disengage.wav", 1, MAX_VOLUME),
  AudibleAlert.refuse: ("refuse.wav", 1, MAX_VOLUME),

  AudibleAlert.prompt: ("prompt.wav", 1, MAX_VOLUME),
  AudibleAlert.promptRepeat: ("prompt.wav", None, MAX_VOLUME),
  AudibleAlert.promptDistracted: ("prompt_distracted.wav", None, MAX_VOLUME),

  AudibleAlert.warningSoft: ("warning_soft.wav", None, MAX_VOLUME),
  AudibleAlert.warningImmediate: ("warning_immediate.wav", None, MAX_VOLUME),

  # FrogPilot sounds
  AudibleAlert.angry: ("angry.wav", 1, MAX_VOLUME),
  AudibleAlert.continued: ("continued.wav", 1, MAX_VOLUME),
  AudibleAlert.dejaVu: ("dejaVu.wav", 1, MAX_VOLUME),
  AudibleAlert.doc: ("doc.wav", 1, MAX_VOLUME),
  AudibleAlert.fart: ("fart.wav", 1, MAX_VOLUME),
  AudibleAlert.firefox: ("firefox.wav", 1, MAX_VOLUME),
  AudibleAlert.goat: ("goat.wav", None, MAX_VOLUME),
  AudibleAlert.hal9000: ("hal9000.wav", 1, MAX_VOLUME),
  AudibleAlert.mail: ("mail.wav", 1, MAX_VOLUME),
  AudibleAlert.nessie: ("nessie.wav", 1, MAX_VOLUME),
  AudibleAlert.noice: ("noice.wav", 1, MAX_VOLUME),
  AudibleAlert.promptRepeat: ("prompt_repeat.wav", None, MAX_VOLUME),
  AudibleAlert.startup: ("startup.wav", 1, MAX_VOLUME),
  AudibleAlert.thisIsFine: ("this_is_fine.wav", 1, MAX_VOLUME),
  AudibleAlert.uwu: ("uwu.wav", 1, MAX_VOLUME),
}

def check_controls_timeout_alert(sm):
  controls_missing = time.monotonic() - sm.recv_time['controlsState']

  if controls_missing > CONTROLS_TIMEOUT:
    if sm['controlsState'].enabled and (controls_missing - CONTROLS_TIMEOUT) < 10:
      return True

  return False


class Soundd:
  def __init__(self):
    self.current_alert = AudibleAlert.none
    self.current_volume = MIN_VOLUME
    self.current_sound_frame = 0

    self.controls_timeout_alert = False

    self.spl_filter_weighted = FirstOrderFilter(0, 2.5, FILTER_DT, initialized=False)

    # FrogPilot variables
    self.frogpilot_toggles = get_frogpilot_toggles()

    self.openpilot_crashed_played = False
    self.restart_stream = False

    self.auto_volume = 0

    self.previous_sound_pack = None

    self.error_log = ERROR_LOGS_PATH / "error.txt"
    self.random_events_directory = RANDOM_EVENTS_PATH / "sounds"

    self.random_events_map = {
      AudibleAlert.angry: MAX_VOLUME,
      AudibleAlert.continued: MAX_VOLUME,
      AudibleAlert.dejaVu: MAX_VOLUME,
      AudibleAlert.doc: MAX_VOLUME,
      AudibleAlert.fart: MAX_VOLUME,
      AudibleAlert.firefox: MAX_VOLUME,
      AudibleAlert.goat: MAX_VOLUME,
      AudibleAlert.hal9000: MAX_VOLUME,
      AudibleAlert.mail: MAX_VOLUME,
      AudibleAlert.nessie: MAX_VOLUME,
      AudibleAlert.noice: MAX_VOLUME,
      AudibleAlert.thisIsFine: MAX_VOLUME,
      AudibleAlert.uwu: MAX_VOLUME,
    }

    self.update_frogpilot_sounds()

  def load_sounds(self):
    self.loaded_sounds: dict[int, np.ndarray] = {}

    # Load all sounds
    for sound in sound_list:
      filename, play_count, volume = sound_list[sound]

      if sound in self.random_events_map:
        wavefile = wave.open(str(self.random_events_directory / filename), 'r')
      else:
        try:
          wavefile = wave.open(str(self.sound_directory / filename), 'r')
        except FileNotFoundError:
          if filename == "prompt_repeat.wav":
            filename = "prompt.wav"
          elif filename == "startup.wav":
            filename = "engage.wav"
          wavefile = wave.open(BASEDIR + "/selfdrive/assets/sounds/" + filename, 'r')

      assert wavefile.getnchannels() == 1
      assert wavefile.getsampwidth() == 2
      assert wavefile.getframerate() == SAMPLE_RATE

      length = wavefile.getnframes()
      self.loaded_sounds[sound] = np.frombuffer(wavefile.readframes(length), dtype=np.int16).astype(np.float32) / (2**16/2)

  def get_sound_data(self, frames): # get "frames" worth of data from the current alert sound, looping when required

    ret = np.zeros(frames, dtype=np.float32)

    if self.current_alert != AudibleAlert.none:
      num_loops = sound_list[self.current_alert][1]
      sound_data = self.loaded_sounds[self.current_alert]
      written_frames = 0

      current_sound_frame = self.current_sound_frame % len(sound_data)
      loops = self.current_sound_frame // len(sound_data)

      while written_frames < frames and (num_loops is None or loops < num_loops):
        available_frames = sound_data.shape[0] - current_sound_frame
        frames_to_write = min(available_frames, frames - written_frames)
        ret[written_frames:written_frames+frames_to_write] = sound_data[current_sound_frame:current_sound_frame+frames_to_write]
        written_frames += frames_to_write
        self.current_sound_frame += frames_to_write

    return ret * self.current_volume

  def callback(self, data_out: np.ndarray, frames: int, time, status) -> None:
    if status:
      cloudlog.warning(f"soundd stream over/underflow: {status}")
    data_out[:frames, 0] = self.get_sound_data(frames)

  def update_alert(self, new_alert):
    current_alert_played_once = self.current_alert == AudibleAlert.none or self.current_sound_frame > len(self.loaded_sounds[self.current_alert])
    if self.current_alert != new_alert and (new_alert != AudibleAlert.none or current_alert_played_once):
      self.current_alert = new_alert
      self.current_sound_frame = 0

  def get_audible_alert(self, sm):
    if params_memory.get("TestAlert", encoding="utf-8"):
      self.update_alert(getattr(AudibleAlert, params_memory.get("TestAlert", encoding="utf-8")))

      params_memory.remove("TestAlert")
    elif not self.openpilot_crashed_played and self.error_log.is_file():
      if self.frogpilot_toggles.random_events:
        self.update_alert(AudibleAlert.fart)
      else:
        self.update_alert(AudibleAlert.prompt)

      self.openpilot_crashed_played = True
    elif sm.updated['controlsState']:
      new_alert = sm['controlsState'].alertSound.raw
      self.update_alert(new_alert)
    elif check_controls_timeout_alert(sm):
      self.update_alert(AudibleAlert.warningImmediate)
      self.controls_timeout_alert = True
    elif self.controls_timeout_alert:
      self.update_alert(AudibleAlert.none)
      self.controls_timeout_alert = False

  def calculate_volume(self, weighted_db):
    volume = ((weighted_db - AMBIENT_DB) / DB_SCALE) * (MAX_VOLUME - MIN_VOLUME) + MIN_VOLUME
    return math.pow(10, (np.clip(volume, MIN_VOLUME, MAX_VOLUME) - 1))

  @retry(attempts=7, delay=3)
  def get_stream(self, sd):
    # reload sounddevice to reinitialize portaudio
    sd._terminate()
    sd._initialize()
    return sd.OutputStream(channels=1, samplerate=SAMPLE_RATE, callback=self.callback, blocksize=SAMPLE_BUFFER)

  def soundd_thread(self):
    # sounddevice must be imported after forking processes
    import sounddevice as sd

    sm = messaging.SubMaster(['controlsState', 'microphone', 'frogpilotPlan'])

    with self.get_stream(sd) as stream:
      rk = Ratekeeper(20)

      cloudlog.info(f"soundd stream started: {stream.samplerate=} {stream.channels=} {stream.dtype=} {stream.device=}, {stream.blocksize=}")
      while True:
        sm.update(0)

        if sm.updated['microphone'] and self.current_alert == AudibleAlert.none: # only update volume filter when not playing alert
          self.spl_filter_weighted.update(sm["microphone"].soundPressureWeightedDb)

          if self.frogpilot_toggles.alert_volume_control:
            self.auto_volume = self.calculate_volume(float(self.spl_filter_weighted.x))
            self.current_volume = 0.0
          else:
            self.current_volume = self.calculate_volume(float(self.spl_filter_weighted.x))

        elif self.frogpilot_toggles.alert_volume_control and self.current_alert in self.volume_map:
          self.current_volume = self.volume_map[self.current_alert] / 100.0
          if self.current_volume == 1.01:
            if self.current_alert == AudibleAlert.startup:
              self.current_volume = MAX_VOLUME
            else:
              self.current_volume = self.auto_volume

        elif self.current_alert in self.random_events_map:
          self.current_volume = self.random_events_map[self.current_alert]

        elif self.current_alert == AudibleAlert.startup:
          self.current_volume = MAX_VOLUME

        self.get_audible_alert(sm)

        rk.keep_time()

        assert stream.active

        # Update FrogPilot parameters
        if sm['frogpilotPlan'].togglesUpdated:
          self.frogpilot_toggles = get_frogpilot_toggles()

          self.update_frogpilot_sounds()

        if self.restart_stream:
          stream.close()
          stream = self.get_stream(sd)
          stream.start()

          self.restart_stream = False

  def update_frogpilot_sounds(self):
    self.volume_map = {
      AudibleAlert.engage: self.frogpilot_toggles.engage_volume,
      AudibleAlert.disengage: self.frogpilot_toggles.disengage_volume,
      AudibleAlert.refuse: self.frogpilot_toggles.refuse_volume,

      AudibleAlert.prompt: self.frogpilot_toggles.prompt_volume,
      AudibleAlert.promptRepeat: self.frogpilot_toggles.prompt_volume,
      AudibleAlert.promptDistracted: self.frogpilot_toggles.promptDistracted_volume,

      AudibleAlert.warningSoft: self.frogpilot_toggles.warningSoft_volume,
      AudibleAlert.warningImmediate: self.frogpilot_toggles.warningImmediate_volume,

      AudibleAlert.goat: self.frogpilot_toggles.prompt_volume,
      AudibleAlert.startup: self.frogpilot_toggles.engage_volume,
    }

    if self.frogpilot_toggles.sound_pack != "stock":
      self.sound_directory = ACTIVE_THEME_PATH / "sounds"
    else:
      self.sound_directory = Path(BASEDIR) / "selfdrive" / "assets" / "sounds"

    if self.frogpilot_toggles.sound_pack != self.previous_sound_pack:
      self.load_sounds()

      self.previous_sound_pack = self.frogpilot_toggles.sound_pack

      self.restart_stream = True

def main():
  s = Soundd()
  s.soundd_thread()


if __name__ == "__main__":
  main()
