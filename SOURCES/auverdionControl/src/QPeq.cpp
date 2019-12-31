#include <QAction>

#include "QPeq.hpp"
#include "ui_QPeq.h"

using namespace Vektorraum;

extern void enableGui( bool enable );

//==============================================================================
/*!
 *
 */
QPeq::QPeq( double gain, double freq, double qfactor,
            uint16_t addrB2, uint16_t addrB1, uint16_t addrB0,
            uint16_t addrA2, uint16_t addrA1,
            tfloat samplerate,
            CFreeDspAurora* ptrdsp, 
            QChannel* ptrchn,
            QWidget *parent) :
  QDspBlock(parent), ui(new Ui::QPeq)
{
  addr[kParamB2] = addrB2;
  addr[kParamB1] = addrB1;
  addr[kParamB0] = addrB0;
  addr[kParamA2] = addrA2;
  addr[kParamA1] = addrA1;
  fs = samplerate;
  dsp = ptrdsp;
  channel = ptrchn;

  ui->setupUi(this);
  ui->doubleSpinBoxGain->blockSignals( true );
  ui->doubleSpinBoxGain->setAttribute( Qt::WA_MacShowFocusRect, 0 );
  ui->doubleSpinBoxGain->setValue( gain );
  ui->doubleSpinBoxGain->blockSignals( false );
  ui->doubleSpinBoxFc->blockSignals( true );
  ui->doubleSpinBoxFc->setAttribute( Qt::WA_MacShowFocusRect, 0 );
  ui->doubleSpinBoxFc->setValue( freq );
  ui->doubleSpinBoxFc->blockSignals( false );
  ui->doubleSpinBoxQ->blockSignals( true );
  ui->doubleSpinBoxQ->setAttribute( Qt::WA_MacShowFocusRect, 0 );
  ui->doubleSpinBoxQ->setValue( qfactor );
  ui->doubleSpinBoxQ->blockSignals( false );

  QAction* action = new QAction( "Import REW PEQs" );
  contextMenu.addAction( action );

  connect( this, SIGNAL(customContextMenuRequested(const QPoint &)),
           this, SLOT(on_showContextMenu(const QPoint &)));

  connect( action, &QAction::triggered, this, &QPeq::on_importRewPeqs );

  connect( ui->doubleSpinBoxGain, SIGNAL(wheelMoved()), this, SLOT(delayDspUpdate()) );
  connect( ui->doubleSpinBoxFc, SIGNAL(wheelMoved()), this, SLOT(delayDspUpdate()) );
  connect( ui->doubleSpinBoxQ, SIGNAL(wheelMoved()), this, SLOT(delayDspUpdate()) );

  type = PEQ;

}

//==============================================================================
/*!
 *
 */
QPeq::~QPeq()
{
  delete ui;
}

//==============================================================================
/*!
 *
 */
void QPeq::update( Vektorraum::tvector<Vektorraum::tfloat> f )
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
void QPeq::updateCoeffs( void )
{
  V0 = ui->doubleSpinBoxGain->value();
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
    tfloat A = std::pow( 10.0, V0 / 40.0 );
    tfloat w0 = 2.0 * pi * fc / fs;
    tfloat BW = asinh( (1.0 / Q) / 2.0 ) / ( log(2.0) / 2.0 );
    tfloat alpha = sin(w0) * sinh( std::log(2.0)/2.0 * BW * w0 / sin(w0) );
    tfloat b0 =  1.0 + alpha * A;
    tfloat b1 = -2.0 * cos(w0);
    tfloat b2 =  1.0 - alpha * A;
    tfloat a0 =  1.0 + alpha / A;
    tfloat a1 =  2.0 * cos(w0);
    tfloat a2 = -1.0 + alpha / A;

    coeffs[ kB0 ] = b0 / a0;
    coeffs[ kB1 ] = b1 / a0;
    coeffs[ kB2 ] = b2 / a0;
    coeffs[ kA1 ] = a1 / a0;
    coeffs[ kA2 ] = a2 / a0;
  }
}

//==============================================================================
/*!
 *
 */
void QPeq::on_doubleSpinBoxGain_valueChanged( double  )
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
void QPeq::on_doubleSpinBoxFc_valueChanged( double  )
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
void QPeq::on_doubleSpinBoxQ_valueChanged( double  )
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
void QPeq::on_pushButtonBypass_clicked()
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
void QPeq::sendDspParameter( void )
{
  QByteArray content;

  dsp->muteDAC();
  QThread::msleep( 200 );

  content.append( dsp->makeParameterForWifi( addr[kParamB2], static_cast<float>(coeffs[kB2]) ) );
  content.append( dsp->makeParameterForWifi( addr[kParamB1], static_cast<float>(coeffs[kB1]) ) );
  content.append( dsp->makeParameterForWifi( addr[kParamB0], static_cast<float>(coeffs[kB0]) ) );
  content.append( dsp->makeParameterForWifi( addr[kParamA2], static_cast<float>(coeffs[kA2]) ) );
  content.append( dsp->makeParameterForWifi( addr[kParamA1], static_cast<float>(coeffs[kA1]) ) );

  dsp->sendParameterWifi( content );

  dsp->unmuteDAC();
}

//==============================================================================
/*!
 *
 */
uint32_t QPeq::getNumBytes( void )
{
  return 2*5 + 4*5;
}

//==============================================================================
/*!
 *
 */
void QPeq::on_showContextMenu( const QPoint &pos )
{
  qDebug()<<"Context Menu";
  contextMenu.exec( mapToGlobal(pos) );
}

//==============================================================================
/*!
 *
 */
void QPeq::on_importRewPeqs( void )
{
  emit importRewPeqs( this );
}

//==============================================================================
/*!
 *
 */
void QPeq::setParameters( Vektorraum::tfloat newfc, Vektorraum::tfloat newV0, Vektorraum::tfloat newQ )
{
  fc = newfc;
  Q = newQ;
  V0 = newV0;

  ui->doubleSpinBoxGain->blockSignals( true );
  ui->doubleSpinBoxFc->blockSignals( true );
  ui->doubleSpinBoxQ->blockSignals( true );
  ui->doubleSpinBoxGain->setValue( V0 );
  ui->doubleSpinBoxFc->setValue( fc );
  ui->doubleSpinBoxQ->setValue( Q );
  ui->doubleSpinBoxGain->blockSignals( false );
  ui->doubleSpinBoxFc->blockSignals( false );
  ui->doubleSpinBoxQ->blockSignals( false );

  updateCoeffs();
  sendDspParameter();
  emit valueChanged();
}

//==============================================================================
/*!
 */
QByteArray QPeq::getUserParams( void )
{
  QByteArray content;
  float fct = static_cast<float>(ui->doubleSpinBoxFc->value());
  content.append( reinterpret_cast<const char*>(&fct), sizeof(fct) );
  float Qt = static_cast<float>(ui->doubleSpinBoxQ->value());
  content.append( reinterpret_cast<const char*>(&Qt), sizeof(Qt) );
  float V0t = static_cast<float>(ui->doubleSpinBoxGain->value());
  content.append( reinterpret_cast<const char*>(&V0t), sizeof(V0t) );
  content.append( reinterpret_cast<const char*>(&bypass), sizeof(bypass) );
  return content;
}

//==============================================================================
/*!
 */
void QPeq::setUserParams( QByteArray& userParams, int& idx )
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

    bypass = static_cast<bool>(userParams.at(idx));
    idx++;

    ui->doubleSpinBoxFc->blockSignals( true );
    ui->doubleSpinBoxFc->setValue( static_cast<double>(fct) );
    ui->doubleSpinBoxFc->blockSignals( false );

    ui->doubleSpinBoxQ->blockSignals( true );
    ui->doubleSpinBoxQ->setValue( static_cast<double>(Qt) );
    ui->doubleSpinBoxQ->blockSignals( false );

    ui->doubleSpinBoxGain->blockSignals( true );
    ui->doubleSpinBoxGain->setValue( static_cast<double>(V0t) );
    ui->doubleSpinBoxGain->blockSignals( false );

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
QByteArray QPeq::getDspParams( void )
{
  QByteArray content;
  content.append( dsp->makeParameterForWifi( addr[kParamB2], static_cast<float>(coeffs[kB2]) ) );
  content.append( dsp->makeParameterForWifi( addr[kParamB1], static_cast<float>(coeffs[kB1]) ) );
  content.append( dsp->makeParameterForWifi( addr[kParamB0], static_cast<float>(coeffs[kB0]) ) );
  content.append( dsp->makeParameterForWifi( addr[kParamA2], static_cast<float>(coeffs[kA2]) ) );
  content.append( dsp->makeParameterForWifi( addr[kParamA1], static_cast<float>(coeffs[kA1]) ) );
  return content;
}

