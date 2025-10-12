#include "frogpilot/ui/qt/offroad/data_settings.h"

FrogPilotDataPanel::FrogPilotDataPanel(FrogPilotSettingsWindow *parent) : FrogPilotListWidget(parent), parent(parent) {
  QJsonObject shownDescriptions = QJsonDocument::fromJson(QString::fromStdString(params.get("ShownToggleDescriptions")).toUtf8()).object();
  QString className = this->metaObject()->className();

  bool forceOpenDescriptions = false;
  if (!shownDescriptions.value(className).toBool(false)) {
    forceOpenDescriptions = true;
    shownDescriptions.insert(className, true);
    params.put("ShownToggleDescriptions", QJsonDocument(shownDescriptions).toJson(QJsonDocument::Compact).toStdString());
  }

  QStackedLayout *dataLayout = new QStackedLayout();
  addItem(dataLayout);

  FrogPilotListWidget *dataMainList = new FrogPilotListWidget(this);
  ScrollView *dataMainPanel = new ScrollView(dataMainList, this);
  dataLayout->addWidget(dataMainPanel);
}
