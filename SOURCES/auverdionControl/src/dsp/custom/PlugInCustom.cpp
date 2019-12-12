#include <cstdint>

#include <QObject>

#include "PlugInCustom.hpp"

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

using namespace Vektorraum;

//==============================================================================
/*! Constructor
 *
 */
CPlugInCustom::CPlugInCustom( tfloat samplerate )
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
CPlugInCustom::~CPlugInCustom( void )
{
}

//==============================================================================
/*!
 *
 */
tDspChannel CPlugInCustom::getGuiForChannel( unsigned int chn, tfloat, CFreeDspAurora* ptrdsp, QWidget* )
{
  tDspChannel dspChannel;

  dsp = ptrdsp;

  QHBoxLayout* layout = new QHBoxLayout;
  QChannel* channel = new QChannel;
  QGain* gain = nullptr;

  if( chn == 0 )
  {
    //--------------------------------------------------------------------------
    //--- Channel 1
    dspChannel.name = QString( "Channel 1" );
    channel->setName( dspChannel.name );
    layout->addWidget( new QLabel( "Custom PlugIn" ) );
    listChannels.append( channel );
  }
  else if( chn == 1 )
  {
    //--------------------------------------------------------------------------
    //--- Channel 2
    dspChannel.name = QString( "Channel 2" );
    channel->setName( dspChannel.name );
    listChannels.append( channel );
  }
  else if( chn == 2 )
  {
    //--------------------------------------------------------------------------
    //--- Channel 3
    dspChannel.name = QString( "Channel 3" );
    channel->setName( dspChannel.name );
    listChannels.append( channel );
  }
  else if( chn == 3 )
  {
    //--------------------------------------------------------------------------
    //--- Channel 4
    dspChannel.name = QString( "Channel 4" );
    channel->setName( dspChannel.name );
    listChannels.append( channel );
  }
  else if( chn == 4 )
  {
    //--------------------------------------------------------------------------
    //--- Channel 5
    dspChannel.name = QString( "Channel 5" );
    channel->setName( dspChannel.name );
    listChannels.append( channel );
  }
  else if( chn == 5 )
  {
    //--------------------------------------------------------------------------
    //--- Channel 6
    dspChannel.name = QString( "Channel 6" );
    channel->setName( dspChannel.name );
    listChannels.append( channel );
  }
  else if( chn == 6 )
  {
    //--------------------------------------------------------------------------
    //--- Channel 7
    dspChannel.name = QString( "Channel 7" );
    channel->setName( dspChannel.name );
    listChannels.append( channel );
  }
  else if( chn == 7 )
  {
    //--------------------------------------------------------------------------
    //--- Channel 8
    dspChannel.name = QString( "Channel 8" );
    channel->setName( dspChannel.name );
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
void CPlugInCustom::setMasterVolume( double val, bool )
{
  masterVolume = val;
}

//==============================================================================
/*!
 *
 */
uint16_t CPlugInCustom::getAddressMasterVolume( void )
{
  return 0; //MOD_MASTERVOLUME_ALG0_TARGET_ADDR;
}

//==============================================================================
/*!
 *
 */
void CPlugInCustom::setEnableVolumePoti( bool val, bool )
{
  enableVolumePoti = val;
}

//==============================================================================
/*! Get the parameters in DSP format. The parameters are returned with register 
 *  address followed by value dword ready to be sent via i2c to DSP.
 *
 * \return Byte array with parameters for DSP. 
 */
QByteArray CPlugInCustom::getDspParams( void )
{
  QByteArray content;
  return content;
}

