#ifndef DSPPLUGIN_H
#define DSPPLUGIN_H

#include <QHBoxLayout>
#include <QString>

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

  void setDoSummation( bool yesno ) { flagSummation = yesno; } 

  bool doSummation( void ) { return flagSummation; }

  virtual QString getChannelName( int channel ) = 0;

protected:
  bool flagSummation;

private:
};

#endif
