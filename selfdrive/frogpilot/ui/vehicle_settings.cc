#include "selfdrive/frogpilot/ui/vehicle_settings.h"

FrogPilotVehiclesPanel::FrogPilotVehiclesPanel(SettingsWindow *parent) : ListWidget(parent) {
  setToggles();
}

void FrogPilotVehiclesPanel::setToggles() {
  std::function<ToggleControl*(const char*, const char*, const char*)> addToggle = 
    [&](const char *param, const char *title, const char *description) {
      bool value = params.getBool(param);
      ToggleControl *toggle = new ToggleControl(tr(title), description, "", value);
      QObject::connect(toggle, &ToggleControl::toggleFlipped, [this, param](bool state) {
        params.putBool(param, state);
        paramsMemory.putBool("FrogPilotTogglesUpdated", true);
      });
      addItem(toggle);
      return toggle;
  };
}
