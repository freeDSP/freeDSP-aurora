#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include <QList>
#include <QDataStream>
#include <QTcpSocket>
#include <QByteArray>

#include "figure/QFigure.h"
#include "QChannel.hpp"
#include "QDspBlock.hpp"
#include "QHighPass.hpp"
#include "QLowPass.hpp"
#include "QPeq.hpp"
#include "QPhase.hpp"
#include "QGain.hpp"
#include "QDelay.hpp"
#include "QLowShelv.hpp"
#include "QHighShelv.hpp"
#include "QInputSelect.hpp"
#include "QOutputSelect.hpp"
#include "dialoglicense.hpp"

#include "vektorraum.h"

#include "freeDSP-Aurora.hpp"

class QTcpSocket;
class QNetworkSession;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  enum twifistatus
  {
    STATUS_WIFI_IDLE,
    STATUS_WIFI_RECEIVE_USERPARAM
  };

public:
  explicit MainWindow(QWidget *parent = nullptr);
  ~MainWindow();


public slots:
  void showLicense( void );
  void updatePlots( void );
  void importRewPeqs( QWidget* );

private slots:
  void on_actionWrite_to_DSP_triggered();

  void on_actionAbout_triggered();

  void on_actionSettings_triggered();

  void on_volumeSliderMain_valueChanged( double val );

  void on_actionRead_from_DSP_triggered();

signals:
  void replyFinished( void );  

private:
  Ui::MainWindow *ui;

  Vektorraum::tvector<Vektorraum::tfloat> freq;
  Vektorraum::tfloat fs = 48000.0;
  unsigned int numChannels;

  CFreeDspAurora dsp;

  QString portName;
  QList<QGain*> listOutputGains;
};

#endif // MAINWINDOW_HPP
