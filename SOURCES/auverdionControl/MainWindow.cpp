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

#define VERSION_STR "0.9.6"
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

CDspPlugin* dspPlugin;

MainWindow::MainWindow( QWidget* parent ) :
  QMainWindow( parent ),
  ui( new Ui::MainWindow )
{
  ui->setupUi(this);
  #if defined( __IOS__ ) || defined( __WIN__ ) || defined( __LINUX__ )
  ui->menuBar->hide();
  #endif
  //ui->actionWrite_to_DSP->setEnabled( false );

  #if defined( __MACOSX__ )
  QFile fileSettings( "./settings.json" );
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
  ui->tabChannels->removeTab( 0 );
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
 
  //if( dialog.comboBox()->currentText() == QString("8channels") )
  //{
    qDebug()<<"Loading plugin 8channels";
    dspPlugin = new CPlugIn8Channels( FS );
    numChannels = dspPlugin->getNumChannels();
    for( unsigned int n = 0; n < numChannels; n++ )
    {
      tDspChannel dspChannel = dspPlugin->getGuiForChannel( n, FS, &dsp, this );

      listOutputGains.append( dspChannel.gain );

      ui->tabChannels->addTab( dspChannel.channel, "" );
      lbl1 = new QLabel( ui->tabChannels );
      lbl1->setText( dspChannel.name );
      lbl1->setStyleSheet( QString("background-color: transparent; border: 0px solid black; border-left: 2px solid ") + colorPlot[n%kMaxPlotColors].name() + QString("; color: white; ") );
      lbl1->setFixedWidth( 100 );
      ui->tabChannels->tabBar()->setTabButton( static_cast<int>(n), QTabBar::LeftSide, lbl1 );

      dspChannel.layout->setSpacing( 0 );
      dspChannel.layout->setMargin( 0 );
      dspChannel.layout->setContentsMargins( 0, 0, 0, 0 );
      dspChannel.layout->setAlignment( Qt::AlignLeft );

      dspChannel.channel->widgetChannel->setLayout( dspChannel.layout );

      for( unsigned int chn = 0; chn < numChannels; chn++ )
      {
        //QAction* action = new QAction( "Show " + plugin8Channels.getChannelName( chn ) );
        QAction* action = new QAction( "Show " + dspPlugin->getChannelName( chn ) );
        action->setCheckable( true );
        dspChannel.channel->actionsContextMenu.append( action );
        dspChannel.channel->contextMenu.addAction( action );
      }
      dspChannel.channel->actionsContextMenu.at(static_cast<int>(n))->setChecked( true );
      connect( dspChannel.channel, SIGNAL(selectionChanged()), this, SLOT(updatePlots()) );
    }
    //dspPlugin = &plugin8Channels;
  //}         
  #endif

  freq = dspPlugin->getFrequencyVector();

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
  for( int chn = 0; chn < ui->tabChannels->count(); chn++ )
  {
    QChannel* channel = static_cast<QChannel*>(ui->tabChannels->widget(chn));
    if( channel != nullptr )
    {
      channel->update( freq );
      //tvector<tcomplex> H = channel->getTransferFunction();
      //channel->figVoltageMagnitude->semilogx( freq, 20.0 * log10( abs( H ) ), Qt::white, 2 );
    }
  }

  for( int chn = 0; chn < ui->tabChannels->count(); chn++ )
  {
    tvector<tcomplex> H;
    QChannel* currentChannel = static_cast<QChannel*>(ui->tabChannels->widget(chn));
    if( currentChannel != nullptr )
    {
      currentChannel->figVoltageMagnitude->clear();
      currentChannel->figVoltageMagnitude->holdon();

      for( unsigned int ii = 0; ii < numChannels; ii++ )
      {
        if( currentChannel->actionsContextMenu.at(static_cast<int>(ii))->isChecked() )
        {
          QChannel* channel = static_cast<QChannel*>(ui->tabChannels->widget(static_cast<int>(ii)));
          if( length(H) > 0 )
            H = H + channel->getTransferFunction();
          else
            H = channel->getTransferFunction();

          currentChannel->figVoltageMagnitude->semilogx( freq, 20.0 * log10( abs( channel->getTransferFunction() ) ), colorPlot[ii%8], 2 );
        }
      }

      if( dspPlugin->doSummation() )
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
 
  //----------------------------------------------------------------------------
  //--- Request the DSP-plugin id
  //----------------------------------------------------------------------------
  setEnabled( false );

  QTimer timerWait;
  connect( &timerWait, SIGNAL(timeout()), this, SLOT(updateWaitingForConnect()) );
  timerWait.start( 100 );
  currentWaitRotation = 0;

  msgBox = new QMessageBox( QMessageBox::Information, tr("Waiting"), tr("Connecting to DSP..."), QMessageBox::Cancel, this );
  QImage srcImg = QImage(":/reload_128x128.png").scaled(64,64);
  srcImg = srcImg.copy( 0, 0, 70, 70 );
  msgBox->setIconPixmap( QPixmap::fromImage( srcImg ) );
  msgBox->setStandardButtons(0);
  msgBox->open();

  ui->statusBar->showMessage("Reading PID.......");
  uint32_t pid = dsp.requestPidWifi();

  while( ui->tabChannels->count() )
  {
	  delete ui->tabChannels->widget( ui->tabChannels->currentIndex() );
  }

  // \TODO Fix the crash when calling delete.
  //delete dspPlugin;
  
  switch( pid )
  {
  case CFreeDspAurora::PLUGIN_8CHANNELS:
    
    qDebug()<<"Loading 8channels";
    dspPlugin = new CPlugIn8Channels( FS );
    numChannels = dspPlugin->getNumChannels();
    for( unsigned int n = 0; n < numChannels; n++ )
    {
      //tDspChannel dspChannel = plugin8Channels.getGuiForChannel( n, FS, &dsp, this );
      tDspChannel dspChannel = dspPlugin->getGuiForChannel( n, FS, &dsp, this );

      listOutputGains.append( dspChannel.gain );

      ui->tabChannels->addTab( dspChannel.channel, "" );
      QLabel* lbl1 = new QLabel( ui->tabChannels );
      lbl1->setText( dspChannel.name );
      lbl1->setStyleSheet( QString("background-color: transparent; border: 0px solid black; border-left: 2px solid ") + colorPlot[n%kMaxPlotColors].name() + QString("; color: white; ") );
      lbl1->setFixedWidth( 100 );
      ui->tabChannels->tabBar()->setTabButton( static_cast<int>(n), QTabBar::LeftSide, lbl1 );

      dspChannel.layout->setSpacing( 0 );
      dspChannel.layout->setMargin( 0 );
      dspChannel.layout->setContentsMargins( 0, 0, 0, 0 );
      dspChannel.layout->setAlignment( Qt::AlignLeft );

      dspChannel.channel->widgetChannel->setLayout( dspChannel.layout );

      for( unsigned int chn = 0; chn < numChannels; chn++ )
      {
        //QAction* action = new QAction( "Show " + plugin8Channels.getChannelName( chn ) );
        QAction* action = new QAction( "Show " + dspPlugin->getChannelName( chn ) );
        action->setCheckable( true );
        dspChannel.channel->actionsContextMenu.append( action );
        dspChannel.channel->contextMenu.addAction( action );
      }
      dspChannel.channel->actionsContextMenu.at(static_cast<int>(n))->setChecked( true );
      connect( dspChannel.channel, SIGNAL(selectionChanged()), this, SLOT(updatePlots()) );
    }
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
  //--- Request user parameters
  //----------------------------------------------------------------------------
  ui->statusBar->showMessage("Reading user parameter.......");
  QByteArray userparams;
  if( dsp.requestUserParameterWifi( userparams ) )
  {
    int idx = 0;
    for( unsigned int ii = 0; ii < dspPlugin->getNumChannels(); ii++ )
    {
      QChannel* channel = dspPlugin->getChannel( ii );
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
void MainWindow::on_actionWrite_to_DSP_triggered()
{
  //----------------------------------------------------------------------------
  //--- Build dspparam.hex file
  //----------------------------------------------------------------------------
  qDebug()<<"Build dspparam.hex file";
  QByteArray dspparams;
  for( unsigned int ii = 0; ii < dspPlugin->getNumChannels(); ii++ )
  {
    QChannel* channel = dspPlugin->getChannel( ii );
    for( unsigned int n = 0; n < channel->getNumDspBlocks(); n++ )
    {
      QDspBlock* dspBlock = channel->getDspBlock(n);
      QByteArray params = dspBlock->getDspParams();
      if( params.size() )
        dspparams.append( params );
    }
  }
  dspparams.append( dsp.makeParameterForWifi( dspPlugin->getAddressMasterVolume(), static_cast<float>(pow( 10.0, ui->volumeSliderMain->value()/20.0 ) ) ) );
  
  //----------------------------------------------------------------------------
  //--- Build usrparam.hex file
  //----------------------------------------------------------------------------
  qDebug()<<"Build usrparam.hex file";
  QByteArray usrparams;
  for( unsigned int ii = 0; ii < dspPlugin->getNumChannels(); ii++ )
  {
    QChannel* channel = dspPlugin->getChannel( ii );
    for( unsigned int n = 0; n < channel->getNumDspBlocks(); n++ )
    {
      QDspBlock* dspBlock = channel->getDspBlock(n);
      qDebug()<<n;
      QByteArray params = dspBlock->getUserParams();
      if( params.size() )
        usrparams.append( params );
    }
  }
  usrparams.append( ui->volumeSliderMain->getUserParams() );

  //----------------------------------------------------------------------------
  //--- Send dspparam.hex file
  //----------------------------------------------------------------------------
  qDebug()<<"Send dspparam.hex file";
  QProgressDialog progress( tr("Storing your DSP settings..."), tr("Abort"), 0, dspparams.size() + usrparams.size(), this );
  progress.setWindowModality(Qt::WindowModal);

  int offset = 0;
  uint32_t totalTransmittedBytes = 0;
  while( offset < dspparams.size() )
  {
    QByteArray packet;
    for( int ii = 0; ii < 64; ii++ )
    {
      if( offset < dspparams.size() )
        packet.append( dspparams.at(offset) );
      offset++;
    }
    dsp.sendDspParameterWifi( packet );
    totalTransmittedBytes += static_cast<uint32_t>(packet.size());

    progress.setValue( offset );

    if( progress.wasCanceled() )
      /* \TODO Handle cancel */
      return;
  }
  progress.setValue( dspparams.size() );

  if( !dsp.finishDspParameterWifi( totalTransmittedBytes*2 ) )
  {
    QMessageBox::critical( this, tr("Error"), tr("Uups, something went wrong with storing the DSP parameters. Please double check everything and try again."), QMessageBox::Ok );  
    return;
  }

  //----------------------------------------------------------------------------
  //--- Send userparam.hex file
  //----------------------------------------------------------------------------
  qDebug()<<"Send userparam.hex file";
  offset = 0;
  totalTransmittedBytes = 0;
  while( offset < usrparams.size() )
  {
    QByteArray packet;
    for( int ii = 0; ii < 64; ii++ )
    {
      if( offset < usrparams.size() )
        packet.append( usrparams.at(offset) );
      offset++;
    }
    dsp.sendUserParameterWifi( packet );
    totalTransmittedBytes += static_cast<uint32_t>(packet.size());

    progress.setValue( dspparams.size() + offset );

    if( progress.wasCanceled() )
      /* \TODO Handle cancel */
      return;
  }
  progress.setValue( dspparams.size() + usrparams.size() );

  if( !dsp.finishUserParameterWifi( totalTransmittedBytes*2 ) )
  {
    QMessageBox::critical( this, tr("Error"), tr("Uups, something went wrong with storing the user settings. Please double check everything and try again."), QMessageBox::Ok );  
    return;
  }

  qDebug()<<"Success";
  qDebug()<<"File size dspparam.hex:"<<dspparams.size() / 1024<<"KiB";
  qDebug()<<"File size usrparam.hex:"<<usrparams.size() / 1024<<"KiB";

  QMessageBox::information( this, tr("Success"), tr("You have successfully stored your settings!"), QMessageBox::Ok );

#if 0
  

  QProgressDialog progress( tr("Storing user parameter..."), tr("Abort"), 0, content.size(), this );
  progress.setWindowModality(Qt::WindowModal);

  int offset = 0;
  int npckt = 0;
  uint32_t totalTransmittedBytes = 0;
  while( offset < content.size() )
  {
    QByteArray packet;
    for( int ii = 0; ii < 64; ii++ )
    {
      if( offset < content.size() )
        packet.append( content.at(offset) );
      else
        packet.append( (char)0 );
      offset++;
    }
    dsp.sendUserParameterWifi( packet );
    totalTransmittedBytes += packet.size();

    progress.setValue( offset );

    if( progress.wasCanceled() )
      /* \TODO Handle cancel */
      return;

    npckt++;
  }

  progress.setValue( content.size() );

  if( dsp.finishUserParameterWifi( totalTransmittedBytes ) )
    QMessageBox::information( this, tr("Success"), tr("You have successfully stored your settings!"), QMessageBox::Ok );
  else
    QMessageBox::critical( this, tr("Error"), tr("Uups, something went wrong. Please double check everything and try again."), QMessageBox::Ok );  

  qDebug()<<"Success";
  qDebug()<<"File size:"<<content.size() / 1024<<"KiB";
#endif
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
  dspPlugin->setMasterVolume( val );
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
