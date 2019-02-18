#include <cstdint>

#include "QDelay.hpp"
#include "ui_QDelay.h"

using namespace Vektorraum;

QDelay::QDelay( tfloat dly, tfloat samplerate, uint16_t delayaddr, CFreeDspAurora* ptrdsp, QWidget *parent ) :
  QDspBlock(parent), ui(new Ui::QDelay)
{
  ui->setupUi(this);
  delay = static_cast<tuint>( dly/1000.0 * fs );
  fs = samplerate;
  addr[kDelay] = delayaddr;
  dsp = ptrdsp;

  ui->doubleSpinBoxDelay->blockSignals( true );
  ui->doubleSpinBoxDelay->setValue( delay );
  ui->doubleSpinBoxDelay->setAttribute( Qt::WA_MacShowFocusRect, 0 );
  ui->doubleSpinBoxDelay->blockSignals( false );

}

QDelay::~QDelay()
{
  delete ui;
}

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

//------------------------------------------------------------------------------
/*!
 *
 */
void QDelay::on_doubleSpinBoxDelay_valueChanged( double  )
{
  emit valueChanged();
  sendDspParameter();
}

//------------------------------------------------------------------------------
/*!
 *
 */
void QDelay::on_pushButtonBypass_clicked()
{
  bypass = ui->pushButtonBypass->isChecked();
  sendDspParameter();
  emit valueChanged();
}

//------------------------------------------------------------------------------
/*!
 *
 */
void QDelay::sendDspParameter( void )
{
  uint32_t val = static_cast<uint32_t>(ui->doubleSpinBoxDelay->value()/1000.0 * fs + 0.5);
  if( bypass )
    val = 0;
  dsp->sendParameter( addr[kDelay], val );
}

//------------------------------------------------------------------------------
/*!
 *
 */
uint32_t QDelay::getNumBytes( void )
{
  return 6;
}

//------------------------------------------------------------------------------
/*!
 *
 */
void QDelay::writeDspParameter( void )
{
  uint32_t val = static_cast<uint32_t>(ui->doubleSpinBoxDelay->value()/1000.0 * fs + 0.5);
  if( bypass )
    val = 0;
  dsp->storeRegAddr( addr[kDelay] );
  dsp->storeValue( val );
}
