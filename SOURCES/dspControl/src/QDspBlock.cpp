#include <QStyleOption>
#include <QPainter>
#include <QDebug>

#include "QDspBlock.hpp"
#include "ui_QDspBlock.h"

QDspBlock::QDspBlock(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::QDspBlock)
{
  ui->setupUi(this);
  //setFixedWidth( 100 );
  #if defined( __MACOSX__ )
  setFixedSize( QSize( 100, 185 ) );
  #elif defined( __WIN__ )
  setFixedSize( QSize( 100, 165 ) );
  #endif
}

QDspBlock::~QDspBlock()
{
  delete ui;
}

void QDspBlock::paintEvent(QPaintEvent *)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

//------------------------------------------------------------------------------
/*!
 *
 */
/*void QDspBlock::sendDspParameter( void )
{
  qDebug()<<"sendDspParameter not implemented";
}*/
