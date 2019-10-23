#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include <QList>
#include <QDataStream>
#include <QTcpSocket>
#include <QByteArray>
#include <QMessageBox>

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
#include "QPreset.h"

#include "vektorraum.h"

#include "freeDSP-Aurora.hpp"
#include "DspPlugIn.hpp"

class QTcpSocket;
class QNetworkSession;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

private:
  //============================================================================
  /*!
   */
  void rotateIconConnect( int rotation );

  //============================================================================
  /*!
   */
  void updatePresetGui( int p, QByteArray& userparams );

  //============================================================================
  /*!
   */
  void writeSettings( void );

  //==============================================================================
  /*!
   */
  void switchPluginGui( uint32_t pid );


public slots:
  void showLicense( void );
  void updatePlots( void );
  void importRewPeqs( QWidget* );

private slots:
  void on_actionWrite_to_DSP_triggered();

  void on_actionAbout_triggered();

  void on_actionSettings_triggered();

  void on_volumeSliderMain_valueChanged( double val );

  void on_actionRead_from_DSP_triggered( void );

  void updateWaitingForConnect( void );

  void on_tabPresets_currentChanged(int index);

signals:
  void replyFinished( void );  

private:
  Ui::MainWindow *ui;

  Vektorraum::tvector<Vektorraum::tfloat> freq;
  Vektorraum::tfloat fs = 48000.0;
  unsigned int numChannels;

  CFreeDspAurora dsp;
  CDspPlugin* dspPlugin[NUMPRESETS];

  QString portName;

  int currentWaitRotation = 0;
  QMessageBox* msgBox;

  QPreset* presets[NUMPRESETS];
  int currentPreset = 0;
  QByteArray presetUserParams[NUMPRESETS];
  QJsonObject jsonObjSettings;
};

#endif // MAINWINDOW_HPP
