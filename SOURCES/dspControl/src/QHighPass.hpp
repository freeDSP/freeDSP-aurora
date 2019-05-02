#ifndef QHIGHPASS_HPP
#define QHIGHPASS_HPP

#include <QWidget>
#include "QDspBlock.hpp"

#include "freeDSP-Aurora.hpp"

namespace Ui {
class QHighPass;
}

class QHighPass : public QDspBlock
{
  Q_OBJECT

public:
  enum tfilterdesign
  {
    kBessel6,
    kBessel12,
    kBessel18,
    kBessel24,
    kButterworth6,
    kButterworth12,
    kButterworth18,
    kButterworth24,
    kLinkwitzRiley12,
    kLinkwitzRiley24,
    kLinkwitzRiley36,
    kLinkwitzRiley48
  };

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
    kParamB2_1 = 0,
    kParamB1_1,
    kParamB0_1,
    kParamA2_1,
    kParamA1_1,
    kParamB2_2,
    kParamB1_2,
    kParamB0_2,
    kParamA2_2,
    kParamA1_2,
    kParamB2_3,
    kParamB1_3,
    kParamB0_3,
    kParamA2_3,
    kParamA1_3,
    kParamB2_4,
    kParamB1_4,
    kParamB0_4,
    kParamA2_4,
    kParamA1_4,
    kNumParams
  };

public:
  explicit QHighPass( tfilterdesign design, Vektorraum::tfloat fc,
                      uint16_t addrB2_1, uint16_t addrB1_1, uint16_t addrB0_1,
                      uint16_t addrA2_1, uint16_t addrA1_1,
                      uint16_t addrB2_2, uint16_t addrB1_2, uint16_t addrB0_2,
                      uint16_t addrA2_2, uint16_t addrA1_2,
                      uint16_t addrB2_3, uint16_t addrB1_3, uint16_t addrB0_3,
                      uint16_t addrA2_3, uint16_t addrA1_3,
                      uint16_t addrB2_4, uint16_t addrB1_4, uint16_t addrB0_4,
                      uint16_t addrA2_4, uint16_t addrA1_4,
                      Vektorraum::tfloat samplerate,
                      CFreeDspAurora* ptrdsp,
                      QWidget *parent = nullptr );
  ~QHighPass();

  virtual Vektorraum::tvector<Vektorraum::tcomplex> getTransferFunction( void )
  {
    return H;
  }

  void update( Vektorraum::tvector<Vektorraum::tfloat> f );

  unsigned int numParameter( void )
  {
    return kNumParams;
  }

  virtual void sendDspParameter( void );

  virtual uint32_t getNumBytes( void );

  //virtual void writeDspParameter( void );

  void setName( QString newname );

  virtual void getUserParams( QByteArray* userParams );

  virtual void setUserParams( QByteArray& userParams, int& idx );

  virtual QByteArray getDspParams( void );

private:
  void updateCoeffs( void );

private slots:
  void on_doubleSpinBoxFc_valueChanged( double  );
  void on_comboBoxType_currentIndexChanged( int  );

  void on_pushButtonBypass_clicked();

private:
  Ui::QHighPass *ui;

  tfilterdesign filterDesign;
  //Vektorraum::tfloat Q[4];
  //Vektorraum::tfloat fc[4];
  Vektorraum::tfloat coeffs[4*5];
  uint16_t addr[kNumParams];
  CFreeDspAurora* dsp;
  Vektorraum::tuint stages;
};

#endif // QHIGHPASS_HPP
