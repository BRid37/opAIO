#!/usr/bin/env python3
import importlib
import math
from collections import deque
from types import SimpleNamespace
from typing import Any

import capnp
from cereal import messaging, log, car
from openpilot.common.filter_simple import FirstOrderFilter
from openpilot.common.numpy_fast import interp
from openpilot.common.params import Params
from openpilot.common.realtime import DT_CTRL, DT_MDL, Ratekeeper, Priority, config_realtime_process
from openpilot.common.swaglog import cloudlog

from openpilot.common.simple_kalman import KF1D

from openpilot.selfdrive.frogpilot.frogpilot_variables import get_frogpilot_toggles

# Default lead acceleration decay set to 50% at 1s
_LEAD_ACCEL_TAU = 1.5

# radar tracks
SPEED, ACCEL = 0, 1     # Kalman filter states enum

# stationary qualification parameters
V_EGO_STATIONARY = 4.   # no stationary object flag below this speed

RADAR_TO_CENTER = 2.7   # (deprecated) RADAR is ~ 2.7m ahead from center of car
RADAR_TO_CAMERA = 1.52  # RADAR is ~ 1.5m ahead from center of mesh frame


class KalmanParams:
  def __init__(self, dt: float):
    # Lead Kalman Filter params, calculating K from A, C, Q, R requires the control library.
    # hardcoding a lookup table to compute K for values of radar_ts between 0.01s and 0.2s
    assert dt > .01 and dt < .2, "Radar time step must be between .01s and 0.2s"
    self.A = [[1.0, dt], [0.0, 1.0]]
    self.C = [1.0, 0.0]
    #Q = np.matrix([[10., 0.0], [0.0, 100.]])
    #R = 1e3
    #K = np.matrix([[ 0.05705578], [ 0.03073241]])
    dts = [dt * 0.01 for dt in range(1, 21)]
    K0 = [0.12287673, 0.14556536, 0.16522756, 0.18281627, 0.1988689,  0.21372394,
          0.22761098, 0.24069424, 0.253096,   0.26491023, 0.27621103, 0.28705801,
          0.29750003, 0.30757767, 0.31732515, 0.32677158, 0.33594201, 0.34485814,
          0.35353899, 0.36200124]
    K1 = [0.29666309, 0.29330885, 0.29042818, 0.28787125, 0.28555364, 0.28342219,
          0.28144091, 0.27958406, 0.27783249, 0.27617149, 0.27458948, 0.27307714,
          0.27162685, 0.27023228, 0.26888809, 0.26758976, 0.26633338, 0.26511557,
          0.26393339, 0.26278425]
    self.K = [[interp(dt, dts, K0)], [interp(dt, dts, K1)]]


class Track:
  def __init__(self, identifier: int, v_lead: float, kalman_params: KalmanParams):
    self.identifier = identifier
    self.cnt = 0
    self.aLeadTau = FirstOrderFilter(_LEAD_ACCEL_TAU, 0.45, DT_MDL)
    self.K_A = kalman_params.A
    self.K_C = kalman_params.C
    self.K_K = kalman_params.K
    self.kf = KF1D([[v_lead], [0.0]], self.K_A, self.K_C, self.K_K)

  def update(self, d_rel: float, y_rel: float, v_rel: float, v_lead: float, measured: float):
    # relative values, copy
    self.dRel = d_rel   # LONG_DIST
    self.yRel = y_rel   # -LAT_DIST
    self.vRel = v_rel   # REL_SPEED
    self.vLead = v_lead
    self.measured = measured   # measured or estimate

    # computed velocity and accelerations
    if self.cnt > 0:
      self.kf.update(self.vLead)

    self.vLeadK = float(self.kf.x[SPEED][0])
    self.aLeadK = float(self.kf.x[ACCEL][0])

    # Learn if constant acceleration
    if abs(self.aLeadK) < 0.5:
      self.aLeadTau.x = _LEAD_ACCEL_TAU
    else:
      self.aLeadTau.update(0.0)

    self.cnt += 1

  def get_RadarState(self, model_prob: float = 0.0):
    return {
      "dRel": float(self.dRel),
      "yRel": float(self.yRel),
      "vRel": float(self.vRel),
      "vLead": float(self.vLead),
      "vLeadK": float(self.vLeadK),
      "aLeadK": float(self.aLeadK),
      "aLeadTau": float(self.aLeadTau.x),
      "status": True,
      "fcw": self.is_potential_fcw(model_prob),
      "modelProb": model_prob,
      "radar": True,
      "radarTrackId": self.identifier,
    }

  def potential_adjacent_lead(self, left: bool, standstill: bool, model_data: capnp._DynamicStructReader):
    if standstill or self.vLeadK < 1:
      return False

    if left:
      left_lane = interp(self.dRel, model_data.laneLines[1].x, model_data.laneLines[1].y)
      return -self.yRel < left_lane
    else:
      right_lane = interp(self.dRel, model_data.laneLines[2].x, model_data.laneLines[2].y)
      return -self.yRel > right_lane

  def potential_far_lead(self, standstill: bool, model_data: capnp._DynamicStructReader):
    if standstill or self.vLeadK < 1:
      return False

    left_lane = interp(self.dRel, model_data.laneLines[1].x, model_data.laneLines[1].y)
    right_lane = interp(self.dRel, model_data.laneLines[2].x, model_data.laneLines[2].y)

    return left_lane < -self.yRel < right_lane

  def potential_low_speed_lead(self, v_ego: float):
    # stop for stuff in front of you and low speed, even without model confirmation
    # Radar points closer than 0.75, are almost always glitches on toyota radars
    return abs(self.yRel) < 1.0 and (v_ego < V_EGO_STATIONARY) and (0.75 < self.dRel < 25)

  def is_potential_fcw(self, model_prob: float):
    return model_prob > .9

  def __str__(self):
    ret = f"x: {self.dRel:4.1f}  y: {self.yRel:4.1f}  v: {self.vRel:4.1f}  a: {self.aLeadK:4.1f}"
    return ret


def laplacian_pdf(x: float, mu: float, b: float):
  b = max(b, 1e-4)
  return math.exp(-abs(x-mu)/b)


def match_vision_to_track(v_ego: float, lead: capnp._DynamicStructReader, tracks: dict[int, Track]):
  offset_vision_dist = lead.x[0] - RADAR_TO_CAMERA

  def prob(c):
    prob_d = laplacian_pdf(c.dRel, offset_vision_dist, lead.xStd[0])
    prob_y = laplacian_pdf(c.yRel, -lead.y[0], lead.yStd[0])
    prob_v = laplacian_pdf(c.vRel + v_ego, lead.v[0], lead.vStd[0])

    # This isn't exactly right, but it's a good heuristic
    return prob_d * prob_y * prob_v

  track = max(tracks.values(), key=prob)

  # if no 'sane' match is found return -1
  # stationary radar points can be false positives
  dist_sane = abs(track.dRel - offset_vision_dist) < max([(offset_vision_dist)*.25, 5.0])
  vel_sane = (abs(track.vRel + v_ego - lead.v[0]) < 10) or (v_ego + track.vRel > 3)
  if dist_sane and vel_sane:
    return track
  else:
    return None


def get_RadarState_from_vision(lead_msg: capnp._DynamicStructReader, v_ego: float, model_v_ego: float):
  lead_v_rel_pred = lead_msg.v[0] - model_v_ego
  return {
    "dRel": float(lead_msg.x[0] - RADAR_TO_CAMERA),
    "yRel": float(-lead_msg.y[0]),
    "vRel": float(lead_v_rel_pred),
    "vLead": float(v_ego + lead_v_rel_pred),
    "vLeadK": float(v_ego + lead_v_rel_pred),
    "aLeadK": float(lead_msg.a[0]),
    "aLeadTau": 0.3,
    "fcw": False,
    "modelProb": float(lead_msg.prob),
    "status": True,
    "radar": False,
    "radarTrackId": -1,
  }


def get_lead(v_ego: float, ready: bool, tracks: dict[int, Track], lead_msg: capnp._DynamicStructReader,
             model_v_ego: float, model_data: capnp._DynamicStructReader, standstill: bool,
             frogpilot_toggles: SimpleNamespace, frogpilotCarState: capnp._DynamicStructReader,
             low_speed_override: bool = True) -> dict[str, Any]:
  # Determine leads, this is where the essential logic happens
  if len(tracks) > 0 and ready and lead_msg.prob > frogpilot_toggles.lead_detection_probability:
    track = match_vision_to_track(v_ego, lead_msg, tracks)
  else:
    track = None

  lead_dict = {'status': False}
  if track is not None:
    lead_dict = track.get_RadarState(lead_msg.prob)
  elif (track is None) and ready and (lead_msg.prob > frogpilot_toggles.lead_detection_probability):
    lead_dict = get_RadarState_from_vision(lead_msg, v_ego, model_v_ego)

  if low_speed_override:
    low_speed_tracks = [c for c in tracks.values() if c.potential_low_speed_lead(v_ego)]
    if len(low_speed_tracks) > 0:
      closest_track = min(low_speed_tracks, key=lambda c: c.dRel)

      # Only choose new track if it is actually closer than the previous one
      if (not lead_dict['status']) or (closest_track.dRel < lead_dict['dRel']):
        lead_dict = closest_track.get_RadarState()

    if not lead_dict['status'] and frogpilot_toggles.allow_far_lead_tracking:
      far_lead_tracks = [c for c in tracks.values() if c.potential_far_lead(standstill, model_data)]
      if len(far_lead_tracks) > 0:
        closest_track = min(far_lead_tracks, key=lambda c: c.dRel)
        lead_dict = closest_track.get_RadarState()
        lead_dict['vLead'] = lead_dict['vLeadK']

  if 'dRel' in lead_dict:
    lead_dict['dRel'] -= frogpilot_toggles.increased_stopped_distance if not frogpilotCarState.trafficMode else 0

  return lead_dict


def get_adjacent_lead(tracks: dict[int, Track], standstill: bool, model_data: capnp._DynamicStructReader, left: bool = True) -> dict[str, Any]:
  lead_dict = {'status': False}

  adjacent_tracks = [c for c in tracks.values() if c.potential_adjacent_lead(left, standstill, model_data)]
  if len(adjacent_tracks) > 0:
    closest_track = min(adjacent_tracks, key=lambda c: c.dRel)
    lead_dict = closest_track.get_RadarState()

  return lead_dict


class RadarD:
  def __init__(self, frogpilot_toggles, radar_ts: float, delay: int = 0):
    self.points: dict[int, tuple[float, float, float]] = {}

    self.current_time = 0.0

    self.tracks: dict[int, Track] = {}
    self.kalman_params = KalmanParams(radar_ts)

    self.v_ego = 0.0
    self.v_ego_hist = deque([0.0], maxlen=delay+1)
    self.last_v_ego_frame = -1

    self.radar_state: capnp._DynamicStructBuilder | None = None
    self.radar_state_valid = False
    self.radar_tracks_valid = False

    self.ready = False

    # FrogPilot variables
    self.frogpilot_toggles = frogpilot_toggles

    self.classic_model = self.frogpilot_toggles.classic_model

  def update(self, sm: messaging.SubMaster, rr):
    self.ready = sm.seen['modelV2']
    self.current_time = 1e-9*max(sm.logMonoTime.values())

    radar_points = []
    radar_errors = []
    if rr is not None:
      radar_points = rr.points
      radar_errors = rr.errors

    if sm.recv_frame['carState'] != self.last_v_ego_frame:
      self.v_ego = sm['carState'].vEgo
      self.v_ego_hist.append(self.v_ego)
      self.last_v_ego_frame = sm.recv_frame['carState']

    ar_pts = {}
    for pt in radar_points:
      ar_pts[pt.trackId] = [pt.dRel, pt.yRel, pt.vRel, pt.measured]

    # *** remove missing points from meta data ***
    for ids in list(self.tracks.keys()):
      if ids not in ar_pts:
        self.tracks.pop(ids, None)

    # *** compute the tracks ***
    for ids in ar_pts:
      rpt = ar_pts[ids]

      # align v_ego by a fixed time to align it with the radar measurement
      v_lead = rpt[2] + self.v_ego_hist[0]

      # create the track if it doesn't exist or it's a new track
      if ids not in self.tracks:
        self.tracks[ids] = Track(ids, v_lead, self.kalman_params)
      self.tracks[ids].update(rpt[0], rpt[1], rpt[2], v_lead, rpt[3])

    # *** publish radarState ***
    self.radar_state_valid = sm.all_checks() and len(radar_errors) == 0
    self.radar_state = log.RadarState.new_message()
    self.radar_state.mdMonoTime = sm.logMonoTime['modelV2']
    self.radar_state.radarErrors = list(radar_errors)
    self.radar_state.carStateMonoTime = sm.logMonoTime['carState']

    if self.classic_model and len(sm['modelV2'].temporalPose.trans):
      model_v_ego = sm['modelV2'].temporalPose.trans[0]
    elif len(sm['modelV2'].velocity.x):
      model_v_ego = sm['modelV2'].velocity.x[0]
    else:
      model_v_ego = self.v_ego
    leads_v3 = sm['modelV2'].leadsV3
    if len(leads_v3) > 1:
      self.radar_state.leadOne = get_lead(self.v_ego, self.ready, self.tracks, leads_v3[0], model_v_ego, sm['modelV2'], sm['carState'].standstill, self.frogpilot_toggles, sm['frogpilotCarState'], low_speed_override=True)
      self.radar_state.leadTwo = get_lead(self.v_ego, self.ready, self.tracks, leads_v3[1], model_v_ego, sm['modelV2'], sm['carState'].standstill, self.frogpilot_toggles, sm['frogpilotCarState'], low_speed_override=False)

    if self.frogpilot_toggles.adjacent_lead_tracking and self.ready:
      self.radar_state.leadLeft = get_adjacent_lead(self.tracks, sm['carState'].standstill, sm['modelV2'], left=True)
      self.radar_state.leadRight = get_adjacent_lead(self.tracks, sm['carState'].standstill, sm['modelV2'], left=False)

    # Update FrogPilot parameters
    if sm['frogpilotPlan'].togglesUpdated:
      self.frogpilot_toggles = get_frogpilot_toggles()

  def publish(self, pm: messaging.PubMaster, lag_ms: float):
    assert self.radar_state is not None

    radar_msg = messaging.new_message("radarState")
    radar_msg.valid = self.radar_state_valid
    radar_msg.radarState = self.radar_state
    radar_msg.radarState.cumLagMs = lag_ms
    pm.send("radarState", radar_msg)

    # publish tracks for UI debugging (keep last)
    tracks_msg = messaging.new_message('liveTracks', len(self.tracks))
    tracks_msg.valid = self.radar_state_valid
    for index, tid in enumerate(sorted(self.tracks.keys())):
      tracks_msg.liveTracks[index] = {
        "trackId": tid,
        "dRel": float(self.tracks[tid].dRel),
        "yRel": float(self.tracks[tid].yRel),
        "vRel": float(self.tracks[tid].vRel),
      }
    pm.send('liveTracks', tracks_msg)

  def update_radardless(self, rr):
    radar_points = []
    radar_errors = []
    if rr is not None:
      radar_points = rr.points
      radar_errors = rr.errors

    self.radar_tracks_valid = len(radar_errors) == 0

    self.points = {}
    for pt in radar_points:
      self.points[pt.trackId] = (pt.dRel, pt.yRel, pt.vRel)

  def publish_radardless(self):
    tracks_msg = messaging.new_message('liveTracks', len(self.points))
    tracks_msg.valid = self.radar_tracks_valid
    for index, tid in enumerate(sorted(self.points.keys())):
      tracks_msg.liveTracks[index] = {
        "trackId": tid,
        "dRel": float(self.points[tid][0]) + RADAR_TO_CAMERA,
        "yRel": -float(self.points[tid][1]),
        "vRel": float(self.points[tid][2]),
      }

    return tracks_msg

# fuses camera and radar data for best lead detection
def main():
  config_realtime_process(5, Priority.CTRL_LOW)

  # wait for stats about the car to come in from controls
  cloudlog.info("radard is waiting for CarParams")
  with car.CarParams.from_bytes(Params().get("CarParams", block=True)) as msg:
    CP = msg
  cloudlog.info("radard got CarParams")

  # import the radar from the fingerprint
  cloudlog.info("radard is importing %s", CP.carName)
  RadarInterface = importlib.import_module(f'selfdrive.car.{CP.carName}.radar_interface').RadarInterface

  # *** setup messaging
  can_sock = messaging.sub_sock('can')

  RI = RadarInterface(CP)

  rk = Ratekeeper(1.0 / CP.radarTimeStep, print_delay_threshold=None)

  # FrogPilot variables
  frogpilot_toggles = get_frogpilot_toggles()

  RD = RadarD(frogpilot_toggles, CP.radarTimeStep, RI.delay)

  if not frogpilot_toggles.radarless_model:
    sm = messaging.SubMaster(['modelV2', 'carState', 'frogpilotCarState', 'frogpilotPlan'], frequency=int(1./DT_CTRL))
    pm = messaging.PubMaster(['radarState', 'liveTracks'])
    while 1:
      can_strings = messaging.drain_sock_raw(can_sock, wait_for_one=True)
      rr = RI.update(can_strings)
      sm.update(0)
      if rr is None:
        continue

      RD.update(sm, rr)
      RD.publish(pm, -rk.remaining*1000.0)
      rk.monitor_time()
  else:
    pub_sock = messaging.pub_sock('liveTracks')
    while 1:
      can_strings = messaging.drain_sock_raw(can_sock, wait_for_one=True)
      rr = RI.update(can_strings)
      if rr is None:
        continue

      RD.update_radardless(rr)
      msg = RD.publish_radardless()
      pub_sock.send(msg.to_bytes())

      rk.monitor_time()

if __name__ == "__main__":
  main()
