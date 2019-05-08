#include <QFileDialog>
#include <QDebug>
#include <QFile>

#include "dialogDspFirmware.hpp"
#include "ui_dialogDspFirmware.h"

Dialog::Dialog(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::Dialog)
{
  ui->setupUi(this);
}

Dialog::~Dialog()
{
  delete ui;
}

//==============================================================================
/*!
 *
 */
void Dialog::on_toolButtonSelectHexFile_triggered( QAction* )
{
  QString filename = QFileDialog::getOpenFileName(
          this,
          "Open Firmware Binary",
          QDir::currentPath(),
          "SigmaStudio Log File (*.dat)" );

    if( !filename.isNull() )
      ui->lineEditHexFile->setText( filename );
}

//==============================================================================
/*!
 *
 */
void Dialog::on_pushButtonHexFile_clicked()
{
  this->on_toolButtonSelectHexFile_triggered( nullptr );
}

//==============================================================================
/*!
 *
 */
void Dialog::on_pushButtonFlash_clicked()
{
  if( ui->lineEditHexFile->text().isEmpty() )
  {
    qDebug()<<__FILE__<<__LINE__<<"no file selected";
    return;
  }

  board.writeFirmwareToESP32viaBluetooth( ui->lineEditHexFile->text() );
}

void Dialog::on_pushButtonVerify_clicked()
{
  if( ui->lineEditHexFile->text().isEmpty() )
  {
    qDebug()<<__FILE__<<__LINE__<<"no file selected";
    return;
  }

  board.verifyFirmwareESP32viaBluetooth( ui->lineEditHexFile->text() );
}
