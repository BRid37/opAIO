#include "frogpilot/ui/qt/offroad/data_settings.h"
#include "frogpilot/ui/qt/offroad/device_settings.h"
#include "frogpilot/ui/qt/offroad/frogpilot_settings.h"
#include "frogpilot/ui/qt/offroad/lateral_settings.h"
#include "frogpilot/ui/qt/offroad/longitudinal_settings.h"
#include "frogpilot/ui/qt/offroad/maps_settings.h"
#include "frogpilot/ui/qt/offroad/model_settings.h"
#include "frogpilot/ui/qt/offroad/navigation_settings.h"
#include "frogpilot/ui/qt/offroad/sounds_settings.h"
#include "frogpilot/ui/qt/offroad/theme_settings.h"
#include "frogpilot/ui/qt/offroad/utilities.h"
#include "frogpilot/ui/qt/offroad/vehicle_settings.h"
#include "frogpilot/ui/qt/offroad/visual_settings.h"
#include "frogpilot/ui/qt/offroad/wheel_settings.h"

bool nnffLogFileExists(const QString &carFingerprint) {
  static QStringList files;
  if (files.isEmpty()) {
    QFileInfoList fileInfoList = QDir(QStringLiteral("../car/torque_data/lat_models")).entryInfoList(QDir::Files | QDir::NoDotAndDotDot);
    for (const QFileInfo &fileInfo : fileInfoList) {
      files.append(fileInfo.completeBaseName());
    }
  }

  for (const QString &file : files) {
    if (file.startsWith(carFingerprint)) {
      std::cout << "NNFF supports fingerprint: " << file.toStdString() << std::endl;
      return true;
    }
  }

  return false;
}

void FrogPilotSettingsWindow::createPanelButtons(FrogPilotListWidget *list) {
  FrogPilotDevicePanel *frogpilotDevicePanel = new FrogPilotDevicePanel(this);
  FrogPilotLateralPanel *frogpilotLateralPanel = new FrogPilotLateralPanel(this);
  FrogPilotLongitudinalPanel *frogpilotLongitudinalPanel = new FrogPilotLongitudinalPanel(this);
  FrogPilotMapsPanel *frogpilotMapsPanel = new FrogPilotMapsPanel(this);
  FrogPilotModelPanel *frogpilotModelPanel = new FrogPilotModelPanel(this);
  FrogPilotNavigationPanel *frogpilotNavigationPanel = new FrogPilotNavigationPanel(this);
  FrogPilotSoundsPanel *frogpilotSoundsPanel = new FrogPilotSoundsPanel(this);
  FrogPilotThemesPanel *frogpilotThemesPanel = new FrogPilotThemesPanel(this);
  FrogPilotVehiclesPanel *frogpilotVehiclesPanel = new FrogPilotVehiclesPanel(this);
  FrogPilotVisualsPanel *frogpilotVisualsPanel = new FrogPilotVisualsPanel(this);
  FrogPilotWheelPanel *frogpilotWheelPanel = new FrogPilotWheelPanel(this);

  std::vector<std::vector<std::tuple<QString, QWidget*>>> panelButtons = {
    {{tr("MANAGE"), frogpilotSoundsPanel}},
    {{tr("DRIVING MODEL"), frogpilotModelPanel}, {tr("GAS / BRAKE"), frogpilotLongitudinalPanel}, {tr("STEERING"), frogpilotLateralPanel}},
    {{tr("MAP DATA"), frogpilotMapsPanel}, {tr("NAVIGATION"), frogpilotNavigationPanel}},
    {{tr("DATA"), new FrogPilotDataPanel(this)}, {tr("DEVICE CONTROLS"), frogpilotDevicePanel}, {tr("UTILITIES"), new FrogPilotUtilitiesPanel(this)}},
    {{tr("APPEARANCE"), frogpilotVisualsPanel}, {tr("THEME"), frogpilotThemesPanel}},
    {{tr("VEHICLE SETTINGS"), frogpilotVehiclesPanel}, {tr("WHEEL CONTROLS"), frogpilotWheelPanel}}
  };

  std::vector<std::tuple<QString, QString, QString>> panelInfo = {
    {tr("Alerts and Sounds"), tr("FrogPilot settings for alert volumes and custom notifications to stay informed about important driving events."), "../../frogpilot/assets/toggle_icons/icon_sound.png"},
    {tr("Driving Controls"), tr("FrogPilot settings for acceleration, braking, and steering."), "../../frogpilot/assets/toggle_icons/icon_steering.png"},
    {tr("Navigation"), tr("Download map data for <b>Curve Speed Control</b>, <b>Speed Limit Controller</b>, and set up <b>Navigate on openpilot (NOO)</b>."), "../../frogpilot/assets/toggle_icons/icon_map.png"},
    {tr("System Management"), tr("Data storage management, debugging tools, device settings, screen behavior settings, system backups, and utilities to maintain, optimize, and troubleshoot FrogPilot."), "../../frogpilot/assets/toggle_icons/icon_system.png"},
    {tr("Theme and Appearance"), tr("FrogPilot settings for the current theme, driving-screen, and the overall user interface."), "../../frogpilot/assets/toggle_icons/icon_display.png"},
    {tr("Vehicle Controls"), tr("Options unique to supported manufacturers and vehicle fingerprint management."), "../../frogpilot/assets/toggle_icons/icon_vehicle.png"}
  };

  for (size_t i = 0; i < panelInfo.size(); ++i) {
    const QString &title = std::get<0>(panelInfo[i]);
    const QString &description = std::get<1>(panelInfo[i]);
    const QString &icon = std::get<2>(panelInfo[i]);

    const std::vector<std::tuple<QString, QWidget*>> &widgetLabels = panelButtons[i];

    std::vector<QString> labels;
    std::vector<QWidget*> widgets;

    for (size_t j = 0; j < widgetLabels.size(); ++j) {
      labels.push_back(std::get<0>(widgetLabels[j]));

      QWidget *panel = std::get<1>(widgetLabels[j]);
      panel->setContentsMargins(50, 25, 50, 25);

      ScrollView *panelFrame = new ScrollView(panel, this);
      mainLayout->addWidget(panelFrame);
      widgets.push_back(panelFrame);
    }

    FrogPilotButtonsControl *panelButton = new FrogPilotButtonsControl(title, description, icon, labels);
    if (title == tr("Driving Controls")) drivingPanelButtons = panelButton;
    if (title == tr("System Management")) systemPanelButtons = panelButton;
    if (title == tr("Vehicle Controls")) vehiclePanelButtons = panelButton;

    QObject::connect(panelButton, &FrogPilotButtonsControl::buttonClicked, [this, widgets](int id) {
      mainLayout->setCurrentWidget(widgets[id]);

      panelOpen = true;

      openPanel();
    });

    list->addItem(panelButton);
  }

  QObject::connect(frogpilotDevicePanel, &FrogPilotDevicePanel::openSubPanel, this, &FrogPilotSettingsWindow::openSubPanel);
  QObject::connect(frogpilotLateralPanel, &FrogPilotLateralPanel::openSubPanel, this, &FrogPilotSettingsWindow::openSubPanel);
  QObject::connect(frogpilotLongitudinalPanel, &FrogPilotLongitudinalPanel::openSubPanel, this, &FrogPilotSettingsWindow::openSubPanel);
  QObject::connect(frogpilotLongitudinalPanel, &FrogPilotLongitudinalPanel::openSubSubPanel, this, &FrogPilotSettingsWindow::openSubSubPanel);
  QObject::connect(frogpilotMapsPanel, &FrogPilotMapsPanel::openSubPanel, this, &FrogPilotSettingsWindow::openSubPanel);
  QObject::connect(frogpilotModelPanel, &FrogPilotModelPanel::openSubPanel, this, &FrogPilotSettingsWindow::openSubPanel);
  QObject::connect(frogpilotNavigationPanel, &FrogPilotNavigationPanel::closeSubSubPanel, this, &FrogPilotSettingsWindow::closeSubSubPanel);
  QObject::connect(frogpilotNavigationPanel, &FrogPilotNavigationPanel::openSubSubPanel, this, &FrogPilotSettingsWindow::openSubSubPanel);
  QObject::connect(frogpilotSoundsPanel, &FrogPilotSoundsPanel::openSubPanel, this, &FrogPilotSettingsWindow::openSubPanel);
  QObject::connect(frogpilotThemesPanel, &FrogPilotThemesPanel::openSubPanel, this, &FrogPilotSettingsWindow::openSubPanel);
  QObject::connect(frogpilotVehiclesPanel, &FrogPilotVehiclesPanel::openSubPanel, this, &FrogPilotSettingsWindow::openSubPanel);
  QObject::connect(frogpilotVisualsPanel, &FrogPilotVisualsPanel::openSubPanel, this, &FrogPilotSettingsWindow::openSubPanel);
  QObject::connect(frogpilotVisualsPanel, &FrogPilotVisualsPanel::openSubSubPanel, this, &FrogPilotSettingsWindow::openSubSubPanel);
}

FrogPilotSettingsWindow::FrogPilotSettingsWindow(SettingsWindow *parent) : QFrame(parent) {
  mainLayout = new QStackedLayout(this);

  QWidget *frogpilotWidget = new QWidget(this);
  QVBoxLayout *frogpilotLayout = new QVBoxLayout(frogpilotWidget);
  frogpilotLayout->setContentsMargins(50, 25, 50, 25);
  frogpilotWidget->setLayout(frogpilotLayout);

  frogpilotPanel = new ScrollView(frogpilotWidget, this);
  mainLayout->addWidget(frogpilotPanel);
  frogpilotPanel->setWidget(frogpilotWidget);

  FrogPilotListWidget *list = new FrogPilotListWidget(this);
  frogpilotLayout->addWidget(list);

  std::vector<QString> togglePresets{tr("Minimal"), tr("Standard"), tr("Advanced"), tr("Developer")};
  FrogPilotButtonsControl *togglePreset = new FrogPilotButtonsControl(tr("Tuning Level"),
                                          tr("The visibility and complexity of tuning settings. Lower levels simplify the interface by hiding advanced options, while higher levels unlock detailed customization.\n\n"
                                          "Minimal - Ideal for those who prefer simplicity or ease of use\n"
                                          "Standard - Recommended for most users for a balanced experience\n"
                                          "Advanced - Unlocks fine-tuning controls for more experienced users\n"
                                          "Developer - Unlocks highly customizable settings for seasoned enthusiasts"),
                                          "../../frogpilot/assets/toggle_icons/icon_customization.png",
                                          togglePresets, true);

  int timeTo100FPHours = 100 - (params_tracking.getInt("FrogPilotMinutes") / 60);
  int timeTo250OPHours = 250 - (params.getInt("KonikMinutes") / 60) - (params.getInt("openpilotMinutes") / 60);
  togglePreset->setEnabledButtons(3, timeTo100FPHours <= 0 || timeTo250OPHours <= 0);

  QObject::connect(togglePreset, &FrogPilotButtonsControl::buttonClicked, [this](int id) {
    tuningLevel = id;

    params.putInt("TuningLevel", tuningLevel);

    updateVariables();

    if (id == 3) {
      ConfirmationDialog::alert(tr("WARNING: This unlocks some potentially dangerous settings that can DRASTICALLY alter your driving experience!"), this);
    }
  });

  QObject::connect(togglePreset, &FrogPilotButtonsControl::disabledButtonClicked, [this](int id) {
    if (id == 3) {
      ConfirmationDialog::alert(tr("The <b>Developer</b> preset is only available for users with either over 100 hours on FrogPilot, or 250 hours with openpilot."), this);
    }
  });
  togglePreset->setCheckedButton(params.getInt("TuningLevel"));
  list->addItem(togglePreset, true);

  createPanelButtons(list);

  QObject::connect(parent, &SettingsWindow::closePanel, this, &FrogPilotSettingsWindow::closePanel);
  QObject::connect(parent, &SettingsWindow::closeSubPanel, this, &FrogPilotSettingsWindow::closeSubPanel);
  QObject::connect(parent, &SettingsWindow::closeSubSubPanel, this, &FrogPilotSettingsWindow::closeSubSubPanel);
  QObject::connect(parent, &SettingsWindow::updateMetric, this, &FrogPilotSettingsWindow::updateMetric);
  QObject::connect(uiState(), &UIState::offroadTransition, this, &FrogPilotSettingsWindow::updateVariables);
  QObject::connect(uiState(), &UIState::uiUpdate, this, &FrogPilotSettingsWindow::updateState);

  frogpilotToggleLevels = QJsonDocument::fromJson(params_memory.get("FrogPilotTuningLevels", true).c_str()).object();
  tuningLevel = params.getInt("TuningLevel");

  closeSubPanel();
  updateMetric(params.getBool("IsMetric"), true);
  updateVariables();
}

void FrogPilotSettingsWindow::hideEvent(QHideEvent *event) {
  closePanel();
}

void FrogPilotSettingsWindow::closePanel() {
  mainLayout->setCurrentWidget(frogpilotPanel);

  panelOpen = false;

  updateFrogPilotToggles();
}

void FrogPilotSettingsWindow::updateState() {
  FrogPilotUIState &fs = *frogpilotUIState();
  FrogPilotUIScene &frogpilot_scene = fs.frogpilot_scene;

  frogpilot_scene.frogpilot_panel_active = panelOpen && keepScreenOn;
}

void FrogPilotSettingsWindow::updateVariables() {
  std::string carParams = params.get("CarParamsPersistent");
  if (!carParams.empty()) {
    AlignedBuffer aligned_buf;
    capnp::FlatArrayMessageReader cmsg(aligned_buf.align(carParams.data(), carParams.size()));
    cereal::CarParams::Reader CP = cmsg.getRoot<cereal::CarParams>();
    cereal::CarParams::SafetyModel safetyModel = CP.getSafetyConfigs()[0].getSafetyModel();

    std::string carFingerprint = CP.getCarFingerprint();
    std::string carMake = CP.getCarName();

    friction = CP.getLateralTuning().getTorque().getFriction();
    hasAutoTune = (carMake == "hyundai" || carMake == "toyota") && CP.getLateralTuning().which() == cereal::CarParams::LateralTuning::TORQUE;
    hasBSM = CP.getEnableBsm();
    hasDashSpeedLimits = carMake == "ford" || carMake == "hyundai" || carMake == "toyota";
    hasExperimentalOpenpilotLongitudinal = CP.getExperimentalLongitudinalAvailable();
    hasNNFFLog = nnffLogFileExists(QString::fromStdString(carFingerprint));
    hasOpenpilotLongitudinal = hasLongitudinalControl(CP);
    hasPCMCruise = CP.getPcmCruise();
    hasPedal = CP.getEnableGasInterceptor();
    hasRadar = !CP.getRadarUnavailable();
    hasSNG = CP.getAutoResumeSng();
    isBolt = carFingerprint == "CHEVROLET_BOLT_CC" || carFingerprint == "CHEVROLET_BOLT_EUV";
    isGM = carMake == "gm";
    isHKG = carMake == "hyundai";
    isHKGCanFd = isHKG && safetyModel == cereal::CarParams::SafetyModel::HYUNDAI_CANFD;
    isSubaru = carMake == "subaru";
    isTorqueCar = CP.getLateralTuning().which() == cereal::CarParams::LateralTuning::TORQUE;
    isToyota = carMake == "toyota";
    isTSK = CP.getSecOcRequired();
    isVolt = carFingerprint == "CHEVROLET_VOLT";
    latAccelFactor = CP.getLateralTuning().getTorque().getLatAccelFactor();
    longitudinalActuatorDelay = CP.getLongitudinalActuatorDelay();
    startAccel = CP.getStartAccel();
    steerActuatorDelay = CP.getSteerActuatorDelay();
    steerKp = CP.getLateralTuning().getTorque().getKp();
    steerRatio = CP.getSteerRatio();
    stopAccel = CP.getStopAccel();
    stoppingDecelRate = CP.getStoppingDecelRate();
    vEgoStarting = CP.getVEgoStarting();
    vEgoStopping = CP.getVEgoStopping();

    float currentDelayStock = params.getFloat("SteerDelayStock");
    float currentFrictionStock = params.getFloat("SteerFrictionStock");
    float currentKPStock = params.getFloat("SteerKPStock");
    float currentLatAccelStock = params.getFloat("SteerLatAccelStock");
    float currentLongDelayStock = params.getFloat("LongitudinalActuatorDelayStock");
    float currentStartAccelStock = params.getFloat("StartAccelStock");
    float currentSteerRatioStock = params.getFloat("SteerRatioStock");
    float currentStopAccelStock = params.getFloat("StopAccelStock");
    float currentStoppingDecelRateStock = params.getFloat("StoppingDecelRateStock");
    float currentVEgoStartingStock = params.getFloat("VEgoStartingStock");
    float currentVEgoStoppingStock = params.getFloat("VEgoStoppingStock");

    if (currentDelayStock != steerActuatorDelay && steerActuatorDelay != 0) {
      if (params.getFloat("SteerDelay") == currentDelayStock || currentDelayStock == 0) {
        params.putFloat("SteerDelay", steerActuatorDelay);
      }
      params.putFloat("SteerDelayStock", steerActuatorDelay);
    }

    if (currentFrictionStock != friction && friction != 0) {
      if (params.getFloat("SteerFriction") == currentFrictionStock || currentFrictionStock == 0) {
        params.putFloat("SteerFriction", friction);
      }
      params.putFloat("SteerFrictionStock", friction);
    }

    if (currentKPStock != steerKp && steerKp != 0) {
      if (params.getFloat("SteerKP") == currentKPStock || currentKPStock == 0) {
        params.putFloat("SteerKP", steerKp);
      }
      params.putFloat("SteerKPStock", steerKp);
    }

    if (currentLatAccelStock != latAccelFactor && latAccelFactor != 0) {
      if (params.getFloat("SteerLatAccel") == currentLatAccelStock || currentLatAccelStock == 0) {
        params.putFloat("SteerLatAccel", latAccelFactor);
      }
      params.putFloat("SteerLatAccelStock", latAccelFactor);
    }

    if (currentLongDelayStock != longitudinalActuatorDelay && longitudinalActuatorDelay != 0) {
      if (params.getFloat("LongitudinalActuatorDelay") == currentLongDelayStock || currentLongDelayStock == 0) {
        params.putFloat("LongitudinalActuatorDelay", longitudinalActuatorDelay);
      }
      params.putFloat("LongitudinalActuatorDelayStock", longitudinalActuatorDelay);
    }

    if (currentStartAccelStock != startAccel && startAccel != 0) {
      if (params.getFloat("StartAccel") == currentStartAccelStock || currentStartAccelStock == 0) {
        params.putFloat("StartAccel", startAccel);
      }
      params.putFloat("StartAccelStock", startAccel);
    }

    if (currentSteerRatioStock != steerRatio && steerRatio != 0) {
      if (params.getFloat("SteerRatio") == currentSteerRatioStock || currentSteerRatioStock == 0) {
        params.putFloat("SteerRatio", steerRatio);
      }
      params.putFloat("SteerRatioStock", steerRatio);
    }

    if (currentStopAccelStock != stopAccel && stopAccel != 0) {
      if (params.getFloat("StopAccel") == currentStopAccelStock || currentStopAccelStock == 0) {
        params.putFloat("StopAccel", stopAccel);
      }
      params.putFloat("StopAccelStock", stopAccel);
    }

    if (currentStoppingDecelRateStock != stoppingDecelRate && stoppingDecelRate != 0) {
      if (params.getFloat("StoppingDecelRate") == currentStoppingDecelRateStock || currentStoppingDecelRateStock == 0) {
        params.putFloat("StoppingDecelRate", stoppingDecelRate);
      }
      params.putFloat("StoppingDecelRateStock", stoppingDecelRate);
    }

    if (currentVEgoStartingStock != vEgoStarting && vEgoStarting != 0) {
      if (params.getFloat("VEgoStarting") == currentVEgoStartingStock || currentVEgoStartingStock == 0) {
        params.putFloat("VEgoStarting", vEgoStarting);
      }
      params.putFloat("VEgoStartingStock", vEgoStarting);
    }

    if (currentVEgoStoppingStock != vEgoStopping && vEgoStopping != 0) {
      if (params.getFloat("VEgoStopping") == currentVEgoStoppingStock || currentVEgoStoppingStock == 0) {
        params.putFloat("VEgoStopping", vEgoStopping);
      }
      params.putFloat("VEgoStoppingStock", vEgoStopping);
    }
  }

  std::string frogpilotCarParams = params.get("FrogPilotCarParamsPersistent");
  if (!frogpilotCarParams.empty()) {
    AlignedBuffer aligned_buf;
    capnp::FlatArrayMessageReader fpcmsg(aligned_buf.align(frogpilotCarParams.data(), frogpilotCarParams.size()));
    cereal::FrogPilotCarParams::Reader FPCP = fpcmsg.getRoot<cereal::FrogPilotCarParams>();

    openpilotLongitudinalControlDisabled = FPCP.getOpenpilotLongitudinalControlDisabled();
    tacoHacksAllowed = isHKGCanFd && !FPCP.getIsHDA2();
  }

  isC3 = util::read_file("/sys/firmware/devicetree/base/model").find("tici") != std::string::npos;

  drivingPanelButtons->setVisibleButton(0, tuningLevel >= frogpilotToggleLevels.value("Model").toDouble());
  drivingPanelButtons->setVisibleButton(1, hasOpenpilotLongitudinal);

  systemPanelButtons->setVisibleButton(1, tuningLevel >= frogpilotToggleLevels.value("DeviceManagement").toDouble() || tuningLevel >= frogpilotToggleLevels.value("ScreenManagement").toDouble());

  vehiclePanelButtons->setVisibleButton(1, tuningLevel >= frogpilotToggleLevels.value("WheelControls").toDouble());

  update();
}
