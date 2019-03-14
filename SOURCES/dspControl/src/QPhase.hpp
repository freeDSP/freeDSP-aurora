#ifndef QPHASE_H
#define QPHASE_H

#include <QWidget>

#include "QDspBlock.hpp"

#include "vektorraum.h"

#include "freeDSP-Aurora.hpp"

namespace Ui {
class QPhase;
}

class QPhase : public QDspBlock
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
  explicit QPhase( Vektorraum::tfloat freq, Vektorraum::tfloat qfactor,
                   uint16_t addrB2, uint16_t addrB1, uint16_t addrB0,
                   uint16_t addrA2, uint16_t addrA1,
                   Vektorraum::tfloat samplerate,
                   CFreeDspAurora* ptrdsp, QWidget *parent = nullptr );
  ~QPhase();

  virtual Vektorraum::tvector<Vektorraum::tcomplex> getTransferFunction( void )
  {
    return H;
  }

  void update( Vektorraum::tvector<Vektorraum::tfloat> f );

  virtual void getUserParams( QByteArray* userParams );

  virtual void setUserParams( QByteArray& userParams, int& idx );

  unsigned int numParameter( void )
  {
    return kNumParams;
  }

  virtual void sendDspParameter( void );

  virtual uint32_t getNumBytes( void );

  virtual void writeDspParameter( void );

private:
  void updateCoeffs( void );

private slots:
  void on_doubleSpinBoxFc_valueChanged( double  );
  void on_doubleSpinBoxQ_valueChanged( double  );
  void on_pushButtonBypass_clicked();

  void on_checkBoxInvert_stateChanged(int arg1);

private:
  Ui::QPhase *ui;

  Vektorraum::tfloat fc;
  Vektorraum::tfloat Q;
  Vektorraum::tfloat coeffs[5];
  uint16_t addr[kNumParams];
  CFreeDspAurora* dsp = nullptr;
};

#endif // QPHASE_H
