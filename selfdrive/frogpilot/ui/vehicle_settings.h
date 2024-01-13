#pragma once

#include <set>

#include "selfdrive/frogpilot/ui/frogpilot_functions.h"
#include "selfdrive/ui/qt/offroad/settings.h"

class FrogPilotVehiclesPanel : public FrogPilotListWidget {
  Q_OBJECT

public:
  explicit FrogPilotVehiclesPanel(SettingsWindow *parent);

private:
  void setToggles();
  void updateToggles();

  std::map<std::string, ParamControl*> toggles;

  std::set<QString> gmKeys;
  std::set<QString> toyotaKeys;

  Params params;
  Params paramsMemory{"/dev/shm/params"};
};
