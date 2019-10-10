#include <QDebug>

#include "QCrossover.hpp"
#include "ui_QCrossover.h"

#include "vektorraum.h"

using namespace Vektorraum;

extern void enableGui( bool enable );

QCrossover::QCrossover( tfilterdesign designHp, tfloat fchp,
                        tfilterdesign designLp, tfloat fclp,
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
                        tfloat samplerate,
                        CFreeDspAurora* ptrdsp,
                        QWidget* parent ) :
  QDspBlock(parent), ui(new Ui::QCrossover)
{
  type = CROSSOVER;

  #if defined( __MACOSX__ )
  setFixedSize( QSize( 200, 185 ) );
  #elif defined( __WIN__ )
  setFixedSize( QSize( 200, 165 ) );
  #endif

  addr[kParamB2_1_HP] = addrB2_1_HP;
  addr[kParamB1_1_HP] = addrB1_1_HP;
  addr[kParamB0_1_HP] = addrB0_1_HP;
  addr[kParamA2_1_HP] = addrA2_1_HP;
  addr[kParamA1_1_HP] = addrA1_1_HP;
  addr[kParamB2_2_HP] = addrB2_2_HP;
  addr[kParamB1_2_HP] = addrB1_2_HP;
  addr[kParamB0_2_HP] = addrB0_2_HP;
  addr[kParamA2_2_HP] = addrA2_2_HP;
  addr[kParamA1_2_HP] = addrA1_2_HP;
  addr[kParamB2_3_HP] = addrB2_3_HP;
  addr[kParamB1_3_HP] = addrB1_3_HP;
  addr[kParamB0_3_HP] = addrB0_3_HP;
  addr[kParamA2_3_HP] = addrA2_3_HP;
  addr[kParamA1_3_HP] = addrA1_3_HP;
  addr[kParamB2_4_HP] = addrB2_4_HP;
  addr[kParamB1_4_HP] = addrB1_4_HP;
  addr[kParamB0_4_HP] = addrB0_4_HP;
  addr[kParamA2_4_HP] = addrA2_4_HP;
  addr[kParamA1_4_HP] = addrA1_4_HP;

  addr[kParamB2_1_LP] = addrB2_1_LP;
  addr[kParamB1_1_LP] = addrB1_1_LP;
  addr[kParamB0_1_LP] = addrB0_1_LP;
  addr[kParamA2_1_LP] = addrA2_1_LP;
  addr[kParamA1_1_LP] = addrA1_1_LP;
  addr[kParamB2_2_LP] = addrB2_2_LP;
  addr[kParamB1_2_LP] = addrB1_2_LP;
  addr[kParamB0_2_LP] = addrB0_2_LP;
  addr[kParamA2_2_LP] = addrA2_2_LP;
  addr[kParamA1_2_LP] = addrA1_2_LP;
  addr[kParamB2_3_LP] = addrB2_3_LP;
  addr[kParamB1_3_LP] = addrB1_3_LP;
  addr[kParamB0_3_LP] = addrB0_3_LP;
  addr[kParamA2_3_LP] = addrA2_3_LP;
  addr[kParamA1_3_LP] = addrA1_3_LP;
  addr[kParamB2_4_LP] = addrB2_4_LP;
  addr[kParamB1_4_LP] = addrB1_4_LP;
  addr[kParamB0_4_LP] = addrB0_4_LP;
  addr[kParamA2_4_LP] = addrA2_4_LP;
  addr[kParamA1_4_LP] = addrA1_4_LP;

  fs = samplerate;
  dsp = ptrdsp;

  ui->setupUi(this);
  ui->comboBoxTypeHp->blockSignals( true );
  ui->comboBoxTypeHp->addItem( "Bes 6dB",  kBessel6 );
  ui->comboBoxTypeHp->addItem( "Bes 12dB", kBessel12 );
  ui->comboBoxTypeHp->addItem( "Bes 18dB", kBessel18 );
  ui->comboBoxTypeHp->addItem( "Bes 24dB", kBessel24 );
  ui->comboBoxTypeHp->addItem( "But 6dB",  kButterworth6 );
  ui->comboBoxTypeHp->addItem( "But 12dB", kButterworth12 );
  ui->comboBoxTypeHp->addItem( "But 18dB", kButterworth18 );
  ui->comboBoxTypeHp->addItem( "But 24dB", kButterworth24 );
  ui->comboBoxTypeHp->addItem( "LR 12dB",  kLinkwitzRiley12 );
  ui->comboBoxTypeHp->addItem( "LR 24dB",  kLinkwitzRiley24 );
  ui->comboBoxTypeHp->addItem( "LR 36dB",  kLinkwitzRiley36 );
  ui->comboBoxTypeHp->addItem( "LR 48dB",  kLinkwitzRiley48 );
  ui->comboBoxTypeHp->setCurrentIndex( designHp );
  ui->comboBoxTypeHp->blockSignals( false );
  ui->doubleSpinBoxFcHp->blockSignals( true );
  ui->doubleSpinBoxFcHp->setAttribute( Qt::WA_MacShowFocusRect, 0 );
  ui->doubleSpinBoxFcHp->setValue( fchp );
  ui->doubleSpinBoxFcHp->blockSignals( false );

  ui->comboBoxTypeLp->blockSignals( true );
  ui->comboBoxTypeLp->addItem( "Bes 6dB",  kBessel6 );
  ui->comboBoxTypeLp->addItem( "Bes 12dB", kBessel12 );
  ui->comboBoxTypeLp->addItem( "Bes 18dB", kBessel18 );
  ui->comboBoxTypeLp->addItem( "Bes 24dB", kBessel24 );
  ui->comboBoxTypeLp->addItem( "But 6dB",  kButterworth6 );
  ui->comboBoxTypeLp->addItem( "But 12dB", kButterworth12 );
  ui->comboBoxTypeLp->addItem( "But 18dB", kButterworth18 );
  ui->comboBoxTypeLp->addItem( "But 24dB", kButterworth24 );
  ui->comboBoxTypeLp->addItem( "LR 12dB",  kLinkwitzRiley12 );
  ui->comboBoxTypeLp->addItem( "LR 24dB",  kLinkwitzRiley24 );
  ui->comboBoxTypeLp->addItem( "LR 36dB",  kLinkwitzRiley36 );
  ui->comboBoxTypeLp->addItem( "LR 48dB",  kLinkwitzRiley48 );
  ui->comboBoxTypeLp->setCurrentIndex( designLp );
  ui->comboBoxTypeLp->blockSignals( false );
  ui->doubleSpinBoxFcLp->blockSignals( true );
  ui->doubleSpinBoxFcLp->setAttribute( Qt::WA_MacShowFocusRect, 0 );
  ui->doubleSpinBoxFcLp->setValue( fclp );
  ui->doubleSpinBoxFcLp->blockSignals( false );

  //bypass = isbypassed;
  //ui->pushButtonBypass->setChecked( bypass );
}

QCrossover::~QCrossover()
{
  delete ui;
}

//------------------------------------------------------------------------------
/*! \brief Updates the filter.
 *
 */
void QCrossover::update( tvector<tfloat> f )
{
  updateCoeffs();
  tvector<tcomplex> z = exp( j * ( -2.0 * pi * f / fs ) );
  tvector<tcomplex> z2 = z*z;
  tfloat b0 = coeffs_hp[kB0];
  tfloat b1 = coeffs_hp[kB1];
  tfloat b2 = coeffs_hp[kB2];
  tfloat a1 = coeffs_hp[kA1];
  tfloat a2 = coeffs_hp[kA2];
  tfloat a0 = 1.0;
  H = ( b0 + b1*z + b2*z2 ) / ( a0 - a1*z - a2*z2 );

  for( tuint ii = 1; ii < 4; ii++ )
  {
    b0 = coeffs_hp[ii*5+kB0];
    b1 = coeffs_hp[ii*5+kB1];
    b2 = coeffs_hp[ii*5+kB2];
    a1 = coeffs_hp[ii*5+kA1];
    a2 = coeffs_hp[ii*5+kA2];
    a0 = 1.0;

    H = H * ( b0 + b1*z + b2*z2 ) / ( a0 - a1*z - a2*z2 );
  }
}

//------------------------------------------------------------------------------
/*!
 *
 */
void QCrossover::updateCoeffs( void )
{
  for( tuint ii = 0; ii < 4; ii++ )
  {
    Q_hp[ii] = -1.0;
    fc_hp[ii] = -1.0;
  }
  for( tuint ii = 0; ii < 4; ii++ )
  {
    Q_lp[ii] = -1.0;
    fc_lp[ii] = -1.0;
  }

  filterDesignHp = static_cast<tfilterdesign>(ui->comboBoxTypeHp->currentData().toInt());
  filterDesignLp = static_cast<tfilterdesign>(ui->comboBoxTypeLp->currentData().toInt());

  for( tuint ii = 0; ii < 4; ii++ )
  {
    tfloat b0 = 1.0;
    tfloat b1 = 0.0;
    tfloat b2 = 0.0;
    tfloat a1 = 0.0;
    tfloat a2 = 0.0;
    coeffs_hp[ii*5+kB0] = b0;
    coeffs_hp[ii*5+kB1] = b1;
    coeffs_hp[ii*5+kB2] = b2;
    coeffs_hp[ii*5+kA1] = a1;
    coeffs_hp[ii*5+kA2] = a2;
  }
  for( tuint ii = 0; ii < 4; ii++ )
  {
    tfloat b0 = 1.0;
    tfloat b1 = 0.0;
    tfloat b2 = 0.0;
    tfloat a1 = 0.0;
    tfloat a2 = 0.0;
    coeffs_lp[ii*5+kB0] = b0;
    coeffs_lp[ii*5+kB1] = b1;
    coeffs_lp[ii*5+kB2] = b2;
    coeffs_lp[ii*5+kA1] = a1;
    coeffs_lp[ii*5+kA2] = a2;
  }

  if( bypass )
  {
    for( tuint ii = 0; ii < 4; ii++ )
    {
      tfloat b0 = 1.0;
      tfloat b1 = 0.0;
      tfloat b2 = 0.0;
      tfloat a1 = 0.0;
      tfloat a2 = 0.0;
      coeffs_hp[ii*5+kB0] = b0;
      coeffs_hp[ii*5+kB1] = b1;
      coeffs_hp[ii*5+kB2] = b2;
      coeffs_hp[ii*5+kA1] = a1;
      coeffs_hp[ii*5+kA2] = a2;
    }

    for( tuint ii = 0; ii < 4; ii++ )
    {
      tfloat b0 = 1.0;
      tfloat b1 = 0.0;
      tfloat b2 = 0.0;
      tfloat a1 = 0.0;
      tfloat a2 = 0.0;
      coeffs_lp[ii*5+kB0] = b0;
      coeffs_lp[ii*5+kB1] = b1;
      coeffs_lp[ii*5+kB2] = b2;
      coeffs_lp[ii*5+kA1] = a1;
      coeffs_lp[ii*5+kA2] = a2;
    }
  }
  else
  {
    tfloat w0, alpha;
    tfloat a0, a1, a2;
    tfloat b0, b1, b2;

    tfloat sa[3];
    tfloat sb[3];
    tfloat za[3];
    tfloat zb[3];
    tfloat Omega, T, T2, wn;

    switch( filterDesignHp )
    {
    case kLinkwitzRiley12:
      Q_hp[0] = 0.5;
      fc_hp[0] = ui->doubleSpinBoxFcHp->value();

      w0 = 2.0 * pi * fc_hp[0] / fs;
      alpha = sin(w0) / (2.0 * Q_hp[0]);
      a0 = 1.0 + alpha;
      b0 = ( ( 1.0 + cos(w0) ) * 0.5 ) / a0;
      b1 = ( -( 1.0 + cos(w0) ) ) / a0;
      b2 = ( ( 1.0 + cos(w0) ) * 0.5 ) / a0;
      a1 = ( -2.0 * cos(w0) ) / a0;
      a2 = ( 1.0 - alpha ) / a0;
      a0 = 1.0;
      coeffs_hp[kB0] = b0;
      coeffs_hp[kB1] = b1;
      coeffs_hp[kB2] = b2;
      coeffs_hp[kA1] = (-1.0)*a1;
      coeffs_hp[kA2] = (-1.0)*a2;

      break;

    case kLinkwitzRiley24:
      Q_hp[0] = 0.71;
      Q_hp[1] = 0.71;
      fc_hp[0] = ui->doubleSpinBoxFcHp->value();
      fc_hp[1] = ui->doubleSpinBoxFcHp->value();

      w0 = 2.0 * pi * fc_hp[0] / fs;
      alpha = sin(w0) / (2.0 * Q_hp[0]);
      a0 = 1.0 + alpha;
      b0 = ( ( 1.0 + cos(w0) ) * 0.5 ) / a0;
      b1 = ( -( 1.0 + cos(w0) ) ) / a0;
      b2 = ( ( 1.0 + cos(w0) ) * 0.5 ) / a0;
      a1 = ( -2.0 * cos(w0) ) / a0;
      a2 = ( 1.0 - alpha ) / a0;
      a0 = 1.0;
      coeffs_hp[kB0] = b0;
      coeffs_hp[kB1] = b1;
      coeffs_hp[kB2] = b2;
      coeffs_hp[kA1] = (-1.0)*a1;
      coeffs_hp[kA2] = (-1.0)*a2;

      w0 = 2.0 * pi * fc_hp[1] / fs;
      alpha = sin(w0) / (2.0 * Q_hp[1]);
      a0 = 1.0 + alpha;
      b0 = ( ( 1.0 + cos(w0) ) * 0.5 ) / a0;
      b1 = ( -( 1.0 + cos(w0) ) ) / a0;
      b2 = ( ( 1.0 + cos(w0) ) * 0.5 ) / a0;
      a1 = ( -2.0 * cos(w0) ) / a0;
      a2 = ( 1.0 - alpha ) / a0;
      a0 = 1.0;
      coeffs_hp[5+kB0] = b0;
      coeffs_hp[5+kB1] = b1;
      coeffs_hp[5+kB2] = b2;
      coeffs_hp[5+kA1] = (-1.0)*a1;
      coeffs_hp[5+kA2] = (-1.0)*a2;

      break;

    case kLinkwitzRiley36:
      Q_hp[0] = 0.50;
      Q_hp[1] = 1.00;
      Q_hp[2] = 1.00;
      fc_hp[0] = ui->doubleSpinBoxFcHp->value();
      fc_hp[1] = ui->doubleSpinBoxFcHp->value();
      fc_hp[2] = ui->doubleSpinBoxFcHp->value();

      w0 = 2.0 * pi * fc_hp[0] / fs;
      alpha = sin(w0) / (2.0 * Q_hp[0]);
      a0 = 1.0 + alpha;
      b0 = ( ( 1.0 + cos(w0) ) * 0.5 ) / a0;
      b1 = ( -( 1.0 + cos(w0) ) ) / a0;
      b2 = ( ( 1.0 + cos(w0) ) * 0.5 ) / a0;
      a1 = ( -2.0 * cos(w0) ) / a0;
      a2 = ( 1.0 - alpha ) / a0;
      a0 = 1.0;
      coeffs_hp[kB0] = b0;
      coeffs_hp[kB1] = b1;
      coeffs_hp[kB2] = b2;
      coeffs_hp[kA1] = (-1.0)*a1;
      coeffs_hp[kA2] = (-1.0)*a2;

      w0 = 2.0 * pi * fc_hp[1] / fs;
      alpha = sin(w0) / (2.0 * Q_hp[1]);
      a0 = 1.0 + alpha;
      b0 = ( ( 1.0 + cos(w0) ) * 0.5 ) / a0;
      b1 = ( -( 1.0 + cos(w0) ) ) / a0;
      b2 = ( ( 1.0 + cos(w0) ) * 0.5 ) / a0;
      a1 = ( -2.0 * cos(w0) ) / a0;
      a2 = ( 1.0 - alpha ) / a0;
      a0 = 1.0;
      coeffs_hp[5+kB0] = b0;
      coeffs_hp[5+kB1] = b1;
      coeffs_hp[5+kB2] = b2;
      coeffs_hp[5+kA1] = (-1.0)*a1;
      coeffs_hp[5+kA2] = (-1.0)*a2;

      w0 = 2.0 * pi * fc_hp[2] / fs;
      alpha = sin(w0) / (2.0 * Q_hp[2]);
      a0 = 1.0 + alpha;
      b0 = ( ( 1.0 + cos(w0) ) * 0.5 ) / a0;
      b1 = ( -( 1.0 + cos(w0) ) ) / a0;
      b2 = ( ( 1.0 + cos(w0) ) * 0.5 ) / a0;
      a1 = ( -2.0 * cos(w0) ) / a0;
      a2 = ( 1.0 - alpha ) / a0;
      a0 = 1.0;
      coeffs_hp[10+kB0] = b0;
      coeffs_hp[10+kB1] = b1;
      coeffs_hp[10+kB2] = b2;
      coeffs_hp[10+kA1] = (-1.0)*a1;
      coeffs_hp[10+kA2] = (-1.0)*a2;

      break;

    case kLinkwitzRiley48:
      Q_hp[0] = 0.54;
      Q_hp[1] = 1.34;
      Q_hp[2] = 0.54;
      Q_hp[3] = 1.34;
      fc_hp[0] = ui->doubleSpinBoxFcHp->value();
      fc_hp[1] = ui->doubleSpinBoxFcHp->value();
      fc_hp[2] = ui->doubleSpinBoxFcHp->value();
      fc_hp[3] = ui->doubleSpinBoxFcHp->value();

      w0 = 2.0 * pi * fc_hp[0] / fs;
      alpha = sin(w0) / (2.0 * Q_hp[0]);
      a0 = 1.0 + alpha;
      b0 = ( ( 1.0 + cos(w0) ) * 0.5 ) / a0;
      b1 = ( -( 1.0 + cos(w0) ) ) / a0;
      b2 = ( ( 1.0 + cos(w0) ) * 0.5 ) / a0;
      a1 = ( -2.0 * cos(w0) ) / a0;
      a2 = ( 1.0 - alpha ) / a0;
      a0 = 1.0;
      coeffs_hp[kB0] = b0;
      coeffs_hp[kB1] = b1;
      coeffs_hp[kB2] = b2;
      coeffs_hp[kA1] = (-1.0)*a1;
      coeffs_hp[kA2] = (-1.0)*a2;

      w0 = 2.0 * pi * fc_hp[1] / fs;
      alpha = sin(w0) / (2.0 * Q_hp[1]);
      a0 = 1.0 + alpha;
      b0 = ( ( 1.0 + cos(w0) ) * 0.5 ) / a0;
      b1 = ( -( 1.0 + cos(w0) ) ) / a0;
      b2 = ( ( 1.0 + cos(w0) ) * 0.5 ) / a0;
      a1 = ( -2.0 * cos(w0) ) / a0;
      a2 = ( 1.0 - alpha ) / a0;
      a0 = 1.0;
      coeffs_hp[5+kB0] = b0;
      coeffs_hp[5+kB1] = b1;
      coeffs_hp[5+kB2] = b2;
      coeffs_hp[5+kA1] = (-1.0)*a1;
      coeffs_hp[5+kA2] = (-1.0)*a2;

      w0 = 2.0 * pi * fc_hp[2] / fs;
      alpha = sin(w0) / (2.0 * Q_hp[2]);
      a0 = 1.0 + alpha;
      b0 = ( ( 1.0 + cos(w0) ) * 0.5 ) / a0;
      b1 = ( -( 1.0 + cos(w0) ) ) / a0;
      b2 = ( ( 1.0 + cos(w0) ) * 0.5 ) / a0;
      a1 = ( -2.0 * cos(w0) ) / a0;
      a2 = ( 1.0 - alpha ) / a0;
      a0 = 1.0;
      coeffs_hp[10+kB0] = b0;
      coeffs_hp[10+kB1] = b1;
      coeffs_hp[10+kB2] = b2;
      coeffs_hp[10+kA1] = (-1.0)*a1;
      coeffs_hp[10+kA2] = (-1.0)*a2;

      w0 = 2.0 * pi * fc_hp[3] / fs;
      alpha = sin(w0) / (2.0 * Q_hp[3]);
      a0 = 1.0 + alpha;
      b0 = ( ( 1.0 + cos(w0) ) * 0.5 ) / a0;
      b1 = ( -( 1.0 + cos(w0) ) ) / a0;
      b2 = ( ( 1.0 + cos(w0) ) * 0.5 ) / a0;
      a1 = ( -2.0 * cos(w0) ) / a0;
      a2 = ( 1.0 - alpha ) / a0;
      a0 = 1.0;
      coeffs_hp[15+kB0] = b0;
      coeffs_hp[15+kB1] = b1;
      coeffs_hp[15+kB2] = b2;
      coeffs_hp[15+kA1] = (-1.0)*a1;
      coeffs_hp[15+kA2] = (-1.0)*a2;

      break;

    case kBessel6:
      stages = 1;
      Q_hp[0] = 0.0;
      fc_hp[0] = ui->doubleSpinBoxFcHp->value();

      T = 1.0/fs;
      T2 = T*T;

      Omega = 2.0*pi*fc_hp[0]/fs;
      wn  = 2.0/T * tan( Omega/2.0 );
      
      a0 = 0.0000; // bi
      a1 = 1.0000; // ai
      a2 = 1.0;
      b0 = 0.0;
      b1 = 0.0;
      b2 = 1.0;

      sa[0] = a2;
      sa[1] = a1 * wn;
      sa[2] = a0 * wn*wn;
      sb[0] = b2;
      sb[1] = b1;
      sb[2] = b0;

      zb[0] = 4.0*sb[0]    + 2.0*sb[1]*T + sb[2]*T2;
      zb[1] = 2.0*sb[2]*T2 - 8.0*sb[0];
      zb[2] = 4.0*sb[0]    - 2.0*sb[1]*T + sb[2]*T2;

      za[0] = 4.0*sa[0]    + 2.0*sa[1]*T + sa[2]*T2;
      za[1] = 2.0*sa[2]*T2 - 8.0*sa[0];
      za[2] = 4.0*sa[0]    - 2.0*sa[1]*T + sa[2]*T2;

      coeffs_hp[ kB0 ] = zb[0] / za[0];
      coeffs_hp[ kB1 ] = zb[1] / za[0];
      coeffs_hp[ kB2 ] = zb[2] / za[0];
      coeffs_hp[ kA1 ] = (-1.0)*za[1] / za[0];
      coeffs_hp[ kA2 ] = (-1.0)*za[2] / za[0];

      break;

    case kBessel12:
      stages = 1;
      Q_hp[0] = 0.577;
      fc_hp[0] = ui->doubleSpinBoxFcHp->value();

      Omega = 2.0*pi*fc_hp[0]/fs;
      T = 1.0/fs;
      T2 = T*T;
      wn  = 2.0/T * tan( Omega/2.0 );
      
      a0 = 0.6180;  // bi
      a1 = 1.3617;  // ai
      a2 = 1.0;
      b0 = 0.0;
      b1 = 0.0;
      b2 = 1.0;

      sa[0] = a2;
      sa[1] = a1 * wn;
      sa[2] = a0 * wn*wn;
      sb[0] = b2;
      sb[1] = b1;
      sb[2] = b0;

      zb[0] = 4.0*sb[0]    + 2.0*sb[1]*T + sb[2]*T2;
      zb[1] = 2.0*sb[2]*T2 - 8.0*sb[0];
      zb[2] = 4.0*sb[0]    - 2.0*sb[1]*T + sb[2]*T2;

      za[0] = 4.0*sa[0]    + 2.0*sa[1]*T + sa[2]*T2;
      za[1] = 2.0*sa[2]*T2 - 8.0*sa[0];
      za[2] = 4.0*sa[0]    - 2.0*sa[1]*T + sa[2]*T2;

      coeffs_hp[ kB0 ] = zb[0] / za[0];
      coeffs_hp[ kB1 ] = zb[1] / za[0];
      coeffs_hp[ kB2 ] = zb[2] / za[0];
      coeffs_hp[ kA1 ] = (-1.0)*za[1] / za[0];
      coeffs_hp[ kA2 ] = (-1.0)*za[2] / za[0];

      break;

    case kBessel18:
      stages = 2;
      Q_hp[0] = 0.0;
      Q_hp[1] = 0.69;
      fc_hp[0] = ui->doubleSpinBoxFcHp->value();
      fc_hp[1] = ui->doubleSpinBoxFcHp->value();

      T = 1.0/fs;
      T2 = T*T;

      Omega = 2.0*pi*fc_hp[0]/fs;
      wn  = 2.0/T * tan( Omega/2.0 );
      
      a0 = 0.0000; // bi
      a1 = 1.0000; // ai
      a2 = 1.0;
      b0 = 0.0;
      b1 = 0.0;
      b2 = 1.0;

      sa[0] = a2;
      sa[1] = a1 * wn;
      sa[2] = a0 * wn*wn;
      sb[0] = b2;
      sb[1] = b1;
      sb[2] = b0;

      zb[0] = 4.0*sb[0]    + 2.0*sb[1]*T + sb[2]*T2;
      zb[1] = 2.0*sb[2]*T2 - 8.0*sb[0];
      zb[2] = 4.0*sb[0]    - 2.0*sb[1]*T + sb[2]*T2;

      za[0] = 4.0*sa[0]    + 2.0*sa[1]*T + sa[2]*T2;
      za[1] = 2.0*sa[2]*T2 - 8.0*sa[0];
      za[2] = 4.0*sa[0]    - 2.0*sa[1]*T + sa[2]*T2;

      coeffs_hp[ kB0 ] = zb[0] / za[0];
      coeffs_hp[ kB1 ] = zb[1] / za[0];
      coeffs_hp[ kB2 ] = zb[2] / za[0];
      coeffs_hp[ kA1 ] = (-1.0)*za[1] / za[0];
      coeffs_hp[ kA2 ] = (-1.0)*za[2] / za[0];
     
      a0 = 0.4772;  // bi
      a1 = 0.9996;  // ai
      a2 = 1.0;
      b0 = 0.0;
      b1 = 0.0;
      b2 = 1.0;

      sa[0] = a2;
      sa[1] = a1 * wn;
      sa[2] = a0 * wn*wn;
      sb[0] = b2;
      sb[1] = b1;
      sb[2] = b0;

      zb[0] = 4.0*sb[0]    + 2.0*sb[1]*T + sb[2]*T2;
      zb[1] = 2.0*sb[2]*T2 - 8.0*sb[0];
      zb[2] = 4.0*sb[0]    - 2.0*sb[1]*T + sb[2]*T2;

      za[0] = 4.0*sa[0]    + 2.0*sa[1]*T + sa[2]*T2;
      za[1] = 2.0*sa[2]*T2 - 8.0*sa[0];
      za[2] = 4.0*sa[0]    - 2.0*sa[1]*T + sa[2]*T2;

      coeffs_hp[ 5 + kB0 ] = zb[0] / za[0];
      coeffs_hp[ 5 + kB1 ] = zb[1] / za[0];
      coeffs_hp[ 5 + kB2 ] = zb[2] / za[0];
      coeffs_hp[ 5 + kA1 ] = (-1.0)*za[1] / za[0];
      coeffs_hp[ 5 + kA2 ] = (-1.0)*za[2] / za[0];

      break;

    case kBessel24:
      stages = 2;
      Q_hp[0] = 0.52;
      Q_hp[1] = 0.81;
      fc_hp[0] = ui->doubleSpinBoxFcHp->value();
      fc_hp[1] = ui->doubleSpinBoxFcHp->value();
     
      T = 1.0/fs;
      T2 = T*T;

      Omega = 2.0*pi*fc_hp[0]/fs;
      wn  = 2.0/T * tan( Omega/2.0 );
      
      a0 = 0.4889;  // bi
      a1 = 1.3397;  // ai
      a2 = 1.0;
      b0 = 0.0;
      b1 = 0.0;
      b2 = 1.0;

      sa[0] = a2;
      sa[1] = a1 * wn;
      sa[2] = a0 * wn*wn;
      sb[0] = b2;
      sb[1] = b1;
      sb[2] = b0;

      zb[0] = 4.0*sb[0]    + 2.0*sb[1]*T + sb[2]*T2;
      zb[1] = 2.0*sb[2]*T2 - 8.0*sb[0];
      zb[2] = 4.0*sb[0]    - 2.0*sb[1]*T + sb[2]*T2;

      za[0] = 4.0*sa[0]    + 2.0*sa[1]*T + sa[2]*T2;
      za[1] = 2.0*sa[2]*T2 - 8.0*sa[0];
      za[2] = 4.0*sa[0]    - 2.0*sa[1]*T + sa[2]*T2;

      coeffs_hp[ kB0 ] = zb[0] / za[0];
      coeffs_hp[ kB1 ] = zb[1] / za[0];
      coeffs_hp[ kB2 ] = zb[2] / za[0];
      coeffs_hp[ kA1 ] = (-1.0)*za[1] / za[0];
      coeffs_hp[ kA2 ] = (-1.0)*za[2] / za[0];
     
      sa[0] = 0.3890 / (wn*wn);  // bi
      sa[1] = 0.7743 / wn;       // ai
      sa[2] = 1.0;
      sb[0] = 0.0;
      sb[1] = 0.0;
      sb[2] = 1.0;

      sa[0] = a2;
      sa[1] = a1 * wn;
      sa[2] = a0 * wn*wn;
      sb[0] = b2;
      sb[1] = b1;
      sb[2] = b0;

      zb[0] = 4.0*sb[0]    + 2.0*sb[1]*T + sb[2]*T2;
      zb[1] = 2.0*sb[2]*T2 - 8.0*sb[0];
      zb[2] = 4.0*sb[0]    - 2.0*sb[1]*T + sb[2]*T2;

      za[0] = 4.0*sa[0]    + 2.0*sa[1]*T + sa[2]*T2;
      za[1] = 2.0*sa[2]*T2 - 8.0*sa[0];
      za[2] = 4.0*sa[0]    - 2.0*sa[1]*T + sa[2]*T2;

      coeffs_hp[ 5 + kB0 ] = zb[0] / za[0];
      coeffs_hp[ 5 + kB1 ] = zb[1] / za[0];
      coeffs_hp[ 5 + kB2 ] = zb[2] / za[0];
      coeffs_hp[ 5 + kA1 ] = (-1.0)*za[1] / za[0];
      coeffs_hp[ 5 + kA2 ] = (-1.0)*za[2] / za[0];

      break;

    case kButterworth6:
      stages = 1;
      Q_hp[0] = 0.0;
      fc_hp[0] = ui->doubleSpinBoxFcHp->value();

      T = 1.0/fs;
      T2 = T*T;

      Omega = 2.0*pi*fc_hp[0]/fs;
      wn  = 2.0/T * tan( Omega/2.0 );
      
      a0 = 0.0000; // bi
      a1 = 1.0000; // ai
      a2 = 1.0;
      b0 = 0.0;
      b1 = 0.0;
      b2 = 1.0;

      sa[0] = a2;
      sa[1] = a1 * wn;
      sa[2] = a0 * wn*wn;
      sb[0] = b2;
      sb[1] = b1;
      sb[2] = b0;

      zb[0] = 4.0*sb[0]    + 2.0*sb[1]*T + sb[2]*T2;
      zb[1] = 2.0*sb[2]*T2 - 8.0*sb[0];
      zb[2] = 4.0*sb[0]    - 2.0*sb[1]*T + sb[2]*T2;

      za[0] = 4.0*sa[0]    + 2.0*sa[1]*T + sa[2]*T2;
      za[1] = 2.0*sa[2]*T2 - 8.0*sa[0];
      za[2] = 4.0*sa[0]    - 2.0*sa[1]*T + sa[2]*T2;

      coeffs_hp[ kB0 ] = zb[0] / za[0];
      coeffs_hp[ kB1 ] = zb[1] / za[0];
      coeffs_hp[ kB2 ] = zb[2] / za[0];
      coeffs_hp[ kA1 ] = (-1.0)*za[1] / za[0];
      coeffs_hp[ kA2 ] = (-1.0)*za[2] / za[0];

      break;

    case kButterworth12:
      stages = 1;
      Q_hp[0] = 0.71;
      fc_hp[0] = ui->doubleSpinBoxFcHp->value();

      Omega = 2.0*pi*fc_hp[0]/fs;
      T = 1.0/fs;
      T2 = T*T;
      wn  = 2.0/T * tan( Omega/2.0 );
      
      a0 = 1.0000;  // bi
      a1 = 1.4142;  // ai
      a2 = 1.0;
      b0 = 0.0;
      b1 = 0.0;
      b2 = 1.0;

      sa[0] = a2;
      sa[1] = a1 * wn;
      sa[2] = a0 * wn*wn;
      sb[0] = b2;
      sb[1] = b1;
      sb[2] = b0;

      zb[0] = 4.0*sb[0]    + 2.0*sb[1]*T + sb[2]*T2;
      zb[1] = 2.0*sb[2]*T2 - 8.0*sb[0];
      zb[2] = 4.0*sb[0]    - 2.0*sb[1]*T + sb[2]*T2;

      za[0] = 4.0*sa[0]    + 2.0*sa[1]*T + sa[2]*T2;
      za[1] = 2.0*sa[2]*T2 - 8.0*sa[0];
      za[2] = 4.0*sa[0]    - 2.0*sa[1]*T + sa[2]*T2;

      coeffs_hp[ kB0 ] = zb[0] / za[0];
      coeffs_hp[ kB1 ] = zb[1] / za[0];
      coeffs_hp[ kB2 ] = zb[2] / za[0];
      coeffs_hp[ kA1 ] = (-1.0)*za[1] / za[0];
      coeffs_hp[ kA2 ] = (-1.0)*za[2] / za[0];

      break;

    case kButterworth18:
      stages = 2;
      Q_hp[0] = 0.0;
      Q_hp[1] = 1.0;
      fc_hp[0] = ui->doubleSpinBoxFcHp->value();
      fc_hp[1] = ui->doubleSpinBoxFcHp->value();

      T = 1.0/fs;
      T2 = T*T;

      Omega = 2.0*pi*fc_hp[0]/fs;
      wn  = 2.0/T * tan( Omega/2.0 );
      
      a0 = 0.0000; // bi
      a1 = 1.0000; // ai
      a2 = 1.0;
      b0 = 0.0;
      b1 = 0.0;
      b2 = 1.0;

      sa[0] = a2;
      sa[1] = a1 * wn;
      sa[2] = a0 * wn*wn;
      sb[0] = b2;
      sb[1] = b1;
      sb[2] = b0;

      zb[0] = 4.0*sb[0]    + 2.0*sb[1]*T + sb[2]*T2;
      zb[1] = 2.0*sb[2]*T2 - 8.0*sb[0];
      zb[2] = 4.0*sb[0]    - 2.0*sb[1]*T + sb[2]*T2;

      za[0] = 4.0*sa[0]    + 2.0*sa[1]*T + sa[2]*T2;
      za[1] = 2.0*sa[2]*T2 - 8.0*sa[0];
      za[2] = 4.0*sa[0]    - 2.0*sa[1]*T + sa[2]*T2;

      coeffs_hp[ kB0 ] = zb[0] / za[0];
      coeffs_hp[ kB1 ] = zb[1] / za[0];
      coeffs_hp[ kB2 ] = zb[2] / za[0];
      coeffs_hp[ kA1 ] = (-1.0)*za[1] / za[0];
      coeffs_hp[ kA2 ] = (-1.0)*za[2] / za[0];
     
      a0 = 1.0000;  // bi
      a1 = 1.0000;  // ai
      a2 = 1.0;
      b0 = 0.0;
      b1 = 0.0;
      b2 = 1.0;

      sa[0] = a2;
      sa[1] = a1 * wn;
      sa[2] = a0 * wn*wn;
      sb[0] = b2;
      sb[1] = b1;
      sb[2] = b0;

      zb[0] = 4.0*sb[0]    + 2.0*sb[1]*T + sb[2]*T2;
      zb[1] = 2.0*sb[2]*T2 - 8.0*sb[0];
      zb[2] = 4.0*sb[0]    - 2.0*sb[1]*T + sb[2]*T2;

      za[0] = 4.0*sa[0]    + 2.0*sa[1]*T + sa[2]*T2;
      za[1] = 2.0*sa[2]*T2 - 8.0*sa[0];
      za[2] = 4.0*sa[0]    - 2.0*sa[1]*T + sa[2]*T2;

      coeffs_hp[ 5 + kB0 ] = zb[0] / za[0];
      coeffs_hp[ 5 + kB1 ] = zb[1] / za[0];
      coeffs_hp[ 5 + kB2 ] = zb[2] / za[0];
      coeffs_hp[ 5 + kA1 ] = (-1.0)*za[1] / za[0];
      coeffs_hp[ 5 + kA2 ] = (-1.0)*za[2] / za[0];

      break;

    case kButterworth24:
      stages = 2;
      Q_hp[0] = 0.54;
      Q_hp[1] = 1.31;
      fc_hp[0] = ui->doubleSpinBoxFcHp->value();
      fc_hp[1] = ui->doubleSpinBoxFcHp->value();

      T = 1.0/fs;
      T2 = T*T;

      Omega = 2.0*pi*fc_hp[0]/fs;
      wn  = 2.0/T * tan( Omega/2.0 );
      
      a0 = 1.0000; // bi
      a1 = 1.8478; // ai
      a2 = 1.0;
      b0 = 0.0;
      b1 = 0.0;
      b2 = 1.0;

      sa[0] = a2;
      sa[1] = a1 * wn;
      sa[2] = a0 * wn*wn;
      sb[0] = b2;
      sb[1] = b1;
      sb[2] = b0;

      zb[0] = 4.0*sb[0]    + 2.0*sb[1]*T + sb[2]*T2;
      zb[1] = 2.0*sb[2]*T2 - 8.0*sb[0];
      zb[2] = 4.0*sb[0]    - 2.0*sb[1]*T + sb[2]*T2;

      za[0] = 4.0*sa[0]    + 2.0*sa[1]*T + sa[2]*T2;
      za[1] = 2.0*sa[2]*T2 - 8.0*sa[0];
      za[2] = 4.0*sa[0]    - 2.0*sa[1]*T + sa[2]*T2;

      coeffs_hp[ kB0 ] = zb[0] / za[0];
      coeffs_hp[ kB1 ] = zb[1] / za[0];
      coeffs_hp[ kB2 ] = zb[2] / za[0];
      coeffs_hp[ kA1 ] = (-1.0)*za[1] / za[0];
      coeffs_hp[ kA2 ] = (-1.0)*za[2] / za[0];
     
      a0 = 1.0000;  // bi
      a1 = 0.7654;  // ai
      a2 = 1.0;
      b0 = 0.0;
      b1 = 0.0;
      b2 = 1.0;

      sa[0] = a2;
      sa[1] = a1 * wn;
      sa[2] = a0 * wn*wn;
      sb[0] = b2;
      sb[1] = b1;
      sb[2] = b0;

      zb[0] = 4.0*sb[0]    + 2.0*sb[1]*T + sb[2]*T2;
      zb[1] = 2.0*sb[2]*T2 - 8.0*sb[0];
      zb[2] = 4.0*sb[0]    - 2.0*sb[1]*T + sb[2]*T2;

      za[0] = 4.0*sa[0]    + 2.0*sa[1]*T + sa[2]*T2;
      za[1] = 2.0*sa[2]*T2 - 8.0*sa[0];
      za[2] = 4.0*sa[0]    - 2.0*sa[1]*T + sa[2]*T2;

      coeffs_hp[ 5 + kB0 ] = zb[0] / za[0];
      coeffs_hp[ 5 + kB1 ] = zb[1] / za[0];
      coeffs_hp[ 5 + kB2 ] = zb[2] / za[0];
      coeffs_hp[ 5 + kA1 ] = (-1.0)*za[1] / za[0];
      coeffs_hp[ 5 + kA2 ] = (-1.0)*za[2] / za[0];

      break;

    }

    switch( filterDesignLp )
    {
    case kLinkwitzRiley12:
      stages = 1;
      Q_lp[0] = 0.5;
      fc_lp[0] = ui->doubleSpinBoxFcLp->value();

      w0 = 2.0 * pi * fc_lp[0] / fs;
      alpha = sin(w0) / (2.0 * Q_lp[0]);
      a0 = 1.0 + alpha;
      b0 = ( ( 1.0 - cos(w0) ) * 0.5 ) / a0;
      b1 = (   1.0 - cos(w0) ) / a0;
      b2 = ( ( 1.0 - cos(w0) ) * 0.5 ) / a0;
      a1 = ( -2.0 * cos(w0) ) / a0;
      a2 = ( 1.0 - alpha ) / a0;
      a0 = 1.0;
      coeffs_lp[ kB0 ] = b0;
      coeffs_lp[ kB1 ] = b1;
      coeffs_lp[ kB2 ] = b2;
      coeffs_lp[ kA1 ] = (-1.0)*a1;
      coeffs_lp[ kA2 ] = (-1.0)*a2;

      break;

    case kLinkwitzRiley24:
      stages = 2;
      Q_lp[0] = 0.71;
      Q_lp[1] = 0.71;
      fc_lp[0] = ui->doubleSpinBoxFcLp->value();
      fc_lp[1] = ui->doubleSpinBoxFcLp->value();

      w0 = 2.0 * pi * fc_lp[0] / fs;
      alpha = sin(w0) / (2.0 * Q_lp[0]);
      a0 = 1.0 + alpha;
      b0 = ( ( 1.0 - cos(w0) ) * 0.5 ) / a0;
      b1 = (   1.0 - cos(w0) ) / a0;
      b2 = ( ( 1.0 - cos(w0) ) * 0.5 ) / a0;
      a1 = ( -2.0 * cos(w0) ) / a0;
      a2 = ( 1.0 - alpha ) / a0;
      a0 = 1.0;
      coeffs_lp[ kB0 ] = b0;
      coeffs_lp[ kB1 ] = b1;
      coeffs_lp[ kB2 ] = b2;
      coeffs_lp[ kA1 ] = (-1.0)*a1;
      coeffs_lp[ kA2 ] = (-1.0)*a2;

      w0 = 2.0 * pi * fc_lp[1] / fs;
      alpha = sin(w0) / (2.0 * Q_lp[1]);
      a0 = 1.0 + alpha;
      b0 = ( ( 1.0 - cos(w0) ) * 0.5 ) / a0;
      b1 = (   1.0 - cos(w0) ) / a0;
      b2 = ( ( 1.0 - cos(w0) ) * 0.5 ) / a0;
      a1 = ( -2.0 * cos(w0) ) / a0;
      a2 = ( 1.0 - alpha ) / a0;
      a0 = 1.0;
      coeffs_lp[ 5 + kB0 ] = b0;
      coeffs_lp[ 5 + kB1 ] = b1;
      coeffs_lp[ 5 + kB2 ] = b2;
      coeffs_lp[ 5 + kA1 ] = (-1.0)*a1;
      coeffs_lp[ 5 + kA2 ] = (-1.0)*a2;

      break;

    case kLinkwitzRiley36:
      stages = 3;
      Q_lp[0] = 0.50;
      Q_lp[1] = 1.00;
      Q_lp[2] = 1.00;
      fc_lp[0] = ui->doubleSpinBoxFcLp->value();
      fc_lp[1] = ui->doubleSpinBoxFcLp->value();
      fc_lp[2] = ui->doubleSpinBoxFcLp->value();

      w0 = 2.0 * pi * fc_lp[0] / fs;
      alpha = sin(w0) / (2.0 * Q_lp[0]);
      a0 = 1.0 + alpha;
      b0 = ( ( 1.0 - cos(w0) ) * 0.5 ) / a0;
      b1 = (   1.0 - cos(w0) ) / a0;
      b2 = ( ( 1.0 - cos(w0) ) * 0.5 ) / a0;
      a1 = ( -2.0 * cos(w0) ) / a0;
      a2 = ( 1.0 - alpha ) / a0;
      a0 = 1.0;
      coeffs_lp[ kB0 ] = b0;
      coeffs_lp[ kB1 ] = b1;
      coeffs_lp[ kB2 ] = b2;
      coeffs_lp[ kA1 ] = (-1.0)*a1;
      coeffs_lp[ kA2 ] = (-1.0)*a2;

      w0 = 2.0 * pi * fc_lp[1] / fs;
      alpha = sin(w0) / (2.0 * Q_lp[1]);
      a0 = 1.0 + alpha;
      b0 = ( ( 1.0 - cos(w0) ) * 0.5 ) / a0;
      b1 = (   1.0 - cos(w0) ) / a0;
      b2 = ( ( 1.0 - cos(w0) ) * 0.5 ) / a0;
      a1 = ( -2.0 * cos(w0) ) / a0;
      a2 = ( 1.0 - alpha ) / a0;
      a0 = 1.0;
      coeffs_lp[ 5 + kB0 ] = b0;
      coeffs_lp[ 5 + kB1 ] = b1;
      coeffs_lp[ 5 + kB2 ] = b2;
      coeffs_lp[ 5 + kA1 ] = (-1.0)*a1;
      coeffs_lp[ 5 + kA2 ] = (-1.0)*a2;

      w0 = 2.0 * pi * fc_lp[2] / fs;
      alpha = sin(w0) / (2.0 * Q_lp[2]);
      a0 = 1.0 + alpha;
      b0 = ( ( 1.0 - cos(w0) ) * 0.5 ) / a0;
      b1 = (   1.0 - cos(w0) ) / a0;
      b2 = ( ( 1.0 - cos(w0) ) * 0.5 ) / a0;
      a1 = ( -2.0 * cos(w0) ) / a0;
      a2 = ( 1.0 - alpha ) / a0;
      a0 = 1.0;
      coeffs_lp[ 10 + kB0 ] = b0;
      coeffs_lp[ 10 + kB1 ] = b1;
      coeffs_lp[ 10 + kB2 ] = b2;
      coeffs_lp[ 10 + kA1 ] = (-1.0)*a1;
      coeffs_lp[ 10 + kA2 ] = (-1.0)*a2;

      break;

    case kLinkwitzRiley48:
      stages = 4;
      Q_lp[0] = 0.54;
      Q_lp[1] = 1.34;
      Q_lp[2] = 0.54;
      Q_lp[3] = 1.34;
      fc_lp[0] = ui->doubleSpinBoxFcLp->value();
      fc_lp[1] = ui->doubleSpinBoxFcLp->value();
      fc_lp[2] = ui->doubleSpinBoxFcLp->value();
      fc_lp[3] = ui->doubleSpinBoxFcLp->value();

      w0 = 2.0 * pi * fc_lp[0] / fs;
      alpha = sin(w0) / (2.0 * Q_lp[0]);
      a0 = 1.0 + alpha;
      b0 = ( ( 1.0 - cos(w0) ) * 0.5 ) / a0;
      b1 = (   1.0 - cos(w0) ) / a0;
      b2 = ( ( 1.0 - cos(w0) ) * 0.5 ) / a0;
      a1 = ( -2.0 * cos(w0) ) / a0;
      a2 = ( 1.0 - alpha ) / a0;
      a0 = 1.0;
      coeffs_lp[ kB0 ] = b0;
      coeffs_lp[ kB1 ] = b1;
      coeffs_lp[ kB2 ] = b2;
      coeffs_lp[ kA1 ] = (-1.0)*a1;
      coeffs_lp[ kA2 ] = (-1.0)*a2;

      w0 = 2.0 * pi * fc_lp[1] / fs;
      alpha = sin(w0) / (2.0 * Q_lp[1]);
      a0 = 1.0 + alpha;
      b0 = ( ( 1.0 - cos(w0) ) * 0.5 ) / a0;
      b1 = (   1.0 - cos(w0) ) / a0;
      b2 = ( ( 1.0 - cos(w0) ) * 0.5 ) / a0;
      a1 = ( -2.0 * cos(w0) ) / a0;
      a2 = ( 1.0 - alpha ) / a0;
      a0 = 1.0;
      coeffs_lp[ 5 + kB0 ] = b0;
      coeffs_lp[ 5 + kB1 ] = b1;
      coeffs_lp[ 5 + kB2 ] = b2;
      coeffs_lp[ 5 + kA1 ] = (-1.0)*a1;
      coeffs_lp[ 5 + kA2 ] = (-1.0)*a2;

      w0 = 2.0 * pi * fc_lp[2] / fs;
      alpha = sin(w0) / (2.0 * Q_lp[2]);
      a0 = 1.0 + alpha;
      b0 = ( ( 1.0 - cos(w0) ) * 0.5 ) / a0;
      b1 = (   1.0 - cos(w0) ) / a0;
      b2 = ( ( 1.0 - cos(w0) ) * 0.5 ) / a0;
      a1 = ( -2.0 * cos(w0) ) / a0;
      a2 = ( 1.0 - alpha ) / a0;
      a0 = 1.0;
      coeffs_lp[ 10 + kB0 ] = b0;
      coeffs_lp[ 10 + kB1 ] = b1;
      coeffs_lp[ 10 + kB2 ] = b2;
      coeffs_lp[ 10 + kA1 ] = (-1.0)*a1;
      coeffs_lp[ 10 + kA2 ] = (-1.0)*a2;

      w0 = 2.0 * pi * fc_lp[3] / fs;
      alpha = sin(w0) / (2.0 * Q_lp[3]);
      a0 = 1.0 + alpha;
      b0 = ( ( 1.0 - cos(w0) ) * 0.5 ) / a0;
      b1 = (   1.0 - cos(w0) ) / a0;
      b2 = ( ( 1.0 - cos(w0) ) * 0.5 ) / a0;
      a1 = ( -2.0 * cos(w0) ) / a0;
      a2 = ( 1.0 - alpha ) / a0;
      a0 = 1.0;
      coeffs_lp[ 15 + kB0 ] = b0;
      coeffs_lp[ 15 + kB1 ] = b1;
      coeffs_lp[ 15 + kB2 ] = b2;
      coeffs_lp[ 15 + kA1 ] = (-1.0)*a1;
      coeffs_lp[ 15 + kA2 ] = (-1.0)*a2;

      break;

    case kBessel6:
      stages = 1;
      Q_lp[0] = 0.0;
      fc_lp[0] = ui->doubleSpinBoxFcLp->value();

      T = 1.0/fs;
      T2 = T*T;

      Omega = 2.0*pi*fc_lp[0]/fs;
      wn  = 2.0/T * tan( Omega/2.0 );
      
      sa[0] = 0.0000 / (wn*wn); // bi
      sa[1] = 1.0000 / wn;      // ai
      sa[2] = 1.0;
      sb[0] = 0.0;
      sb[1] = 0.0;
      sb[2] = 1.0;

      zb[0] = 4.0*sb[0]    + 2.0*sb[1]*T + sb[2]*T2;
      zb[1] = 2.0*sb[2]*T2 - 8.0*sb[0];
      zb[2] = 4.0*sb[0]    - 2.0*sb[1]*T + sb[2]*T2;

      za[0] = 4.0*sa[0]    + 2.0*sa[1]*T + sa[2]*T2;
      za[1] = 2.0*sa[2]*T2 - 8.0*sa[0];
      za[2] = 4.0*sa[0]    - 2.0*sa[1]*T + sa[2]*T2;

      coeffs_lp[ kB0 ] = zb[0] / za[0];
      coeffs_lp[ kB1 ] = zb[1] / za[0];
      coeffs_lp[ kB2 ] = zb[2] / za[0];
      coeffs_lp[ kA1 ] = (-1.0)*za[1] / za[0];
      coeffs_lp[ kA2 ] = (-1.0)*za[2] / za[0];

      //! \TODO Check, why calculation above does not work on ADAU1452
      a1 = pow( 2.7, -Omega ); 
      coeffs_lp[ kB0 ] = 1.0 - a1;
      coeffs_lp[ kB1 ] = 0.0;
      coeffs_lp[ kB2 ] = 0.0;
      coeffs_lp[ kA1 ] = a1;
      coeffs_lp[ kA2 ] = 0.0;

      break;

    case kBessel12:
      stages = 1;
      Q_lp[0] = 0.577;
      fc_lp[0] = ui->doubleSpinBoxFcLp->value();

      Omega = 2.0*pi*fc_lp[0]/fs;
      T = 1.0/fs;
      T2 = T*T;
      wn  = 2.0/T * tan( Omega/2.0 );
      
      sa[0] = 0.6180 / (wn*wn);  // bi
      sa[1] = 1.3617 / wn;       // ai
      sa[2] = 1.0;
      sb[0] = 0.0;
      sb[1] = 0.0;
      sb[2] = 1.0;

      zb[0] = 4.0*sb[0]    + 2.0*sb[1]*T + sb[2]*T2;
      zb[1] = 2.0*sb[2]*T2 - 8.0*sb[0];
      zb[2] = 4.0*sb[0]    - 2.0*sb[1]*T + sb[2]*T2;

      za[0] = 4.0*sa[0]    + 2.0*sa[1]*T + sa[2]*T2;
      za[1] = 2.0*sa[2]*T2 - 8.0*sa[0];
      za[2] = 4.0*sa[0]    - 2.0*sa[1]*T + sa[2]*T2;

      coeffs_lp[ kB0 ] = zb[0] / za[0];
      coeffs_lp[ kB1 ] = zb[1] / za[0];
      coeffs_lp[ kB2 ] = zb[2] / za[0];
      coeffs_lp[ kA1 ] = (-1.0)*za[1] / za[0];
      coeffs_lp[ kA2 ] = (-1.0)*za[2] / za[0];

      break;

    case kBessel18:
      stages = 2;
      Q_lp[0] = 0.0;
      Q_lp[1] = 0.69;
      fc_lp[0] = ui->doubleSpinBoxFcLp->value();
      fc_lp[1] = ui->doubleSpinBoxFcLp->value();

      T = 1.0/fs;
      T2 = T*T;

      Omega = 2.0*pi*fc_lp[0]/fs;
      wn  = 2.0/T * tan( Omega/2.0 );
      
      sa[0] = 0.0000 / (wn*wn); // bi
      sa[1] = 1.0000 / wn;      // ai
      sa[2] = 1.0;
      sb[0] = 0.0;
      sb[1] = 0.0;
      sb[2] = 1.0;

      zb[0] = 4.0*sb[0]    + 2.0*sb[1]*T + sb[2]*T2;
      zb[1] = 2.0*sb[2]*T2 - 8.0*sb[0];
      zb[2] = 4.0*sb[0]    - 2.0*sb[1]*T + sb[2]*T2;

      za[0] = 4.0*sa[0]    + 2.0*sa[1]*T + sa[2]*T2;
      za[1] = 2.0*sa[2]*T2 - 8.0*sa[0];
      za[2] = 4.0*sa[0]    - 2.0*sa[1]*T + sa[2]*T2;

      coeffs_lp[ kB0 ] = zb[0] / za[0];
      coeffs_lp[ kB1 ] = zb[1] / za[0];
      coeffs_lp[ kB2 ] = zb[2] / za[0];
      coeffs_lp[ kA1 ] = (-1.0)*za[1] / za[0];
      coeffs_lp[ kA2 ] = (-1.0)*za[2] / za[0];

      //! \TODO Check, why calculation above does not work on ADAU1452
      a1 = pow( 2.7, -Omega ); 
      coeffs_lp[ kB0 ] = 1.0 - a1;
      coeffs_lp[ kB1 ] = 0.0;
      coeffs_lp[ kB2 ] = 0.0;
      coeffs_lp[ kA1 ] = a1;
      coeffs_lp[ kA2 ] = 0.0;
     
      sa[0] = 0.4772 / (wn*wn);  // bi
      sa[1] = 0.9996 / wn;       // ai
      sa[2] = 1.0;
      sb[0] = 0.0;
      sb[1] = 0.0;
      sb[2] = 1.0;

      zb[0] = 4.0*sb[0]    + 2.0*sb[1]*T + sb[2]*T2;
      zb[1] = 2.0*sb[2]*T2 - 8.0*sb[0];
      zb[2] = 4.0*sb[0]    - 2.0*sb[1]*T + sb[2]*T2;

      za[0] = 4.0*sa[0]    + 2.0*sa[1]*T + sa[2]*T2;
      za[1] = 2.0*sa[2]*T2 - 8.0*sa[0];
      za[2] = 4.0*sa[0]    - 2.0*sa[1]*T + sa[2]*T2;

      coeffs_lp[ 5 + kB0 ] = zb[0] / za[0];
      coeffs_lp[ 5 + kB1 ] = zb[1] / za[0];
      coeffs_lp[ 5 + kB2 ] = zb[2] / za[0];
      coeffs_lp[ 5 + kA1 ] = (-1.0)*za[1] / za[0];
      coeffs_lp[ 5 + kA2 ] = (-1.0)*za[2] / za[0];

      break;

    case kBessel24:
      stages = 2;
      Q_lp[0] = 0.52;
      Q_lp[1] = 0.81;
      fc_lp[0] = ui->doubleSpinBoxFcLp->value();
      fc_lp[1] = ui->doubleSpinBoxFcLp->value();
     
      T = 1.0/fs;
      T2 = T*T;

      Omega = 2.0*pi*fc_lp[0]/fs;
      wn  = 2.0/T * tan( Omega/2.0 );
      
      sa[0] = 0.4889 / (wn*wn);  // bi
      sa[1] = 1.3397 / wn;       // ai
      sa[2] = 1.0;
      sb[0] = 0.0;
      sb[1] = 0.0;
      sb[2] = 1.0;

      zb[0] = 4.0*sb[0]    + 2.0*sb[1]*T + sb[2]*T2;
      zb[1] = 2.0*sb[2]*T2 - 8.0*sb[0];
      zb[2] = 4.0*sb[0]    - 2.0*sb[1]*T + sb[2]*T2;

      za[0] = 4.0*sa[0]    + 2.0*sa[1]*T + sa[2]*T2;
      za[1] = 2.0*sa[2]*T2 - 8.0*sa[0];
      za[2] = 4.0*sa[0]    - 2.0*sa[1]*T + sa[2]*T2;

      coeffs_lp[ kB0 ] = zb[0] / za[0];
      coeffs_lp[ kB1 ] = zb[1] / za[0];
      coeffs_lp[ kB2 ] = zb[2] / za[0];
      coeffs_lp[ kA1 ] = (-1.0)*za[1] / za[0];
      coeffs_lp[ kA2 ] = (-1.0)*za[2] / za[0];
     
      sa[0] = 0.3890 / (wn*wn);  // bi
      sa[1] = 0.7743 / wn;       // ai
      sa[2] = 1.0;
      sb[0] = 0.0;
      sb[1] = 0.0;
      sb[2] = 1.0;

      zb[0] = 4.0*sb[0]    + 2.0*sb[1]*T + sb[2]*T2;
      zb[1] = 2.0*sb[2]*T2 - 8.0*sb[0];
      zb[2] = 4.0*sb[0]    - 2.0*sb[1]*T + sb[2]*T2;

      za[0] = 4.0*sa[0]    + 2.0*sa[1]*T + sa[2]*T2;
      za[1] = 2.0*sa[2]*T2 - 8.0*sa[0];
      za[2] = 4.0*sa[0]    - 2.0*sa[1]*T + sa[2]*T2;

      coeffs_lp[ 5 + kB0 ] = zb[0] / za[0];
      coeffs_lp[ 5 + kB1 ] = zb[1] / za[0];
      coeffs_lp[ 5 + kB2 ] = zb[2] / za[0];
      coeffs_lp[ 5 + kA1 ] = (-1.0)*za[1] / za[0];
      coeffs_lp[ 5 + kA2 ] = (-1.0)*za[2] / za[0];

      break;

    case kButterworth6:
      stages = 1;
      Q_lp[0] = 0.0;
      fc_lp[0] = ui->doubleSpinBoxFcLp->value();

      T = 1.0/fs;
      T2 = T*T;

      Omega = 2.0*pi*fc_lp[0]/fs;
      wn  = 2.0/T * tan( Omega/2.0 );
      
      sa[0] = 0.0000 / (wn*wn); // bi
      sa[1] = 1.0000 / wn;      // ai
      sa[2] = 1.0;
      sb[0] = 0.0;
      sb[1] = 0.0;
      sb[2] = 1.0;

      zb[0] = 4.0*sb[0]    + 2.0*sb[1]*T + sb[2]*T2;
      zb[1] = 2.0*sb[2]*T2 - 8.0*sb[0];
      zb[2] = 4.0*sb[0]    - 2.0*sb[1]*T + sb[2]*T2;

      za[0] = 4.0*sa[0]    + 2.0*sa[1]*T + sa[2]*T2;
      za[1] = 2.0*sa[2]*T2 - 8.0*sa[0];
      za[2] = 4.0*sa[0]    - 2.0*sa[1]*T + sa[2]*T2;

      coeffs_lp[ kB0 ] = zb[0] / za[0];
      coeffs_lp[ kB1 ] = zb[1] / za[0];
      coeffs_lp[ kB2 ] = zb[2] / za[0];
      coeffs_lp[ kA1 ] = (-1.0)*za[1] / za[0];
      coeffs_lp[ kA2 ] = (-1.0)*za[2] / za[0];

      //! \TODO Check, why calculation above does not work on ADAU1452
      a1 = pow( 2.7, -Omega ); 
      coeffs_lp[ kB0 ] = 1.0 - a1;
      coeffs_lp[ kB1 ] = 0.0;
      coeffs_lp[ kB2 ] = 0.0;
      coeffs_lp[ kA1 ] = a1;
      coeffs_lp[ kA2 ] = 0.0;

      break;

    case kButterworth12:
      stages = 1;
      Q_lp[0] = 0.71;
      fc_lp[0] = ui->doubleSpinBoxFcLp->value();

      Omega = 2.0*pi*fc_lp[0]/fs;
      T = 1.0/fs;
      T2 = T*T;
      wn  = 2.0/T * tan( Omega/2.0 );
      
      sa[0] = 1.0000 / (wn*wn);  // bi
      sa[1] = 1.4142 / wn;       // ai
      sa[2] = 1.0;
      sb[0] = 0.0;
      sb[1] = 0.0;
      sb[2] = 1.0;

      zb[0] = 4.0*sb[0]    + 2.0*sb[1]*T + sb[2]*T2;
      zb[1] = 2.0*sb[2]*T2 - 8.0*sb[0];
      zb[2] = 4.0*sb[0]    - 2.0*sb[1]*T + sb[2]*T2;

      za[0] = 4.0*sa[0]    + 2.0*sa[1]*T + sa[2]*T2;
      za[1] = 2.0*sa[2]*T2 - 8.0*sa[0];
      za[2] = 4.0*sa[0]    - 2.0*sa[1]*T + sa[2]*T2;

      coeffs_lp[ kB0 ] = zb[0] / za[0];
      coeffs_lp[ kB1 ] = zb[1] / za[0];
      coeffs_lp[ kB2 ] = zb[2] / za[0];
      coeffs_lp[ kA1 ] = (-1.0)*za[1] / za[0];
      coeffs_lp[ kA2 ] = (-1.0)*za[2] / za[0];

      break;

    case kButterworth18:
      stages = 2;
      Q_lp[0] = 0.0;
      Q_lp[1] = 1.0;
      fc_lp[0] = ui->doubleSpinBoxFcLp->value();
      fc_lp[1] = ui->doubleSpinBoxFcLp->value();

      T = 1.0/fs;
      T2 = T*T;

      Omega = 2.0*pi*fc_lp[0]/fs;
      wn  = 2.0/T * tan( Omega/2.0 );
      
      sa[0] = 0.0000 / (wn*wn); // bi
      sa[1] = 1.0000 / wn;      // ai
      sa[2] = 1.0;
      sb[0] = 0.0;
      sb[1] = 0.0;
      sb[2] = 1.0;

      zb[0] = 4.0*sb[0]    + 2.0*sb[1]*T + sb[2]*T2;
      zb[1] = 2.0*sb[2]*T2 - 8.0*sb[0];
      zb[2] = 4.0*sb[0]    - 2.0*sb[1]*T + sb[2]*T2;

      za[0] = 4.0*sa[0]    + 2.0*sa[1]*T + sa[2]*T2;
      za[1] = 2.0*sa[2]*T2 - 8.0*sa[0];
      za[2] = 4.0*sa[0]    - 2.0*sa[1]*T + sa[2]*T2;

      coeffs_lp[ kB0 ] = zb[0] / za[0];
      coeffs_lp[ kB1 ] = zb[1] / za[0];
      coeffs_lp[ kB2 ] = zb[2] / za[0];
      coeffs_lp[ kA1 ] = (-1.0)*za[1] / za[0];
      coeffs_lp[ kA2 ] = (-1.0)*za[2] / za[0];

      //! \TODO Check, why calculation above does not work on ADAU1452
      a1 = pow( 2.7, -Omega ); 
      coeffs_lp[ kB0 ] = 1.0 - a1;
      coeffs_lp[ kB1 ] = 0.0;
      coeffs_lp[ kB2 ] = 0.0;
      coeffs_lp[ kA1 ] = a1;
      coeffs_lp[ kA2 ] = 0.0;
     
      sa[0] = 1.0000 / (wn*wn);  // bi
      sa[1] = 1.0000 / wn;       // ai
      sa[2] = 1.0;
      sb[0] = 0.0;
      sb[1] = 0.0;
      sb[2] = 1.0;

      zb[0] = 4.0*sb[0]    + 2.0*sb[1]*T + sb[2]*T2;
      zb[1] = 2.0*sb[2]*T2 - 8.0*sb[0];
      zb[2] = 4.0*sb[0]    - 2.0*sb[1]*T + sb[2]*T2;

      za[0] = 4.0*sa[0]    + 2.0*sa[1]*T + sa[2]*T2;
      za[1] = 2.0*sa[2]*T2 - 8.0*sa[0];
      za[2] = 4.0*sa[0]    - 2.0*sa[1]*T + sa[2]*T2;

      coeffs_lp[ 5 + kB0 ] = zb[0] / za[0];
      coeffs_lp[ 5 + kB1 ] = zb[1] / za[0];
      coeffs_lp[ 5 + kB2 ] = zb[2] / za[0];
      coeffs_lp[ 5 + kA1 ] = (-1.0)*za[1] / za[0];
      coeffs_lp[ 5 + kA2 ] = (-1.0)*za[2] / za[0];

      break;

    case kButterworth24:
      stages = 2;
      Q_lp[0] = 0.54;
      Q_lp[1] = 1.31;
      fc_lp[0] = ui->doubleSpinBoxFcLp->value();
      fc_lp[1] = ui->doubleSpinBoxFcLp->value();

      T = 1.0/fs;
      T2 = T*T;

      Omega = 2.0*pi*fc_lp[0]/fs;
      wn  = 2.0/T * tan( Omega/2.0 );
      
      sa[0] = 1.0000 / (wn*wn); // bi
      sa[1] = 1.8478 / wn;      // ai
      sa[2] = 1.0;
      sb[0] = 0.0;
      sb[1] = 0.0;
      sb[2] = 1.0;

      zb[0] = 4.0*sb[0]    + 2.0*sb[1]*T + sb[2]*T2;
      zb[1] = 2.0*sb[2]*T2 - 8.0*sb[0];
      zb[2] = 4.0*sb[0]    - 2.0*sb[1]*T + sb[2]*T2;

      za[0] = 4.0*sa[0]    + 2.0*sa[1]*T + sa[2]*T2;
      za[1] = 2.0*sa[2]*T2 - 8.0*sa[0];
      za[2] = 4.0*sa[0]    - 2.0*sa[1]*T + sa[2]*T2;

      coeffs_lp[ kB0 ] = zb[0] / za[0];
      coeffs_lp[ kB1 ] = zb[1] / za[0];
      coeffs_lp[ kB2 ] = zb[2] / za[0];
      coeffs_lp[ kA1 ] = (-1.0)*za[1] / za[0];
      coeffs_lp[ kA2 ] = (-1.0)*za[2] / za[0];
     
      sa[0] = 1.0000 / (wn*wn);  // bi
      sa[1] = 0.7654 / wn;       // ai
      sa[2] = 1.0;
      sb[0] = 0.0;
      sb[1] = 0.0;
      sb[2] = 1.0;

      zb[0] = 4.0*sb[0]    + 2.0*sb[1]*T + sb[2]*T2;
      zb[1] = 2.0*sb[2]*T2 - 8.0*sb[0];
      zb[2] = 4.0*sb[0]    - 2.0*sb[1]*T + sb[2]*T2;

      za[0] = 4.0*sa[0]    + 2.0*sa[1]*T + sa[2]*T2;
      za[1] = 2.0*sa[2]*T2 - 8.0*sa[0];
      za[2] = 4.0*sa[0]    - 2.0*sa[1]*T + sa[2]*T2;

      coeffs_lp[ 5 + kB0 ] = zb[0] / za[0];
      coeffs_lp[ 5 + kB1 ] = zb[1] / za[0];
      coeffs_lp[ 5 + kB2 ] = zb[2] / za[0];
      coeffs_lp[ 5 + kA1 ] = (-1.0)*za[1] / za[0];
      coeffs_lp[ 5 + kA2 ] = (-1.0)*za[2] / za[0];

      break;
    }

  }
}

//------------------------------------------------------------------------------
/*!
 *
 */
void QCrossover::on_doubleSpinBoxFcHp_valueChanged( double  )
{
  updateCoeffs();
  //sendDspParameter();
  emit valueChanged();
  timerDspUpdate.stop();
  timerDspUpdate.start( DSPUPDATELATENCY );
}

//------------------------------------------------------------------------------
/*!
 *
 */
void QCrossover::on_comboBoxTypeHp_currentIndexChanged( int  )
{
  updateCoeffs();
  sendDspParameter();
  emit valueChanged();
}

//------------------------------------------------------------------------------
/*!
 *
 */
void QCrossover::on_pushButtonBypass_clicked()
{
  bypass = ui->pushButtonBypass->isChecked();
  updateCoeffs();
  sendDspParameter();
  emit valueChanged();
}

//------------------------------------------------------------------------------
/*!
 *
 */
void QCrossover::sendDspParameter( void )
{
  QByteArray content;

  enableGui( false );

  content.append( dsp->muteSequence() );

  content.append( dsp->makeParameterForWifi( addr[kParamB2_1_HP], static_cast<float>(coeffs_hp[kB2]) ) );
  content.append( dsp->makeParameterForWifi( addr[kParamB1_1_HP], static_cast<float>(coeffs_hp[kB1]) ) );
  content.append( dsp->makeParameterForWifi( addr[kParamB0_1_HP], static_cast<float>(coeffs_hp[kB0]) ) );
  content.append( dsp->makeParameterForWifi( addr[kParamA2_1_HP], static_cast<float>(coeffs_hp[kA2]) ) );
  content.append( dsp->makeParameterForWifi( addr[kParamA1_1_HP], static_cast<float>(coeffs_hp[kA1]) ) );
  dsp->sendParameterWifi( content );

  content.clear();
  content.append( dsp->makeParameterForWifi( addr[kParamB2_2_HP], static_cast<float>(coeffs_hp[5+kB2]) ) );
  content.append( dsp->makeParameterForWifi( addr[kParamB1_2_HP], static_cast<float>(coeffs_hp[5+kB1]) ) );
  content.append( dsp->makeParameterForWifi( addr[kParamB0_2_HP], static_cast<float>(coeffs_hp[5+kB0]) ) );
  content.append( dsp->makeParameterForWifi( addr[kParamA2_2_HP], static_cast<float>(coeffs_hp[5+kA2]) ) );
  content.append( dsp->makeParameterForWifi( addr[kParamA1_2_HP], static_cast<float>(coeffs_hp[5+kA1]) ) );
  dsp->sendParameterWifi( content );

  content.clear();
  content.append( dsp->makeParameterForWifi( addr[kParamB2_3_HP], static_cast<float>(coeffs_hp[2*5+kB2]) ) );
  content.append( dsp->makeParameterForWifi( addr[kParamB1_3_HP], static_cast<float>(coeffs_hp[2*5+kB1]) ) );
  content.append( dsp->makeParameterForWifi( addr[kParamB0_3_HP], static_cast<float>(coeffs_hp[2*5+kB0]) ) );
  content.append( dsp->makeParameterForWifi( addr[kParamA2_3_HP], static_cast<float>(coeffs_hp[2*5+kA2]) ) );
  content.append( dsp->makeParameterForWifi( addr[kParamA1_3_HP], static_cast<float>(coeffs_hp[2*5+kA1]) ) );
  dsp->sendParameterWifi( content );

  content.clear();
  content.append( dsp->makeParameterForWifi( addr[kParamB2_4_HP], static_cast<float>(coeffs_hp[3*5+kB2]) ) );
  content.append( dsp->makeParameterForWifi( addr[kParamB1_4_HP], static_cast<float>(coeffs_hp[3*5+kB1]) ) );
  content.append( dsp->makeParameterForWifi( addr[kParamB0_4_HP], static_cast<float>(coeffs_hp[3*5+kB0]) ) );
  content.append( dsp->makeParameterForWifi( addr[kParamA2_4_HP], static_cast<float>(coeffs_hp[3*5+kA2]) ) );
  content.append( dsp->makeParameterForWifi( addr[kParamA1_4_HP], static_cast<float>(coeffs_hp[3*5+kA1]) ) );
  dsp->sendParameterWifi( content );

  content.clear();
  content.append( dsp->makeParameterForWifi( addr[kParamB2_1_LP], static_cast<float>(coeffs_lp[kB2]) ) );
  content.append( dsp->makeParameterForWifi( addr[kParamB1_1_LP], static_cast<float>(coeffs_lp[kB1]) ) );
  content.append( dsp->makeParameterForWifi( addr[kParamB0_1_LP], static_cast<float>(coeffs_lp[kB0]) ) );
  content.append( dsp->makeParameterForWifi( addr[kParamA2_1_LP], static_cast<float>(coeffs_lp[kA2]) ) );
  content.append( dsp->makeParameterForWifi( addr[kParamA1_1_LP], static_cast<float>(coeffs_lp[kA1]) ) );
  dsp->sendParameterWifi( content );

  content.clear();
  content.append( dsp->makeParameterForWifi( addr[kParamB2_2_LP], static_cast<float>(coeffs_lp[5+kB2]) ) );
  content.append( dsp->makeParameterForWifi( addr[kParamB1_2_LP], static_cast<float>(coeffs_lp[5+kB1]) ) );
  content.append( dsp->makeParameterForWifi( addr[kParamB0_2_LP], static_cast<float>(coeffs_lp[5+kB0]) ) );
  content.append( dsp->makeParameterForWifi( addr[kParamA2_2_LP], static_cast<float>(coeffs_lp[5+kA2]) ) );
  content.append( dsp->makeParameterForWifi( addr[kParamA1_2_LP], static_cast<float>(coeffs_lp[5+kA1]) ) );
  dsp->sendParameterWifi( content );

  content.clear();
  content.append( dsp->makeParameterForWifi( addr[kParamB2_3_LP], static_cast<float>(coeffs_lp[2*5+kB2]) ) );
  content.append( dsp->makeParameterForWifi( addr[kParamB1_3_LP], static_cast<float>(coeffs_lp[2*5+kB1]) ) );
  content.append( dsp->makeParameterForWifi( addr[kParamB0_3_LP], static_cast<float>(coeffs_lp[2*5+kB0]) ) );
  content.append( dsp->makeParameterForWifi( addr[kParamA2_3_LP], static_cast<float>(coeffs_lp[2*5+kA2]) ) );
  content.append( dsp->makeParameterForWifi( addr[kParamA1_3_LP], static_cast<float>(coeffs_lp[2*5+kA1]) ) );
  dsp->sendParameterWifi( content );

  content.clear();
  content.append( dsp->makeParameterForWifi( addr[kParamB2_4_LP], static_cast<float>(coeffs_lp[3*5+kB2]) ) );
  content.append( dsp->makeParameterForWifi( addr[kParamB1_4_LP], static_cast<float>(coeffs_lp[3*5+kB1]) ) );
  content.append( dsp->makeParameterForWifi( addr[kParamB0_4_LP], static_cast<float>(coeffs_lp[3*5+kB0]) ) );
  content.append( dsp->makeParameterForWifi( addr[kParamA2_4_LP], static_cast<float>(coeffs_lp[3*5+kA2]) ) );
  content.append( dsp->makeParameterForWifi( addr[kParamA1_4_LP], static_cast<float>(coeffs_lp[3*5+kA1]) ) );
    
  content.append( dsp->unmuteSequence() );

  dsp->sendParameterWifi( content );

  enableGui( true );
}

//------------------------------------------------------------------------------
/*!
 *
 */
uint32_t QCrossover::getNumBytes( void )
{
  return (2*5*4 + 4*5*4) * 2;
}

//==============================================================================
/*!
 */
QByteArray QCrossover::getUserParams( void )
{
  QByteArray content;
  content.append( static_cast<char>(filterDesignHp) );
  float fc_hp = static_cast<float>(ui->doubleSpinBoxFcHp->value());
  content.append( reinterpret_cast<const char*>(&fc_hp), sizeof(fc_hp) );
  content.append( static_cast<uint8_t>(filterDesignLp) );
  float fc_lp = static_cast<float>(ui->doubleSpinBoxFcLp->value());
  content.append( reinterpret_cast<const char*>(&fc_lp), sizeof(fc_lp) );
  bypass = ui->pushButtonBypass->isChecked();
  content.append( reinterpret_cast<const char*>(&bypass), sizeof(bypass) );
  return content;
}

//==============================================================================
/*!
 */
void QCrossover::setUserParams( QByteArray& userParams, int& idx )
{
  QByteArray param;

  if( userParams.size() >= idx + 10 )
  {
    filterDesignHp = static_cast<tfilterdesign>(userParams.at(idx));
    idx++;
    param.append( userParams.at(idx) );
    idx++;
    param.append( userParams.at(idx) );
    idx++;
    param.append( userParams.at(idx) );
    idx++;
    param.append( userParams.at(idx) );
    idx++;

    float fc_hp = *reinterpret_cast<const float*>(param.data());

    filterDesignLp = static_cast<tfilterdesign>(userParams.at(idx));
    idx++;
    
    param.clear();
    param.append( userParams.at(idx) );
    idx++;
    param.append( userParams.at(idx) );
    idx++;
    param.append( userParams.at(idx) );
    idx++;
    param.append( userParams.at(idx) );
    idx++;

    float fc_lp = *reinterpret_cast<const float*>(param.data());

    bypass = static_cast<bool>(userParams.at(idx));
    idx++;

    ui->comboBoxTypeHp->blockSignals( true );
    int index = ui->comboBoxTypeHp->findData( filterDesignHp );
    if ( index != -1 )
      ui->comboBoxTypeHp->setCurrentIndex( index );
    ui->comboBoxTypeHp->blockSignals( false );
    ui->doubleSpinBoxFcHp->blockSignals( true );
    ui->doubleSpinBoxFcHp->setValue( static_cast<double>(fc_hp) );
    ui->doubleSpinBoxFcHp->blockSignals( false );

    ui->comboBoxTypeLp->blockSignals( true );
    index = ui->comboBoxTypeLp->findData( filterDesignLp );
    if ( index != -1 )
      ui->comboBoxTypeLp->setCurrentIndex(index);
    ui->comboBoxTypeLp->blockSignals( false );
    ui->doubleSpinBoxFcLp->blockSignals( true );
    ui->doubleSpinBoxFcLp->setValue( fc_lp );
    ui->doubleSpinBoxFcLp->blockSignals( false );

    ui->pushButtonBypass->blockSignals( true );
    ui->pushButtonBypass->setChecked( bypass );
    ui->pushButtonBypass->blockSignals( false );
  }
  else
    qDebug()<<"QCrossover::setUserParams: Not enough data";
}

//==============================================================================
/*!
 */
QByteArray QCrossover::getDspParams( void )
{
  QByteArray content;

  content.append( dsp->makeParameterForWifi( addr[kParamB2_1_HP], static_cast<float>(coeffs_hp[kB2]) ) );
  content.append( dsp->makeParameterForWifi( addr[kParamB1_1_HP], static_cast<float>(coeffs_hp[kB1]) ) );
  content.append( dsp->makeParameterForWifi( addr[kParamB0_1_HP], static_cast<float>(coeffs_hp[kB0]) ) );
  content.append( dsp->makeParameterForWifi( addr[kParamA2_1_HP], static_cast<float>(coeffs_hp[kA2]) ) );
  content.append( dsp->makeParameterForWifi( addr[kParamA1_1_HP], static_cast<float>(coeffs_hp[kA1]) ) );

  content.append( dsp->makeParameterForWifi( addr[kParamB2_2_HP], static_cast<float>(coeffs_hp[5+kB2]) ) );
  content.append( dsp->makeParameterForWifi( addr[kParamB1_2_HP], static_cast<float>(coeffs_hp[5+kB1]) ) );
  content.append( dsp->makeParameterForWifi( addr[kParamB0_2_HP], static_cast<float>(coeffs_hp[5+kB0]) ) );
  content.append( dsp->makeParameterForWifi( addr[kParamA2_2_HP], static_cast<float>(coeffs_hp[5+kA2]) ) );
  content.append( dsp->makeParameterForWifi( addr[kParamA1_2_HP], static_cast<float>(coeffs_hp[5+kA1]) ) );

  content.append( dsp->makeParameterForWifi( addr[kParamB2_3_HP], static_cast<float>(coeffs_hp[2*5+kB2]) ) );
  content.append( dsp->makeParameterForWifi( addr[kParamB1_3_HP], static_cast<float>(coeffs_hp[2*5+kB1]) ) );
  content.append( dsp->makeParameterForWifi( addr[kParamB0_3_HP], static_cast<float>(coeffs_hp[2*5+kB0]) ) );
  content.append( dsp->makeParameterForWifi( addr[kParamA2_3_HP], static_cast<float>(coeffs_hp[2*5+kA2]) ) );
  content.append( dsp->makeParameterForWifi( addr[kParamA1_3_HP], static_cast<float>(coeffs_hp[2*5+kA1]) ) );

  content.append( dsp->makeParameterForWifi( addr[kParamB2_4_HP], static_cast<float>(coeffs_hp[3*5+kB2]) ) );
  content.append( dsp->makeParameterForWifi( addr[kParamB1_4_HP], static_cast<float>(coeffs_hp[3*5+kB1]) ) );
  content.append( dsp->makeParameterForWifi( addr[kParamB0_4_HP], static_cast<float>(coeffs_hp[3*5+kB0]) ) );
  content.append( dsp->makeParameterForWifi( addr[kParamA2_4_HP], static_cast<float>(coeffs_hp[3*5+kA2]) ) );
  content.append( dsp->makeParameterForWifi( addr[kParamA1_4_HP], static_cast<float>(coeffs_hp[3*5+kA1]) ) );

  content.append( dsp->makeParameterForWifi( addr[kParamB2_1_LP], static_cast<float>(coeffs_lp[kB2]) ) );
  content.append( dsp->makeParameterForWifi( addr[kParamB1_1_LP], static_cast<float>(coeffs_lp[kB1]) ) );
  content.append( dsp->makeParameterForWifi( addr[kParamB0_1_LP], static_cast<float>(coeffs_lp[kB0]) ) );
  content.append( dsp->makeParameterForWifi( addr[kParamA2_1_LP], static_cast<float>(coeffs_lp[kA2]) ) );
  content.append( dsp->makeParameterForWifi( addr[kParamA1_1_LP], static_cast<float>(coeffs_lp[kA1]) ) );

  content.append( dsp->makeParameterForWifi( addr[kParamB2_2_LP], static_cast<float>(coeffs_lp[5+kB2]) ) );
  content.append( dsp->makeParameterForWifi( addr[kParamB1_2_LP], static_cast<float>(coeffs_lp[5+kB1]) ) );
  content.append( dsp->makeParameterForWifi( addr[kParamB0_2_LP], static_cast<float>(coeffs_lp[5+kB0]) ) );
  content.append( dsp->makeParameterForWifi( addr[kParamA2_2_LP], static_cast<float>(coeffs_lp[5+kA2]) ) );
  content.append( dsp->makeParameterForWifi( addr[kParamA1_2_LP], static_cast<float>(coeffs_lp[5+kA1]) ) );

  content.append( dsp->makeParameterForWifi( addr[kParamB2_3_LP], static_cast<float>(coeffs_lp[2*5+kB2]) ) );
  content.append( dsp->makeParameterForWifi( addr[kParamB1_3_LP], static_cast<float>(coeffs_lp[2*5+kB1]) ) );
  content.append( dsp->makeParameterForWifi( addr[kParamB0_3_LP], static_cast<float>(coeffs_lp[2*5+kB0]) ) );
  content.append( dsp->makeParameterForWifi( addr[kParamA2_3_LP], static_cast<float>(coeffs_lp[2*5+kA2]) ) );
  content.append( dsp->makeParameterForWifi( addr[kParamA1_3_LP], static_cast<float>(coeffs_lp[2*5+kA1]) ) );

  content.append( dsp->makeParameterForWifi( addr[kParamB2_4_LP], static_cast<float>(coeffs_lp[3*5+kB2]) ) );
  content.append( dsp->makeParameterForWifi( addr[kParamB1_4_LP], static_cast<float>(coeffs_lp[3*5+kB1]) ) );
  content.append( dsp->makeParameterForWifi( addr[kParamB0_4_LP], static_cast<float>(coeffs_lp[3*5+kB0]) ) );
  content.append( dsp->makeParameterForWifi( addr[kParamA2_4_LP], static_cast<float>(coeffs_lp[3*5+kA2]) ) );
  content.append( dsp->makeParameterForWifi( addr[kParamA1_4_LP], static_cast<float>(coeffs_lp[3*5+kA1]) ) );

  return content;
}
