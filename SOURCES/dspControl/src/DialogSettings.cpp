//#if !defined( __IOS__ )
//#include <QSerialPortInfo>
//#endif
#include <QDebug>
#include <QAbstractItemView>
#include <QFile>
#include <QByteArray>
#include <QMessageBox>

#include "DialogSettings.hpp"
#include "ui_DialogSettings.h"

DialogSettings::DialogSettings( CFreeDspAurora* ptrdsp, QWidget* parent ) :
  QDialog(parent),
  ui(new Ui::DialogSettings)
{
  ui->setupUi(this);
  /*
#if !defined( __IOS__ )
  foreach( const QSerialPortInfo &info, QSerialPortInfo::availablePorts() )
    ui->comboBoxSerialPort->addItem( info.portName() );
#endif
  ui->comboBoxSerialPort->view()->setMinimumWidth( 300 );
*/
  dsp = ptrdsp;
}

DialogSettings::~DialogSettings()
{
  delete ui;
}
/*
QString DialogSettings::getPortName( void )
{
  return ui->comboBoxSerialPort->currentText();
}*/
/*
void DialogSettings::setPortName( const QString portname )
{
  ui->comboBoxSerialPort->setCurrentText( portname );
}*/

//==============================================================================
/*!
 *
 */
void DialogSettings::on_pushButtonInstallPlugin_clicked()
{
  //----------------------------------------------------------------------------
  //--- Read and convert the TxBuffer_IC_1.dat file
  //----------------------------------------------------------------------------
  #warning Pfad anpassen
  QFile fileTxBuffer( "/Users/rkn/Documents/freeDSP/freeDSP-aurora/SOURCES/SIGMASTUDIO/8channels/TxBuffer_IC_1.dat" );
  if( !fileTxBuffer.open( QIODevice::ReadOnly ) )
  {
    qDebug()<<__FILE__<<__LINE__<<"Could not open selected file";
    return;
  }

  QTextStream in( &fileTxBuffer );
  QStringList listTxBuffer;

  while( !in.atEnd() )
  {
    QString line = in.readLine().simplified();
    QStringList listStrings = line.split( ',' );
    for( int ii = 0; ii < listStrings.size(); ii++ )
    {
      QString str = listStrings[ii].simplified();
      if( str.startsWith( "0x" ) )
        listTxBuffer<<str;
    }
  }

  fileTxBuffer.close();

  //----------------------------------------------------------------------------
  //--- Read and convert the NumBytes_IC_1.dat file
  //----------------------------------------------------------------------------
  #warning Pfad anpassen
  QFile fileNumBytes( "/Users/rkn/Documents/freeDSP/freeDSP-aurora/SOURCES/SIGMASTUDIO/8channels/NumBytes_IC_1.dat" );
  if( !fileNumBytes.open( QIODevice::ReadOnly ) )
  {
    qDebug()<<__FILE__<<__LINE__<<"Could not open corresponding dat file";
    return;
  }

  QTextStream indat( &fileNumBytes );
  QStringList listNumBytes;

  while( !indat.atEnd() )
  {
    QString line = indat.readLine().simplified();
    QStringList listStrings = line.split( ',' );
    for( int ii = 0; ii < listStrings.size(); ii++ )
    {
      QString str = listStrings[ii].simplified();
      if( !str.isEmpty() )
        listNumBytes<<str;
    }
  }

  fileNumBytes.close();

  //----------------------------------------------------------------------------
  //--- Send data to ESP32 via WiFi
  //----------------------------------------------------------------------------
  QByteArray content;
  uint32_t offset = 0;
  for( int ii = 0; ii < listNumBytes.size(); ii++ )
  {
    uint32_t numbytes = listNumBytes[ii].toUInt( nullptr, 10 );

    content.append( (numbytes >> 24) & 0xFF );
    content.append( (numbytes >> 16) & 0xFF );
    content.append( (numbytes >>  8) & 0xFF );
    content.append(         numbytes & 0xFF );

    for( uint32_t n = 0; n < numbytes; n++ )
    {
      if( offset >= listTxBuffer.size() )
      {
        qDebug()<<"TxBuffer too small";
        return;
      }

      char data = static_cast<char>( listTxBuffer[offset].toUInt( nullptr, 16 ) & 0xff );
      content.append( data );
      offset++;
    }
  }

  ui->progressBar->setMaximum( content.size() );
  ui->progressBar->setValue( 0 );

  //qDebug()<<content.toHex();
  //qDebug()<<"Content size:"<<content.size();

  offset = 0;
  int npckt = 0;
  uint32_t totalTransmittedBytes = 0;
  while( offset < content.size() )
  {
    QByteArray packet;
    for( int ii = 0; ii < 64; ii++ )
    {
      if( offset < content.size() )
        packet.append( content.at(offset) );
      else
        packet.append( (char)0 );
      offset++;
    }
    //if( npckt == 0 )
    dsp->sendDspFirmwareWifi( packet );
    //if( !dsp->sendDspFirmwareWifi( packet ) )
    //  QMessageBox::critical( this, tr("Error"), tr("Did not receive an ACK. Please check your WiFi"), QMessageBox::Ok );
    totalTransmittedBytes += packet.size();

    if( offset < content.size() )
      ui->progressBar->setValue( offset );
    else
      ui->progressBar->setValue( content.size() );  
    npckt++;
  }

  if( dsp->finishDspFirmwareWifi( totalTransmittedBytes ) )
    QMessageBox::information( this, tr("Success"), tr("You have successfully installed the new DSP-Plugin!"), QMessageBox::Ok );
  else
    QMessageBox::critical( this, tr("Error"), tr("Uups, something went wrong. Please double check everythind and try again."), QMessageBox::Ok );  

  qDebug()<<"Success";
  qDebug()<<"File size:"<<content.size() * 8 / 1024<<"kBit";
  
}
