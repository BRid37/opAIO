#include "selfdrive/ui/qt/offroad/kisatuning.h"
#include "selfdrive/ui/qt/offroad/settings.h"
#include "selfdrive/ui/qt/widgets/controls.h"


TuningPanel::TuningPanel(SettingsWindow *parent) : QWidget((QWidget*)parent) {
  layout = new QVBoxLayout(this);
  layout->setSpacing(20);

  layout->addWidget(new CameraOffset());
  //layout->addWidget(new PathOffset());
  layout->addWidget(new SteerAngleCorrection());
  layout->addWidget(horizontal_line());

  layout->addWidget(new SteerActuatorDelay());

  layout->addWidget(new TireStiffnessFactor());
  layout->addWidget(new SteerThreshold());
  layout->addWidget(new SteerLimitTimer());

  layout->addWidget(new LiveSteerRatioToggle());
  layout->addWidget(new LiveSRPercent());
  layout->addWidget(new SRBaseControl());
  layout->addWidget(horizontal_line());
  layout->addWidget(new SteerMax());
  layout->addWidget(new SteerDeltaUp());
  layout->addWidget(new SteerDeltaDown());
  layout->addWidget(horizontal_line());

  layout->addWidget(new CLateralControlGroup());
  layout->addWidget(horizontal_line());
  layout->addWidget(new CLongControlGroup());
}
