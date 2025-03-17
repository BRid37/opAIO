#include "selfdrive/ui/qt/offroad/kisaui.h"
#include "selfdrive/ui/qt/offroad/settings.h"
#include "selfdrive/ui/qt/widgets/controls.h"


UIPanel::UIPanel(SettingsWindow *parent) : QWidget((QWidget*)parent) {
  layout = new QVBoxLayout(this);
  layout->setSpacing(20);

  layout->addWidget(new AutoShutdown());
  layout->addWidget(new VolumeControl());
  layout->addWidget(new BrightnessControl());
  layout->addWidget(new AutoScreenOff());
  layout->addWidget(new BrightnessOffControl());
  layout->addWidget(new DoNotDisturbMode());  
  layout->addWidget(horizontal_line());
  layout->addWidget(new DrivingRecordToggle());
  layout->addWidget(new RecordCount());
  const char* record_del = "rm -f /data/media/*.mp4";
  auto recorddelbtn = new ButtonControl(tr("Delete All Recorded Files"), tr("RUN"));
  QObject::connect(recorddelbtn, &ButtonControl::clicked, [=]() {
    if (ConfirmationDialog::confirm2(tr("Delete all saved recorded files. Do you want to proceed?"), this)){
      std::system(record_del);
    }
  });
  layout->addWidget(recorddelbtn);
  layout->addWidget(horizontal_line());
  layout->addWidget(new EnableLogger());
  //layout->addWidget(new EnableUploader());
  const char* realdata_del = "rm -rf /data/media/0/realdata/*";
  auto realdatadelbtn = new ButtonControl(tr("Delete All Driving Logs"), tr("RUN"));
  QObject::connect(realdatadelbtn, &ButtonControl::clicked, [=]() {
    if (ConfirmationDialog::confirm2(tr("Delete all saved driving logs. Do you want to proceed?"), this)){
      std::system(realdata_del);
    }
  });
  layout->addWidget(realdatadelbtn);
  layout->addWidget(horizontal_line());
  layout->addWidget(new MonitoringMode());
  layout->addWidget(new MonitorEyesThreshold());
  layout->addWidget(new BlinkThreshold());
  layout->addWidget(horizontal_line());
  layout->addWidget(new KISANaviSelect());
  layout->addWidget(new ExternalDeviceIP());
  //layout->addWidget(new KISAMapboxStyle());
  layout->addWidget(horizontal_line());
  layout->addWidget(new KISABottomTextView());
  layout->addWidget(new RPMAnimatedToggle());
  layout->addWidget(new RPMAnimatedMaxValue());
  layout->addWidget(new LowUIProfile());
}
