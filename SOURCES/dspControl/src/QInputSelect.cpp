#include <QAbstractItemView>
#include <QDebug>
#include <QStandardItemModel>

#include "QInputSelect.hpp"
#include "ui_QInputSelect.h"

using namespace Vektorraum;

QInputSelect::QInputSelect( uint32_t selection, uint16_t inputaddr, CFreeDspAurora* ptrdsp, QWidget *parent) :
  QDspBlock(parent), ui(new Ui::QInputSelect)
{
  addr[kInput] = inputaddr;
  dsp = ptrdsp;

  ui->setupUi(this);

  //QListView * listView = new QListView(ui->comboBoxInput );

  //listView->setStyleSheet( "QWidget:item:selected { border: 0px solid #999900; background: transparent; } QWidget:item:checked { font-weight: bold;}" );
  //ui->comboBoxInput->setView(listView);

  ui->comboBoxInput->blockSignals( true );
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
  ui->comboBoxInput->blockSignals( false );
  //ui->comboBoxInput->setMaxVisibleItems( 16 );
}

QInputSelect::~QInputSelect()
{
  delete ui;
}

//------------------------------------------------------------------------------
/*! \brief Updates the filter.
 *
 */
void QInputSelect::update( tvector<tfloat> f )
{
  H = tvector<tcomplex>( length(f) );
  for( tuint ii = 0; ii < length(f); ii++ )
    H[ii] = 1.0;
}

//------------------------------------------------------------------------------
/*!
 *
 */
void QInputSelect::sendDspParameter( void )
{
  qDebug()<<"Selected index"<<ui->comboBoxInput->currentIndex();
  uint32_t val = static_cast<uint32_t>(ui->comboBoxInput->currentIndex());
  dsp->sendParameter( addr[kInput], val );
}

//------------------------------------------------------------------------------
/*!
 *
 */
uint32_t QInputSelect::getNumBytes( void )
{
  return 6;
}

//------------------------------------------------------------------------------
/*!
 *
 */
void QInputSelect::writeDspParameter( void )
{
  uint32_t val = static_cast<uint32_t>(ui->comboBoxInput->currentIndex());
  dsp->storeRegAddr( addr[kInput] );
  dsp->storeValue( val );
}

//------------------------------------------------------------------------------
/*!
 *
 */
void QInputSelect::on_comboBoxInput_currentIndexChanged( int  )
{
  sendDspParameter();
  emit valueChanged();
}
