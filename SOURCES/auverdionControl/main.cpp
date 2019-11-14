#include "MainWindow.hpp"
#include <QApplication>
#include <QFile>
#include <QStandardPaths>

#include "LogFile.h"

CLogFile myLog;

int main(int argc, char *argv[])
{
  QApplication::setOrganizationName("auverdion");
  QApplication::setApplicationName( "auverdionControl" );
  #if defined( __IOS__ )
  QGuiApplication::setAttribute( Qt::AA_UseHighDpiPixmaps );
  QGuiApplication::setAttribute( Qt::AA_EnableHighDpiScaling );
  #endif

  QApplication app(argc, argv);

  

  QFile fileStyleSheet( QStringLiteral(":/freedsp.qss") );
  if( fileStyleSheet.open(QIODevice::ReadOnly | QIODevice::Text) )
  {
    QString stylesheet = QString::fromLatin1( fileStyleSheet.readAll() );
    app.setStyleSheet( stylesheet );
    fileStyleSheet.close();
  }

  QPalette p(app.palette());
  p.setColor(QPalette::Mid, p.color(QPalette::Base));
  app.setPalette(p);

  MainWindow w;
  w.show();

  return app.exec();
}
