#ifndef SIGMADSP_HPP
#define SIGMADSP_HPP

#include <cstdint>

#include <QWidget>
#include <QEventLoop>
#include <QTcpSocket>
#include <QByteArray>

class CFreeDspAurora : public QWidget
{
  Q_OBJECT

private:
  typedef char byte;

  enum
  {
    RESET      = 0x01,
    NEWFW      = 0x02,
    VERIFY     = 0x03,
    PARAM      = 0x04,
    SAVEPARAMS = 0x05
  };

public:
  //============================================================================
  /*! Constructor
   *
   */
  explicit CFreeDspAurora( QWidget* parent = nullptr );

  //============================================================================
  /*! Destructor
   *
   */
  ~CFreeDspAurora( void );

  bool open( const QString portname );

  void close( void );

  bool sendParameter( uint16_t reg, float val );
  bool sendParameter( uint16_t reg, uint32_t val );

  bool sendParameterWifi( QByteArray content );
  QByteArray makeParameterForWifi( uint16_t reg, double val );

  bool storeRegAddr( uint16_t reg );
  bool storeValue( float val );
  bool storeValue( uint32_t val );

  //bool beginStoreParams( uint32_t numbytes );

  //============================================================================
  /*! Starts the transfer of a new dsp firmware.
   *
   *  \param content First block of firmware.
   */
  bool sendDspFirmwareWifi( QByteArray content );

  //============================================================================
  /*! Finishes the transfer of a new dsp firmware.
   *
   *  \param totalTransmittedBytes Number of transmitted bytes.
   */
  bool finishDspFirmwareWifi( uint32_t totalTransmittedBytes );

  //============================================================================
  /*! Waits for an ACK from WiFi connection.
   *
   */
  bool waitForAckWifi( void );

  //============================================================================
  /*! Requests the PID of current installed DSP-Plugin
   *
   */
  uint32_t requestPidWifi( void );

  //============================================================================
  /*! Starts the transfer of a user data block.
   *
   * \param content Data block of user data.
   */
  bool sendUserParameterWifi( QByteArray content );

  //============================================================================
  /*! Finishes the transfer of user parameter file.
   *
   */
  bool finishUserParameterWifi( uint32_t totalTransmittedBytes );

  //============================================================================
  /*! Request the user parameter file.
   *
   */
  bool requestUserParameterWifi( QByteArray& userparams );

private:
  //bool sendByteSecured( char* txbyte );
  //bool sendByteSecured( byte txbyte );

  void waitForReplyWifi( void );

  //==============================================================================
  /*! 
   *
   */
  bool waitForResponseWifi( void );

  //==============================================================================
  /*!
   */
  void writeRequestWifi( QByteArray& request );

private slots:
  void readyReadWifi();

signals:
  void haveReplyWifi( void );

public:
  QTcpSocket* tcpSocket;

private:
//#if !defined( __IOS__ )
//  QSerialPort serialBT;
//#endif
  bool isOpen = false;
  
  QEventLoop loopWaitForResponseWiFi;
  QByteArray replyWifi;
  QByteArray replyDSP;

};

#endif // SIGMADSP_HPP
