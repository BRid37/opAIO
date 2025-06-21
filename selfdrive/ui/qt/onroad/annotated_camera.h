#pragma once

#include <QVBoxLayout>
#include <memory>

#include "selfdrive/ui/qt/onroad/buttons.h"
#include "selfdrive/ui/qt/widgets/cameraview.h"

#include "frogpilot/ui/qt/onroad/frogpilot_annotated_camera.h"
#include "frogpilot/ui/qt/onroad/frogpilot_buttons.h"
#include "frogpilot/ui/screenrecorder/screenrecorder.h"

class AnnotatedCameraWidget : public CameraWidget {
  Q_OBJECT

public:
  explicit AnnotatedCameraWidget(VisionStreamType type, QWidget* parent = 0);
  void updateState(const UIState &s, const FrogPilotUIState &fs);

  MapSettingsButton *map_settings_btn;

  // FrogPilot variables
  double fps;

  FrogPilotAnnotatedCameraWidget *frogpilot_nvg;
  ScreenRecorder *screen_recorder;

private:
  void drawText(QPainter &p, int x, int y, const QString &text, int alpha = 255);

  QVBoxLayout *main_layout;
  ExperimentalButton *experimental_btn;
  QPixmap dm_img;
  float speed;
  QString speedUnit;
  float setSpeed;
  float speedLimit;
  bool is_cruise_set = false;
  bool is_metric = false;
  bool dmActive = false;
  bool hideBottomIcons = false;
  bool rightHandDM = false;
  float dm_fade_state = 1.0;
  bool has_us_speed_limit = false;
  bool has_eu_speed_limit = false;
  bool v_ego_cluster_seen = false;
  int status = STATUS_DISENGAGED;
  std::unique_ptr<PubMaster> pm;

  int skip_frame_count = 0;
  bool wide_cam_requested = false;

  // FrogPilot variables
  void paintEvent(QPaintEvent *event) override;
  void resizeEvent(QResizeEvent *event);

  DistanceButton *distance_btn;

protected:
  void paintGL() override;
  void initializeGL() override;
  void showEvent(QShowEvent *event) override;
  void updateFrameMat() override;
  void drawLaneLines(QPainter &painter, const UIState *s, const FrogPilotUIState *fs);
  void drawLead(QPainter &painter, const cereal::RadarState::LeadData::Reader &lead_data, const cereal::FrogPilotPlan::Reader &frogpilotPlan, const QPointF &vd, const QColor &marker_color, const FrogPilotUIState *fs, bool adjacent = false);
  void drawHud(QPainter &p, const cereal::FrogPilotPlan::Reader &frogpilotPlan, const FrogPilotUIState &fs, const QJsonObject &frogpilot_toggles);
  void drawDriverState(QPainter &painter, const UIState *s, const QJsonObject &frogpilot_toggles);
  inline QColor redColor(int alpha = 255) { return QColor(201, 34, 49, alpha); }
  inline QColor whiteColor(int alpha = 255) { return QColor(255, 255, 255, alpha); }
  inline QColor blackColor(int alpha = 255) { return QColor(0, 0, 0, alpha); }

  double prev_draw_t = 0;
  FirstOrderFilter fps_filter;
};
