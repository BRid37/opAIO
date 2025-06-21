#pragma once

#include <map>
#include <string>

#include <QButtonGroup>
#include <QFrame>
#include <QLabel>
#include <QPushButton>
#include <QStackedWidget>
#include <QWidget>

#include "selfdrive/ui/ui.h"
#include "selfdrive/ui/qt/util.h"
#include "selfdrive/ui/qt/widgets/controls.h"

// ********** settings window + top-level panels **********
class SettingsWindow : public QFrame {
  Q_OBJECT

public:
  explicit SettingsWindow(QWidget *parent = 0);
  void setCurrentPanel(int index, const QString &param = "");

protected:
  void showEvent(QShowEvent *event) override;

  // FrogPilot widgets
  void hideEvent(QHideEvent *event) override;

signals:
  void closeSettings();
  void reviewTrainingGuide();
  void showDriverView();
  void expandToggleDescription(const QString &param);

  // FrogPilot signals
  void closeMapBoxInstructions();
  void closeMapSelection();
  void closePanel();
  void closeParentToggle();
  void closeSubParentToggle();
  void updateMetric(bool metric, bool bootRun=false);

private:
  QPushButton *sidebar_alert_widget;
  QWidget *sidebar_widget;
  QButtonGroup *nav_btns;
  QStackedWidget *panel_widget;

  // FrogPilot variables
  Params params;
  Params paramsTracking{"/cache/tracking"};

  bool mapboxInstructionsOpen;
  bool mapSelectionOpen;
  bool panelOpen;
  bool parentToggleOpen;
  bool subParentToggleOpen;
};

class DevicePanel : public ListWidget {
  Q_OBJECT
public:
  explicit DevicePanel(SettingsWindow *parent);
  void showEvent(QShowEvent *event) override;

signals:
  void reviewTrainingGuide();
  void showDriverView();

private slots:
  void poweroff();
  void reboot();
  void updateCalibDescription();

private:
  Params params;
  ButtonControl *pair_device;

  // FrogPilot variables
  Params params_cache{"/cache/params"};
};

class TogglesPanel : public ListWidget {
  Q_OBJECT
public:
  explicit TogglesPanel(SettingsWindow *parent);
  void showEvent(QShowEvent *event) override;

signals:
  // FrogPilot signals
  void updateMetric(bool metric, bool bootRun=false);

public slots:
  void expandToggleDescription(const QString &param);

private slots:
  void updateState(const UIState &s);

private:
  Params params;
  std::map<std::string, ParamControl*> toggles;
  ButtonParamControl *long_personality_setting;

  void updateToggles();
};

class SoftwarePanel : public ListWidget {
  Q_OBJECT
public:
  explicit SoftwarePanel(QWidget* parent = nullptr);

private:
  void showEvent(QShowEvent *event) override;
  void updateLabels();
  void checkForUpdates();

  bool is_onroad = false;

  QLabel *onroadLbl;
  LabelControl *versionLbl;
  ButtonControl *installBtn;
  ButtonControl *downloadBtn;
  ButtonControl *targetBranchBtn;

  Params params;
  ParamWatcher *fs_watch;

  // FrogPilot variables
  Params params_memory{"/dev/shm/params"};
};
