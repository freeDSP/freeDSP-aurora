#include <QProxyStyle>
#include <QStyleOptionTab>
#include <QLabel>
#include <QVBoxLayout>
#include <QPushButton>
#include <QDialog>

#include "MainWindow.hpp"
#include "ui_MainWindow.h"

#include "DialogSettings.hpp"
#include "QDialogDemoSelector.hpp"

#include "8channels_IC_1_PARAM.h"

#include "PlugIn8Channels.hpp"
#include "PlugInHomeCinema71.hpp"

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

QVolumeSlider* sliderMainVolume;

CPlugIn8Channels plugin8Channels;
CPlugInHomeCinema71 pluginHomeCinema71;

CDspPlugin* dspPlugin;

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  #if defined( __IOS__ ) || defined( __WIN__ )
  ui->menuBar->hide();
  #endif

  //----------------------------------------------------------------------------
  //--- Setup the channel tabs
  //----------------------------------------------------------------------------
  ui->tabChannels->removeTab( 0 );
  QLabel* lbl1;

  #if defined( DEMO )
  setWindowTitle( QString("dspControl DEMO ").append( VERSION_STR ) );

  QStringList itemList( {"8channels", "Home Cinema 7.1"} );
  QDialogDemoSelector dialog( "Please select the plugin for demo: ", itemList );
  if( dialog.exec() == QDialog::Accepted )
  {
    if( dialog.comboBox()->currentText() == QString("8channels") )
    {
      qDebug()<<"Loading plugin 8channels";
      numChannels = plugin8Channels.getNumChannels();
      for( int n = 0; n < numChannels; n++ )
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

        for( int chn = 0; chn < numChannels; chn++ )
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
      for( int n = 0; n < numChannels; n++ )
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

        for( int chn = 0; chn < numChannels; chn++ )
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
    
  }

  #else
  setWindowTitle( "dspControl " + VERSION_STR );
  #endif

  //----------------------------------------------------------------------------
  //--- Init frequency vector
  //----------------------------------------------------------------------------
  tuint n = 0;
  tfloat pointsperdecade = 100.0;
  tfloat fstart = 1.0;
  tfloat fstop = 20000.0;

  for( tfloat k = 1.0; k < 10.0; k = k + 10.0/pointsperdecade )
  {
    if( (k >= fstart) && (k <= fstop) )
      n++;
  }
  for( tfloat k = 10.0; k < 100.0; k = k + 100.0/pointsperdecade )
  {
    if( (k >= fstart) && (k <= fstop) )
      n++;
  }
  for( tfloat k = 100.0; k < 1000.0; k = k + 1000.0/pointsperdecade )
  {
    if( (k >= fstart) && (k <= fstop) )
      n++;
  }
  for( tfloat k = 1000.0; k < 10000.0; k = k + 10000.0/pointsperdecade )
  {
    if( (k >= fstart) && (k <= fstop) )
      n++;
  }
  for( tfloat k = 10000.0; k < 20001.0; k = k + 100000.0/pointsperdecade )
  {
    if( (k >= fstart) && (k <= fstop) )
      n++;
  }

  tvector<tfloat> f( n );
  n = 0;
  for( tfloat k = 1.0; k < 10.0; k = k + 10.0/pointsperdecade )
  {
    if( (k >= fstart) && (k <= fstop) )
    {
      f[n] = k;
      n++;
    }
  }
  for( tfloat k = 10.0; k < 100.0; k = k + 100.0/pointsperdecade )
  {
    if( (k >= fstart) && (k <= fstop) )
    {
      f[n] = k;
      n++;
    }
  }
  for( tfloat k = 100.0; k < 1000.0; k = k + 1000.0/pointsperdecade )
  {
    if( (k >= fstart) && (k <= fstop) ) {
      f[n] = k;
      n++;
    }
  }
  for( tfloat k = 1000.0; k < 10000.0; k = k + 10000.0/pointsperdecade )
  {
    if( (k >= fstart) && (k <= fstop) )
    {
      f[n] = k;
      n++;
    }
  }
  for( tfloat k = 10000.0; k < 20001.0; k = k + 100000.0/pointsperdecade )
  {
    if( (k >= fstart) && (k <= fstop) )
    {
      f[n] = k;
      n++;
    }
  }
  freq = f;
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
      tvector<tcomplex> H = channel->getTransferFunction();
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

      for( int ii = 0; ii < numChannels; ii++ )
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
void MainWindow::on_actionWrite_to_DSP_triggered()
{
  uint32_t numBytes = 0;
  for( int chn = 0; chn < ui->tabChannels->count(); chn++ )
  {
    QChannel* channel = static_cast<QChannel*>(ui->tabChannels->widget(chn));
    if( channel != nullptr )
      numBytes += channel->getNumBytes();
  }

  qDebug()<<numBytes<<"Bytes";
  dsp.beginStoreParams( numBytes );
  for( int chn = 0; chn < ui->tabChannels->count(); chn++ )
  {
    qDebug()<<"Channel"<<chn;
    QChannel* channel = static_cast<QChannel*>(ui->tabChannels->widget(chn));
    if( channel != nullptr )
      channel->writeDspParameter();
  }
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
  DialogSettings dialog;
  dialog.setPortName( portName );
  int result = dialog.exec();
  if( result == QDialog::Accepted )
  {
    #if !defined( DEMO )
    dsp.close();
    dsp.open( dialog.getPortName() );
    #endif
    portName = dialog.getPortName();
    qDebug()<<portName;
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
