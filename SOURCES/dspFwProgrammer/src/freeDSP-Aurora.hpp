#ifndef SIGMADSP_HPP
#define SIGMADSP_HPP

#include <QSerialPort>

class CFreeDspAurora
{
private:
  typedef char byte;
  
  enum
  {
    RESET  = 0x01,
    NEWFW  = 0x02,
    VERIFY = 0x03
  };

public:
  CFreeDspAurora();

  bool writeFirmwareToESP32viaBluetooth( const QString& hexfilename );

  bool verifyFirmwareESP32viaBluetooth( const QString& hexfilename );

private:
  bool sendByteSecured( char* txbyte );
  bool sendByteSecured( byte txbyte );

private:
  QSerialPort serial;

};

#endif // SIGMADSP_HPP
