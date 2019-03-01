#include <QAbstractItemView>
#include <QDebug>
#include <QStandardItemModel>
#include <QFileDialog>
#include <QStandardPaths>

#include "QOutputSelect.hpp"
#include "ui_QOutputSelect.h"

using namespace Vektorraum;

QOutputSelect::QOutputSelect( uint32_t selection, uint16_t outputaddr, CFreeDspAurora* ptrdsp, QWidget *parent) :
  QDspBlock(parent), ui(new Ui::QOutputSelect)
{
  addr[kOutput] = outputaddr;
  dsp = ptrdsp;

  ui->setupUi(this);

  ui->lineEditResponseFile->installEventFilter( this );

  //QListView * listView = new QListView(ui->comboBoxInput );

  //listView->setStyleSheet( "QWidget:item:selected { border: 0px solid #999900; background: transparent; } QWidget:item:checked { font-weight: bold;}" );
  //ui->comboBoxInput->setView(listView);

  /*ui->comboBoxInput->blockSignals( true );
  ui->comboBoxInput->addItem( "Analog 1", 0 );
  ui->comboBoxInput->addItem( "Analog 2", 1 );
  ui->comboBoxInput->addItem( "Analog 3", 2 );
  ui->comboBoxInput->addItem( "Analog 4", 3 );
  ui->comboBoxInput->addItem( "Analog 5", 4 );
  ui->comboBoxInput->addItem( "Analog 6", 5 );
  ui->comboBoxInput->addItem( "Analog 7", 6 );
  ui->comboBoxInput->addItem( "Analog 8", 7 );
  ui->comboBoxInput->addItem( "USB 1", 8 );
  ui->comboBoxInput->addItem( "USB 2", 9 );
  ui->comboBoxInput->addItem( "USB 3", 10 );
  ui->comboBoxInput->addItem( "USB 4", 11 );
  ui->comboBoxInput->addItem( "USB 5", 12 );
  ui->comboBoxInput->addItem( "USB 6", 13 );
  ui->comboBoxInput->addItem( "USB 7", 14 );
  ui->comboBoxInput->addItem( "USB 8", 15 );
  ui->comboBoxInput->setCurrentIndex( selection );
  ui->comboBoxInput->blockSignals( false );*/
  //ui->comboBoxInput->setMaxVisibleItems( 16 );
}

QOutputSelect::~QOutputSelect()
{
  delete ui;
}

//------------------------------------------------------------------------------
/*! \brief Updates the filter.
 *
 */
void QOutputSelect::update( tvector<tfloat> f )
{
  H = tvector<tcomplex>( length(f) );
  for( tuint ii = 0; ii < length(f); ii++ )
    H[ii] = 1.0;
}

//------------------------------------------------------------------------------
/*!
 *
 */
void QOutputSelect::sendDspParameter( void )
{
  //uint32_t val = static_cast<uint32_t>(ui->comboBoxInput->currentIndex());
  //dsp->sendParameter( addr[kInput], val );
}

//------------------------------------------------------------------------------
/*!
 *
 */
uint32_t QOutputSelect::getNumBytes( void )
{
  return 0;
}

//------------------------------------------------------------------------------
/*!
 *
 */
void QOutputSelect::writeDspParameter( void )
{
  //uint32_t val = static_cast<uint32_t>(ui->comboBoxInput->currentIndex());
  //dsp->storeRegAddr( addr[kOutput] );
  //dsp->storeValue( val );
}

//------------------------------------------------------------------------------
/*!
 *
 */
/*void QOutputSelect::on_comboBoxInput_currentIndexChanged( int  )
{
  sendDspParameter();
  emit valueChanged();
}*/

//------------------------------------------------------------------------------
/*!
 *
 */
bool QOutputSelect::eventFilter( QObject* object, QEvent* event )
{
  if( object == ui->lineEditResponseFile && event->type() == QEvent::MouseButtonDblClick )
  {
    QString fileName = QFileDialog::getOpenFileName( this, tr("Open Frequency Response"), 
                                                     QStandardPaths::locate(QStandardPaths::DocumentsLocation, QString(), QStandardPaths::LocateDirectory),
                                                     tr("FRD Files (*.frd)") );
    return true;
  }
  return false;
}
