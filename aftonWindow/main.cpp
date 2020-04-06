#include "window.h"
#include <QGuiApplication>

#include <QDebug>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    // Set OpenGL Version information
    qDebug() << "Set OpenGL Version information";

      QSurfaceFormat format;
      format.setRenderableType(QSurfaceFormat::OpenGL);
      format.setProfile(QSurfaceFormat::CoreProfile);
      format.setVersion(3, 3);

      qDebug() << "Set the window up";
      // Set the window up
      Window window;
      window.setFormat(format);
      window.resize(QSize(800, 600));
      window.show();

    return app.exec();
}
