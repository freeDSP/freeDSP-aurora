#ifndef QPLUGIN8CHANNELSUSB_H
#define QPLUGIN8CHANNELSUSB_H

#include <QWidget>
#include <QHBoxLayout>
#include <QString>

#include "vektorraum.h"

#include "DspPlugIn.hpp"

class CPlugIn8ChannelsUSB : public CDspPlugin
{

public:
  explicit CPlugIn8ChannelsUSB( Vektorraum::tfloat samplerate );
  virtual ~CPlugIn8ChannelsUSB( void );

  //============================================================================
  /*!
   *
   */
  virtual unsigned int getNumChannels( void ) { return 8; }

  //============================================================================
  /*!
   *
   */
  virtual tDspChannel getGuiForChannel( unsigned int chn, Vektorraum::tfloat fs, CFreeDspAurora* ptrdsp, QWidget* parent );

  //============================================================================
  /*!
   *
   */
  virtual QString getChannelName( unsigned int channel )
  {
    if( channel == 0 )
      return QString( "Channel 1" );
    else if( channel == 1 )
      return QString( "Channel 2" );
    else if( channel == 2 )
      return QString( "Channel 3" );
    else if( channel == 3 )
      return QString( "Channel 4" );
    else if( channel == 4 )
      return QString( "Channel 5" );
    else if( channel == 5 )
      return QString( "Channel 6" );
    else if( channel == 6 )
      return QString( "Channel 7" );
    else if( channel == 7 )
      return QString( "Channel 8" );
    else
      return QString( "" );
  }

  //============================================================================
  /*!
   *
   */
  virtual void setMasterVolume( double val, bool doSend );

  //============================================================================
  /*!
   *
   */
  virtual double getMasterVolume( void )
  {
    return masterVolume;
  }

  //============================================================================
  /*!
   *
   */
  virtual uint16_t getAddressMasterVolume( void );

  //============================================================================
  /*!
   *
   */
  virtual uint32_t getPid( void )
  {
    return CFreeDspAurora::PLUGIN_8CHANNELS_USB;
  }

  //============================================================================
  /*!
   *
   */
  virtual void setEnableVolumePoti( bool val, bool doSend );

  //============================================================================
  /*! Get the parameters in DSP format. The parameters are returned with register 
   *  address followed by value dword ready to be sent via i2c to DSP.
   *
   * \return Byte array with parameters for DSP. 
   */
  QByteArray getDspParams( void );

  //============================================================================
  //
  // Member Variables
  //
  //============================================================================
private:
  

};

#endif
