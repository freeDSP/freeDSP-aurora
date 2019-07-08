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

#include "MainWindow.hpp"
#include "ui_MainWindow.h"

#include "DialogSettings.hpp"
#include "QDialogDemoSelector.hpp"

#include "PlugIn8Channels.hpp"
#include "PlugInHomeCinema71.hpp"
#include "PlugIn4FIRs.hpp"

#include "LogFile.h"

extern CLogFile myLog;

#define VERSION_STR "0.9.9"
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


QVolumeSlider* sliderMainVolume;

MainWindow::MainWindow( QWidget* parent ) :
  QMainWindow( parent ),
  ui( new Ui::MainWindow )
{
  ui->setupUi(this);
  #if defined( __IOS__ ) || defined( __WIN__ ) || defined( __LINUX__ )
  ui->menuBar->hide();
  #endif
  ui->actionWrite_to_DSP->setEnabled( false );

  #if defined( __MACOSX__ )
  QFile fileSettings( "./settings.json" );
  #elif defined( __WIN__ )
  QFile fileSettings( "settings.json" );
  #endif

  if( fileSettings.open( QIODevice::ReadOnly ) )
  {
    QByteArray settings = fileSettings.readAll();
    QJsonDocument jsonDoc( QJsonDocument::fromJson( settings ) );
    QJsonObject jsonObj = jsonDoc.object();
    dsp.setConnectionTypeWifi( jsonObj[ "network" ].toInt() );
    dsp.setSsidWifi( jsonObj[ "ssid" ].toString() );
    dsp.setIpAddressWifi( jsonObj[ "ip" ].toString() );
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
        QAction* action = new QAction( "Show " + dspPlugin[ii]->getChannelName( chn ) );
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
  //--- Request the DSP-plugin id
  //----------------------------------------------------------------------------
  ui->statusBar->showMessage("Reading PID.......");
  uint32_t pid = dsp.requestPidWifi();
  if( pid == 0 )
  {
    msgBox->accept();
    return;
  }

  int preset = dsp.requestCurrentPresetWifi();
  if( preset > -1 )
  {
    currentPreset = preset;
    ui->tabPresets->blockSignals( true );
    ui->tabPresets->setCurrentIndex( preset );
    ui->tabPresets->blockSignals( false );
  }

  //----------------------------------------------------------------------------
  //--- Delete old preset GUI
  //----------------------------------------------------------------------------
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
  
  switch( pid )
  {
  case CFreeDspAurora::PLUGIN_8CHANNELS:
    
    qDebug()<<"Loading 8channels";

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
        //tDspChannel dspChannel = plugin8Channels.getGuiForChannel( n, FS, &dsp, this );
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
          //QAction* action = new QAction( "Show " + plugin8Channels.getChannelName( chn ) );
          QAction* action = new QAction( "Show " + dspPlugin[ii]->getChannelName( chn ) );
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
    qDebug()<<"PID"<<pid;
    setEnabled( true );
    disconnect( &timerWait, SIGNAL(timeout()), this, SLOT(updateWaitingForConnect()) );
    msgBox->accept();
    QMessageBox::warning( this, tr("Warning"), tr("It seems that there is no plugin installed. Please install a valid plugin on your board."), QMessageBox::Ok ); 
    ui->statusBar->showMessage("Ready");
    return;

  default:
    qDebug()<<"Unkown plugin"<<pid;
    setEnabled( true );
    disconnect( &timerWait, SIGNAL(timeout()), this, SLOT(updateWaitingForConnect()) );
    msgBox->accept();
    QMessageBox::critical( this, tr("Error"), tr("Your DSP reports an unkown PID. Please reinstall a valid plugin on your board."), QMessageBox::Ok ); 
    ui->statusBar->showMessage("Ready");
    return;
  }

  //----------------------------------------------------------------------------
  //--- Request the firmware version
  //----------------------------------------------------------------------------
  ui->statusBar->showMessage("Reading firmware version.......");
  dsp.requestFirmwareVersionWifi();

  //----------------------------------------------------------------------------
  //--- Request the AddOn-Id
  //----------------------------------------------------------------------------
  ui->statusBar->showMessage("Reading AddOn-Id.......");
  dsp.requestAddOnIdWifi();

  //----------------------------------------------------------------------------
  //--- Request user parameters
  //----------------------------------------------------------------------------
  ui->statusBar->showMessage("Reading user parameter.......");

  for( unsigned int p = 0; p < NUMPRESETS; p++ )
  {
    dsp.selectPresetWifi( p );
    QByteArray userparams;
    if( dsp.requestUserParameterWifi( userparams ) )
    {
      updatePresetGui( p, userparams );
      presetUserParams[p] = userparams;
    }
  }

  currentPreset = preset;
  dsp.selectPresetWifi( preset );
  ui->tabPresets->blockSignals( true );
  ui->tabPresets->setCurrentIndex( currentPreset );
  ui->tabPresets->blockSignals( false );  

  updatePlots();

  setEnabled( true );
  disconnect( &timerWait, SIGNAL(timeout()), this, SLOT(updateWaitingForConnect()) );
  currentWaitRotation = 0;
  //rotateIconConnect( currentWaitRotation );
  msgBox->accept();
  ui->statusBar->showMessage("Ready");
  ui->actionWrite_to_DSP->setEnabled( true );
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
    qDebug()<<"Set volume slider: Not enough data";
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
        if( params.size() )
          dspparams[p].append( params );
      }
    }
    dspparams[p].append( dsp.makeParameterForWifi( dspPlugin[p]->getAddressMasterVolume(), static_cast<float>(pow( 10.0, ui->volumeSliderMain->value()/20.0 ) ) ) );
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
        if( params.size() )
          usrparams[p].append( params );
      }
    }
    usrparams[p].append( ui->volumeSliderMain->getUserParams() );
    presetUserParams[p] = usrparams[p];
  }
  
  QProgressDialog progress( tr("Storing your DSP settings..."), tr("Abort"), 0, (dspparams[0].size() + usrparams[0].size()) * NUMPRESETS, this );
  progress.setWindowModality(Qt::WindowModal);
  int progressValue = 0;

  for( int p = 0; p < NUMPRESETS; p++ )
  {
    dsp.selectPresetWifi( p );

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
  progress.setValue( dspparams[0].size() * NUMPRESETS + usrparams[0].size() * NUMPRESETS );

  dsp.selectPresetWifi( ui->tabPresets->currentIndex() );
  dsp.storePresetSelection();

  myLog()<<"Success";
  qDebug()<<"File size dspparam.hex:"<<dspparams[0].size() / 1024<<"KiB";
  qDebug()<<"File size usrparam.hex:"<<usrparams[0].size() / 1024<<"KiB";

  QMessageBox::information( this, tr("Success"), tr("You have successfully stored your settings!"), QMessageBox::Ok );

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
  DialogSettings dialog( &dsp, this );
  int result = dialog.exec();
  if( result == QDialog::Accepted )
  { 
    #if defined( __MACOSX__ )
    QFile fileSettings( "./settings.json" );
    #elif defined( __WIN__ )
    QFile fileSettings( "settings.json" );
    #endif

    QJsonObject jsonObj;
    jsonObj[ "network" ] = dsp.getConnectionTypeWifi();
    jsonObj[ "ssid" ] = dsp.getSsidWifi();
    jsonObj[ "ip" ] = dsp.getIpAddressLocalWifi();

    QJsonDocument jsonDoc( jsonObj );

    if( !fileSettings.open( QIODevice::WriteOnly ) )
    {
      qWarning( "Couldn't open file for saving user settings" );
      return;
    }
    fileSettings.write( jsonDoc.toJson() );
    fileSettings.close();
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

  QString fileName = QFileDialog::getOpenFileName( this, tr("Open REW export file"), 
                                                     QStandardPaths::locate(QStandardPaths::DocumentsLocation, QString(), QStandardPaths::LocateDirectory),
                                                     tr("REW Files (*.txt)") );
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
          str.replace( ".", "" );
          str.replace( ",", "." );
          tfloat fc = str.toDouble();
          str = values.value(8);
          str.replace( ".", "" );
          str.replace( ",", "." );
          tfloat V0 = str.toDouble();
          str = values.value(11);
          str.replace( ".", "" );
          str.replace( ",", "." );
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
  if( (index >= 0) && (index < 4) )
  {
    ui->statusBar->showMessage("Switching preset.......");

    msgBox = new QMessageBox( QMessageBox::Information, tr("Waiting"), tr("Switching preset..."), QMessageBox::Cancel, this );
    msgBox->setStandardButtons( nullptr );
    msgBox->open();

    updatePresetGui( currentPreset, presetUserParams[currentPreset] );
    currentPreset = index;
    updatePlots();
    dsp.selectPresetWifi( index );

    msgBox->accept();
    ui->statusBar->showMessage("Ready");
  }
}
