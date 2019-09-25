#include <cstdint>

#include <QObject>

#include "PlugIn4FIRs.hpp"

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
#include "QFir.hpp"

#include "4FIRs_IC_1_PARAM.h"

using namespace Vektorraum;

//==============================================================================
/*! Constructor
 *
 */
CPlugIn4FIRs::CPlugIn4FIRs( tfloat samplerate )
{
  fs = samplerate;
  NFFT = 4096;

  //----------------------------------------------------------------------------
  //--- Init frequency vector
  //----------------------------------------------------------------------------
  tvector<tfloat> f( NFFT/2 + 1 );
  for( tuint n = 0; n < NFFT/2+1; n++ )
    f[n] = static_cast<tfloat>(n) * fs / static_cast<tfloat>(NFFT);
  freq = f;
}

//==============================================================================
/*! Destructor
 *
 */
CPlugIn4FIRs::~CPlugIn4FIRs( void )
{

}

//==============================================================================
/*!
 *
 */
tDspChannel CPlugIn4FIRs::getGuiForChannel( unsigned int chn, tfloat fs, CFreeDspAurora* ptrdsp, QWidget* parent )
{
  tDspChannel dspChannel;

  QInputSelect* input;
  QFir* fir;
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
  QDelay* dly;
  QGain* gain = nullptr;
  QOutputSelect* output;

  QHBoxLayout* layout = new QHBoxLayout;
  QChannel* channel = new QChannel;

  if( chn == 0 )
  {
    //--------------------------------------------------------------------------
    //--- Channel 1
    dspChannel.name = getChannelName(chn);

    input = new QInputSelect( 0, MOD_NX1_1_1_MONOMUXSIGMA300NS1INDEX_ADDR, ptrdsp, channel );
    layout->addWidget( input );
    channel->addDspBlock( input );
    channel->setName( dspChannel.name );

    fir = new QFir( MOD_FIR1_ALG0_FIRSIGMA300ALG1FIRCOEFF0_ADDR, NFFT, ptrdsp, channel );
    layout->addWidget( fir );
    channel->addDspBlock( fir );

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
    
    dly = new QDelay( 0.0, fs, MOD_DELAY1_DELAYAMT_ADDR, ptrdsp, channel );
    layout->addWidget( dly );
    channel->addDspBlock( dly ); 

    gain = new QGain( 0.0, MOD_GAIN1_ALG0_TARGET_ADDR, ptrdsp, channel );
    layout->addWidget( gain );
    channel->addDspBlock( gain );
 
    output = new QOutputSelect( 1, 0, ptrdsp, channel );
    layout->addWidget( output );
    channel->addDspBlock( output );

    QObject::connect( fir,    SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );
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
    dspChannel.name = getChannelName(chn);

    input = new QInputSelect( 1, MOD_NX1_1_2_MONOMUXSIGMA300NS2INDEX_ADDR, ptrdsp, channel );
    layout->addWidget( input );
    channel->addDspBlock( input );
    channel->setName( dspChannel.name );

    fir = new QFir( MOD_FIR2_ALG0_FIRSIGMA300ALG2FIRCOEFF0_ADDR, NFFT, ptrdsp, channel );
    layout->addWidget( fir );
    channel->addDspBlock( fir );

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

    dly = new QDelay( 0.0, fs, MOD_DELAY2_DELAYAMT_ADDR, ptrdsp, channel );
    layout->addWidget( dly );
    channel->addDspBlock( dly );

    gain = new QGain( 0.0, MOD_GAIN2_ALG0_TARGET_ADDR, ptrdsp, channel );
    layout->addWidget( gain );
    channel->addDspBlock( gain );

    output = new QOutputSelect( 1, 0, ptrdsp, channel );
    layout->addWidget( output );
    channel->addDspBlock( output );

    QObject::connect( fir,    SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );
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
    dspChannel.name = getChannelName(chn);

    input = new QInputSelect( 2, MOD_NX1_1_3_MONOMUXSIGMA300NS3INDEX_ADDR, ptrdsp, channel );
    layout->addWidget( input );
    channel->addDspBlock( input );
    channel->setName( dspChannel.name );

    fir = new QFir( MOD_FIR3_ALG0_FIRSIGMA300ALG3FIRCOEFF0_ADDR, NFFT, ptrdsp, channel );
    layout->addWidget( fir );
    channel->addDspBlock( fir );

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

    dly = new QDelay( 0.0, 48000.0, MOD_DELAY3_DELAYAMT_ADDR, ptrdsp, channel );
    layout->addWidget( dly );
    channel->addDspBlock( dly );

    gain = new QGain( 0.0, MOD_GAIN3_ALG0_TARGET_ADDR, ptrdsp, channel );
    layout->addWidget( gain );
    channel->addDspBlock( gain );

    output = new QOutputSelect( 1, 0, ptrdsp, channel );
    layout->addWidget( output );
    channel->addDspBlock( output );

    QObject::connect( fir,    SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );
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
    dspChannel.name = getChannelName(chn);

    input = new QInputSelect( 3, MOD_NX1_1_4_MONOMUXSIGMA300NS4INDEX_ADDR, ptrdsp, channel );
    layout->addWidget( input );
    channel->addDspBlock( input );
    channel->setName( dspChannel.name );

    fir = new QFir( MOD_FIR4_ALG0_FIRSIGMA300ALG4FIRCOEFF0_ADDR, NFFT, ptrdsp, channel );
    layout->addWidget( fir );
    channel->addDspBlock( fir );

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

    dly = new QDelay( 0.0, 48000.0, MOD_DELAY4_DELAYAMT_ADDR, ptrdsp, channel );
    layout->addWidget( dly );
    channel->addDspBlock( dly );

    gain = new QGain( 0.0, MOD_GAIN4_ALG0_TARGET_ADDR, ptrdsp, channel );
    layout->addWidget( gain );
    channel->addDspBlock( gain );

    output = new QOutputSelect( 1, 0, ptrdsp, channel );
    layout->addWidget( output );
    channel->addDspBlock( output );

    QObject::connect( fir,    SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );
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

  //dsp->setMuteAddr( MOD_MASTERVOLUME_ALG0_TARGET_ADDR );
  
  dspChannel.layout = layout;
  dspChannel.channel = channel;
  dspChannel.gain = gain;

  flagSummation = true;

  return dspChannel;
}

//==============================================================================
/*!
 *
 */
void CPlugIn4FIRs::setMasterVolume( double val, bool doSend )
{
  qDebug()<<"CPlugInHomeCinema71::setMasterVolume not implemented";
}

//==============================================================================
/*!
 *
 */
uint16_t CPlugIn4FIRs::getAddressMasterVolume( void )
{
  qDebug()<<"CPlugIn4FIRs::getAddressMasterVolume not implemented";
  return 0;
}
