#include <QSlider>
#include <QDebug>

#include "QVolumeSlider.hpp"

#include "QGain.hpp"
#include "ui_QGain.h"

using namespace Vektorraum;

extern QVolumeSlider* sliderMainVolume;
extern void enableGui( bool enable );

//==============================================================================
/*!
 *
 */
QGain::QGain( tfloat V0, uint16_t gainaddr, CFreeDspAurora* ptrdsp, QWidget *parent ) :
  QDspBlock(parent), ui(new Ui::QGain)
{
  type = GAIN;
  
  addr[kTargetGain] = gainaddr;

  dsp = ptrdsp;

  ui->setupUi(this);
  ui->doubleSpinBoxGain->blockSignals( true );
  ui->doubleSpinBoxGain->setValue( V0 );
  ui->doubleSpinBoxGain->setAttribute( Qt::WA_MacShowFocusRect, 0 );
  ui->doubleSpinBoxGain->blockSignals( false );
}

//==============================================================================
/*!
 *
 */
QGain::~QGain()
{
  delete ui;
}

//==============================================================================
/*! \brief Updates the filter.
 *
 */
void QGain::update( tvector<tfloat> f )
{
  H = tvector<tcomplex>( length(f) );
  if( bypass )
  {
    for( tuint ii = 0; ii < length(f); ii++ )
      H[ii] = 1.0;
  }
  else
  {
    for( tuint ii = 0; ii < length(f); ii++ )
      H[ii] = pow( 10.0, ui->doubleSpinBoxGain->value()/20.0 );
  }
}

//==============================================================================
/*!
 *
 */
void QGain::on_doubleSpinBoxGain_valueChanged( double )
{
  //sendDspParameter();
  emit valueChanged();
  timerDspUpdate.stop();
  timerDspUpdate.start( DSPUPDATELATENCY );
}

//==============================================================================
/*!
 *
 */
void QGain::on_pushButtonBypass_clicked()
{
  bypass = ui->pushButtonBypass->isChecked();
  sendDspParameter();
  emit valueChanged();
}

//==============================================================================
/*!
 *
 */
void QGain::sendDspParameter( void )
{
  enableGui( false );

  double gain = 0.0; //static_cast<double>(sliderMainVolume->value());
  if( !bypass )
    gain += ui->doubleSpinBoxGain->value();
  //qDebug()<<sliderMainVolume->value()<<ui->doubleSpinBoxGain->value()<<gain;
  float val = static_cast<float>(pow( 10.0, gain/20.0 ));

  QByteArray content;
  content.append( dsp->makeParameterForWifi( addr[kTargetGain], val ) );
  dsp->sendParameterWifi( content );

  enableGui( true );
}

//==============================================================================
/*!
 *
 */
uint32_t QGain::getNumBytes( void )
{
  return 6;
}

//==============================================================================
/*!
 */
QByteArray QGain::getUserParams( void )
{
  QByteArray content;
  float gain = static_cast<float>(ui->doubleSpinBoxGain->value());
  content.append( reinterpret_cast<const char*>(&gain), sizeof(gain) );
  content.append( reinterpret_cast<const char*>(&bypass), sizeof(bypass) );
  return content;
}

//==============================================================================
/*!
 */
void QGain::setUserParams( QByteArray& userParams, int& idx )
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

    float gain = *reinterpret_cast<const float*>(param.data());

    bypass = static_cast<bool>(userParams.at(idx));
    idx++;

    ui->doubleSpinBoxGain->blockSignals( true );
    ui->doubleSpinBoxGain->setValue( static_cast<double>(gain) );
    ui->doubleSpinBoxGain->blockSignals( false );

    ui->pushButtonBypass->blockSignals( true );
    ui->pushButtonBypass->setChecked( bypass );
    ui->pushButtonBypass->blockSignals( false );
  }
  else
    qDebug()<<"QGain::setUserParams: Not enough data";

}

//==============================================================================
/*! Get the parameters in DSP format. The parameters are returned with register 
 *  address followed by value dword ready to be sent via i2c to DSP.
 *
 * \return Byte array with parameters for DSP. 
 */
QByteArray QGain::getDspParams( void )
{
  QByteArray ret;

  double gain = 0.0;
  if( !bypass )
    gain += ui->doubleSpinBoxGain->value();
  float val = static_cast<float>(pow( 10.0, gain/20.0 ));
  
  ret.append( dsp->makeParameterForWifi( addr[kTargetGain], val ) );
  
  return ret;
}
