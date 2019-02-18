#include "QLowShelv.hpp"
#include "ui_QLowShelv.h"

using namespace Vektorraum;

QLowShelv::QLowShelv( double gain, double freq, double slope,
                      uint16_t addrB2, uint16_t addrB1, uint16_t addrB0,
                      uint16_t addrA2, uint16_t addrA1,
                      tfloat samplerate,
                      CFreeDspAurora* ptrdsp, QWidget *parent ) :
  QDspBlock(parent),
  ui(new Ui::QLowShelv)
{
  addr[kParamB2] = addrB2;
  addr[kParamB1] = addrB1;
  addr[kParamB0] = addrB0;
  addr[kParamA2] = addrA2;
  addr[kParamA1] = addrA1;
  fs = samplerate;
  dsp = ptrdsp;

  ui->setupUi(this);
  ui->doubleSpinBoxGain->blockSignals( true );
  ui->doubleSpinBoxGain->setAttribute( Qt::WA_MacShowFocusRect, 0 );
  ui->doubleSpinBoxGain->setValue( gain );
  ui->doubleSpinBoxGain->blockSignals( false );
  ui->doubleSpinBoxFc->blockSignals( true );
  ui->doubleSpinBoxFc->setAttribute( Qt::WA_MacShowFocusRect, 0 );
  ui->doubleSpinBoxFc->setValue( freq );
  ui->doubleSpinBoxFc->blockSignals( false );
  ui->doubleSpinBoxS->blockSignals( true );
  ui->doubleSpinBoxS->setAttribute( Qt::WA_MacShowFocusRect, 0 );
  ui->doubleSpinBoxS->setValue( slope );
  ui->doubleSpinBoxS->blockSignals( false );
}

QLowShelv::~QLowShelv()
{
  delete ui;
}

void QLowShelv::update( Vektorraum::tvector<Vektorraum::tfloat> f )
{
  updateCoeffs();
  tvector<tcomplex> z = exp( j * ( -2.0 * pi * f / fs ) );
  tvector<tcomplex> z2 = z*z;
  tfloat b0 = coeffs[kB0];
  tfloat b1 = coeffs[kB1];
  tfloat b2 = coeffs[kB2];
  tfloat a1 = coeffs[kA1];
  tfloat a2 = coeffs[kA2];
  tfloat a0 = 1.0;

  H = ( b0 + b1*z + b2*z2 ) / ( a0 + a1*z + a2*z2 );
}

//------------------------------------------------------------------------------
/*!
 *
 */
void QLowShelv::updateCoeffs( void )
{
  V0 = ui->doubleSpinBoxGain->value();
  fc = ui->doubleSpinBoxFc->value();
  S = ui->doubleSpinBoxS->value();

  if( bypass )
  {
    tfloat b0 = 1.0;
    tfloat b1 = 0.0;
    tfloat b2 = 0.0;
    tfloat a1 = 0.0;
    tfloat a2 = 0.0;
    coeffs[kB0] = b0;
    coeffs[kB1] = b1;
    coeffs[kB2] = b2;
    coeffs[kA1] = a1;
    coeffs[kA2] = a2;
  }
  else
  {
    tfloat A = std::pow( 10.0, V0/40.0 );
    tfloat w0 = 2*pi*fc/fs;
    tfloat alpha = sin(w0)/2.0 * sqrt( (A + 1.0/A) * (1.0/S - 1.0) + 2.0);

    tfloat a0 = (A + 1.0) + (A - 1.0) * cos(w0) + 2.0 * sqrt(A) * alpha;
    tfloat a1 = ( -2.0 * ( (A - 1.0) + (A + 1.0) * cos(w0) ) ) / a0;
    tfloat a2 = ( (A + 1.0) + (A - 1.0) * cos(w0) - 2.0 * sqrt(A) * alpha ) / a0;
    tfloat b0 = ( A * ( (A + 1.0) - (A - 1.0) * cos(w0) + 2.0 * sqrt(A) * alpha ) ) / a0;
    tfloat b1 = ( 2.0 * A * ( (A - 1.0) - (A + 1.0) * cos(w0) ) ) / a0;
    tfloat b2 = ( A * ( (A + 1.0) - (A - 1.0) * cos(w0) - 2.0 * sqrt(A) * alpha ) ) / a0;
    a0 = 1.0;
    coeffs[ kB0 ] = b0;
    coeffs[ kB1 ] = b1;
    coeffs[ kB2 ] = b2;
    coeffs[ kA1 ] = a1;
    coeffs[ kA2 ] = a2;
  }
}

//------------------------------------------------------------------------------
/*!
 *
 */
void QLowShelv::on_doubleSpinBoxGain_valueChanged( double  )
{
  updateCoeffs();
  sendDspParameter();
  emit valueChanged();
}

//------------------------------------------------------------------------------
/*!
 *
 */
void QLowShelv::on_doubleSpinBoxFc_valueChanged( double  )
{
  updateCoeffs();
  sendDspParameter();
  emit valueChanged();
}

//------------------------------------------------------------------------------
/*!
 *
 */
void QLowShelv::on_doubleSpinBoxS_valueChanged( double  )
{
  updateCoeffs();
  sendDspParameter();
  emit valueChanged();
}

//------------------------------------------------------------------------------
/*!
 *
 */
void QLowShelv::on_pushButtonBypass_clicked()
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
void QLowShelv::sendDspParameter( void )
{
  dsp->sendParameter( addr[kParamB2], static_cast<float>(coeffs[kB2]) );
  dsp->sendParameter( addr[kParamB1], static_cast<float>(coeffs[kB1]) );
  dsp->sendParameter( addr[kParamB0], static_cast<float>(coeffs[kB0]) );
  dsp->sendParameter( addr[kParamA2], static_cast<float>(coeffs[kA2]) );
  dsp->sendParameter( addr[kParamA1], static_cast<float>(coeffs[kA1]) );
}

//------------------------------------------------------------------------------
/*!
 *
 */
uint32_t QLowShelv::getNumBytes( void )
{
  return 2*5 + 4*5;
}

//------------------------------------------------------------------------------
/*!
 *
 */
void QLowShelv::writeDspParameter( void )
{
  dsp->storeRegAddr( addr[kParamB2] );
  dsp->storeValue( static_cast<float>(coeffs[kB2]) );
  dsp->storeRegAddr( addr[kParamB1] );
  dsp->storeValue( static_cast<float>(coeffs[kB1]) );
  dsp->storeRegAddr( addr[kParamB0] );
  dsp->storeValue( static_cast<float>(coeffs[kB0]) );
  dsp->storeRegAddr( addr[kParamA2] );
  dsp->storeValue( static_cast<float>(coeffs[kA2]) );
  dsp->storeRegAddr( addr[kParamA1] );
  dsp->storeValue( static_cast<float>(coeffs[kA1]) );

}
