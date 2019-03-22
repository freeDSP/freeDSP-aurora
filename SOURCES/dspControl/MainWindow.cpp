#include <QProxyStyle>
#include <QStyleOptionTab>
#include <QLabel>
#include <QVBoxLayout>
#include <QPushButton>
#include <QDialog>
#include <QFileDialog>
#include <QMessageBox>
#include <QtNetwork>
#include <QHostAddress>

#include "MainWindow.hpp"
#include "ui_MainWindow.h"

#include "DialogSettings.hpp"
#include "QDialogDemoSelector.hpp"

//#include "8channels_IC_1_PARAM.h"

#include "PlugIn8Channels.hpp"
#include "PlugInHomeCinema71.hpp"
#include "PlugIn4FIRs.hpp"

#define VERSION_STR "0.9.2"
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

enum tdspluginid
{
  PLUGIN_8CHANNELS    = 0x01,
  PLUGIN_HOMECINEMA71 = 0x02,
  PLUGIN_4FIRS        = 0x03
};

QVolumeSlider* sliderMainVolume;

CPlugIn8Channels plugin8Channels( FS );
CPlugInHomeCinema71 pluginHomeCinema71( FS );
CPlugIn4FIRs plugin4FIRs( FS );

CDspPlugin* dspPlugin;

QTcpSocket* tcpSocket = nullptr;
QString wifiIpHost;
int wifiPortHost;

MainWindow::MainWindow( QWidget* parent ) :
  QMainWindow( parent ),
  ui( new Ui::MainWindow )
{
  ui->setupUi(this);
  #if defined( __IOS__ ) || defined( __WIN__ )
  ui->menuBar->hide();
  #endif
  ui->actionWrite_to_DSP->setEnabled( false );

  //----------------------------------------------------------------------------
  //--- Setup the channel tabs
  //----------------------------------------------------------------------------
  ui->tabChannels->removeTab( 0 );
  QLabel* lbl1;

  #if defined( DEMO )
  setWindowTitle( QString("dspControl DEMO ").append( VERSION_STR ) );

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
  setWindowTitle( QString("dspControl DEMO ").append( VERSION_STR ) );

  tcpSocket = new QTcpSocket(this);
  wifiIpHost = "192.168.5.1";
  wifiPortHost = 8088;
  //ipHost = QString( "192.168.5.1" );
  //connect( tcpSocket, SIGNAL(connected()),                         this, SLOT(connected()) );
  connect( tcpSocket, SIGNAL(disconnected()),                      this, SLOT(disconnected()) );
  connect( tcpSocket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(error(QAbstractSocket::SocketError)) );
  connect( tcpSocket, SIGNAL(hostFound()),                         this, SLOT(hostFound()) );
  connect( tcpSocket, SIGNAL(bytesWritten(qint64)),                this, SLOT(bytesWritten(qint64)) );
  //connect( tcpSocket, SIGNAL(readyRead()),                         this, SLOT(readyRead()) );

  //if( dialog.comboBox()->currentText() == QString("8channels") )
  //{
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

  portName = "/dev/cu.freedsp-aurora-ESP32_SP";
  #if !defined( DEMO )
  dsp.open( "/dev/cu.freedsp-aurora-ESP32_SP" );
  #endif

}

//==============================================================================
/*!
 */
MainWindow::~MainWindow()
{
  dsp.close();
  
  tcpSocket->disconnectFromHost();

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
        if( currentChannel->actionsContextMenu.at(ii)->isChecked() )
        {
          QChannel* channel = static_cast<QChannel*>(ui->tabChannels->widget(ii));
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
  statusWifi = STATUS_WIFI_IDLE;
  
  //--- Connecting to aurora
  qDebug()<<"Connecting to aurora";
  tcpSocket->abort();
  tcpSocket->connectToHost( wifiIpHost, wifiPortHost );

  QEventLoop loopConnect;
  connect( tcpSocket, SIGNAL(connected()), &loopConnect, SLOT(quit()) );
  // \TODO Add timeout timer
  //connect(timeoutTimer, SIGNAL(timeout()), &loop, SLOT(quit()));
  loopConnect.exec();
  qDebug()<<"[OK]";

  //----------------------------------------------------------------------------
  //--- Request the DSP-plugin id
  //----------------------------------------------------------------------------
  wifiRxBytes = 0;
  wifiExpectedBytes = 66;
  wifiReply.clear();
  QString requestString = "GET /pid HTTP/1.1\r\nhost: 192.168.5.1\r\n\r\n";
  QByteArray request;
  request.append( requestString );
  tcpSocket->write( request );

  QEventLoop loopPidRequest;
  connect( this, SIGNAL(replyFinished()), &loopPidRequest, SLOT(quit()) );
  loopPidRequest.exec();
  qDebug()<<QString( wifiReply );
  QStringList listReply = QString( wifiReply ).split( QRegExp("\\s+") );

  bool ok;
  switch( listReply.at(4).toUInt( &ok, 0 ) )
  {
  case PLUGIN_8CHANNELS:
    qDebug()<<"Loading 8channels";
    // \todo Clear GUI and load new GUI
    break;

  default:
    qDebug()<<"Unkown plugin"<<listReply.at(4).toInt( &ok, 0 );
    // \todo Show MessageBox  
  }

  //----------------------------------------------------------------------------
  //--- Request user parameters
  //----------------------------------------------------------------------------
  qDebug()<<"Connecting to aurora";
  tcpSocket->abort();
  tcpSocket->connectToHost( "192.168.5.1", 8088 );
  loopConnect.exec();
  qDebug()<<"[OK]";

  wifiRxBytes = 0;
  wifiExpectedBytes = 0;
  wifiReply.clear();
  statusWifi = STATUS_WIFI_RECEIVE_USERPARAM;
  requestString = "GET /userparams HTTP/1.1\r\nhost: 192.168.5.1\r\n\r\n";
  request.clear();
  request.append( requestString );
  tcpSocket->write( request );

  QEventLoop loopUserParamsRequest;
  connect( this, SIGNAL(replyFinished()), &loopUserParamsRequest, SLOT(quit()) );
  loopUserParamsRequest.exec();
  QString strReply( wifiReply );
  int idx = strReply.indexOf( "\r\n\r\n", Qt::CaseInsensitive );
  QString strContent = strReply.mid( idx+4 );
  strContent = strContent.left( strContent.length()-2 );
  qDebug()<<"strContent"<<strContent;

  QByteArray userParams;
  for( int ii = 0; ii < strContent.length(); ii = ii + 2 )
  {
    QString str;
    str.append( strContent[ii] );
    str.append( strContent[ii+1] );
    userParams.append( static_cast<char>(str.toUInt( &ok, 16 ) & 0xff) );
  }

  qDebug()<<"--- user params ---";
  for( int ii=0; ii < userParams.size(); ii++ )
  {
    unsigned int val = userParams.at(ii);
    qDebug()<<QString::number(val, 16);
  }

  qDebug()<<"--- fill gui elements ---";

  idx = 0;
  for( unsigned int ii = 0; ii < dspPlugin->getNumChannels(); ii++ )
  {
    QChannel* channel = dspPlugin->getChannel( ii );
    for( unsigned int n = 0; n < channel->getNumDspBlocks(); n++ )
    {
      QDspBlock* dspBlock = channel->getDspBlock(n);
      dspBlock->setUserParams( userParams, idx );
    }
  }

  // TODO update plots

  ui->actionWrite_to_DSP->setEnabled( true );
}

//==============================================================================
/*!
 */
void MainWindow::on_actionWrite_to_DSP_triggered()
{
  qDebug()<<"Sending userparam.hex";

  //--- Connecting to aurora
  qDebug()<<"Connecting to aurora";
  tcpSocket->abort();
  tcpSocket->connectToHost( "192.168.5.1", 8088 );

  QEventLoop loopConnect;
  connect( tcpSocket, SIGNAL(connected()), &loopConnect, SLOT(quit()) );
  // \TODO Add timeout timer
  //connect(timeoutTimer, SIGNAL(timeout()), &loop, SLOT(quit()));
  loopConnect.exec();
  qDebug()<<"[OK]";

  //--- Send the user parameters
  QByteArray content;
  for( unsigned int ii = 0; ii < dspPlugin->getNumChannels(); ii++ )
  {
    QChannel* channel = dspPlugin->getChannel( ii );
    for( unsigned int n = 0; n < channel->getNumDspBlocks(); n++ )
    {
      QDspBlock* dspBlock = channel->getDspBlock(n);
      dspBlock->getUserParams( &content );
    }
  }

  qDebug()<<"--- Content ---";
  for( int ii = 0; ii < content.size(); ii++ )
  {
    char val = content.at(ii);
    qDebug()<<QString::number(val, 16);
  }
  qDebug()<<"content.size()"<<content.size();

  QString requestString = QString("PUT /userparams HTTP/1.1\r\nhost: 192.168.5.1\r\nContent-type:application/octet-stream\r\nContent-length: ")
                        + QString::number( content.size() )
                        + QString("\r\n");
  QByteArray request;
  request.append( requestString );
  request.append( content );  
  request.append( "\r\n\r\n" );
  tcpSocket->write( request );


}

//==============================================================================
/*!
 */
void MainWindow::on_actionAbout_triggered()
{
  QPointer<QLabel> label = new QLabel;
  label->setObjectName( "labelAboutText" );
  label->setWordWrap( true );

  label->setText(QString("<p> dspControl") +
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
  dialog.setPortName( portName );
  int result = dialog.exec();
  if( result == QDialog::Accepted )
  {
    /*#if !defined( DEMO )
    dsp.close();
    dsp.open( dialog.getPortName() );
    #endif
    portName = dialog.getPortName();
    qDebug()<<portName;*/
  }
}

//==============================================================================
/*!
 */
void MainWindow::on_volumeSliderMain_valueChanged( double val )
{
  for( int ii = 0; ii < listOutputGains.size(); ii++ )
    listOutputGains.at(ii)->sendDspParameter();
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
//void MainWindow::connected( void )
//{
  //qDebug()<<"Connected to server";

  //Ask for the web page.
  /*
    GET /index.html HTTP/1.1[CRLF]
    HOST : www.host.com[CRLF]
    * */

  //QString requestString ="GET /index.html HTTP/1.1\r\nhost: 192.168.5.1\r\n\r\n";
  //QString requestString ="GET /pid HTTP/1.1\r\nhost: 192.168.5.1\r\n\r\n";

  //QByteArray request;
  //request.append( requestString );
  //tcpSocket->write( request );
  

  //QNetworkRequest request( QUrl("192.168.5.1:8088") );
  //request.setHeader( QNetworkRequest::ContentTypeHeader, "application/json" );

  /*
  QJsonObject json;
  json.insert( "item1", "value1" );
  QNetworkAccessManager nam;
  QNetworkReply *reply = nam.post(request, QJsonDocument(json).toJson());

  while(!reply->isFinished())
  {
    qApp->processEvents();
  }

  QByteArray response_data = reply->readAll();
  QJsonDocument jsonResponse = QJsonDocument::fromJson(response_data);
  reply->deleteLater();
 */ 
//}

//==============================================================================
/*!
 */
void MainWindow::disconnected( void )
{
  qDebug()<<"Disconnected from server";
}

//==============================================================================
/*!
 */
void MainWindow::error( QAbstractSocket::SocketError socketError )
{
  QString errorStr = tcpSocket->errorString();
  qDebug()<<"An error occured :"<<errorStr;
}

//==============================================================================
/*!
 */
void MainWindow::hostFound( void )
{
  qDebug()<<"Host found";
}

//==============================================================================
/*!
 */
void MainWindow::bytesWritten( qint64 bytes )
{
  QString outString = QString::number(bytes) + " bytes writen.";
  qDebug()<<outString;
}

//==============================================================================
/*!
 */
void MainWindow::readyRead( void )
{
  qDebug()<<"readyRead "<<tcpSocket->bytesAvailable()<<wifiRxBytes;
  if( statusWifi == STATUS_WIFI_RECEIVE_USERPARAM )
  {
    wifiRxBytes += tcpSocket->bytesAvailable();
    wifiReply.append( tcpSocket->readAll() );
    QString strReply( wifiReply );
    if( strReply.contains( "\r\n\r\n", Qt::CaseInsensitive ) && wifiExpectedBytes == 0  )
    {
      qDebug()<<"1"<<strReply;
      int idx = strReply.indexOf( "\r\n\r\n", Qt::CaseInsensitive );
      QString strHead = strReply.left( idx );
      qDebug()<<"strHead"<<strHead;
      idx = strHead.indexOf( "Content-length", Qt::CaseInsensitive );
      QString strContentLength = strHead.right( strHead.length() - idx - 15 );
      int contentLength = strContentLength.toInt();
      qDebug()<<"strContentLength"<<contentLength;
      qDebug()<<"strHead.length()"<<strHead.length();
      wifiExpectedBytes = strHead.length() + 4 + contentLength + 2;
      qDebug()<<wifiExpectedBytes<<strReply.length();
      if( wifiRxBytes == wifiExpectedBytes )
      {
        qDebug()<<"emit replyFinished();";
        statusWifi = STATUS_WIFI_IDLE;
        emit replyFinished();
      }
    
    }
    else if ( wifiRxBytes <= wifiExpectedBytes  )
    {
      qDebug()<<"2"<<QString( wifiReply );
      if( wifiRxBytes == wifiExpectedBytes )
      {
        qDebug()<<"emit replyFinished();";
        statusWifi = STATUS_WIFI_IDLE;
        emit replyFinished();
      }
    }
  }
  else
  {
    wifiRxBytes += tcpSocket->bytesAvailable();
    wifiReply.append( tcpSocket->readAll() );
    if( wifiRxBytes == wifiExpectedBytes )
      emit replyFinished();
  }
}
