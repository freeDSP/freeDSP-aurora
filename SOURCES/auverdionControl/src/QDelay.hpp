#ifndef QDELAY_H
#define QDELAY_H

#include <QWidget>

#include "QDspBlock.hpp"

#include "vektorraum.h"

#include "freeDSP-Aurora.hpp"

namespace Ui {
class QDelay;
}

class QDelay : public QDspBlock
{
  Q_OBJECT

  enum
  {
    kDelay = 0,
    kNumParams
  };

public:
  explicit QDelay( Vektorraum::tfloat dly, Vektorraum::tfloat fs, uint16_t delayaddr, CFreeDspAurora* ptrdsp, QWidget *parent = nullptr );
  ~QDelay();

  virtual Vektorraum::tvector<Vektorraum::tcomplex> getTransferFunction( void )
  {
    return H;
  }

  void update( Vektorraum::tvector<Vektorraum::tfloat> f );

  virtual QByteArray getUserParams( void );

  virtual void setUserParams( QByteArray& userParams, int& idx );

  unsigned int numParameter( void )
  {
    return kNumParams;
  }

  virtual void sendDspParameter( void );

  virtual uint32_t getNumBytes( void );

  virtual QByteArray getDspParams( void );

protected:
  void updateCoeffs( void ) { }

private slots:
  void on_doubleSpinBoxDelay_valueChanged( double arg1 );
  void on_pushButtonBypass_clicked();

protected slots:
  //============================================================================
  /*! 
   *
   */
  virtual void updateDsp( void )
  {
    sendDspParameter();
  }

private:
  Ui::QDelay *ui;

  Vektorraum::tuint delay;
  uint16_t addr[kNumParams];
  CFreeDspAurora* dsp;

};

#endif // QDELAY_H
