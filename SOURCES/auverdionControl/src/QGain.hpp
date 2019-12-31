#ifndef QGAIN_H
#define QGAIN_H

#include <QWidget>
#include "QDspBlock.hpp"

#include "vektorraum.h"

#include "freeDSP-Aurora.hpp"

namespace Ui {
class QGain;
}

class QGain : public QDspBlock
{
  Q_OBJECT

  enum
  {
    kTargetGain = 0,
    kNumParams
  };

public:
  explicit QGain( Vektorraum::tfloat V0, uint16_t gainaddr, CFreeDspAurora* ptrdsp, QWidget *parent = nullptr );
  ~QGain();

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
  void on_doubleSpinBoxGain_valueChanged(double arg1);
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
  Ui::QGain *ui;

  uint16_t addr[kNumParams];
  CFreeDspAurora* dsp;
};

#endif // QGAIN_H
