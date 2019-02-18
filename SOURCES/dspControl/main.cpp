#include "MainWindow.hpp"
#include <QApplication>
#include <QFile>

int main(int argc, char *argv[])
{
  QApplication::setOrganizationName("Raphael Knoop");
  QApplication::setApplicationName( "dspControl" );
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

  MainWindow w;
  w.show();

  return app.exec();
}
