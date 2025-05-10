import copy
import numpy as np
from opendbc.car import CanBusBase
from opendbc.car.hyundai.values import HyundaiFlags


class CanBus(CanBusBase):
  def __init__(self, CP, fingerprint=None, lka_steering=None) -> None:
    super().__init__(CP, fingerprint)

    if lka_steering is None:
      lka_steering = CP.flags & HyundaiFlags.CANFD_LKA_STEERING.value if CP is not None else False

    # On the CAN-FD platforms, the LKAS camera is on both A-CAN and E-CAN. LKA steering cars
    # have a different harness than the LFA steering variants in order to split
    # a different bus, since the steering is done by different ECUs.
    self._a, self._e = 1, 0
    if lka_steering:
      self._a, self._e = 0, 1

    self._a += self.offset
    self._e += self.offset
    self._cam = 2 + self.offset

  @property
  def ECAN(self):
    return self._e

  @property
  def ACAN(self):
    return self._a

  @property
  def CAM(self):
    return self._cam


def create_steering_messages(packer, CP, CAN, enabled, lat_active, apply_torque, apply_angle, max_torque, lfa_info, lfa_alt_info):
  common_values = {
    "LKA_MODE": 2,
    "LKA_ICON": 2 if enabled else 1,
    "TORQUE_REQUEST": apply_torque,
    "LKA_ASSIST": 0,
    "STEER_REQ": 1 if lat_active else 0,
    "STEER_MODE": 0,
    "HAS_LANE_SAFETY": 0,  # hide LKAS settings
    "NEW_SIGNAL_2": 0,
  }

  lkas_values = copy.copy(common_values)
  lkas_values["LKA_AVAILABLE"] = 0

  lfa_values = copy.copy(common_values)
  lfa_values["NEW_SIGNAL_1"] = 0

  ret = []
  if CP.flags & HyundaiFlags.CANFD_LKA_STEERING: # hda2
    lkas_msg = "LKAS_ALT" if CP.flags & HyundaiFlags.CANFD_LKA_STEERING_ALT else "LKAS"
    if CP.openpilotLongitudinalControl:
      ret.append(packer.make_can_msg("LFA", CAN.ECAN, lfa_values))
    if CP.isAngleControl: # hda2 angle control
      lkas_values["LKA_MODE"] = 0
      lkas_values["TORQUE_REQUEST"] = 0
      lkas_values["STEER_REQ"] = 0
      lkas_values["LKA_AVAILABLE"] = 3 if lat_active else 0
      lkas_values["LKAS_ANGLE_ACTIVE"] = 2 if lat_active else 0
      lkas_values["LKAS_ANGLE_CMD"] = apply_angle if lat_active else 0
      lkas_values["LKAS_ANGLE_MAX_TORQUE"] = max_torque if lat_active else 0
      lkas_values["LKAS_SIGNAL_1"] = 10
      lkas_values["LKAS_SIGNAL_2"] = 1
      lkas_values["LKAS_SIGNAL_3"] = 1
      lkas_values["LKAS_SIGNAL_4"] = 1
      lkas_values["LKAS_SIGNAL_5"] = 1
      lkas_values["NEW_SIGNAL_3"] = 9
    ret.append(packer.make_can_msg(lkas_msg, CAN.ACAN, lkas_values))
  elif CP.isAngleControl: # non-hda2 angle control or adas direct connected.
    lfa_values["LKA_MODE"] = 0
    lfa_values["NEW_SIGNAL_1"] = 3 if lat_active else 0
    lfa_values["TORQUE_REQUEST"] = -1024
    lfa_values["STEER_REQ"] = 0
    lfa_values["NEW_SIGNAL_3"] = 0
    lfa_values["NEW_SIGNAL_4"] = 1
    lfa_values["NEW_SIGNAL_5"] = 1
    ret.append(packer.make_can_msg("LFA", CAN.ECAN, lfa_values))

    ang_values = {
      "LKAS_ANGLE_ACTIVE": 2 if lat_active else 1,
      "LKAS_ANGLE_CMD": apply_angle if lat_active else 0,
      "LKAS_ANGLE_MAX_TORQUE": max_torque if lat_active else 0,
    }
    ret.append(packer.make_can_msg("LFA_ALT", CAN.ECAN, ang_values))
  else:
    lfa_values["LKA_MODE"] = 0
    lfa_values["NEW_SIGNAL_1"] = 3 if lat_active else 0
    lfa_values["NEW_SIGNAL_3"] = 31 if lat_active else 100
    lfa_values["NEW_SIGNAL_5"] = 1
    ret.append(packer.make_can_msg("LFA", CAN.ECAN, lfa_values))

  return ret

def create_suppress_lfa(packer, CAN, lfa_block_msg, lka_steering_alt, enabled):
  suppress_msg = "CAM_0x362" if lka_steering_alt else "CAM_0x2a4"

  #msg_bytes = 32 if lka_steering_alt else 24

  #values = {f"BYTE{i}": lfa_block_msg[f"BYTE{i}"] for i in range(3, msg_bytes) if i != 7}
  values = lfa_block_msg

  values["COUNTER"] = lfa_block_msg["COUNTER"]
  
  values["LEFT_LANE_LINE_PROB"] = lfa_block_msg["LEFT_LANE_LINE_PROB"] # maybe double lane above 20
  values["RIGHT_LANE_LINE_PROB"] = lfa_block_msg["RIGHT_LANE_LINE_PROB"] # maybe double lane above 20
  values["LEFT_LANE_TYPE"] = 0   # lfa_block_msg["LEFT_LANE_TYPE"]
  values["RIGHT_LANE_TYPE"] = 0  # lfa_block_msg["RIGHT_LANE_TYPE"]
  values["LEFT_LANE_COLOR"] = lfa_block_msg["LEFT_LANE_COLOR"]
  values["RIGHT_LANE_COLOR"] = lfa_block_msg["RIGHT_LANE_COLOR"]
  values["LEFT_GUARD"] = lfa_block_msg["LEFT_GUARD"]
  values["RIGHT_GUARD"] = lfa_block_msg["RIGHT_GUARD"]
  values["LEFT_BLOCKED"] = lfa_block_msg["LEFT_BLOCKED"]
  values["RIGHT_BLOCKED"] = lfa_block_msg["RIGHT_BLOCKED"]
  values["DISTANCE_1"] = lfa_block_msg["DISTANCE_1"]
  values["DISTANCE_2"] = lfa_block_msg["DISTANCE_2"]
  values["DISTANCE_3"] = lfa_block_msg["DISTANCE_3"]
  values["DISTANCE_4"] = lfa_block_msg["DISTANCE_4"]
  values["DISTANCE_5"] = lfa_block_msg["DISTANCE_5"]
  values["DISTANCE_6"] = lfa_block_msg["DISTANCE_6"]
  values["DISTANCE_7"] = lfa_block_msg["DISTANCE_7"]
  values["DISTANCE_8"] = lfa_block_msg["DISTANCE_8"]
  values["SET_ME_0"] = 0
  values["SET_ME_0_2"] = 0
  values["LEFT_LANE_LINE"] = 0 if enabled else 3
  values["RIGHT_LANE_LINE"] = 0 if enabled else 3
  return packer.make_can_msg(suppress_msg, CAN.ACAN, values)

def create_buttons(packer, CP, CAN, cnt, btn, regen = None, r_pad = None, l_pad = None):
  values = {
    "COUNTER": cnt,
    "SET_ME_1": 1,
    "CRUISE_BUTTONS": btn,
  }

  if regen:
    if r_pad:
      values["RIGHT_PADDLE"] = r_pad
    if l_pad:
      values["LEFT_PADDLE"] = l_pad

  bus = CAN.ECAN if CP.flags & HyundaiFlags.CANFD_LKA_STEERING else CAN.CAM
  return packer.make_can_msg("CRUISE_BUTTONS", bus, values)

def create_acc_cancel(packer, CP, CAN, cruise_info_copy):
  # TODO: why do we copy different values here?
  if CP.flags & HyundaiFlags.CANFD_CAMERA_SCC.value:
    values = {s: cruise_info_copy[s] for s in [
      "COUNTER",
      "CHECKSUM",
      "NEW_SIGNAL_1",
      "MainMode_ACC",
      "ACCMode",
      "ZEROS_9",
      "CRUISE_STANDSTILL",
      "ZEROS_5",
      "DISTANCE_SETTING",
      "VSetDis",
    ]}
  else:
    values = {s: cruise_info_copy[s] for s in [
      "COUNTER",
      "CHECKSUM",
      "ACCMode",
      "VSetDis",
      "CRUISE_STANDSTILL",
    ]}
  values.update({
    "ACCMode": 4,
    "aReqRaw": 0.0,
    "aReqValue": 0.0,
  })
  return packer.make_can_msg("SCC_CONTROL", CAN.ECAN, values)

def create_lfahda_cluster(packer, CAN, enabled):
  values = {
    "HDA_ICON": 1 if enabled else 0,
    "LFA_ICON": 2 if enabled else 0,
  }
  return packer.make_can_msg("LFAHDA_CLUSTER", CAN.ECAN, values)


def create_acc_control(packer, CAN, enabled, accel_last, accel, stopping, gas_override, set_speed, hud_control):
  jerk = 5
  jn = jerk / 50
  if not enabled or gas_override:
    a_val, a_raw = 0, 0
  else:
    a_raw = accel
    a_val = np.clip(accel, accel_last - jn, accel_last + jn)

  values = {
    "ACCMode": 0 if not enabled else (2 if gas_override else 1),
    "MainMode_ACC": 1,
    "StopReq": 1 if stopping else 0,
    "aReqValue": a_val,
    "aReqRaw": a_raw,
    "VSetDis": set_speed,
    "JerkLowerLimit": jerk if enabled else 1,
    "JerkUpperLimit": 3.0,

    "ACC_ObjDist": 1,
    "ObjValid": 0,
    "OBJ_STATUS": 2,
    "SET_ME_2": 0x4,
    "SET_ME_3": 0x3,
    "SET_ME_TMP_64": 0x64,
    "DISTANCE_SETTING": hud_control.leadDistanceBars,
  }

  return packer.make_can_msg("SCC_CONTROL", CAN.ECAN, values)


def create_spas_messages(packer, CAN, left_blink, right_blink):
  ret = []

  values = {
  }
  ret.append(packer.make_can_msg("SPAS1", CAN.ECAN, values))

  blink = 0
  if left_blink:
    blink = 3
  elif right_blink:
    blink = 4
  values = {
    "BLINKER_CONTROL": blink,
  }
  ret.append(packer.make_can_msg("SPAS2", CAN.ECAN, values))

  return ret


def create_fca_warning_light(packer, CAN, frame):
  ret = []

  if frame % 2 == 0:
    values = {
      'AEB_SETTING': 0x1,  # show AEB disabled icon
      'SET_ME_2': 0x2,
      'SET_ME_FF': 0xff,
      'SET_ME_FC': 0xfc,
      'SET_ME_9': 0x9,
    }
    ret.append(packer.make_can_msg("ADRV_0x160", CAN.ECAN, values))
  return ret


def create_adrv_messages(packer, CAN, frame):
  # messages needed to car happy after disabling
  # the ADAS Driving ECU to do longitudinal control

  ret = []

  values = {
  }
  ret.append(packer.make_can_msg("ADRV_0x51", CAN.ACAN, values))

  ret.extend(create_fca_warning_light(packer, CAN, frame))

  if frame % 5 == 0:
    values = {
      'SET_ME_1C': 0x1c,
      'SET_ME_FF': 0xff,
      'SET_ME_TMP_F': 0xf,
      'SET_ME_TMP_F_2': 0xf,
    }
    ret.append(packer.make_can_msg("ADRV_0x1ea", CAN.ECAN, values))

    values = {
      'SET_ME_E1': 0xe1,
      'SET_ME_3A': 0x3a,
    }
    ret.append(packer.make_can_msg("ADRV_0x200", CAN.ECAN, values))

  if frame % 20 == 0:
    values = {
      'SET_ME_15': 0x15,
    }
    ret.append(packer.make_can_msg("ADRV_0x345", CAN.ECAN, values))

  if frame % 100 == 0:
    values = {
      'SET_ME_22': 0x22,
      'SET_ME_41': 0x41,
    }
    ret.append(packer.make_can_msg("ADRV_0x1da", CAN.ECAN, values))

  return ret


def create_ccnc(packer, CAN, frame, ccnc_161, ccnc_162, adrv_1ea):
  ret = []

  values_161 = ccnc_161
  values_161.update({
    "FCA_ALT_ICON": 0,
  })
  ret.append(packer.make_can_msg("CCNC_0x161", CAN.ECAN, values_161))

  values_162 = ccnc_162
  values_162.update({
    "FAULT_FCA": 0,
    "FAULT_LFA": 0,
    "FAULT_LCA": 0,
    "FAULT_DAS": 0,
  })
  ret.append(packer.make_can_msg("CCNC_0x162", CAN.ECAN, values_162))

  values_1ea = adrv_1ea
  values_1ea.update({
    "SET_ME_1C": 0,
    "NEW_SIGNAL_1": 0,
  })
  ret.append(packer.make_can_msg("ADRV_0x1ea", CAN.ECAN, values_1ea))

  return ret