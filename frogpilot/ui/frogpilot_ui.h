#pragma once

#include "cereal/messaging/messaging.h"
#include "selfdrive/ui/qt/network/wifi_manager.h"

#include "frogpilot/ui/qt/widgets/frogpilot_controls.h"

struct FrogPilotUIScene {
  bool always_on_lateral_active;
  bool downloading_update;
  bool enabled;
  bool frogpilot_panel_active;
  bool online;
  bool parked;
  bool reverse;
  bool standstill;

  int conditional_status;
  int started_timer;

  QJsonObject frogpilot_toggles;

  QPointF lead_vertices[2];
};

class FrogPilotUIState : public QObject {
  Q_OBJECT

public:
  explicit FrogPilotUIState(QObject *parent = nullptr);

  void update();

  std::unique_ptr<SubMaster> sm;

  FrogPilotUIScene frogpilot_scene;

  Params params_memory{"", false, true};

  WifiManager *wifi;

signals:
};

FrogPilotUIState *frogpilotUIState();
