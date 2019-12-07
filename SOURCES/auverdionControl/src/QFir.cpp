#include <QAbstractItemView>
#include <QDebug>
#include <QStandardItemModel>
#include <QFileDialog>
#include <QStandardPaths>
#include <QMessageBox>

#include "QFir.hpp"
#include "ui_QFir.h"

#include "LogFile.h"

extern CLogFile myLog;

using namespace Vektorraum;

//==============================================================================
/*! Constructor
 *
 */
QFir::QFir( uint16_t firaddr, tuint filterlength, tfloat samplerate, CFreeDspAurora* ptrdsp, QWidget *parent) :
  QDspBlock(parent), ui(new Ui::QFir)
{
  type = FIR;
  
  addr[kImpulseResponse] = firaddr;
  dsp = ptrdsp;

  ui->setupUi(this);

  ui->lineEditResponseFile->installEventFilter( this );

  nfft = filterlength;
  taps = 0;
  fs = samplerate;

  ir = tvector<tfloat>(nfft);
  for( tuint k = 0; k < length(ir); k++ )
    ir[k] = 0.0;
  ir[0] = 1.0;

  freq = tvector<tfloat>(nfft/2 + 1);
  for( uint n = 0; n < length(freq); n++ )
    freq[n] = static_cast<tfloat>(n) / static_cast<tfloat>(nfft) * fs;

  updateCoeffs();
}

QFir::~QFir()
{
  delete ui;
}

//==============================================================================
/*! \brief Updates the filter.
 *
 */
void QFir::update( tvector<tfloat> f )
{
  tvector<tcomplex> X = fft( ir, nfft );
  tvector<tfloat> magt = abs( X( 0, nfft/2 ) );
  tvector<tfloat> phit = angle( X( 0, nfft/2 ) );

  if( length(f) >= length(freq) )
  {
    tvector<tfloat> mag = interp1( freq, magt, f, "spline" );
    tvector<tfloat> phi = interp1( freq, phit, f, "spline" );
    H = mag * exp( j*phi );
  }
  else
  {
    tvector<tcomplex> FR_dec = tvector<tcomplex>(length(f));
    tvector<tfloat> freq_dec = tvector<tfloat>(length(f));
    tfloat q = static_cast<tfloat>(length(freq)) / static_cast<tfloat>(length(f));
    tuint idx = 0;
    for( tfloat ii = 0; ii < static_cast<tfloat>(length(X)); ii = ii + q )
    {
      if( idx < length(f) )
      {
        FR_dec[idx] = X[static_cast<tuint>(ii)];
        freq_dec[idx] = freq[static_cast<tuint>(ii)];
      }
      idx++;
    }
    if( idx < length(f) )
    {
      FR_dec[length(f)-1] = X[length(freq)-1];
      freq_dec[length(f)-1] = freq[length(freq)-1];
    }
    
    tvector<tfloat> mag = interp1( freq_dec, abs( FR_dec ), f, "spline" );
    tvector<tfloat> phi = interp1( freq_dec, angle( FR_dec ), f, "spline" );
    H = mag * exp( j*phi );
  }
}

//==============================================================================
/*!
 */
void QFir::updateCoeffs( void )
{
  tvector<tcomplex> X = fft( ir, nfft );
  //H = X( 0, nfft/2 );
}

//==============================================================================
/*!
 *
 */
void QFir::sendDspParameter( void )
{
  qDebug()<<"QFir::sendDspParameter not implemented";
  //uint32_t val = static_cast<uint32_t>(ui->comboBoxInput->currentIndex());
  //dsp->sendParameter( addr[kInput], val );
}

//==============================================================================
/*!
 *
 */
uint32_t QFir::getNumBytes( void )
{
  return 0;
}

//==============================================================================
/*!
 *
 */
bool QFir::eventFilter( QObject* object, QEvent* event )
{
  if( object == ui->lineEditResponseFile && event->type() == QEvent::MouseButtonDblClick )
  {
    QString fileName = QFileDialog::getOpenFileName( this, tr("Open Impulse Response"), 
                                                     QStandardPaths::locate(QStandardPaths::DocumentsLocation, QString(), QStandardPaths::LocateDirectory) + QString("/auverdionControl"),
                                                     tr("IR Files (*.txt)") );
    
    QFile irFile( fileName );
    if( irFile.open(QIODevice::ReadOnly) )
    {
      QTextStream in( &irFile );
      //ir = tvector<tfloat>(nfft);
      for( tuint k = 0; k < length(ir); k++ )
        ir[k] = 0.0;
      tuint k = 0;
      while (!in.atEnd())
      {
        QString line = in.readLine();
        if( k < nfft )
          ir[k] = line.toDouble();
        k++;
      }
      taps = k;
      irFile.close();

      updateCoeffs();
      sendDspParameter();

      QMessageBox::information( this,
                                tr( "auverdionControl" ),
                                tr( "Loaded " ) + QString::number(k) + tr( " taps" ) );
      
      ui->lineEditResponseFile->blockSignals( true );
      QFileInfo fileInfo( irFile.fileName() );
      ui->lineEditResponseFile->setText( fileInfo.fileName() );
      ui->lineEditResponseFile->blockSignals( false );
      emit valueChanged();
    }

    return true;
  }
  return false;
}

//==============================================================================
/*!
 */
QByteArray QFir::getUserParams( void )
{
  QByteArray content;

  qDebug()<<"QFir::getUserParams";

  for( uint32_t kk = 0; kk < nfft; kk++ )
  {
    float tap = static_cast<float>(ir[kk]);
    content.append( reinterpret_cast<const char*>(&tap), sizeof(float) );
  }

  return content;
}

//==============================================================================
/*!
 */
void QFir::setUserParams( QByteArray& userParams, int& idx )
{
  //#if !defined( __WIN__ )
  //#warning QFir::setUserParams not implemented
  //#endif
  qDebug()<<"QFir::setUserParams";

  if( userParams.size() >= idx + 4096 * sizeof(float) )
  {
    for( uint32_t kk = 0; kk < nfft; kk++ )
    {
      QByteArray param;
      param.append( userParams.at(idx) );
      idx++;
      param.append( userParams.at(idx) );
      idx++;
      param.append( userParams.at(idx) );
      idx++;
      param.append( userParams.at(idx) );
      idx++;
      ir[kk] = static_cast<Vektorraum::tfloat>(*reinterpret_cast<const float*>(param.data()));
    }
  }
    
}

//==============================================================================
/*! Get the parameters in DSP format. The parameters are returned with register 
 *  address followed by value dword ready to be sent via i2c to DSP.
 *
 * \return Byte array with parameters for DSP. 
 */
QByteArray QFir::getDspParams( void )
{
  QByteArray ret;

  #if !defined( __WIN__ )
  #warning QFir::getDspParam not implemented
  #endif
  qDebug()<<"QFir::getDspParam not implemented";

  return ret;
}
