#ifndef QCROSSOVER_HPP
#define QCROSSOVER_HPP

#include <QWidget>
#include "QDspBlock.hpp"

#include "freeDSP-Aurora.hpp"

namespace Ui {
class QCrossover;
}

class QCrossover : public QDspBlock
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
    kParamB2_1_HP = 0,
    kParamB1_1_HP,
    kParamB0_1_HP,
    kParamA2_1_HP,
    kParamA1_1_HP,
    kParamB2_2_HP,
    kParamB1_2_HP,
    kParamB0_2_HP,
    kParamA2_2_HP,
    kParamA1_2_HP,
    kParamB2_3_HP,
    kParamB1_3_HP,
    kParamB0_3_HP,
    kParamA2_3_HP,
    kParamA1_3_HP,
    kParamB2_4_HP,
    kParamB1_4_HP,
    kParamB0_4_HP,
    kParamA2_4_HP,
    kParamA1_4_HP,
    kParamB2_1_LP,
    kParamB1_1_LP,
    kParamB0_1_LP,
    kParamA2_1_LP,
    kParamA1_1_LP,
    kParamB2_2_LP,
    kParamB1_2_LP,
    kParamB0_2_LP,
    kParamA2_2_LP,
    kParamA1_2_LP,
    kParamB2_3_LP,
    kParamB1_3_LP,
    kParamB0_3_LP,
    kParamA2_3_LP,
    kParamA1_3_LP,
    kParamB2_4_LP,
    kParamB1_4_LP,
    kParamB0_4_LP,
    kParamA2_4_LP,
    kParamA1_4_LP,
    kNumParams
  };

public:
  explicit QCrossover( tfilterdesign designHp, Vektorraum::tfloat fchp,
                       tfilterdesign designLp, Vektorraum::tfloat fclp,
                       uint16_t addrB2_1_HP, uint16_t addrB1_1_HP, uint16_t addrB0_1_HP,
                       uint16_t addrA2_1_HP, uint16_t addrA1_1_HP,
                       uint16_t addrB2_2_HP, uint16_t addrB1_2_HP, uint16_t addrB0_2_HP,
                       uint16_t addrA2_2_HP, uint16_t addrA1_2_HP,
                       uint16_t addrB2_3_HP, uint16_t addrB1_3_HP, uint16_t addrB0_3_HP,
                       uint16_t addrA2_3_HP, uint16_t addrA1_3_HP,
                       uint16_t addrB2_4_HP, uint16_t addrB1_4_HP, uint16_t addrB0_4_HP,
                       uint16_t addrA2_4_HP, uint16_t addrA1_4_HP,
                       uint16_t addrB2_1_LP, uint16_t addrB1_1_LP, uint16_t addrB0_1_LP,
                       uint16_t addrA2_1_LP, uint16_t addrA1_1_LP,
                       uint16_t addrB2_2_LP, uint16_t addrB1_2_LP, uint16_t addrB0_2_LP,
                       uint16_t addrA2_2_LP, uint16_t addrA1_2_LP,
                       uint16_t addrB2_3_LP, uint16_t addrB1_3_LP, uint16_t addrB0_3_LP,
                       uint16_t addrA2_3_LP, uint16_t addrA1_3_LP,
                       uint16_t addrB2_4_LP, uint16_t addrB1_4_LP, uint16_t addrB0_4_LP,
                       uint16_t addrA2_4_LP, uint16_t addrA1_4_LP,
                       Vektorraum::tfloat samplerate,
                       CFreeDspAurora* ptrdsp,
                       QWidget *parent = nullptr );
  ~QCrossover();

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
  void on_doubleSpinBoxFcHp_valueChanged( double  );
  void on_comboBoxTypeHp_currentIndexChanged( int  );

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
  Ui::QCrossover *ui;

  tfilterdesign filterDesignHp;
  tfilterdesign filterDesignLp;
  Vektorraum::tfloat Q_hp[4];
  Vektorraum::tfloat fc_hp[4];
  Vektorraum::tfloat Q_lp[4];
  Vektorraum::tfloat fc_lp[4];
  Vektorraum::tfloat coeffs_hp[4*5];
  Vektorraum::tfloat coeffs_lp[4*5];
  uint16_t addr[kNumParams];
  CFreeDspAurora* dsp;
  Vektorraum::tuint stages;
};

#endif // QCROSSOVER_HPP
