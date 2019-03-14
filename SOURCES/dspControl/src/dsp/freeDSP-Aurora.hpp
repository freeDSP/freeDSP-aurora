#ifndef SIGMADSP_HPP
#define SIGMADSP_HPP

#include <cstdint>

#include <QWidget>

#if !defined( __IOS__ )
#include <QSerialPort>
#endif

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
  explicit CFreeDspAurora( QWidget* parent = nullptr );

  ~CFreeDspAurora( void );

  bool writeFirmwareToESP32viaBluetooth( const QString& hexfilename );

  bool verifyFirmwareESP32viaBluetooth( const QString& hexfilename );

  bool open( const QString portname );

  void close( void );

  bool sendParameter( uint16_t reg, float val );
  bool sendParameter( uint16_t reg, uint32_t val );

  //bool sendParameterWifi( uint16_t reg, double val );
  //bool sendParameterWifi( uint16_t reg, uint32_t val );
  bool sendParameterWifi( QByteArray content );
  QByteArray makeParameterForWifi( uint16_t reg, double val );

  bool storeRegAddr( uint16_t reg );
  bool storeValue( float val );
  bool storeValue( uint32_t val );

  bool beginStoreParams( uint32_t numbytes );

private:
  bool sendByteSecured( char* txbyte );
  bool sendByteSecured( byte txbyte );

private:
#if !defined( __IOS__ )
  QSerialPort serialBT;
#endif
  bool isOpen = false;

};

#endif // SIGMADSP_HPP
