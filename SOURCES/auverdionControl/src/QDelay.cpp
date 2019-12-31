#include <QDebug>
#include <cstdint>
#include <QThread>

#include "QDelay.hpp"
#include "ui_QDelay.h"

using namespace Vektorraum;

extern void enableGui( bool enable );

//==============================================================================
/*!
 *
 */
QDelay::QDelay( tfloat dly, tfloat samplerate, uint16_t delayaddr, CFreeDspAurora* ptrdsp, QWidget *parent ) :
  QDspBlock(parent), ui(new Ui::QDelay)
{
  type = DELAY;
  
  ui->setupUi(this);
  delay = static_cast<tuint>( dly/1000.0 * fs );
  fs = samplerate;
  addr[kDelay] = delayaddr;
  dsp = ptrdsp;

  ui->doubleSpinBoxDelay->blockSignals( true );
  ui->doubleSpinBoxDelay->setValue( delay );
  ui->doubleSpinBoxDelay->setAttribute( Qt::WA_MacShowFocusRect, 0 );
  ui->doubleSpinBoxDelay->setSingleStep( 1.0/fs * 1000.0 );
  ui->doubleSpinBoxDelay->blockSignals( false );

  connect( ui->doubleSpinBoxDelay, SIGNAL(wheelMoved()), this, SLOT(delayDspUpdate()) );

}

//==============================================================================
/*!
 *
 */
QDelay::~QDelay()
{
  delete ui;
}

//==============================================================================
/*!
 *
 */
void QDelay::update( tvector<tfloat> f )
{
  H = tvector<tcomplex>( length(f) );
  delay = static_cast<tuint>( ui->doubleSpinBoxDelay->value()/1000.0 * fs );

  if( bypass )
  {
    for( tuint ii = 0; ii < length(f); ii++ )
      H[ii] = 1.0;
  }
  else
  {
    tfloat n = ui->doubleSpinBoxDelay->value()/1000.0 * fs;
    H = exp( j * ( 2.0 * pi * f / fs ) * n );
  }
}

//==============================================================================
/*!
 *
 */
void QDelay::on_doubleSpinBoxDelay_valueChanged( double  )
{
  emit valueChanged();
  //sendDspParameter();
  timerDspUpdate.stop();
  timerDspUpdate.start( DSPUPDATELATENCY );
}

//==============================================================================
/*!
 *
 */
void QDelay::on_pushButtonBypass_clicked()
{
  bypass = ui->pushButtonBypass->isChecked();
  sendDspParameter();
  emit valueChanged();
}

//==============================================================================
/*!
 *
 */
void QDelay::sendDspParameter( void )
{
  int32_t val = static_cast<int32_t>(ui->doubleSpinBoxDelay->value()/1000.0 * fs + 0.5);
  if( bypass )
    val = 0;

  QByteArray content;

  dsp->muteDAC();
  QThread::msleep( 200 );

  content.append( dsp->makeParameterForWifi( addr[kDelay], val ) );

  dsp->sendParameterWifi( content );

  dsp->unmuteDAC();
}

//==============================================================================
/*!
 *
 */
uint32_t QDelay::getNumBytes( void )
{
  return 6;
}

//==============================================================================
/*!
 */
QByteArray QDelay::getUserParams( void )
{
  QByteArray content;
  float dly = static_cast<float>(ui->doubleSpinBoxDelay->value());
  content.append( reinterpret_cast<const char*>(&dly), sizeof(dly) );
  content.append( reinterpret_cast<const char*>(&bypass), sizeof(bypass) );
  return content;
}

//==============================================================================
/*!
 */
void QDelay::setUserParams( QByteArray& userParams, int& idx )
{
  QByteArray param;

  if( userParams.size() >= idx + 4 )
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

    float dly = *reinterpret_cast<const float*>(param.data());

    bypass = static_cast<bool>(userParams.at(idx));
    idx++;

    ui->doubleSpinBoxDelay->blockSignals( true );
    ui->doubleSpinBoxDelay->setValue( static_cast<double>(dly) );
    ui->doubleSpinBoxDelay->blockSignals( false );

    ui->pushButtonBypass->blockSignals( true );
    ui->pushButtonBypass->setChecked( bypass );
    ui->pushButtonBypass->blockSignals( false );
  }
  else
    qDebug()<<"QDelay::setUserParams: Not enough data";

}

//==============================================================================
/*! Get the parameters in DSP format. The parameters are returned with register 
 *  address followed by value dword ready to be sent via i2c to DSP.
 *
 * \return Byte array with parameters for DSP. 
 */
QByteArray QDelay::getDspParams( void )
{
  QByteArray content;

  int32_t val = static_cast<int32_t>(ui->doubleSpinBoxDelay->value()/1000.0 * fs + 0.5);
  if( bypass )
    val = 0;

  content.append( dsp->makeParameterForWifi( addr[kDelay], val ) );

  return content;
}
