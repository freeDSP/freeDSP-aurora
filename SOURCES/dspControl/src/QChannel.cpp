#include "QChannel.hpp"
#include "ui_QChannel.h"

QChannel::QChannel(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::QChannel)
{
  ui->setupUi(this);
  ui->figVoltageMagnitude->axis( 10.0, 20000.0, -40.0, 20.0 );
  //figVoltageMagnitude->xlabel( tr("Frequency [Hz]") );
  //figVoltageMagnitude->ylabel( tr("20*log10(|G(s)|) [dB]") );
  ui->figVoltageMagnitude->ytick( 2.0 );
  ui->figVoltageMagnitude->xtick( 10.0 );

  #if defined( __MACOSX__ )
  ui->widgetChannel->setMinimumHeight( 183 );
  ui->scrollArea->setMinimumHeight( 185 );
  #elif defined( __WIN__ ) 
  ui->widgetChannel->setMinimumHeight( 140 );
  ui->scrollArea->setMinimumHeight( 160 );
  #endif

  widgetChannel = ui->widgetChannel;
  figVoltageMagnitude = ui->figVoltageMagnitude;

  connect( ui->figVoltageMagnitude, SIGNAL(customContextMenuRequested(const QPoint &)),
           this, SLOT(on_showContextMenu(const QPoint &)));
}

QChannel::~QChannel()
{
  delete ui;
}

void QChannel::on_showContextMenu( const QPoint &pos )
{
  contextMenu.exec( mapToGlobal(pos) );
  emit selectionChanged();
}
