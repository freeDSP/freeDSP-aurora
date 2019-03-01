#ifndef QPLUGINHOMECINEMA71_H
#define QPLUGINHOMECINEMA71_H

#include <QWidget>
#include <QHBoxLayout>
#include <QString>

#include "vektorraum.h"

#include "freeDSP-Aurora.hpp"
#include "DspPlugIn.hpp"

#include "8channels_IC_1_PARAM.h"

class CPlugInHomeCinema71 : public CDspPlugin
{

public:
  explicit CPlugInHomeCinema71( void );
  ~CPlugInHomeCinema71( void );

  //============================================================================
  /*!
   *
   */
  int getNumChannels( void ) { return 8; }

  //============================================================================
  /*!
   *
   */
  tDspChannel getGuiForChannel( int chn, Vektorraum::tfloat fs, CFreeDspAurora* ptrdsp, QWidget* parent );

  //============================================================================
  /*!
   *
   */
  virtual QString getChannelName( int channel )
  {
    if( channel == 0 )
      return QString( "Front Left" );
    else if( channel == 1 )
      return QString( "Front Right" );
    else if( channel == 2 )
      return QString( "Front Center" );
    else if( channel == 3 )
      return QString( "Rear Left" );
    else if( channel == 4 )
      return QString( "Rear Right" );
    else if( channel == 5 )
      return QString( "Side Left" );
    else if( channel == 6 )
      return QString( "Side Right" );
    else if( channel == 7 )
      return QString( "LFE" );
  }

};

#endif
