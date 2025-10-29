#include "frogpilot/ui/frogpilot_ui.h"

static void update_state(FrogPilotUIState *fs) {
  FrogPilotUIScene &frogpilot_scene = fs->frogpilot_scene;

  SubMaster &fpsm = *(fs->sm);
  fpsm.update(0);

  if (fpsm.updated("carState")) {
    const cereal::CarState::Reader &carState = fpsm["carState"].getCarState();
    frogpilot_scene.parked = carState.getGearShifter() == cereal::CarState::GearShifter::PARK;
    frogpilot_scene.reverse = carState.getGearShifter() == cereal::CarState::GearShifter::REVERSE;
    frogpilot_scene.standstill = carState.getStandstill() && !frogpilot_scene.reverse;
  }
  if (fpsm.updated("deviceState")) {
    const cereal::DeviceState::Reader &deviceState = fpsm["deviceState"].getDeviceState();
    frogpilot_scene.online = deviceState.getNetworkType() != cereal::DeviceState::NetworkType::NONE;
  }
  if (fpsm.updated("frogpilotCarState")) {
    const cereal::FrogPilotCarState::Reader &frogpilotCarState = fpsm["frogpilotCarState"].getFrogpilotCarState();
    frogpilot_scene.always_on_lateral_active = !frogpilot_scene.enabled && frogpilotCarState.getAlwaysOnLateralEnabled();
  }
  if (fpsm.updated("frogpilotPlan")) {
    const cereal::FrogPilotPlan::Reader &frogpilotPlan = fpsm["frogpilotPlan"].getFrogpilotPlan();
    if (frogpilotPlan.getTogglesUpdated()) {
      frogpilot_scene.frogpilot_toggles = QJsonDocument::fromJson(QByteArray::fromStdString(fs->params_memory.get("FrogPilotToggles"))).object();
    }
  }
  if (fpsm.updated("selfdriveState")) {
    const cereal::SelfdriveState::Reader &selfdriveState = fpsm["selfdriveState"].getSelfdriveState();
    frogpilot_scene.enabled = selfdriveState.getEnabled();
  }
}

FrogPilotUIState::FrogPilotUIState(QObject *parent) : QObject(parent) {
  sm = std::make_unique<SubMaster, const std::initializer_list<const char *>>({
    "carState", "deviceState", "frogpilotCarState", "frogpilotDeviceState", "frogpilotPlan", "selfdriveState"
  });

  wifi = new WifiManager(this);

  frogpilot_scene.frogpilot_toggles = QJsonDocument::fromJson(QByteArray::fromStdString(params_memory.get("FrogPilotToggles", true))).object();
}

FrogPilotUIState *frogpilotUIState() {
  static FrogPilotUIState frogpilot_ui_state;
  return &frogpilot_ui_state;
}

void FrogPilotUIState::update() {
  update_state(this);
}
