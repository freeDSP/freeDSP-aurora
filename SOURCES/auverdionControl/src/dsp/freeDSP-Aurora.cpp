#include <math.h>
#include <cstdint>
#include <cstring>

#include <QFile>
#include <QMessageBox>
#include <QTimer>

#include "LogFile.h"
#include "freeDSP-Aurora.hpp"

extern CLogFile myLog;

#define TIMEOUT_WIFI (60000)

//==============================================================================
/*! Constructor
 *
 */
CFreeDspAurora::CFreeDspAurora( QWidget* parent ) : QWidget( parent )
{
  tcpSocket = new QTcpSocket( this );
  connect( tcpSocket, SIGNAL( bytesWritten(qint64) ),                this, SLOT( bytesWrittenWifi(qint64)                ) );
  connect( tcpSocket, SIGNAL( disconnected() ),                      this, SLOT( disconnectedWifi()                      ) );
  connect( tcpSocket, SIGNAL( error(QAbstractSocket::SocketError) ), this, SLOT( errorWifi(QAbstractSocket::SocketError) ) );
  connect( tcpSocket, SIGNAL( hostFound() ),                         this, SLOT( hostFoundWifi()                         ) );
  connect( tcpSocket, SIGNAL( readyRead() ),                         this, SLOT( readyReadWifi()                         ) );
  
  //connect( this, SIGNAL( haveReplyWifi() ), &loopWaitForResponseWiFi, SLOT( quit() ) );

  ipAddressAP = "192.168.5.1";
  ipAddressLocal = "0.0.0.0";
  connectionType = ACCESS_POINT;
  portHostWifi = 80;
  
  ptrProgressBar = nullptr;
}

//==============================================================================
/*! Destructor
 *
 */
CFreeDspAurora::~CFreeDspAurora( void )
{
  if( tcpSocket != nullptr )
    delete tcpSocket;
}

//==============================================================================
/*!
 *
 */
uint32_t convertTo824( float val )
{
  float fractpart, intpart;
  uint32_t ret;
  fractpart = modf( val, &intpart );
  if( intpart > 127.0f )
    intpart = 127.0f;
  if( intpart < -128.0f )
    intpart = -128.0f;

  if( fractpart < 0.0f )
    fractpart *= -1.0f;
  
  intpart = floor( val );
  fractpart = val - intpart;
  
  ret = ((( static_cast<uint32_t>(static_cast<int8_t>(intpart)) ) << 24) & 0xff000000)
      + ((static_cast<uint32_t>(fractpart * 16777216.f)) & 0x00ffffff);

  return ret;
}


//==============================================================================
/*! Prepares a content packet for a parameter
 *
 */
QByteArray CFreeDspAurora::makeParameterForWifi( uint16_t reg, float val )
{
  QByteArray content;
  content.append( static_cast<char>((reg >> 8) & 0x000000FF) );
  content.append( static_cast<char>(reg & 0x000000FF) );

  uint32_t data = convertTo824( val );

  content.append( static_cast<char>((data >> 24) & 0x000000FF) );
  content.append( static_cast<char>((data >> 16) & 0x000000FF) );
  content.append( static_cast<char>((data >> 8) & 0x000000FF) );
  content.append( static_cast<char>(data & 0x000000FF) );
  
  return content;
}

//==============================================================================
/*! Prepares a content packet for a parameter
 *
 */
QByteArray CFreeDspAurora::makeParameterForWifi( uint16_t reg, int32_t val )
{
  QByteArray content;
  content.append( static_cast<char>((reg >> 8) & 0x000000FF) );
  content.append( static_cast<char>(reg & 0x000000FF) );

  uint32_t data = static_cast<uint32_t>(val);

  content.append( static_cast<char>((data >> 24) & 0x000000FF) );
  content.append( static_cast<char>((data >> 16) & 0x000000FF) );
  content.append( static_cast<char>((data >> 8) & 0x000000FF) );
  content.append( static_cast<char>(data & 0x000000FF) );
  
  return content;
}

//==============================================================================
/*!
 *
 */
bool CFreeDspAurora::sendParameterWifi( QByteArray content )
{
  myLog()<<"---------------------------------------------------------------";
  myLog()<<"sendParameterWifi()";
  
  if( isConnected )
  {
    QString wifiIpHost = getIpAddressWifi();

    QString requestString = QString("POST /parameter HTTP/1.1\r\n")
                          + QString("Host: ") + wifiIpHost + QString("\r\n")
                          + QString("Content-type:text/plain\r\n")
                          + QString("Content-length: ") +  QString::number( content.size()*2 ) + QString("\r\n")
                          + QString("\r\n");
    QByteArray request;
    request.append( requestString );  
    request.append( content.toHex() );  
    request.append( "\r\n" );

    writeRequestWifi( request );
  /*
    if( !waitForReplyWifi() )
      return false;
    else
    {
      myLog<<QString( replyDSP );
      QStringList listReply = QString( replyDSP ).split( QRegExp("\\s+") );
      //! \TODO Test for ACK.
      return true;
    }
  */
    return true;
  }
  else
  {
    myLog()<<"Not connected to DSP.";
    return false;
  }
  
}

//==============================================================================
/*! Starts the transfer of a new dsp firmware block.
 *
 * \param content Data block of firmware.
 */
bool CFreeDspAurora::sendDspFirmwareWifi( QByteArray content )
{
  myLog()<<"---------------------------------------------------------------";
  myLog()<<"sendDspFirmwareWifi()";

  QString wifiIpHost = getIpAddressWifi();

  QString requestString = QString( "PUT /dspfw HTTP/1.1\r\n" )
                        + QString( "Host: " ) + wifiIpHost + QString( "\r\n" )
                        + QString( "Content-type:application/octet-stream\r\n" )
                        + QString( "Content-length: " ) + QString::number( content.size()*2 ) + QString( "\r\n" )
                        + QString( "\r\n" );
  QByteArray request;
  request.append( requestString );
  request.append( content.toHex() );  
  request.append( "\r\n" );

  if( writeRequestWifi( request ) )
  {
    if( !waitForReplyWifi() )
    {
      myLog()<<"Writing firmware to DSP failed";
      QMessageBox::critical( this, tr("Error"), tr("Uups, writing firmware to DSP failed. Please double check everything, reset DSP and try again."), QMessageBox::Ok ); 
      return false;
    }
    else
      return true;
  }
  else
  {
    myLog()<<"Could not connect to DSP";
    QMessageBox::critical( this, tr("Error"), tr("Uups, could not connect to DSP. Did you switch it on?"), QMessageBox::Ok );
  }

  return false;

}

//==============================================================================
/*! Finishes the transfer of a new dsp firmware.
 *
 */
bool CFreeDspAurora::finishDspFirmwareWifi( uint32_t totalTransmittedBytes )
{
  myLog()<<"---------------------------------------------------------------";
  myLog()<<"finishDspFirmwareWifi";


  QString wifiIpHost = getIpAddressWifi();

  QString requestString = QString( "GET /finishdspfw HTTP/1.1\r\n" )
                        + QString( "Host: " ) + wifiIpHost + QString( "\r\n" )
                        + QString( "\r\n" );
  QByteArray request;
  request.append( requestString );
  
  writeRequestWifi( request );

  if( !waitForReplyWifi() )
  {
    QMessageBox::critical( this, tr("Error"), tr("Uups, could not finish transfer of DSP firmware. Please double check everything, reset DSP and try again."), QMessageBox::Ok ); 
    myLog()<<"CFreeDspAurora::finishDspFirmwareWifi: Did not receive reply.";
    return false;
  }
  else
  {
    myLog()<<QString( replyDSP );
    QStringList listReply = QString( replyDSP ).split( QRegExp("\\s+") );
    uint32_t totalReceivedBytes = listReply.at(4).toUInt();
    myLog()<<totalTransmittedBytes<<totalReceivedBytes;

    if( totalTransmittedBytes == totalReceivedBytes )
      return true;
    else
      return false;
  }

}

//==============================================================================
/*! Starts the transfer of a new block of the dsp parameter file.
 *
 * \param content Block of parameter file.
 */
bool CFreeDspAurora::sendDspParameterWifi( QByteArray content )
{
  myLog()<<"---------------------------------------------------------------";
  myLog()<<"sendDspParameterWifi()";

  if( isConnected )
  {
    QString wifiIpHost = getIpAddressWifi();

    QString requestString = QString( "PUT /dspparam HTTP/1.1\r\n" )
                          + QString( "Host: " ) + wifiIpHost + QString( "\r\n" )
                          + QString( "Content-type:application/octet-stream\r\n" )
                          + QString( "Content-length: " ) + QString::number( content.size()*2 ) + QString( "\r\n" )
                          + QString( "\r\n" );
    QByteArray request;
    request.append( requestString );
    request.append( content.toHex() );  
    request.append( "\r\n" );
    
    writeRequestWifi( request );

    if( !waitForReplyWifi() )
    {
      myLog()<<"Writing parameters to DSP failed";
      QMessageBox::critical( this, tr("Error"), tr("Uups, writing parameters to DSP failed. Please double check everything, reset DSP and try again."), QMessageBox::Ok ); 
      return false;
    }
    else
      return true;
  }
  else
  {
    myLog()<<"Not connected to DSP.";
    return false;
  }
}

//==============================================================================
/*! Finishes the transfer of the DSP parameter file.
 *
 */
bool CFreeDspAurora::finishDspParameterWifi( uint32_t totalTransmittedBytes )
{
  myLog()<<"---------------------------------------------------------------";
  myLog()<<"finishDspParameterWifi";

  if( isConnected )
  {
    QString wifiIpHost = getIpAddressWifi();

    QString requestString = QString( "GET /finishdspparameter HTTP/1.1\r\n" )
                          + QString( "Host: " ) + wifiIpHost + QString( "\r\n" )
                          + QString( "\r\n" );
    QByteArray request;
    request.append( requestString );
    
    writeRequestWifi( request );

    if( !waitForReplyWifi() )
    {
      myLog()<<"Could not finish transfer of DSP parameter file";
      QMessageBox::critical( this, tr("Error"), tr("Uups, could not finish transfer of DSP parameter file. Please double check everything, reset DSP and try again."), QMessageBox::Ok ); 
      return false;
    }
    else
    {
      myLog()<<QString( replyDSP );
      QStringList listReply = QString( replyDSP ).split( QRegExp("\\s+") );
      uint32_t totalReceivedBytes = listReply.at(4).toUInt();
      myLog()<<totalTransmittedBytes<<totalReceivedBytes;

      if( totalTransmittedBytes == totalReceivedBytes )
        return true;
      else
      {
        myLog()<<"[ERROR] Transmitted "<<totalTransmittedBytes*2<<"but DSP received "<<totalReceivedBytes<<"bytes.";
        return false;
      }
    }
  }
  else
  {
    myLog()<<"Not connected to DSP.";
    return false;
  }
}

//==============================================================================
/*! Requests the PID of current installed DSP-Plugin
 *
 */
uint32_t CFreeDspAurora::requestPidWifi( void )
{
  myLog()<<"---------------------------------------------------------------";
  myLog()<<"requestPidWifi";

  isConnected = false;

  QString wifiIpHost = getIpAddressWifi();

  QString requestString = QString("GET /pid HTTP/1.1\r\nHost: ")
                        + wifiIpHost
                        + QString("\r\n\r\n");
  QByteArray request;
  request.append( requestString );

  uint32_t pid = 0;
  if( writeRequestWifi( request ) )
  {
    if( !waitForReplyWifi() )
    {
      myLog()<<"Did not receive PID.";
      QMessageBox::critical( this, tr("Error"), tr("Uuups, could not receive PID. Please double check everything and try again."), QMessageBox::Ok ); 
      return 0;
    }
    else
    {
      QStringList listReply = QString( replyDSP ).split( QRegExp("\\s+") );
      if( listReply.size() > 4 )
        pid = listReply.at(4).toUInt();
      myLog()<<"PID:"<<pid;  
      if( pid > 0 )
        isConnected = true;
    }
  }
  else
  {
    myLog()<<"Could not connect to DSP";
    QMessageBox::critical( this, tr("Error"), tr("Uups, could not connect to DSP. Did you switch it on?"), QMessageBox::Ok );
  }
  
  return pid;
}

//==============================================================================
/*! Requests index of current selected preset
 *
 */
int32_t CFreeDspAurora::requestCurrentPresetWifi( void )
{
  myLog()<<"---------------------------------------------------------------";
  myLog()<<"requestCurrentPresetWifi";

  QString wifiIpHost = getIpAddressWifi();

  QString requestString = QString("GET /currentpreset HTTP/1.1\r\nHost: ")
                        + wifiIpHost
                        + QString("\r\n\r\n");
  QByteArray request;
  request.append( requestString );

  int32_t preset = -1;
  if( writeRequestWifi( request ) )
  {
    if( !waitForReplyWifi() )
    {
      myLog()<<"Did not receive index of current preset.";
      QMessageBox::critical( this, tr("Error"), tr("Uuups, could not receive index of current preset. Please double check everything and try again."), QMessageBox::Ok ); 
      return -1;
    }
    else
    {
      QStringList listReply = QString( replyDSP ).split( QRegExp("\\s+") );
      if( listReply.size() > 4 )
        preset = listReply.at(4).toUInt();
      myLog()<<"Current preset:"<<preset;  
    }
  }
  else
  {
    myLog()<<"Could not connect to DSP";
    QMessageBox::critical( this, tr("Error"), tr("Uups, could not connect to DSP. Did you switch it on?"), QMessageBox::Ok );
  }
  
  return preset;
}

//==============================================================================
/*! Starts the transfer of a user data block.
 *
 * \param content Data block of user data.
 */
bool CFreeDspAurora::sendUserParameterWifi( QByteArray content )
{
  myLog()<<"---------------------------------------------------------------";
  myLog()<<"sendUserParameterWifi()";

  if( isConnected )
  {
    QString wifiIpHost = getIpAddressWifi();

    QString requestString = QString( "PUT /userparam HTTP/1.1\r\n" )
                          + QString( "Host: " ) + wifiIpHost + QString( "\r\n" )
                          + QString( "Content-type:application/octet-stream\r\n" )
                          + QString( "Content-length: " ) + QString::number( content.size()*2 ) + QString( "\r\n" )
                          + QString( "\r\n" );
    QByteArray request;
    request.append( requestString );
    request.append( content.toHex() );  
    request.append( "\r\n" );

    writeRequestWifi( request );

    if( !waitForReplyWifi() )
    {
      myLog()<<"Writng parameters to DSP failed";
      QMessageBox::critical( this, tr("Error"), tr("Uups, writing parameters to DSP failed. Please double check everything, reset DSP and try again."), QMessageBox::Ok ); 
      return false;
    }
    else
      return true;
  }
  else
  {
    myLog()<<"Not connected to DSP.";
    return false;
  }
  
}

//==============================================================================
/*! Finishes the transfer of user parameter file.
 *
 */
bool CFreeDspAurora::finishUserParameterWifi( uint32_t totalTransmittedBytes )
{
  myLog()<<"---------------------------------------------------------------";
  myLog()<<"finishUserParameterWifi";

  if( isConnected )
  {
    QString wifiIpHost = getIpAddressWifi();

    QString requestString = QString("GET /finishuserparam HTTP/1.1\r\nHost: ")
                          + wifiIpHost
                          + QString("\r\n\r\n");
    QByteArray request;
    request.append( requestString );
    
    writeRequestWifi( request );

    if( !waitForReplyWifi() )
    {
      myLog()<<"Could not finish transfer of user parameter";
      QMessageBox::critical( this, tr("Error"), tr("Could not finish transfer of user parameter file. Please double check everything, reset DSP and try again."), QMessageBox::Ok ); 
      return false;
    }
    else
    {
      myLog()<<QString( replyDSP );
      QStringList listReply = QString( replyDSP ).split( QRegExp("\\s+") );
      uint32_t totalReceivedBytes = listReply.at(4).toUInt();

      if( totalTransmittedBytes == totalReceivedBytes )
        return true;
      else
      {
        myLog()<<"[ERROR] Transmitted "<<totalTransmittedBytes*2<<"but DSP received "<<totalReceivedBytes<<"bytes.";
        return false;
      }
    }
  }
  else
  {
    myLog()<<"Not connected to DSP.";
    return false;
  }
}

//==============================================================================
/*! Request the user parameter file.
 *
 */
bool CFreeDspAurora::requestUserParameterWifi( QByteArray& userparams )
{
  myLog()<<"---------------------------------------------------------------";
  myLog()<<"receiveUserParameterWifi";

  if( isConnected )
  {
    QString wifiIpHost = getIpAddressWifi();

    uint32_t totalBytes = 0;

    QString requestString = QString("GET /sizeuserparam HTTP/1.1\r\nHost: ")
                          + wifiIpHost
                          + QString("\r\n\r\n");
    QByteArray request;
    request.append( requestString );

    writeRequestWifi( request );
    if( !waitForReplyWifi() )
    {
      myLog()<<"Could not receive the size of the user parameter file";
      QMessageBox::critical( this, tr("Error"), tr("Could not receive the size of the user parameter file. Please double check everything and try again."), QMessageBox::Ok ); 
      return false;
    }
    else
    {
      myLog()<<QString( replyDSP );
      QStringList listReply = QString( replyDSP ).split( QRegExp("\\s+") );
      totalBytes = listReply.at(4).toUInt();

      if( totalBytes > 0 )
      {
        requestString = QString("GET /userparam HTTP/1.1\r\nHost: ")
                      + wifiIpHost
                      + QString("\r\n\r\n");
        request.clear();
        request.append( requestString );
        writeRequestWifi( request );
        if( !waitForReplyWifi() )
        {
          myLog()<<"Could not receive the user parameter file";
          QMessageBox::critical( this, tr("Error"), tr("Could not receive the user parameter file. Please double check everything and try again."), QMessageBox::Ok ); 
          return false;
        }
        else
        {
          listReply = QString( replyDSP ).split( QRegExp("\\s+") );
          myLog()<<"Received user parameter"<<listReply.at(4).size();
          QString str = listReply.at(4);
          int offset = 0;
          
          while( offset < str.length() )
          {
            bool ok;
            uint8_t val = str.mid( offset, 2 ).toUInt( &ok, 16 );
            userparams.append( val );
            offset += 2;
          }
        }
      }
    }  
  
    myLog()<<"Done";
    myLog()<<"Received: "<<userparams.size()<<"/"<<totalBytes;

    if( static_cast<uint32_t>(userparams.size()) < totalBytes )
    {
      myLog()<<"Could not receive all bytes of the user parameter file";
      QMessageBox::critical( this, tr("Error"), tr("Could not receive all bytes of the user parameter file. Please double check all connections and reset all devices and try again."), QMessageBox::Ok ); 
      return false;
    }

    return true;
  }
  else
  {
    myLog()<<"Not connected to DSP.";
    return false;
  }
}

//==============================================================================
/*!
 */
void CFreeDspAurora::readyReadWifi( void )
{
  replyWifi.append( tcpSocket->readAll() );
  QString str = QString( replyWifi );
  QStringList listReply = str.split( QRegExp("\\s+") );
  if( ptrProgressBar != nullptr )
    ptrProgressBar->setValue( replyWifi.size() );
  if( (listReply.size() > 4) && (str.mid( str.length()-2, 2 ) == QString("\r\n")) )
  {
    myLog()<<QString( replyWifi );
    myLog()<<"Reply complete";
    replyCompleteWifi = true;
    replyDSP = replyWifi;
    replyWifi.clear();
    emit haveReplyWifi();
  }
}

//==============================================================================
/*! Wait for reply of DSP via WiFi.
 *
 */
bool CFreeDspAurora::waitForReplyWifi( int msec )
{
  QEventLoop loopWaitForReply;
  QTimer timerWait;
  timerWait.setSingleShot( true );
  replyCompleteWifi = false;
  connect( this, SIGNAL(haveReplyWifi()), &loopWaitForReply, SLOT(quit()) );
  connect( &timerWait, SIGNAL(timeout()), &loopWaitForReply, SLOT(quit()) );
  timerWait.start( msec );
  loopWaitForReply.exec();
  disconnect( this, SIGNAL(haveReplyWifi()), &loopWaitForReply, SLOT(quit()) );
  disconnect( &timerWait, SIGNAL(timeout()), &loopWaitForReply, SLOT(quit()) );
  return replyCompleteWifi;
}

//==============================================================================
/*! Sends a request to the current DSP.
 *  \param request Contains the reques
 */
bool CFreeDspAurora::writeRequestWifi( QByteArray& request )
{
  return writeRequestWifi( request, getIpAddressWifi() );
}

//==============================================================================
/*! Sends a request to a DSP identified by an ip address.
 *  \param request Contains the request.
 *  \param host Ip address of host.
 */
bool CFreeDspAurora::writeRequestWifi( QByteArray& request, QString host )
{
  tcpSocket->abort();
  tcpSocket->connectToHost( host, portHostWifi );

  QEventLoop loopConnect;
  connect( tcpSocket, SIGNAL(connected()), &loopConnect, SLOT(quit()) );
  QTimer::singleShot( TIMEOUT_WIFI, &loopConnect, SLOT(quit()) );
  loopConnect.exec();

  if( tcpSocket->state() == QTcpSocket::ConnectedState )
  {
    replyWifi.clear();
    myLog()<<QString( request );
    tcpSocket->write( request );
    return true;
  }
  else
  {
    myLog()<<"[ERROR] CFreeDspAurora::writeRequestWifi() could not connect to DSP.";
    return false;
  }
}

//==============================================================================
/*! Request the DSP firmware.
 *
 * \param firmware Firmware data.
 * \param progress Pointer to progress bar.
 */
bool CFreeDspAurora::requestDspFirmwareWifi( QByteArray& firmware, QProgressBar* progress )
{
  myLog()<<"---------------------------------------------------------------";
  myLog()<<"requestDspFirmwareWifi";

  QString wifiIpHost = getIpAddressWifi();

  uint32_t totalBytes = 0;

  QString requestString = QString("GET /sizedspfw HTTP/1.1\r\n")
                        + QString( "Host: ") + wifiIpHost + QString("\r\n")
                        + QString("\r\n");
  QByteArray request;
  request.append( requestString );

  writeRequestWifi( request );

  if( !waitForReplyWifi() )
  {
    myLog()<<"Could not receive the size of the DSP firmware";
    QMessageBox::critical( this, tr("Error"), tr("Uuups, could not receive the size of DSP firmware. Please double check everything and try again."), QMessageBox::Ok ); 
    return false;
  }
  else
  {
    myLog()<<QString( replyDSP );
    QStringList listReply = QString( replyDSP ).split( QRegExp("\\s+") );
    totalBytes = listReply.at(4).toUInt();
    
    if( totalBytes > 0 )
    {
      requestString = QString("GET /dspfw HTTP/1.1\r\nHost: ")
                    + wifiIpHost
                    + QString("\r\n\r\n");
      request.clear();
      request.append( requestString );
      ptrProgressBar = progress;
      writeRequestWifi( request );
      if( !waitForReplyWifi(TIMEOUT_WIFI) )
      {
        myLog()<<"Could not receive the DSP firmware";
        QMessageBox::critical( this, tr("Error"), tr("Uuups, could not receive the DSP firmware. Please double check everything and try again."), QMessageBox::Ok ); 
        ptrProgressBar = nullptr;
        return false;
      }
      else
      {
        listReply = QString( replyDSP ).split( QRegExp("\\s+") );
        myLog()<<"Received dspfw";
        QString str = listReply.at(4);
        int offset = 0;
        ptrProgressBar = nullptr;
        
        while( offset < str.length() )
        {
          bool ok;
          int8_t val = str.mid( offset, 2 ).toUInt( &ok, 16 );
          firmware.append( val );
          offset += 2;
        }
      }
    }
    else
    {
      myLog()<<"DSP says: There is no plugin installed";
      QMessageBox::information( this, tr("Information"), tr("DSP says: There is no plugin installed."), QMessageBox::Ok ); 
      return false;
    }
  }

  myLog()<<"Done";
  myLog()<<"Received: "<<firmware.size()<<"/"<<totalBytes;

  if( static_cast<uint32_t>(firmware.size()) < totalBytes )
  {
    myLog()<<"Could not receive all bytes of the firmware";
    QMessageBox::critical( this, tr("Error"), tr("Uuups, could not receive all bytes of the firmware. Please double check all connections and reset all devices and try again."), QMessageBox::Ok ); 
    return false;
  }

  return true;

}

//==============================================================================
/*! Sends the SSID and password for the Wifi network to DSP and stores it nonvolatile.
 *
 * \param ssid New SSID
 * \parma password New password
 */
bool CFreeDspAurora::storeSettingsWifi( QString ssid, QString password )
{
  myLog()<<"---------------------------------------------------------------";
  myLog()<<"storeSsidWifi";

  QString wifiIpHost = getIpAddressWifi();
  ssidWifi = ssid;

  QString content = QString("SSID=") + ssid + QString("&")
                  + QString("Password=") + password;

  QString requestString = QString("POST /wificonfig HTTP/1.1\r\n")
                        + QString("Host: ") + wifiIpHost + QString("\r\n")
                        + QString("Content-type:text/plain\r\n")
                        + QString("Content-length: ") +  QString::number( content.size() ) + QString("\r\n")
                        + QString("\r\n")
                        + content
                        + QString("\r\n");
  QByteArray request;
  request.append( requestString );  
  
  writeRequestWifi( request );

  if( !waitForReplyWifi() )
    return false;
  else
  {
    myLog()<<QString( replyDSP );
    QStringList listReply = QString( replyDSP ).split( QRegExp("\\s+") );
    if( listReply.at(4) == "CONNECTED" )
    {
      myLog()<<"DSP is now connected to local WiFi network";
      QMessageBox::information( this, tr("Information"), tr("Your DSP is now connected to local WiFi network."), QMessageBox::Ok ); 
      return true;
    }
    else
    {
      myLog()<<"DSP cannot connect to local WiFi network";
      QMessageBox::critical( this, tr("Error"), tr("Your DSP cannot connect to local WiFi network. Please double-check SSID and password."), QMessageBox::Ok ); 
      return false;
    }
  }
}

//==============================================================================
/*! Sends the PID to DSP and stores it nonvolatile.
 *
 * \param pid New PID
 */
bool CFreeDspAurora::storePidWifi( uint8_t pid )
{
  myLog()<<"---------------------------------------------------------------";
  myLog()<<"storePidWifi";

  QString wifiIpHost = getIpAddressWifi();

  QByteArray content;
  content.append( static_cast<char>(pid) );

  QString requestString = QString("POST /pid HTTP/1.1\r\n")
                        + QString("Host: ") + wifiIpHost + QString("\r\n")
                        + QString("Content-type:text/plain\r\n")
                        + QString("Content-length: ") +  QString::number( content.size()*2 ) + QString("\r\n")
                        + QString("\r\n")
                        + content.toHex()
                        + QString("\r\n");
  QByteArray request;
  request.append( requestString );  
  
  writeRequestWifi( request );

  if( !waitForReplyWifi() )
    return false;
  else
  {
    myLog()<<QString( replyDSP );
    QStringList listReply = QString( replyDSP ).split( QRegExp("\\s+") );
    if( listReply.at(4) == "ACK" )
    {
      return true;
    }
    else
    {
      myLog()<<"Could not store the plugin id";
      QMessageBox::critical( this, tr("Error"), tr("Could not store the plugin id. Please double-check everything and try again."), QMessageBox::Ok ); 
      return false;
    }
  }
}

//==============================================================================
/*! Send a ping to the DSP to see wether it is there.
 *
 */
bool CFreeDspAurora::pingWifi( void )
{
  myLog()<<"---------------------------------------------------------------";
  myLog()<<"pingWifi";

  QString wifiIpHost = getIpAddressWifi();

  QString requestString = QString("GET /ping HTTP/1.1\r\n")
                        + QString("Host: freeDSP-aurora\r\n")
                        + QString("\r\n\r\n");
  QByteArray request;
  request.append( requestString );
  writeRequestWifi( request, "freeDSP-aurora" );

  if( !waitForReplyWifi() )
  {
    myLog()<<"Could not ping the DSP";
    QMessageBox::critical( this, tr("Error"), tr("Could not ping the DSP. Please double check everything and try again."), QMessageBox::Ok ); 
    return false;
  }
  else
  {
    myLog()<<QString( replyDSP );
    QStringList listReply = QString( replyDSP ).split( QRegExp("\\s+") );
    ipAddressLocal = listReply.at(4);
  }

  return true;
}

//==============================================================================
/*!
 */
void CFreeDspAurora::disconnectedWifi( void )
{
  myLog()<<"Disconnected from server";
}

//==============================================================================
/*!
 */
void CFreeDspAurora::bytesWrittenWifi( qint64  )
{
  //QString outString = QString::number(bytes) + " bytes writen.";
  //myLog()<<outString;
}

//==============================================================================
/*!
 */
void CFreeDspAurora::errorWifi( QAbstractSocket::SocketError )
{
  QString errorStr = tcpSocket->errorString();
  myLog()<<"An error occured :"<<errorStr;
}

//==============================================================================
/*!
 */
void CFreeDspAurora::hostFoundWifi( void )
{
  myLog()<<"CFreeDspAurora::hostFoundWifi()";
}

//==============================================================================
/*! Select preset on DSP
 *
 * \param presetid New preset id.
 */
bool CFreeDspAurora::selectPresetWifi( int presetid )
{
  myLog()<<"---------------------------------------------------------------";
  myLog()<<"selectPresetWifi";

  if( isConnected )
  {
    QString wifiIpHost = getIpAddressWifi();

    QByteArray content;
    content.append( static_cast<char>(presetid) );

    QString requestString = QString("POST /preset HTTP/1.1\r\n")
                          + QString("Host: ") + wifiIpHost + QString("\r\n")
                          + QString("Content-type:text/plain\r\n")
                          + QString("Content-length: ") +  QString::number( content.size()*2 ) + QString("\r\n")
                          + QString("\r\n")
                          + content.toHex()
                          + QString("\r\n");
    QByteArray request;
    request.append( requestString );  
    
    writeRequestWifi( request );

    if( !waitForReplyWifi() )
      return false;
    else
    {
      myLog()<<QString( replyDSP );
      QStringList listReply = QString( replyDSP ).split( QRegExp("\\s+") );
      if( listReply.at(4) == "ACK" )
      {
        return true;
      }
      else
      {
        myLog()<<"Could not select the preset";
        QMessageBox::critical( this, tr("Error"), tr("Could not select the preset. Please double-check everything and try again."), QMessageBox::Ok ); 
        return false;
      }
    }
  }
  else
  {
    myLog()<<"Not connected to DSP.";
    return false;
  }
}

//==============================================================================
/*! Stores the current selected preset as default.
 *
 */
bool CFreeDspAurora::storePresetSelection( void )
{
  myLog()<<"---------------------------------------------------------------";
  myLog()<<"storePresetSelection";

  QString wifiIpHost = getIpAddressWifi();

  QString requestString = QString("POST /savepreset HTTP/1.1\r\n")
                        + QString("Host: ") + wifiIpHost + QString("\r\n")
                        + QString("Content-type:text/plain\r\n")
                        + QString("Content-length: 0\r\n")
                        + QString("\r\n")
                        + QString("\r\n");
  QByteArray request;
  request.append( requestString );  
  
  writeRequestWifi( request );

  if( !waitForReplyWifi() )
    return false;
  else
  {
    myLog()<<QString( replyDSP );
    QStringList listReply = QString( replyDSP ).split( QRegExp("\\s+") );
    if( listReply.at(4) == "ACK" )
    {
      return true;
    }
    else
    {
      myLog()<<"Could not save the preset selection";
      QMessageBox::critical( this, tr("Error"), tr("Could not save the preset selection. Please double-check everything and try again."), QMessageBox::Ok ); 
      return false;
    }
  }
}
