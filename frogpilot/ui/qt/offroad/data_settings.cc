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

  FrogPilotListWidget *statsLabelsList = new FrogPilotListWidget(this);
  ScrollView *statsLabelsPanel = new ScrollView(statsLabelsList, this);
  dataLayout->addWidget(statsLabelsPanel);

  FrogPilotButtonsControl *viewStatsButton = new FrogPilotButtonsControl(tr("FrogPilot Stats"), tr("<b>View your collected FrogPilot stats.</b>"), "", {tr("RESET"), tr("VIEW")});
  QObject::connect(viewStatsButton, &FrogPilotButtonsControl::buttonClicked, [dataLayout, statsLabelsPanel, this](int id) {
    if (id == 0) {
      if (ConfirmationDialog::confirm(tr("Are you sure you want to reset all of your FrogPilot stats?"), tr("Reset"), this)) {
        params.remove("FrogPilotStats");
        params_cache.remove("FrogPilotStats");
      }
    } else if (id == 1) {
      emit openSubPanel();
      dataLayout->setCurrentWidget(statsLabelsPanel);
    }
  });
  if (forceOpenDescriptions) {
    viewStatsButton->showDescription();
  }
  dataMainList->addItem(viewStatsButton);

  QObject::connect(parent, &FrogPilotSettingsWindow::closeSubPanel, [dataLayout, dataMainPanel] {
    dataLayout->setCurrentWidget(dataMainPanel);
  });
  QObject::connect(parent, &FrogPilotSettingsWindow::updateMetric, [this](bool metric){isMetric = metric;});
  QObject::connect(uiState(), &UIState::offroadTransition, [statsLabelsList, this](bool offroad) {
    if (offroad) {
      updateStatsLabels(statsLabelsList);
    }
  });

  updateStatsLabels(statsLabelsList);
}

void FrogPilotDataPanel::updateStatsLabels(FrogPilotListWidget *labelsList) {
  labelsList->clear();

  QJsonObject stats = QJsonDocument::fromJson(QString::fromStdString(params.get("FrogPilotStats")).toUtf8()).object();

  static QSet<QString> ignored_keys = {
    "Month"
  };

  static QMap<QString, QPair<QString, QString>> key_map = {
    {"AEBEvents", {tr("Total Emergency Brake Alerts"), "count"}},
    {"AOLTime", {tr("Time Using \"Always On Lateral\""), "time"}},
    {"CruiseSpeedTimes", {tr("Favorite Set Speed"), "speed"}},
    {"CurrentMonthsKilometers", {tr("Distance Driven This Month"), "distance"}},
    {"DayTime", {tr("Time Driving (Daytime)"), "time"}},
    {"Disengages", {tr("Total Disengagements"), "count"}},
    {"Engages", {tr("Total Engagements"), "count"}},
    {"ExperimentalModeTime", {tr("Time Using \"Experimental Mode\""), "time"}},
    {"FrogChirps", {tr("Total Frog Chirps"), "count"}},
    {"FrogHops", {tr("Total Frog Hops"), "count"}},
    {"FrogPilotDrives", {tr("Total Drives"), "count"}},
    {"FrogPilotMeters", {tr("Total Distance Driven"), "distance"}},
    {"FrogPilotSeconds", {tr("Total Driving Time"), "time"}},
    {"FrogSqueaks", {tr("Total Frog Squeaks"), "count"}},
    {"GoatScreams", {tr("Total Goat Screams"), "count"}},
    {"HighestAcceleration", {tr("Highest Acceleration Rate"), "accel"}},
    {"LateralTime", {tr("Time Using Lateral Control"), "time"}},
    {"LongestDistanceWithoutOverride", {tr("Longest Distance Without an Override"), "distance"}},
    {"LongitudinalTime", {tr("Time Using Longitudinal Control"), "time"}},
    {"ModelTimes", {tr("Driving Models:"), "other"}},
    {"Month", {tr("Month"), "other"}},
    {"NightTime", {tr("Time Driving (Nighttime)"), "time"}},
    {"Overrides", {tr("Total Overrides"), "count"}},
    {"OverrideTime", {tr("Time Overriding openpilot"), "time"}},
    {"PersonalityTimes", {tr("Driving Personalities:"), "other"}},
    {"RandomEvents", {tr("Random Events:"), "other"}},
    {"StandstillTime", {tr("Time Stopped"), "time"}},
    {"StopLightTime", {tr("Time Spent at Stoplights"), "time"}},
    {"TrackedTime", {tr("Total Time Tracked"), "time"}},
    {"WeatherTimes", {tr("Time Driven (Weather):"), "other"}}
  };

  static QSet<QString> parent_keys = {
    "ModelTimes",
    "PersonalityTimes",
    "RandomEvents",
    "WeatherTimes"
  };

  static QSet<QString> percentage_keys = {
    "AOLTime",
    "DayTime",
    "ExperimentalModeTime",
    "LateralTime",
    "LongitudinalTime",
    "NightTime",
    "OverrideTime",
    "StandstillTime",
    "StopLightTime"
  };

  static QMap<QString, QString> random_events_map = {
    {"accel30", tr("UwUs")},
    {"accel35", tr("Loch Ness Encounters")},
    {"accel40", tr("Visits to 1955")},
    {"dejaVuCurve", tr("Deja Vu Moments")},
    {"firefoxSteerSaturated", tr("Internet Explorer Weeeeeeees")},
    {"hal9000", tr("HAL 9000 Denials")},
    {"openpilotCrashedRandomEvent", tr("openpilot Crashes")},
    {"thisIsFineSteerSaturated", tr("This Is Fine Moments")},
    {"toBeContinued", tr("To Be Continued Moments")},
    {"vCruise69", tr("Noices")},
    {"yourFrogTriedToKillMe", tr("Attempted Frog Murders")},
    {"youveGotMail", tr("Total Mail Received")}
  };

  QStringList keys = key_map.keys();
  std::sort(keys.begin(), keys.end(), [&](const QString &a, const QString &b) {
    return key_map.value(a).first.toLower() < key_map.value(b).first.toLower();
  });

  double tracked_time = stats.contains("TrackedTime") ? stats.value("TrackedTime").toDouble() : 0.0;

  std::function<QString(double)> format_number = [&](double number) {
    return QLocale().toString(number);
  };

  std::function<QString(double)> format_distance = [&](double meters) {
    double value;
    QString unit;
    if (isMetric) {
      value = meters / 1000.0;
      unit = (value == 1.0) ? tr(" kilometer") : tr(" kilometers");
    } else {
      value = meters * METER_TO_MILE;
      unit = (value == 1.0) ? tr(" mile") : tr(" miles");
    }
    return format_number(qRound(value)) + unit;
  };

  std::function<QString(int)> format_time = [&](int seconds) {
    static int seconds_in_day = 60 * 60 * 24;
    static int seconds_in_hour = 60 * 60;

    int days = seconds / seconds_in_day;
    int hours = (seconds % seconds_in_day) / seconds_in_hour;
    int minutes = (seconds % seconds_in_hour) / 60;

    QString result;
    if (days > 0) result += format_number(days) + (days == 1 ? tr(" day ") : tr(" days "));
    if (hours > 0 || days > 0) result += format_number(hours) + (hours == 1 ? tr(" hour ") : tr(" hours "));
    result += format_number(minutes) + (minutes == 1 ? tr(" minute") : tr(" minutes"));
    return result.trimmed();
  };

  for (const QString &key : keys) {
    if (ignored_keys.contains(key)) continue;

    QJsonValue value = stats.contains(key) ? stats.value(key) : QJsonValue(0);
    QString label_text = key_map.value(key).first;
    QString type = key_map.value(key).second;

    if (key == "AEBEvents") {
      QJsonObject totalEvents = stats.value("TotalEvents").toObject();

      QString trimmed_label = label_text;
      if (trimmed_label.startsWith(tr("Total "))) {
        trimmed_label = trimmed_label.mid(6);
      }
      QString display_value = format_number(totalEvents.value("stockAeb").toInt(0) + totalEvents.value("fcw").toInt(0)) + " " + trimmed_label;

      labelsList->addItem(new LabelControl(label_text, display_value, "", this));

    } else if (key == "CruiseSpeedTimes" && value.isObject()) {
      QJsonObject speeds = value.toObject();

      double max_time = -1.0;
      QString best_speed;
      for (const QString &speed_key : speeds.keys()) {
        double time = speeds.value(speed_key).toDouble();
        if (time > max_time) {
          best_speed = speed_key;
          max_time = time;
        }
      }

      QString display_speed;
      if (isMetric) {
        display_speed = QString::number(qRound(best_speed.toDouble() * MS_TO_KPH)) + " " + tr("km/h");
      } else {
        display_speed = QString::number(qRound(best_speed.toDouble() * MS_TO_MPH)) + " " + tr("mph");
      }

      labelsList->addItem(new LabelControl(label_text, display_speed + " (" + format_time(max_time) + ")", "", this));
    } else if (parent_keys.contains(key) && value.isObject()) {
      labelsList->addItem(new LabelControl(label_text, "", "", this));

      QJsonObject subobj = value.toObject();
      QStringList subkeys;

      if (key == "RandomEvents") {
        subkeys = random_events_map.keys();
      } else {
        subkeys = subobj.keys();
      }

      std::sort(subkeys.begin(), subkeys.end(), [&](const QString &a, const QString &b) {
        QString display_a, display_b;
        if (key == "ModelTimes") {
          display_a = cleanModelName(a);
          display_b = cleanModelName(b);
        } else if (key == "RandomEvents") {
          display_a = random_events_map.value(a, a);
          display_b = random_events_map.value(b, b);
        } else if (key == "WeatherTimes") {
          display_a = a.left(1).toUpper() + a.mid(1);
          display_b = b.left(1).toUpper() + b.mid(1);
        } else {
          display_a = a;
          display_b = b;
        }
        return display_a.toLower() < display_b.toLower();
      });

      for (const QString &subkey : subkeys) {
        if (subkey == "Unknown") {
          continue;
        }

        QString display_subkey;
        if (key == "ModelTimes") {
          display_subkey = cleanModelName(subkey);
        } else if (key == "RandomEvents") {
          display_subkey = random_events_map.value(subkey, subkey);
        } else if (key == "WeatherTimes") {
          display_subkey = subkey.left(1).toUpper() + subkey.mid(1);
        } else {
          display_subkey = subkey;
        }

        QString subvalue;
        if (key == "ModelTimes" || key == "PersonalityTimes" || key == "WeatherTimes") {
          subvalue = format_time(subobj.value(subkey).toDouble());
        } else {
          subvalue = format_number(subobj.value(subkey).toInt(0));
        }

        labelsList->addItem(new LabelControl("     " + display_subkey, subvalue, "", this));
      }
    } else {
      QString display_value;
      if (type == "accel") {
        display_value = QString::number(value.toDouble(), 'f', 2) + " " + tr("m/s²");
      } else if (type == "count") {
        QString trimmed_label = label_text;
        if (trimmed_label.startsWith(tr("Total "))) {
          trimmed_label = trimmed_label.mid(6);
        }
        display_value = format_number(value.toInt()) + " " + trimmed_label;
      } else if (type == "distance") {
        display_value = format_distance(value.toDouble());
      } else if (type == "time") {
        display_value = format_time(value.toDouble());
      } else {
        QString str_val = value.toVariant().toString();
        display_value = str_val.isEmpty() ? "0" : str_val;
      }

      labelsList->addItem(new LabelControl(label_text, display_value, "", this));

      if (percentage_keys.contains(key)) {
        int percent = 0;
        if (tracked_time > 0.0) {
          percent = (value.toDouble() * 100.0) / tracked_time;
        }

        labelsList->addItem(new LabelControl(tr("% of ") + label_text, format_number(percent) + "%", "", this));
      }
    }
  }
}
