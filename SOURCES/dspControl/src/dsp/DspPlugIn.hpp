#ifndef DSPPLUGIN_H
#define DSPPLUGIN_H

#include <QHBoxLayout>
#include <QString>
#include <QList>

#include "vektorraum.h"

#include "QChannel.hpp"
#include "QGain.hpp"

typedef struct _tdspchannel
{
  QHBoxLayout* layout;
  QChannel* channel;
  QGain* gain;
  QString name;
} tDspChannel;

class CDspPlugin
{
public:
  explicit CDspPlugin( void )
  {
    flagSummation = true;
  }

  ~CDspPlugin( void )
  {
    
  }

  //============================================================================
  /*!
   *
   */
  Vektorraum::tvector<Vektorraum::tfloat> getFrequencyVector( void )
  {
    return freq;
  }

  void setDoSummation( bool yesno ) { flagSummation = yesno; } 

  bool doSummation( void ) { return flagSummation; }

  virtual QString getChannelName( unsigned int channel ) = 0;

  virtual unsigned int getNumChannels( void ) = 0;

  //============================================================================
  /*! Returns a channel of the DSP-Plugin.
   *
   * \param chn Index of channel to be returned.
   */
  QChannel* getChannel( unsigned int chn )
  {
    return listChannels.at(chn);
  }

  //============================================================================
  //
  // Member Variables
  //
  //============================================================================
protected:
  Vektorraum::tvector<Vektorraum::tfloat> freq;
  Vektorraum::tfloat fs;
  bool flagSummation;
  QList<QChannel*> listChannels;
};

#endif
