#ifndef SIGMADSP_HPP
#define SIGMADSP_HPP

#include <cstdint>

#include <QWidget>
#include <QEventLoop>
#include <QTcpSocket>
#include <QByteArray>
#include <QProcess>
#include <QProgressBar>

#define NUMPRESETS (4)

class CFreeDspAurora : public QWidget
{
  Q_OBJECT

public:
  enum
  {
    ACCESS_POINT,
    LOCAL_WIFI
  };

  enum tdspluginid
  {
    PLUGIN_8CHANNELS    = 0x01,
    PLUGIN_HOMECINEMA71 = 0x02,
    PLUGIN_4FIRS        = 0x03
  };

private:
  typedef uint8_t byte;

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

  //============================================================================
  /*!
   */
  bool sendParameterWifi( QByteArray content );

  //============================================================================
  /*!
   */
  QByteArray makeParameterForWifi( uint16_t reg, float val );

  //============================================================================
  /*! Prepares a content packet for a parameter
   *
   */
  QByteArray makeParameterForWifi( uint16_t reg, int32_t val );

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
  /*! Requests index of current selected preset
   *
   */
  int32_t requestCurrentPresetWifi( void );

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

  //============================================================================
  /*! Starts the transfer of a dsp parameter block.
   *
   * \param content Data block of dsp parameter.
   */
  bool sendDspParameterWifi( QByteArray content );

  //============================================================================
  /*! Finishes the transfer of dsp parameter file.
   *
   */
  bool finishDspParameterWifi( uint32_t totalTransmittedBytes );

  //============================================================================
  /*! Request the DSP firmware.
   *
   * \param content Firmware data.
   * \param progress Pointer to progress dialog
   */
  bool requestDspFirmwareWifi( QByteArray& content, QProgressBar* progress = nullptr );

  //============================================================================
  /*! Sends the SSID and password for the Wifi network to DSP and stores it nonvolatile.
   *
   * \param ssid New SSID
   * \parma password New password
   */
  bool storeSettingsWifi( QString ssid, QString password );

  //============================================================================
  /*! Sends the PID to DSP and stores it nonvolatile.
   *
   * \param pid New PID
   */
  bool storePidWifi( uint8_t pid );

  //============================================================================
  /*! Stores the current selected preset as default.
   *
   */
  bool storePresetSelection( void );

  //============================================================================
  /*! Returns the currently used ip address for communication with DSP.
   */
  QString getIpAddressWifi( void )
  {
    if( connectionType == ACCESS_POINT )
      return ipAddressAP;
    else
      return ipAddressLocal;
  }

  //============================================================================
  /*! Returns the ip address in local wifi network.
   */
  QString getIpAddressLocalWifi( void )
  {
    return ipAddressLocal;
  }

  //============================================================================
  /*! Sets the currently used ip address for communication with DSP.
   */
  void setIpAddressWifi( QString ip )
  {
    ipAddressLocal = ip;
  }

  //============================================================================
  /*! Returns wether the DSP is connected via access point mode or local WiFi.
   */
  int getConnectionTypeWifi( void ) { return connectionType; }

  //============================================================================
  /*!
   */
  void setConnectionTypeWifi( int type ) { connectionType = type; }

  //============================================================================
  /*! Returns the ssid of local wifi network.
   */
  QString getSsidWifi( void )
  {
    return ssidWifi;
  }

  //============================================================================
  /*! Sets the ssid of local wifi network.
   */
  void setSsidWifi( QString ssid )
  {
    ssidWifi = ssid;
  }

  //============================================================================
  /*! Send a ping to the DSP to see wether it is there.
   *
   */
  bool pingWifi( void );

  //============================================================================
  /*! Disconnect from DSP.
   */
  void disconnectWifi( void )
  {
    tcpSocket->disconnectFromHost();
  }

  //============================================================================
  /*! Select preset on DSP
   *
   * \param presetid New preset id.
   */
  bool selectPresetWifi( int presetid );
  
private:
  //============================================================================
  /*!
   */
  bool waitForReplyWifi( int msec = 5000 );

  //============================================================================
  /*! Sends a request to the current DSP.
   *  \param request Contains the reques
   */
  bool writeRequestWifi( QByteArray& request );

  //============================================================================
  /*! Sends a request to a DSP identified by an ip address.
   *  \param request Contains the request.
   *  \param host Ip address of host.
   */
  bool writeRequestWifi( QByteArray& request, QString host );

private slots:
  void bytesWrittenWifi( qint64 bytes );
  void disconnectedWifi( void );
  void errorWifi( QAbstractSocket::SocketError socketError );
  void hostFoundWifi( void );
  void readyReadWifi( void );

signals:
  void haveReplyWifi( void );

public:
  
private: 
  QTcpSocket* tcpSocket;
  //QEventLoop loopWaitForResponseWiFi;
  QByteArray replyWifi;
  QByteArray replyDSP;
  QString ipAddressAP;
  QString ipAddressLocal;
  quint16 portHostWifi;
  int connectionType;
  bool replyCompleteWifi;
  QProgressBar* ptrProgressBar;
  QString ssidWifi;
  bool isConnected = false;

};

#endif // SIGMADSP_HPP
