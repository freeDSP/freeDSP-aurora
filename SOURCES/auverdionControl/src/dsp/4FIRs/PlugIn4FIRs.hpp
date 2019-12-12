#ifndef QPLUGIN4FIRS_H
#define QPLUGIN4FIRS_H

#include <QWidget>
#include <QHBoxLayout>
#include <QString>

#include "vektorraum.h"

#include "freeDSP-Aurora.hpp"
#include "DspPlugIn.hpp"

class CPlugIn4FIRs : public CDspPlugin
{

public:
  explicit CPlugIn4FIRs( Vektorraum::tfloat samplerate );
  virtual ~CPlugIn4FIRs( void );

  //============================================================================
  /*!
   *
   */
  virtual unsigned int getNumChannels( void ) { return 4; }

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
    return CFreeDspAurora::PLUGIN_4FIRS;
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
  unsigned int NFFT;

};

#endif
