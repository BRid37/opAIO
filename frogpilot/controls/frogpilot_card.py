#!/usr/bin/env python3
from cereal import car
from openpilot.common.params import Params
from openpilot.selfdrive.selfdrived.events import ET

from openpilot.frogpilot.common.frogpilot_variables import NON_DRIVING_GEARS

ButtonType = car.CarState.ButtonEvent.Type

class FrogPilotCard:
  def __init__(self, CP):
    self.CP = CP

    self.params = Params()
    self.params_memory = Params(memory=True)

    self.always_on_lateral_allowed = False

  def update(self, carState, frogpilotCarState, sm, frogpilot_toggles):
    if self.CP.brand == "hyundai":
      for be in carState.buttonEvents:
        if be.type == ButtonType.lkas and be.pressed and frogpilot_toggles.always_on_lateral_lkas:
          self.always_on_lateral_allowed = not self.always_on_lateral_allowed
        elif be.type == ButtonType.mainCruise and be.pressed and frogpilot_toggles.always_on_lateral_main:
          self.always_on_lateral_allowed = not self.always_on_lateral_allowed
    elif frogpilot_toggles.always_on_lateral_main:
      self.always_on_lateral_allowed = carState.cruiseState.available
    else:
      self.always_on_lateral_allowed = carState.cruiseState.enabled

    self.always_on_lateral_enabled = self.always_on_lateral_allowed and frogpilot_toggles.always_on_lateral_set
    self.always_on_lateral_enabled &= carState.gearShifter not in NON_DRIVING_GEARS
    self.always_on_lateral_enabled &= sm["frogpilotPlan"].lateralCheck
    self.always_on_lateral_enabled &= sm["liveCalibration"].calPerc >= 1
    self.always_on_lateral_enabled &= sm["selfdriveState"].alertType != ET.IMMEDIATE_DISABLE or frogpilot_toggles.frogs_go_moo
    self.always_on_lateral_enabled &= not (carState.brakePressed and carState.vEgo < frogpilot_toggles.always_on_lateral_pause_speed or carState.standstill)

    frogpilotCarState.alwaysOnLateralEnabled = self.always_on_lateral_enabled

    return frogpilotCarState
