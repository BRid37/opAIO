#include "selfdrive/ui/qt/offroad/kisadriving.h"
#include "selfdrive/ui/qt/offroad/settings.h"
#include "selfdrive/ui/qt/widgets/controls.h"
#include "selfdrive/ui/qt/widgets/steerWidget.h" // kisapilot


DrivingPanel::DrivingPanel(SettingsWindow *parent) : QWidget((QWidget*)parent) {
  layout = new QVBoxLayout(this);
  layout->setSpacing(20);

  layout->addWidget(new CResumeGroup());
  layout->addWidget(horizontal_line());
  layout->addWidget(new CCruiseGapGroup());
  layout->addWidget(horizontal_line());
  layout->addWidget(new CVariableCruiseGroup());
  layout->addWidget(horizontal_line());
  layout->addWidget(new CLaneChangeGroup());
  layout->addWidget(horizontal_line());
  layout->addWidget(new CDrivingQuality());
  layout->addWidget(horizontal_line());
  layout->addWidget(new CSafetyandMap());
  layout->addWidget(horizontal_line());
  layout->addWidget(new CSteerWidget());
  layout->addWidget(horizontal_line());

  layout->addWidget(new UseLegacyLaneModel());
}
