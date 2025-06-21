#include "selfdrive/ui/qt/request_repeater.h"
#include "selfdrive/ui/qt/util.h"

#include "selfdrive/frogpilot/ui/qt/widgets/drive_stats.h"

static QLabel *newLabel(const QString &text, const QString &type) {
  QLabel *label = new QLabel(text);
  label->setProperty("type", type);
  return label;
}

DriveStats::DriveStats(QWidget *parent) : QFrame(parent) {
  metric = params.getBool("IsMetric");

  QVBoxLayout *main_layout = new QVBoxLayout(this);
  main_layout->setContentsMargins(50, 25, 50, 20);

  addStatsLayouts(tr("ALL TIME"), all);
  addStatsLayouts(tr("PAST WEEK"), week);
  addStatsLayouts(tr("FROGPILOT"), frogPilot, true);

  std::optional<QString> dongleId = getDongleId();
  if (dongleId.has_value()) {
    QString url = CommaApi::BASE_URL + "/v1.1/devices/" + dongleId.value() + "/stats";
    RequestRepeater *repeater = new RequestRepeater(this, url, "ApiCache_DriveStats", 30);
    QObject::connect(repeater, &RequestRepeater::requestDone, this, &DriveStats::parseResponse);
  }

  setStyleSheet(R"(
    DriveStats {
      background-color: #333333;
      border-radius: 10px;
    }

    QLabel[type="title"] { font-size: 50px; font-weight: 500; }
    QLabel[type="frogpilot_title"] { font-size: 50px; font-weight: 500; color: #178643; }
    QLabel[type="number"] { font-size: 65px; font-weight: 400; }
    QLabel[type="unit"] { font-size: 50px; font-weight: 300; color: #A0A0A0; }
  )");
}

void DriveStats::addStatsLayouts(const QString &title, StatsLabels &labels, bool FrogPilot) {
  QGridLayout *grid_layout = new QGridLayout;
  grid_layout->setVerticalSpacing(10);
  grid_layout->setContentsMargins(0, 10, 0, 10);

  int row = 0;
  grid_layout->addWidget(newLabel(title, FrogPilot ? "frogpilot_title" : "title"), row++, 0, 1, 3);
  grid_layout->addItem(new QSpacerItem(0, 10), row++, 0, 1, 1);

  grid_layout->addWidget(labels.routes = newLabel("0", "number"), row, 0, Qt::AlignLeft);
  grid_layout->addWidget(labels.distance = newLabel("0", "number"), row, 1, Qt::AlignLeft);
  grid_layout->addWidget(labels.hours = newLabel("0", "number"), row, 2, Qt::AlignLeft);

  grid_layout->addWidget(newLabel(tr("Drives"), "unit"), row + 1, 0, Qt::AlignLeft);
  grid_layout->addWidget(labels.distance_unit = newLabel(getDistanceUnit(), "unit"), row + 1, 1, Qt::AlignLeft);
  grid_layout->addWidget(newLabel(tr("Hours"), "unit"), row + 1, 2, Qt::AlignLeft);

  QVBoxLayout *main_layout = static_cast<QVBoxLayout *>(layout());
  main_layout->addLayout(grid_layout);
  main_layout->addStretch(1);
}

void DriveStats::updateStatsForLabel(const QJsonObject &obj, StatsLabels &labels) {
  labels.routes->setText(QString::number((int)obj["routes"].toDouble()));
  labels.distance->setText(QString::number(int(obj["distance"].toDouble() * (metric ? MILE_TO_KM : 1))));
  labels.distance_unit->setText(getDistanceUnit());
  labels.hours->setText(QString::number((int)(obj["minutes"].toDouble() / 60)));
}

void DriveStats::updateFrogPilotStats(const QJsonObject &obj, StatsLabels &labels) {
  labels.routes->setText(QString::number(paramsTracking.getInt("FrogPilotDrives")));
  labels.distance->setText(QString::number(int(paramsTracking.getFloat("FrogPilotKilometers") * (metric ? 1 : KM_TO_MILE))));
  labels.distance_unit->setText(getDistanceUnit());
  labels.hours->setText(QString::number(int(paramsTracking.getFloat("FrogPilotMinutes") / 60)));
}

void DriveStats::updateStats() {
  QJsonObject json = stats.object();

  updateFrogPilotStats(json["frogpilot"].toObject(), frogPilot);
  updateStatsForLabel(json["all"].toObject(), all);
  updateStatsForLabel(json["week"].toObject(), week);

  int all_time_minutes = (int)(json["all"].toObject()["minutes"].toDouble());
  params.put("openpilotMinutes", QString::number(all_time_minutes).toStdString());
}

void DriveStats::parseResponse(const QString &response, bool success) {
  if (!success) {
    return;
  }

  QJsonDocument doc = QJsonDocument::fromJson(response.trimmed().toUtf8());
  if (doc.isNull()) {
    qDebug() << "JSON Parse failed on getting past drives statistics";
    return;
  }
  stats = doc;
  updateStats();
}

void DriveStats::showEvent(QShowEvent *event) {
  metric = params.getBool("IsMetric");
  updateStats();
}
