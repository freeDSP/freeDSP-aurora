#include <QAbstractItemView>
#include <QDebug>
#include <QStandardItemModel>
#include <QFileDialog>
#include <QStandardPaths>
#include <QMessageBox>

#include "QFir.hpp"
#include "ui_QFir.h"

using namespace Vektorraum;

//==============================================================================
/*! Constructor
 *
 */
QFir::QFir( uint16_t firaddr, tuint filterlength, CFreeDspAurora* ptrdsp, QWidget *parent) :
  QDspBlock(parent), ui(new Ui::QFir)
{
  addr[kImpulseResponse] = firaddr;
  dsp = ptrdsp;

  ui->setupUi(this);

  ui->lineEditResponseFile->installEventFilter( this );

  nfft = filterlength;
  taps = 0;

  ir = tvector<tfloat>(nfft);
  for( tuint k = 0; k < length(ir); k++ )
    ir[k] = 0.0;
  ir[0] = 1.0;

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

}

//==============================================================================
/*!
 */
void QFir::updateCoeffs( void )
{
  tvector<tcomplex> X = fft( ir, nfft );
  H = X( 0, nfft/2 );
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
void QFir::writeDspParameter( void )
{
  qDebug()<<"QFir::writeDspParameter not implemented";
  //uint32_t val = static_cast<uint32_t>(ui->comboBoxInput->currentIndex());
  //dsp->storeRegAddr( addr[kOutput] );
  //dsp->storeValue( val );
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
                                                     QStandardPaths::locate(QStandardPaths::DocumentsLocation, QString(), QStandardPaths::LocateDirectory) + QString("/dspControl"),
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
                                tr( "dspControl" ),
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
void QFir::getUserParams( QByteArray* userParams )
{
  #warning QFir::getUserParams not implemented
  qDebug()<<"QFir::getUserParams not implemented";
}

//==============================================================================
/*!
 */
void QFir::setUserParams( QByteArray& userParams, int& idx )
{
  #warning QFir::setUserParams not implemented
  qDebug()<<"QFir::setUserParams not implemented";
}
