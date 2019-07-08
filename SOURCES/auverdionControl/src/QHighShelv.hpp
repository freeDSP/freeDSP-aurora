#ifndef QHIGHSHELV_HPP
#define QHIGHSHELV_HPP

#include <QWidget>
#include "QDspBlock.hpp"

#include "vektorraum.h"

#include "freeDSP-Aurora.hpp"

namespace Ui {
class QHighShelv;
}

class QHighShelv : public QDspBlock
{
  Q_OBJECT

private:
  enum
  {
    kB0 = 0,
    kB1,
    kB2,
    kA1,
    kA2
  };

  enum
  {
    kParamB2 = 0,
    kParamB1,
    kParamB0,
    kParamA2,
    kParamA1,
    kNumParams
  };

public:
  explicit QHighShelv( double gain, double freq, double slope,
                       uint16_t addrB2, uint16_t addrB1, uint16_t addrB0,
                       uint16_t addrA2, uint16_t addrA1,
                       Vektorraum::tfloat samplerate,
                       CFreeDspAurora* ptrdsp, QWidget *parent = nullptr );
  ~QHighShelv();

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

private:
  void updateCoeffs( void );

private slots:
  void on_doubleSpinBoxGain_valueChanged( double  );
  void on_doubleSpinBoxFc_valueChanged( double  );
  void on_doubleSpinBoxS_valueChanged( double  );
  void on_pushButtonBypass_clicked();

protected slots:
  //============================================================================
  /*! 
   *
   */
  virtual void updateDsp( void )
  {
    updateCoeffs();
    sendDspParameter();
  }

private:
  Ui::QHighShelv *ui;
  Vektorraum::tfloat fc;
  Vektorraum::tfloat S;
  Vektorraum::tfloat V0;
  Vektorraum::tfloat coeffs[5];
  uint16_t addr[kNumParams];
  CFreeDspAurora* dsp = nullptr;
};

#endif // QHIGHSHELV_HPP
