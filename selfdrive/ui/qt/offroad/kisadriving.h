#pragma once

#include <QWidget>
#include <QVBoxLayout>
#include "selfdrive/ui/qt/widgets/kisapilot.h" // kisapilot

class SettingsWindow;

class DrivingPanel : public QWidget {
  Q_OBJECT
public:
  explicit DrivingPanel(SettingsWindow *parent);

private:
  QVBoxLayout *layout;
};