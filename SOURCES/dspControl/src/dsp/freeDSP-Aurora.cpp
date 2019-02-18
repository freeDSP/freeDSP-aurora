#if !defined( __IOS__ )
#include <QSerialPortInfo>
#endif
#include <QDebug>
#include <QFile>

#include <cstdint>
#include <cstring>

#include "freeDSP-Aurora.hpp"

//==============================================================================
/*!
 *
 */
CFreeDspAurora::CFreeDspAurora()
{

}

//==============================================================================
/*!
 *
 */
bool CFreeDspAurora::sendByteSecured( char* txbyte )
{
  qDebug()<<"TX:"<<"0x" + QString::number( static_cast<uint32_t>(*txbyte), 16 );

  if( !isOpen )
    return false;
#if !defined( __IOS__ )
  const qint64 bytesWritten = serialBT.write( txbyte, 1 );
  if (bytesWritten == -1)
  {
    qDebug()<<"Failed to write the data"<<serialBT.errorString();
    return false;
  }
  else if( bytesWritten != 1 )
  {
    qDebug()<<"Failed to write all the data"<<serialBT.errorString();
    return false;
  }
  else if( !serialBT.waitForBytesWritten() )
  {
    qDebug()<<"Operation timed out or an error occurred"<<serialBT.errorString();
    return false;
  }

  serialBT.waitForReadyRead();
  QByteArray rxData = serialBT.readAll();
  char rxByte = rxData[0];
  //qDebug()<<"RX:"<<"0x" + QString::number( ((int)rxByte & 0xFF), 16 );

  if( *txbyte != rxByte )
  {
    qDebug()<<"[ERROR] Received wrong byte. Connection seems corrupted.";
    return false;
  }
#endif
  return true;
}

//==============================================================================
/*!
 *
 */
bool CFreeDspAurora::sendByteSecured( byte txbyte )
{
  qDebug()<<"TX:"<<"0x" + QString::number( static_cast<uint32_t>(txbyte), 16 );

  if( !isOpen )
    return false;
#if !defined( __IOS__ )
  const qint64 bytesWritten = serialBT.write( &txbyte, 1 );
  if (bytesWritten == -1)
  {
    qDebug()<<"Failed to write the data"<<serialBT.errorString();
    return false;
  }
  else if( bytesWritten != 1 )
  {
    qDebug()<<"Failed to write all the data"<<serialBT.errorString();
    return false;
  }
  else if( !serialBT.waitForBytesWritten() )
  {
    qDebug()<<"Operation timed out or an error occurred"<<serialBT.errorString();
    return false;
  }

  serialBT.waitForReadyRead();
  QByteArray rxData = serialBT.readAll();
  char rxByte = rxData[0];
  //qDebug()<<"RX:"<<"0x" + QString::number( ((int)rxByte & 0xFF), 16 );

  if( txbyte != rxByte )
  {
    qDebug()<<"[ERROR] Received wrong byte. Connection seems corrupted.";
    return false;
  }
#endif
  return true;

}

//==============================================================================
/*!
 *
 */
bool CFreeDspAurora::writeFirmwareToESP32viaBluetooth( const QString& hexfilename )
{
  //----------------------------------------------------------------------------
  //--- Read and convert the TxBuffer_IC_1.dat file
  //----------------------------------------------------------------------------
  QFile hexfile( hexfilename );
  if( !hexfile.open( QIODevice::ReadOnly ) )
  {
    qDebug()<<__FILE__<<__LINE__<<"Could not open selected hex file";
    return false;
  }

  QTextStream in( &hexfile );
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

  hexfile.close();

  //----------------------------------------------------------------------------
  //--- Read and convert the NumBytes_IC_1.dat file
  //----------------------------------------------------------------------------
  QString path = hexfilename;
  QString file = path.section("/",-1,-1);
  QString dir = path.section("/",0,-2);
  file.replace( QString(".hex"), QString(".dat") );

  QFile datfile( dir + "/" + file );
  if( !datfile.open( QIODevice::ReadOnly ) )
  {
    qDebug()<<__FILE__<<__LINE__<<"Could not open corresponding dat file";
    return false;
  }

  QTextStream indat( &datfile );
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

  datfile.close();

  uint32_t maxBytes = 0;
  for( int ii = 0; ii < listNumBytes.size(); ii++ )
    maxBytes += listNumBytes[ii].toUInt( nullptr, 10 );
  maxBytes += static_cast<unsigned>(listNumBytes.size()) * 4;

  //----------------------------------------------------------------------------
  //--- Open the serial port Bluetooth device
  //----------------------------------------------------------------------------
#if !defined( __IOS__ )
  serialBT.setPortName( "/dev/cu.freedsp-aurora-ESP32_SP" );
  serialBT.open( QIODevice::ReadWrite );
  serialBT.setBaudRate( QSerialPort::Baud115200 );
  serialBT.setDataBits( QSerialPort::Data8 );
  serialBT.setParity( QSerialPort::NoParity );
  serialBT.setStopBits( QSerialPort::OneStop );
  serialBT.setFlowControl( QSerialPort::NoFlowControl );
  if( !serialBT.isOpen() )
  {
    if( !serialBT.open( QIODevice::ReadWrite ) )
    {
      qDebug()<<"Failed to open serial port"<<serialBT.errorString();
      return false;
    }
  }
  qDebug()<<"Opened serial port freeDSP-Aurora";
#endif
  //----------------------------------------------------------------------------
  //--- Send data to ESP32 via Bluetooth
  //----------------------------------------------------------------------------

  char cmd = NEWFW;
  if( !sendByteSecured( &cmd ) )
    return false;

  qDebug()<<"Sending"<<maxBytes<<"bytes";

  char data = static_cast<char>( (maxBytes & 0xFF000000) >> 24 );
  if( !sendByteSecured( &data ) )
    return false;
  data = static_cast<char>( (maxBytes & 0x00FF0000) >> 16 );
  if( !sendByteSecured( &data ) )
    return false;
  data = static_cast<char>( (maxBytes & 0x0000FF00) >> 8 );
  if( !sendByteSecured( &data ) )
    return false;
  data = static_cast<char>( maxBytes & 0x000000FF );
  if( !sendByteSecured( &data ) )
    return false;

  uint32_t offset = 0;
  for( int ii = 0; ii < listNumBytes.size(); ii++ )
  {
    uint32_t numbytes = listNumBytes[ii].toUInt( nullptr, 10 );
    qDebug()<<"Bytes: "<<numbytes;

    if( !sendByteSecured( (numbytes >> 24) & 0xFF ) )
      return false;
    if( !sendByteSecured( (numbytes >> 16) & 0xFF ) )
      return false;
    if( !sendByteSecured( (numbytes >> 8) & 0xFF ) )
      return false;
    if( !sendByteSecured( numbytes & 0xFF ) )
      return false;

    qDebug()<<"Data:";
    for( uint32_t n = 0; n < numbytes; n++ )
    {
      if( offset >= static_cast<unsigned>(listTxBuffer.size()) )
      {
        qDebug()<<"TxBuffer too small";
        return false;
      }

      data = static_cast<char>( listTxBuffer[offset].toUInt( nullptr, 16 ) & 0xff );
      if( !sendByteSecured( &data ) )
        return false;
      offset++;
    }

    qDebug()<<"---------------------------------------------------------------";
  }

  qDebug()<<"Data successfully sent";
#if !defined( __IOS__ )
  serialBT.close();
#endif
  return true;
}

//==============================================================================
/*!
 *
 */
bool CFreeDspAurora::verifyFirmwareESP32viaBluetooth( const QString& hexfilename )
{
  //----------------------------------------------------------------------------
  //--- Open the serial port Bluetooth device
  //----------------------------------------------------------------------------
#if !defined( __IOS__ )
  serialBT.setPortName( "/dev/cu.freedsp-aurora-ESP32_SP" );
  serialBT.open( QIODevice::ReadWrite );
  serialBT.setBaudRate( QSerialPort::Baud115200 );
  serialBT.setDataBits( QSerialPort::Data8 );
  serialBT.setParity( QSerialPort::NoParity );
  serialBT.setStopBits( QSerialPort::OneStop );
  serialBT.setFlowControl( QSerialPort::NoFlowControl );
  if( !serialBT.isOpen() )
  {
    if( !serialBT.open( QIODevice::ReadWrite ) )
    {
      qDebug()<<"Failed to open serial port"<<serialBT.errorString();
      return false;
    }
  }
  qDebug()<<"Opened serial port freeDSP-Aurora";
#endif
  //----------------------------------------------------------------------------
  //--- Send data to ESP32 via Bluetooth
  //----------------------------------------------------------------------------

  char cmd = VERIFY;
  if( !sendByteSecured( &cmd ) )
    return false;

#if !defined( __IOS__ )
  serialBT.close();
#endif
  return true;
}

//==============================================================================
/*!
 *
 */
bool CFreeDspAurora::open( const QString portname )
{
  isOpen = false;

  #if !defined( DEMO )
  //----------------------------------------------------------------------------
  //--- Open the serial port Bluetooth device
  //----------------------------------------------------------------------------
  serialBT.setPortName( portname );
  serialBT.open( QIODevice::ReadWrite );
  serialBT.setBaudRate( QSerialPort::Baud115200 );
  serialBT.setDataBits( QSerialPort::Data8 );
  serialBT.setParity( QSerialPort::NoParity );
  serialBT.setStopBits( QSerialPort::OneStop );
  serialBT.setFlowControl( QSerialPort::NoFlowControl );
  if( !serialBT.isOpen() )
  {
    if( !serialBT.open( QIODevice::ReadWrite ) )
    {
      qDebug()<<"Failed to open serial port"<<serialBT.errorString();
      return false;
    }
  }
  qDebug()<<"Opened serial port freeDSP-Aurora";
  isOpen = true;
  #endif

  return true;
}

//==============================================================================
/*!
 *
 */
void CFreeDspAurora::close( void )
{
  isOpen = false;
  #if !defined( DEMO )
  serialBT.close();
  #endif
}

//==============================================================================
/*!
 *
 */
bool CFreeDspAurora::sendParameter( uint16_t reg, float val )
{
  qDebug()<<"---------------------------------------------------------------";
  qDebug()<<"sendParameter()";

  char cmd = PARAM;
  if( !sendByteSecured( &cmd ) )
    return false;

/*  uint32_t numbytes = 6;
  qDebug()<<"Bytes: "<<numbytes;

  if( !sendByteSecured( (numbytes >> 24) & 0xFF ) )
    return false;
  if( !sendByteSecured( (numbytes >> 16) & 0xFF ) )
    return false;
  if( !sendByteSecured( (numbytes >> 8) & 0xFF ) )
    return false;
  if( !sendByteSecured( numbytes & 0xFF ) )
    return false;
*/

  if( !sendByteSecured( (reg >> 8) & 0xFF ) )
    return false;
  if( !sendByteSecured( reg & 0xFF ) )
    return false;

  uint32_t data;
  std::memcpy( &data, &val, sizeof(float) );
  if( !sendByteSecured( (data >> 24) & 0xFF ) )
    return false;
  if( !sendByteSecured( (data >> 16) & 0xFF ) )
    return false;
  if( !sendByteSecured( (data >> 8) & 0xFF ) )
    return false;
  if( !sendByteSecured( data & 0xFF ) )
    return false;

  return true;
}

//==============================================================================
/*!
 *
 */
bool CFreeDspAurora::sendParameter( uint16_t reg, uint32_t val )
{
  qDebug()<<"---------------------------------------------------------------";
  qDebug()<<"sendParameter()";

  char cmd = PARAM;
  if( !sendByteSecured( &cmd ) )
    return false;

/*  uint32_t numbytes = 6;
  qDebug()<<"Bytes: "<<numbytes;

  if( !sendByteSecured( (numbytes >> 24) & 0xFF ) )
    return false;
  if( !sendByteSecured( (numbytes >> 16) & 0xFF ) )
    return false;
  if( !sendByteSecured( (numbytes >> 8) & 0xFF ) )
    return false;
  if( !sendByteSecured( numbytes & 0xFF ) )
    return false;
*/

  if( !sendByteSecured( (reg >> 8) & 0xFF ) )
    return false;
  if( !sendByteSecured( reg & 0xFF ) )
    return false;

  uint32_t data = val;
  //std::memcpy( &data, &val, sizeof(float) );
  if( !sendByteSecured( (data >> 24) & 0xFF ) )
    return false;
  if( !sendByteSecured( (data >> 16) & 0xFF ) )
    return false;
  if( !sendByteSecured( (data >> 8) & 0xFF ) )
    return false;
  if( !sendByteSecured( data & 0xFF ) )
    return false;

  return true;
}

//==============================================================================
/*!
 *
 */
bool CFreeDspAurora::storeRegAddr( uint16_t reg )
{
  if( !sendByteSecured( static_cast<byte>((reg >> 8) & 0xFF) ) )
    return false;
  if( !sendByteSecured( static_cast<byte>(reg & 0xFF) ) )
    return false;
  return true;
}

//==============================================================================
/*!
 *
 */
bool CFreeDspAurora::storeValue( float val )
{
  uint32_t data;
  std::memcpy( &data, &val, sizeof(float) );
  if( !sendByteSecured( static_cast<byte>((data >> 24) & 0xFF) ) )
    return false;
  if( !sendByteSecured( static_cast<byte>((data >> 16) & 0xFF) ) )
    return false;
  if( !sendByteSecured( static_cast<byte>((data >> 8) & 0xFF) ) )
    return false;
  if( !sendByteSecured( static_cast<byte>(data & 0xFF) ) )
    return false;
  return true;
}

//==============================================================================
/*!
 *
 */
bool CFreeDspAurora::storeValue( uint32_t val )
{
  uint32_t data = val;
  if( !sendByteSecured( static_cast<byte>((data >> 24) & 0xFF) ) )
    return false;
  if( !sendByteSecured( static_cast<byte>((data >> 16) & 0xFF) ) )
    return false;
  if( !sendByteSecured( static_cast<byte>((data >> 8) & 0xFF) ) )
    return false;
  if( !sendByteSecured( static_cast<byte>(data & 0xFF) ) )
    return false;
  return true;
}

//==============================================================================
/*!
 *
 */
bool CFreeDspAurora::beginStoreParams( uint32_t numbytes )
{
  qDebug()<<"---------------------------------------------------------------";
  qDebug()<<"beginStoreParams()";

  char cmd = SAVEPARAMS;
  if( !sendByteSecured( &cmd ) )
    return false;

  if( !sendByteSecured( (numbytes >> 24) & 0xFF ) )
    return false;
  if( !sendByteSecured( (numbytes >> 16) & 0xFF ) )
    return false;
  if( !sendByteSecured( (numbytes >> 8) & 0xFF ) )
    return false;
  if( !sendByteSecured( numbytes & 0xFF ) )
    return false;
  return true;
}
