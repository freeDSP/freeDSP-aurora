#include <QProxyStyle>
#include <QStyleOptionTab>
#include <QLabel>
#include <QVBoxLayout>
#include <QPushButton>
#include <QDialog>

#include "MainWindow.hpp"
#include "ui_MainWindow.h"

#include "DialogSettings.hpp"

#include "8channels_IC_1_PARAM.h"

#define VERSION_STR "0.9.1"
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

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  #if defined( __IOS__ ) || defined( __WIN__ )
  ui->menuBar->hide();
  #endif

  #if defined( DEMO )
  setWindowTitle( QString("dspControl DEMO ").append( VERSION_STR ) );
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

  numChannels = 8;

  //----------------------------------------------------------------------------
  //--- Setup the channel tabs
  //----------------------------------------------------------------------------
  ui->tabChannels->removeTab( 0 );

  int chn;
  QChannel* channel;
  QHBoxLayout* layout;
  QLabel* lbl1;

  QInputSelect* input;
  QHighPass* hp;
  QLowShelv* lshelv;
  QPeq* peq;
  QHighShelv* hshelv;
  QLowPass* lp;
  QPhase* phase;
  QDelay* dly;
  QGain* gain;

  tvector<tcomplex> H;

  //----------------------------------------------------------------------------
  //--- Channel 1
  chn = 0;
  channel = new QChannel;
  ui->tabChannels->addTab( channel, "" );
  lbl1 = new QLabel();
  lbl1->setText( "  Channel " + QString::number( chn+1 ) );
  lbl1->setStyleSheet( QString("background-color: transparent; border: 0px solid black; border-left: 2px solid ") + colorPlot[chn%kMaxPlotColors].name() + QString("; color: white; ") );
  ui->tabChannels->tabBar()->setTabButton( chn, QTabBar::LeftSide, lbl1 );

  layout = new QHBoxLayout;

  input = new QInputSelect( 0, MOD_NX1_1_1_MONOMUXSIGMA300NS1INDEX_ADDR, &dsp );
  layout->addWidget( input );
  channel->addDspBlock( input );

  hp = new QHighPass( QHighPass::kLinkwitzRiley12, 100.0,
                      MOD_HP1_1_ALG0_STAGE0_B2_ADDR, MOD_HP1_1_ALG0_STAGE0_B1_ADDR, MOD_HP1_1_ALG0_STAGE0_B0_ADDR,
                      MOD_HP1_1_ALG0_STAGE0_A2_ADDR, MOD_HP1_1_ALG0_STAGE0_A1_ADDR,
                      MOD_HP1_2_ALG0_STAGE0_B2_ADDR, MOD_HP1_2_ALG0_STAGE0_B1_ADDR, MOD_HP1_2_ALG0_STAGE0_B0_ADDR,
                      MOD_HP1_2_ALG0_STAGE0_A2_ADDR, MOD_HP1_2_ALG0_STAGE0_A1_ADDR,
                      MOD_HP1_3_ALG0_STAGE0_B2_ADDR, MOD_HP1_3_ALG0_STAGE0_B1_ADDR, MOD_HP1_3_ALG0_STAGE0_B0_ADDR,
                      MOD_HP1_3_ALG0_STAGE0_A2_ADDR, MOD_HP1_3_ALG0_STAGE0_A1_ADDR,
                      MOD_HP1_4_ALG0_STAGE0_B2_ADDR, MOD_HP1_4_ALG0_STAGE0_B1_ADDR, MOD_HP1_4_ALG0_STAGE0_B0_ADDR,
                      MOD_HP1_4_ALG0_STAGE0_A2_ADDR, MOD_HP1_4_ALG0_STAGE0_A1_ADDR,
                      FS,
                      &dsp );
  layout->addWidget( hp );
  channel->addDspBlock( hp );
  connect( hp, SIGNAL(valueChanged()), this, SLOT(updatePlots()) );

  lshelv = new QLowShelv( 6.0, 100.0, 1.0,
                          MOD_LOWSHELV1_ALG0_STAGE0_B2_ADDR, MOD_LOWSHELV1_ALG0_STAGE0_B1_ADDR, MOD_LOWSHELV1_ALG0_STAGE0_B0_ADDR,
                          MOD_LOWSHELV1_ALG0_STAGE0_A2_ADDR, MOD_LOWSHELV1_ALG0_STAGE0_A1_ADDR,
                          FS,
                          &dsp );
  layout->addWidget( lshelv );
  channel->addDspBlock( lshelv );
  connect( lshelv, SIGNAL(valueChanged()), this, SLOT(updatePlots()) );

  peq = new QPeq( 6.0, 1000.0, 1.0,
                  MOD_PARAMEQ1_ALG0_STAGE0_B2_ADDR, MOD_PARAMEQ1_ALG0_STAGE0_B1_ADDR, MOD_PARAMEQ1_ALG0_STAGE0_B0_ADDR,
                  MOD_PARAMEQ1_ALG0_STAGE0_A2_ADDR, MOD_PARAMEQ1_ALG0_STAGE0_A1_ADDR,
                  FS,
                  &dsp );
  layout->addWidget( peq );
  channel->addDspBlock( peq );
  connect( peq, SIGNAL(valueChanged()), this, SLOT(updatePlots()) );

  peq = new QPeq( -6.0, 2000.0, 2.0,
                  MOD_PARAMEQ1_ALG0_STAGE1_B2_ADDR, MOD_PARAMEQ1_ALG0_STAGE1_B1_ADDR, MOD_PARAMEQ1_ALG0_STAGE1_B0_ADDR,
                  MOD_PARAMEQ1_ALG0_STAGE1_A2_ADDR, MOD_PARAMEQ1_ALG0_STAGE1_A1_ADDR,
                  FS,
                  &dsp );
  layout->addWidget( peq );
  channel->addDspBlock( peq );
  connect( peq, SIGNAL(valueChanged()), this, SLOT(updatePlots()) );

  peq = new QPeq( 6.0, 3000.0, 2.0,
                  MOD_PARAMEQ1_ALG0_STAGE2_B2_ADDR, MOD_PARAMEQ1_ALG0_STAGE2_B1_ADDR, MOD_PARAMEQ1_ALG0_STAGE2_B0_ADDR,
                  MOD_PARAMEQ1_ALG0_STAGE2_A2_ADDR, MOD_PARAMEQ1_ALG0_STAGE2_A1_ADDR,
                  FS,
                  &dsp );
  layout->addWidget( peq );
  channel->addDspBlock( peq );
  connect( peq, SIGNAL(valueChanged()), this, SLOT(updatePlots()) );

  peq = new QPeq( -6.0, 4000.0, 2.0,
                  MOD_PARAMEQ1_ALG0_STAGE3_B2_ADDR, MOD_PARAMEQ1_ALG0_STAGE3_B1_ADDR, MOD_PARAMEQ1_ALG0_STAGE3_B0_ADDR,
                  MOD_PARAMEQ1_ALG0_STAGE3_A2_ADDR, MOD_PARAMEQ1_ALG0_STAGE3_A1_ADDR,
                  FS,
                  &dsp );
  layout->addWidget( peq );
  channel->addDspBlock( peq );
  connect( peq, SIGNAL(valueChanged()), this, SLOT(updatePlots()) );

  peq = new QPeq( 6.0, 5000.0, 2.0,
                  MOD_PARAMEQ1_ALG0_STAGE4_B2_ADDR, MOD_PARAMEQ1_ALG0_STAGE4_B1_ADDR, MOD_PARAMEQ1_ALG0_STAGE4_B0_ADDR,
                  MOD_PARAMEQ1_ALG0_STAGE4_A2_ADDR, MOD_PARAMEQ1_ALG0_STAGE4_A1_ADDR,
                  FS,
                  &dsp );
  layout->addWidget( peq );
  channel->addDspBlock( peq );
  connect( peq, SIGNAL(valueChanged()), this, SLOT(updatePlots()) );

  peq = new QPeq( -6.0, 6000.0, 2.0,
                  MOD_PARAMEQ1_ALG0_STAGE5_B2_ADDR, MOD_PARAMEQ1_ALG0_STAGE5_B1_ADDR, MOD_PARAMEQ1_ALG0_STAGE5_B0_ADDR,
                  MOD_PARAMEQ1_ALG0_STAGE5_A2_ADDR, MOD_PARAMEQ1_ALG0_STAGE5_A1_ADDR,
                  FS,
                  &dsp );
  layout->addWidget( peq );
  channel->addDspBlock( peq );
  connect( peq, SIGNAL(valueChanged()), this, SLOT(updatePlots()) );

  peq = new QPeq( 6.0, 7000.0, 2.0,
                  MOD_PARAMEQ1_ALG0_STAGE6_B2_ADDR, MOD_PARAMEQ1_ALG0_STAGE6_B1_ADDR, MOD_PARAMEQ1_ALG0_STAGE6_B0_ADDR,
                  MOD_PARAMEQ1_ALG0_STAGE6_A2_ADDR, MOD_PARAMEQ1_ALG0_STAGE6_A1_ADDR,
                  FS,
                  &dsp );
  layout->addWidget( peq );
  channel->addDspBlock( peq );
  connect( peq, SIGNAL(valueChanged()), this, SLOT(updatePlots()) );

  peq = new QPeq( -6.0, 8000.0, 2.0,
                  MOD_PARAMEQ1_ALG0_STAGE7_B2_ADDR, MOD_PARAMEQ1_ALG0_STAGE7_B1_ADDR, MOD_PARAMEQ1_ALG0_STAGE7_B0_ADDR,
                  MOD_PARAMEQ1_ALG0_STAGE7_A2_ADDR, MOD_PARAMEQ1_ALG0_STAGE7_A1_ADDR,
                  FS,
                  &dsp );
  layout->addWidget( peq );
  channel->addDspBlock( peq );
  connect( peq, SIGNAL(valueChanged()), this, SLOT(updatePlots()) );

  peq = new QPeq( 6.0, 9000.0, 2.0,
                  MOD_PARAMEQ1_ALG0_STAGE8_B2_ADDR, MOD_PARAMEQ1_ALG0_STAGE8_B1_ADDR, MOD_PARAMEQ1_ALG0_STAGE8_B0_ADDR,
                  MOD_PARAMEQ1_ALG0_STAGE8_A2_ADDR, MOD_PARAMEQ1_ALG0_STAGE8_A1_ADDR,
                  FS,
                  &dsp );
  layout->addWidget( peq );
  channel->addDspBlock( peq );
  connect( peq, SIGNAL(valueChanged()), this, SLOT(updatePlots()) );

  peq = new QPeq( -6.0, 10000.0, 2.0,
                  MOD_PARAMEQ1_ALG0_STAGE9_B2_ADDR, MOD_PARAMEQ1_ALG0_STAGE9_B1_ADDR, MOD_PARAMEQ1_ALG0_STAGE9_B0_ADDR,
                  MOD_PARAMEQ1_ALG0_STAGE9_A2_ADDR, MOD_PARAMEQ1_ALG0_STAGE9_A1_ADDR,
                  FS,
                  &dsp );
  layout->addWidget( peq );
  channel->addDspBlock( peq );
  connect( peq, SIGNAL(valueChanged()), this, SLOT(updatePlots()) );

  hshelv = new QHighShelv( 6.0, 5000.0, 1.0,
                           MOD_HIGHSHELV1_ALG0_STAGE0_B2_ADDR, MOD_HIGHSHELV1_ALG0_STAGE0_B1_ADDR, MOD_HIGHSHELV1_ALG0_STAGE0_B0_ADDR,
                           MOD_HIGHSHELV1_ALG0_STAGE0_A2_ADDR, MOD_HIGHSHELV1_ALG0_STAGE0_A1_ADDR,
                           FS,
                           &dsp );
  layout->addWidget( hshelv );
  channel->addDspBlock( hshelv );
  connect( hshelv, SIGNAL(valueChanged()), this, SLOT(updatePlots()) );

  lp = new QLowPass( QLowPass::kLinkwitzRiley12, 10000.0,
                     MOD_LP1_1_ALG0_STAGE0_B2_ADDR, MOD_LP1_1_ALG0_STAGE0_B1_ADDR, MOD_LP1_1_ALG0_STAGE0_B0_ADDR,
                     MOD_LP1_1_ALG0_STAGE0_A2_ADDR, MOD_LP1_1_ALG0_STAGE0_A1_ADDR,
                     MOD_LP1_2_ALG0_STAGE0_B2_ADDR, MOD_LP1_2_ALG0_STAGE0_B1_ADDR, MOD_LP1_2_ALG0_STAGE0_B0_ADDR,
                     MOD_LP1_2_ALG0_STAGE0_A2_ADDR, MOD_LP1_2_ALG0_STAGE0_A1_ADDR,
                     MOD_LP1_3_ALG0_STAGE0_B2_ADDR, MOD_LP1_3_ALG0_STAGE0_B1_ADDR, MOD_LP1_3_ALG0_STAGE0_B0_ADDR,
                     MOD_LP1_3_ALG0_STAGE0_A2_ADDR, MOD_LP1_3_ALG0_STAGE0_A1_ADDR,
                     MOD_LP1_4_ALG0_STAGE0_B2_ADDR, MOD_LP1_4_ALG0_STAGE0_B1_ADDR, MOD_LP1_4_ALG0_STAGE0_B0_ADDR,
                     MOD_LP1_4_ALG0_STAGE0_A2_ADDR, MOD_LP1_4_ALG0_STAGE0_A1_ADDR,
                     FS,
                     &dsp );
  layout->addWidget( lp );
  channel->addDspBlock( lp );
  connect( lp, SIGNAL(valueChanged()), this, SLOT(updatePlots()) );

  phase = new QPhase( 1000.0, 1.0,
                      MOD_PHASE1_ALG0_STAGE0_B2_ADDR, MOD_PHASE1_ALG0_STAGE0_B1_ADDR, MOD_PHASE1_ALG0_STAGE0_B0_ADDR,
                      MOD_PHASE1_ALG0_STAGE0_A2_ADDR, MOD_PHASE1_ALG0_STAGE0_A1_ADDR,
                      FS,
                      &dsp );
  layout->addWidget( phase );
  channel->addDspBlock( phase );
  connect( phase, SIGNAL(valueChanged()), this, SLOT(updatePlots()) );

  dly = new QDelay( 0.0, 48000.0, MOD_DELAY1_DELAYAMT_ADDR, &dsp );
  layout->addWidget( dly );
  channel->addDspBlock( dly );
  connect( dly, SIGNAL(valueChanged()), this, SLOT(updatePlots()) );

  gain = new QGain( 0.0, MOD_GAIN1_ALG0_TARGET_ADDR, &dsp );
  layout->addWidget( gain );
  channel->addDspBlock( gain );
  connect( gain, SIGNAL(valueChanged()), this, SLOT(updatePlots()) );
  listOutputGains.append( gain );

  layout->setSpacing( 0 );
  layout->setMargin( 0 );
  layout->setContentsMargins( 0, 0, 0, 0 );
  layout->setAlignment( Qt::AlignLeft );

  channel->widgetChannel->setLayout( layout );

  for( int chn = 0; chn < numChannels; chn++ )
  {
    QAction* action = new QAction( "Show Channel " + QString::number(chn+1) );
    action->setCheckable( true );
    channel->actionsContextMenu.append( action );
    channel->contextMenu.addAction( action );
  }
  channel->actionsContextMenu.at(chn)->setChecked( true );
  connect( channel, SIGNAL(selectionChanged()), this, SLOT(updatePlots()) );

  //----------------------------------------------------------------------------
  //--- Channel 2
  chn = 1;
  channel = new QChannel;
  ui->tabChannels->addTab( channel, "" );
  lbl1 = new QLabel();
  lbl1->setText( "  Channel " + QString::number( chn+1 ) );
  lbl1->setStyleSheet( QString("background-color: transparent; border: 0px solid black; border-left: 2px solid ") + colorPlot[chn%kMaxPlotColors].name() + QString("; color: white; ") );
  ui->tabChannels->tabBar()->setTabButton( chn, QTabBar::LeftSide, lbl1 );

  layout = new QHBoxLayout;

  input = new QInputSelect( 1, MOD_NX1_1_2_MONOMUXSIGMA300NS2INDEX_ADDR, &dsp );
  layout->addWidget( input );
  channel->addDspBlock( input );

  hp = new QHighPass( QHighPass::kLinkwitzRiley12, 100.0,
                      MOD_HP2_1_ALG0_STAGE0_B2_ADDR, MOD_HP2_1_ALG0_STAGE0_B1_ADDR, MOD_HP2_1_ALG0_STAGE0_B0_ADDR,
                      MOD_HP2_1_ALG0_STAGE0_A2_ADDR, MOD_HP2_1_ALG0_STAGE0_A1_ADDR,
                      MOD_HP2_2_ALG0_STAGE0_B2_ADDR, MOD_HP2_2_ALG0_STAGE0_B1_ADDR, MOD_HP2_2_ALG0_STAGE0_B0_ADDR,
                      MOD_HP2_2_ALG0_STAGE0_A2_ADDR, MOD_HP2_2_ALG0_STAGE0_A1_ADDR,
                      MOD_HP2_3_ALG0_STAGE0_B2_ADDR, MOD_HP2_3_ALG0_STAGE0_B1_ADDR, MOD_HP2_3_ALG0_STAGE0_B0_ADDR,
                      MOD_HP2_3_ALG0_STAGE0_A2_ADDR, MOD_HP2_3_ALG0_STAGE0_A1_ADDR,
                      MOD_HP2_4_ALG0_STAGE0_B2_ADDR, MOD_HP2_4_ALG0_STAGE0_B1_ADDR, MOD_HP2_4_ALG0_STAGE0_B0_ADDR,
                      MOD_HP2_4_ALG0_STAGE0_A2_ADDR, MOD_HP2_4_ALG0_STAGE0_A1_ADDR,
                      FS,
                      &dsp );
  layout->addWidget( hp );
  channel->addDspBlock( hp );
  connect( hp, SIGNAL(valueChanged()), this, SLOT(updatePlots()) );

  lshelv = new QLowShelv( 6.0, 100.0, 1.0,
                          MOD_LOWSHELV2_ALG0_STAGE0_B2_ADDR, MOD_LOWSHELV2_ALG0_STAGE0_B1_ADDR, MOD_LOWSHELV2_ALG0_STAGE0_B0_ADDR,
                          MOD_LOWSHELV2_ALG0_STAGE0_A2_ADDR, MOD_LOWSHELV2_ALG0_STAGE0_A1_ADDR,
                          FS,
                          &dsp );
  layout->addWidget( lshelv );
  channel->addDspBlock( lshelv );
  connect( lshelv, SIGNAL(valueChanged()), this, SLOT(updatePlots()) );

  peq = new QPeq( 6.0, 1000.0, 1.0,
                  MOD_PARAMEQ2_ALG0_STAGE0_B2_ADDR, MOD_PARAMEQ2_ALG0_STAGE0_B1_ADDR, MOD_PARAMEQ2_ALG0_STAGE0_B0_ADDR,
                  MOD_PARAMEQ2_ALG0_STAGE0_A2_ADDR, MOD_PARAMEQ2_ALG0_STAGE0_A1_ADDR,
                  FS,
                  &dsp );
  layout->addWidget( peq );
  channel->addDspBlock( peq );
  connect( peq, SIGNAL(valueChanged()), this, SLOT(updatePlots()) );

  peq = new QPeq( -6.0, 2000.0, 2.0,
                  MOD_PARAMEQ2_ALG0_STAGE1_B2_ADDR, MOD_PARAMEQ2_ALG0_STAGE1_B1_ADDR, MOD_PARAMEQ2_ALG0_STAGE1_B0_ADDR,
                  MOD_PARAMEQ2_ALG0_STAGE1_A2_ADDR, MOD_PARAMEQ2_ALG0_STAGE1_A1_ADDR,
                  FS,
                  &dsp );
  layout->addWidget( peq );
  channel->addDspBlock( peq );
  connect( peq, SIGNAL(valueChanged()), this, SLOT(updatePlots()) );

  peq = new QPeq( 6.0, 3000.0, 2.0,
                  MOD_PARAMEQ2_ALG0_STAGE2_B2_ADDR, MOD_PARAMEQ2_ALG0_STAGE2_B1_ADDR, MOD_PARAMEQ2_ALG0_STAGE2_B0_ADDR,
                  MOD_PARAMEQ2_ALG0_STAGE2_A2_ADDR, MOD_PARAMEQ2_ALG0_STAGE2_A1_ADDR,
                  FS,
                  &dsp );
  layout->addWidget( peq );
  channel->addDspBlock( peq );
  connect( peq, SIGNAL(valueChanged()), this, SLOT(updatePlots()) );

  peq = new QPeq( -6.0, 4000.0, 2.0,
                  MOD_PARAMEQ2_ALG0_STAGE3_B2_ADDR, MOD_PARAMEQ2_ALG0_STAGE3_B1_ADDR, MOD_PARAMEQ2_ALG0_STAGE3_B0_ADDR,
                  MOD_PARAMEQ2_ALG0_STAGE3_A2_ADDR, MOD_PARAMEQ2_ALG0_STAGE3_A1_ADDR,
                  FS,
                  &dsp );
  layout->addWidget( peq );
  channel->addDspBlock( peq );
  connect( peq, SIGNAL(valueChanged()), this, SLOT(updatePlots()) );

  peq = new QPeq( 6.0, 5000.0, 2.0,
                  MOD_PARAMEQ2_ALG0_STAGE4_B2_ADDR, MOD_PARAMEQ2_ALG0_STAGE4_B1_ADDR, MOD_PARAMEQ2_ALG0_STAGE4_B0_ADDR,
                  MOD_PARAMEQ2_ALG0_STAGE4_A2_ADDR, MOD_PARAMEQ2_ALG0_STAGE4_A1_ADDR,
                  FS,
                  &dsp );
  layout->addWidget( peq );
  channel->addDspBlock( peq );
  connect( peq, SIGNAL(valueChanged()), this, SLOT(updatePlots()) );

  peq = new QPeq( -6.0, 6000.0, 2.0,
                  MOD_PARAMEQ2_ALG0_STAGE5_B2_ADDR, MOD_PARAMEQ2_ALG0_STAGE5_B1_ADDR, MOD_PARAMEQ2_ALG0_STAGE5_B0_ADDR,
                  MOD_PARAMEQ2_ALG0_STAGE5_A2_ADDR, MOD_PARAMEQ2_ALG0_STAGE5_A1_ADDR,
                  FS,
                  &dsp );
  layout->addWidget( peq );
  channel->addDspBlock( peq );
  connect( peq, SIGNAL(valueChanged()), this, SLOT(updatePlots()) );

  peq = new QPeq( 6.0, 7000.0, 2.0,
                  MOD_PARAMEQ2_ALG0_STAGE6_B2_ADDR, MOD_PARAMEQ2_ALG0_STAGE6_B1_ADDR, MOD_PARAMEQ2_ALG0_STAGE6_B0_ADDR,
                  MOD_PARAMEQ2_ALG0_STAGE6_A2_ADDR, MOD_PARAMEQ2_ALG0_STAGE6_A1_ADDR,
                  FS,
                  &dsp );
  layout->addWidget( peq );
  channel->addDspBlock( peq );
  connect( peq, SIGNAL(valueChanged()), this, SLOT(updatePlots()) );

  peq = new QPeq( -6.0, 8000.0, 2.0,
                  MOD_PARAMEQ2_ALG0_STAGE7_B2_ADDR, MOD_PARAMEQ2_ALG0_STAGE7_B1_ADDR, MOD_PARAMEQ2_ALG0_STAGE7_B0_ADDR,
                  MOD_PARAMEQ2_ALG0_STAGE7_A2_ADDR, MOD_PARAMEQ2_ALG0_STAGE7_A1_ADDR,
                  FS,
                  &dsp );
  layout->addWidget( peq );
  channel->addDspBlock( peq );
  connect( peq, SIGNAL(valueChanged()), this, SLOT(updatePlots()) );

  peq = new QPeq( 6.0, 9000.0, 2.0,
                  MOD_PARAMEQ2_ALG0_STAGE8_B2_ADDR, MOD_PARAMEQ2_ALG0_STAGE8_B1_ADDR, MOD_PARAMEQ2_ALG0_STAGE8_B0_ADDR,
                  MOD_PARAMEQ2_ALG0_STAGE8_A2_ADDR, MOD_PARAMEQ2_ALG0_STAGE8_A1_ADDR,
                  FS,
                  &dsp );
  layout->addWidget( peq );
  channel->addDspBlock( peq );
  connect( peq, SIGNAL(valueChanged()), this, SLOT(updatePlots()) );

  peq = new QPeq( -6.0, 10000.0, 2.0,
                  MOD_PARAMEQ2_ALG0_STAGE9_B2_ADDR, MOD_PARAMEQ2_ALG0_STAGE9_B1_ADDR, MOD_PARAMEQ2_ALG0_STAGE9_B0_ADDR,
                  MOD_PARAMEQ2_ALG0_STAGE9_A2_ADDR, MOD_PARAMEQ2_ALG0_STAGE9_A1_ADDR,
                  FS,
                  &dsp );
  layout->addWidget( peq );
  channel->addDspBlock( peq );
  connect( peq, SIGNAL(valueChanged()), this, SLOT(updatePlots()) );

  hshelv = new QHighShelv( 6.0, 5000.0, 1.0,
                           MOD_HIGHSHELV2_ALG0_STAGE0_B2_ADDR, MOD_HIGHSHELV2_ALG0_STAGE0_B1_ADDR, MOD_HIGHSHELV2_ALG0_STAGE0_B0_ADDR,
                           MOD_HIGHSHELV2_ALG0_STAGE0_A2_ADDR, MOD_HIGHSHELV2_ALG0_STAGE0_A1_ADDR,
                           FS,
                           &dsp );
  layout->addWidget( hshelv );
  channel->addDspBlock( hshelv );
  connect( hshelv, SIGNAL(valueChanged()), this, SLOT(updatePlots()) );

  lp = new QLowPass( QLowPass::kLinkwitzRiley12, 10000.0,
                     MOD_LP2_1_ALG0_STAGE0_B2_ADDR, MOD_LP2_1_ALG0_STAGE0_B1_ADDR, MOD_LP2_1_ALG0_STAGE0_B0_ADDR,
                     MOD_LP2_1_ALG0_STAGE0_A2_ADDR, MOD_LP2_1_ALG0_STAGE0_A1_ADDR,
                     MOD_LP2_2_ALG0_STAGE0_B2_ADDR, MOD_LP2_2_ALG0_STAGE0_B1_ADDR, MOD_LP2_2_ALG0_STAGE0_B0_ADDR,
                     MOD_LP2_2_ALG0_STAGE0_A2_ADDR, MOD_LP2_2_ALG0_STAGE0_A1_ADDR,
                     MOD_LP2_3_ALG0_STAGE0_B2_ADDR, MOD_LP2_3_ALG0_STAGE0_B1_ADDR, MOD_LP2_3_ALG0_STAGE0_B0_ADDR,
                     MOD_LP2_3_ALG0_STAGE0_A2_ADDR, MOD_LP2_3_ALG0_STAGE0_A1_ADDR,
                     MOD_LP2_4_ALG0_STAGE0_B2_ADDR, MOD_LP2_4_ALG0_STAGE0_B1_ADDR, MOD_LP2_4_ALG0_STAGE0_B0_ADDR,
                     MOD_LP2_4_ALG0_STAGE0_A2_ADDR, MOD_LP2_4_ALG0_STAGE0_A1_ADDR,
                     FS,
                     &dsp );
  layout->addWidget( lp );
  channel->addDspBlock( lp );
  connect( lp, SIGNAL(valueChanged()), this, SLOT(updatePlots()) );

  phase = new QPhase( 1000.0, 1.0,
                      MOD_PHASE2_ALG0_STAGE0_B2_ADDR, MOD_PHASE2_ALG0_STAGE0_B1_ADDR, MOD_PHASE2_ALG0_STAGE0_B0_ADDR,
                      MOD_PHASE2_ALG0_STAGE0_A2_ADDR, MOD_PHASE2_ALG0_STAGE0_A1_ADDR,
                      FS,
                      &dsp );
  layout->addWidget( phase );
  channel->addDspBlock( phase );
  connect( phase, SIGNAL(valueChanged()), this, SLOT(updatePlots()) );

  dly = new QDelay( 0.0, 48000.0, MOD_DELAY2_DELAYAMT_ADDR, &dsp );
  layout->addWidget( dly );
  channel->addDspBlock( dly );
  connect( dly, SIGNAL(valueChanged()), this, SLOT(updatePlots()) );

  gain = new QGain( 0.0, MOD_GAIN2_ALG0_TARGET_ADDR, &dsp );
  layout->addWidget( gain );
  channel->addDspBlock( gain );
  connect( gain, SIGNAL(valueChanged()), this, SLOT(updatePlots()) );
  listOutputGains.append( gain );

  layout->setSpacing( 0 );
  layout->setMargin( 0 );
  layout->setContentsMargins( 0, 0, 0, 0 );
  layout->setAlignment( Qt::AlignLeft );

  channel->widgetChannel->setLayout( layout );

  for( int chn = 0; chn < numChannels; chn++ )
  {
    QAction* action = new QAction( "Show Channel " + QString::number(chn+1) );
    action->setCheckable( true );
    channel->actionsContextMenu.append( action );
    channel->contextMenu.addAction( action );
  }
  channel->actionsContextMenu.at(chn)->setChecked( true );
  connect( channel, SIGNAL(selectionChanged()), this, SLOT(updatePlots()) );

  //----------------------------------------------------------------------------
  //--- Channel 3
  chn = 2;
  channel = new QChannel;
  ui->tabChannels->addTab( channel, "" );
  lbl1 = new QLabel();
  lbl1->setText( "  Channel " + QString::number( chn+1 ) );
  lbl1->setStyleSheet( QString("background-color: transparent; border: 0px solid black; border-left: 2px solid ") + colorPlot[chn%kMaxPlotColors].name() + QString("; color: white; ") );
  ui->tabChannels->tabBar()->setTabButton( chn, QTabBar::LeftSide, lbl1 );

  layout = new QHBoxLayout;

  input = new QInputSelect( 2, MOD_NX1_1_3_MONOMUXSIGMA300NS3INDEX_ADDR, &dsp );
  layout->addWidget( input );
  channel->addDspBlock( input );

  hp = new QHighPass( QHighPass::kLinkwitzRiley12, 100.0,
                      MOD_HP3_1_ALG0_STAGE0_B2_ADDR, MOD_HP3_1_ALG0_STAGE0_B1_ADDR, MOD_HP3_1_ALG0_STAGE0_B0_ADDR,
                      MOD_HP3_1_ALG0_STAGE0_A2_ADDR, MOD_HP3_1_ALG0_STAGE0_A1_ADDR,
                      MOD_HP3_2_ALG0_STAGE0_B2_ADDR, MOD_HP3_2_ALG0_STAGE0_B1_ADDR, MOD_HP3_2_ALG0_STAGE0_B0_ADDR,
                      MOD_HP3_2_ALG0_STAGE0_A2_ADDR, MOD_HP3_2_ALG0_STAGE0_A1_ADDR,
                      MOD_HP3_3_ALG0_STAGE0_B2_ADDR, MOD_HP3_3_ALG0_STAGE0_B1_ADDR, MOD_HP3_3_ALG0_STAGE0_B0_ADDR,
                      MOD_HP3_3_ALG0_STAGE0_A2_ADDR, MOD_HP3_3_ALG0_STAGE0_A1_ADDR,
                      MOD_HP3_4_ALG0_STAGE0_B2_ADDR, MOD_HP3_4_ALG0_STAGE0_B1_ADDR, MOD_HP3_4_ALG0_STAGE0_B0_ADDR,
                      MOD_HP3_4_ALG0_STAGE0_A2_ADDR, MOD_HP3_4_ALG0_STAGE0_A1_ADDR,
                      FS,
                      &dsp );
  layout->addWidget( hp );
  channel->addDspBlock( hp );
  connect( hp, SIGNAL(valueChanged()), this, SLOT(updatePlots()) );

  lshelv = new QLowShelv( 6.0, 100.0, 1.0,
                          MOD_LOWSHELV3_ALG0_STAGE0_B2_ADDR, MOD_LOWSHELV3_ALG0_STAGE0_B1_ADDR, MOD_LOWSHELV3_ALG0_STAGE0_B0_ADDR,
                          MOD_LOWSHELV3_ALG0_STAGE0_A2_ADDR, MOD_LOWSHELV3_ALG0_STAGE0_A1_ADDR,
                          FS,
                          &dsp );
  layout->addWidget( lshelv );
  channel->addDspBlock( lshelv );
  connect( lshelv, SIGNAL(valueChanged()), this, SLOT(updatePlots()) );

  peq = new QPeq( 6.0, 1000.0, 1.0,
                  MOD_PARAMEQ3_ALG0_STAGE0_B2_ADDR, MOD_PARAMEQ3_ALG0_STAGE0_B1_ADDR, MOD_PARAMEQ3_ALG0_STAGE0_B0_ADDR,
                  MOD_PARAMEQ3_ALG0_STAGE0_A2_ADDR, MOD_PARAMEQ3_ALG0_STAGE0_A1_ADDR,
                  FS,
                  &dsp );
  layout->addWidget( peq );
  channel->addDspBlock( peq );
  connect( peq, SIGNAL(valueChanged()), this, SLOT(updatePlots()) );

  peq = new QPeq( -6.0, 2000.0, 2.0,
                  MOD_PARAMEQ3_ALG0_STAGE1_B2_ADDR, MOD_PARAMEQ3_ALG0_STAGE1_B1_ADDR, MOD_PARAMEQ3_ALG0_STAGE1_B0_ADDR,
                  MOD_PARAMEQ3_ALG0_STAGE1_A2_ADDR, MOD_PARAMEQ3_ALG0_STAGE1_A1_ADDR,
                  FS,
                  &dsp );
  layout->addWidget( peq );
  channel->addDspBlock( peq );
  connect( peq, SIGNAL(valueChanged()), this, SLOT(updatePlots()) );

  peq = new QPeq( 6.0, 3000.0, 2.0,
                  MOD_PARAMEQ3_ALG0_STAGE2_B2_ADDR, MOD_PARAMEQ3_ALG0_STAGE2_B1_ADDR, MOD_PARAMEQ3_ALG0_STAGE2_B0_ADDR,
                  MOD_PARAMEQ3_ALG0_STAGE2_A2_ADDR, MOD_PARAMEQ3_ALG0_STAGE2_A1_ADDR,
                  FS,
                  &dsp );
  layout->addWidget( peq );
  channel->addDspBlock( peq );
  connect( peq, SIGNAL(valueChanged()), this, SLOT(updatePlots()) );

  peq = new QPeq( -6.0, 4000.0, 2.0,
                  MOD_PARAMEQ3_ALG0_STAGE3_B2_ADDR, MOD_PARAMEQ3_ALG0_STAGE3_B1_ADDR, MOD_PARAMEQ3_ALG0_STAGE3_B0_ADDR,
                  MOD_PARAMEQ3_ALG0_STAGE3_A2_ADDR, MOD_PARAMEQ3_ALG0_STAGE3_A1_ADDR,
                  FS,
                  &dsp );
  layout->addWidget( peq );
  channel->addDspBlock( peq );
  connect( peq, SIGNAL(valueChanged()), this, SLOT(updatePlots()) );

  peq = new QPeq( 6.0, 5000.0, 2.0,
                  MOD_PARAMEQ3_ALG0_STAGE4_B2_ADDR, MOD_PARAMEQ3_ALG0_STAGE4_B1_ADDR, MOD_PARAMEQ3_ALG0_STAGE4_B0_ADDR,
                  MOD_PARAMEQ3_ALG0_STAGE4_A2_ADDR, MOD_PARAMEQ3_ALG0_STAGE4_A1_ADDR,
                  FS,
                  &dsp );
  layout->addWidget( peq );
  channel->addDspBlock( peq );
  connect( peq, SIGNAL(valueChanged()), this, SLOT(updatePlots()) );

  peq = new QPeq( -6.0, 6000.0, 2.0,
                  MOD_PARAMEQ3_ALG0_STAGE5_B2_ADDR, MOD_PARAMEQ3_ALG0_STAGE5_B1_ADDR, MOD_PARAMEQ3_ALG0_STAGE5_B0_ADDR,
                  MOD_PARAMEQ3_ALG0_STAGE5_A2_ADDR, MOD_PARAMEQ3_ALG0_STAGE5_A1_ADDR,
                  FS,
                  &dsp );
  layout->addWidget( peq );
  channel->addDspBlock( peq );
  connect( peq, SIGNAL(valueChanged()), this, SLOT(updatePlots()) );

  peq = new QPeq( 6.0, 7000.0, 2.0,
                  MOD_PARAMEQ3_ALG0_STAGE6_B2_ADDR, MOD_PARAMEQ3_ALG0_STAGE6_B1_ADDR, MOD_PARAMEQ3_ALG0_STAGE6_B0_ADDR,
                  MOD_PARAMEQ3_ALG0_STAGE6_A2_ADDR, MOD_PARAMEQ3_ALG0_STAGE6_A1_ADDR,
                  FS,
                  &dsp );
  layout->addWidget( peq );
  channel->addDspBlock( peq );
  connect( peq, SIGNAL(valueChanged()), this, SLOT(updatePlots()) );

  peq = new QPeq( -6.0, 8000.0, 2.0,
                  MOD_PARAMEQ3_ALG0_STAGE7_B2_ADDR, MOD_PARAMEQ3_ALG0_STAGE7_B1_ADDR, MOD_PARAMEQ3_ALG0_STAGE7_B0_ADDR,
                  MOD_PARAMEQ3_ALG0_STAGE7_A2_ADDR, MOD_PARAMEQ3_ALG0_STAGE7_A1_ADDR,
                  FS,
                  &dsp );
  layout->addWidget( peq );
  channel->addDspBlock( peq );
  connect( peq, SIGNAL(valueChanged()), this, SLOT(updatePlots()) );

  peq = new QPeq( 6.0, 9000.0, 2.0,
                  MOD_PARAMEQ3_ALG0_STAGE8_B2_ADDR, MOD_PARAMEQ3_ALG0_STAGE8_B1_ADDR, MOD_PARAMEQ3_ALG0_STAGE8_B0_ADDR,
                  MOD_PARAMEQ3_ALG0_STAGE8_A2_ADDR, MOD_PARAMEQ3_ALG0_STAGE8_A1_ADDR,
                  FS,
                  &dsp );
  layout->addWidget( peq );
  channel->addDspBlock( peq );
  connect( peq, SIGNAL(valueChanged()), this, SLOT(updatePlots()) );

  peq = new QPeq( -6.0, 10000.0, 2.0,
                  MOD_PARAMEQ3_ALG0_STAGE9_B2_ADDR, MOD_PARAMEQ3_ALG0_STAGE9_B1_ADDR, MOD_PARAMEQ3_ALG0_STAGE9_B0_ADDR,
                  MOD_PARAMEQ3_ALG0_STAGE9_A2_ADDR, MOD_PARAMEQ3_ALG0_STAGE9_A1_ADDR,
                  FS,
                  &dsp );
  layout->addWidget( peq );
  channel->addDspBlock( peq );
  connect( peq, SIGNAL(valueChanged()), this, SLOT(updatePlots()) );

  hshelv = new QHighShelv( 6.0, 5000.0, 1.0,
                           MOD_HIGHSHELV3_ALG0_STAGE0_B2_ADDR, MOD_HIGHSHELV3_ALG0_STAGE0_B1_ADDR, MOD_HIGHSHELV3_ALG0_STAGE0_B0_ADDR,
                           MOD_HIGHSHELV3_ALG0_STAGE0_A2_ADDR, MOD_HIGHSHELV3_ALG0_STAGE0_A1_ADDR,
                           FS,
                           &dsp );
  layout->addWidget( hshelv );
  channel->addDspBlock( hshelv );
  connect( hshelv, SIGNAL(valueChanged()), this, SLOT(updatePlots()) );

  lp = new QLowPass( QLowPass::kLinkwitzRiley12, 10000.0,
                     MOD_LP3_1_ALG0_STAGE0_B2_ADDR, MOD_LP3_1_ALG0_STAGE0_B1_ADDR, MOD_LP3_1_ALG0_STAGE0_B0_ADDR,
                     MOD_LP3_1_ALG0_STAGE0_A2_ADDR, MOD_LP3_1_ALG0_STAGE0_A1_ADDR,
                     MOD_LP3_2_ALG0_STAGE0_B2_ADDR, MOD_LP3_2_ALG0_STAGE0_B1_ADDR, MOD_LP3_2_ALG0_STAGE0_B0_ADDR,
                     MOD_LP3_2_ALG0_STAGE0_A2_ADDR, MOD_LP3_2_ALG0_STAGE0_A1_ADDR,
                     MOD_LP3_3_ALG0_STAGE0_B2_ADDR, MOD_LP3_3_ALG0_STAGE0_B1_ADDR, MOD_LP3_3_ALG0_STAGE0_B0_ADDR,
                     MOD_LP3_3_ALG0_STAGE0_A2_ADDR, MOD_LP3_3_ALG0_STAGE0_A1_ADDR,
                     MOD_LP3_4_ALG0_STAGE0_B2_ADDR, MOD_LP3_4_ALG0_STAGE0_B1_ADDR, MOD_LP3_4_ALG0_STAGE0_B0_ADDR,
                     MOD_LP3_4_ALG0_STAGE0_A2_ADDR, MOD_LP3_4_ALG0_STAGE0_A1_ADDR,
                     FS,
                     &dsp );
  layout->addWidget( lp );
  channel->addDspBlock( lp );
  connect( lp, SIGNAL(valueChanged()), this, SLOT(updatePlots()) );

  phase = new QPhase( 1000.0, 1.0,
                      MOD_PHASE3_ALG0_STAGE0_B2_ADDR, MOD_PHASE3_ALG0_STAGE0_B1_ADDR, MOD_PHASE3_ALG0_STAGE0_B0_ADDR,
                      MOD_PHASE3_ALG0_STAGE0_A2_ADDR, MOD_PHASE3_ALG0_STAGE0_A1_ADDR,
                      FS,
                      &dsp );
  layout->addWidget( phase );
  channel->addDspBlock( phase );
  connect( phase, SIGNAL(valueChanged()), this, SLOT(updatePlots()) );

  dly = new QDelay( 0.0, 48000.0, MOD_DELAY3_DELAYAMT_ADDR, &dsp );
  layout->addWidget( dly );
  channel->addDspBlock( dly );
  connect( dly, SIGNAL(valueChanged()), this, SLOT(updatePlots()) );

  gain = new QGain( 0.0, MOD_GAIN3_ALG0_TARGET_ADDR, &dsp );
  layout->addWidget( gain );
  channel->addDspBlock( gain );
  connect( gain, SIGNAL(valueChanged()), this, SLOT(updatePlots()) );
  listOutputGains.append( gain );

  layout->setSpacing( 0 );
  layout->setMargin( 0 );
  layout->setContentsMargins( 0, 0, 0, 0 );
  layout->setAlignment( Qt::AlignLeft );

  channel->widgetChannel->setLayout( layout );

  for( int chn = 0; chn < numChannels; chn++ )
  {
    QAction* action = new QAction( "Show Channel " + QString::number(chn+1) );
    action->setCheckable( true );
    channel->actionsContextMenu.append( action );
    channel->contextMenu.addAction( action );
  }
  channel->actionsContextMenu.at(chn)->setChecked( true );
  connect( channel, SIGNAL(selectionChanged()), this, SLOT(updatePlots()) );

  //----------------------------------------------------------------------------
  //--- Channel 4
  chn = 3;
  channel = new QChannel;
  ui->tabChannels->addTab( channel, "" );
  lbl1 = new QLabel();
  lbl1->setText( "  Channel " + QString::number( chn+1 ) );
  lbl1->setStyleSheet( QString("background-color: transparent; border: 0px solid black; border-left: 2px solid ") + colorPlot[chn%kMaxPlotColors].name() + QString("; color: white; ") );
  ui->tabChannels->tabBar()->setTabButton( chn, QTabBar::LeftSide, lbl1 );

  layout = new QHBoxLayout;

  input = new QInputSelect( 3, MOD_NX1_1_4_MONOMUXSIGMA300NS4INDEX_ADDR, &dsp );
  layout->addWidget( input );
  channel->addDspBlock( input );

  hp = new QHighPass( QHighPass::kLinkwitzRiley12, 100.0,
                      MOD_HP4_1_ALG0_STAGE0_B2_ADDR, MOD_HP4_1_ALG0_STAGE0_B1_ADDR, MOD_HP4_1_ALG0_STAGE0_B0_ADDR,
                      MOD_HP4_1_ALG0_STAGE0_A2_ADDR, MOD_HP4_1_ALG0_STAGE0_A1_ADDR,
                      MOD_HP4_2_ALG0_STAGE0_B2_ADDR, MOD_HP4_2_ALG0_STAGE0_B1_ADDR, MOD_HP4_2_ALG0_STAGE0_B0_ADDR,
                      MOD_HP4_2_ALG0_STAGE0_A2_ADDR, MOD_HP4_2_ALG0_STAGE0_A1_ADDR,
                      MOD_HP4_3_ALG0_STAGE0_B2_ADDR, MOD_HP4_3_ALG0_STAGE0_B1_ADDR, MOD_HP4_3_ALG0_STAGE0_B0_ADDR,
                      MOD_HP4_3_ALG0_STAGE0_A2_ADDR, MOD_HP4_3_ALG0_STAGE0_A1_ADDR,
                      MOD_HP4_4_ALG0_STAGE0_B2_ADDR, MOD_HP4_4_ALG0_STAGE0_B1_ADDR, MOD_HP4_4_ALG0_STAGE0_B0_ADDR,
                      MOD_HP4_4_ALG0_STAGE0_A2_ADDR, MOD_HP4_4_ALG0_STAGE0_A1_ADDR,
                      FS,
                      &dsp );
  layout->addWidget( hp );
  channel->addDspBlock( hp );
  connect( hp, SIGNAL(valueChanged()), this, SLOT(updatePlots()) );

  lshelv = new QLowShelv( 6.0, 100.0, 1.0,
                          MOD_LOWSHELV4_ALG0_STAGE0_B2_ADDR, MOD_LOWSHELV4_ALG0_STAGE0_B1_ADDR, MOD_LOWSHELV4_ALG0_STAGE0_B0_ADDR,
                          MOD_LOWSHELV4_ALG0_STAGE0_A2_ADDR, MOD_LOWSHELV4_ALG0_STAGE0_A1_ADDR,
                          FS,
                          &dsp );
  layout->addWidget( lshelv );
  channel->addDspBlock( lshelv );
  connect( lshelv, SIGNAL(valueChanged()), this, SLOT(updatePlots()) );

  peq = new QPeq( 6.0, 1000.0, 1.0,
                  MOD_PARAMEQ4_ALG0_STAGE0_B2_ADDR, MOD_PARAMEQ4_ALG0_STAGE0_B1_ADDR, MOD_PARAMEQ4_ALG0_STAGE0_B0_ADDR,
                  MOD_PARAMEQ4_ALG0_STAGE0_A2_ADDR, MOD_PARAMEQ4_ALG0_STAGE0_A1_ADDR,
                  FS,
                  &dsp );
  layout->addWidget( peq );
  channel->addDspBlock( peq );
  connect( peq, SIGNAL(valueChanged()), this, SLOT(updatePlots()) );

  peq = new QPeq( -6.0, 2000.0, 2.0,
                  MOD_PARAMEQ4_ALG0_STAGE1_B2_ADDR, MOD_PARAMEQ4_ALG0_STAGE1_B1_ADDR, MOD_PARAMEQ4_ALG0_STAGE1_B0_ADDR,
                  MOD_PARAMEQ4_ALG0_STAGE1_A2_ADDR, MOD_PARAMEQ4_ALG0_STAGE1_A1_ADDR,
                  FS,
                  &dsp );
  layout->addWidget( peq );
  channel->addDspBlock( peq );
  connect( peq, SIGNAL(valueChanged()), this, SLOT(updatePlots()) );

  peq = new QPeq( 6.0, 3000.0, 2.0,
                  MOD_PARAMEQ4_ALG0_STAGE2_B2_ADDR, MOD_PARAMEQ4_ALG0_STAGE2_B1_ADDR, MOD_PARAMEQ4_ALG0_STAGE2_B0_ADDR,
                  MOD_PARAMEQ4_ALG0_STAGE2_A2_ADDR, MOD_PARAMEQ4_ALG0_STAGE2_A1_ADDR,
                  FS,
                  &dsp );
  layout->addWidget( peq );
  channel->addDspBlock( peq );
  connect( peq, SIGNAL(valueChanged()), this, SLOT(updatePlots()) );

  peq = new QPeq( -6.0, 4000.0, 2.0,
                  MOD_PARAMEQ4_ALG0_STAGE3_B2_ADDR, MOD_PARAMEQ4_ALG0_STAGE3_B1_ADDR, MOD_PARAMEQ4_ALG0_STAGE3_B0_ADDR,
                  MOD_PARAMEQ4_ALG0_STAGE3_A2_ADDR, MOD_PARAMEQ4_ALG0_STAGE3_A1_ADDR,
                  FS,
                  &dsp );
  layout->addWidget( peq );
  channel->addDspBlock( peq );
  connect( peq, SIGNAL(valueChanged()), this, SLOT(updatePlots()) );

  peq = new QPeq( 6.0, 5000.0, 2.0,
                  MOD_PARAMEQ4_ALG0_STAGE4_B2_ADDR, MOD_PARAMEQ4_ALG0_STAGE4_B1_ADDR, MOD_PARAMEQ4_ALG0_STAGE4_B0_ADDR,
                  MOD_PARAMEQ4_ALG0_STAGE4_A2_ADDR, MOD_PARAMEQ4_ALG0_STAGE4_A1_ADDR,
                  FS,
                  &dsp );
  layout->addWidget( peq );
  channel->addDspBlock( peq );
  connect( peq, SIGNAL(valueChanged()), this, SLOT(updatePlots()) );

  peq = new QPeq( -6.0, 6000.0, 2.0,
                  MOD_PARAMEQ4_ALG0_STAGE5_B2_ADDR, MOD_PARAMEQ4_ALG0_STAGE5_B1_ADDR, MOD_PARAMEQ4_ALG0_STAGE5_B0_ADDR,
                  MOD_PARAMEQ4_ALG0_STAGE5_A2_ADDR, MOD_PARAMEQ4_ALG0_STAGE5_A1_ADDR,
                  FS,
                  &dsp );
  layout->addWidget( peq );
  channel->addDspBlock( peq );
  connect( peq, SIGNAL(valueChanged()), this, SLOT(updatePlots()) );

  peq = new QPeq( 6.0, 7000.0, 2.0,
                  MOD_PARAMEQ4_ALG0_STAGE6_B2_ADDR, MOD_PARAMEQ4_ALG0_STAGE6_B1_ADDR, MOD_PARAMEQ4_ALG0_STAGE6_B0_ADDR,
                  MOD_PARAMEQ4_ALG0_STAGE6_A2_ADDR, MOD_PARAMEQ4_ALG0_STAGE6_A1_ADDR,
                  FS,
                  &dsp );
  layout->addWidget( peq );
  channel->addDspBlock( peq );
  connect( peq, SIGNAL(valueChanged()), this, SLOT(updatePlots()) );

  peq = new QPeq( -6.0, 8000.0, 2.0,
                  MOD_PARAMEQ4_ALG0_STAGE7_B2_ADDR, MOD_PARAMEQ4_ALG0_STAGE7_B1_ADDR, MOD_PARAMEQ4_ALG0_STAGE7_B0_ADDR,
                  MOD_PARAMEQ4_ALG0_STAGE7_A2_ADDR, MOD_PARAMEQ4_ALG0_STAGE7_A1_ADDR,
                  FS,
                  &dsp );
  layout->addWidget( peq );
  channel->addDspBlock( peq );
  connect( peq, SIGNAL(valueChanged()), this, SLOT(updatePlots()) );

  peq = new QPeq( 6.0, 9000.0, 2.0,
                  MOD_PARAMEQ4_ALG0_STAGE8_B2_ADDR, MOD_PARAMEQ4_ALG0_STAGE8_B1_ADDR, MOD_PARAMEQ4_ALG0_STAGE8_B0_ADDR,
                  MOD_PARAMEQ4_ALG0_STAGE8_A2_ADDR, MOD_PARAMEQ4_ALG0_STAGE8_A1_ADDR,
                  FS,
                  &dsp );
  layout->addWidget( peq );
  channel->addDspBlock( peq );
  connect( peq, SIGNAL(valueChanged()), this, SLOT(updatePlots()) );

  peq = new QPeq( -6.0, 10000.0, 2.0,
                  MOD_PARAMEQ4_ALG0_STAGE9_B2_ADDR, MOD_PARAMEQ4_ALG0_STAGE9_B1_ADDR, MOD_PARAMEQ4_ALG0_STAGE9_B0_ADDR,
                  MOD_PARAMEQ4_ALG0_STAGE9_A2_ADDR, MOD_PARAMEQ4_ALG0_STAGE9_A1_ADDR,
                  FS,
                  &dsp );
  layout->addWidget( peq );
  channel->addDspBlock( peq );
  connect( peq, SIGNAL(valueChanged()), this, SLOT(updatePlots()) );

  hshelv = new QHighShelv( 6.0, 5000.0, 1.0,
                           MOD_HIGHSHELV4_ALG0_STAGE0_B2_ADDR, MOD_HIGHSHELV4_ALG0_STAGE0_B1_ADDR, MOD_HIGHSHELV4_ALG0_STAGE0_B0_ADDR,
                           MOD_HIGHSHELV4_ALG0_STAGE0_A2_ADDR, MOD_HIGHSHELV4_ALG0_STAGE0_A1_ADDR,
                           FS,
                           &dsp );
  layout->addWidget( hshelv );
  channel->addDspBlock( hshelv );
  connect( hshelv, SIGNAL(valueChanged()), this, SLOT(updatePlots()) );

  lp = new QLowPass( QLowPass::kLinkwitzRiley12, 10000.0,
                     MOD_LP4_1_ALG0_STAGE0_B2_ADDR, MOD_LP4_1_ALG0_STAGE0_B1_ADDR, MOD_LP4_1_ALG0_STAGE0_B0_ADDR,
                     MOD_LP4_1_ALG0_STAGE0_A2_ADDR, MOD_LP4_1_ALG0_STAGE0_A1_ADDR,
                     MOD_LP4_2_ALG0_STAGE0_B2_ADDR, MOD_LP4_2_ALG0_STAGE0_B1_ADDR, MOD_LP4_2_ALG0_STAGE0_B0_ADDR,
                     MOD_LP4_2_ALG0_STAGE0_A2_ADDR, MOD_LP4_2_ALG0_STAGE0_A1_ADDR,
                     MOD_LP4_3_ALG0_STAGE0_B2_ADDR, MOD_LP4_3_ALG0_STAGE0_B1_ADDR, MOD_LP4_3_ALG0_STAGE0_B0_ADDR,
                     MOD_LP4_3_ALG0_STAGE0_A2_ADDR, MOD_LP4_3_ALG0_STAGE0_A1_ADDR,
                     MOD_LP4_4_ALG0_STAGE0_B2_ADDR, MOD_LP4_4_ALG0_STAGE0_B1_ADDR, MOD_LP4_4_ALG0_STAGE0_B0_ADDR,
                     MOD_LP4_4_ALG0_STAGE0_A2_ADDR, MOD_LP4_4_ALG0_STAGE0_A1_ADDR,
                     FS,
                     &dsp );
  layout->addWidget( lp );
  channel->addDspBlock( lp );
  connect( lp, SIGNAL(valueChanged()), this, SLOT(updatePlots()) );

  phase = new QPhase( 1000.0, 1.0,
                      MOD_PHASE4_ALG0_STAGE0_B2_ADDR, MOD_PHASE4_ALG0_STAGE0_B1_ADDR, MOD_PHASE4_ALG0_STAGE0_B0_ADDR,
                      MOD_PHASE4_ALG0_STAGE0_A2_ADDR, MOD_PHASE4_ALG0_STAGE0_A1_ADDR,
                      FS,
                      &dsp );
  layout->addWidget( phase );
  channel->addDspBlock( phase );
  connect( phase, SIGNAL(valueChanged()), this, SLOT(updatePlots()) );

  dly = new QDelay( 0.0, 48000.0, MOD_DELAY4_DELAYAMT_ADDR, &dsp );
  layout->addWidget( dly );
  channel->addDspBlock( dly );
  connect( dly, SIGNAL(valueChanged()), this, SLOT(updatePlots()) );

  gain = new QGain( 0.0, MOD_GAIN4_ALG0_TARGET_ADDR, &dsp );
  layout->addWidget( gain );
  channel->addDspBlock( gain );
  connect( gain, SIGNAL(valueChanged()), this, SLOT(updatePlots()) );
  listOutputGains.append( gain );

  layout->setSpacing( 0 );
  layout->setMargin( 0 );
  layout->setContentsMargins( 0, 0, 0, 0 );
  layout->setAlignment( Qt::AlignLeft );

  channel->widgetChannel->setLayout( layout );

  for( int chn = 0; chn < numChannels; chn++ )
  {
    QAction* action = new QAction( "Show Channel " + QString::number(chn+1) );
    action->setCheckable( true );
    channel->actionsContextMenu.append( action );
    channel->contextMenu.addAction( action );
  }
  channel->actionsContextMenu.at(chn)->setChecked( true );
  connect( channel, SIGNAL(selectionChanged()), this, SLOT(updatePlots()) );

  //----------------------------------------------------------------------------
  //--- Channel 5
  chn = 4;
  channel = new QChannel;
  ui->tabChannels->addTab( channel, "" );
  lbl1 = new QLabel();
  lbl1->setText( "  Channel " + QString::number( chn+1 ) );
  lbl1->setStyleSheet( QString("background-color: transparent; border: 0px solid black; border-left: 2px solid ") + colorPlot[chn%kMaxPlotColors].name() + QString("; color: white; ") );
  ui->tabChannels->tabBar()->setTabButton( chn, QTabBar::LeftSide, lbl1 );

  layout = new QHBoxLayout;

  input = new QInputSelect( 4, MOD_NX1_1_5_MONOMUXSIGMA300NS5INDEX_ADDR, &dsp );
  layout->addWidget( input );
  channel->addDspBlock( input );

  hp = new QHighPass( QHighPass::kLinkwitzRiley12, 100.0,
                      MOD_HP5_1_ALG0_STAGE0_B2_ADDR, MOD_HP5_1_ALG0_STAGE0_B1_ADDR, MOD_HP5_1_ALG0_STAGE0_B0_ADDR,
                      MOD_HP5_1_ALG0_STAGE0_A2_ADDR, MOD_HP5_1_ALG0_STAGE0_A1_ADDR,
                      MOD_HP5_2_ALG0_STAGE0_B2_ADDR, MOD_HP5_2_ALG0_STAGE0_B1_ADDR, MOD_HP5_2_ALG0_STAGE0_B0_ADDR,
                      MOD_HP5_2_ALG0_STAGE0_A2_ADDR, MOD_HP5_2_ALG0_STAGE0_A1_ADDR,
                      MOD_HP5_3_ALG0_STAGE0_B2_ADDR, MOD_HP5_3_ALG0_STAGE0_B1_ADDR, MOD_HP5_3_ALG0_STAGE0_B0_ADDR,
                      MOD_HP5_3_ALG0_STAGE0_A2_ADDR, MOD_HP5_3_ALG0_STAGE0_A1_ADDR,
                      MOD_HP5_4_ALG0_STAGE0_B2_ADDR, MOD_HP5_4_ALG0_STAGE0_B1_ADDR, MOD_HP5_4_ALG0_STAGE0_B0_ADDR,
                      MOD_HP5_4_ALG0_STAGE0_A2_ADDR, MOD_HP5_4_ALG0_STAGE0_A1_ADDR,
                      FS,
                      &dsp );
  layout->addWidget( hp );
  channel->addDspBlock( hp );
  connect( hp, SIGNAL(valueChanged()), this, SLOT(updatePlots()) );

  lshelv = new QLowShelv( 6.0, 100.0, 1.0,
                          MOD_LOWSHELV5_ALG0_STAGE0_B2_ADDR, MOD_LOWSHELV5_ALG0_STAGE0_B1_ADDR, MOD_LOWSHELV5_ALG0_STAGE0_B0_ADDR,
                          MOD_LOWSHELV5_ALG0_STAGE0_A2_ADDR, MOD_LOWSHELV5_ALG0_STAGE0_A1_ADDR,
                          FS,
                          &dsp );
  layout->addWidget( lshelv );
  channel->addDspBlock( lshelv );
  connect( lshelv, SIGNAL(valueChanged()), this, SLOT(updatePlots()) );

  peq = new QPeq( 6.0, 1000.0, 1.0,
                  MOD_PARAMEQ5_ALG0_STAGE0_B2_ADDR, MOD_PARAMEQ5_ALG0_STAGE0_B1_ADDR, MOD_PARAMEQ5_ALG0_STAGE0_B0_ADDR,
                  MOD_PARAMEQ5_ALG0_STAGE0_A2_ADDR, MOD_PARAMEQ5_ALG0_STAGE0_A1_ADDR,
                  FS,
                  &dsp );
  layout->addWidget( peq );
  channel->addDspBlock( peq );
  connect( peq, SIGNAL(valueChanged()), this, SLOT(updatePlots()) );

  peq = new QPeq( -6.0, 2000.0, 2.0,
                  MOD_PARAMEQ5_ALG0_STAGE1_B2_ADDR, MOD_PARAMEQ5_ALG0_STAGE1_B1_ADDR, MOD_PARAMEQ5_ALG0_STAGE1_B0_ADDR,
                  MOD_PARAMEQ5_ALG0_STAGE1_A2_ADDR, MOD_PARAMEQ5_ALG0_STAGE1_A1_ADDR,
                  FS,
                  &dsp );
  layout->addWidget( peq );
  channel->addDspBlock( peq );
  connect( peq, SIGNAL(valueChanged()), this, SLOT(updatePlots()) );

  peq = new QPeq( 6.0, 3000.0, 2.0,
                  MOD_PARAMEQ5_ALG0_STAGE2_B2_ADDR, MOD_PARAMEQ5_ALG0_STAGE2_B1_ADDR, MOD_PARAMEQ5_ALG0_STAGE2_B0_ADDR,
                  MOD_PARAMEQ5_ALG0_STAGE2_A2_ADDR, MOD_PARAMEQ5_ALG0_STAGE2_A1_ADDR,
                  FS,
                  &dsp );
  layout->addWidget( peq );
  channel->addDspBlock( peq );
  connect( peq, SIGNAL(valueChanged()), this, SLOT(updatePlots()) );

  peq = new QPeq( -6.0, 4000.0, 2.0,
                  MOD_PARAMEQ5_ALG0_STAGE3_B2_ADDR, MOD_PARAMEQ5_ALG0_STAGE3_B1_ADDR, MOD_PARAMEQ5_ALG0_STAGE3_B0_ADDR,
                  MOD_PARAMEQ5_ALG0_STAGE3_A2_ADDR, MOD_PARAMEQ5_ALG0_STAGE3_A1_ADDR,
                  FS,
                  &dsp );
  layout->addWidget( peq );
  channel->addDspBlock( peq );
  connect( peq, SIGNAL(valueChanged()), this, SLOT(updatePlots()) );

  peq = new QPeq( 6.0, 5000.0, 2.0,
                  MOD_PARAMEQ5_ALG0_STAGE4_B2_ADDR, MOD_PARAMEQ5_ALG0_STAGE4_B1_ADDR, MOD_PARAMEQ5_ALG0_STAGE4_B0_ADDR,
                  MOD_PARAMEQ5_ALG0_STAGE4_A2_ADDR, MOD_PARAMEQ5_ALG0_STAGE4_A1_ADDR,
                  FS,
                  &dsp );
  layout->addWidget( peq );
  channel->addDspBlock( peq );
  connect( peq, SIGNAL(valueChanged()), this, SLOT(updatePlots()) );

  peq = new QPeq( -6.0, 6000.0, 2.0,
                  MOD_PARAMEQ5_ALG0_STAGE5_B2_ADDR, MOD_PARAMEQ5_ALG0_STAGE5_B1_ADDR, MOD_PARAMEQ5_ALG0_STAGE5_B0_ADDR,
                  MOD_PARAMEQ5_ALG0_STAGE5_A2_ADDR, MOD_PARAMEQ5_ALG0_STAGE5_A1_ADDR,
                  FS,
                  &dsp );
  layout->addWidget( peq );
  channel->addDspBlock( peq );
  connect( peq, SIGNAL(valueChanged()), this, SLOT(updatePlots()) );

  peq = new QPeq( 6.0, 7000.0, 2.0,
                  MOD_PARAMEQ5_ALG0_STAGE6_B2_ADDR, MOD_PARAMEQ5_ALG0_STAGE6_B1_ADDR, MOD_PARAMEQ5_ALG0_STAGE6_B0_ADDR,
                  MOD_PARAMEQ5_ALG0_STAGE6_A2_ADDR, MOD_PARAMEQ5_ALG0_STAGE6_A1_ADDR,
                  FS,
                  &dsp );
  layout->addWidget( peq );
  channel->addDspBlock( peq );
  connect( peq, SIGNAL(valueChanged()), this, SLOT(updatePlots()) );

  peq = new QPeq( -6.0, 8000.0, 2.0,
                  MOD_PARAMEQ5_ALG0_STAGE7_B2_ADDR, MOD_PARAMEQ5_ALG0_STAGE7_B1_ADDR, MOD_PARAMEQ5_ALG0_STAGE7_B0_ADDR,
                  MOD_PARAMEQ5_ALG0_STAGE7_A2_ADDR, MOD_PARAMEQ5_ALG0_STAGE7_A1_ADDR,
                  FS,
                  &dsp );
  layout->addWidget( peq );
  channel->addDspBlock( peq );
  connect( peq, SIGNAL(valueChanged()), this, SLOT(updatePlots()) );

  peq = new QPeq( 6.0, 9000.0, 2.0,
                  MOD_PARAMEQ5_ALG0_STAGE8_B2_ADDR, MOD_PARAMEQ5_ALG0_STAGE8_B1_ADDR, MOD_PARAMEQ5_ALG0_STAGE8_B0_ADDR,
                  MOD_PARAMEQ5_ALG0_STAGE8_A2_ADDR, MOD_PARAMEQ5_ALG0_STAGE8_A1_ADDR,
                  FS,
                  &dsp );
  layout->addWidget( peq );
  channel->addDspBlock( peq );
  connect( peq, SIGNAL(valueChanged()), this, SLOT(updatePlots()) );

  peq = new QPeq( -6.0, 10000.0, 2.0,
                  MOD_PARAMEQ5_ALG0_STAGE9_B2_ADDR, MOD_PARAMEQ5_ALG0_STAGE9_B1_ADDR, MOD_PARAMEQ5_ALG0_STAGE9_B0_ADDR,
                  MOD_PARAMEQ5_ALG0_STAGE9_A2_ADDR, MOD_PARAMEQ5_ALG0_STAGE9_A1_ADDR,
                  FS,
                  &dsp );
  layout->addWidget( peq );
  channel->addDspBlock( peq );
  connect( peq, SIGNAL(valueChanged()), this, SLOT(updatePlots()) );

  hshelv = new QHighShelv( 6.0, 5000.0, 1.0,
                           MOD_HIGHSHELV5_ALG0_STAGE0_B2_ADDR, MOD_HIGHSHELV5_ALG0_STAGE0_B1_ADDR, MOD_HIGHSHELV5_ALG0_STAGE0_B0_ADDR,
                           MOD_HIGHSHELV5_ALG0_STAGE0_A2_ADDR, MOD_HIGHSHELV5_ALG0_STAGE0_A1_ADDR,
                           FS,
                           &dsp );
  layout->addWidget( hshelv );
  channel->addDspBlock( hshelv );
  connect( hshelv, SIGNAL(valueChanged()), this, SLOT(updatePlots()) );

  lp = new QLowPass( QLowPass::kLinkwitzRiley12, 10000.0,
                     MOD_LP5_1_ALG0_STAGE0_B2_ADDR, MOD_LP5_1_ALG0_STAGE0_B1_ADDR, MOD_LP5_1_ALG0_STAGE0_B0_ADDR,
                     MOD_LP5_1_ALG0_STAGE0_A2_ADDR, MOD_LP5_1_ALG0_STAGE0_A1_ADDR,
                     MOD_LP5_2_ALG0_STAGE0_B2_ADDR, MOD_LP5_2_ALG0_STAGE0_B1_ADDR, MOD_LP5_2_ALG0_STAGE0_B0_ADDR,
                     MOD_LP5_2_ALG0_STAGE0_A2_ADDR, MOD_LP5_2_ALG0_STAGE0_A1_ADDR,
                     MOD_LP5_3_ALG0_STAGE0_B2_ADDR, MOD_LP5_3_ALG0_STAGE0_B1_ADDR, MOD_LP5_3_ALG0_STAGE0_B0_ADDR,
                     MOD_LP5_3_ALG0_STAGE0_A2_ADDR, MOD_LP5_3_ALG0_STAGE0_A1_ADDR,
                     MOD_LP5_4_ALG0_STAGE0_B2_ADDR, MOD_LP5_4_ALG0_STAGE0_B1_ADDR, MOD_LP5_4_ALG0_STAGE0_B0_ADDR,
                     MOD_LP5_4_ALG0_STAGE0_A2_ADDR, MOD_LP5_4_ALG0_STAGE0_A1_ADDR,
                     FS,
                     &dsp );
  layout->addWidget( lp );
  channel->addDspBlock( lp );
  connect( lp, SIGNAL(valueChanged()), this, SLOT(updatePlots()) );

  phase = new QPhase( 1000.0, 1.0,
                      MOD_PHASE5_ALG0_STAGE0_B2_ADDR, MOD_PHASE5_ALG0_STAGE0_B1_ADDR, MOD_PHASE5_ALG0_STAGE0_B0_ADDR,
                      MOD_PHASE5_ALG0_STAGE0_A2_ADDR, MOD_PHASE5_ALG0_STAGE0_A1_ADDR,
                      FS,
                      &dsp );
  layout->addWidget( phase );
  channel->addDspBlock( phase );
  connect( phase, SIGNAL(valueChanged()), this, SLOT(updatePlots()) );

  dly = new QDelay( 0.0, 48000.0, MOD_DELAY5_DELAYAMT_ADDR, &dsp );
  layout->addWidget( dly );
  channel->addDspBlock( dly );
  connect( dly, SIGNAL(valueChanged()), this, SLOT(updatePlots()) );

  gain = new QGain( 0.0, MOD_GAIN5_ALG0_TARGET_ADDR, &dsp );
  layout->addWidget( gain );
  channel->addDspBlock( gain );
  connect( gain, SIGNAL(valueChanged()), this, SLOT(updatePlots()) );
  listOutputGains.append( gain );

  layout->setSpacing( 0 );
  layout->setMargin( 0 );
  layout->setContentsMargins( 0, 0, 0, 0 );
  layout->setAlignment( Qt::AlignLeft );

  channel->widgetChannel->setLayout( layout );

  for( int chn = 0; chn < numChannels; chn++ )
  {
    QAction* action = new QAction( "Show Channel " + QString::number(chn+1) );
    action->setCheckable( true );
    channel->actionsContextMenu.append( action );
    channel->contextMenu.addAction( action );
  }
  channel->actionsContextMenu.at(chn)->setChecked( true );
  connect( channel, SIGNAL(selectionChanged()), this, SLOT(updatePlots()) );

  //----------------------------------------------------------------------------
  //--- Channel 6
  chn = 5;
  channel = new QChannel;
  ui->tabChannels->addTab( channel, "" );
  lbl1 = new QLabel();
  lbl1->setText( "  Channel " + QString::number( chn+1 ) );
  lbl1->setStyleSheet( QString("background-color: transparent; border: 0px solid black; border-left: 2px solid ") + colorPlot[chn%kMaxPlotColors].name() + QString("; color: white; ") );
  ui->tabChannels->tabBar()->setTabButton( chn, QTabBar::LeftSide, lbl1 );

  layout = new QHBoxLayout;

  input = new QInputSelect( 5, MOD_NX1_1_6_MONOMUXSIGMA300NS6INDEX_ADDR, &dsp );
  layout->addWidget( input );
  channel->addDspBlock( input );

  hp = new QHighPass( QHighPass::kLinkwitzRiley12, 100.0,
                      MOD_HP6_1_ALG0_STAGE0_B2_ADDR, MOD_HP6_1_ALG0_STAGE0_B1_ADDR, MOD_HP6_1_ALG0_STAGE0_B0_ADDR,
                      MOD_HP6_1_ALG0_STAGE0_A2_ADDR, MOD_HP6_1_ALG0_STAGE0_A1_ADDR,
                      MOD_HP6_2_ALG0_STAGE0_B2_ADDR, MOD_HP6_2_ALG0_STAGE0_B1_ADDR, MOD_HP6_2_ALG0_STAGE0_B0_ADDR,
                      MOD_HP6_2_ALG0_STAGE0_A2_ADDR, MOD_HP6_2_ALG0_STAGE0_A1_ADDR,
                      MOD_HP6_3_ALG0_STAGE0_B2_ADDR, MOD_HP6_3_ALG0_STAGE0_B1_ADDR, MOD_HP6_3_ALG0_STAGE0_B0_ADDR,
                      MOD_HP6_3_ALG0_STAGE0_A2_ADDR, MOD_HP6_3_ALG0_STAGE0_A1_ADDR,
                      MOD_HP6_4_ALG0_STAGE0_B2_ADDR, MOD_HP6_4_ALG0_STAGE0_B1_ADDR, MOD_HP6_4_ALG0_STAGE0_B0_ADDR,
                      MOD_HP6_4_ALG0_STAGE0_A2_ADDR, MOD_HP6_4_ALG0_STAGE0_A1_ADDR,
                      FS,
                      &dsp );
  layout->addWidget( hp );
  channel->addDspBlock( hp );
  connect( hp, SIGNAL(valueChanged()), this, SLOT(updatePlots()) );

  lshelv = new QLowShelv( 6.0, 100.0, 1.0,
                          MOD_LOWSHELV6_ALG0_STAGE0_B2_ADDR, MOD_LOWSHELV6_ALG0_STAGE0_B1_ADDR, MOD_LOWSHELV6_ALG0_STAGE0_B0_ADDR,
                          MOD_LOWSHELV6_ALG0_STAGE0_A2_ADDR, MOD_LOWSHELV6_ALG0_STAGE0_A1_ADDR,
                          FS,
                          &dsp );
  layout->addWidget( lshelv );
  channel->addDspBlock( lshelv );
  connect( lshelv, SIGNAL(valueChanged()), this, SLOT(updatePlots()) );

  peq = new QPeq( 6.0, 1000.0, 1.0,
                  MOD_PARAMEQ6_ALG0_STAGE0_B2_ADDR, MOD_PARAMEQ6_ALG0_STAGE0_B1_ADDR, MOD_PARAMEQ6_ALG0_STAGE0_B0_ADDR,
                  MOD_PARAMEQ6_ALG0_STAGE0_A2_ADDR, MOD_PARAMEQ6_ALG0_STAGE0_A1_ADDR,
                  FS,
                  &dsp );
  layout->addWidget( peq );
  channel->addDspBlock( peq );
  connect( peq, SIGNAL(valueChanged()), this, SLOT(updatePlots()) );

  peq = new QPeq( -6.0, 2000.0, 2.0,
                  MOD_PARAMEQ6_ALG0_STAGE1_B2_ADDR, MOD_PARAMEQ6_ALG0_STAGE1_B1_ADDR, MOD_PARAMEQ6_ALG0_STAGE1_B0_ADDR,
                  MOD_PARAMEQ6_ALG0_STAGE1_A2_ADDR, MOD_PARAMEQ6_ALG0_STAGE1_A1_ADDR,
                  FS,
                  &dsp );
  layout->addWidget( peq );
  channel->addDspBlock( peq );
  connect( peq, SIGNAL(valueChanged()), this, SLOT(updatePlots()) );

  peq = new QPeq( 6.0, 3000.0, 2.0,
                  MOD_PARAMEQ6_ALG0_STAGE2_B2_ADDR, MOD_PARAMEQ6_ALG0_STAGE2_B1_ADDR, MOD_PARAMEQ6_ALG0_STAGE2_B0_ADDR,
                  MOD_PARAMEQ6_ALG0_STAGE2_A2_ADDR, MOD_PARAMEQ6_ALG0_STAGE2_A1_ADDR,
                  FS,
                  &dsp );
  layout->addWidget( peq );
  channel->addDspBlock( peq );
  connect( peq, SIGNAL(valueChanged()), this, SLOT(updatePlots()) );

  peq = new QPeq( -6.0, 4000.0, 2.0,
                  MOD_PARAMEQ6_ALG0_STAGE3_B2_ADDR, MOD_PARAMEQ6_ALG0_STAGE3_B1_ADDR, MOD_PARAMEQ6_ALG0_STAGE3_B0_ADDR,
                  MOD_PARAMEQ6_ALG0_STAGE3_A2_ADDR, MOD_PARAMEQ6_ALG0_STAGE3_A1_ADDR,
                  FS,
                  &dsp );
  layout->addWidget( peq );
  channel->addDspBlock( peq );
  connect( peq, SIGNAL(valueChanged()), this, SLOT(updatePlots()) );

  peq = new QPeq( 6.0, 5000.0, 2.0,
                  MOD_PARAMEQ6_ALG0_STAGE4_B2_ADDR, MOD_PARAMEQ6_ALG0_STAGE4_B1_ADDR, MOD_PARAMEQ6_ALG0_STAGE4_B0_ADDR,
                  MOD_PARAMEQ6_ALG0_STAGE4_A2_ADDR, MOD_PARAMEQ6_ALG0_STAGE4_A1_ADDR,
                  FS,
                  &dsp );
  layout->addWidget( peq );
  channel->addDspBlock( peq );
  connect( peq, SIGNAL(valueChanged()), this, SLOT(updatePlots()) );

  peq = new QPeq( -6.0, 6000.0, 2.0,
                  MOD_PARAMEQ6_ALG0_STAGE5_B2_ADDR, MOD_PARAMEQ6_ALG0_STAGE5_B1_ADDR, MOD_PARAMEQ6_ALG0_STAGE5_B0_ADDR,
                  MOD_PARAMEQ6_ALG0_STAGE5_A2_ADDR, MOD_PARAMEQ6_ALG0_STAGE5_A1_ADDR,
                  FS,
                  &dsp );
  layout->addWidget( peq );
  channel->addDspBlock( peq );
  connect( peq, SIGNAL(valueChanged()), this, SLOT(updatePlots()) );

  peq = new QPeq( 6.0, 7000.0, 2.0,
                  MOD_PARAMEQ6_ALG0_STAGE6_B2_ADDR, MOD_PARAMEQ6_ALG0_STAGE6_B1_ADDR, MOD_PARAMEQ6_ALG0_STAGE6_B0_ADDR,
                  MOD_PARAMEQ6_ALG0_STAGE6_A2_ADDR, MOD_PARAMEQ6_ALG0_STAGE6_A1_ADDR,
                  FS,
                  &dsp );
  layout->addWidget( peq );
  channel->addDspBlock( peq );
  connect( peq, SIGNAL(valueChanged()), this, SLOT(updatePlots()) );

  peq = new QPeq( -6.0, 8000.0, 2.0,
                  MOD_PARAMEQ6_ALG0_STAGE7_B2_ADDR, MOD_PARAMEQ6_ALG0_STAGE7_B1_ADDR, MOD_PARAMEQ6_ALG0_STAGE7_B0_ADDR,
                  MOD_PARAMEQ6_ALG0_STAGE7_A2_ADDR, MOD_PARAMEQ6_ALG0_STAGE7_A1_ADDR,
                  FS,
                  &dsp );
  layout->addWidget( peq );
  channel->addDspBlock( peq );
  connect( peq, SIGNAL(valueChanged()), this, SLOT(updatePlots()) );

  peq = new QPeq( 6.0, 9000.0, 2.0,
                  MOD_PARAMEQ6_ALG0_STAGE8_B2_ADDR, MOD_PARAMEQ6_ALG0_STAGE8_B1_ADDR, MOD_PARAMEQ6_ALG0_STAGE8_B0_ADDR,
                  MOD_PARAMEQ6_ALG0_STAGE8_A2_ADDR, MOD_PARAMEQ6_ALG0_STAGE8_A1_ADDR,
                  FS,
                  &dsp );
  layout->addWidget( peq );
  channel->addDspBlock( peq );
  connect( peq, SIGNAL(valueChanged()), this, SLOT(updatePlots()) );

  peq = new QPeq( -6.0, 10000.0, 2.0,
                  MOD_PARAMEQ6_ALG0_STAGE9_B2_ADDR, MOD_PARAMEQ6_ALG0_STAGE9_B1_ADDR, MOD_PARAMEQ6_ALG0_STAGE9_B0_ADDR,
                  MOD_PARAMEQ6_ALG0_STAGE9_A2_ADDR, MOD_PARAMEQ6_ALG0_STAGE9_A1_ADDR,
                  FS,
                  &dsp );
  layout->addWidget( peq );
  channel->addDspBlock( peq );
  connect( peq, SIGNAL(valueChanged()), this, SLOT(updatePlots()) );

  hshelv = new QHighShelv( 6.0, 5000.0, 1.0,
                           MOD_HIGHSHELV6_ALG0_STAGE0_B2_ADDR, MOD_HIGHSHELV6_ALG0_STAGE0_B1_ADDR, MOD_HIGHSHELV6_ALG0_STAGE0_B0_ADDR,
                           MOD_HIGHSHELV6_ALG0_STAGE0_A2_ADDR, MOD_HIGHSHELV6_ALG0_STAGE0_A1_ADDR,
                           FS,
                           &dsp );
  layout->addWidget( hshelv );
  channel->addDspBlock( hshelv );
  connect( hshelv, SIGNAL(valueChanged()), this, SLOT(updatePlots()) );

  lp = new QLowPass( QLowPass::kLinkwitzRiley12, 10000.0,
                     MOD_LP6_1_ALG0_STAGE0_B2_ADDR, MOD_LP6_1_ALG0_STAGE0_B1_ADDR, MOD_LP6_1_ALG0_STAGE0_B0_ADDR,
                     MOD_LP6_1_ALG0_STAGE0_A2_ADDR, MOD_LP6_1_ALG0_STAGE0_A1_ADDR,
                     MOD_LP6_2_ALG0_STAGE0_B2_ADDR, MOD_LP6_2_ALG0_STAGE0_B1_ADDR, MOD_LP6_2_ALG0_STAGE0_B0_ADDR,
                     MOD_LP6_2_ALG0_STAGE0_A2_ADDR, MOD_LP6_2_ALG0_STAGE0_A1_ADDR,
                     MOD_LP6_3_ALG0_STAGE0_B2_ADDR, MOD_LP6_3_ALG0_STAGE0_B1_ADDR, MOD_LP6_3_ALG0_STAGE0_B0_ADDR,
                     MOD_LP6_3_ALG0_STAGE0_A2_ADDR, MOD_LP6_3_ALG0_STAGE0_A1_ADDR,
                     MOD_LP6_4_ALG0_STAGE0_B2_ADDR, MOD_LP6_4_ALG0_STAGE0_B1_ADDR, MOD_LP6_4_ALG0_STAGE0_B0_ADDR,
                     MOD_LP6_4_ALG0_STAGE0_A2_ADDR, MOD_LP6_4_ALG0_STAGE0_A1_ADDR,
                     FS,
                     &dsp );
  layout->addWidget( lp );
  channel->addDspBlock( lp );
  connect( lp, SIGNAL(valueChanged()), this, SLOT(updatePlots()) );

  phase = new QPhase( 1000.0, 1.0,
                      MOD_PHASE6_ALG0_STAGE0_B2_ADDR, MOD_PHASE6_ALG0_STAGE0_B1_ADDR, MOD_PHASE6_ALG0_STAGE0_B0_ADDR,
                      MOD_PHASE6_ALG0_STAGE0_A2_ADDR, MOD_PHASE6_ALG0_STAGE0_A1_ADDR,
                      FS,
                      &dsp );
  layout->addWidget( phase );
  channel->addDspBlock( phase );
  connect( phase, SIGNAL(valueChanged()), this, SLOT(updatePlots()) );

  dly = new QDelay( 0.0, 48000.0, MOD_DELAY6_DELAYAMT_ADDR, &dsp );
  layout->addWidget( dly );
  channel->addDspBlock( dly );
  connect( dly, SIGNAL(valueChanged()), this, SLOT(updatePlots()) );

  gain = new QGain( 0.0, MOD_GAIN6_ALG0_TARGET_ADDR, &dsp );
  layout->addWidget( gain );
  channel->addDspBlock( gain );
  connect( gain, SIGNAL(valueChanged()), this, SLOT(updatePlots()) );
  listOutputGains.append( gain );

  layout->setSpacing( 0 );
  layout->setMargin( 0 );
  layout->setContentsMargins( 0, 0, 0, 0 );
  layout->setAlignment( Qt::AlignLeft );

  channel->widgetChannel->setLayout( layout );

  for( int chn = 0; chn < numChannels; chn++ )
  {
    QAction* action = new QAction( "Show Channel " + QString::number(chn+1) );
    action->setCheckable( true );
    channel->actionsContextMenu.append( action );
    channel->contextMenu.addAction( action );
  }
  channel->actionsContextMenu.at(chn)->setChecked( true );
  connect( channel, SIGNAL(selectionChanged()), this, SLOT(updatePlots()) );

  //----------------------------------------------------------------------------
  //--- Channel 7
  chn = 6;
  channel = new QChannel;
  ui->tabChannels->addTab( channel, "" );
  lbl1 = new QLabel();
  lbl1->setText( "  Channel " + QString::number( chn+1 ) );
  lbl1->setStyleSheet( QString("background-color: transparent; border: 0px solid black; border-left: 2px solid ") + colorPlot[chn%kMaxPlotColors].name() + QString("; color: white; ") );
  ui->tabChannels->tabBar()->setTabButton( chn, QTabBar::LeftSide, lbl1 );

  layout = new QHBoxLayout;

  input = new QInputSelect( 6, MOD_NX1_1_7_MONOMUXSIGMA300NS7INDEX_ADDR, &dsp );
  layout->addWidget( input );
  channel->addDspBlock( input );

  hp = new QHighPass( QHighPass::kLinkwitzRiley12, 100.0,
                      MOD_HP7_1_ALG0_STAGE0_B2_ADDR, MOD_HP7_1_ALG0_STAGE0_B1_ADDR, MOD_HP7_1_ALG0_STAGE0_B0_ADDR,
                      MOD_HP7_1_ALG0_STAGE0_A2_ADDR, MOD_HP7_1_ALG0_STAGE0_A1_ADDR,
                      MOD_HP7_2_ALG0_STAGE0_B2_ADDR, MOD_HP7_2_ALG0_STAGE0_B1_ADDR, MOD_HP7_2_ALG0_STAGE0_B0_ADDR,
                      MOD_HP7_2_ALG0_STAGE0_A2_ADDR, MOD_HP7_2_ALG0_STAGE0_A1_ADDR,
                      MOD_HP7_3_ALG0_STAGE0_B2_ADDR, MOD_HP7_3_ALG0_STAGE0_B1_ADDR, MOD_HP7_3_ALG0_STAGE0_B0_ADDR,
                      MOD_HP7_3_ALG0_STAGE0_A2_ADDR, MOD_HP7_3_ALG0_STAGE0_A1_ADDR,
                      MOD_HP7_4_ALG0_STAGE0_B2_ADDR, MOD_HP7_4_ALG0_STAGE0_B1_ADDR, MOD_HP7_4_ALG0_STAGE0_B0_ADDR,
                      MOD_HP7_4_ALG0_STAGE0_A2_ADDR, MOD_HP7_4_ALG0_STAGE0_A1_ADDR,
                      FS,
                      &dsp );
  layout->addWidget( hp );
  channel->addDspBlock( hp );
  connect( hp, SIGNAL(valueChanged()), this, SLOT(updatePlots()) );

  lshelv = new QLowShelv( 6.0, 100.0, 1.0,
                          MOD_LOWSHELV7_ALG0_STAGE0_B2_ADDR, MOD_LOWSHELV7_ALG0_STAGE0_B1_ADDR, MOD_LOWSHELV7_ALG0_STAGE0_B0_ADDR,
                          MOD_LOWSHELV7_ALG0_STAGE0_A2_ADDR, MOD_LOWSHELV7_ALG0_STAGE0_A1_ADDR,
                          FS,
                          &dsp );
  layout->addWidget( lshelv );
  channel->addDspBlock( lshelv );
  connect( lshelv, SIGNAL(valueChanged()), this, SLOT(updatePlots()) );

  peq = new QPeq( 6.0, 1000.0, 1.0,
                  MOD_PARAMEQ7_ALG0_STAGE0_B2_ADDR, MOD_PARAMEQ7_ALG0_STAGE0_B1_ADDR, MOD_PARAMEQ7_ALG0_STAGE0_B0_ADDR,
                  MOD_PARAMEQ7_ALG0_STAGE0_A2_ADDR, MOD_PARAMEQ7_ALG0_STAGE0_A1_ADDR,
                  FS,
                  &dsp );
  layout->addWidget( peq );
  channel->addDspBlock( peq );
  connect( peq, SIGNAL(valueChanged()), this, SLOT(updatePlots()) );

  peq = new QPeq( -6.0, 2000.0, 2.0,
                  MOD_PARAMEQ7_ALG0_STAGE1_B2_ADDR, MOD_PARAMEQ7_ALG0_STAGE1_B1_ADDR, MOD_PARAMEQ7_ALG0_STAGE1_B0_ADDR,
                  MOD_PARAMEQ7_ALG0_STAGE1_A2_ADDR, MOD_PARAMEQ7_ALG0_STAGE1_A1_ADDR,
                  FS,
                  &dsp );
  layout->addWidget( peq );
  channel->addDspBlock( peq );
  connect( peq, SIGNAL(valueChanged()), this, SLOT(updatePlots()) );

  peq = new QPeq( 6.0, 3000.0, 2.0,
                  MOD_PARAMEQ7_ALG0_STAGE2_B2_ADDR, MOD_PARAMEQ7_ALG0_STAGE2_B1_ADDR, MOD_PARAMEQ7_ALG0_STAGE2_B0_ADDR,
                  MOD_PARAMEQ7_ALG0_STAGE2_A2_ADDR, MOD_PARAMEQ7_ALG0_STAGE2_A1_ADDR,
                  FS,
                  &dsp );
  layout->addWidget( peq );
  channel->addDspBlock( peq );
  connect( peq, SIGNAL(valueChanged()), this, SLOT(updatePlots()) );

  peq = new QPeq( -6.0, 4000.0, 2.0,
                  MOD_PARAMEQ7_ALG0_STAGE3_B2_ADDR, MOD_PARAMEQ7_ALG0_STAGE3_B1_ADDR, MOD_PARAMEQ7_ALG0_STAGE3_B0_ADDR,
                  MOD_PARAMEQ7_ALG0_STAGE3_A2_ADDR, MOD_PARAMEQ7_ALG0_STAGE3_A1_ADDR,
                  FS,
                  &dsp );
  layout->addWidget( peq );
  channel->addDspBlock( peq );
  connect( peq, SIGNAL(valueChanged()), this, SLOT(updatePlots()) );

  peq = new QPeq( 6.0, 5000.0, 2.0,
                  MOD_PARAMEQ7_ALG0_STAGE4_B2_ADDR, MOD_PARAMEQ7_ALG0_STAGE4_B1_ADDR, MOD_PARAMEQ7_ALG0_STAGE4_B0_ADDR,
                  MOD_PARAMEQ7_ALG0_STAGE4_A2_ADDR, MOD_PARAMEQ7_ALG0_STAGE4_A1_ADDR,
                  FS,
                  &dsp );
  layout->addWidget( peq );
  channel->addDspBlock( peq );
  connect( peq, SIGNAL(valueChanged()), this, SLOT(updatePlots()) );

  peq = new QPeq( -6.0, 6000.0, 2.0,
                  MOD_PARAMEQ7_ALG0_STAGE5_B2_ADDR, MOD_PARAMEQ7_ALG0_STAGE5_B1_ADDR, MOD_PARAMEQ7_ALG0_STAGE5_B0_ADDR,
                  MOD_PARAMEQ7_ALG0_STAGE5_A2_ADDR, MOD_PARAMEQ7_ALG0_STAGE5_A1_ADDR,
                  FS,
                  &dsp );
  layout->addWidget( peq );
  channel->addDspBlock( peq );
  connect( peq, SIGNAL(valueChanged()), this, SLOT(updatePlots()) );

  peq = new QPeq( 6.0, 7000.0, 2.0,
                  MOD_PARAMEQ7_ALG0_STAGE6_B2_ADDR, MOD_PARAMEQ7_ALG0_STAGE6_B1_ADDR, MOD_PARAMEQ7_ALG0_STAGE6_B0_ADDR,
                  MOD_PARAMEQ7_ALG0_STAGE6_A2_ADDR, MOD_PARAMEQ7_ALG0_STAGE6_A1_ADDR,
                  FS,
                  &dsp );
  layout->addWidget( peq );
  channel->addDspBlock( peq );
  connect( peq, SIGNAL(valueChanged()), this, SLOT(updatePlots()) );

  peq = new QPeq( -6.0, 8000.0, 2.0,
                  MOD_PARAMEQ7_ALG0_STAGE7_B2_ADDR, MOD_PARAMEQ7_ALG0_STAGE7_B1_ADDR, MOD_PARAMEQ7_ALG0_STAGE7_B0_ADDR,
                  MOD_PARAMEQ7_ALG0_STAGE7_A2_ADDR, MOD_PARAMEQ7_ALG0_STAGE7_A1_ADDR,
                  FS,
                  &dsp );
  layout->addWidget( peq );
  channel->addDspBlock( peq );
  connect( peq, SIGNAL(valueChanged()), this, SLOT(updatePlots()) );

  peq = new QPeq( 6.0, 9000.0, 2.0,
                  MOD_PARAMEQ7_ALG0_STAGE8_B2_ADDR, MOD_PARAMEQ7_ALG0_STAGE8_B1_ADDR, MOD_PARAMEQ7_ALG0_STAGE8_B0_ADDR,
                  MOD_PARAMEQ7_ALG0_STAGE8_A2_ADDR, MOD_PARAMEQ7_ALG0_STAGE8_A1_ADDR,
                  FS,
                  &dsp );
  layout->addWidget( peq );
  channel->addDspBlock( peq );
  connect( peq, SIGNAL(valueChanged()), this, SLOT(updatePlots()) );

  peq = new QPeq( -6.0, 10000.0, 2.0,
                  MOD_PARAMEQ7_ALG0_STAGE9_B2_ADDR, MOD_PARAMEQ7_ALG0_STAGE9_B1_ADDR, MOD_PARAMEQ7_ALG0_STAGE9_B0_ADDR,
                  MOD_PARAMEQ7_ALG0_STAGE9_A2_ADDR, MOD_PARAMEQ7_ALG0_STAGE9_A1_ADDR,
                  FS,
                  &dsp );
  layout->addWidget( peq );
  channel->addDspBlock( peq );
  connect( peq, SIGNAL(valueChanged()), this, SLOT(updatePlots()) );

  hshelv = new QHighShelv( 6.0, 5000.0, 1.0,
                           MOD_HIGHSHELV7_ALG0_STAGE0_B2_ADDR, MOD_HIGHSHELV7_ALG0_STAGE0_B1_ADDR, MOD_HIGHSHELV7_ALG0_STAGE0_B0_ADDR,
                           MOD_HIGHSHELV7_ALG0_STAGE0_A2_ADDR, MOD_HIGHSHELV7_ALG0_STAGE0_A1_ADDR,
                           FS,
                           &dsp );
  layout->addWidget( hshelv );
  channel->addDspBlock( hshelv );
  connect( hshelv, SIGNAL(valueChanged()), this, SLOT(updatePlots()) );

  lp = new QLowPass( QLowPass::kLinkwitzRiley12, 10000.0,
                     MOD_LP7_1_ALG0_STAGE0_B2_ADDR, MOD_LP7_1_ALG0_STAGE0_B1_ADDR, MOD_LP7_1_ALG0_STAGE0_B0_ADDR,
                     MOD_LP7_1_ALG0_STAGE0_A2_ADDR, MOD_LP7_1_ALG0_STAGE0_A1_ADDR,
                     MOD_LP7_2_ALG0_STAGE0_B2_ADDR, MOD_LP7_2_ALG0_STAGE0_B1_ADDR, MOD_LP7_2_ALG0_STAGE0_B0_ADDR,
                     MOD_LP7_2_ALG0_STAGE0_A2_ADDR, MOD_LP7_2_ALG0_STAGE0_A1_ADDR,
                     MOD_LP7_3_ALG0_STAGE0_B2_ADDR, MOD_LP7_3_ALG0_STAGE0_B1_ADDR, MOD_LP7_3_ALG0_STAGE0_B0_ADDR,
                     MOD_LP7_3_ALG0_STAGE0_A2_ADDR, MOD_LP7_3_ALG0_STAGE0_A1_ADDR,
                     MOD_LP7_4_ALG0_STAGE0_B2_ADDR, MOD_LP7_4_ALG0_STAGE0_B1_ADDR, MOD_LP7_4_ALG0_STAGE0_B0_ADDR,
                     MOD_LP7_4_ALG0_STAGE0_A2_ADDR, MOD_LP7_4_ALG0_STAGE0_A1_ADDR,
                     FS,
                     &dsp );
  layout->addWidget( lp );
  channel->addDspBlock( lp );
  connect( lp, SIGNAL(valueChanged()), this, SLOT(updatePlots()) );

  phase = new QPhase( 1000.0, 1.0,
                      MOD_PHASE7_ALG0_STAGE0_B2_ADDR, MOD_PHASE7_ALG0_STAGE0_B1_ADDR, MOD_PHASE7_ALG0_STAGE0_B0_ADDR,
                      MOD_PHASE7_ALG0_STAGE0_A2_ADDR, MOD_PHASE7_ALG0_STAGE0_A1_ADDR,
                      FS,
                      &dsp );
  layout->addWidget( phase );
  channel->addDspBlock( phase );
  connect( phase, SIGNAL(valueChanged()), this, SLOT(updatePlots()) );

  dly = new QDelay( 0.0, 48000.0, MOD_DELAY7_DELAYAMT_ADDR, &dsp );
  layout->addWidget( dly );
  channel->addDspBlock( dly );
  connect( dly, SIGNAL(valueChanged()), this, SLOT(updatePlots()) );

  gain = new QGain( 0.0, MOD_GAIN7_ALG0_TARGET_ADDR, &dsp );
  layout->addWidget( gain );
  channel->addDspBlock( gain );
  connect( gain, SIGNAL(valueChanged()), this, SLOT(updatePlots()) );
  listOutputGains.append( gain );

  layout->setSpacing( 0 );
  layout->setMargin( 0 );
  layout->setContentsMargins( 0, 0, 0, 0 );
  layout->setAlignment( Qt::AlignLeft );

  channel->widgetChannel->setLayout( layout );

  for( int chn = 0; chn < numChannels; chn++ )
  {
    QAction* action = new QAction( "Show Channel " + QString::number(chn+1) );
    action->setCheckable( true );
    channel->actionsContextMenu.append( action );
    channel->contextMenu.addAction( action );
  }
  channel->actionsContextMenu.at(chn)->setChecked( true );
  connect( channel, SIGNAL(selectionChanged()), this, SLOT(updatePlots()) );

  //----------------------------------------------------------------------------
  //--- Channel 8
  chn = 7;
  channel = new QChannel;
  ui->tabChannels->addTab( channel, "" );
  lbl1 = new QLabel();
  lbl1->setText( "  Channel " + QString::number( chn+1 ) );
  lbl1->setStyleSheet( QString("background-color: transparent; border: 0px solid black; border-left: 2px solid ") + colorPlot[chn%kMaxPlotColors].name() + QString("; color: white; ") );
  ui->tabChannels->tabBar()->setTabButton( chn, QTabBar::LeftSide, lbl1 );

  layout = new QHBoxLayout;

  input = new QInputSelect( 7, MOD_NX1_1_8_MONOMUXSIGMA300NS8INDEX_ADDR, &dsp );
  layout->addWidget( input );
  channel->addDspBlock( input );

  hp = new QHighPass( QHighPass::kLinkwitzRiley12, 100.0,
                      MOD_HP8_1_ALG0_STAGE0_B2_ADDR, MOD_HP8_1_ALG0_STAGE0_B1_ADDR, MOD_HP8_1_ALG0_STAGE0_B0_ADDR,
                      MOD_HP8_1_ALG0_STAGE0_A2_ADDR, MOD_HP8_1_ALG0_STAGE0_A1_ADDR,
                      MOD_HP8_2_ALG0_STAGE0_B2_ADDR, MOD_HP8_2_ALG0_STAGE0_B1_ADDR, MOD_HP8_2_ALG0_STAGE0_B0_ADDR,
                      MOD_HP8_2_ALG0_STAGE0_A2_ADDR, MOD_HP8_2_ALG0_STAGE0_A1_ADDR,
                      MOD_HP8_3_ALG0_STAGE0_B2_ADDR, MOD_HP8_3_ALG0_STAGE0_B1_ADDR, MOD_HP8_3_ALG0_STAGE0_B0_ADDR,
                      MOD_HP8_3_ALG0_STAGE0_A2_ADDR, MOD_HP8_3_ALG0_STAGE0_A1_ADDR,
                      MOD_HP8_4_ALG0_STAGE0_B2_ADDR, MOD_HP8_4_ALG0_STAGE0_B1_ADDR, MOD_HP8_4_ALG0_STAGE0_B0_ADDR,
                      MOD_HP8_4_ALG0_STAGE0_A2_ADDR, MOD_HP8_4_ALG0_STAGE0_A1_ADDR,
                      FS,
                      &dsp );
  layout->addWidget( hp );
  channel->addDspBlock( hp );
  connect( hp, SIGNAL(valueChanged()), this, SLOT(updatePlots()) );

  lshelv = new QLowShelv( 6.0, 100.0, 1.0,
                          MOD_LOWSHELV8_ALG0_STAGE0_B2_ADDR, MOD_LOWSHELV8_ALG0_STAGE0_B1_ADDR, MOD_LOWSHELV8_ALG0_STAGE0_B0_ADDR,
                          MOD_LOWSHELV8_ALG0_STAGE0_A2_ADDR, MOD_LOWSHELV8_ALG0_STAGE0_A1_ADDR,
                          FS,
                          &dsp );
  layout->addWidget( lshelv );
  channel->addDspBlock( lshelv );
  connect( lshelv, SIGNAL(valueChanged()), this, SLOT(updatePlots()) );

  peq = new QPeq( 6.0, 1000.0, 1.0,
                  MOD_PARAMEQ8_ALG0_STAGE0_B2_ADDR, MOD_PARAMEQ8_ALG0_STAGE0_B1_ADDR, MOD_PARAMEQ8_ALG0_STAGE0_B0_ADDR,
                  MOD_PARAMEQ8_ALG0_STAGE0_A2_ADDR, MOD_PARAMEQ8_ALG0_STAGE0_A1_ADDR,
                  FS,
                  &dsp );
  layout->addWidget( peq );
  channel->addDspBlock( peq );
  connect( peq, SIGNAL(valueChanged()), this, SLOT(updatePlots()) );

  peq = new QPeq( -6.0, 2000.0, 2.0,
                  MOD_PARAMEQ8_ALG0_STAGE1_B2_ADDR, MOD_PARAMEQ8_ALG0_STAGE1_B1_ADDR, MOD_PARAMEQ8_ALG0_STAGE1_B0_ADDR,
                  MOD_PARAMEQ8_ALG0_STAGE1_A2_ADDR, MOD_PARAMEQ8_ALG0_STAGE1_A1_ADDR,
                  FS,
                  &dsp );
  layout->addWidget( peq );
  channel->addDspBlock( peq );
  connect( peq, SIGNAL(valueChanged()), this, SLOT(updatePlots()) );

  peq = new QPeq( 6.0, 3000.0, 2.0,
                  MOD_PARAMEQ8_ALG0_STAGE2_B2_ADDR, MOD_PARAMEQ8_ALG0_STAGE2_B1_ADDR, MOD_PARAMEQ8_ALG0_STAGE2_B0_ADDR,
                  MOD_PARAMEQ8_ALG0_STAGE2_A2_ADDR, MOD_PARAMEQ8_ALG0_STAGE2_A1_ADDR,
                  FS,
                  &dsp );
  layout->addWidget( peq );
  channel->addDspBlock( peq );
  connect( peq, SIGNAL(valueChanged()), this, SLOT(updatePlots()) );

  peq = new QPeq( -6.0, 4000.0, 2.0,
                  MOD_PARAMEQ8_ALG0_STAGE3_B2_ADDR, MOD_PARAMEQ8_ALG0_STAGE3_B1_ADDR, MOD_PARAMEQ8_ALG0_STAGE3_B0_ADDR,
                  MOD_PARAMEQ8_ALG0_STAGE3_A2_ADDR, MOD_PARAMEQ8_ALG0_STAGE3_A1_ADDR,
                  FS,
                  &dsp );
  layout->addWidget( peq );
  channel->addDspBlock( peq );
  connect( peq, SIGNAL(valueChanged()), this, SLOT(updatePlots()) );

  peq = new QPeq( 6.0, 5000.0, 2.0,
                  MOD_PARAMEQ8_ALG0_STAGE4_B2_ADDR, MOD_PARAMEQ8_ALG0_STAGE4_B1_ADDR, MOD_PARAMEQ8_ALG0_STAGE4_B0_ADDR,
                  MOD_PARAMEQ8_ALG0_STAGE4_A2_ADDR, MOD_PARAMEQ8_ALG0_STAGE4_A1_ADDR,
                  FS,
                  &dsp );
  layout->addWidget( peq );
  channel->addDspBlock( peq );
  connect( peq, SIGNAL(valueChanged()), this, SLOT(updatePlots()) );

  peq = new QPeq( -6.0, 6000.0, 2.0,
                  MOD_PARAMEQ8_ALG0_STAGE5_B2_ADDR, MOD_PARAMEQ8_ALG0_STAGE5_B1_ADDR, MOD_PARAMEQ8_ALG0_STAGE5_B0_ADDR,
                  MOD_PARAMEQ8_ALG0_STAGE5_A2_ADDR, MOD_PARAMEQ8_ALG0_STAGE5_A1_ADDR,
                  FS,
                  &dsp );
  layout->addWidget( peq );
  channel->addDspBlock( peq );
  connect( peq, SIGNAL(valueChanged()), this, SLOT(updatePlots()) );

  peq = new QPeq( 6.0, 7000.0, 2.0,
                  MOD_PARAMEQ8_ALG0_STAGE6_B2_ADDR, MOD_PARAMEQ8_ALG0_STAGE6_B1_ADDR, MOD_PARAMEQ8_ALG0_STAGE6_B0_ADDR,
                  MOD_PARAMEQ8_ALG0_STAGE6_A2_ADDR, MOD_PARAMEQ8_ALG0_STAGE6_A1_ADDR,
                  FS,
                  &dsp );
  layout->addWidget( peq );
  channel->addDspBlock( peq );
  connect( peq, SIGNAL(valueChanged()), this, SLOT(updatePlots()) );

  peq = new QPeq( -6.0, 8000.0, 2.0,
                  MOD_PARAMEQ8_ALG0_STAGE7_B2_ADDR, MOD_PARAMEQ8_ALG0_STAGE7_B1_ADDR, MOD_PARAMEQ8_ALG0_STAGE7_B0_ADDR,
                  MOD_PARAMEQ8_ALG0_STAGE7_A2_ADDR, MOD_PARAMEQ8_ALG0_STAGE7_A1_ADDR,
                  FS,
                  &dsp );
  layout->addWidget( peq );
  channel->addDspBlock( peq );
  connect( peq, SIGNAL(valueChanged()), this, SLOT(updatePlots()) );

  peq = new QPeq( 6.0, 9000.0, 2.0,
                  MOD_PARAMEQ8_ALG0_STAGE8_B2_ADDR, MOD_PARAMEQ8_ALG0_STAGE8_B1_ADDR, MOD_PARAMEQ8_ALG0_STAGE8_B0_ADDR,
                  MOD_PARAMEQ8_ALG0_STAGE8_A2_ADDR, MOD_PARAMEQ8_ALG0_STAGE8_A1_ADDR,
                  FS,
                  &dsp );
  layout->addWidget( peq );
  channel->addDspBlock( peq );
  connect( peq, SIGNAL(valueChanged()), this, SLOT(updatePlots()) );

  peq = new QPeq( -6.0, 10000.0, 2.0,
                  MOD_PARAMEQ8_ALG0_STAGE9_B2_ADDR, MOD_PARAMEQ8_ALG0_STAGE9_B1_ADDR, MOD_PARAMEQ8_ALG0_STAGE9_B0_ADDR,
                  MOD_PARAMEQ8_ALG0_STAGE9_A2_ADDR, MOD_PARAMEQ8_ALG0_STAGE9_A1_ADDR,
                  FS,
                  &dsp );
  layout->addWidget( peq );
  channel->addDspBlock( peq );
  connect( peq, SIGNAL(valueChanged()), this, SLOT(updatePlots()) );

  hshelv = new QHighShelv( 6.0, 5000.0, 1.0,
                           MOD_HIGHSHELV8_ALG0_STAGE0_B2_ADDR, MOD_HIGHSHELV8_ALG0_STAGE0_B1_ADDR, MOD_HIGHSHELV8_ALG0_STAGE0_B0_ADDR,
                           MOD_HIGHSHELV8_ALG0_STAGE0_A2_ADDR, MOD_HIGHSHELV8_ALG0_STAGE0_A1_ADDR,
                           FS,
                           &dsp );
  layout->addWidget( hshelv );
  channel->addDspBlock( hshelv );
  connect( hshelv, SIGNAL(valueChanged()), this, SLOT(updatePlots()) );

  lp = new QLowPass( QLowPass::kLinkwitzRiley12, 10000.0,
                     MOD_LP8_1_ALG0_STAGE0_B2_ADDR, MOD_LP8_1_ALG0_STAGE0_B1_ADDR, MOD_LP8_1_ALG0_STAGE0_B0_ADDR,
                     MOD_LP8_1_ALG0_STAGE0_A2_ADDR, MOD_LP8_1_ALG0_STAGE0_A1_ADDR,
                     MOD_LP8_2_ALG0_STAGE0_B2_ADDR, MOD_LP8_2_ALG0_STAGE0_B1_ADDR, MOD_LP8_2_ALG0_STAGE0_B0_ADDR,
                     MOD_LP8_2_ALG0_STAGE0_A2_ADDR, MOD_LP8_2_ALG0_STAGE0_A1_ADDR,
                     MOD_LP8_3_ALG0_STAGE0_B2_ADDR, MOD_LP8_3_ALG0_STAGE0_B1_ADDR, MOD_LP8_3_ALG0_STAGE0_B0_ADDR,
                     MOD_LP8_3_ALG0_STAGE0_A2_ADDR, MOD_LP8_3_ALG0_STAGE0_A1_ADDR,
                     MOD_LP8_4_ALG0_STAGE0_B2_ADDR, MOD_LP8_4_ALG0_STAGE0_B1_ADDR, MOD_LP8_4_ALG0_STAGE0_B0_ADDR,
                     MOD_LP8_4_ALG0_STAGE0_A2_ADDR, MOD_LP8_4_ALG0_STAGE0_A1_ADDR,
                     FS,
                     &dsp );
  layout->addWidget( lp );
  channel->addDspBlock( lp );
  connect( lp, SIGNAL(valueChanged()), this, SLOT(updatePlots()) );

  phase = new QPhase( 1000.0, 1.0,
                      MOD_PHASE8_ALG0_STAGE0_B2_ADDR, MOD_PHASE8_ALG0_STAGE0_B1_ADDR, MOD_PHASE8_ALG0_STAGE0_B0_ADDR,
                      MOD_PHASE8_ALG0_STAGE0_A2_ADDR, MOD_PHASE8_ALG0_STAGE0_A1_ADDR,
                      FS,
                      &dsp );
  layout->addWidget( phase );
  channel->addDspBlock( phase );
  connect( phase, SIGNAL(valueChanged()), this, SLOT(updatePlots()) );

  dly = new QDelay( 0.0, 48000.0, MOD_DELAY8_DELAYAMT_ADDR, &dsp );
  layout->addWidget( dly );
  channel->addDspBlock( dly );
  connect( dly, SIGNAL(valueChanged()), this, SLOT(updatePlots()) );

  gain = new QGain( 0.0, MOD_GAIN8_ALG0_TARGET_ADDR, &dsp );
  layout->addWidget( gain );
  channel->addDspBlock( gain );
  connect( gain, SIGNAL(valueChanged()), this, SLOT(updatePlots()) );
  listOutputGains.append( gain );

  layout->setSpacing( 0 );
  layout->setMargin( 0 );
  layout->setContentsMargins( 0, 0, 0, 0 );
  layout->setAlignment( Qt::AlignLeft );

  channel->widgetChannel->setLayout( layout );

  for( int chn = 0; chn < numChannels; chn++ )
  {
    QAction* action = new QAction( "Show Channel " + QString::number(chn+1) );
    action->setCheckable( true );
    channel->actionsContextMenu.append( action );
    channel->contextMenu.addAction( action );
  }
  channel->actionsContextMenu.at(chn)->setChecked( true );
  connect( channel, SIGNAL(selectionChanged()), this, SLOT(updatePlots()) );

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

      if( length(H) > 0 )
        currentChannel->figVoltageMagnitude->semilogx( freq, 20.0 * log10( abs( H ) ), Qt::white, 2 );

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
/*void MainWindow::on_verticalSliderMainVolume_valueChanged( int value )
{
  for( int ii = 0; ii < listOutputGains.size(); ii++ )
    listOutputGains.at(ii)->sendDspParameter();
}*/
void MainWindow::on_volumeSliderMain_valueChanged( double val )
{
  for( int ii = 0; ii < listOutputGains.size(); ii++ )
    listOutputGains.at(ii)->sendDspParameter();
}
