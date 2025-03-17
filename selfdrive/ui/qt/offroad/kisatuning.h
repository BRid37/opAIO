#pragma once

#include <QWidget>
#include <QVBoxLayout>
#include "selfdrive/ui/qt/widgets/kisapilot.h" // kisapilot

class SettingsWindow;

class TuningPanel : public QWidget {
  Q_OBJECT
public:
  explicit TuningPanel(SettingsWindow *parent);

private:
  QVBoxLayout *layout;
};