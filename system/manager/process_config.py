import os

from cereal import car
from openpilot.common.params import Params
from openpilot.system.hardware import PC, TICI
from openpilot.system.manager.process import PythonProcess, NativeProcess, DaemonProcess

WEBCAM = os.getenv("USE_WEBCAM") is not None

def driverview(started: bool, params: Params, CP: car.CarParams, classic_model, tinygrad_model, frogpilot_toggles) -> bool:
  return started or params.get_bool("IsDriverViewEnabled")

def notcar(started: bool, params: Params, CP: car.CarParams, classic_model, tinygrad_model, frogpilot_toggles) -> bool:
  return started and CP.notCar

def iscar(started: bool, params: Params, CP: car.CarParams, classic_model, tinygrad_model, frogpilot_toggles) -> bool:
  return started and not CP.notCar

def logging(started, params, CP: car.CarParams, classic_model, tinygrad_model, frogpilot_toggles) -> bool:
  run = (not CP.notCar) or not params.get_bool("DisableLogging")
  return started and run

def ublox_available() -> bool:
  return os.path.exists('/dev/ttyHS0') and not os.path.exists('/persist/comma/use-quectel-gps')

def ublox(started, params, CP: car.CarParams, classic_model, tinygrad_model, frogpilot_toggles) -> bool:
  use_ublox = ublox_available()
  if use_ublox != params.get_bool("UbloxAvailable"):
    params.put_bool("UbloxAvailable", use_ublox)
  return started and use_ublox

def qcomgps(started, params, CP: car.CarParams, classic_model, tinygrad_model, frogpilot_toggles) -> bool:
  return started and not ublox_available()

def always_run(started, params, CP: car.CarParams, classic_model, tinygrad_model, frogpilot_toggles) -> bool:
  return True

def only_onroad(started: bool, params, CP: car.CarParams, classic_model, tinygrad_model, frogpilot_toggles) -> bool:
  return started

def only_offroad(started, params, CP: car.CarParams, classic_model, tinygrad_model, frogpilot_toggles) -> bool:
  return not started

# FrogPilot functions
def allow_logging(started, params, CP: car.CarParams, classic_model, tinygrad_model, frogpilot_toggles) -> bool:
  return not frogpilot_toggles.no_logging and logging(started, params, CP, classic_model, tinygrad_model, frogpilot_toggles)

def allow_uploads(started, params, CP: car.CarParams, classic_model, tinygrad_model, frogpilot_toggles) -> bool:
  return not frogpilot_toggles.no_uploads

def run_classic_modeld(started, params, CP: car.CarParams, classic_model, tinygrad_model, frogpilot_toggles) -> bool:
  return started and classic_model

def run_new_modeld(started, params, CP: car.CarParams, classic_model, tinygrad_model, frogpilot_toggles) -> bool:
  return started and not (classic_model or tinygrad_model)

def run_tinygrad_modeld(started, params, CP: car.CarParams, classic_model, tinygrad_model, frogpilot_toggles) -> bool:
  return started and tinygrad_model

procs = [
  DaemonProcess("manage_athenad", "system.athena.manage_athenad", "AthenadPid"),

  NativeProcess("camerad", "system/camerad", ["./camerad"], driverview),
  NativeProcess("logcatd", "system/logcatd", ["./logcatd"], allow_logging),
  NativeProcess("proclogd", "system/proclogd", ["./proclogd"], allow_logging),
  PythonProcess("logmessaged", "system.logmessaged", allow_logging),
  PythonProcess("micd", "system.micd", iscar),
  PythonProcess("timed", "system.timed", always_run, enabled=not PC),

  PythonProcess("dmonitoringmodeld", "selfdrive.modeld.dmonitoringmodeld", driverview, enabled=(not PC or WEBCAM)),
  NativeProcess("encoderd", "system/loggerd", ["./encoderd"], allow_logging),
  NativeProcess("stream_encoderd", "system/loggerd", ["./encoderd", "--stream"], notcar),
  NativeProcess("loggerd", "system/loggerd", ["./loggerd"], allow_logging),
  NativeProcess("modeld", "selfdrive/modeld", ["./modeld"], run_new_modeld),
  NativeProcess("mapsd", "selfdrive/navd", ["./mapsd"], run_classic_modeld),
  PythonProcess("navmodeld", "selfdrive.classic_modeld.navmodeld", run_classic_modeld),
  NativeProcess("sensord", "system/sensord", ["./sensord"], only_onroad, enabled=not PC),
  NativeProcess("ui", "selfdrive/ui", ["./ui"], always_run, watchdog_max_dt=(5 if not PC else None)),
  PythonProcess("soundd", "selfdrive.ui.soundd", only_onroad),
  NativeProcess("locationd", "selfdrive/locationd", ["./locationd"], only_onroad),
  NativeProcess("pandad", "selfdrive/pandad", ["./pandad"], always_run, enabled=False),
  PythonProcess("calibrationd", "selfdrive.locationd.calibrationd", only_onroad),
  PythonProcess("torqued", "selfdrive.locationd.torqued", only_onroad),
  PythonProcess("controlsd", "selfdrive.controls.controlsd", only_onroad),
  PythonProcess("card", "selfdrive.car.card", only_onroad),
  PythonProcess("deleter", "system.loggerd.deleter", always_run),
  PythonProcess("dmonitoringd", "selfdrive.monitoring.dmonitoringd", driverview, enabled=(not PC or WEBCAM)),
  PythonProcess("qcomgpsd", "system.qcomgpsd.qcomgpsd", qcomgps, enabled=TICI),
  #PythonProcess("ugpsd", "system.ugpsd", only_onroad, enabled=TICI),
  PythonProcess("navd", "selfdrive.navd.navd", only_onroad),
  PythonProcess("pandad", "selfdrive.pandad.pandad", always_run),
  PythonProcess("paramsd", "selfdrive.locationd.paramsd", only_onroad),
  NativeProcess("ubloxd", "system/ubloxd", ["./ubloxd"], ublox, enabled=TICI),
  PythonProcess("pigeond", "system.ubloxd.pigeond", ublox, enabled=TICI),
  PythonProcess("plannerd", "selfdrive.controls.plannerd", only_onroad),
  PythonProcess("radard", "selfdrive.controls.radard", only_onroad),
  PythonProcess("hardwared", "system.hardware.hardwared", always_run),
  PythonProcess("tombstoned", "system.tombstoned", always_run, enabled=not PC),
  PythonProcess("updated", "system.updated.updated", always_run, enabled=not PC),
  PythonProcess("uploader", "system.loggerd.uploader", allow_uploads),
  PythonProcess("statsd", "system.statsd", allow_logging),

  # debug procs
  NativeProcess("bridge", "cereal/messaging", ["./bridge"], notcar),
  PythonProcess("webrtcd", "system.webrtc.webrtcd", notcar),
  PythonProcess("webjoystick", "tools.bodyteleop.web", notcar),

  # FrogPilot processes
  NativeProcess("classic_modeld", "selfdrive/classic_modeld", ["./classic_modeld"], run_classic_modeld),
  PythonProcess("fleet_manager", "selfdrive.frogpilot.fleetmanager.fleet_manager", always_run),
  PythonProcess("frogpilot_process", "selfdrive.frogpilot.frogpilot_process", always_run),
  PythonProcess("mapd", "selfdrive.frogpilot.navigation.mapd", always_run),
  NativeProcess("tinygrad_modeld", "selfdrive/tinygrad_modeld", ["./tinygrad_modeld"], run_tinygrad_modeld),
]

managed_processes = {p.name: p for p in procs}
