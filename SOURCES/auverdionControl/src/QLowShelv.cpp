#include <QDebug>

#include "QLowShelv.hpp"
#include "ui_QLowShelv.h"

using namespace Vektorraum;

extern void enableGui( bool enable );

//==============================================================================
/*!
 *
 */
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

  type = LOWSHELV;
}

//==============================================================================
/*!
 *
 */
QLowShelv::~QLowShelv()
{
  delete ui;
}

//==============================================================================
/*!
 *
 */
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

  H = ( b0 + b1*z + b2*z2 ) / ( a0 - a1*z - a2*z2 );
}

//==============================================================================
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
    coeffs[ kA1 ] = (-1.0)*a1;
    coeffs[ kA2 ] = (-1.0)*a2;
  }
}

//==============================================================================
/*!
 *
 */
void QLowShelv::on_doubleSpinBoxGain_valueChanged( double  )
{
  updateCoeffs();
  //sendDspParameter();
  emit valueChanged();
  timerDspUpdate.stop();
  timerDspUpdate.start( DSPUPDATELATENCY );
}

//==============================================================================
/*!
 *
 */
void QLowShelv::on_doubleSpinBoxFc_valueChanged( double  )
{
  updateCoeffs();
  //sendDspParameter();
  emit valueChanged();
  timerDspUpdate.stop();
  timerDspUpdate.start( DSPUPDATELATENCY );
}

//==============================================================================
/*!
 *
 */
void QLowShelv::on_doubleSpinBoxS_valueChanged( double  )
{
  updateCoeffs();
  //sendDspParameter();
  emit valueChanged();
  timerDspUpdate.stop();
  timerDspUpdate.start( DSPUPDATELATENCY );
}

//==============================================================================
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

//==============================================================================
/*!
 *
 */
void QLowShelv::sendDspParameter( void )
{
  QByteArray content;

  enableGui( false );

  content.append( dsp->muteSequence() );

  content.append( dsp->makeParameterForWifi( addr[kParamB2], static_cast<float>(coeffs[kB2]) ) );
  content.append( dsp->makeParameterForWifi( addr[kParamB1], static_cast<float>(coeffs[kB1]) ) );
  content.append( dsp->makeParameterForWifi( addr[kParamB0], static_cast<float>(coeffs[kB0]) ) );
  content.append( dsp->makeParameterForWifi( addr[kParamA2], static_cast<float>(coeffs[kA2]) ) );
  content.append( dsp->makeParameterForWifi( addr[kParamA1], static_cast<float>(coeffs[kA1]) ) );
  
  content.append( dsp->unmuteSequence() );

  dsp->sendParameterWifi( content );

  enableGui( true );
}

//==============================================================================
/*!
 *
 */
uint32_t QLowShelv::getNumBytes( void )
{
  return 2*5 + 4*5;
}

//==============================================================================
/*!
 *
 */
/*
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

}*/

//==============================================================================
/*!
 */
QByteArray QLowShelv::getUserParams( void )
{
  QByteArray content;
  float V0t = static_cast<float>(ui->doubleSpinBoxGain->value());
  content.append( reinterpret_cast<const char*>(&V0t), sizeof(V0t) );
  float fct = static_cast<float>(ui->doubleSpinBoxFc->value());
  content.append( reinterpret_cast<const char*>(&fct), sizeof(fct) );
  float St = static_cast<float>(ui->doubleSpinBoxS->value());
  content.append( reinterpret_cast<const char*>(&St), sizeof(St) );
  content.append( reinterpret_cast<const char*>(&bypass), sizeof(bypass) );
  return content;
}

//==============================================================================
/*!
 */
void QLowShelv::setUserParams( QByteArray& userParams, int& idx )
{
  QByteArray param;

  if( userParams.size() >= idx + 12 )
  {
    param.clear();
    param.append( userParams.at(idx) );
    idx++;
    param.append( userParams.at(idx) );
    idx++;
    param.append( userParams.at(idx) );
    idx++;
    param.append( userParams.at(idx) );
    idx++;

    float V0t = *reinterpret_cast<const float*>(param.data());

    param.clear();
    param.append( userParams.at(idx) );
    idx++;
    param.append( userParams.at(idx) );
    idx++;
    param.append( userParams.at(idx) );
    idx++;
    param.append( userParams.at(idx) );
    idx++;

    float fct = *reinterpret_cast<const float*>(param.data());

    param.clear();
    param.append( userParams.at(idx) );
    idx++;
    param.append( userParams.at(idx) );
    idx++;
    param.append( userParams.at(idx) );
    idx++;
    param.append( userParams.at(idx) );
    idx++;

    float St = *reinterpret_cast<const float*>(param.data());

    bypass = static_cast<bool>(userParams.at(idx));
    idx++;

    ui->doubleSpinBoxGain->blockSignals( true );
    ui->doubleSpinBoxGain->setValue( V0t );
    ui->doubleSpinBoxGain->blockSignals( false );

    ui->doubleSpinBoxFc->blockSignals( true );
    ui->doubleSpinBoxFc->setValue( fct );
    ui->doubleSpinBoxFc->blockSignals( false );

    ui->doubleSpinBoxS->blockSignals( true );
    ui->doubleSpinBoxS->setValue( St );
    ui->doubleSpinBoxS->blockSignals( false );

    ui->pushButtonBypass->blockSignals( true );
    ui->pushButtonBypass->setChecked( bypass );
    ui->pushButtonBypass->blockSignals( false );
  }
  else
    qDebug()<<"QLowShelv::setUserParams: Not enough data";
}

//==============================================================================
/*! Get the parameters in DSP format. The parameters are returned with register 
 *  address followed by value dword ready to be sent via i2c to DSP.
 *
 * \return Byte array with parameters for DSP. 
 */
QByteArray QLowShelv::getDspParams( void )
{
  QByteArray content;

  content.append( dsp->makeParameterForWifi( addr[kParamB2], static_cast<float>(coeffs[kB2]) ) );
  content.append( dsp->makeParameterForWifi( addr[kParamB1], static_cast<float>(coeffs[kB1]) ) );
  content.append( dsp->makeParameterForWifi( addr[kParamB0], static_cast<float>(coeffs[kB0]) ) );
  content.append( dsp->makeParameterForWifi( addr[kParamA2], static_cast<float>(coeffs[kA2]) ) );
  content.append( dsp->makeParameterForWifi( addr[kParamA1], static_cast<float>(coeffs[kA1]) ) );

  return content;
}
