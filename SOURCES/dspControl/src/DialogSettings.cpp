#if !defined( __IOS__ )
#include <QSerialPortInfo>
#endif
#include <QDebug>
#include <QAbstractItemView>

#include "DialogSettings.hpp"
#include "ui_DialogSettings.h"

DialogSettings::DialogSettings(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::DialogSettings)
{
  ui->setupUi(this);
#if !defined( __IOS__ )
  foreach( const QSerialPortInfo &info, QSerialPortInfo::availablePorts() )
    ui->comboBoxSerialPort->addItem( info.portName() );
#endif
  ui->comboBoxSerialPort->view()->setMinimumWidth( 300 );
}

DialogSettings::~DialogSettings()
{
  delete ui;
}

QString DialogSettings::getPortName( void )
{
  return ui->comboBoxSerialPort->currentText();
}

void DialogSettings::setPortName( const QString portname )
{
  ui->comboBoxSerialPort->setCurrentText( portname );
}
