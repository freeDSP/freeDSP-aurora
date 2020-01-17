#include <QProxyStyle>
#include <QStyleOptionTab>
#include <QLabel>
#include <QVBoxLayout>
#include <QPushButton>
#include <QDialog>
#include <QFileDialog>
#include <QtNetwork>
#include <QHostAddress>
#include <QProgressDialog>
#include <QJsonObject>
#include <QJsonDocument>
#include <QStatusBar>

#include "MainWindow.hpp"
#include "ui_MainWindow.h"

#include "QSleeper.hpp"

#include "DialogSettings.hpp"
#include "QDialogDemoSelector.hpp"
#include "DialogReleaseNotes.h"
#include "DialogConnect.h"
#include "WizardImportRewPeq.hpp"

#include "PlugIn8Channels.hpp"
#include "PlugInHomeCinema71.hpp"
#include "PlugIn4FIRs.hpp"
#include "PlugIn8ChannelsUSB.hpp"
#include "PlugInHomeCinema71USB.hpp"
#include "PlugInCustom.hpp"

#include "LogFile.h"

#include "customdefines.hpp"

extern CLogFile myLog;

#define FS 48000.0

using namespace Vektorraum;

// https://www.iconfinder.com/icons/15700/information_icon

static const unsigned int kMaxPlotColors = 8;
QColor colorPlot[kMaxPlotColors] = { QColor(  81, 158, 228 ),
                        QColor( 184,  92, 213 ),
                        QColor( 135, 185, 102 ),
                        QColor( 222, 180,  96 ),
                        QColor( 207,  85,  98 ),
                        QColor(  73, 168, 181 ),
                        QColor( 198, 136,  78 ),
                        QColor(   0,  94, 240 )
                      };


static QVolumeSlider* sliderMainVolume;
static QString pathSettings;   
static MainWindow* ptrMainWindow;
static QStatusBar* ptrMainStatusBar;

//==============================================================================
/*!
 */
void setStatusBarMessage( QString str )
{
  ptrMainStatusBar->showMessage( str );
}

//==============================================================================
/*!
 */
void enableGui( bool enable )
{
  ptrMainWindow->setEnabled( enable );
}

//==============================================================================
/*!
 */
MainWindow::MainWindow( QWidget* parent ) :
  QMainWindow( parent ),
  ui( new Ui::MainWindow )
{
  ptrMainWindow = this;

  ui->setupUi(this);
  #if defined( __IOS__ ) || defined( __WIN__ ) || defined( __LINUX__ )
  ui->menuBar->hide();
  #endif
  ui->actionWrite_to_DSP->setEnabled( false );

  ptrMainStatusBar = ui->statusBar;
  
  #if defined( __MACOSX__ )
  pathSettings = QString( "./settings.json" );
  QFile fileSettings( pathSettings );
  #elif defined( __WIN__ )

  pathSettings = QStandardPaths::writableLocation( QStandardPaths::AppLocalDataLocation );
  if( !pathSettings.isEmpty() )
  {
    QDir d(pathSettings);
    d.mkpath( d.absolutePath() );
  }
  pathSettings += QString( "/settings.json" );

  QFile fileSettings( pathSettings );
  #else
  #error StandardPath not given.
  #endif

  if( fileSettings.open( QIODevice::ReadOnly ) )
  {
    QByteArray settings = fileSettings.readAll();
    QJsonDocument jsonDoc( QJsonDocument::fromJson( settings ) );
    jsonObjSettings = jsonDoc.object();
    dsp.setConnectionTypeWifi( jsonObjSettings[ "network" ].toInt() );
    dsp.setSsidWifi( jsonObjSettings[ "ssid" ].toString() );
    dsp.setIpAddressWifi( jsonObjSettings[ "ip" ].toString() );
    fileSettings.close();
  }
  

  //----------------------------------------------------------------------------
  //--- Setup the channel tabs
  //----------------------------------------------------------------------------
  //ui->tabChannels->removeTab( 0 );
  QLabel* lbl1;

  #if defined( DEMO )

  CPlugIn8Channels plugin8Channels( FS );
  CPlugInHomeCinema71 pluginHomeCinema71( FS );
  CPlugIn4FIRs plugin4FIRs( FS );

  setWindowTitle( QString("auverdionControl DEMO ").append( VERSION_STR ) );

  QStringList itemList( {"8channels", "Home Cinema 7.1", "4 FIRs"} );
  QDialogDemoSelector dialog( "Please select the plugin for demo: ", itemList );
  if( dialog.exec() == QDialog::Accepted )
  {
    if( dialog.comboBox()->currentText() == QString("8channels") )
    {
      qDebug()<<"Loading plugin 8channels";
      numChannels = plugin8Channels.getNumChannels();
      for( unsigned int n = 0; n < numChannels; n++ )
      {
        tDspChannel dspChannel = plugin8Channels.getGuiForChannel( n, FS, &dsp, this );
        listOutputGains.append( dspChannel.gain );

        ui->tabChannels->addTab( dspChannel.channel, "" );
        lbl1 = new QLabel();
        lbl1->setText( dspChannel.name );
        lbl1->setStyleSheet( QString("background-color: transparent; border: 0px solid black; border-left: 2px solid ") + colorPlot[n%kMaxPlotColors].name() + QString("; color: white; ") );
        lbl1->setFixedWidth( 100 );
        ui->tabChannels->tabBar()->setTabButton( n, QTabBar::LeftSide, lbl1 );

        dspChannel.layout->setSpacing( 0 );
        dspChannel.layout->setMargin( 0 );
        dspChannel.layout->setContentsMargins( 0, 0, 0, 0 );
        dspChannel.layout->setAlignment( Qt::AlignLeft );

        dspChannel.channel->widgetChannel->setLayout( dspChannel.layout );

        for( unsigned int chn = 0; chn < numChannels; chn++ )
        {
          QAction* action = new QAction( "Show " + plugin8Channels.getChannelName( chn ) );
          action->setCheckable( true );
          dspChannel.channel->actionsContextMenu.append( action );
          dspChannel.channel->contextMenu.addAction( action );
        }
        dspChannel.channel->actionsContextMenu.at(n)->setChecked( true );
        connect( dspChannel.channel, SIGNAL(selectionChanged()), this, SLOT(updatePlots()) );
      }
      dspPlugin = &plugin8Channels;
    }
    else if( dialog.comboBox()->currentText() == QString("Home Cinema 7.1") )
    {
      qDebug()<<"Loading plugin Home Cinema 7.1";
      numChannels = pluginHomeCinema71.getNumChannels();
      for( unsigned int n = 0; n < numChannels; n++ )
      {
        tDspChannel dspChannel = pluginHomeCinema71.getGuiForChannel( n, FS, &dsp, this );
        listOutputGains.append( dspChannel.gain );

        ui->tabChannels->addTab( dspChannel.channel, "" );
        lbl1 = new QLabel();
        lbl1->setText( dspChannel.name );
        lbl1->setStyleSheet( QString("background-color: transparent; border: 0px solid black; border-left: 2px solid ") + colorPlot[n%kMaxPlotColors].name() + QString("; color: white; ") );
        lbl1->setFixedWidth( 100 );
        ui->tabChannels->tabBar()->setTabButton( n, QTabBar::LeftSide, lbl1 );

        dspChannel.layout->setSpacing( 0 );
        dspChannel.layout->setMargin( 0 );
        dspChannel.layout->setContentsMargins( 0, 0, 0, 0 );
        dspChannel.layout->setAlignment( Qt::AlignLeft );

        dspChannel.channel->widgetChannel->setLayout( dspChannel.layout );

        for( unsigned int chn = 0; chn < numChannels; chn++ )
        {
          QAction* action = new QAction( "Show " + pluginHomeCinema71.getChannelName( chn ) );
          action->setCheckable( true );
          dspChannel.channel->actionsContextMenu.append( action );
          dspChannel.channel->contextMenu.addAction( action );
        }
        dspChannel.channel->actionsContextMenu.at(n)->setChecked( true );
        connect( dspChannel.channel, SIGNAL(selectionChanged()), this, SLOT(updatePlots()) );
      }
      dspPlugin = &pluginHomeCinema71;
    }
    else if( dialog.comboBox()->currentText() == QString("4 FIRs") )
    {
      qDebug()<<"Loading plugin 4 FIRs";
      numChannels = plugin4FIRs.getNumChannels();
      for( unsigned int n = 0; n < numChannels; n++ )
      {
        tDspChannel dspChannel = plugin4FIRs.getGuiForChannel( n, FS, &dsp, this );
        listOutputGains.append( dspChannel.gain );

        ui->tabChannels->addTab( dspChannel.channel, "" );
        lbl1 = new QLabel();
        lbl1->setText( dspChannel.name );
        lbl1->setStyleSheet( QString("background-color: transparent; border: 0px solid black; border-left: 2px solid ") + colorPlot[n%kMaxPlotColors].name() + QString("; color: white; ") );
        lbl1->setFixedWidth( 100 );
        ui->tabChannels->tabBar()->setTabButton( n, QTabBar::LeftSide, lbl1 );

        dspChannel.layout->setSpacing( 0 );
        dspChannel.layout->setMargin( 0 );
        dspChannel.layout->setContentsMargins( 0, 0, 0, 0 );
        dspChannel.layout->setAlignment( Qt::AlignLeft );

        dspChannel.channel->widgetChannel->setLayout( dspChannel.layout );

        for( unsigned int chn = 0; chn < numChannels; chn++ )
        {
          QAction* action = new QAction( "Show " + plugin4FIRs.getChannelName( chn ) );
          action->setCheckable( true );
          dspChannel.channel->actionsContextMenu.append( action );
          dspChannel.channel->contextMenu.addAction( action );
        }
        dspChannel.channel->actionsContextMenu.at(n)->setChecked( true );
        connect( dspChannel.channel, SIGNAL(selectionChanged()), this, SLOT(updatePlots()) );
      }
      dspPlugin = &plugin4FIRs;
    }
    
  }

  #else
  setWindowTitle( QString("auverdionControl ").append( VERSION_STR ) );
 
  qDebug()<<"Loading plugin 8channels";

  ui->tabPresets->removeTab( 0 );
  ui->tabPresets->blockSignals( true );

  for( int ii = 0; ii < NUMPRESETS; ii++ )
  {
    presets[ii] = new QPreset;
    if( ii == 0 )
      ui->tabPresets->addTab( presets[ii], "Preset A" );
    else if( ii == 1 )
      ui->tabPresets->addTab( presets[ii], "Preset B" );  
    else if( ii == 2 )
      ui->tabPresets->addTab( presets[ii], "Preset C" ); 
    else if( ii == 3 )
      ui->tabPresets->addTab( presets[ii], "Preset D" ); 

    presets[ii]->tabChannels->removeTab( 0 );
    
    dspPlugin[ii] = new CPlugIn8Channels( FS );
    numChannels = dspPlugin[ii]->getNumChannels();
    for( unsigned int n = 0; n < numChannels; n++ )
    {
      tDspChannel dspChannel = dspPlugin[ii]->getGuiForChannel( n, FS, &dsp, this );

      //listOutputGains.append( dspChannel.gain );

      presets[ii]->tabChannels->addTab( dspChannel.channel, "" );
      lbl1 = new QLabel( presets[ii]->tabChannels );
      lbl1->setText( dspChannel.name );
      lbl1->setStyleSheet( QString("background-color: transparent; border: 0px solid black; border-left: 2px solid ") + colorPlot[n%kMaxPlotColors].name() + QString("; color: white; ") );
      lbl1->setFixedWidth( 100 );
      presets[ii]->tabChannels->tabBar()->setTabButton( static_cast<int>(n), QTabBar::LeftSide, lbl1 );

      dspChannel.layout->setSpacing( 0 );
      dspChannel.layout->setMargin( 0 );
      dspChannel.layout->setContentsMargins( 0, 0, 0, 0 );
      dspChannel.layout->setAlignment( Qt::AlignLeft );

      dspChannel.channel->widgetChannel->setLayout( dspChannel.layout );

      for( unsigned int chn = 0; chn < numChannels; chn++ )
      {
        QAction* action = new QAction( "    Show " + dspPlugin[ii]->getChannelName( chn ) );
        action->setCheckable( true );
        dspChannel.channel->actionsContextMenu.append( action );
        dspChannel.channel->contextMenu.addAction( action );
      }
      dspChannel.channel->actionsContextMenu.at(static_cast<int>(n))->setChecked( true );
      connect( dspChannel.channel, SIGNAL(selectionChanged()), this, SLOT(updatePlots()) );
    }
  }
  ui->tabPresets->blockSignals( false );

  for( uint32_t p = 0; p < NUMPRESETS; p++ )
  {
    QByteArray usrparams;
    for( unsigned int ii = 0; ii < dspPlugin[p]->getNumChannels(); ii++ )
    {
      QChannel* channel = dspPlugin[p]->getChannel( ii );
      for( unsigned int n = 0; n < channel->getNumDspBlocks(); n++ )
      {
        QDspBlock* dspBlock = channel->getDspBlock(n);
        QByteArray params = dspBlock->getUserParams();
        if( params.size() )
          usrparams.append( params );
      }
    }
    usrparams.append( ui->volumeSliderMain->getUserParams() );
    presetUserParams[p] = usrparams;
  }

  #endif

  freq = dspPlugin[0]->getFrequencyVector();

  //tvector<tcomplex> H;

  updatePlots();

  sliderMainVolume = ui->volumeSliderMain;

  QLabel* logo = new QLabel( this );
  logo->setPixmap( QPixmap::fromImage( QImage(":/freeDSP_LOGO_white.png") ) );
  logo->move( 6, 6 );
  logo->show();

  labelPlugIn = new QLabel( "Unknown PlugIn" );
  labelConnected = new QLabel( "Not connected" );
  QHBoxLayout* layout = new QHBoxLayout;
  layout->addWidget( labelPlugIn );
  layout->addWidget( labelConnected );
  QWidget* widget = new QWidget( ui->statusBar );
  widget->setLayout( layout );
  ui->statusBar->addPermanentWidget( widget );

}

//==============================================================================
/*!
 */
MainWindow::~MainWindow()
{
  dsp.disconnectWifi();
  
  //dsp.tcpSocket->disconnectFromHost();

  delete ui;
}

//==============================================================================
/*!
 */
void MainWindow::showLicense( void )
{
  DialogLicense dlg;
  dlg.exec();
}

//==============================================================================
/*!
 */
void MainWindow::updatePlots( void )
{
  for( int chn = 0; chn < presets[currentPreset]->tabChannels->count(); chn++ )
  {
    QChannel* channel = static_cast<QChannel*>(presets[currentPreset]->tabChannels->widget(chn));
    if( channel != nullptr )
      channel->update( freq );
  }

  for( int chn = 0; chn < presets[currentPreset]->tabChannels->count(); chn++ )
  {
    tvector<tcomplex> H;
    QChannel* currentChannel = static_cast<QChannel*>(presets[currentPreset]->tabChannels->widget(chn));
    if( currentChannel != nullptr )
    {
      currentChannel->figVoltageMagnitude->clear();
      currentChannel->figVoltageMagnitude->holdon();

      for( unsigned int ii = 0; ii < numChannels; ii++ )
      {
        if( currentChannel->actionsContextMenu.at(static_cast<int>(ii))->isChecked() )
        {
          QChannel* channel = static_cast<QChannel*>(presets[currentPreset]->tabChannels->widget(static_cast<int>(ii)));
          if( length(H) > 0 )
            H = H + channel->getTransferFunction();
          else
            H = channel->getTransferFunction();

          currentChannel->figVoltageMagnitude->semilogx( freq, 20.0 * log10( abs( channel->getTransferFunction() ) ), colorPlot[ii%8], 2 );
        }
      }

      if( dspPlugin[currentPreset]->doSummation() )
      {
        if( length(H) > 0 )
          currentChannel->figVoltageMagnitude->semilogx( freq, 20.0 * log10( abs( H ) ), Qt::white, 2 );
      }
      currentChannel->figVoltageMagnitude->holdoff();
    }
  }
}

//==============================================================================
/*!
 */
void MainWindow::on_actionRead_from_DSP_triggered()
{
  setEnabled( false );
  dsp.setIsConnected( false );

  if( dsp.getConnectionTypeWifi() != CFreeDspAurora::OFFLINE )
  {
    QTimer timerWait;
    connect( &timerWait, SIGNAL(timeout()), this, SLOT(updateWaitingForConnect()) );
    timerWait.start( 100 );
    currentWaitRotation = 0;

    msgBox = new QMessageBox( QMessageBox::Information, tr("Waiting"), tr("Connecting to DSP..."), QMessageBox::Cancel, this );
    QImage srcImg = QImage(":/reload_128x128.png").scaled(64,64);
    srcImg = srcImg.copy( 0, 0, 70, 70 );
    msgBox->setIconPixmap( QPixmap::fromImage( srcImg ) );
    msgBox->setStandardButtons( nullptr );
    msgBox->open();

    //----------------------------------------------------------------------------
    //--- Request the firmware version
    //----------------------------------------------------------------------------
    ui->statusBar->showMessage("Reading firmware version.......");
    if( dsp.requestFirmwareVersionWifi( false ) )
    {

      if( dsp.getFwVersion() != VERSION_HEX )
      {
        QMessageBox::critical( this, tr("Error: Version mismatch"), tr("I am really sorry. The firmware version is not compatible with your version of auverdionControl. Please install firmware ") + VERSION_STR + tr(" on your Aurora first."), QMessageBox::Ok ); 
        msgBox->accept();
        ui->statusBar->showMessage("Ready");
        setEnabled( true );
        return;
      }

      //--------------------------------------------------------------------------
      //--- Request the AddOn-Id
      //--------------------------------------------------------------------------
      ui->statusBar->showMessage("Reading AddOn-Id.......");
      dsp.requestAddOnIdWifi();

      //--------------------------------------------------------------------------
      //--- Request the DSP-plugin id
      //--------------------------------------------------------------------------
      ui->statusBar->showMessage("Reading PID.......");
      uint32_t pid = dsp.requestPidWifi();
      if( pid == 0 )
      {
        msgBox->accept();
        return;
      }

      //--------------------------------------------------------------------------
      //--- Request the DSP-plugin version
      //--------------------------------------------------------------------------
      ui->statusBar->showMessage("Requesting plugin version.......");
      dsp.requestPluginVersionWifi();
      QString pversion = dsp.getPluginVersion();
      if( pversion != VERSION_STR )
      {
        QMessageBox::critical( this, tr("Error: Plugin version mismatch"), tr("I am really sorry. The plugin version is not compatible with your version of auverdionControl. Please (re)install the plugin on your Aurora first."), QMessageBox::Ok ); 
        msgBox->accept();
        ui->statusBar->showMessage("Ready");
        setEnabled( true );
        return;
      }

      //--------------------------------------------------------------------------
      //--- Request current preset selection
      //--------------------------------------------------------------------------
      ui->statusBar->showMessage("Requesting current preset selection.......");
      int preset = dsp.requestCurrentPresetWifi();
      if( preset > -1 )
      {
        currentPreset = preset;
        ui->tabPresets->blockSignals( true );
        ui->tabPresets->setCurrentIndex( preset );
        ui->tabPresets->blockSignals( false );
      }

      //--------------------------------------------------------------------------
      //--- Delete old preset GUI
      //--------------------------------------------------------------------------
      for( int ii = 0; ii < NUMPRESETS; ii++ )
      {
        while( presets[ii]->tabChannels->count() )
          delete presets[ii]->tabChannels->widget( presets[ii]->tabChannels->currentIndex() );
      }

      ui->tabPresets->blockSignals( true );
      while( ui->tabPresets->count() )
        delete ui->tabPresets->widget( ui->tabPresets->currentIndex() );
      ui->tabPresets->blockSignals( false );

      // \TODO Fix the crash when calling delete.
      //delete dspPlugin;

      switchPluginGui( pid );
    
      //--------------------------------------------------------------------------
      //--- Request user parameters
      //-------------------------------------------------------------------------- 
      dsp.muteDAC();
      QThread::msleep( 200 );
    
      for( int p = 0; p < NUMPRESETS; p++ )
      {
        ui->statusBar->showMessage( "Selecting preset......." );
        dsp.selectPresetWifi( p, 100000 );

        ui->statusBar->showMessage( "Reading user parameter......." );
        QByteArray userparams;
        if( dsp.requestUserParameterWifi( userparams, 60000 ) )
        {
          updatePresetGui( p, userparams );
          currentPreset = p;
          updatePlots();
          presetUserParams[p] = userparams;
        }
        dspPlugin[p]->setMasterVolume( ui->volumeSliderMain->value(), false );
      }

      currentPreset = preset;

      dsp.selectPresetWifi( preset, 100000 );
      dsp.setMasterVolume( static_cast<float>(dspPlugin[currentPreset]->getMasterVolume()) );

      ui->tabPresets->blockSignals( true );
      ui->tabPresets->setCurrentIndex( currentPreset );
      ui->tabPresets->blockSignals( false );  

      updatePlots();

      QThread::msleep( 3000 );

      dsp.unmuteDAC();

      setEnabled( true );
      disconnect( &timerWait, SIGNAL(timeout()), this, SLOT(updateWaitingForConnect()) );
      currentWaitRotation = 0;
      //rotateIconConnect( currentWaitRotation );
      msgBox->accept();
      ui->statusBar->showMessage("Ready");
      ui->actionWrite_to_DSP->setEnabled( true );

      myLog()<<"Fw Version: "<<dsp.getFwVersion();
      if( dsp.getFwVersion() < 0x010200 )
      {
        if( !jsonObjSettings["msg0004"].toBool() )
        {
          DialogReleaseNotes dlg( this );
          dlg.setWindowTitle( "Release Note" );
          dlg.setReleaseNote( QString( "There is a new firmware available for your Aurora DSP!\n" )
                            + QString( "This firmware update adds FIR filters to your Aurora DSP.\n" ) );
          int result = dlg.exec();
          if( result == QDialog::Accepted )
          {
            if( dlg.getDontShowAgain() )
            {
              jsonObjSettings["msg0004"] = true;
              writeSettings();
            }
          }
        }
      }
      else if( dsp.getFwVersion() < 0x010101 )
      {
        if( !jsonObjSettings["msg0003"].toBool() )
        {
          DialogReleaseNotes dlg( this );
          dlg.setWindowTitle( "Release Note" );
          dlg.setReleaseNote( QString( "There is a new firmware available for your Aurora DSP!\n" )
                            + QString( "This fixes an issue with corrupted files on your board after a firmware update.\n" ) );
          int result = dlg.exec();
          if( result == QDialog::Accepted )
          {
            if( dlg.getDontShowAgain() )
            {
              jsonObjSettings["msg0003"] = true;
              writeSettings();
            }
          }
        }
      }
      else if( dsp.getFwVersion() < 0x010100 )
      {
        if( !jsonObjSettings["msg0002"].toBool() )
        {
          DialogReleaseNotes dlg( this );
          dlg.setWindowTitle( "Release Note" );
          dlg.setReleaseNote( QString( "There is a new firmware available for your Aurora DSP!\n" )
                            + QString( "New features and changes are:\n" )
                            + QString( "- Full support of AddOnB (S/P-DIF multiplexer)\n" )
                            + QString( "- DAC mute function\n" )
                            + QString( "- New webOTA interface for future firmware updates\n" )
                            + QString( "Please download the latest firmware and install it.\nIn the user manual (UserManual.pdf) you will find instructions how to update the firmware." ) );
          int result = dlg.exec();
          if( result == QDialog::Accepted )
          {
            if( dlg.getDontShowAgain() )
            {
              jsonObjSettings["msg0002"] = true;
              writeSettings();
            }
          }
        }
      }
      else if( !jsonObjSettings["msg0001"].toBool() )
      {
        if( dsp.getFirmwareVersion() == "1.0.0" )
        {
          DialogReleaseNotes dlg( this );
          dlg.setWindowTitle( "Hotfix available" );
          dlg.setReleaseNote( "There is a new hotfix available for your aurora!\nPlease download the latest firmware and install it.\nIn the user manual (UserManual.pdf) you will find instructions how to update the firmware." );
          int result = dlg.exec();
          if( result == QDialog::Accepted )
          {
            if( dlg.getDontShowAgain() )
            {
              jsonObjSettings["msg0001"] = true;
              writeSettings();
            }
          }
        }
      }
      switch( pid )
      {
      case CFreeDspAurora::PLUGIN_8CHANNELS:
        labelPlugIn->setText( "8channels" );
        labelConnected->setText( "Connected" );
        ui->tabPresets->blockSignals( true );
        ui->tabPresets->setTabEnabled( 0, true );
        ui->tabPresets->setTabEnabled( 1, true );
        ui->tabPresets->setTabEnabled( 2, true );
        ui->tabPresets->setTabEnabled( 3, true );
        ui->tabPresets->blockSignals( false );
        break;
      case CFreeDspAurora::PLUGIN_HOMECINEMA71:
        labelPlugIn->setText( "HomeCinema71" );
        labelConnected->setText( "Connected" );
        ui->tabPresets->blockSignals( true );
        ui->tabPresets->setTabEnabled( 0, true );
        ui->tabPresets->setTabEnabled( 1, true );
        ui->tabPresets->setTabEnabled( 2, true );
        ui->tabPresets->setTabEnabled( 3, true );
        ui->tabPresets->blockSignals( false );
        break;
      case CFreeDspAurora::PLUGIN_4FIRS:
        labelPlugIn->setText( "4FIRs" );
        labelConnected->setText( "Connected" );
        ui->tabPresets->blockSignals( true );
        ui->tabPresets->setTabEnabled( 0, true );
        ui->tabPresets->setTabEnabled( 1, true );
        ui->tabPresets->setTabEnabled( 2, true );
        ui->tabPresets->setTabEnabled( 3, true );
        ui->tabPresets->blockSignals( false );
        break;
      case CFreeDspAurora::PLUGIN_8CHANNELS_USB:
        labelPlugIn->setText( "8channels USB" );
        labelConnected->setText( "Connected" );
        ui->tabPresets->blockSignals( true );
        ui->tabPresets->setTabEnabled( 0, true );
        ui->tabPresets->setTabEnabled( 1, true );
        ui->tabPresets->setTabEnabled( 2, true );
        ui->tabPresets->setTabEnabled( 3, true );
        ui->tabPresets->blockSignals( false );
        break;
      case CFreeDspAurora::PLUGIN_HOMECINEMA71_USB:
        labelPlugIn->setText( "HomeCinema71 USB" );
        labelConnected->setText( "Connected" );
        ui->tabPresets->blockSignals( true );
        ui->tabPresets->setTabEnabled( 0, true );
        ui->tabPresets->setTabEnabled( 1, true );
        ui->tabPresets->setTabEnabled( 2, true );
        ui->tabPresets->setTabEnabled( 3, true );
        ui->tabPresets->blockSignals( false );
        break;
      case CFreeDspAurora::PLUGIN_CUSTOM:
        labelPlugIn->setText( "Custom" );
        labelConnected->setText( "Connected" );
        ui->tabPresets->blockSignals( true );
        ui->tabPresets->setTabEnabled( 0, false );
        ui->tabPresets->setTabEnabled( 1, false );
        ui->tabPresets->setTabEnabled( 2, false );
        ui->tabPresets->setTabEnabled( 3, false );
        ui->tabPresets->blockSignals( false );
        break;
      default:
        labelPlugIn->setText( "Unknown Plugin" );
        labelConnected->setText( "Connected" );
      }
      
    }
    else
    {
      msgBox->accept();
      QMessageBox msgQuestion;
      msgQuestion.setText( tr("There is no DSP responding. Do you want to run auverdionControl in offline mode?") );
      //msgQuestion.setInformativeText("Do you want to save your changes?");
      msgQuestion.setStandardButtons( QMessageBox::Yes | QMessageBox::No );
      msgQuestion.setDefaultButton( QMessageBox::Yes );
      int ret = msgQuestion.exec();

      QStringList itemList( {"8channels", "Home Cinema 7.1", "4FIRs"} );
      QDialogDemoSelector dialog( "Please select the plugin for offline mode: ", itemList );
      switch (ret)
      {
      case QMessageBox::Yes:
        myLog()<<"Offline mode selected";
        if( dialog.exec() == QDialog::Accepted )
        {
          for( int ii = 0; ii < NUMPRESETS; ii++ )
          {
            while( presets[ii]->tabChannels->count() )
              delete presets[ii]->tabChannels->widget( presets[ii]->tabChannels->currentIndex() );
          }

          ui->tabPresets->blockSignals( true );
          while( ui->tabPresets->count() )
            delete ui->tabPresets->widget( ui->tabPresets->currentIndex() );
          ui->tabPresets->blockSignals( false );

          if( dialog.comboBox()->currentText() == QString("8channels") )
          {
            switchPluginGui( CFreeDspAurora::PLUGIN_8CHANNELS );
            labelPlugIn->setText( "8channels" );
            ui->tabPresets->blockSignals( true );
            ui->tabPresets->setTabEnabled( 0, true );
            ui->tabPresets->setTabEnabled( 1, true );
            ui->tabPresets->setTabEnabled( 2, true );
            ui->tabPresets->setTabEnabled( 3, true );
            ui->tabPresets->blockSignals( false );
          }
          else if( dialog.comboBox()->currentText() == QString("Home Cinema 7.1") )
          {
            switchPluginGui( CFreeDspAurora::PLUGIN_HOMECINEMA71 );
            labelPlugIn->setText( "HomeCinema71" );
            ui->tabPresets->blockSignals( true );
            ui->tabPresets->setTabEnabled( 0, true );
            ui->tabPresets->setTabEnabled( 1, true );
            ui->tabPresets->setTabEnabled( 2, true );
            ui->tabPresets->setTabEnabled( 3, true );
            ui->tabPresets->blockSignals( false );
          }
          else if( dialog.comboBox()->currentText() == QString("4FIRs") )
          {
            switchPluginGui( CFreeDspAurora::PLUGIN_4FIRS );
            labelPlugIn->setText( "4FIRs" );
            ui->tabPresets->blockSignals( true );
            ui->tabPresets->setTabEnabled( 0, true );
            ui->tabPresets->setTabEnabled( 1, true );
            ui->tabPresets->setTabEnabled( 2, true );
            ui->tabPresets->setTabEnabled( 3, true );
            ui->tabPresets->blockSignals( false );
          }

          for( int p = 0; p < NUMPRESETS; p++ )
          {
            dsp.selectPresetWifi( p );
            QByteArray userparams;
            if( dsp.requestUserParameterWifi( userparams ) )
            {
              updatePresetGui( p, userparams );
              presetUserParams[p] = userparams;
            }
            dspPlugin[p]->setMasterVolume( ui->volumeSliderMain->value(), false );
            qDebug()<<"Preset Master Volume:"<<dspPlugin[p]->getMasterVolume();
          }

          updatePlots();
        }
        ui->statusBar->showMessage("Ready");
        ui->actionWrite_to_DSP->setEnabled( false );
        break;
      case QMessageBox::No:
        myLog()<<"Abort";
        ui->statusBar->showMessage("Ready");
        break;
      default:
        break;
      }
    }
    disconnect( &timerWait, SIGNAL(timeout()), this, SLOT(updateWaitingForConnect()) );

  }
  else
  {
    QStringList itemList( {"8channels", "Home Cinema 7.1", "4FIRs"} );
    QDialogDemoSelector dialog( "Please select the plugin for offline mode: ", itemList );
    if( dialog.exec() == QDialog::Accepted )
    {
      for( int ii = 0; ii < NUMPRESETS; ii++ )
      {
        while( presets[ii]->tabChannels->count() )
          delete presets[ii]->tabChannels->widget( presets[ii]->tabChannels->currentIndex() );
      }

      ui->tabPresets->blockSignals( true );
      while( ui->tabPresets->count() )
        delete ui->tabPresets->widget( ui->tabPresets->currentIndex() );
      ui->tabPresets->blockSignals( false );

      if( dialog.comboBox()->currentText() == QString("8channels") )
      {
        switchPluginGui( CFreeDspAurora::PLUGIN_8CHANNELS );
        labelPlugIn->setText( "8channels" );
        ui->tabPresets->blockSignals( true );
        ui->tabPresets->setTabEnabled( 0, true );
        ui->tabPresets->setTabEnabled( 1, true );
        ui->tabPresets->setTabEnabled( 2, true );
        ui->tabPresets->setTabEnabled( 3, true );
        ui->tabPresets->blockSignals( false );
      }
      else if( dialog.comboBox()->currentText() == QString("Home Cinema 7.1") )
      {
        switchPluginGui( CFreeDspAurora::PLUGIN_HOMECINEMA71 );
        labelPlugIn->setText( "HomeCinema71" );
        ui->tabPresets->blockSignals( true );
        ui->tabPresets->setTabEnabled( 0, true );
        ui->tabPresets->setTabEnabled( 1, true );
        ui->tabPresets->setTabEnabled( 2, true );
        ui->tabPresets->setTabEnabled( 3, true );
        ui->tabPresets->blockSignals( false );
      }
      else if( dialog.comboBox()->currentText() == QString("4FIRs") )
      {
        switchPluginGui( CFreeDspAurora::PLUGIN_4FIRS );
        labelPlugIn->setText( "4FIRs" );
        ui->tabPresets->blockSignals( true );
        ui->tabPresets->setTabEnabled( 0, true );
        ui->tabPresets->setTabEnabled( 1, true );
        ui->tabPresets->setTabEnabled( 2, true );
        ui->tabPresets->setTabEnabled( 3, true );
        ui->tabPresets->blockSignals( false );
      }
      else if( dialog.comboBox()->currentText() == QString("Custom") )
      {
        switchPluginGui( CFreeDspAurora::PLUGIN_CUSTOM );
        labelPlugIn->setText( "Custom" );
        ui->tabPresets->blockSignals( true );
        ui->tabPresets->setTabEnabled( 0, false );
        ui->tabPresets->setTabEnabled( 1, false );
        ui->tabPresets->setTabEnabled( 2, false );
        ui->tabPresets->setTabEnabled( 3, false );
        ui->tabPresets->blockSignals( false );
      }

      for( int p = 0; p < NUMPRESETS; p++ )
      {
        dsp.selectPresetWifi( p );
        QByteArray userparams;
        if( dsp.requestUserParameterWifi( userparams ) )
        {
          updatePresetGui( p, userparams );
          presetUserParams[p] = userparams;
        }
        dspPlugin[p]->setMasterVolume( ui->volumeSliderMain->value(), false );
        qDebug()<<"Preset Master Volume:"<<dspPlugin[p]->getMasterVolume();
      }

      updatePlots();
    }
    ui->statusBar->showMessage("Ready");
    ui->actionWrite_to_DSP->setEnabled( false );

  }
  setEnabled( true );
}

//==============================================================================
/*!
 */
void MainWindow::updatePresetGui( int p, QByteArray& userparams )
{
  int idx = 0;
  for( unsigned int ii = 0; ii < dspPlugin[p]->getNumChannels(); ii++ )
  {
    QChannel* channel = dspPlugin[p]->getChannel( ii );
    for( unsigned int n = 0; n < channel->getNumDspBlocks(); n++ )
    {
      QDspBlock* dspBlock = channel->getDspBlock(n);
      dspBlock->setUserParams( userparams, idx );
    }
  }

  if( userparams.size() >= idx + 4 )
  {
    QByteArray param;
    param.append( userparams.at(idx) );
    idx++;
    param.append( userparams.at(idx) );
    idx++;
    param.append( userparams.at(idx) );
    idx++;
    param.append( userparams.at(idx) );
    idx++;

    float gain = *reinterpret_cast<const float*>(param.data());

    ui->volumeSliderMain->blockSignals( true );
    ui->volumeSliderMain->setValue( static_cast<double>(gain) );
    ui->volumeSliderMain->blockSignals( false );
  }
  else
    myLog()<<"Set volume slider: Not enough data";

  if( userparams.size() >= idx + 1 )
  {
    QByteArray param;
    param.append( userparams.at(idx) );
    idx++;

    bool enableVolPoti = *reinterpret_cast<const bool*>(param.data());

    dspPlugin[p]->setEnableVolumePoti( enableVolPoti, false );
  }
  else
    myLog()<<"Set enable volume potie: Not enough data";

}

//==============================================================================
/*!
 */
void MainWindow::on_actionWrite_to_DSP_triggered()
{
  //----------------------------------------------------------------------------
  //--- Build dspparam.hex files
  //----------------------------------------------------------------------------
  myLog()<<"Build dspparam files";
  QByteArray dspparams[NUMPRESETS];

  for( uint32_t p = 0; p < NUMPRESETS; p++ )
  {
    for( unsigned int ii = 0; ii < dspPlugin[p]->getNumChannels(); ii++ )
    {
      QChannel* channel = dspPlugin[p]->getChannel( ii );
      for( unsigned int n = 0; n < channel->getNumDspBlocks(); n++ )
      {
        QDspBlock* dspBlock = channel->getDspBlock(n);
        QByteArray params = dspBlock->getDspParams();
        if( params.size() > 0 )
          dspparams[p].append( params );
      }
    }
    dspparams[p].append( dsp.makeParameterForWifi( dspPlugin[p]->getAddressMasterVolume(), static_cast<float>(pow( 10.0, ui->volumeSliderMain->value()/20.0 ) ) ) );
    dspparams[p].append( dspPlugin[p]->getDspParams() );
  }

  //----------------------------------------------------------------------------
  //--- Build usrparam.hex file
  //----------------------------------------------------------------------------
  myLog()<<"Build usrparam files";
  QByteArray usrparams[NUMPRESETS];

  for( uint32_t p = 0; p < NUMPRESETS; p++ )
  {
    for( unsigned int ii = 0; ii < dspPlugin[p]->getNumChannels(); ii++ )
    {
      QChannel* channel = dspPlugin[p]->getChannel( ii );
      for( unsigned int n = 0; n < channel->getNumDspBlocks(); n++ )
      {
        QDspBlock* dspBlock = channel->getDspBlock(n);
        QByteArray params = dspBlock->getUserParams();
        if( params.size() > 0 )
          usrparams[p].append( params );
      }
    }
    usrparams[p].append( ui->volumeSliderMain->getUserParams() );
    usrparams[p].append( dspPlugin[p]->getUserParams() );
    presetUserParams[p] = usrparams[p];
  }
  
  QProgressDialog progress( tr("Storing your DSP settings..."), tr("Abort"), 0, (dspparams[0].size() + usrparams[0].size()) * NUMPRESETS + 1, this );
  progress.setWindowModality(Qt::WindowModal);
  int progressValue = 0;

  dsp.muteDAC();
  QThread::msleep( 400 );

  for( int p = 0; p < NUMPRESETS; p++ )
  {
    /*dsp.mute();
  
    QEventLoop loopWaitForReply;
    QTimer timerWaitMute;
    timerWaitMute.setSingleShot( true );
    connect( &timerWaitMute, SIGNAL(timeout()), &loopWaitForReply, SLOT(quit()) );
    timerWaitMute.start( 500 );
    loopWaitForReply.exec();*/

    dsp.selectPresetWifi( p, 60000 );

    //----------------------------------------------------------------------------
    //--- Send dspparam file
    //----------------------------------------------------------------------------
    myLog()<<"Send dspparam file for preset"<<p;
    int offset = 0;
    uint32_t totalTransmittedBytes = 0;
    while( offset < dspparams[p].size() )
    {
      QByteArray packet;
      for( int ii = 0; ii < 64; ii++ )
      {
        if( offset < dspparams[p].size() )
          packet.append( dspparams[p].at(offset) );
        offset++;
      }
      dsp.sendDspParameterWifi( packet );
      totalTransmittedBytes += static_cast<uint32_t>(packet.size());

      progressValue += packet.size();
      progress.setValue( progressValue );

      if( progress.wasCanceled() )
        /* \TODO Handle cancel */
        return;
    }

    if( !dsp.finishDspParameterWifi( totalTransmittedBytes*2 ) )
    {
      QMessageBox::critical( this, tr("Error"), tr("Uups, something went wrong with storing the DSP parameters. Please double check everything and try again."), QMessageBox::Ok );  
      return;
    }

    //--------------------------------------------------------------------------
    //--- Send userparam file
    //--------------------------------------------------------------------------
    myLog()<<"Send userparam file for preset"<<p;
    offset = 0;
    totalTransmittedBytes = 0;
    while( offset < usrparams[p].size() )
    {
      QByteArray packet;
      for( int ii = 0; ii < 64; ii++ )
      {
        if( offset < usrparams[p].size() )
          packet.append( usrparams[p].at(offset) );
        offset++;
      }
      dsp.sendUserParameterWifi( packet );
      totalTransmittedBytes += static_cast<uint32_t>(packet.size());

      progressValue += packet.size();
      progress.setValue( progressValue );

      if( progress.wasCanceled() )
        /* \TODO Handle cancel */
        return;
    }

    if( !dsp.finishUserParameterWifi( totalTransmittedBytes*2 ) )
    {
      QMessageBox::critical( this, tr("Error"), tr("Uups, something went wrong with storing the user settings. Please double check everything and try again."), QMessageBox::Ok );  
      return;
    }
  }

  dsp.selectPresetWifi( ui->tabPresets->currentIndex() );
  dsp.storePresetSelection();

  progress.setValue( dspparams[0].size() * NUMPRESETS + usrparams[0].size() * NUMPRESETS + 1 );

  myLog()<<"Success";
  //qDebug()<<"File size dspparam.hex:"<<dspparams[0].size() / 1024<<"KiB";
  //qDebug()<<"File size usrparam.hex:"<<usrparams[0].size() / 1024<<"KiB";

  QMessageBox::information( this, tr("Success"), tr("You have successfully stored your settings!"), QMessageBox::Ok );

  dsp.unmuteDAC();

}

//==============================================================================
/*!
 */
void MainWindow::on_actionAbout_triggered()
{
  QPointer<QLabel> label = new QLabel;
  label->setObjectName( "labelAboutText" );
  label->setWordWrap( true );

  label->setText(QString("<p> auverdionControl") +
                 QString("<p> <b>Version</b> %1 </p>").arg( VERSION_STR ) +
                 QString("<p> <b>Built on</b> %1 @ %2 </p>").arg(__DATE__).arg(__TIME__) +
                 QString("<p> <b>Runs with</b> Qt %1 (LGPLv21) </p>").arg(QT_VERSION_STR) +
                 QString("<p> <a href style=\"color: #CC0000\">licenses</a></p>") +
                 QString("<p> <b>By</b> Raphael Knoop </p>"));

  connect( label, SIGNAL(linkActivated(QString)), this, SLOT(showLicense()) );

  label->setAlignment( Qt::AlignCenter );

  QPointer<QPushButton> pushButtonQuit = new QPushButton( "OK" );
  //pushButtonQuit->setIcon( QIcon(":/icons/ok.png") );

  QPointer<QHBoxLayout> layoutTop = new QHBoxLayout;
  layoutTop->setMargin( 10 );
  layoutTop->setSpacing( 10 );
  layoutTop->addWidget( label );

  QPointer<QHBoxLayout> layoutBottom = new QHBoxLayout;
  layoutBottom->addStretch();
  layoutBottom->addWidget( pushButtonQuit );
  layoutBottom->addStretch();

  QPointer<QLabel> labelLogo = new QLabel( "ICON" );
  labelLogo->setPixmap( QPixmap(":/appicon_256x256@2x.png") );

  QPointer<QVBoxLayout> layoutMain = new QVBoxLayout;
  layoutMain->addWidget( labelLogo );
  layoutMain->addSpacerItem( new QSpacerItem(0, 10, QSizePolicy::Minimum, QSizePolicy::Expanding ) );
  layoutMain->setAlignment( labelLogo, Qt::AlignCenter );
  layoutMain->addLayout( layoutTop );
  layoutMain->addSpacerItem( new QSpacerItem( 0, 10, QSizePolicy::Minimum, QSizePolicy::Expanding ) );
  layoutMain->addLayout( layoutBottom );

  QDialog dialogAbout(this);
  dialogAbout.setObjectName( "DialogAbout" );
  dialogAbout.setModal(true);
  dialogAbout.setWindowTitle( tr("About") );
  dialogAbout.setLayout( layoutMain );

  connect( pushButtonQuit, SIGNAL(clicked()), &dialogAbout, SLOT(close()) );

  dialogAbout.setMinimumSize( 400, 280 );
  dialogAbout.exec();
}

//==============================================================================
/*!
 */
void MainWindow::on_actionSettings_triggered()
{
  DialogSettings dialog( &dsp, dspPlugin[0]->getEnableVolumePoti(), this );
  int result = dialog.exec();
  if( result == QDialog::Accepted )
  { 
    enableGui( false );

    dsp.setConnectionTypeWifi( static_cast<int>(dialog.getConnection()) );

    jsonObjSettings[ "network" ] = dsp.getConnectionTypeWifi();
    jsonObjSettings[ "ssid" ] = dsp.getSsidWifi();
    jsonObjSettings[ "ip" ] = dsp.getIpAddressLocalWifi();
    writeSettings();

    if( dsp.getAddOnId() == CFreeDspAurora::ADDONB )
    {
      if( dialog.getSpdifInput() == 0x00 )
        dsp.sendAddOnConfig( "820104" );
      else if( dialog.getSpdifInput() == 0x01 )
        dsp.sendAddOnConfig( "820105" );
      else if( dialog.getSpdifInput() == 0x02 )
        dsp.sendAddOnConfig( "820106" );
      else if( dialog.getSpdifInput() == 0x03 )
        dsp.sendAddOnConfig( "820107" );
      else if( dialog.getSpdifInput() == 0x04 )
        dsp.sendAddOnConfig( "820100" );
      else if( dialog.getSpdifInput() == 0x05 )
        dsp.sendAddOnConfig( "820101" );
      else if( dialog.getSpdifInput() == 0x06 )
        dsp.sendAddOnConfig( "820102" );
      else if( dialog.getSpdifInput() == 0x07 )
        dsp.sendAddOnConfig( "820103" );
    }

    if( dsp.getConnectionTypeWifi() == CFreeDspAurora::OFFLINE )
      labelConnected->setText( "Not connected" );

    for( uint32_t p = 0; p < NUMPRESETS; p++ )
      dspPlugin[p]->setEnableVolumePoti( dialog.getEnableVolumePoti(), false );
    dspPlugin[0]->setEnableVolumePoti( dialog.getEnableVolumePoti(), true );

    enableGui( true );
  }
}

//==============================================================================
/*!
 */
void MainWindow::on_volumeSliderMain_valueChanged( double val )
{
  for( int p = 0; p < NUMPRESETS; p++ )
  {
    if( p == currentPreset )
      dspPlugin[p]->setMasterVolume( val, true );
    else
      dspPlugin[p]->setMasterVolume( val, false );
  }
}

//==============================================================================
/*!
 */
void MainWindow::importRewPeqs( QWidget* sender )
{
  qDebug()<<"MainWindow::Importing REW PEQs";
  QPeq* peq = static_cast<QPeq*>(sender);
  QChannel* chn = peq->getChannel();
  qDebug()<<"Channel Name"<<chn->getName();

  WizardImportRewPeq wizardImport;
  int result = wizardImport.exec();
  if( result != QDialog::Accepted )
    return;

  QString fileName = wizardImport.field( "file" ).toString();

  //QString fileName = QFileDialog::getOpenFileName( this, tr("Open REW export file"), 
  //                                                   QStandardPaths::locate(QStandardPaths::DocumentsLocation, QString(), QStandardPaths::LocateDirectory),
  //                                                   tr("REW Files (*.txt)") );
  
  QFile rewFile( fileName );
  if( rewFile.open(QIODevice::ReadOnly) )
  {
    QVector<QPeq*> peqs = chn->getPeqs();
    for( int ii = 0; ii < peqs.size(); ii++ )
      peqs.at(ii)->setParameters( 1000.0, 0.0, 1.0 );

    QTextStream in( &rewFile );
    QString line = in.readLine();
    int idx = 0;
    while (!in.atEnd())
    {
      QString line = in.readLine();
      line = line.simplified();
      QStringList values = line.split( ' ' );
      if( values.value(0) == QString( "Filter") )
      {
        if( (values.value(2) == QString( "ON")) && (values.value(3) == QString( "PK")) )
        {
          qDebug()<<values.value(0)<<values.value(1)<<values.value(2)<<values.value(3);
          QString str = values.value(5);
          //str.replace( ".", "" );
          //str.replace( ",", "." );
          tfloat fc = str.toDouble();
          str = values.value(8);
          //str.replace( ".", "" );
          //str.replace( ",", "." );
          tfloat V0 = str.toDouble();
          str = values.value(11);
          //str.replace( ".", "" );
          //str.replace( ",", "." );
          tfloat Q = str.toDouble();
          peqs.at(idx)->setParameters( fc, V0, Q );
          idx++;
        }
      }
    }
    qDebug()<<"Closing file";
    rewFile.close();
  }
  else
    QMessageBox::critical( this, tr("Loading file failed"),
                                     tr("I could not open your file. I am sorry."),
                                     QMessageBox::Ok, QMessageBox::NoButton, QMessageBox::NoButton );
}

//==============================================================================
/*!
 */
void MainWindow::updateWaitingForConnect( void )
{
  currentWaitRotation -= 10;
  rotateIconConnect( currentWaitRotation );
}

//==============================================================================
/*!
 */
void MainWindow::rotateIconConnect( int rotation )
{
  QImage srcImg(":/reload_128x128.png");
  srcImg = srcImg.scaled( 64, 64 );
  QPoint center = srcImg.rect().center();
  QMatrix matrix;
  matrix.translate(center.x(), center.y());
  matrix.rotate( rotation );
  QImage dstImg = srcImg.transformed(matrix, Qt::SmoothTransformation);
  dstImg = dstImg.copy( (dstImg.width()-64)/2, (dstImg.height()-64)/2, 70, 70 );
  //ui->actionRead_from_DSP->setIcon( QPixmap::fromImage(dstImg) );
  msgBox->setIconPixmap( QPixmap::fromImage(dstImg) );
}

//==============================================================================
/*!
 */
void MainWindow::on_tabPresets_currentChanged( int index )
{
  if( (index >= 0) && (index < NUMPRESETS) )
  {
    ui->statusBar->showMessage("Switching preset.......");
    enableGui( false );

    dsp.muteDAC();
    QThread::msleep( 200 );

    msgBox = new QMessageBox( QMessageBox::Information, tr("Waiting"), tr("Switching preset..."), QMessageBox::Cancel, this );
    msgBox->setStandardButtons( nullptr );
    msgBox->open();

    //dspPlugin[currentPreset]->setMasterVolume( -120, true );

    //dsp.mute();

    QEventLoop loopWaitForReply;
    QTimer timerWait;
    timerWait.setSingleShot( true );
    connect( &timerWait, SIGNAL(timeout()), &loopWaitForReply, SLOT(quit()) );
    timerWait.start( 500 );
    loopWaitForReply.exec();

    updatePresetGui( currentPreset, presetUserParams[currentPreset] );
    currentPreset = index;
    updatePlots();

    //qDebug()<<"Master Volume"<<dspPlugin[currentPreset]->getMasterVolume();

    dsp.selectPresetWifi( index, 60000 );
    dsp.setMasterVolume( static_cast<float>(dspPlugin[currentPreset]->getMasterVolume()) );
    dspPlugin[currentPreset]->setMasterVolume( ui->volumeSliderMain->value(), false );

    msgBox->accept();

    dsp.unmuteDAC();
    
    enableGui( true );
    ui->statusBar->showMessage("Ready");
  }
}

//==============================================================================
/*!
 */
void MainWindow::writeSettings( void )
{
  QFile fileSettings( pathSettings );
  QJsonDocument jsonDoc( jsonObjSettings );

  if( !fileSettings.open( QIODevice::WriteOnly ) )
  {
    qWarning( "Couldn't open file for saving user settings" );
    return;
  }
  fileSettings.write( jsonDoc.toJson() );
  fileSettings.close();
}

//==============================================================================
/*!
 */
void MainWindow::switchPluginGui( uint32_t pid )
{
switch( pid )
  {
  case CFreeDspAurora::PLUGIN_8CHANNELS:
    myLog()<<"Loading 8channels";

    ui->tabPresets->blockSignals( true );
    for( int ii = 0; ii < 4; ii++ )
    {
      presets[ii] = new QPreset;
      if( ii == 0 )
        ui->tabPresets->addTab( presets[ii], "Preset A" );
      else if( ii == 1 )
        ui->tabPresets->addTab( presets[ii], "Preset B" );  
      else if( ii == 2 )
        ui->tabPresets->addTab( presets[ii], "Preset C" ); 
      else if( ii == 3 )
        ui->tabPresets->addTab( presets[ii], "Preset D" ); 

      presets[ii]->tabChannels->removeTab( 0 );

      dspPlugin[ii] = new CPlugIn8Channels( FS );
      numChannels = dspPlugin[ii]->getNumChannels();
      for( unsigned int n = 0; n < numChannels; n++ )
      {
        tDspChannel dspChannel = dspPlugin[ii]->getGuiForChannel( n, FS, &dsp, this );

        presets[ii]->tabChannels->addTab( dspChannel.channel, "" );
        QLabel* lbl1 = new QLabel( presets[ii]->tabChannels );
        lbl1->setText( dspChannel.name );
        lbl1->setStyleSheet( QString("background-color: transparent; border: 0px solid black; border-left: 2px solid ") + colorPlot[n%kMaxPlotColors].name() + QString("; color: white; ") );
        lbl1->setFixedWidth( 100 );
        presets[ii]->tabChannels->tabBar()->setTabButton( static_cast<int>(n), QTabBar::LeftSide, lbl1 );

        dspChannel.layout->setSpacing( 0 );
        dspChannel.layout->setMargin( 0 );
        dspChannel.layout->setContentsMargins( 0, 0, 0, 0 );
        dspChannel.layout->setAlignment( Qt::AlignLeft );

        dspChannel.channel->widgetChannel->setLayout( dspChannel.layout );

        for( unsigned int chn = 0; chn < numChannels; chn++ )
        {
          QAction* action = new QAction( "    Show " + dspPlugin[ii]->getChannelName( chn ) );
          action->setCheckable( true );
          dspChannel.channel->actionsContextMenu.append( action );
          dspChannel.channel->contextMenu.addAction( action );
        }
        dspChannel.channel->actionsContextMenu.at(static_cast<int>(n))->setChecked( true );
        connect( dspChannel.channel, SIGNAL(selectionChanged()), this, SLOT(updatePlots()) );
      }
    }
    ui->tabPresets->blockSignals( false );
    break;

  case CFreeDspAurora::PLUGIN_HOMECINEMA71:
    myLog()<<"Loading HomeCinema71";

    ui->tabPresets->blockSignals( true );
    for( int ii = 0; ii < 4; ii++ )
    {
      presets[ii] = new QPreset;
      if( ii == 0 )
        ui->tabPresets->addTab( presets[ii], "Preset A" );
      else if( ii == 1 )
        ui->tabPresets->addTab( presets[ii], "Preset B" );  
      else if( ii == 2 )
        ui->tabPresets->addTab( presets[ii], "Preset C" ); 
      else if( ii == 3 )
        ui->tabPresets->addTab( presets[ii], "Preset D" ); 

      presets[ii]->tabChannels->removeTab( 0 );

      dspPlugin[ii] = new CPlugInHomeCinema71( FS );
      numChannels = dspPlugin[ii]->getNumChannels();
      for( unsigned int n = 0; n < numChannels; n++ )
      {
        tDspChannel dspChannel = dspPlugin[ii]->getGuiForChannel( n, FS, &dsp, this );

        presets[ii]->tabChannels->addTab( dspChannel.channel, "" );
        QLabel* lbl1 = new QLabel( presets[ii]->tabChannels );
        lbl1->setText( dspChannel.name );
        lbl1->setStyleSheet( QString("background-color: transparent; border: 0px solid black; border-left: 2px solid ") + colorPlot[n%kMaxPlotColors].name() + QString("; color: white; ") );
        lbl1->setFixedWidth( 100 );
        presets[ii]->tabChannels->tabBar()->setTabButton( static_cast<int>(n), QTabBar::LeftSide, lbl1 );

        dspChannel.layout->setSpacing( 0 );
        dspChannel.layout->setMargin( 0 );
        dspChannel.layout->setContentsMargins( 0, 0, 0, 0 );
        dspChannel.layout->setAlignment( Qt::AlignLeft );

        dspChannel.channel->widgetChannel->setLayout( dspChannel.layout );

        for( unsigned int chn = 0; chn < numChannels; chn++ )
        {
          QAction* action = new QAction( "    Show " + dspPlugin[ii]->getChannelName( chn ) );
          action->setCheckable( true );
          dspChannel.channel->actionsContextMenu.append( action );
          dspChannel.channel->contextMenu.addAction( action );
        }
        dspChannel.channel->actionsContextMenu.at(static_cast<int>(n))->setChecked( true );
        connect( dspChannel.channel, SIGNAL(selectionChanged()), this, SLOT(updatePlots()) );
      }
    }
    ui->tabPresets->blockSignals( false );
    break;

  case CFreeDspAurora::PLUGIN_8CHANNELS_USB:
    myLog()<<"Loading 8channelsUSB";

    ui->tabPresets->blockSignals( true );
    for( int ii = 0; ii < 4; ii++ )
    {
      presets[ii] = new QPreset;
      if( ii == 0 )
        ui->tabPresets->addTab( presets[ii], "Preset A" );
      else if( ii == 1 )
        ui->tabPresets->addTab( presets[ii], "Preset B" );  
      else if( ii == 2 )
        ui->tabPresets->addTab( presets[ii], "Preset C" ); 
      else if( ii == 3 )
        ui->tabPresets->addTab( presets[ii], "Preset D" ); 

      presets[ii]->tabChannels->removeTab( 0 );

      dspPlugin[ii] = new CPlugIn8ChannelsUSB( FS );
      numChannels = dspPlugin[ii]->getNumChannels();
      for( unsigned int n = 0; n < numChannels; n++ )
      {
        tDspChannel dspChannel = dspPlugin[ii]->getGuiForChannel( n, FS, &dsp, this );

        presets[ii]->tabChannels->addTab( dspChannel.channel, "" );
        QLabel* lbl1 = new QLabel( presets[ii]->tabChannels );
        lbl1->setText( dspChannel.name );
        lbl1->setStyleSheet( QString("background-color: transparent; border: 0px solid black; border-left: 2px solid ") + colorPlot[n%kMaxPlotColors].name() + QString("; color: white; ") );
        lbl1->setFixedWidth( 100 );
        presets[ii]->tabChannels->tabBar()->setTabButton( static_cast<int>(n), QTabBar::LeftSide, lbl1 );

        dspChannel.layout->setSpacing( 0 );
        dspChannel.layout->setMargin( 0 );
        dspChannel.layout->setContentsMargins( 0, 0, 0, 0 );
        dspChannel.layout->setAlignment( Qt::AlignLeft );

        dspChannel.channel->widgetChannel->setLayout( dspChannel.layout );

        for( unsigned int chn = 0; chn < numChannels; chn++ )
        {
          QAction* action = new QAction( "    Show " + dspPlugin[ii]->getChannelName( chn ) );
          action->setCheckable( true );
          dspChannel.channel->actionsContextMenu.append( action );
          dspChannel.channel->contextMenu.addAction( action );
        }
        dspChannel.channel->actionsContextMenu.at(static_cast<int>(n))->setChecked( true );
        connect( dspChannel.channel, SIGNAL(selectionChanged()), this, SLOT(updatePlots()) );
      }
    }
    ui->tabPresets->blockSignals( false );
    break;

  case CFreeDspAurora::PLUGIN_HOMECINEMA71_USB:
    myLog()<<"Loading HomeCinema71 USB";

    ui->tabPresets->blockSignals( true );
    for( int ii = 0; ii < 4; ii++ )
    {
      presets[ii] = new QPreset;
      if( ii == 0 )
        ui->tabPresets->addTab( presets[ii], "Preset A" );
      else if( ii == 1 )
        ui->tabPresets->addTab( presets[ii], "Preset B" );  
      else if( ii == 2 )
        ui->tabPresets->addTab( presets[ii], "Preset C" ); 
      else if( ii == 3 )
        ui->tabPresets->addTab( presets[ii], "Preset D" ); 

      presets[ii]->tabChannels->removeTab( 0 );

      dspPlugin[ii] = new CPlugInHomeCinema71USB( FS );
      numChannels = dspPlugin[ii]->getNumChannels();
      for( unsigned int n = 0; n < numChannels; n++ )
      {
        tDspChannel dspChannel = dspPlugin[ii]->getGuiForChannel( n, FS, &dsp, this );

        presets[ii]->tabChannels->addTab( dspChannel.channel, "" );
        QLabel* lbl1 = new QLabel( presets[ii]->tabChannels );
        lbl1->setText( dspChannel.name );
        lbl1->setStyleSheet( QString("background-color: transparent; border: 0px solid black; border-left: 2px solid ") + colorPlot[n%kMaxPlotColors].name() + QString("; color: white; ") );
        lbl1->setFixedWidth( 100 );
        presets[ii]->tabChannels->tabBar()->setTabButton( static_cast<int>(n), QTabBar::LeftSide, lbl1 );

        dspChannel.layout->setSpacing( 0 );
        dspChannel.layout->setMargin( 0 );
        dspChannel.layout->setContentsMargins( 0, 0, 0, 0 );
        dspChannel.layout->setAlignment( Qt::AlignLeft );

        dspChannel.channel->widgetChannel->setLayout( dspChannel.layout );

        for( unsigned int chn = 0; chn < numChannels; chn++ )
        {
          QAction* action = new QAction( "    Show " + dspPlugin[ii]->getChannelName( chn ) );
          action->setCheckable( true );
          dspChannel.channel->actionsContextMenu.append( action );
          dspChannel.channel->contextMenu.addAction( action );
        }
        dspChannel.channel->actionsContextMenu.at(static_cast<int>(n))->setChecked( true );
        connect( dspChannel.channel, SIGNAL(selectionChanged()), this, SLOT(updatePlots()) );
      }
    }
    ui->tabPresets->blockSignals( false );
    break;

  case CFreeDspAurora::PLUGIN_4FIRS:
    myLog()<<"Loading 4FIRS";

    ui->tabPresets->blockSignals( true );
    for( int ii = 0; ii < 4; ii++ )
    {
      presets[ii] = new QPreset;
      if( ii == 0 )
        ui->tabPresets->addTab( presets[ii], "Preset A" );
      else if( ii == 1 )
        ui->tabPresets->addTab( presets[ii], "Preset B" );  
      else if( ii == 2 )
        ui->tabPresets->addTab( presets[ii], "Preset C" ); 
      else if( ii == 3 )
        ui->tabPresets->addTab( presets[ii], "Preset D" ); 

      presets[ii]->tabChannels->removeTab( 0 );

      dspPlugin[ii] = new CPlugIn4FIRs( FS );
      numChannels = dspPlugin[ii]->getNumChannels();
      for( unsigned int n = 0; n < numChannels; n++ )
      {
        tDspChannel dspChannel = dspPlugin[ii]->getGuiForChannel( n, FS, &dsp, this );

        presets[ii]->tabChannels->addTab( dspChannel.channel, "" );
        QLabel* lbl1 = new QLabel( presets[ii]->tabChannels );
        lbl1->setText( dspChannel.name );
        lbl1->setStyleSheet( QString("background-color: transparent; border: 0px solid black; border-left: 2px solid ") + colorPlot[n%kMaxPlotColors].name() + QString("; color: white; ") );
        lbl1->setFixedWidth( 100 );
        presets[ii]->tabChannels->tabBar()->setTabButton( static_cast<int>(n), QTabBar::LeftSide, lbl1 );

        dspChannel.layout->setSpacing( 0 );
        dspChannel.layout->setMargin( 0 );
        dspChannel.layout->setContentsMargins( 0, 0, 0, 0 );
        dspChannel.layout->setAlignment( Qt::AlignLeft );

        dspChannel.channel->widgetChannel->setLayout( dspChannel.layout );

        for( unsigned int chn = 0; chn < numChannels; chn++ )
        {
          QAction* action = new QAction( "    Show " + dspPlugin[ii]->getChannelName( chn ) );
          action->setCheckable( true );
          dspChannel.channel->actionsContextMenu.append( action );
          dspChannel.channel->contextMenu.addAction( action );
        }
        dspChannel.channel->actionsContextMenu.at(static_cast<int>(n))->setChecked( true );
        connect( dspChannel.channel, SIGNAL(selectionChanged()), this, SLOT(updatePlots()) );
      }
    }
    ui->tabPresets->blockSignals( false );
    break;

  case CFreeDspAurora::PLUGIN_CUSTOM:
    myLog()<<"Loading custom";

    ui->tabPresets->blockSignals( true );
    for( int ii = 0; ii < 4; ii++ )
    {
      presets[ii] = new QPreset;
      if( ii == 0 )
        ui->tabPresets->addTab( presets[ii], "Preset A" );
      else if( ii == 1 )
        ui->tabPresets->addTab( presets[ii], "Preset B" );  
      else if( ii == 2 )
        ui->tabPresets->addTab( presets[ii], "Preset C" ); 
      else if( ii == 3 )
        ui->tabPresets->addTab( presets[ii], "Preset D" ); 

      presets[ii]->tabChannels->removeTab( 0 );

      dspPlugin[ii] = new CPlugInCustom( FS );
      numChannels = dspPlugin[ii]->getNumChannels();
      for( unsigned int n = 0; n < numChannels; n++ )
      {
        tDspChannel dspChannel = dspPlugin[ii]->getGuiForChannel( n, FS, &dsp, this );

        presets[ii]->tabChannels->addTab( dspChannel.channel, "" );
        QLabel* lbl1 = new QLabel( presets[ii]->tabChannels );
        lbl1->setText( dspChannel.name );
        lbl1->setStyleSheet( QString("background-color: transparent; border: 0px solid black; border-left: 2px solid ") + colorPlot[n%kMaxPlotColors].name() + QString("; color: white; ") );
        lbl1->setFixedWidth( 100 );
        presets[ii]->tabChannels->tabBar()->setTabButton( static_cast<int>(n), QTabBar::LeftSide, lbl1 );

        dspChannel.layout->setSpacing( 0 );
        dspChannel.layout->setMargin( 0 );
        dspChannel.layout->setContentsMargins( 0, 0, 0, 0 );
        dspChannel.layout->setAlignment( Qt::AlignLeft );

        dspChannel.channel->widgetChannel->setLayout( dspChannel.layout );

        for( unsigned int chn = 0; chn < numChannels; chn++ )
        {
          QAction* action = new QAction( "    Show " + dspPlugin[ii]->getChannelName( chn ) );
          action->setCheckable( true );
          dspChannel.channel->actionsContextMenu.append( action );
          dspChannel.channel->contextMenu.addAction( action );
        }
        dspChannel.channel->actionsContextMenu.at(static_cast<int>(n))->setChecked( true );
        connect( dspChannel.channel, SIGNAL(selectionChanged()), this, SLOT(updatePlots()) );
      }
    }
    ui->tabPresets->blockSignals( false );
    break;

  case 0:
    setEnabled( true );
    msgBox->accept();
    QMessageBox::warning( this, tr("Warning"), tr("It seems that there is no plugin installed. Please install a valid plugin on your board."), QMessageBox::Ok ); 
    ui->statusBar->showMessage("Ready");
    return;

  default:
    qDebug()<<"Unknown plugin"<<pid;
    setEnabled( true );
    msgBox->accept();
    QMessageBox::critical( this, tr("Error"), tr("Your DSP reports an unknown PID. Please reinstall a valid plugin on your board."), QMessageBox::Ok ); 
    ui->statusBar->showMessage("Ready");
    return;
  }
}

//==============================================================================
/*!
 */
void MainWindow::on_actionSaveParameters_triggered()
{
  QString fileName = QFileDialog::getSaveFileName( this, tr("Save parameters to file"), 
                                                   QStandardPaths::locate(QStandardPaths::DocumentsLocation, QString(), QStandardPaths::LocateDirectory),
                                                   tr("Parameters Files (*.dspPrj)") );
  if( fileName.isEmpty() )
    return;

  //----------------------------------------------------------------------------
  //--- Build usrparam.hex file
  //----------------------------------------------------------------------------
  QByteArray fileparams;

  fileparams.append( static_cast<char>((VERSION_HEX)       & 0x000000FF) );
  fileparams.append( static_cast<char>((VERSION_HEX >>  8) & 0x000000FF) );
  fileparams.append( static_cast<char>((VERSION_HEX >> 16) & 0x000000FF) );
  fileparams.append( static_cast<char>((VERSION_HEX >> 24) & 0x000000FF) );

  for( uint32_t p = 0; p < NUMPRESETS; p++ )
  {
    fileparams.append( static_cast<char>((dspPlugin[p]->getPid()) & 0x000000FF) );
    fileparams.append( static_cast<char>((dspPlugin[p]->getPid() >> 8) & 0x000000FF) );
    fileparams.append( static_cast<char>((dspPlugin[p]->getPid() >> 16) & 0x000000FF) );
    fileparams.append( static_cast<char>((dspPlugin[p]->getPid() >> 24) & 0x000000FF) );

    QByteArray usrparams;
    for( unsigned int ii = 0; ii < dspPlugin[p]->getNumChannels(); ii++ )
    {
      QChannel* channel = dspPlugin[p]->getChannel( ii );
      for( unsigned int n = 0; n < channel->getNumDspBlocks(); n++ )
      {
        QDspBlock* dspBlock = channel->getDspBlock(n);
        QByteArray params = dspBlock->getUserParams();
        if( params.size() )
          usrparams.append( params );
      }
    }
    usrparams.append( ui->volumeSliderMain->getUserParams() );
    usrparams.append( dspPlugin[p]->getUserParams() );

    uint32_t size = static_cast<uint32_t>(usrparams.size());
    fileparams.append( static_cast<char>((size) & 0x000000FF) );
    fileparams.append( static_cast<char>((size >> 8) & 0x000000FF) );
    fileparams.append( static_cast<char>((size >> 16) & 0x000000FF) );
    fileparams.append( static_cast<char>((size >> 24) & 0x000000FF) );
    fileparams.append( usrparams );
  }

  QFile file( fileName );
  if( !file.open( QIODevice::WriteOnly ) )
  {
    QMessageBox::critical( this, tr("Error"), tr("Could not open the file."), QMessageBox::Ok ); 
    myLog()<<"Could not open file "<<fileName;
    return;
  }

  if( file.write( fileparams ) == -1 )
  {
    QMessageBox::critical( this, tr("Error"), tr("Could not write to file."), QMessageBox::Ok ); 
    myLog()<<"Could not write to file "<<fileName;
    return;
  }

  file.close();
}

//==============================================================================
/*!
 */
void MainWindow::on_actionLoadParameters_triggered()
{
  QString fileName = QFileDialog::getOpenFileName( this, tr("Load parameters from file"), 
                                                   QStandardPaths::locate(QStandardPaths::DocumentsLocation, QString(), QStandardPaths::LocateDirectory),
                                                   tr("Parameters Files (*.dspPrj)") );
  if( fileName.isEmpty() )
    return;

  QFile file( fileName );
  if( !file.open( QIODevice::ReadOnly ) )
  {
    QMessageBox::critical( this, tr("Error"), tr("Coudl not open the file."), QMessageBox::Ok ); 
    myLog()<<"Could not open file "<<fileName;
    return;
  }

  QByteArray fileparams = file.readAll();

  file.close();

  if( fileparams.size() > 0 )
  {
    int idx = 0;

    QByteArray fileversion;
    fileversion.append( fileparams.at(idx) );
    idx++;
    fileversion.append( fileparams.at(idx) );
    idx++;
    fileversion.append( fileparams.at(idx) );
    idx++;
    fileversion.append( fileparams.at(idx) );
    idx++;
    uint32_t pver = *reinterpret_cast<const uint32_t*>(fileversion.data());
    if( (pver != VERSION_HEX) && (pver != 0x00010200) )
    {
      QMessageBox::critical( this, tr("Error"), tr("File version incompatible with current version of auverdionControl."), QMessageBox::Ok ); 
      myLog()<<"File version incompatible with current version of auverdionControl.";
      return;
    }
      
    for( int p = 0; p < NUMPRESETS; p++ )
    {
      QByteArray param;
      param.append( fileparams.at(idx) );
      idx++;
      param.append( fileparams.at(idx) );
      idx++;
      param.append( fileparams.at(idx) );
      idx++;
      param.append( fileparams.at(idx) );
      idx++;
      uint32_t pid = *reinterpret_cast<const uint32_t*>(param.data());
      int32_t size = 0;
      if( pid == dspPlugin[p]->getPid() )
      {
        param.clear();
        param.append( fileparams.at(idx) );
        idx++;
        param.append( fileparams.at(idx) );
        idx++;
        param.append( fileparams.at(idx) );
        idx++;
        param.append( fileparams.at(idx) );
        idx++;
        size = static_cast<int32_t>(*reinterpret_cast<const uint32_t*>(param.data()));

        QByteArray userparams = fileparams.mid( idx, size );
        updatePresetGui( p, userparams );
        presetUserParams[p] = userparams;
        dspPlugin[p]->setMasterVolume( ui->volumeSliderMain->value(), false );
      }
      else
      {
        myLog()<<"Plugin does not match the file.";
        QMessageBox::critical( this, tr("Error"), tr("Sorry, Plugin does not match the file."), QMessageBox::Ok );
        return;
      }
      idx += size;
    }
    updatePlots();
  }
}
