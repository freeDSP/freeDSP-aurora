#include <QDebug>
#include <QAbstractItemView>
#include <QFile>
#include <QByteArray>
#include <QMessageBox>
#include <QProgressDialog>

#include "DialogSettings.hpp"
#include "ui_DialogSettings.h"

DialogSettings::DialogSettings( CFreeDspAurora* ptrdsp, QWidget* parent ) :
  QDialog(parent),
  ui(new Ui::DialogSettings)
{
  ui->setupUi(this);
  dsp = ptrdsp;

  ui->radioButtonAP->blockSignals( true );
  ui->radioButtonLocalWifi->blockSignals( true );
  if( dsp->getConnectionTypeWifi() == CFreeDspAurora::ACCESS_POINT )
  {
    ui->radioButtonAP->setChecked( true );
    ui->pushButtonPing->setEnabled( false );
  }
  else
  {
    ui->radioButtonLocalWifi->setChecked( true );
    ui->pushButtonPing->setEnabled( true );
  }
  ui->radioButtonAP->blockSignals( false );
  ui->radioButtonLocalWifi->blockSignals( false );

  ui->lineEditIpAddress->setText( dsp->getIpAddressWifi() );
}

DialogSettings::~DialogSettings()
{
  delete ui;
}

//==============================================================================
/*!
 *
 */
void DialogSettings::on_pushButtonInstallPlugin_clicked()
{
  enableGui( false );

  //----------------------------------------------------------------------------
  //--- Read and convert the TxBuffer_IC_1.dat file
  //----------------------------------------------------------------------------
  #warning Pfad anpassen
  QFile fileTxBuffer( "/Users/rkn/Documents/freeDSP/freeDSP-aurora/SOURCES/SIGMASTUDIO/8channels/TxBuffer_IC_1.dat" );
  if( !fileTxBuffer.open( QIODevice::ReadOnly ) )
  {
    qDebug()<<__FILE__<<__LINE__<<"Could not open selected file";
    enableGui( true );
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
    enableGui( true );
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
      if( offset >= static_cast<uint32_t>(listTxBuffer.size()) )
      {
        qDebug()<<"TxBuffer too small";
        enableGui( true );
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
  while( offset < static_cast<uint32_t>(content.size()) )
  {
    QByteArray packet;
    for( int ii = 0; ii < 64; ii++ )
    {
      if( offset < static_cast<uint32_t>(content.size()) )
        packet.append( content.at(offset) );
      else
        packet.append( static_cast<char>(0) );
      offset++;
    }
    //if( npckt == 0 )
    dsp->sendDspFirmwareWifi( packet );
    //if( !dsp->sendDspFirmwareWifi( packet ) )
    //  QMessageBox::critical( this, tr("Error"), tr("Did not receive an ACK. Please check your WiFi"), QMessageBox::Ok );
    totalTransmittedBytes += static_cast<uint32_t>(packet.size());

    if( offset < static_cast<uint32_t>(content.size()) )
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

  enableGui( true );
}

//==============================================================================
/*!
 *
 */
void DialogSettings::on_pushButtonVerifyPlugin_clicked()
{
  enableGui( false );

  //----------------------------------------------------------------------------
  //--- Read and convert the TxBuffer_IC_1.dat file
  //----------------------------------------------------------------------------
  #warning Pfad anpassen
  QFile fileTxBuffer( "/Users/rkn/Documents/freeDSP/freeDSP-aurora/SOURCES/SIGMASTUDIO/8channels/TxBuffer_IC_1.dat" );
  if( !fileTxBuffer.open( QIODevice::ReadOnly ) )
  {
    qDebug()<<__FILE__<<__LINE__<<"Could not open selected file";
    enableGui( true );
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
    enableGui( true );
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
      if( offset >= static_cast<uint32_t>(listTxBuffer.size()) )
      {
        qDebug()<<"TxBuffer too small";
        enableGui( true );
        return;
      }

      char data = static_cast<char>( listTxBuffer[offset].toUInt( nullptr, 16 ) & 0xff );
      content.append( data );
      offset++;
    }
  }

  //----------------------------------------------------------------------------
  //--- Receive data from ESP32 via WiFi
  //----------------------------------------------------------------------------
  ui->progressBar->setMaximum( content.size()*3 );
  ui->progressBar->setValue( 0 );

  QByteArray firmware;
  dsp->requestDspFirmwareWifi( firmware, ui->progressBar );
  ui->progressBar->setValue( content.size()*2 );

  //----------------------------------------------------------------------------
  //--- Verify DSP firmware
  //----------------------------------------------------------------------------
  bool verified = true;
  for( int ii = 0; ii < content.size(); ii++ )
  {
    if( content.at(ii) != firmware.at(ii) )
    {
      verified = false;
      ui->progressBar->setValue( ii );
      //qDebug()<<ii<<":"<<QString::number( content.at(ii), 16 )<<QString::number( firmware.at(ii), 16 );
    }
  }

  ui->progressBar->setValue( content.size()*3 );

  if( !verified )
    QMessageBox::critical( this, tr("Error"), tr("DSP Plugin not verfied. You may want to reinstall the DSP plugin."), QMessageBox::Ok ); 
  else
    QMessageBox::information( this, tr("Information"), tr("Super! DSP plugin successfully verified."), QMessageBox::Ok ); 

  enableGui( true );  
}

//==============================================================================
/*!
 *
 */
void DialogSettings::on_pushButtonStoreWiFiConfig_clicked()
{
  enableGui( false );
  if( !ui->lineEditSSID->text().isEmpty() )
  {
    // --- Send WiFi configuration to DSP ---
    if( !dsp->storeSettingsWifi( ui->lineEditSSID->text(), ui->lineEditPassword->text() ) )
      QMessageBox::critical( this, tr("Error"), tr("Uups, something went wrong when sending WiFi configuration. Please double check everythind and try again."), QMessageBox::Ok );  
  }
  enableGui( true );
}

//==============================================================================
/*!
 *
 */
void DialogSettings::on_pushButtonPing_clicked()
{
  enableGui( false );
  dsp->pingWifi();
  ui->lineEditIpAddress->setText( dsp->getIpAddressWifi() );
  enableGui( true );
}

//==============================================================================
/*!
 *
 */
void DialogSettings::on_radioButtonAP_toggled(bool checked)
{
  if( checked )
  {
    dsp->setConnectionTypeWifi( CFreeDspAurora::ACCESS_POINT );
    ui->lineEditIpAddress->setText( dsp->getIpAddressWifi() );
    ui->pushButtonPing->setEnabled( false );
  }
}

//==============================================================================
/*!
 *
 */
void DialogSettings::on_radioButtonLocalWifi_toggled(bool checked)
{
  if( checked )
  {
    dsp->setConnectionTypeWifi( CFreeDspAurora::LOCAL_WIFI );
    ui->lineEditIpAddress->setText( dsp->getIpAddressWifi() );
    ui->pushButtonPing->setEnabled( true );
  }
}

//==============================================================================
/*!
 *
 */
void DialogSettings::enableGui( bool state )
{
  if( state )
  {
    ui->pushButtonInstallPlugin->setEnabled( true );
    ui->pushButtonVerifyPlugin->setEnabled( true );
    ui->radioButtonAP->setEnabled( true );
    ui->radioButtonLocalWifi->setEnabled( true );
    ui->lineEditSSID->setEnabled( true );
    ui->lineEditPassword->setEnabled( true );
    ui->pushButtonStoreWiFiConfig->setEnabled( true );
    ui->lineEditIpAddress->setEnabled( true );
    if( ui->radioButtonLocalWifi->isChecked() )
      ui->pushButtonPing->setEnabled( true );
    else
      ui->pushButtonPing->setEnabled( false );
    ui->buttonBox->setEnabled( true );
  }
  else
  {
    ui->pushButtonInstallPlugin->setEnabled( false );
    ui->pushButtonVerifyPlugin->setEnabled( false );
    ui->radioButtonAP->setEnabled( false );
    ui->radioButtonLocalWifi->setEnabled( false );
    ui->lineEditSSID->setEnabled( false );
    ui->lineEditPassword->setEnabled( false );
    ui->pushButtonStoreWiFiConfig->setEnabled( false );
    ui->lineEditIpAddress->setEnabled( false );
    ui->pushButtonPing->setEnabled( false );
    ui->buttonBox->setEnabled( false );
  }

}
