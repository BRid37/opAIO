import math
from cereal import car
from openpilot.common.realtime import DT_CTRL
from openpilot.selfdrive.car import get_safety_config
from openpilot.selfdrive.car.interfaces import CarInterfaceBase
from openpilot.selfdrive.car.body.values import SPEED_FROM_RPM

class CarInterface(CarInterfaceBase):
  @staticmethod
  def _get_params(ret, candidate, fingerprint, car_fw, disable_openpilot_long, experimental_long, docs):
    ret.notCar = True
    ret.carName = "body"
    ret.safetyConfigs = [get_safety_config(car.CarParams.SafetyModel.body)]

    ret.minSteerSpeed = -math.inf
    ret.maxLateralAccel = math.inf  # TODO: set to a reasonable value
    ret.steerLimitTimer = 1.0
    ret.steerActuatorDelay = 0.

    ret.wheelSpeedFactor = SPEED_FROM_RPM

    ret.radarUnavailable = True
    ret.openpilotLongitudinalControl = True
    ret.steerControlType = car.CarParams.SteerControlType.angle

    return ret

  def _update(self, c, frogpilot_toggles):
    ret, fp_ret = self.CS.update(self.cp, frogpilot_toggles)

    # wait for everything to init first
    if self.frame > int(5. / DT_CTRL):
      # body always wants to enable
      ret.init('events', 1)
      ret.events[0].name = car.CarEvent.EventName.pcmEnable
      ret.events[0].enable = True
    self.frame += 1

    return ret, fp_ret
