#include <QDebug>

#include "QPhase.hpp"
#include "ui_QPhase.h"

using namespace Vektorraum;

extern void enableGui( bool enable );

//==============================================================================
/*!
 *
 */
QPhase::QPhase( tfloat freq, tfloat qfactor,
                uint16_t addrB2, uint16_t addrB1, uint16_t addrB0,
                uint16_t addrA2, uint16_t addrA1,
                tfloat samplerate,
                CFreeDspAurora* ptrdsp, QWidget *parent ) : QDspBlock(parent), ui(new Ui::QPhase)
{
  type = PHASE;

  fc = freq;
  Q = qfactor;

  addr[kParamB2] = addrB2;
  addr[kParamB1] = addrB1;
  addr[kParamB0] = addrB0;
  addr[kParamA2] = addrA2;
  addr[kParamA1] = addrA1;
  fs = samplerate;
  dsp = ptrdsp;

  ui->setupUi(this);

  ui->doubleSpinBoxFc->blockSignals( true );
  ui->doubleSpinBoxFc->setAttribute( Qt::WA_MacShowFocusRect, 0 );
  ui->doubleSpinBoxFc->setValue( freq );
  ui->doubleSpinBoxFc->blockSignals( false );

  ui->doubleSpinBoxQ->blockSignals( true );
  ui->doubleSpinBoxQ->setAttribute( Qt::WA_MacShowFocusRect, 0 );
  ui->doubleSpinBoxQ->setValue( qfactor );
  ui->doubleSpinBoxQ->blockSignals( false );

}

//==============================================================================
/*!
 *
 */
QPhase::~QPhase()
{
  delete ui;
}

//==============================================================================
/*! \brief Updates the filter.
 *
 */
void QPhase::update( tvector<tfloat> f )
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
void QPhase::updateCoeffs( void )
{
  fc = ui->doubleSpinBoxFc->value();
  Q = ui->doubleSpinBoxQ->value();

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
    tfloat w0 = 2.0 * pi * fc / fs;
    tfloat alpha = sin(w0) / (2.0 * Q);

    tfloat a0 = 1.0 + alpha;
    tfloat b0 = (1.0 - alpha) / a0;
    tfloat b1 = -2.0 * cos(w0) / a0;
    tfloat b2 = ( 1.0 + alpha ) / a0;
    tfloat a1 = ( -2.0 * cos(w0) ) / a0;
    tfloat a2 = ( 1.0 - alpha ) / a0;
    a0 = 1.0;
    coeffs[kB0] = b0;
    coeffs[kB1] = b1;
    coeffs[kB2] = b2;
    coeffs[kA1] = (-1.0)*a1;
    coeffs[kA2] = (-1.0)*a2;
  }

  if( ui->checkBoxInvert->isChecked() )
  {
    coeffs[kB0] *= -1.0;
    coeffs[kB1] *= -1.0;
    coeffs[kB2] *= -1.0;
  }
}

//==============================================================================
/*!
 *
 */
void QPhase::on_checkBoxInvert_stateChanged( int )
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
void QPhase::on_doubleSpinBoxFc_valueChanged( double  )
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
void QPhase::on_doubleSpinBoxQ_valueChanged( double  )
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
void QPhase::on_pushButtonBypass_clicked()
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
void QPhase::sendDspParameter( void )
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
uint32_t QPhase::getNumBytes( void )
{
  return 2*5 + 4*5;
}

//==============================================================================
/*!
 */
QByteArray QPhase::getUserParams( void )
{
  QByteArray content;
  float fct = static_cast<float>(ui->doubleSpinBoxFc->value());
  content.append( reinterpret_cast<const char*>(&fct), sizeof(fct) );
  float Qt = static_cast<float>(ui->doubleSpinBoxQ->value());
  content.append( reinterpret_cast<const char*>(&Qt), sizeof(Qt) );
  uint8_t invert = 0;
  if( ui->checkBoxInvert->isChecked() )
    invert = 1;
  content.append( reinterpret_cast<const char*>(&invert), sizeof(invert) );
  content.append( reinterpret_cast<const char*>(&bypass), sizeof(bypass) );
  return content;
}

//==============================================================================
/*!
 */
void QPhase::setUserParams( QByteArray& userParams, int& idx )
{
  QByteArray param;

  if( userParams.size() >= idx + 8 )
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

    float Qt = *reinterpret_cast<const float*>(param.data());

    uint8_t invert = static_cast<uint8_t>(userParams.at(idx));
    idx++;

    bypass = static_cast<bool>(userParams.at(idx));
    idx++;

    ui->doubleSpinBoxFc->blockSignals( true );
    ui->doubleSpinBoxFc->setValue( static_cast<double>(fct) );
    ui->doubleSpinBoxFc->blockSignals( false );

    ui->doubleSpinBoxQ->blockSignals( true );
    ui->doubleSpinBoxQ->setValue( static_cast<double>(Qt) );
    ui->doubleSpinBoxQ->blockSignals( false );

    ui->checkBoxInvert->blockSignals( true );
    if( invert )
      ui->checkBoxInvert->setChecked( true );
    else
      ui->checkBoxInvert->setChecked( false );
    ui->checkBoxInvert->blockSignals( false );

    ui->pushButtonBypass->blockSignals( true );
    ui->pushButtonBypass->setChecked( bypass );
    ui->pushButtonBypass->blockSignals( false );
  }
  else
    qDebug()<<"QPhase::setUserParams: Not enough data";
}

//==============================================================================
/*! Get the parameters in DSP format. The parameters are returned with register 
 *  address followed by value dword ready to be sent via i2c to DSP.
 *
 * \return Byte array with parameters for DSP. 
 */
QByteArray QPhase::getDspParams( void )
{
  QByteArray content;
  content.append( dsp->makeParameterForWifi( addr[kParamB2], static_cast<float>(coeffs[kB2]) ) );
  content.append( dsp->makeParameterForWifi( addr[kParamB1], static_cast<float>(coeffs[kB1]) ) );
  content.append( dsp->makeParameterForWifi( addr[kParamB0], static_cast<float>(coeffs[kB0]) ) );
  content.append( dsp->makeParameterForWifi( addr[kParamA2], static_cast<float>(coeffs[kA2]) ) );
  content.append( dsp->makeParameterForWifi( addr[kParamA1], static_cast<float>(coeffs[kA1]) ) );
  return content;
}
