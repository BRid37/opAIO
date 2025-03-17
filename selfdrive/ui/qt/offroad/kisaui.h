#pragma once

#include <QWidget>
#include <QVBoxLayout>
#include "selfdrive/ui/qt/widgets/kisapilot.h" // kisapilot

class SettingsWindow;

class UIPanel : public QWidget {
  Q_OBJECT
public:
  explicit UIPanel(SettingsWindow *parent);

private:
  QVBoxLayout *layout;
};