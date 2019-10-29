//#ifndef SIGMADSP_HPP
//#define SIGMADSP_HPP
#pragma once

#include <cstdint>
#include <cmath>

#include <QWidget>
#include <QEventLoop>
#include <QTcpSocket>
#include <QByteArray>
#include <QProcess>
#include <QProgressBar>

#include "../../../ESP32/aurora/ak4458.h"

#define NUMPRESETS (4)

// DSP address on I2C bus
#define DSP_ADDR           (0x70)
// ADC address on I2C bus
#define AK5558_I2C_ADDR    (0x22)
// DAC address on I2C bus
#define AK4458_I2C_ADDR    (0x20)
// S/P-DIF-Mux on AddOnB
#define ADDONB_SPDIFMUX_ADDR (0x82)

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
    PLUGIN_8CHANNELS        = 0x01,
    PLUGIN_HOMECINEMA71     = 0x02,
    PLUGIN_4FIRS            = 0x03,
    PLUGIN_8CHANNELS_USB    = 0x04,
    PLUGIN_HOMECINEMA71_USB = 0x05
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
  /*! Requests the AddOn-Id of the board (if there is one installed).
   */
  bool requestAddOnIdWifi( void );

  //============================================================================
  /*! Requests the DSP firmware.
   *
   * \param content Firmware data.
   * \param progress Pointer to progress dialog
   */
  bool requestDspFirmwareWifi( QByteArray& content, QProgressBar* progress = nullptr );

  //============================================================================
  /*! Requests the firmware version of the board.
   */
  bool requestFirmwareVersionWifi( bool showmessage = true );

  //============================================================================
  /*! Requests the PID of current installed DSP-Plugin
   *
   */
  uint32_t requestPidWifi( void );

  //============================================================================
  /*! Request the user parameter file.
   *
   */
  bool requestUserParameterWifi( QByteArray& userparams );

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
  /*! Sends the AddOn-Id to DSP and stores it nonvolatile.
   *
   * \param aid New AddOn-Id
   */
  bool storeAddOnIdWifi( quint32 aid );

  //============================================================================
  /*! Returns the AddOn-Id of the connected board.
   */
  quint32 getAddOnId( void )
  {
    return addon;
  }

  //============================================================================
  /*! Returns the firmware version of the connected board.
   */
  QString getFirmwareVersion( void )
  {
    return versionstr;
  }

  uint32_t getFwVersion( void )
  {
    return fwVersion;
  }

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
  /*! Returns the ip address of access point.
   */
  QString getIpAddressAP( void )
  {
    return ipAddressAP;
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

  //============================================================================
  /*! Sets the mute address for the DSP
   *
   * \param addr Mute address.
   */
  void setMuteAddr( uint16_t addr )
  {
    addrMute = addr;
  }

  //============================================================================
  /*! Sets the master volume for the DSP in dB.
   *
   * \param vol Master volume.
   */
  void setMasterVolume( float vol )
  {
    masterVolume = vol;
  }

  //============================================================================
  /*! Returns the master volume for the DSP in dB.
   *
   * \return Master volume.
   */
  float getMasterVolume( void )
  {
    return masterVolume;
  }

  //============================================================================
  /*! Makes the mute sequence
   */
  QByteArray muteSequence( void )
  {
    QByteArray content;
    content.append( makeParameterForWifi( addrMute, 0.f ) ); 
    content.append( makeParameterForWifi( 0x0000, 0 ) );
    content.append( makeParameterForWifi( 0x0000, 0 ) );
    content.append( makeParameterForWifi( 0x0000, 0 ) );
    content.append( makeParameterForWifi( 0x0000, 0 ) );

    return content;
  }


  //============================================================================
  /*! Makes the unmute sequence
   */
  QByteArray unmuteSequence( void )
  {
    qDebug()<<"Unmute"<<masterVolume;
    QByteArray content;
    content.append( makeParameterForWifi( 0x0000, 0 ) );
    content.append( makeParameterForWifi( 0x0000, 0 ) );
    content.append( makeParameterForWifi( 0x0000, 0 ) );
    content.append( makeParameterForWifi( 0x0000, 0 ) );
    content.append( makeParameterForWifi( addrMute, static_cast<float>(pow( 10.f, masterVolume/20.f )) ) );
    return content;
  }


  //============================================================================
  /*! Mutes the DSP outputs
   */
  void mute( void )
  {
    QByteArray content;
    content.append( muteSequence() );
    sendParameterWifi( content );
  }

  //============================================================================
  /*! Unmutes the DSP outputs
   */
  void unmute( void )
  {
    QByteArray content;
    content.append( unmuteSequence() );
    sendParameterWifi( content );
  }

  //============================================================================
  /*! Sends a pure i2c message to write to a slave on the i2c bus.
   *
   *  \param addr Address of i2c slave.
   *  \param reg Regsiter of i2c slave.
   *  \param data Data written to i2c slave.
   *  \return true if successful, else false.
   */
  bool writeI2C( const int8_t addr, const int8_t reg, const int8_t data );

  //============================================================================
  /*! Reads from a slave on the i2c bus.
   *
   *  \param addr Address of i2c slave.
   *  \param reg Regsiter of i2c slave.
   *  \param data Data from i2c slave.
   *  \return true if successful, else false.
   */
  bool readI2C( const int8_t addr, const int8_t reg, int8_t& data );

  //============================================================================
  /*! Sends the addon configuration to DSP.
   *
   *  \param str Configuration string.
   *  \return true if successful, else false.
   */
  bool sendAddOnConfig( QString str );

  //============================================================================
  /*! Requests the addon configuration from DSP.
   *
   *  \return true if successful, else false.
   */
  bool requestAddOnConfig( void );

  //============================================================================
  /*! Sets the connection status of DSP
   *
   *  \param state Connection status.
   */
  void setIsConnected( bool state )
  {
    isConnected = state;
  }

  //============================================================================
  /*! Returns the connection status of DSP
   *
   *  \return Connection status.
   */
  bool getIsConnected( void )
  {
    return isConnected;
  }

  //============================================================================
  /*! Sets the debug mode
   *
   *  \param state Debug mode.
   */
  void setDebugMode( bool state )
  {
    debugMode = state;
  }

  //============================================================================
  /*! Returns the addon configuration
   *
   *  \return Addon Configuration.
   */
  QString getAddOnConfig( void )
  {
    return configAddOn;
  }

  //============================================================================
  /*! Mutes the DAC outputs
   */
  bool muteDAC( void )
  {
    return writeI2C( AK4458_I2C_ADDR, AK4458_CONTROL2, 0b00100011 );
  }

  //============================================================================
  /*! Unmutes the DAC outputs
   */
  bool unmuteDAC( void )
  {
    return writeI2C( AK4458_I2C_ADDR, AK4458_CONTROL2, 0b00100010 );
  }

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
  QString versionstr = "0.0.0";
  uint32_t fwVersion = 0;
  quint32 addon;
  uint16_t addrMute;
  float masterVolume;
  bool debugMode = false;
  QString configAddOn;

};

//#endif // SIGMADSP_HPP
