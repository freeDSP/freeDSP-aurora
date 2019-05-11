#include <QSerialPortInfo>
#include <QDebug>
#include <QFile>

#include <cstdint>

#include "freeDSP-Aurora.hpp"

#if 0
class CAdau1452
{
public:
  //----------------------------------------------------------------------------
  /*! Returns the max program size in bytes.
   *
   */
  uint32_t getMaxProgramSize( void ) { return 8192*4; }

public:
  unsigned char programMemory[8192*4];
  uint32_t programSize;

};

CAdau1452 dsp;
#endif

CFreeDspAurora::CFreeDspAurora()
{

}

//==============================================================================
/*!
 *
 */
bool CFreeDspAurora::sendByteSecured( char* txbyte )
{
  qDebug()<<"TX:"<<"0x" + QString::number( (int)(*txbyte), 16 );

  const qint64 bytesWritten = serial.write( txbyte, 1 );
  if (bytesWritten == -1)
  {
    qDebug()<<"Failed to write the data"<<serial.errorString();
    return false;
  }
  else if( bytesWritten != 1 )
  {
    qDebug()<<"Failed to write all the data"<<serial.errorString();
    return false;
  }
  else if( !serial.waitForBytesWritten() )
  {
    qDebug()<<"Operation timed out or an error occurred"<<serial.errorString();
    return false;
  }

  serial.waitForReadyRead();
  QByteArray rxData = serial.readAll();
  char rxByte = rxData[0];
  //qDebug()<<"RX:"<<"0x" + QString::number( ((int)rxByte & 0xFF), 16 );

  if( *txbyte != rxByte )
  {
    qDebug()<<"[ERROR] Received wrong byte. Connection seems corrupted.";
    return false;
  }

  return true;
}

//==============================================================================
/*!
 *
 */
bool CFreeDspAurora::sendByteSecured( byte txbyte )
{
  qDebug()<<"TX:"<<"0x" + QString::number( (int)(txbyte), 16 );

  const qint64 bytesWritten = serial.write( &txbyte, 1 );
  if (bytesWritten == -1)
  {
    qDebug()<<"Failed to write the data"<<serial.errorString();
    return false;
  }
  else if( bytesWritten != 1 )
  {
    qDebug()<<"Failed to write all the data"<<serial.errorString();
    return false;
  }
  else if( !serial.waitForBytesWritten() )
  {
    qDebug()<<"Operation timed out or an error occurred"<<serial.errorString();
    return false;
  }

  serial.waitForReadyRead();
  QByteArray rxData = serial.readAll();
  char rxByte = rxData[0];
  //qDebug()<<"RX:"<<"0x" + QString::number( ((int)rxByte & 0xFF), 16 );

  if( txbyte != rxByte )
  {
    qDebug()<<"[ERROR] Received wrong byte. Connection seems corrupted.";
    return false;
  }

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
  //QString file = path.section("/",-1,-1);
  //QString dir = path.section("/",0,-2);
  //file.replace( QString(".hex"), QString(".dat") );

  //QFile datfile( dir + "/" + file );
  path.replace( QString("TxBuffer"), QString("NumBytes") );
  QFile datfile( path );
  qDebug()<<path;
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
  maxBytes += listNumBytes.size() * 4;

  //----------------------------------------------------------------------------
  //--- Open the serial port Bluetooth device
  //----------------------------------------------------------------------------
  serial.setPortName( "/dev/cu.freedsp-aurora-ESP32_SP" );
  serial.open( QIODevice::ReadWrite );
  serial.setBaudRate( QSerialPort::Baud115200 );
  serial.setDataBits( QSerialPort::Data8 );
  serial.setParity( QSerialPort::NoParity );
  serial.setStopBits( QSerialPort::OneStop );
  serial.setFlowControl( QSerialPort::NoFlowControl );
  if( !serial.isOpen() )
  {
    if( !serial.open( QIODevice::ReadWrite ) )
    {
      qDebug()<<"Failed to open serial port"<<serial.errorString();
      return false;
    }
  }
  qDebug()<<"Opened serial port freeDSP-Aurora";

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
      if( offset >= listTxBuffer.size() )
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

  serial.close();

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
  serial.setPortName( "/dev/cu.freedsp-aurora-ESP32_SP" );
  serial.open( QIODevice::ReadWrite );
  serial.setBaudRate( QSerialPort::Baud115200 );
  serial.setDataBits( QSerialPort::Data8 );
  serial.setParity( QSerialPort::NoParity );
  serial.setStopBits( QSerialPort::OneStop );
  serial.setFlowControl( QSerialPort::NoFlowControl );
  if( !serial.isOpen() )
  {
    if( !serial.open( QIODevice::ReadWrite ) )
    {
      qDebug()<<"Failed to open serial port"<<serial.errorString();
      return false;
    }
  }
  qDebug()<<"Opened serial port freeDSP-Aurora";

  //----------------------------------------------------------------------------
  //--- Send data to ESP32 via Bluetooth
  //----------------------------------------------------------------------------

  char cmd = VERIFY;
  if( !sendByteSecured( &cmd ) )
    return false;


  serial.close();

  return true;
}
