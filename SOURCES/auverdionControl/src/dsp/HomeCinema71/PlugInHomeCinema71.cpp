#include <cstdint>

#include <QObject>

#include "PlugInHomeCinema71.hpp"

#include "QChannel.hpp"
#include "QDspBlock.hpp"
#include "QHighPass.hpp"
#include "QLowPass.hpp"
#include "QPeq.hpp"
#include "QPhase.hpp"
#include "QDelay.hpp"
#include "QLowShelv.hpp"
#include "QHighShelv.hpp"
#include "QInputSelect.hpp"
#include "QOutputSelect.hpp"
#include "QCrossover.hpp"

#include "HomeCinema71_IC_1_PARAM.h"

using namespace Vektorraum;

//==============================================================================
/*! Constructor
 *
 */
CPlugInHomeCinema71::CPlugInHomeCinema71( tfloat samplerate )
{
  fs = samplerate;

  //----------------------------------------------------------------------------
  //--- Init frequency vector
  //----------------------------------------------------------------------------
  tfloat fstart = 1.0;
  tfloat fstop = 20000.0;
  freq = pow( 10.0, linspace( log10(fstart), log10(fstop), 2048 ) );

}

//==============================================================================
/*! Destructor
 *
 */
CPlugInHomeCinema71::~CPlugInHomeCinema71( void )
{

}

//==============================================================================
/*!
 *
 */
tDspChannel CPlugInHomeCinema71::getGuiForChannel( unsigned int chn, tfloat fs, CFreeDspAurora* ptrdsp, QWidget* parent )
{
  tDspChannel dspChannel;

  QInputSelect* input;
  QLowShelv* lshelv;
  QPeq* peq01;
  QPeq* peq02;
  QPeq* peq03;
  QPeq* peq04;
  QPeq* peq05;
  QPeq* peq06;
  QPeq* peq07;
  QPeq* peq08;
  QPeq* peq09;
  QPeq* peq10;
  QHighShelv* hshelv;
  QLowPass* lp;
  QPhase* phase;
  QDelay* dly;
  QGain* gain = nullptr;
  QOutputSelect* output;
  QCrossover* xo;

  dsp = ptrdsp;

  QHBoxLayout* layout = new QHBoxLayout;
  QChannel* channel = new QChannel;

  if( chn == 0 )
  {
    //--------------------------------------------------------------------------
    //--- Channel 1
    dspChannel.name = QString( "Front Left" );

    input = new QInputSelect( 0, 
                              MOD_INPUTSELECT_1_NX1_1_ANALOG_ALG0_MONOMUXSIGMA300NS9INDEX_ADDR,
                              MOD_INPUTSELECT_1_NX1_1_UAC_ALG0_MONOMUXSIGMA300NS10INDEX_ADDR, 
                              MOD_INPUTSELECT_1_NX1_1_ESP32_ALG0_MONOMUXSIGMA300NS11INDEX_ADDR, 
                              MOD_INPUTSELECT_1_NX1_1_EXP_ALG0_MONOMUXSIGMA300NS12INDEX_ADDR, 
                              MOD_INPUTSELECT_1_NX1_1_SPDIF_ALG0_MONOMUXSIGMA300NS13INDEX_ADDR,
                              MOD_INPUTSELECT_1_NX1_1_ALG0_MONOMUXSIGMA300NS14INDEX_ADDR, 
                              ptrdsp, channel );
    layout->addWidget( input );
    channel->addDspBlock( input );
    channel->setName( dspChannel.name );

    lshelv = new QLowShelv( 0.0, 100.0, 1.0,
                            MOD_LOWSHELV1_ALG0_STAGE0_B2_ADDR, MOD_LOWSHELV1_ALG0_STAGE0_B1_ADDR, MOD_LOWSHELV1_ALG0_STAGE0_B0_ADDR,
                            MOD_LOWSHELV1_ALG0_STAGE0_A2_ADDR, MOD_LOWSHELV1_ALG0_STAGE0_A1_ADDR,
                            fs,
                            ptrdsp,
                            channel );
    layout->addWidget( lshelv );
    channel->addDspBlock( lshelv );

    peq01 = new QPeq( 0.0, 1000.0, 1.0,
                      MOD_PARAMEQ1_ALG0_STAGE0_B2_ADDR, MOD_PARAMEQ1_ALG0_STAGE0_B1_ADDR, MOD_PARAMEQ1_ALG0_STAGE0_B0_ADDR,
                      MOD_PARAMEQ1_ALG0_STAGE0_A2_ADDR, MOD_PARAMEQ1_ALG0_STAGE0_A1_ADDR,
                      fs,
                      ptrdsp,
                      channel );
    layout->addWidget( peq01 );
    channel->addDspBlock( peq01 );

    peq02 = new QPeq( 0.0, 2000.0, 2.0,
                      MOD_PARAMEQ1_ALG0_STAGE1_B2_ADDR, MOD_PARAMEQ1_ALG0_STAGE1_B1_ADDR, MOD_PARAMEQ1_ALG0_STAGE1_B0_ADDR,
                      MOD_PARAMEQ1_ALG0_STAGE1_A2_ADDR, MOD_PARAMEQ1_ALG0_STAGE1_A1_ADDR,
                      fs,
                      ptrdsp,
                      channel );
    layout->addWidget( peq02 );
    channel->addDspBlock( peq02 );

    peq03 = new QPeq( 0.0, 3000.0, 2.0,
                      MOD_PARAMEQ1_ALG0_STAGE2_B2_ADDR, MOD_PARAMEQ1_ALG0_STAGE2_B1_ADDR, MOD_PARAMEQ1_ALG0_STAGE2_B0_ADDR,
                      MOD_PARAMEQ1_ALG0_STAGE2_A2_ADDR, MOD_PARAMEQ1_ALG0_STAGE2_A1_ADDR,
                      fs,
                      ptrdsp,
                      channel );
    layout->addWidget( peq03 );
    channel->addDspBlock( peq03 );

    peq04 = new QPeq( 0.0, 4000.0, 2.0,
                      MOD_PARAMEQ1_ALG0_STAGE3_B2_ADDR, MOD_PARAMEQ1_ALG0_STAGE3_B1_ADDR, MOD_PARAMEQ1_ALG0_STAGE3_B0_ADDR,
                      MOD_PARAMEQ1_ALG0_STAGE3_A2_ADDR, MOD_PARAMEQ1_ALG0_STAGE3_A1_ADDR,
                      fs,
                      ptrdsp,
                      channel );
    layout->addWidget( peq04 );
    channel->addDspBlock( peq04 );

    peq05 = new QPeq( 0.0, 5000.0, 2.0,
                      MOD_PARAMEQ1_ALG0_STAGE4_B2_ADDR, MOD_PARAMEQ1_ALG0_STAGE4_B1_ADDR, MOD_PARAMEQ1_ALG0_STAGE4_B0_ADDR,
                      MOD_PARAMEQ1_ALG0_STAGE4_A2_ADDR, MOD_PARAMEQ1_ALG0_STAGE4_A1_ADDR,
                      fs,
                      ptrdsp,
                      channel );
    layout->addWidget( peq05 );
    channel->addDspBlock( peq05 );

    peq06 = new QPeq( 0.0, 6000.0, 2.0,
                      MOD_PARAMEQ1_ALG0_STAGE5_B2_ADDR, MOD_PARAMEQ1_ALG0_STAGE5_B1_ADDR, MOD_PARAMEQ1_ALG0_STAGE5_B0_ADDR,
                      MOD_PARAMEQ1_ALG0_STAGE5_A2_ADDR, MOD_PARAMEQ1_ALG0_STAGE5_A1_ADDR,
                      fs,
                      ptrdsp,
                      channel );
    layout->addWidget( peq06 );
    channel->addDspBlock( peq06 );

    peq07 = new QPeq( 0.0, 7000.0, 2.0,
                      MOD_PARAMEQ1_ALG0_STAGE6_B2_ADDR, MOD_PARAMEQ1_ALG0_STAGE6_B1_ADDR, MOD_PARAMEQ1_ALG0_STAGE6_B0_ADDR,
                      MOD_PARAMEQ1_ALG0_STAGE6_A2_ADDR, MOD_PARAMEQ1_ALG0_STAGE6_A1_ADDR,
                      fs,
                      ptrdsp,
                      channel );
    layout->addWidget( peq07 );
    channel->addDspBlock( peq07 );

    peq08 = new QPeq( 0.0, 8000.0, 2.0,
                      MOD_PARAMEQ1_ALG0_STAGE7_B2_ADDR, MOD_PARAMEQ1_ALG0_STAGE7_B1_ADDR, MOD_PARAMEQ1_ALG0_STAGE7_B0_ADDR,
                      MOD_PARAMEQ1_ALG0_STAGE7_A2_ADDR, MOD_PARAMEQ1_ALG0_STAGE7_A1_ADDR,
                      fs,
                      ptrdsp,
                      channel );
    layout->addWidget( peq08 );
    channel->addDspBlock( peq08 );

    peq09 = new QPeq( 0.0, 9000.0, 2.0,
                      MOD_PARAMEQ1_ALG0_STAGE8_B2_ADDR, MOD_PARAMEQ1_ALG0_STAGE8_B1_ADDR, MOD_PARAMEQ1_ALG0_STAGE8_B0_ADDR,
                      MOD_PARAMEQ1_ALG0_STAGE8_A2_ADDR, MOD_PARAMEQ1_ALG0_STAGE8_A1_ADDR,
                      fs,
                      ptrdsp,
                      channel );
    layout->addWidget( peq09 );
    channel->addDspBlock( peq09 );

    peq10 = new QPeq( 0.0, 10000.0, 2.0,
                      MOD_PARAMEQ1_ALG0_STAGE9_B2_ADDR, MOD_PARAMEQ1_ALG0_STAGE9_B1_ADDR, MOD_PARAMEQ1_ALG0_STAGE9_B0_ADDR,
                      MOD_PARAMEQ1_ALG0_STAGE9_A2_ADDR, MOD_PARAMEQ1_ALG0_STAGE9_A1_ADDR,
                      fs,
                      ptrdsp,
                      channel );
    layout->addWidget( peq10 );
    channel->addDspBlock( peq10 );

    hshelv = new QHighShelv( 0.0, 5000.0, 1.0,
                            MOD_HIGHSHELV1_ALG0_STAGE0_B2_ADDR, MOD_HIGHSHELV1_ALG0_STAGE0_B1_ADDR, MOD_HIGHSHELV1_ALG0_STAGE0_B0_ADDR,
                            MOD_HIGHSHELV1_ALG0_STAGE0_A2_ADDR, MOD_HIGHSHELV1_ALG0_STAGE0_A1_ADDR,
                            fs,
                            ptrdsp,
                            channel );
    layout->addWidget( hshelv );
    channel->addDspBlock( hshelv );

    xo = new QCrossover( QCrossover::kButterworth12, 100.0,
                         QCrossover::kButterworth12, 100.0,
                         MOD_HP1_1_ALG0_STAGE0_B2_ADDR, MOD_HP1_1_ALG0_STAGE0_B1_ADDR, MOD_HP1_1_ALG0_STAGE0_B0_ADDR,
                         MOD_HP1_1_ALG0_STAGE0_A2_ADDR, MOD_HP1_1_ALG0_STAGE0_A1_ADDR,
                         MOD_HP1_2_ALG0_STAGE0_B2_ADDR, MOD_HP1_2_ALG0_STAGE0_B1_ADDR, MOD_HP1_2_ALG0_STAGE0_B0_ADDR,
                         MOD_HP1_2_ALG0_STAGE0_A2_ADDR, MOD_HP1_2_ALG0_STAGE0_A1_ADDR,
                         MOD_HP1_3_ALG0_STAGE0_B2_ADDR, MOD_HP1_3_ALG0_STAGE0_B1_ADDR, MOD_HP1_3_ALG0_STAGE0_B0_ADDR,
                         MOD_HP1_3_ALG0_STAGE0_A2_ADDR, MOD_HP1_3_ALG0_STAGE0_A1_ADDR,
                         MOD_HP1_4_ALG0_STAGE0_B2_ADDR, MOD_HP1_4_ALG0_STAGE0_B1_ADDR, MOD_HP1_4_ALG0_STAGE0_B0_ADDR,
                         MOD_HP1_4_ALG0_STAGE0_A2_ADDR, MOD_HP1_4_ALG0_STAGE0_A1_ADDR,
                         MOD_LP1_1_ALG0_STAGE0_B2_ADDR, MOD_LP1_1_ALG0_STAGE0_B1_ADDR, MOD_LP1_1_ALG0_STAGE0_B0_ADDR,
                         MOD_LP1_1_ALG0_STAGE0_A2_ADDR, MOD_LP1_1_ALG0_STAGE0_A1_ADDR,
                         MOD_LP1_2_ALG0_STAGE0_B2_ADDR, MOD_LP1_2_ALG0_STAGE0_B1_ADDR, MOD_LP1_2_ALG0_STAGE0_B0_ADDR,
                         MOD_LP1_2_ALG0_STAGE0_A2_ADDR, MOD_LP1_2_ALG0_STAGE0_A1_ADDR,
                         MOD_LP1_3_ALG0_STAGE0_B2_ADDR, MOD_LP1_3_ALG0_STAGE0_B1_ADDR, MOD_LP1_3_ALG0_STAGE0_B0_ADDR,
                         MOD_LP1_3_ALG0_STAGE0_A2_ADDR, MOD_LP1_3_ALG0_STAGE0_A1_ADDR,
                         MOD_LP1_4_ALG0_STAGE0_B2_ADDR, MOD_LP1_4_ALG0_STAGE0_B1_ADDR, MOD_LP1_4_ALG0_STAGE0_B0_ADDR,
                         MOD_LP1_4_ALG0_STAGE0_A2_ADDR, MOD_LP1_4_ALG0_STAGE0_A1_ADDR,
                         fs,
                         ptrdsp,
                         channel );
    layout->addWidget( xo );
    channel->addDspBlock( xo );

    phase = new QPhase( 1000.0, 1.0,
                      MOD_PHASE1_ALG0_STAGE0_B2_ADDR, MOD_PHASE1_ALG0_STAGE0_B1_ADDR, MOD_PHASE1_ALG0_STAGE0_B0_ADDR,
                      MOD_PHASE1_ALG0_STAGE0_A2_ADDR, MOD_PHASE1_ALG0_STAGE0_A1_ADDR,
                      fs,
                      ptrdsp,
                      channel );
    layout->addWidget( phase );
    channel->addDspBlock( phase );
    
    dly = new QDelay( 0.0, fs, MOD_DELAY1_DELAYAMT_ADDR, ptrdsp, channel );
    layout->addWidget( dly );
    channel->addDspBlock( dly ); 

    gain = new QGain( 0.0, MOD_GAIN1_ALG0_TARGET_ADDR, ptrdsp, channel );
    layout->addWidget( gain );
    channel->addDspBlock( gain );
 
    output = new QOutputSelect( 1, 0, ptrdsp, channel );
    layout->addWidget( output );
    channel->addDspBlock( output );

    QObject::connect( lshelv, SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );
    QObject::connect( peq01,  SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );
    QObject::connect( peq02,  SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );
    QObject::connect( peq03,  SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );
    QObject::connect( peq04,  SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );
    QObject::connect( peq05,  SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );
    QObject::connect( peq06,  SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );
    QObject::connect( peq07,  SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );
    QObject::connect( peq08,  SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );
    QObject::connect( peq09,  SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );
    QObject::connect( peq10,  SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );
    QObject::connect( hshelv, SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );
    QObject::connect( xo,     SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );
    QObject::connect( phase,  SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );
    QObject::connect( dly,    SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );
    QObject::connect( gain,   SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );
    QObject::connect( output, SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );

    QObject::connect( peq01,  SIGNAL(importRewPeqs( QWidget* )), parent, SLOT(importRewPeqs( QWidget* )) );
    QObject::connect( peq02,  SIGNAL(importRewPeqs( QWidget* )), parent, SLOT(importRewPeqs( QWidget* )) );
    QObject::connect( peq03,  SIGNAL(importRewPeqs( QWidget* )), parent, SLOT(importRewPeqs( QWidget* )) );
    QObject::connect( peq04,  SIGNAL(importRewPeqs( QWidget* )), parent, SLOT(importRewPeqs( QWidget* )) );
    QObject::connect( peq05,  SIGNAL(importRewPeqs( QWidget* )), parent, SLOT(importRewPeqs( QWidget* )) );
    QObject::connect( peq06,  SIGNAL(importRewPeqs( QWidget* )), parent, SLOT(importRewPeqs( QWidget* )) );
    QObject::connect( peq07,  SIGNAL(importRewPeqs( QWidget* )), parent, SLOT(importRewPeqs( QWidget* )) );
    QObject::connect( peq08,  SIGNAL(importRewPeqs( QWidget* )), parent, SLOT(importRewPeqs( QWidget* )) );
    QObject::connect( peq09,  SIGNAL(importRewPeqs( QWidget* )), parent, SLOT(importRewPeqs( QWidget* )) );
    QObject::connect( peq10,  SIGNAL(importRewPeqs( QWidget* )), parent, SLOT(importRewPeqs( QWidget* )) );

    listChannels.append( channel );
  }
  else if( chn == 1 )
  {
    //--------------------------------------------------------------------------
    //--- Channel 2
    dspChannel.name = QString( "Front Right" );

    input = new QInputSelect( 1, 
                              MOD_INPUTSELECT_2_NX1_1_ANALOG_ALG0_MONOMUXSIGMA300NS1INDEX_ADDR,
                              MOD_INPUTSELECT_2_NX1_1_UAC_ALG0_MONOMUXSIGMA300NS2INDEX_ADDR, 
                              MOD_INPUTSELECT_2_NX1_1_ESP32_ALG0_MONOMUXSIGMA300NS3INDEX_ADDR, 
                              MOD_INPUTSELECT_2_NX1_1_EXP_ALG0_MONOMUXSIGMA300NS4INDEX_ADDR, 
                              MOD_INPUTSELECT_2_NX1_1_SPDIF_ALG0_MONOMUXSIGMA300NS5INDEX_ADDR,
                              MOD_INPUTSELECT_2_NX1_1_ALG0_MONOMUXSIGMA300NS6INDEX_ADDR, 
                              ptrdsp, channel );
    layout->addWidget( input );
    channel->addDspBlock( input );
    channel->setName( dspChannel.name );

    lshelv = new QLowShelv( 0.0, 100.0, 1.0,
                            MOD_LOWSHELV2_ALG0_STAGE0_B2_ADDR, MOD_LOWSHELV2_ALG0_STAGE0_B1_ADDR, MOD_LOWSHELV2_ALG0_STAGE0_B0_ADDR,
                            MOD_LOWSHELV2_ALG0_STAGE0_A2_ADDR, MOD_LOWSHELV2_ALG0_STAGE0_A1_ADDR,
                            fs,
                            ptrdsp,
                            channel );
    layout->addWidget( lshelv );
    channel->addDspBlock( lshelv );

    peq01 = new QPeq( 0.0, 1000.0, 1.0,
                      MOD_PARAMEQ2_ALG0_STAGE0_B2_ADDR, MOD_PARAMEQ2_ALG0_STAGE0_B1_ADDR, MOD_PARAMEQ2_ALG0_STAGE0_B0_ADDR,
                      MOD_PARAMEQ2_ALG0_STAGE0_A2_ADDR, MOD_PARAMEQ2_ALG0_STAGE0_A1_ADDR,
                      fs,
                      ptrdsp,
                      channel );
    layout->addWidget( peq01 );
    channel->addDspBlock( peq01 );

    peq02 = new QPeq( 0.0, 2000.0, 2.0,
                      MOD_PARAMEQ2_ALG0_STAGE1_B2_ADDR, MOD_PARAMEQ2_ALG0_STAGE1_B1_ADDR, MOD_PARAMEQ2_ALG0_STAGE1_B0_ADDR,
                      MOD_PARAMEQ2_ALG0_STAGE1_A2_ADDR, MOD_PARAMEQ2_ALG0_STAGE1_A1_ADDR,
                      fs,
                      ptrdsp,
                      channel );
    layout->addWidget( peq02 );
    channel->addDspBlock( peq02 );

    peq03 = new QPeq( 0.0, 3000.0, 2.0,
                      MOD_PARAMEQ2_ALG0_STAGE2_B2_ADDR, MOD_PARAMEQ2_ALG0_STAGE2_B1_ADDR, MOD_PARAMEQ2_ALG0_STAGE2_B0_ADDR,
                      MOD_PARAMEQ2_ALG0_STAGE2_A2_ADDR, MOD_PARAMEQ2_ALG0_STAGE2_A1_ADDR,
                      fs,
                      ptrdsp,
                      channel );
    layout->addWidget( peq03 );
    channel->addDspBlock( peq03 );

    peq04 = new QPeq( 0.0, 4000.0, 2.0,
                      MOD_PARAMEQ2_ALG0_STAGE3_B2_ADDR, MOD_PARAMEQ2_ALG0_STAGE3_B1_ADDR, MOD_PARAMEQ2_ALG0_STAGE3_B0_ADDR,
                      MOD_PARAMEQ2_ALG0_STAGE3_A2_ADDR, MOD_PARAMEQ2_ALG0_STAGE3_A1_ADDR,
                      fs,
                      ptrdsp,
                      channel );
    layout->addWidget( peq04 );
    channel->addDspBlock( peq04 );

    peq05 = new QPeq( 0.0, 5000.0, 2.0,
                      MOD_PARAMEQ2_ALG0_STAGE4_B2_ADDR, MOD_PARAMEQ2_ALG0_STAGE4_B1_ADDR, MOD_PARAMEQ2_ALG0_STAGE4_B0_ADDR,
                      MOD_PARAMEQ2_ALG0_STAGE4_A2_ADDR, MOD_PARAMEQ2_ALG0_STAGE4_A1_ADDR,
                      fs,
                      ptrdsp,
                      channel );
    layout->addWidget( peq05 );
    channel->addDspBlock( peq05 );

    peq06 = new QPeq( 0.0, 6000.0, 2.0,
                      MOD_PARAMEQ2_ALG0_STAGE5_B2_ADDR, MOD_PARAMEQ2_ALG0_STAGE5_B1_ADDR, MOD_PARAMEQ2_ALG0_STAGE5_B0_ADDR,
                      MOD_PARAMEQ2_ALG0_STAGE5_A2_ADDR, MOD_PARAMEQ2_ALG0_STAGE5_A1_ADDR,
                      fs,
                      ptrdsp,
                      channel );
    layout->addWidget( peq06 );
    channel->addDspBlock( peq06 );

    peq07 = new QPeq( 0.0, 7000.0, 2.0,
                      MOD_PARAMEQ2_ALG0_STAGE6_B2_ADDR, MOD_PARAMEQ2_ALG0_STAGE6_B1_ADDR, MOD_PARAMEQ2_ALG0_STAGE6_B0_ADDR,
                      MOD_PARAMEQ2_ALG0_STAGE6_A2_ADDR, MOD_PARAMEQ2_ALG0_STAGE6_A1_ADDR,
                      fs,
                      ptrdsp,
                      channel );
    layout->addWidget( peq07 );
    channel->addDspBlock( peq07 );

    peq08 = new QPeq( 0.0, 8000.0, 2.0,
                      MOD_PARAMEQ2_ALG0_STAGE7_B2_ADDR, MOD_PARAMEQ2_ALG0_STAGE7_B1_ADDR, MOD_PARAMEQ2_ALG0_STAGE7_B0_ADDR,
                      MOD_PARAMEQ2_ALG0_STAGE7_A2_ADDR, MOD_PARAMEQ2_ALG0_STAGE7_A1_ADDR,
                      fs,
                      ptrdsp,
                      channel );
    layout->addWidget( peq08 );
    channel->addDspBlock( peq08 );

    peq09 = new QPeq( 0.0, 9000.0, 2.0,
                      MOD_PARAMEQ2_ALG0_STAGE8_B2_ADDR, MOD_PARAMEQ2_ALG0_STAGE8_B1_ADDR, MOD_PARAMEQ2_ALG0_STAGE8_B0_ADDR,
                      MOD_PARAMEQ2_ALG0_STAGE8_A2_ADDR, MOD_PARAMEQ2_ALG0_STAGE8_A1_ADDR,
                      fs,
                      ptrdsp,
                      channel );
    layout->addWidget( peq09 );
    channel->addDspBlock( peq09 );

    peq10 = new QPeq( 0.0, 10000.0, 2.0,
                      MOD_PARAMEQ2_ALG0_STAGE9_B2_ADDR, MOD_PARAMEQ2_ALG0_STAGE9_B1_ADDR, MOD_PARAMEQ2_ALG0_STAGE9_B0_ADDR,
                      MOD_PARAMEQ2_ALG0_STAGE9_A2_ADDR, MOD_PARAMEQ2_ALG0_STAGE9_A1_ADDR,
                      fs,
                      ptrdsp,
                      channel );
    layout->addWidget( peq10 );
    channel->addDspBlock( peq10 );

    hshelv = new QHighShelv( 0.0, 5000.0, 1.0,
                           MOD_HIGHSHELV2_ALG0_STAGE0_B2_ADDR, MOD_HIGHSHELV2_ALG0_STAGE0_B1_ADDR, MOD_HIGHSHELV2_ALG0_STAGE0_B0_ADDR,
                           MOD_HIGHSHELV2_ALG0_STAGE0_A2_ADDR, MOD_HIGHSHELV2_ALG0_STAGE0_A1_ADDR,
                           fs,
                           ptrdsp,
                           channel );
    layout->addWidget( hshelv );
    channel->addDspBlock( hshelv );

    xo = new QCrossover( QCrossover::kButterworth12, 100.0,
                         QCrossover::kButterworth12, 100.0,
                         MOD_HP2_1_ALG0_STAGE0_B2_ADDR, MOD_HP2_1_ALG0_STAGE0_B1_ADDR, MOD_HP2_1_ALG0_STAGE0_B0_ADDR,
                         MOD_HP2_1_ALG0_STAGE0_A2_ADDR, MOD_HP2_1_ALG0_STAGE0_A1_ADDR,
                         MOD_HP2_2_ALG0_STAGE0_B2_ADDR, MOD_HP2_2_ALG0_STAGE0_B1_ADDR, MOD_HP2_2_ALG0_STAGE0_B0_ADDR,
                         MOD_HP2_2_ALG0_STAGE0_A2_ADDR, MOD_HP2_2_ALG0_STAGE0_A1_ADDR,
                         MOD_HP2_3_ALG0_STAGE0_B2_ADDR, MOD_HP2_3_ALG0_STAGE0_B1_ADDR, MOD_HP2_3_ALG0_STAGE0_B0_ADDR,
                         MOD_HP2_3_ALG0_STAGE0_A2_ADDR, MOD_HP2_3_ALG0_STAGE0_A1_ADDR,
                         MOD_HP2_4_ALG0_STAGE0_B2_ADDR, MOD_HP2_4_ALG0_STAGE0_B1_ADDR, MOD_HP2_4_ALG0_STAGE0_B0_ADDR,
                         MOD_HP2_4_ALG0_STAGE0_A2_ADDR, MOD_HP2_4_ALG0_STAGE0_A1_ADDR,
                         MOD_LP2_1_ALG0_STAGE0_B2_ADDR, MOD_LP2_1_ALG0_STAGE0_B1_ADDR, MOD_LP2_1_ALG0_STAGE0_B0_ADDR,
                         MOD_LP2_1_ALG0_STAGE0_A2_ADDR, MOD_LP2_1_ALG0_STAGE0_A1_ADDR,
                         MOD_LP2_2_ALG0_STAGE0_B2_ADDR, MOD_LP2_2_ALG0_STAGE0_B1_ADDR, MOD_LP2_2_ALG0_STAGE0_B0_ADDR,
                         MOD_LP2_2_ALG0_STAGE0_A2_ADDR, MOD_LP2_2_ALG0_STAGE0_A1_ADDR,
                         MOD_LP2_3_ALG0_STAGE0_B2_ADDR, MOD_LP2_3_ALG0_STAGE0_B1_ADDR, MOD_LP2_3_ALG0_STAGE0_B0_ADDR,
                         MOD_LP2_3_ALG0_STAGE0_A2_ADDR, MOD_LP2_3_ALG0_STAGE0_A1_ADDR,
                         MOD_LP2_4_ALG0_STAGE0_B2_ADDR, MOD_LP2_4_ALG0_STAGE0_B1_ADDR, MOD_LP2_4_ALG0_STAGE0_B0_ADDR,
                         MOD_LP2_4_ALG0_STAGE0_A2_ADDR, MOD_LP2_4_ALG0_STAGE0_A1_ADDR,
                         fs,
                         ptrdsp,
                         channel );
    layout->addWidget( xo );
    channel->addDspBlock( xo );

    phase = new QPhase( 1000.0, 1.0,
                        MOD_PHASE2_ALG0_STAGE0_B2_ADDR, MOD_PHASE2_ALG0_STAGE0_B1_ADDR, MOD_PHASE2_ALG0_STAGE0_B0_ADDR,
                        MOD_PHASE2_ALG0_STAGE0_A2_ADDR, MOD_PHASE2_ALG0_STAGE0_A1_ADDR,
                        fs,
                        ptrdsp,
                        channel );
    layout->addWidget( phase );
    channel->addDspBlock( phase );

    dly = new QDelay( 0.0, fs, MOD_DELAY2_DELAYAMT_ADDR, ptrdsp, channel );
    layout->addWidget( dly );
    channel->addDspBlock( dly );

    gain = new QGain( 0.0, MOD_GAIN2_ALG0_TARGET_ADDR, ptrdsp, channel );
    layout->addWidget( gain );
    channel->addDspBlock( gain );

    output = new QOutputSelect( 1, 0, ptrdsp, channel );
    layout->addWidget( output );
    channel->addDspBlock( output );

    QObject::connect( lshelv, SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );
    QObject::connect( peq01,  SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );
    QObject::connect( peq02,  SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );
    QObject::connect( peq03,  SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );
    QObject::connect( peq04,  SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );
    QObject::connect( peq05,  SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );
    QObject::connect( peq06,  SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );
    QObject::connect( peq07,  SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );
    QObject::connect( peq08,  SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );
    QObject::connect( peq09,  SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );
    QObject::connect( peq10,  SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );
    QObject::connect( hshelv, SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );
    QObject::connect( xo,     SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );
    QObject::connect( phase,  SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );
    QObject::connect( dly,    SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );
    QObject::connect( gain,   SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );
    QObject::connect( output, SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );

    QObject::connect( peq01,  SIGNAL(importRewPeqs( QWidget* )), parent, SLOT(importRewPeqs( QWidget* )) );
    QObject::connect( peq02,  SIGNAL(importRewPeqs( QWidget* )), parent, SLOT(importRewPeqs( QWidget* )) );
    QObject::connect( peq03,  SIGNAL(importRewPeqs( QWidget* )), parent, SLOT(importRewPeqs( QWidget* )) );
    QObject::connect( peq04,  SIGNAL(importRewPeqs( QWidget* )), parent, SLOT(importRewPeqs( QWidget* )) );
    QObject::connect( peq05,  SIGNAL(importRewPeqs( QWidget* )), parent, SLOT(importRewPeqs( QWidget* )) );
    QObject::connect( peq06,  SIGNAL(importRewPeqs( QWidget* )), parent, SLOT(importRewPeqs( QWidget* )) );
    QObject::connect( peq07,  SIGNAL(importRewPeqs( QWidget* )), parent, SLOT(importRewPeqs( QWidget* )) );
    QObject::connect( peq08,  SIGNAL(importRewPeqs( QWidget* )), parent, SLOT(importRewPeqs( QWidget* )) );
    QObject::connect( peq09,  SIGNAL(importRewPeqs( QWidget* )), parent, SLOT(importRewPeqs( QWidget* )) );
    QObject::connect( peq10,  SIGNAL(importRewPeqs( QWidget* )), parent, SLOT(importRewPeqs( QWidget* )) );

    listChannels.append( channel );
  }
  else if( chn == 2 )
  {
    //--------------------------------------------------------------------------
    //--- Channel 3
    dspChannel.name = QString( "Front Center" );

    input = new QInputSelect( 2, 
                              MOD_INPUTSELECT_3_NX1_1_ANALOG_ALG0_MONOMUXSIGMA300NS7INDEX_ADDR,
                              MOD_INPUTSELECT_3_NX1_1_UAC_ALG0_MONOMUXSIGMA300NS8INDEX_ADDR, 
                              MOD_INPUTSELECT_3_NX1_1_ESP32_ALG0_MONOMUXSIGMA300NS15INDEX_ADDR, 
                              MOD_INPUTSELECT_3_NX1_1_EXP_ALG0_MONOMUXSIGMA300NS16INDEX_ADDR, 
                              MOD_INPUTSELECT_3_NX1_1_SPDIF_ALG0_MONOMUXSIGMA300NS17INDEX_ADDR,
                              MOD_INPUTSELECT_3_NX1_1_ALG0_MONOMUXSIGMA300NS18INDEX_ADDR, 
                              ptrdsp, channel );
    layout->addWidget( input );
    channel->addDspBlock( input );
    channel->setName( dspChannel.name );

    lshelv = new QLowShelv( 0.0, 100.0, 1.0,
                            MOD_LOWSHELV3_ALG0_STAGE0_B2_ADDR, MOD_LOWSHELV3_ALG0_STAGE0_B1_ADDR, MOD_LOWSHELV3_ALG0_STAGE0_B0_ADDR,
                            MOD_LOWSHELV3_ALG0_STAGE0_A2_ADDR, MOD_LOWSHELV3_ALG0_STAGE0_A1_ADDR,
                            fs,
                            ptrdsp,
                            channel );
    layout->addWidget( lshelv );
    channel->addDspBlock( lshelv );

    peq01 = new QPeq( 0.0, 1000.0, 1.0,
                      MOD_PARAMEQ3_ALG0_STAGE0_B2_ADDR, MOD_PARAMEQ3_ALG0_STAGE0_B1_ADDR, MOD_PARAMEQ3_ALG0_STAGE0_B0_ADDR,
                      MOD_PARAMEQ3_ALG0_STAGE0_A2_ADDR, MOD_PARAMEQ3_ALG0_STAGE0_A1_ADDR,
                      fs,
                      ptrdsp,
                      channel );
    layout->addWidget( peq01 );
    channel->addDspBlock( peq01 );

    peq02 = new QPeq( 0.0, 2000.0, 2.0,
                      MOD_PARAMEQ3_ALG0_STAGE1_B2_ADDR, MOD_PARAMEQ3_ALG0_STAGE1_B1_ADDR, MOD_PARAMEQ3_ALG0_STAGE1_B0_ADDR,
                      MOD_PARAMEQ3_ALG0_STAGE1_A2_ADDR, MOD_PARAMEQ3_ALG0_STAGE1_A1_ADDR,
                      fs,
                      ptrdsp,
                      channel );
    layout->addWidget( peq02 );
    channel->addDspBlock( peq02 );

    peq03 = new QPeq( 0.0, 3000.0, 2.0,
                      MOD_PARAMEQ3_ALG0_STAGE2_B2_ADDR, MOD_PARAMEQ3_ALG0_STAGE2_B1_ADDR, MOD_PARAMEQ3_ALG0_STAGE2_B0_ADDR,
                      MOD_PARAMEQ3_ALG0_STAGE2_A2_ADDR, MOD_PARAMEQ3_ALG0_STAGE2_A1_ADDR,
                      fs,
                      ptrdsp,
                      channel );
    layout->addWidget( peq03 );
    channel->addDspBlock( peq03 );

    peq04 = new QPeq( 0.0, 4000.0, 2.0,
                      MOD_PARAMEQ3_ALG0_STAGE3_B2_ADDR, MOD_PARAMEQ3_ALG0_STAGE3_B1_ADDR, MOD_PARAMEQ3_ALG0_STAGE3_B0_ADDR,
                      MOD_PARAMEQ3_ALG0_STAGE3_A2_ADDR, MOD_PARAMEQ3_ALG0_STAGE3_A1_ADDR,
                      fs,
                      ptrdsp,
                      channel );
    layout->addWidget( peq04 );
    channel->addDspBlock( peq04 );

    peq05 = new QPeq( 0.0, 5000.0, 2.0,
                      MOD_PARAMEQ3_ALG0_STAGE4_B2_ADDR, MOD_PARAMEQ3_ALG0_STAGE4_B1_ADDR, MOD_PARAMEQ3_ALG0_STAGE4_B0_ADDR,
                      MOD_PARAMEQ3_ALG0_STAGE4_A2_ADDR, MOD_PARAMEQ3_ALG0_STAGE4_A1_ADDR,
                      fs,
                      ptrdsp,
                      channel );
    layout->addWidget( peq05 );
    channel->addDspBlock( peq05 );

    peq06 = new QPeq( 0.0, 6000.0, 2.0,
                      MOD_PARAMEQ3_ALG0_STAGE5_B2_ADDR, MOD_PARAMEQ3_ALG0_STAGE5_B1_ADDR, MOD_PARAMEQ3_ALG0_STAGE5_B0_ADDR,
                      MOD_PARAMEQ3_ALG0_STAGE5_A2_ADDR, MOD_PARAMEQ3_ALG0_STAGE5_A1_ADDR,
                      fs,
                      ptrdsp,
                      channel );
    layout->addWidget( peq06 );
    channel->addDspBlock( peq06 );

    peq07 = new QPeq( 0.0, 7000.0, 2.0,
                      MOD_PARAMEQ3_ALG0_STAGE6_B2_ADDR, MOD_PARAMEQ3_ALG0_STAGE6_B1_ADDR, MOD_PARAMEQ3_ALG0_STAGE6_B0_ADDR,
                      MOD_PARAMEQ3_ALG0_STAGE6_A2_ADDR, MOD_PARAMEQ3_ALG0_STAGE6_A1_ADDR,
                      fs,
                      ptrdsp,
                      channel );
    layout->addWidget( peq07 );
    channel->addDspBlock( peq07 );

    peq08 = new QPeq( 0.0, 8000.0, 2.0,
                      MOD_PARAMEQ3_ALG0_STAGE7_B2_ADDR, MOD_PARAMEQ3_ALG0_STAGE7_B1_ADDR, MOD_PARAMEQ3_ALG0_STAGE7_B0_ADDR,
                      MOD_PARAMEQ3_ALG0_STAGE7_A2_ADDR, MOD_PARAMEQ3_ALG0_STAGE7_A1_ADDR,
                      fs,
                      ptrdsp,
                      channel );
    layout->addWidget( peq08 );
    channel->addDspBlock( peq08 );

    peq09 = new QPeq( 0.0, 9000.0, 2.0,
                      MOD_PARAMEQ3_ALG0_STAGE8_B2_ADDR, MOD_PARAMEQ3_ALG0_STAGE8_B1_ADDR, MOD_PARAMEQ3_ALG0_STAGE8_B0_ADDR,
                      MOD_PARAMEQ3_ALG0_STAGE8_A2_ADDR, MOD_PARAMEQ3_ALG0_STAGE8_A1_ADDR,
                      fs,
                      ptrdsp,
                      channel );
    layout->addWidget( peq09 );
    channel->addDspBlock( peq09 );

    peq10 = new QPeq( 0.0, 10000.0, 2.0,
                      MOD_PARAMEQ3_ALG0_STAGE9_B2_ADDR, MOD_PARAMEQ3_ALG0_STAGE9_B1_ADDR, MOD_PARAMEQ3_ALG0_STAGE9_B0_ADDR,
                      MOD_PARAMEQ3_ALG0_STAGE9_A2_ADDR, MOD_PARAMEQ3_ALG0_STAGE9_A1_ADDR,
                      fs,
                      ptrdsp,
                      channel );
    layout->addWidget( peq10 );
    channel->addDspBlock( peq10 );

    hshelv = new QHighShelv( 0.0, 5000.0, 1.0,
                            MOD_HIGHSHELV3_ALG0_STAGE0_B2_ADDR, MOD_HIGHSHELV3_ALG0_STAGE0_B1_ADDR, MOD_HIGHSHELV3_ALG0_STAGE0_B0_ADDR,
                            MOD_HIGHSHELV3_ALG0_STAGE0_A2_ADDR, MOD_HIGHSHELV3_ALG0_STAGE0_A1_ADDR,
                            fs,
                            ptrdsp,
                            channel );
    layout->addWidget( hshelv );
    channel->addDspBlock( hshelv );

    xo = new QCrossover( QCrossover::kButterworth12, 100.0,
                         QCrossover::kButterworth12, 100.0,
                         MOD_HP3_1_ALG0_STAGE0_B2_ADDR, MOD_HP3_1_ALG0_STAGE0_B1_ADDR, MOD_HP3_1_ALG0_STAGE0_B0_ADDR,
                         MOD_HP3_1_ALG0_STAGE0_A2_ADDR, MOD_HP3_1_ALG0_STAGE0_A1_ADDR,
                         MOD_HP3_2_ALG0_STAGE0_B2_ADDR, MOD_HP3_2_ALG0_STAGE0_B1_ADDR, MOD_HP3_2_ALG0_STAGE0_B0_ADDR,
                         MOD_HP3_2_ALG0_STAGE0_A2_ADDR, MOD_HP3_2_ALG0_STAGE0_A1_ADDR,
                         MOD_HP3_3_ALG0_STAGE0_B2_ADDR, MOD_HP3_3_ALG0_STAGE0_B1_ADDR, MOD_HP3_3_ALG0_STAGE0_B0_ADDR,
                         MOD_HP3_3_ALG0_STAGE0_A2_ADDR, MOD_HP3_3_ALG0_STAGE0_A1_ADDR,
                         MOD_HP3_4_ALG0_STAGE0_B2_ADDR, MOD_HP3_4_ALG0_STAGE0_B1_ADDR, MOD_HP3_4_ALG0_STAGE0_B0_ADDR,
                         MOD_HP3_4_ALG0_STAGE0_A2_ADDR, MOD_HP3_4_ALG0_STAGE0_A1_ADDR,
                         MOD_LP3_1_ALG0_STAGE0_B2_ADDR, MOD_LP3_1_ALG0_STAGE0_B1_ADDR, MOD_LP3_1_ALG0_STAGE0_B0_ADDR,
                         MOD_LP3_1_ALG0_STAGE0_A2_ADDR, MOD_LP3_1_ALG0_STAGE0_A1_ADDR,
                         MOD_LP3_2_ALG0_STAGE0_B2_ADDR, MOD_LP3_2_ALG0_STAGE0_B1_ADDR, MOD_LP3_2_ALG0_STAGE0_B0_ADDR,
                         MOD_LP3_2_ALG0_STAGE0_A2_ADDR, MOD_LP3_2_ALG0_STAGE0_A1_ADDR,
                         MOD_LP3_3_ALG0_STAGE0_B2_ADDR, MOD_LP3_3_ALG0_STAGE0_B1_ADDR, MOD_LP3_3_ALG0_STAGE0_B0_ADDR,
                         MOD_LP3_3_ALG0_STAGE0_A2_ADDR, MOD_LP3_3_ALG0_STAGE0_A1_ADDR,
                         MOD_LP3_4_ALG0_STAGE0_B2_ADDR, MOD_LP3_4_ALG0_STAGE0_B1_ADDR, MOD_LP3_4_ALG0_STAGE0_B0_ADDR,
                         MOD_LP3_4_ALG0_STAGE0_A2_ADDR, MOD_LP3_4_ALG0_STAGE0_A1_ADDR,
                         fs,
                         ptrdsp,
                         channel );
    layout->addWidget( xo );
    channel->addDspBlock( xo );

    phase = new QPhase( 1000.0, 1.0,
                      MOD_PHASE3_ALG0_STAGE0_B2_ADDR, MOD_PHASE3_ALG0_STAGE0_B1_ADDR, MOD_PHASE3_ALG0_STAGE0_B0_ADDR,
                      MOD_PHASE3_ALG0_STAGE0_A2_ADDR, MOD_PHASE3_ALG0_STAGE0_A1_ADDR,
                      fs,
                      ptrdsp,
                      channel );
    layout->addWidget( phase );
    channel->addDspBlock( phase );

    dly = new QDelay( 0.0, 48000.0, MOD_DELAY3_DELAYAMT_ADDR, ptrdsp, channel );
    layout->addWidget( dly );
    channel->addDspBlock( dly );

    gain = new QGain( 0.0, MOD_GAIN3_ALG0_TARGET_ADDR, ptrdsp, channel );
    layout->addWidget( gain );
    channel->addDspBlock( gain );

    output = new QOutputSelect( 1, 0, ptrdsp, channel );
    layout->addWidget( output );
    channel->addDspBlock( output );

    QObject::connect( lshelv, SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );
    QObject::connect( peq01,  SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );
    QObject::connect( peq02,  SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );
    QObject::connect( peq03,  SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );
    QObject::connect( peq04,  SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );
    QObject::connect( peq05,  SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );
    QObject::connect( peq06,  SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );
    QObject::connect( peq07,  SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );
    QObject::connect( peq08,  SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );
    QObject::connect( peq09,  SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );
    QObject::connect( peq10,  SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );
    QObject::connect( hshelv, SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );
    QObject::connect( xo,     SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );
    QObject::connect( phase,  SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );
    QObject::connect( dly,    SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );
    QObject::connect( gain,   SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );
    QObject::connect( output, SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );

    QObject::connect( peq01,  SIGNAL(importRewPeqs( QWidget* )), parent, SLOT(importRewPeqs( QWidget* )) );
    QObject::connect( peq02,  SIGNAL(importRewPeqs( QWidget* )), parent, SLOT(importRewPeqs( QWidget* )) );
    QObject::connect( peq03,  SIGNAL(importRewPeqs( QWidget* )), parent, SLOT(importRewPeqs( QWidget* )) );
    QObject::connect( peq04,  SIGNAL(importRewPeqs( QWidget* )), parent, SLOT(importRewPeqs( QWidget* )) );
    QObject::connect( peq05,  SIGNAL(importRewPeqs( QWidget* )), parent, SLOT(importRewPeqs( QWidget* )) );
    QObject::connect( peq06,  SIGNAL(importRewPeqs( QWidget* )), parent, SLOT(importRewPeqs( QWidget* )) );
    QObject::connect( peq07,  SIGNAL(importRewPeqs( QWidget* )), parent, SLOT(importRewPeqs( QWidget* )) );
    QObject::connect( peq08,  SIGNAL(importRewPeqs( QWidget* )), parent, SLOT(importRewPeqs( QWidget* )) );
    QObject::connect( peq09,  SIGNAL(importRewPeqs( QWidget* )), parent, SLOT(importRewPeqs( QWidget* )) );
    QObject::connect( peq10,  SIGNAL(importRewPeqs( QWidget* )), parent, SLOT(importRewPeqs( QWidget* )) );

    listChannels.append( channel );
  }
  else if( chn == 3 )
  {
    //--------------------------------------------------------------------------
    //--- Channel 4
    dspChannel.name = QString( "Rear Left" );

    input = new QInputSelect( 3, 
                              MOD_INPUTSELECT_4_NX1_1_ANALOG_ALG0_MONOMUXSIGMA300NS19INDEX_ADDR,
                              MOD_INPUTSELECT_4_NX1_1_UAC_ALG0_MONOMUXSIGMA300NS20INDEX_ADDR, 
                              MOD_INPUTSELECT_4_NX1_1_ESP32_ALG0_MONOMUXSIGMA300NS21INDEX_ADDR, 
                              MOD_INPUTSELECT_4_NX1_1_EXP_ALG0_MONOMUXSIGMA300NS22INDEX_ADDR, 
                              MOD_INPUTSELECT_4_NX1_1_SPDIF_ALG0_MONOMUXSIGMA300NS23INDEX_ADDR,
                              MOD_INPUTSELECT_4_NX1_1_ALG0_MONOMUXSIGMA300NS24INDEX_ADDR, 
                              ptrdsp, channel );
    layout->addWidget( input );
    channel->addDspBlock( input );
    channel->setName( dspChannel.name );

    lshelv = new QLowShelv( 0.0, 100.0, 1.0,
                            MOD_LOWSHELV4_ALG0_STAGE0_B2_ADDR, MOD_LOWSHELV4_ALG0_STAGE0_B1_ADDR, MOD_LOWSHELV4_ALG0_STAGE0_B0_ADDR,
                            MOD_LOWSHELV4_ALG0_STAGE0_A2_ADDR, MOD_LOWSHELV4_ALG0_STAGE0_A1_ADDR,
                            fs,
                            ptrdsp,
                            channel );
    layout->addWidget( lshelv );
    channel->addDspBlock( lshelv );

    peq01 = new QPeq( 0.0, 1000.0, 1.0,
                      MOD_PARAMEQ4_ALG0_STAGE0_B2_ADDR, MOD_PARAMEQ4_ALG0_STAGE0_B1_ADDR, MOD_PARAMEQ4_ALG0_STAGE0_B0_ADDR,
                      MOD_PARAMEQ4_ALG0_STAGE0_A2_ADDR, MOD_PARAMEQ4_ALG0_STAGE0_A1_ADDR,
                      fs,
                      ptrdsp,
                      channel );
    layout->addWidget( peq01 );
    channel->addDspBlock( peq01 );

    peq02 = new QPeq( 0.0, 2000.0, 2.0,
                      MOD_PARAMEQ4_ALG0_STAGE1_B2_ADDR, MOD_PARAMEQ4_ALG0_STAGE1_B1_ADDR, MOD_PARAMEQ4_ALG0_STAGE1_B0_ADDR,
                      MOD_PARAMEQ4_ALG0_STAGE1_A2_ADDR, MOD_PARAMEQ4_ALG0_STAGE1_A1_ADDR,
                      fs,
                      ptrdsp,
                      channel );
    layout->addWidget( peq02 );
    channel->addDspBlock( peq02 );

    peq03 = new QPeq( 0.0, 3000.0, 2.0,
                      MOD_PARAMEQ4_ALG0_STAGE2_B2_ADDR, MOD_PARAMEQ4_ALG0_STAGE2_B1_ADDR, MOD_PARAMEQ4_ALG0_STAGE2_B0_ADDR,
                      MOD_PARAMEQ4_ALG0_STAGE2_A2_ADDR, MOD_PARAMEQ4_ALG0_STAGE2_A1_ADDR,
                      fs,
                      ptrdsp,
                      channel );
    layout->addWidget( peq03 );
    channel->addDspBlock( peq03 );

    peq04 = new QPeq( 0.0, 4000.0, 2.0,
                      MOD_PARAMEQ4_ALG0_STAGE3_B2_ADDR, MOD_PARAMEQ4_ALG0_STAGE3_B1_ADDR, MOD_PARAMEQ4_ALG0_STAGE3_B0_ADDR,
                      MOD_PARAMEQ4_ALG0_STAGE3_A2_ADDR, MOD_PARAMEQ4_ALG0_STAGE3_A1_ADDR,
                      fs,
                      ptrdsp,
                      channel );
    layout->addWidget( peq04 );
    channel->addDspBlock( peq04 );

    peq05 = new QPeq( 0.0, 5000.0, 2.0,
                      MOD_PARAMEQ4_ALG0_STAGE4_B2_ADDR, MOD_PARAMEQ4_ALG0_STAGE4_B1_ADDR, MOD_PARAMEQ4_ALG0_STAGE4_B0_ADDR,
                      MOD_PARAMEQ4_ALG0_STAGE4_A2_ADDR, MOD_PARAMEQ4_ALG0_STAGE4_A1_ADDR,
                      fs,
                      ptrdsp,
                      channel );
    layout->addWidget( peq05 );
    channel->addDspBlock( peq05 );

    peq06 = new QPeq( 0.0, 6000.0, 2.0,
                      MOD_PARAMEQ4_ALG0_STAGE5_B2_ADDR, MOD_PARAMEQ4_ALG0_STAGE5_B1_ADDR, MOD_PARAMEQ4_ALG0_STAGE5_B0_ADDR,
                      MOD_PARAMEQ4_ALG0_STAGE5_A2_ADDR, MOD_PARAMEQ4_ALG0_STAGE5_A1_ADDR,
                      fs,
                      ptrdsp,
                      channel );
    layout->addWidget( peq06 );
    channel->addDspBlock( peq06 );

    peq07 = new QPeq( 0.0, 7000.0, 2.0,
                      MOD_PARAMEQ4_ALG0_STAGE6_B2_ADDR, MOD_PARAMEQ4_ALG0_STAGE6_B1_ADDR, MOD_PARAMEQ4_ALG0_STAGE6_B0_ADDR,
                      MOD_PARAMEQ4_ALG0_STAGE6_A2_ADDR, MOD_PARAMEQ4_ALG0_STAGE6_A1_ADDR,
                      fs,
                      ptrdsp,
                      channel );
    layout->addWidget( peq07 );
    channel->addDspBlock( peq07 );

    peq08 = new QPeq( 0.0, 8000.0, 2.0,
                      MOD_PARAMEQ4_ALG0_STAGE7_B2_ADDR, MOD_PARAMEQ4_ALG0_STAGE7_B1_ADDR, MOD_PARAMEQ4_ALG0_STAGE7_B0_ADDR,
                      MOD_PARAMEQ4_ALG0_STAGE7_A2_ADDR, MOD_PARAMEQ4_ALG0_STAGE7_A1_ADDR,
                      fs,
                      ptrdsp,
                      channel );
    layout->addWidget( peq08 );
    channel->addDspBlock( peq08 );

    peq09 = new QPeq( 0.0, 9000.0, 2.0,
                      MOD_PARAMEQ4_ALG0_STAGE8_B2_ADDR, MOD_PARAMEQ4_ALG0_STAGE8_B1_ADDR, MOD_PARAMEQ4_ALG0_STAGE8_B0_ADDR,
                      MOD_PARAMEQ4_ALG0_STAGE8_A2_ADDR, MOD_PARAMEQ4_ALG0_STAGE8_A1_ADDR,
                      fs,
                      ptrdsp,
                      channel );
    layout->addWidget( peq09 );
    channel->addDspBlock( peq09 );

    peq10 = new QPeq( 0.0, 10000.0, 2.0,
                      MOD_PARAMEQ4_ALG0_STAGE9_B2_ADDR, MOD_PARAMEQ4_ALG0_STAGE9_B1_ADDR, MOD_PARAMEQ4_ALG0_STAGE9_B0_ADDR,
                      MOD_PARAMEQ4_ALG0_STAGE9_A2_ADDR, MOD_PARAMEQ4_ALG0_STAGE9_A1_ADDR,
                      fs,
                      ptrdsp,
                      channel );
    layout->addWidget( peq10 );
    channel->addDspBlock( peq10 );

    hshelv = new QHighShelv( 0.0, 5000.0, 1.0,
                            MOD_HIGHSHELV4_ALG0_STAGE0_B2_ADDR, MOD_HIGHSHELV4_ALG0_STAGE0_B1_ADDR, MOD_HIGHSHELV4_ALG0_STAGE0_B0_ADDR,
                            MOD_HIGHSHELV4_ALG0_STAGE0_A2_ADDR, MOD_HIGHSHELV4_ALG0_STAGE0_A1_ADDR,
                            fs,
                            ptrdsp,
                            channel );
    layout->addWidget( hshelv );
    channel->addDspBlock( hshelv );

    xo = new QCrossover( QCrossover::kButterworth12, 100.0,
                         QCrossover::kButterworth12, 100.0,
                         MOD_HP4_1_ALG0_STAGE0_B2_ADDR, MOD_HP4_1_ALG0_STAGE0_B1_ADDR, MOD_HP4_1_ALG0_STAGE0_B0_ADDR,
                         MOD_HP4_1_ALG0_STAGE0_A2_ADDR, MOD_HP4_1_ALG0_STAGE0_A1_ADDR,
                         MOD_HP4_2_ALG0_STAGE0_B2_ADDR, MOD_HP4_2_ALG0_STAGE0_B1_ADDR, MOD_HP4_2_ALG0_STAGE0_B0_ADDR,
                         MOD_HP4_2_ALG0_STAGE0_A2_ADDR, MOD_HP4_2_ALG0_STAGE0_A1_ADDR,
                         MOD_HP4_3_ALG0_STAGE0_B2_ADDR, MOD_HP4_3_ALG0_STAGE0_B1_ADDR, MOD_HP4_3_ALG0_STAGE0_B0_ADDR,
                         MOD_HP4_3_ALG0_STAGE0_A2_ADDR, MOD_HP4_3_ALG0_STAGE0_A1_ADDR,
                         MOD_HP4_4_ALG0_STAGE0_B2_ADDR, MOD_HP4_4_ALG0_STAGE0_B1_ADDR, MOD_HP4_4_ALG0_STAGE0_B0_ADDR,
                         MOD_HP4_4_ALG0_STAGE0_A2_ADDR, MOD_HP4_4_ALG0_STAGE0_A1_ADDR,
                         MOD_LP4_1_ALG0_STAGE0_B2_ADDR, MOD_LP4_1_ALG0_STAGE0_B1_ADDR, MOD_LP4_1_ALG0_STAGE0_B0_ADDR,
                         MOD_LP4_1_ALG0_STAGE0_A2_ADDR, MOD_LP4_1_ALG0_STAGE0_A1_ADDR,
                         MOD_LP4_2_ALG0_STAGE0_B2_ADDR, MOD_LP4_2_ALG0_STAGE0_B1_ADDR, MOD_LP4_2_ALG0_STAGE0_B0_ADDR,
                         MOD_LP4_2_ALG0_STAGE0_A2_ADDR, MOD_LP4_2_ALG0_STAGE0_A1_ADDR,
                         MOD_LP4_3_ALG0_STAGE0_B2_ADDR, MOD_LP4_3_ALG0_STAGE0_B1_ADDR, MOD_LP4_3_ALG0_STAGE0_B0_ADDR,
                         MOD_LP4_3_ALG0_STAGE0_A2_ADDR, MOD_LP4_3_ALG0_STAGE0_A1_ADDR,
                         MOD_LP4_4_ALG0_STAGE0_B2_ADDR, MOD_LP4_4_ALG0_STAGE0_B1_ADDR, MOD_LP4_4_ALG0_STAGE0_B0_ADDR,
                         MOD_LP4_4_ALG0_STAGE0_A2_ADDR, MOD_LP4_4_ALG0_STAGE0_A1_ADDR,
                         fs,
                         ptrdsp,
                         channel );
    layout->addWidget( xo );
    channel->addDspBlock( xo );

    phase = new QPhase( 1000.0, 1.0,
                      MOD_PHASE4_ALG0_STAGE0_B2_ADDR, MOD_PHASE4_ALG0_STAGE0_B1_ADDR, MOD_PHASE4_ALG0_STAGE0_B0_ADDR,
                      MOD_PHASE4_ALG0_STAGE0_A2_ADDR, MOD_PHASE4_ALG0_STAGE0_A1_ADDR,
                      fs,
                      ptrdsp,
                      channel );
    layout->addWidget( phase );
    channel->addDspBlock( phase );

    dly = new QDelay( 0.0, 48000.0, MOD_DELAY4_DELAYAMT_ADDR, ptrdsp, channel );
    layout->addWidget( dly );
    channel->addDspBlock( dly );

    gain = new QGain( 0.0, MOD_GAIN4_ALG0_TARGET_ADDR, ptrdsp, channel );
    layout->addWidget( gain );
    channel->addDspBlock( gain );

    output = new QOutputSelect( 1, 0, ptrdsp, channel );
    layout->addWidget( output );
    channel->addDspBlock( output );

    QObject::connect( lshelv, SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );
    QObject::connect( peq01,  SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );
    QObject::connect( peq02,  SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );
    QObject::connect( peq03,  SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );
    QObject::connect( peq04,  SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );
    QObject::connect( peq05,  SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );
    QObject::connect( peq06,  SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );
    QObject::connect( peq07,  SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );
    QObject::connect( peq08,  SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );
    QObject::connect( peq09,  SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );
    QObject::connect( peq10,  SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );
    QObject::connect( hshelv, SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );
    QObject::connect( xo,     SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );
    QObject::connect( phase,  SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );
    QObject::connect( dly,    SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );
    QObject::connect( gain,   SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );
    QObject::connect( output, SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );

    QObject::connect( peq01,  SIGNAL(importRewPeqs( QWidget* )), parent, SLOT(importRewPeqs( QWidget* )) );
    QObject::connect( peq02,  SIGNAL(importRewPeqs( QWidget* )), parent, SLOT(importRewPeqs( QWidget* )) );
    QObject::connect( peq03,  SIGNAL(importRewPeqs( QWidget* )), parent, SLOT(importRewPeqs( QWidget* )) );
    QObject::connect( peq04,  SIGNAL(importRewPeqs( QWidget* )), parent, SLOT(importRewPeqs( QWidget* )) );
    QObject::connect( peq05,  SIGNAL(importRewPeqs( QWidget* )), parent, SLOT(importRewPeqs( QWidget* )) );
    QObject::connect( peq06,  SIGNAL(importRewPeqs( QWidget* )), parent, SLOT(importRewPeqs( QWidget* )) );
    QObject::connect( peq07,  SIGNAL(importRewPeqs( QWidget* )), parent, SLOT(importRewPeqs( QWidget* )) );
    QObject::connect( peq08,  SIGNAL(importRewPeqs( QWidget* )), parent, SLOT(importRewPeqs( QWidget* )) );
    QObject::connect( peq09,  SIGNAL(importRewPeqs( QWidget* )), parent, SLOT(importRewPeqs( QWidget* )) );
    QObject::connect( peq10,  SIGNAL(importRewPeqs( QWidget* )), parent, SLOT(importRewPeqs( QWidget* )) );

    listChannels.append( channel );
  }
  else if( chn == 4 )
  {
    //--------------------------------------------------------------------------
    //--- Channel 5
    dspChannel.name = QString( "Rear Right" );

    input = new QInputSelect( 4, 
                              MOD_INPUTSELECT_5_NX1_1_ANALOG_ALG0_MONOMUXSIGMA300NS25INDEX_ADDR,
                              MOD_INPUTSELECT_5_NX1_1_UAC_ALG0_MONOMUXSIGMA300NS26INDEX_ADDR, 
                              MOD_INPUTSELECT_5_NX1_1_ESP32_ALG0_MONOMUXSIGMA300NS27INDEX_ADDR, 
                              MOD_INPUTSELECT_5_NX1_1_EXP_ALG0_MONOMUXSIGMA300NS28INDEX_ADDR, 
                              MOD_INPUTSELECT_5_NX1_1_SPDIF_ALG0_MONOMUXSIGMA300NS29INDEX_ADDR,
                              MOD_INPUTSELECT_5_NX1_1_ALG0_MONOMUXSIGMA300NS30INDEX_ADDR, 
                              ptrdsp, channel );
    layout->addWidget( input );
    channel->addDspBlock( input );
    channel->setName( dspChannel.name );

    lshelv = new QLowShelv( 0.0, 100.0, 1.0,
                            MOD_LOWSHELV5_ALG0_STAGE0_B2_ADDR, MOD_LOWSHELV5_ALG0_STAGE0_B1_ADDR, MOD_LOWSHELV5_ALG0_STAGE0_B0_ADDR,
                            MOD_LOWSHELV5_ALG0_STAGE0_A2_ADDR, MOD_LOWSHELV5_ALG0_STAGE0_A1_ADDR,
                            fs,
                            ptrdsp,
                            channel );
    layout->addWidget( lshelv );
    channel->addDspBlock( lshelv );

    peq01 = new QPeq( 0.0, 1000.0, 1.0,
                      MOD_PARAMEQ5_ALG0_STAGE0_B2_ADDR, MOD_PARAMEQ5_ALG0_STAGE0_B1_ADDR, MOD_PARAMEQ5_ALG0_STAGE0_B0_ADDR,
                      MOD_PARAMEQ5_ALG0_STAGE0_A2_ADDR, MOD_PARAMEQ5_ALG0_STAGE0_A1_ADDR,
                      fs,
                      ptrdsp,
                      channel );
    layout->addWidget( peq01 );
    channel->addDspBlock( peq01 );

    peq02 = new QPeq( 0.0, 2000.0, 2.0,
                      MOD_PARAMEQ5_ALG0_STAGE1_B2_ADDR, MOD_PARAMEQ5_ALG0_STAGE1_B1_ADDR, MOD_PARAMEQ5_ALG0_STAGE1_B0_ADDR,
                      MOD_PARAMEQ5_ALG0_STAGE1_A2_ADDR, MOD_PARAMEQ5_ALG0_STAGE1_A1_ADDR,
                      fs,
                      ptrdsp,
                      channel );
    layout->addWidget( peq02 );
    channel->addDspBlock( peq02 );

    peq03 = new QPeq( 0.0, 3000.0, 2.0,
                      MOD_PARAMEQ5_ALG0_STAGE2_B2_ADDR, MOD_PARAMEQ5_ALG0_STAGE2_B1_ADDR, MOD_PARAMEQ5_ALG0_STAGE2_B0_ADDR,
                      MOD_PARAMEQ5_ALG0_STAGE2_A2_ADDR, MOD_PARAMEQ5_ALG0_STAGE2_A1_ADDR,
                      fs,
                      ptrdsp,
                      channel );
    layout->addWidget( peq03 );
    channel->addDspBlock( peq03 );

    peq04 = new QPeq( 0.0, 4000.0, 2.0,
                      MOD_PARAMEQ5_ALG0_STAGE3_B2_ADDR, MOD_PARAMEQ5_ALG0_STAGE3_B1_ADDR, MOD_PARAMEQ5_ALG0_STAGE3_B0_ADDR,
                      MOD_PARAMEQ5_ALG0_STAGE3_A2_ADDR, MOD_PARAMEQ5_ALG0_STAGE3_A1_ADDR,
                      fs,
                      ptrdsp,
                      channel );
    layout->addWidget( peq04 );
    channel->addDspBlock( peq04 );

    peq05 = new QPeq( 0.0, 5000.0, 2.0,
                      MOD_PARAMEQ5_ALG0_STAGE4_B2_ADDR, MOD_PARAMEQ5_ALG0_STAGE4_B1_ADDR, MOD_PARAMEQ5_ALG0_STAGE4_B0_ADDR,
                      MOD_PARAMEQ5_ALG0_STAGE4_A2_ADDR, MOD_PARAMEQ5_ALG0_STAGE4_A1_ADDR,
                      fs,
                      ptrdsp,
                      channel );
    layout->addWidget( peq05 );
    channel->addDspBlock( peq05 );

    peq06 = new QPeq( 0.0, 6000.0, 2.0,
                      MOD_PARAMEQ5_ALG0_STAGE5_B2_ADDR, MOD_PARAMEQ5_ALG0_STAGE5_B1_ADDR, MOD_PARAMEQ5_ALG0_STAGE5_B0_ADDR,
                      MOD_PARAMEQ5_ALG0_STAGE5_A2_ADDR, MOD_PARAMEQ5_ALG0_STAGE5_A1_ADDR,
                      fs,
                      ptrdsp,
                      channel );
    layout->addWidget( peq06 );
    channel->addDspBlock( peq06 );

    peq07 = new QPeq( 0.0, 7000.0, 2.0,
                      MOD_PARAMEQ5_ALG0_STAGE6_B2_ADDR, MOD_PARAMEQ5_ALG0_STAGE6_B1_ADDR, MOD_PARAMEQ5_ALG0_STAGE6_B0_ADDR,
                      MOD_PARAMEQ5_ALG0_STAGE6_A2_ADDR, MOD_PARAMEQ5_ALG0_STAGE6_A1_ADDR,
                      fs,
                      ptrdsp,
                      channel );
    layout->addWidget( peq07 );
    channel->addDspBlock( peq07 );

    peq08 = new QPeq( 0.0, 8000.0, 2.0,
                      MOD_PARAMEQ5_ALG0_STAGE7_B2_ADDR, MOD_PARAMEQ5_ALG0_STAGE7_B1_ADDR, MOD_PARAMEQ5_ALG0_STAGE7_B0_ADDR,
                      MOD_PARAMEQ5_ALG0_STAGE7_A2_ADDR, MOD_PARAMEQ5_ALG0_STAGE7_A1_ADDR,
                      fs,
                      ptrdsp,
                      channel );
    layout->addWidget( peq08 );
    channel->addDspBlock( peq08 );

    peq09 = new QPeq( 0.0, 9000.0, 2.0,
                      MOD_PARAMEQ5_ALG0_STAGE8_B2_ADDR, MOD_PARAMEQ5_ALG0_STAGE8_B1_ADDR, MOD_PARAMEQ5_ALG0_STAGE8_B0_ADDR,
                      MOD_PARAMEQ5_ALG0_STAGE8_A2_ADDR, MOD_PARAMEQ5_ALG0_STAGE8_A1_ADDR,
                      fs,
                      ptrdsp,
                      channel );
    layout->addWidget( peq09 );
    channel->addDspBlock( peq09 );

    peq10 = new QPeq( 0.0, 10000.0, 2.0,
                      MOD_PARAMEQ5_ALG0_STAGE9_B2_ADDR, MOD_PARAMEQ5_ALG0_STAGE9_B1_ADDR, MOD_PARAMEQ5_ALG0_STAGE9_B0_ADDR,
                      MOD_PARAMEQ5_ALG0_STAGE9_A2_ADDR, MOD_PARAMEQ5_ALG0_STAGE9_A1_ADDR,
                      fs,
                      ptrdsp,
                      channel );
    layout->addWidget( peq10 );
    channel->addDspBlock( peq10 );

    hshelv = new QHighShelv( 0.0, 5000.0, 1.0,
                            MOD_HIGHSHELV5_ALG0_STAGE0_B2_ADDR, MOD_HIGHSHELV5_ALG0_STAGE0_B1_ADDR, MOD_HIGHSHELV5_ALG0_STAGE0_B0_ADDR,
                            MOD_HIGHSHELV5_ALG0_STAGE0_A2_ADDR, MOD_HIGHSHELV5_ALG0_STAGE0_A1_ADDR,
                            fs,
                            ptrdsp,
                            channel );
    layout->addWidget( hshelv );
    channel->addDspBlock( hshelv );

    xo = new QCrossover( QCrossover::kButterworth12, 100.0,
                         QCrossover::kButterworth12, 100.0,
                         MOD_HP5_1_ALG0_STAGE0_B2_ADDR, MOD_HP5_1_ALG0_STAGE0_B1_ADDR, MOD_HP5_1_ALG0_STAGE0_B0_ADDR,
                         MOD_HP5_1_ALG0_STAGE0_A2_ADDR, MOD_HP5_1_ALG0_STAGE0_A1_ADDR,
                         MOD_HP5_2_ALG0_STAGE0_B2_ADDR, MOD_HP5_2_ALG0_STAGE0_B1_ADDR, MOD_HP5_2_ALG0_STAGE0_B0_ADDR,
                         MOD_HP5_2_ALG0_STAGE0_A2_ADDR, MOD_HP5_2_ALG0_STAGE0_A1_ADDR,
                         MOD_HP5_3_ALG0_STAGE0_B2_ADDR, MOD_HP5_3_ALG0_STAGE0_B1_ADDR, MOD_HP5_3_ALG0_STAGE0_B0_ADDR,
                         MOD_HP5_3_ALG0_STAGE0_A2_ADDR, MOD_HP5_3_ALG0_STAGE0_A1_ADDR,
                         MOD_HP5_4_ALG0_STAGE0_B2_ADDR, MOD_HP5_4_ALG0_STAGE0_B1_ADDR, MOD_HP5_4_ALG0_STAGE0_B0_ADDR,
                         MOD_HP5_4_ALG0_STAGE0_A2_ADDR, MOD_HP5_4_ALG0_STAGE0_A1_ADDR,
                         MOD_LP5_1_ALG0_STAGE0_B2_ADDR, MOD_LP5_1_ALG0_STAGE0_B1_ADDR, MOD_LP5_1_ALG0_STAGE0_B0_ADDR,
                         MOD_LP5_1_ALG0_STAGE0_A2_ADDR, MOD_LP5_1_ALG0_STAGE0_A1_ADDR,
                         MOD_LP5_2_ALG0_STAGE0_B2_ADDR, MOD_LP5_2_ALG0_STAGE0_B1_ADDR, MOD_LP5_2_ALG0_STAGE0_B0_ADDR,
                         MOD_LP5_2_ALG0_STAGE0_A2_ADDR, MOD_LP5_2_ALG0_STAGE0_A1_ADDR,
                         MOD_LP5_3_ALG0_STAGE0_B2_ADDR, MOD_LP5_3_ALG0_STAGE0_B1_ADDR, MOD_LP5_3_ALG0_STAGE0_B0_ADDR,
                         MOD_LP5_3_ALG0_STAGE0_A2_ADDR, MOD_LP5_3_ALG0_STAGE0_A1_ADDR,
                         MOD_LP5_4_ALG0_STAGE0_B2_ADDR, MOD_LP5_4_ALG0_STAGE0_B1_ADDR, MOD_LP5_4_ALG0_STAGE0_B0_ADDR,
                         MOD_LP5_4_ALG0_STAGE0_A2_ADDR, MOD_LP5_4_ALG0_STAGE0_A1_ADDR,
                         fs,
                         ptrdsp,
                         channel );
    layout->addWidget( xo );
    channel->addDspBlock( xo );

    phase = new QPhase( 1000.0, 1.0,
                        MOD_PHASE5_ALG0_STAGE0_B2_ADDR, MOD_PHASE5_ALG0_STAGE0_B1_ADDR, MOD_PHASE5_ALG0_STAGE0_B0_ADDR,
                        MOD_PHASE5_ALG0_STAGE0_A2_ADDR, MOD_PHASE5_ALG0_STAGE0_A1_ADDR,
                        fs,
                        ptrdsp,
                        channel );
    layout->addWidget( phase );
    channel->addDspBlock( phase );

    dly = new QDelay( 0.0, 48000.0, MOD_DELAY5_DELAYAMT_ADDR, ptrdsp, channel );
    layout->addWidget( dly );
    channel->addDspBlock( dly );

    gain = new QGain( 0.0, MOD_GAIN5_ALG0_TARGET_ADDR, ptrdsp, channel );
    layout->addWidget( gain );
    channel->addDspBlock( gain );

    output = new QOutputSelect( 1, 0, ptrdsp, channel );
    layout->addWidget( output );
    channel->addDspBlock( output );

    QObject::connect( lshelv, SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );
    QObject::connect( peq01,  SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );
    QObject::connect( peq02,  SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );
    QObject::connect( peq03,  SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );
    QObject::connect( peq04,  SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );
    QObject::connect( peq05,  SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );
    QObject::connect( peq06,  SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );
    QObject::connect( peq07,  SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );
    QObject::connect( peq08,  SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );
    QObject::connect( peq09,  SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );
    QObject::connect( peq10,  SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );
    QObject::connect( hshelv, SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );
    QObject::connect( xo,     SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );
    QObject::connect( phase,  SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );
    QObject::connect( dly,    SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );
    QObject::connect( gain,   SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );
    QObject::connect( output, SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );

    QObject::connect( peq01,  SIGNAL(importRewPeqs( QWidget* )), parent, SLOT(importRewPeqs( QWidget* )) );
    QObject::connect( peq02,  SIGNAL(importRewPeqs( QWidget* )), parent, SLOT(importRewPeqs( QWidget* )) );
    QObject::connect( peq03,  SIGNAL(importRewPeqs( QWidget* )), parent, SLOT(importRewPeqs( QWidget* )) );
    QObject::connect( peq04,  SIGNAL(importRewPeqs( QWidget* )), parent, SLOT(importRewPeqs( QWidget* )) );
    QObject::connect( peq05,  SIGNAL(importRewPeqs( QWidget* )), parent, SLOT(importRewPeqs( QWidget* )) );
    QObject::connect( peq06,  SIGNAL(importRewPeqs( QWidget* )), parent, SLOT(importRewPeqs( QWidget* )) );
    QObject::connect( peq07,  SIGNAL(importRewPeqs( QWidget* )), parent, SLOT(importRewPeqs( QWidget* )) );
    QObject::connect( peq08,  SIGNAL(importRewPeqs( QWidget* )), parent, SLOT(importRewPeqs( QWidget* )) );
    QObject::connect( peq09,  SIGNAL(importRewPeqs( QWidget* )), parent, SLOT(importRewPeqs( QWidget* )) );
    QObject::connect( peq10,  SIGNAL(importRewPeqs( QWidget* )), parent, SLOT(importRewPeqs( QWidget* )) );

    listChannels.append( channel );
  }
  else if( chn == 5 )
  {
    //--------------------------------------------------------------------------
    //--- Channel 6
    dspChannel.name = QString( "Side Left" );

    input = new QInputSelect( 5, 
                              MOD_INPUTSELECT_6_NX1_1_ANALOG_ALG0_MONOMUXSIGMA300NS31INDEX_ADDR,
                              MOD_INPUTSELECT_6_NX1_1_UAC_ALG0_MONOMUXSIGMA300NS32INDEX_ADDR, 
                              MOD_INPUTSELECT_6_NX1_1_ESP32_ALG0_MONOMUXSIGMA300NS33INDEX_ADDR, 
                              MOD_INPUTSELECT_6_NX1_1_EXP_ALG0_MONOMUXSIGMA300NS34INDEX_ADDR, 
                              MOD_INPUTSELECT_6_NX1_1_SPDIF_ALG0_MONOMUXSIGMA300NS35INDEX_ADDR,
                              MOD_INPUTSELECT_6_NX1_1_ALG0_MONOMUXSIGMA300NS36INDEX_ADDR, 
                              ptrdsp, channel );
    layout->addWidget( input );
    channel->addDspBlock( input );
    channel->setName( dspChannel.name );

    lshelv = new QLowShelv( 0.0, 100.0, 1.0,
                          MOD_LOWSHELV6_ALG0_STAGE0_B2_ADDR, MOD_LOWSHELV6_ALG0_STAGE0_B1_ADDR, MOD_LOWSHELV6_ALG0_STAGE0_B0_ADDR,
                          MOD_LOWSHELV6_ALG0_STAGE0_A2_ADDR, MOD_LOWSHELV6_ALG0_STAGE0_A1_ADDR,
                          fs,
                          ptrdsp,
                          channel );
    layout->addWidget( lshelv );
    channel->addDspBlock( lshelv );

    peq01 = new QPeq( 0.0, 1000.0, 1.0,
                      MOD_PARAMEQ6_ALG0_STAGE0_B2_ADDR, MOD_PARAMEQ6_ALG0_STAGE0_B1_ADDR, MOD_PARAMEQ6_ALG0_STAGE0_B0_ADDR,
                      MOD_PARAMEQ6_ALG0_STAGE0_A2_ADDR, MOD_PARAMEQ6_ALG0_STAGE0_A1_ADDR,
                      fs,
                      ptrdsp,
                      channel );
    layout->addWidget( peq01 );
    channel->addDspBlock( peq01 );

    peq02 = new QPeq( 0.0, 2000.0, 2.0,
                      MOD_PARAMEQ6_ALG0_STAGE1_B2_ADDR, MOD_PARAMEQ6_ALG0_STAGE1_B1_ADDR, MOD_PARAMEQ6_ALG0_STAGE1_B0_ADDR,
                      MOD_PARAMEQ6_ALG0_STAGE1_A2_ADDR, MOD_PARAMEQ6_ALG0_STAGE1_A1_ADDR,
                      fs,
                      ptrdsp,
                      channel );
    layout->addWidget( peq02 );
    channel->addDspBlock( peq02 );

    peq03 = new QPeq( 0.0, 3000.0, 2.0,
                      MOD_PARAMEQ6_ALG0_STAGE2_B2_ADDR, MOD_PARAMEQ6_ALG0_STAGE2_B1_ADDR, MOD_PARAMEQ6_ALG0_STAGE2_B0_ADDR,
                      MOD_PARAMEQ6_ALG0_STAGE2_A2_ADDR, MOD_PARAMEQ6_ALG0_STAGE2_A1_ADDR,
                      fs,
                      ptrdsp,
                      channel );
    layout->addWidget( peq03 );
    channel->addDspBlock( peq03 );

    peq04 = new QPeq( 0.0, 4000.0, 2.0,
                      MOD_PARAMEQ6_ALG0_STAGE3_B2_ADDR, MOD_PARAMEQ6_ALG0_STAGE3_B1_ADDR, MOD_PARAMEQ6_ALG0_STAGE3_B0_ADDR,
                      MOD_PARAMEQ6_ALG0_STAGE3_A2_ADDR, MOD_PARAMEQ6_ALG0_STAGE3_A1_ADDR,
                      fs,
                      ptrdsp,
                      channel );
    layout->addWidget( peq04 );
    channel->addDspBlock( peq04 );

    peq05 = new QPeq( 0.0, 5000.0, 2.0,
                      MOD_PARAMEQ6_ALG0_STAGE4_B2_ADDR, MOD_PARAMEQ6_ALG0_STAGE4_B1_ADDR, MOD_PARAMEQ6_ALG0_STAGE4_B0_ADDR,
                      MOD_PARAMEQ6_ALG0_STAGE4_A2_ADDR, MOD_PARAMEQ6_ALG0_STAGE4_A1_ADDR,
                      fs,
                      ptrdsp,
                      channel );
    layout->addWidget( peq05 );
    channel->addDspBlock( peq05 );

    peq06 = new QPeq( 0.0, 6000.0, 2.0,
                      MOD_PARAMEQ6_ALG0_STAGE5_B2_ADDR, MOD_PARAMEQ6_ALG0_STAGE5_B1_ADDR, MOD_PARAMEQ6_ALG0_STAGE5_B0_ADDR,
                      MOD_PARAMEQ6_ALG0_STAGE5_A2_ADDR, MOD_PARAMEQ6_ALG0_STAGE5_A1_ADDR,
                      fs,
                      ptrdsp,
                      channel );
    layout->addWidget( peq06 );
    channel->addDspBlock( peq06 );

    peq07 = new QPeq( 0.0, 7000.0, 2.0,
                      MOD_PARAMEQ6_ALG0_STAGE6_B2_ADDR, MOD_PARAMEQ6_ALG0_STAGE6_B1_ADDR, MOD_PARAMEQ6_ALG0_STAGE6_B0_ADDR,
                      MOD_PARAMEQ6_ALG0_STAGE6_A2_ADDR, MOD_PARAMEQ6_ALG0_STAGE6_A1_ADDR,
                      fs,
                      ptrdsp,
                      channel );
    layout->addWidget( peq07 );
    channel->addDspBlock( peq07 );

    peq08 = new QPeq( 0.0, 8000.0, 2.0,
                      MOD_PARAMEQ6_ALG0_STAGE7_B2_ADDR, MOD_PARAMEQ6_ALG0_STAGE7_B1_ADDR, MOD_PARAMEQ6_ALG0_STAGE7_B0_ADDR,
                      MOD_PARAMEQ6_ALG0_STAGE7_A2_ADDR, MOD_PARAMEQ6_ALG0_STAGE7_A1_ADDR,
                      fs,
                      ptrdsp,
                      channel );
    layout->addWidget( peq08 );
    channel->addDspBlock( peq08 );

    peq09 = new QPeq( 0.0, 9000.0, 2.0,
                      MOD_PARAMEQ6_ALG0_STAGE8_B2_ADDR, MOD_PARAMEQ6_ALG0_STAGE8_B1_ADDR, MOD_PARAMEQ6_ALG0_STAGE8_B0_ADDR,
                      MOD_PARAMEQ6_ALG0_STAGE8_A2_ADDR, MOD_PARAMEQ6_ALG0_STAGE8_A1_ADDR,
                      fs,
                      ptrdsp,
                      channel );
    layout->addWidget( peq09 );
    channel->addDspBlock( peq09 );

    peq10 = new QPeq( 0.0, 10000.0, 2.0,
                      MOD_PARAMEQ6_ALG0_STAGE9_B2_ADDR, MOD_PARAMEQ6_ALG0_STAGE9_B1_ADDR, MOD_PARAMEQ6_ALG0_STAGE9_B0_ADDR,
                      MOD_PARAMEQ6_ALG0_STAGE9_A2_ADDR, MOD_PARAMEQ6_ALG0_STAGE9_A1_ADDR,
                      fs,
                      ptrdsp,
                      channel );
    layout->addWidget( peq10 );
    channel->addDspBlock( peq10 );

    hshelv = new QHighShelv( 0.0, 5000.0, 1.0,
                            MOD_HIGHSHELV6_ALG0_STAGE0_B2_ADDR, MOD_HIGHSHELV6_ALG0_STAGE0_B1_ADDR, MOD_HIGHSHELV6_ALG0_STAGE0_B0_ADDR,
                            MOD_HIGHSHELV6_ALG0_STAGE0_A2_ADDR, MOD_HIGHSHELV6_ALG0_STAGE0_A1_ADDR,
                            fs,
                            ptrdsp,
                            channel );
    layout->addWidget( hshelv );
    channel->addDspBlock( hshelv );

    xo = new QCrossover( QCrossover::kButterworth12, 100.0,
                         QCrossover::kButterworth12, 100.0,
                         MOD_HP6_1_ALG0_STAGE0_B2_ADDR, MOD_HP6_1_ALG0_STAGE0_B1_ADDR, MOD_HP6_1_ALG0_STAGE0_B0_ADDR,
                         MOD_HP6_1_ALG0_STAGE0_A2_ADDR, MOD_HP6_1_ALG0_STAGE0_A1_ADDR,
                         MOD_HP6_2_ALG0_STAGE0_B2_ADDR, MOD_HP6_2_ALG0_STAGE0_B1_ADDR, MOD_HP6_2_ALG0_STAGE0_B0_ADDR,
                         MOD_HP6_2_ALG0_STAGE0_A2_ADDR, MOD_HP6_2_ALG0_STAGE0_A1_ADDR,
                         MOD_HP6_3_ALG0_STAGE0_B2_ADDR, MOD_HP6_3_ALG0_STAGE0_B1_ADDR, MOD_HP6_3_ALG0_STAGE0_B0_ADDR,
                         MOD_HP6_3_ALG0_STAGE0_A2_ADDR, MOD_HP6_3_ALG0_STAGE0_A1_ADDR,
                         MOD_HP6_4_ALG0_STAGE0_B2_ADDR, MOD_HP6_4_ALG0_STAGE0_B1_ADDR, MOD_HP6_4_ALG0_STAGE0_B0_ADDR,
                         MOD_HP6_4_ALG0_STAGE0_A2_ADDR, MOD_HP6_4_ALG0_STAGE0_A1_ADDR,
                         MOD_LP6_1_ALG0_STAGE0_B2_ADDR, MOD_LP6_1_ALG0_STAGE0_B1_ADDR, MOD_LP6_1_ALG0_STAGE0_B0_ADDR,
                         MOD_LP6_1_ALG0_STAGE0_A2_ADDR, MOD_LP6_1_ALG0_STAGE0_A1_ADDR,
                         MOD_LP6_2_ALG0_STAGE0_B2_ADDR, MOD_LP6_2_ALG0_STAGE0_B1_ADDR, MOD_LP6_2_ALG0_STAGE0_B0_ADDR,
                         MOD_LP6_2_ALG0_STAGE0_A2_ADDR, MOD_LP6_2_ALG0_STAGE0_A1_ADDR,
                         MOD_LP6_3_ALG0_STAGE0_B2_ADDR, MOD_LP6_3_ALG0_STAGE0_B1_ADDR, MOD_LP6_3_ALG0_STAGE0_B0_ADDR,
                         MOD_LP6_3_ALG0_STAGE0_A2_ADDR, MOD_LP6_3_ALG0_STAGE0_A1_ADDR,
                         MOD_LP6_4_ALG0_STAGE0_B2_ADDR, MOD_LP6_4_ALG0_STAGE0_B1_ADDR, MOD_LP6_4_ALG0_STAGE0_B0_ADDR,
                         MOD_LP6_4_ALG0_STAGE0_A2_ADDR, MOD_LP6_4_ALG0_STAGE0_A1_ADDR,
                         fs,
                         ptrdsp,
                         channel );
    layout->addWidget( xo );
    channel->addDspBlock( xo );

    phase = new QPhase( 1000.0, 1.0,
                      MOD_PHASE6_ALG0_STAGE0_B2_ADDR, MOD_PHASE6_ALG0_STAGE0_B1_ADDR, MOD_PHASE6_ALG0_STAGE0_B0_ADDR,
                      MOD_PHASE6_ALG0_STAGE0_A2_ADDR, MOD_PHASE6_ALG0_STAGE0_A1_ADDR,
                      fs,
                      ptrdsp,
                      channel );
    layout->addWidget( phase );
    channel->addDspBlock( phase );

    dly = new QDelay( 0.0, 48000.0, MOD_DELAY6_DELAYAMT_ADDR, ptrdsp, channel );
    layout->addWidget( dly );
    channel->addDspBlock( dly );

    gain = new QGain( 0.0, MOD_GAIN6_ALG0_TARGET_ADDR, ptrdsp, channel );
    layout->addWidget( gain );
    channel->addDspBlock( gain );

    output = new QOutputSelect( 1, 0, ptrdsp, channel );
    layout->addWidget( output );
    channel->addDspBlock( output );

    QObject::connect( lshelv, SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );
    QObject::connect( peq01,  SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );
    QObject::connect( peq02,  SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );
    QObject::connect( peq03,  SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );
    QObject::connect( peq04,  SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );
    QObject::connect( peq05,  SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );
    QObject::connect( peq06,  SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );
    QObject::connect( peq07,  SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );
    QObject::connect( peq08,  SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );
    QObject::connect( peq09,  SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );
    QObject::connect( peq10,  SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );
    QObject::connect( hshelv, SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );
    QObject::connect( xo,     SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );
    QObject::connect( phase,  SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );
    QObject::connect( dly,    SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );
    QObject::connect( gain,   SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );
    QObject::connect( output, SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );

    QObject::connect( peq01,  SIGNAL(importRewPeqs( QWidget* )), parent, SLOT(importRewPeqs( QWidget* )) );
    QObject::connect( peq02,  SIGNAL(importRewPeqs( QWidget* )), parent, SLOT(importRewPeqs( QWidget* )) );
    QObject::connect( peq03,  SIGNAL(importRewPeqs( QWidget* )), parent, SLOT(importRewPeqs( QWidget* )) );
    QObject::connect( peq04,  SIGNAL(importRewPeqs( QWidget* )), parent, SLOT(importRewPeqs( QWidget* )) );
    QObject::connect( peq05,  SIGNAL(importRewPeqs( QWidget* )), parent, SLOT(importRewPeqs( QWidget* )) );
    QObject::connect( peq06,  SIGNAL(importRewPeqs( QWidget* )), parent, SLOT(importRewPeqs( QWidget* )) );
    QObject::connect( peq07,  SIGNAL(importRewPeqs( QWidget* )), parent, SLOT(importRewPeqs( QWidget* )) );
    QObject::connect( peq08,  SIGNAL(importRewPeqs( QWidget* )), parent, SLOT(importRewPeqs( QWidget* )) );
    QObject::connect( peq09,  SIGNAL(importRewPeqs( QWidget* )), parent, SLOT(importRewPeqs( QWidget* )) );
    QObject::connect( peq10,  SIGNAL(importRewPeqs( QWidget* )), parent, SLOT(importRewPeqs( QWidget* )) );

    listChannels.append( channel );
  }
  else if( chn == 6 )
  {
    //--------------------------------------------------------------------------
    //--- Channel 7
    dspChannel.name = QString( "Side Right" );

    input = new QInputSelect( 6, 
                              MOD_INPUTSELECT_7_NX1_1_ANALOG_ALG0_MONOMUXSIGMA300NS37INDEX_ADDR,
                              MOD_INPUTSELECT_7_NX1_1_UAC_ALG0_MONOMUXSIGMA300NS38INDEX_ADDR, 
                              MOD_INPUTSELECT_7_NX1_1_ESP32_ALG0_MONOMUXSIGMA300NS39INDEX_ADDR, 
                              MOD_INPUTSELECT_7_NX1_1_EXP_ALG0_MONOMUXSIGMA300NS40INDEX_ADDR, 
                              MOD_INPUTSELECT_7_NX1_1_SPDIF_ALG0_MONOMUXSIGMA300NS41INDEX_ADDR,
                              MOD_INPUTSELECT_7_NX1_1_ALG0_MONOMUXSIGMA300NS42INDEX_ADDR, 
                              ptrdsp, channel );
    layout->addWidget( input );
    channel->addDspBlock( input );
    channel->setName( dspChannel.name );

    lshelv = new QLowShelv( 0.0, 100.0, 1.0,
                          MOD_LOWSHELV7_ALG0_STAGE0_B2_ADDR, MOD_LOWSHELV7_ALG0_STAGE0_B1_ADDR, MOD_LOWSHELV7_ALG0_STAGE0_B0_ADDR,
                          MOD_LOWSHELV7_ALG0_STAGE0_A2_ADDR, MOD_LOWSHELV7_ALG0_STAGE0_A1_ADDR,
                          fs,
                          ptrdsp,
                          channel );
    layout->addWidget( lshelv );
    channel->addDspBlock( lshelv );

    peq01 = new QPeq( 0.0, 1000.0, 1.0,
                      MOD_PARAMEQ7_ALG0_STAGE0_B2_ADDR, MOD_PARAMEQ7_ALG0_STAGE0_B1_ADDR, MOD_PARAMEQ7_ALG0_STAGE0_B0_ADDR,
                      MOD_PARAMEQ7_ALG0_STAGE0_A2_ADDR, MOD_PARAMEQ7_ALG0_STAGE0_A1_ADDR,
                      fs,
                      ptrdsp,
                      channel );
    layout->addWidget( peq01 );
    channel->addDspBlock( peq01 );

    peq02 = new QPeq( 0.0, 2000.0, 2.0,
                      MOD_PARAMEQ7_ALG0_STAGE1_B2_ADDR, MOD_PARAMEQ7_ALG0_STAGE1_B1_ADDR, MOD_PARAMEQ7_ALG0_STAGE1_B0_ADDR,
                      MOD_PARAMEQ7_ALG0_STAGE1_A2_ADDR, MOD_PARAMEQ7_ALG0_STAGE1_A1_ADDR,
                      fs,
                      ptrdsp,
                      channel );
    layout->addWidget( peq02 );
    channel->addDspBlock( peq02 );

    peq03 = new QPeq( 0.0, 3000.0, 2.0,
                      MOD_PARAMEQ7_ALG0_STAGE2_B2_ADDR, MOD_PARAMEQ7_ALG0_STAGE2_B1_ADDR, MOD_PARAMEQ7_ALG0_STAGE2_B0_ADDR,
                      MOD_PARAMEQ7_ALG0_STAGE2_A2_ADDR, MOD_PARAMEQ7_ALG0_STAGE2_A1_ADDR,
                      fs,
                      ptrdsp,
                      channel );
    layout->addWidget( peq03 );
    channel->addDspBlock( peq03 );

    peq04 = new QPeq( 0.0, 4000.0, 2.0,
                      MOD_PARAMEQ7_ALG0_STAGE3_B2_ADDR, MOD_PARAMEQ7_ALG0_STAGE3_B1_ADDR, MOD_PARAMEQ7_ALG0_STAGE3_B0_ADDR,
                      MOD_PARAMEQ7_ALG0_STAGE3_A2_ADDR, MOD_PARAMEQ7_ALG0_STAGE3_A1_ADDR,
                      fs,
                      ptrdsp,
                      channel );
    layout->addWidget( peq04 );
    channel->addDspBlock( peq04 );

    peq05 = new QPeq( 0.0, 5000.0, 2.0,
                      MOD_PARAMEQ7_ALG0_STAGE4_B2_ADDR, MOD_PARAMEQ7_ALG0_STAGE4_B1_ADDR, MOD_PARAMEQ7_ALG0_STAGE4_B0_ADDR,
                      MOD_PARAMEQ7_ALG0_STAGE4_A2_ADDR, MOD_PARAMEQ7_ALG0_STAGE4_A1_ADDR,
                      fs,
                      ptrdsp,
                      channel );
    layout->addWidget( peq05 );
    channel->addDspBlock( peq05 );

    peq06 = new QPeq( 0.0, 6000.0, 2.0,
                      MOD_PARAMEQ7_ALG0_STAGE5_B2_ADDR, MOD_PARAMEQ7_ALG0_STAGE5_B1_ADDR, MOD_PARAMEQ7_ALG0_STAGE5_B0_ADDR,
                      MOD_PARAMEQ7_ALG0_STAGE5_A2_ADDR, MOD_PARAMEQ7_ALG0_STAGE5_A1_ADDR,
                      fs,
                      ptrdsp,
                      channel );
    layout->addWidget( peq06 );
    channel->addDspBlock( peq06 );

    peq07 = new QPeq( 0.0, 7000.0, 2.0,
                      MOD_PARAMEQ7_ALG0_STAGE6_B2_ADDR, MOD_PARAMEQ7_ALG0_STAGE6_B1_ADDR, MOD_PARAMEQ7_ALG0_STAGE6_B0_ADDR,
                      MOD_PARAMEQ7_ALG0_STAGE6_A2_ADDR, MOD_PARAMEQ7_ALG0_STAGE6_A1_ADDR,
                      fs,
                      ptrdsp,
                      channel );
    layout->addWidget( peq07 );
    channel->addDspBlock( peq07 );

    peq08 = new QPeq( 0.0, 8000.0, 2.0,
                      MOD_PARAMEQ7_ALG0_STAGE7_B2_ADDR, MOD_PARAMEQ7_ALG0_STAGE7_B1_ADDR, MOD_PARAMEQ7_ALG0_STAGE7_B0_ADDR,
                      MOD_PARAMEQ7_ALG0_STAGE7_A2_ADDR, MOD_PARAMEQ7_ALG0_STAGE7_A1_ADDR,
                      fs,
                      ptrdsp,
                      channel );
    layout->addWidget( peq08 );
    channel->addDspBlock( peq08 );

    peq09 = new QPeq( 0.0, 9000.0, 2.0,
                      MOD_PARAMEQ7_ALG0_STAGE8_B2_ADDR, MOD_PARAMEQ7_ALG0_STAGE8_B1_ADDR, MOD_PARAMEQ7_ALG0_STAGE8_B0_ADDR,
                      MOD_PARAMEQ7_ALG0_STAGE8_A2_ADDR, MOD_PARAMEQ7_ALG0_STAGE8_A1_ADDR,
                      fs,
                      ptrdsp,
                      channel );
    layout->addWidget( peq09 );
    channel->addDspBlock( peq09 );

    peq10 = new QPeq( 0.0, 10000.0, 2.0,
                      MOD_PARAMEQ7_ALG0_STAGE9_B2_ADDR, MOD_PARAMEQ7_ALG0_STAGE9_B1_ADDR, MOD_PARAMEQ7_ALG0_STAGE9_B0_ADDR,
                      MOD_PARAMEQ7_ALG0_STAGE9_A2_ADDR, MOD_PARAMEQ7_ALG0_STAGE9_A1_ADDR,
                      fs,
                      ptrdsp,
                      channel );
    layout->addWidget( peq10 );
    channel->addDspBlock( peq10 );

    hshelv = new QHighShelv( 0.0, 5000.0, 1.0,
                           MOD_HIGHSHELV7_ALG0_STAGE0_B2_ADDR, MOD_HIGHSHELV7_ALG0_STAGE0_B1_ADDR, MOD_HIGHSHELV7_ALG0_STAGE0_B0_ADDR,
                           MOD_HIGHSHELV7_ALG0_STAGE0_A2_ADDR, MOD_HIGHSHELV7_ALG0_STAGE0_A1_ADDR,
                           fs,
                           ptrdsp,
                           channel );
    layout->addWidget( hshelv );
    channel->addDspBlock( hshelv );

    xo = new QCrossover( QCrossover::kButterworth12, 100.0,
                         QCrossover::kButterworth12, 100.0,
                         MOD_HP7_1_ALG0_STAGE0_B2_ADDR, MOD_HP7_1_ALG0_STAGE0_B1_ADDR, MOD_HP7_1_ALG0_STAGE0_B0_ADDR,
                         MOD_HP7_1_ALG0_STAGE0_A2_ADDR, MOD_HP7_1_ALG0_STAGE0_A1_ADDR,
                         MOD_HP7_2_ALG0_STAGE0_B2_ADDR, MOD_HP7_2_ALG0_STAGE0_B1_ADDR, MOD_HP7_2_ALG0_STAGE0_B0_ADDR,
                         MOD_HP7_2_ALG0_STAGE0_A2_ADDR, MOD_HP7_2_ALG0_STAGE0_A1_ADDR,
                         MOD_HP7_3_ALG0_STAGE0_B2_ADDR, MOD_HP7_3_ALG0_STAGE0_B1_ADDR, MOD_HP7_3_ALG0_STAGE0_B0_ADDR,
                         MOD_HP7_3_ALG0_STAGE0_A2_ADDR, MOD_HP7_3_ALG0_STAGE0_A1_ADDR,
                         MOD_HP7_4_ALG0_STAGE0_B2_ADDR, MOD_HP7_4_ALG0_STAGE0_B1_ADDR, MOD_HP7_4_ALG0_STAGE0_B0_ADDR,
                         MOD_HP7_4_ALG0_STAGE0_A2_ADDR, MOD_HP7_4_ALG0_STAGE0_A1_ADDR,
                         MOD_LP7_1_ALG0_STAGE0_B2_ADDR, MOD_LP7_1_ALG0_STAGE0_B1_ADDR, MOD_LP7_1_ALG0_STAGE0_B0_ADDR,
                         MOD_LP7_1_ALG0_STAGE0_A2_ADDR, MOD_LP7_1_ALG0_STAGE0_A1_ADDR,
                         MOD_LP7_2_ALG0_STAGE0_B2_ADDR, MOD_LP7_2_ALG0_STAGE0_B1_ADDR, MOD_LP7_2_ALG0_STAGE0_B0_ADDR,
                         MOD_LP7_2_ALG0_STAGE0_A2_ADDR, MOD_LP7_2_ALG0_STAGE0_A1_ADDR,
                         MOD_LP7_3_ALG0_STAGE0_B2_ADDR, MOD_LP7_3_ALG0_STAGE0_B1_ADDR, MOD_LP7_3_ALG0_STAGE0_B0_ADDR,
                         MOD_LP7_3_ALG0_STAGE0_A2_ADDR, MOD_LP7_3_ALG0_STAGE0_A1_ADDR,
                         MOD_LP7_4_ALG0_STAGE0_B2_ADDR, MOD_LP7_4_ALG0_STAGE0_B1_ADDR, MOD_LP7_4_ALG0_STAGE0_B0_ADDR,
                         MOD_LP7_4_ALG0_STAGE0_A2_ADDR, MOD_LP7_4_ALG0_STAGE0_A1_ADDR,
                         fs,
                         ptrdsp,
                         channel );
    layout->addWidget( xo );
    channel->addDspBlock( xo );

    phase = new QPhase( 1000.0, 1.0,
                      MOD_PHASE7_ALG0_STAGE0_B2_ADDR, MOD_PHASE7_ALG0_STAGE0_B1_ADDR, MOD_PHASE7_ALG0_STAGE0_B0_ADDR,
                      MOD_PHASE7_ALG0_STAGE0_A2_ADDR, MOD_PHASE7_ALG0_STAGE0_A1_ADDR,
                      fs,
                      ptrdsp,
                      channel );
    layout->addWidget( phase );
    channel->addDspBlock( phase );

    dly = new QDelay( 0.0, 48000.0, MOD_DELAY7_DELAYAMT_ADDR, ptrdsp, channel );
    layout->addWidget( dly );
    channel->addDspBlock( dly );

    gain = new QGain( 0.0, MOD_GAIN7_ALG0_TARGET_ADDR, ptrdsp, channel );
    layout->addWidget( gain );
    channel->addDspBlock( gain );

    output = new QOutputSelect( 1, 0, ptrdsp, channel );
    layout->addWidget( output );
    channel->addDspBlock( output );

    QObject::connect( lshelv, SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );
    QObject::connect( peq01,  SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );
    QObject::connect( peq02,  SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );
    QObject::connect( peq03,  SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );
    QObject::connect( peq04,  SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );
    QObject::connect( peq05,  SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );
    QObject::connect( peq06,  SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );
    QObject::connect( peq07,  SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );
    QObject::connect( peq08,  SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );
    QObject::connect( peq09,  SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );
    QObject::connect( peq10,  SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );
    QObject::connect( hshelv, SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );
    QObject::connect( xo,     SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );
    QObject::connect( phase,  SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );
    QObject::connect( dly,    SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );
    QObject::connect( gain,   SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );
    QObject::connect( output, SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );

    QObject::connect( peq01,  SIGNAL(importRewPeqs( QWidget* )), parent, SLOT(importRewPeqs( QWidget* )) );
    QObject::connect( peq02,  SIGNAL(importRewPeqs( QWidget* )), parent, SLOT(importRewPeqs( QWidget* )) );
    QObject::connect( peq03,  SIGNAL(importRewPeqs( QWidget* )), parent, SLOT(importRewPeqs( QWidget* )) );
    QObject::connect( peq04,  SIGNAL(importRewPeqs( QWidget* )), parent, SLOT(importRewPeqs( QWidget* )) );
    QObject::connect( peq05,  SIGNAL(importRewPeqs( QWidget* )), parent, SLOT(importRewPeqs( QWidget* )) );
    QObject::connect( peq06,  SIGNAL(importRewPeqs( QWidget* )), parent, SLOT(importRewPeqs( QWidget* )) );
    QObject::connect( peq07,  SIGNAL(importRewPeqs( QWidget* )), parent, SLOT(importRewPeqs( QWidget* )) );
    QObject::connect( peq08,  SIGNAL(importRewPeqs( QWidget* )), parent, SLOT(importRewPeqs( QWidget* )) );
    QObject::connect( peq09,  SIGNAL(importRewPeqs( QWidget* )), parent, SLOT(importRewPeqs( QWidget* )) );
    QObject::connect( peq10,  SIGNAL(importRewPeqs( QWidget* )), parent, SLOT(importRewPeqs( QWidget* )) );

    listChannels.append( channel );
  }
  else if( chn == 7 )
  {
    //--------------------------------------------------------------------------
    //--- Channel 8
    dspChannel.name = QString( "LFE" );

    input = new QInputSelect( 7, 
                              MOD_INPUTSELECT_8_NX1_1_ANALOG_ALG0_MONOMUXSIGMA300NS43INDEX_ADDR,
                              MOD_INPUTSELECT_8_NX1_1_UAC_ALG0_MONOMUXSIGMA300NS44INDEX_ADDR, 
                              MOD_INPUTSELECT_8_NX1_1_ESP32_ALG0_MONOMUXSIGMA300NS45INDEX_ADDR, 
                              MOD_INPUTSELECT_8_NX1_1_EXP_ALG0_MONOMUXSIGMA300NS46INDEX_ADDR, 
                              MOD_INPUTSELECT_8_NX1_1_SPDIF_ALG0_MONOMUXSIGMA300NS47INDEX_ADDR,
                              MOD_INPUTSELECT_8_NX1_1_ALG0_MONOMUXSIGMA300NS48INDEX_ADDR, 
                              ptrdsp, channel );
    layout->addWidget( input );
    channel->addDspBlock( input );
    channel->setName( dspChannel.name );

    lshelv = new QLowShelv( 0.0, 100.0, 1.0,
                            MOD_LOWSHELV8_ALG0_STAGE0_B2_ADDR, MOD_LOWSHELV8_ALG0_STAGE0_B1_ADDR, MOD_LOWSHELV8_ALG0_STAGE0_B0_ADDR,
                            MOD_LOWSHELV8_ALG0_STAGE0_A2_ADDR, MOD_LOWSHELV8_ALG0_STAGE0_A1_ADDR,
                            fs,
                            ptrdsp,
                            channel );
    layout->addWidget( lshelv );
    channel->addDspBlock( lshelv );

    peq01 = new QPeq( 0.0, 1000.0, 1.0,
                      MOD_PARAMEQ8_ALG0_STAGE0_B2_ADDR, MOD_PARAMEQ8_ALG0_STAGE0_B1_ADDR, MOD_PARAMEQ8_ALG0_STAGE0_B0_ADDR,
                      MOD_PARAMEQ8_ALG0_STAGE0_A2_ADDR, MOD_PARAMEQ8_ALG0_STAGE0_A1_ADDR,
                      fs,
                      ptrdsp,
                      channel );
    layout->addWidget( peq01 );
    channel->addDspBlock( peq01 );

    peq02 = new QPeq( 0.0, 2000.0, 2.0,
                      MOD_PARAMEQ8_ALG0_STAGE1_B2_ADDR, MOD_PARAMEQ8_ALG0_STAGE1_B1_ADDR, MOD_PARAMEQ8_ALG0_STAGE1_B0_ADDR,
                      MOD_PARAMEQ8_ALG0_STAGE1_A2_ADDR, MOD_PARAMEQ8_ALG0_STAGE1_A1_ADDR,
                      fs,
                      ptrdsp,
                      channel );
    layout->addWidget( peq02 );
    channel->addDspBlock( peq02 );

    peq03 = new QPeq( 0.0, 3000.0, 2.0,
                      MOD_PARAMEQ8_ALG0_STAGE2_B2_ADDR, MOD_PARAMEQ8_ALG0_STAGE2_B1_ADDR, MOD_PARAMEQ8_ALG0_STAGE2_B0_ADDR,
                      MOD_PARAMEQ8_ALG0_STAGE2_A2_ADDR, MOD_PARAMEQ8_ALG0_STAGE2_A1_ADDR,
                      fs,
                      ptrdsp,
                      channel );
    layout->addWidget( peq03 );
    channel->addDspBlock( peq03 );

    peq04 = new QPeq( 0.0, 4000.0, 2.0,
                      MOD_PARAMEQ8_ALG0_STAGE3_B2_ADDR, MOD_PARAMEQ8_ALG0_STAGE3_B1_ADDR, MOD_PARAMEQ8_ALG0_STAGE3_B0_ADDR,
                      MOD_PARAMEQ8_ALG0_STAGE3_A2_ADDR, MOD_PARAMEQ8_ALG0_STAGE3_A1_ADDR,
                      fs,
                      ptrdsp,
                      channel );
    layout->addWidget( peq04 );
    channel->addDspBlock( peq04 );

    peq05 = new QPeq( 0.0, 5000.0, 2.0,
                      MOD_PARAMEQ8_ALG0_STAGE4_B2_ADDR, MOD_PARAMEQ8_ALG0_STAGE4_B1_ADDR, MOD_PARAMEQ8_ALG0_STAGE4_B0_ADDR,
                      MOD_PARAMEQ8_ALG0_STAGE4_A2_ADDR, MOD_PARAMEQ8_ALG0_STAGE4_A1_ADDR,
                      fs,
                      ptrdsp,
                      channel );
    layout->addWidget( peq05 );
    channel->addDspBlock( peq05 );

    peq06 = new QPeq( 0.0, 6000.0, 2.0,
                      MOD_PARAMEQ8_ALG0_STAGE5_B2_ADDR, MOD_PARAMEQ8_ALG0_STAGE5_B1_ADDR, MOD_PARAMEQ8_ALG0_STAGE5_B0_ADDR,
                      MOD_PARAMEQ8_ALG0_STAGE5_A2_ADDR, MOD_PARAMEQ8_ALG0_STAGE5_A1_ADDR,
                      fs,
                      ptrdsp,
                      channel );
    layout->addWidget( peq06 );
    channel->addDspBlock( peq06 );

    peq07 = new QPeq( 0.0, 7000.0, 2.0,
                      MOD_PARAMEQ8_ALG0_STAGE6_B2_ADDR, MOD_PARAMEQ8_ALG0_STAGE6_B1_ADDR, MOD_PARAMEQ8_ALG0_STAGE6_B0_ADDR,
                      MOD_PARAMEQ8_ALG0_STAGE6_A2_ADDR, MOD_PARAMEQ8_ALG0_STAGE6_A1_ADDR,
                      fs,
                      ptrdsp,
                      channel );
    layout->addWidget( peq07 );
    channel->addDspBlock( peq07 );

    peq08 = new QPeq( 0.0, 8000.0, 2.0,
                      MOD_PARAMEQ8_ALG0_STAGE7_B2_ADDR, MOD_PARAMEQ8_ALG0_STAGE7_B1_ADDR, MOD_PARAMEQ8_ALG0_STAGE7_B0_ADDR,
                      MOD_PARAMEQ8_ALG0_STAGE7_A2_ADDR, MOD_PARAMEQ8_ALG0_STAGE7_A1_ADDR,
                      fs,
                      ptrdsp,
                      channel );
    layout->addWidget( peq08 );
    channel->addDspBlock( peq08 );

    peq09 = new QPeq( 0.0, 9000.0, 2.0,
                      MOD_PARAMEQ8_ALG0_STAGE8_B2_ADDR, MOD_PARAMEQ8_ALG0_STAGE8_B1_ADDR, MOD_PARAMEQ8_ALG0_STAGE8_B0_ADDR,
                      MOD_PARAMEQ8_ALG0_STAGE8_A2_ADDR, MOD_PARAMEQ8_ALG0_STAGE8_A1_ADDR,
                      fs,
                      ptrdsp,
                      channel );
    layout->addWidget( peq09 );
    channel->addDspBlock( peq09 );

    peq10 = new QPeq( 0.0, 10000.0, 2.0,
                      MOD_PARAMEQ8_ALG0_STAGE9_B2_ADDR, MOD_PARAMEQ8_ALG0_STAGE9_B1_ADDR, MOD_PARAMEQ8_ALG0_STAGE9_B0_ADDR,
                      MOD_PARAMEQ8_ALG0_STAGE9_A2_ADDR, MOD_PARAMEQ8_ALG0_STAGE9_A1_ADDR,
                      fs,
                      ptrdsp,
                      channel );
    layout->addWidget( peq10 );
    channel->addDspBlock( peq10 );

    hshelv = new QHighShelv( 0.0, 5000.0, 1.0,
                           MOD_HIGHSHELV8_ALG0_STAGE0_B2_ADDR, MOD_HIGHSHELV8_ALG0_STAGE0_B1_ADDR, MOD_HIGHSHELV8_ALG0_STAGE0_B0_ADDR,
                           MOD_HIGHSHELV8_ALG0_STAGE0_A2_ADDR, MOD_HIGHSHELV8_ALG0_STAGE0_A1_ADDR,
                           fs,
                           ptrdsp,
                           channel );
    layout->addWidget( hshelv );
    channel->addDspBlock( hshelv );

    lp = new QLowPass( QLowPass::kLinkwitzRiley12, 10000.0,
                       MOD_LP8_1_ALG0_STAGE0_B2_ADDR, MOD_LP8_1_ALG0_STAGE0_B1_ADDR, MOD_LP8_1_ALG0_STAGE0_B0_ADDR,
                       MOD_LP8_1_ALG0_STAGE0_A2_ADDR, MOD_LP8_1_ALG0_STAGE0_A1_ADDR,
                       MOD_LP8_2_ALG0_STAGE0_B2_ADDR, MOD_LP8_2_ALG0_STAGE0_B1_ADDR, MOD_LP8_2_ALG0_STAGE0_B0_ADDR,
                       MOD_LP8_2_ALG0_STAGE0_A2_ADDR, MOD_LP8_2_ALG0_STAGE0_A1_ADDR,
                       MOD_LP8_3_ALG0_STAGE0_B2_ADDR, MOD_LP8_3_ALG0_STAGE0_B1_ADDR, MOD_LP8_3_ALG0_STAGE0_B0_ADDR,
                       MOD_LP8_3_ALG0_STAGE0_A2_ADDR, MOD_LP8_3_ALG0_STAGE0_A1_ADDR,
                       MOD_LP8_4_ALG0_STAGE0_B2_ADDR, MOD_LP8_4_ALG0_STAGE0_B1_ADDR, MOD_LP8_4_ALG0_STAGE0_B0_ADDR,
                       MOD_LP8_4_ALG0_STAGE0_A2_ADDR, MOD_LP8_4_ALG0_STAGE0_A1_ADDR,
                       fs,
                       ptrdsp,
                       channel );
    layout->addWidget( lp );
    channel->addDspBlock( lp );
    lp->setBypassed( true );

    phase = new QPhase( 1000.0, 1.0,
                      MOD_PHASE8_ALG0_STAGE0_B2_ADDR, MOD_PHASE8_ALG0_STAGE0_B1_ADDR, MOD_PHASE8_ALG0_STAGE0_B0_ADDR,
                      MOD_PHASE8_ALG0_STAGE0_A2_ADDR, MOD_PHASE8_ALG0_STAGE0_A1_ADDR,
                      fs,
                      ptrdsp,
                      channel );
    layout->addWidget( phase );
    channel->addDspBlock( phase );

    dly = new QDelay( 0.0, 48000.0, MOD_DELAY8_DELAYAMT_ADDR, ptrdsp, channel );
    layout->addWidget( dly );
    channel->addDspBlock( dly );

    gain = new QGain( 0.0, MOD_GAIN8_ALG0_TARGET_ADDR, ptrdsp, channel );
    layout->addWidget( gain );
    channel->addDspBlock( gain );

    output = new QOutputSelect( 1, 0, ptrdsp, channel );
    layout->addWidget( output );
    channel->addDspBlock( output );

    QObject::connect( lshelv, SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );
    QObject::connect( peq01,  SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );
    QObject::connect( peq02,  SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );
    QObject::connect( peq03,  SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );
    QObject::connect( peq04,  SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );
    QObject::connect( peq05,  SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );
    QObject::connect( peq06,  SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );
    QObject::connect( peq07,  SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );
    QObject::connect( peq08,  SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );
    QObject::connect( peq09,  SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );
    QObject::connect( peq10,  SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );
    QObject::connect( hshelv, SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );
    QObject::connect( lp,     SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );
    QObject::connect( phase,  SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );
    QObject::connect( dly,    SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );
    QObject::connect( gain,   SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );
    QObject::connect( output, SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );

    QObject::connect( peq01,  SIGNAL(importRewPeqs( QWidget* )), parent, SLOT(importRewPeqs( QWidget* )) );
    QObject::connect( peq02,  SIGNAL(importRewPeqs( QWidget* )), parent, SLOT(importRewPeqs( QWidget* )) );
    QObject::connect( peq03,  SIGNAL(importRewPeqs( QWidget* )), parent, SLOT(importRewPeqs( QWidget* )) );
    QObject::connect( peq04,  SIGNAL(importRewPeqs( QWidget* )), parent, SLOT(importRewPeqs( QWidget* )) );
    QObject::connect( peq05,  SIGNAL(importRewPeqs( QWidget* )), parent, SLOT(importRewPeqs( QWidget* )) );
    QObject::connect( peq06,  SIGNAL(importRewPeqs( QWidget* )), parent, SLOT(importRewPeqs( QWidget* )) );
    QObject::connect( peq07,  SIGNAL(importRewPeqs( QWidget* )), parent, SLOT(importRewPeqs( QWidget* )) );
    QObject::connect( peq08,  SIGNAL(importRewPeqs( QWidget* )), parent, SLOT(importRewPeqs( QWidget* )) );
    QObject::connect( peq09,  SIGNAL(importRewPeqs( QWidget* )), parent, SLOT(importRewPeqs( QWidget* )) );
    QObject::connect( peq10,  SIGNAL(importRewPeqs( QWidget* )), parent, SLOT(importRewPeqs( QWidget* )) );

    listChannels.append( channel );
  }

  dsp->setMuteAddr( MOD_MASTERVOLUME_ALG0_TARGET_ADDR );

  dspChannel.layout = layout;
  dspChannel.channel = channel;
  dspChannel.gain = gain;

  flagSummation = false;

  return dspChannel;
}

//==============================================================================
/*!
 *
 */
void CPlugInHomeCinema71::setMasterVolume( double val, bool doSend )
{
  if( doSend )
  {
    QByteArray content;
    content.append( dsp->makeParameterForWifi( MOD_MASTERVOLUME_ALG0_TARGET_ADDR, static_cast<float>(pow( 10.0, val/20.0 )) ) );
    dsp->sendParameterWifi( content );
    dsp->setMasterVolume( val );
  }
  masterVolume = val;
}

//==============================================================================
/*!
 *
 */
uint16_t CPlugInHomeCinema71::getAddressMasterVolume( void )
{
  return MOD_MASTERVOLUME_ALG0_TARGET_ADDR;
}

//==============================================================================
/*!
 *
 */
void CPlugInHomeCinema71::setEnableVolumePoti( bool val, bool doSend )
{
  if( doSend )
  {
    QByteArray content;
    if( val )
      content.append( dsp->makeParameterForWifi( MOD_BYPASSVOLPOTI_MONOMUXSIGMA300NS49INDEX_ADDR, 0x00000000 ) );
    else
      content.append( dsp->makeParameterForWifi( MOD_BYPASSVOLPOTI_MONOMUXSIGMA300NS49INDEX_ADDR, 0x00000001 ) );
    dsp->sendParameterWifi( content );
  }
  enableVolumePoti = val;
}

//==============================================================================
/*! Get the parameters in DSP format. The parameters are returned with register 
 *  address followed by value dword ready to be sent via i2c to DSP.
 *
 * \return Byte array with parameters for DSP. 
 */
QByteArray CPlugInHomeCinema71::getDspParams( void )
{
  QByteArray content;
  if( enableVolumePoti )
    content.append( dsp->makeParameterForWifi( MOD_BYPASSVOLPOTI_MONOMUXSIGMA300NS49INDEX_ADDR, 0x00000000 ) );
  else
    content.append( dsp->makeParameterForWifi( MOD_BYPASSVOLPOTI_MONOMUXSIGMA300NS49INDEX_ADDR, 0x00000001 ) );
  return content;
}
