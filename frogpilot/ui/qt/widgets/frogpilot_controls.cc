#include "selfdrive/ui/ui.h"

#include "frogpilot/ui/frogpilot_ui.h"

bool FrogPilotConfirmationDialog::toggleReboot(QWidget *parent) {
  ConfirmationDialog d(tr("Reboot required to take effect."), tr("Reboot Now"), tr("Reboot Later"), false, parent);
  return d.exec();
}

bool FrogPilotConfirmationDialog::yesorno(const QString &prompt_text, QWidget *parent) {
  ConfirmationDialog d(prompt_text, tr("Yes"), tr("No"), false, parent);
  return d.exec();
}

void clearMovie(QSharedPointer<QMovie> &movie, QWidget *parent) {
  if (!movie) {
    return;
  }

  QObject::disconnect(movie.data(), nullptr, parent, nullptr);
  movie->stop();
  movie.reset();
}

void loadGif(const QString &gifPath, QSharedPointer<QMovie> &movie, const QSize &size, QWidget *parent) {
  clearMovie(movie, parent);

  movie = QSharedPointer<QMovie>::create(gifPath);
  movie->setCacheMode(QMovie::CacheAll);
  movie->setScaledSize(size);

  QPointer<QWidget> safeParent(parent);
  QObject::connect(movie.data(), &QMovie::frameChanged, parent, [safeParent]() {
    if (safeParent && safeParent->isVisible()) {
      safeParent->update();
    }
  }, Qt::UniqueConnection);

  movie->start();
}

void loadImage(const QString &basePath, QPixmap &pixmap, QSharedPointer<QMovie> &movie, const QSize &size, QWidget *parent) {
  if (!parent) {
    return;
  }

  QString gifPath = basePath + ".gif";
  if (QFileInfo::exists(gifPath)) {
    loadGif(gifPath, movie, size, parent);
    if (!pixmap.isNull()) {
      pixmap = QPixmap();
      parent->update();
    }
    return;
  }

  QString pngPath = basePath + ".png";

  clearMovie(movie, parent);

  QPixmap loadedPixmap(pngPath);
  if (!loadedPixmap.isNull()) {
    pixmap = loadedPixmap.scaled(size, Qt::KeepAspectRatio, Qt::SmoothTransformation);
  } else {
    pixmap = QPixmap();
  }

  parent->update();
}

void openDescriptions(bool forceOpenDescriptions, std::map<QString, AbstractControl*> toggles) {
  if (forceOpenDescriptions) {
    for (auto &[key, toggle] : toggles) {
      if (key != "CESpeed") {
        toggle->showDescription();
      }
    }
  }
}
