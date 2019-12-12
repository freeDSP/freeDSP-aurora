#ifndef DSPPLUGIN_H
#define DSPPLUGIN_H

#include <QHBoxLayout>
#include <QString>
#include <QList>

#include "vektorraum.h"
#include "freeDSP-Aurora.hpp"

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

  virtual ~CDspPlugin( void )
  {
    qDebug()<<" ~CDspPlugin";
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

  virtual tDspChannel getGuiForChannel( unsigned int chn, Vektorraum::tfloat fs, CFreeDspAurora* ptrdsp, QWidget* parent ) = 0;

  virtual void setMasterVolume( double val, bool doSend ) = 0;

  virtual double getMasterVolume( void ) = 0;

  virtual uint32_t getPid( void ) = 0;

  //============================================================================
  /*!
   *
   */
  virtual uint16_t getAddressMasterVolume( void ) = 0;

  //============================================================================
  /*!
   *
   */
  virtual void setEnableVolumePoti( bool bypass, bool doSend ) = 0;

  //============================================================================
  /*!
   *
   */
  bool getEnableVolumePoti( void )
  {
    return enableVolumePoti;
  }

  
  //============================================================================
  /*! Returns a channel of the DSP-Plugin.
   *
   * \param chn Index of channel to be returned.
   */
  QChannel* getChannel( unsigned int chn )
  {
    return listChannels.at(chn);
  }

  //==============================================================================
  /*!
   */
  QByteArray getUserParams( void )
  {
    QByteArray content;
    content.append( static_cast<char>(enableVolumePoti) );
    return content;
  }

  //==============================================================================
  /*!
   */
  virtual QByteArray getDspParams( void ) = 0;

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
  CFreeDspAurora* dsp;
  double masterVolume;
  bool enableVolumePoti = false;
};

#endif
