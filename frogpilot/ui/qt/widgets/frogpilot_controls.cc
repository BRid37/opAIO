#include "selfdrive/ui/ui.h"

#include "frogpilot/ui/frogpilot_ui.h"

void clearMovie(QSharedPointer<QMovie> &movie, QWidget *parent) {
  if (movie) {
    QObject::disconnect(movie.data(), &QMovie::frameChanged, parent, nullptr);
    movie->stop();
    movie.clear();
  }
}

void loadGif(const QString &gifPath, QSharedPointer<QMovie> &movie, const QSize &size, QWidget *parent) {
  clearMovie(movie, parent);

  if (QFileInfo::exists(gifPath)) {
    movie = QSharedPointer<QMovie>::create(gifPath, QByteArray(), parent);
    movie->setCacheMode(QMovie::CacheAll);
    movie->setScaledSize(size);

    QObject::connect(movie.data(), &QMovie::frameChanged, parent, [parent](int) {
      if (parent) {
        parent->update();
      }
    }, Qt::UniqueConnection);

    movie->start();
  }

  if (parent) {
    parent->update();
  }
}

void loadImage(const QString &basePath, QPixmap &pixmap, QSharedPointer<QMovie> &movie, const QSize &size, QWidget *parent) {
  const QString gifPath = basePath + ".gif";

  if (QFileInfo::exists(gifPath)) {
    pixmap = QPixmap();
    loadGif(gifPath, movie, size, parent);
  } else {
    clearMovie(movie, parent);
    pixmap = QPixmap(basePath + ".png").scaled(size, Qt::KeepAspectRatio, Qt::SmoothTransformation);

    if (parent) {
      parent->update();
    }
  }
}
