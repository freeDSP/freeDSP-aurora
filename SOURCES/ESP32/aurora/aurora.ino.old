
#include <Wire.h>

#include "BluetoothSerial.h"
#include "SPIFFS.h"

#define I2C_SDA_PIN 16
#define I2C_SCL_PIN 4

#define FORMAT_SPIFFS_IF_FAILED true

#define DSP_ADDR (0x70>>1)

enum
{
  RESET      = 0x01,
  NEWFW      = 0x02,
  VERIFY     = 0x03,
  PARAM      = 0x04,
  SAVEPARAMS = 0x05
};

enum
{
  STATUS_IDLE,
  STATUS_WAITDATASIZE,
  STATUS_RECVFW,
  STATUS_VERIFY,
  STATUS_PARAM_NUMBYTES,
  STATUS_PARAM_REG,
  STATUS_PARAM_VALUE,
  STATUS_WAIT_NUMBYTES,
  STATUS_STORE_PARAMS,
  STATUS_RETURN_PARAMS
};

BluetoothSerial SerialBT;

int state;
int numBytes = 0;
int cntr = 0;
uint16_t dspRegister = 0;
uint32_t dspValueHex = 0;
float dspValue;

File fileDspProgram;
File fileDspParams;

void scan()
{
Serial.println(" Scanning I2C Addresses");
uint8_t cnt=0;
for(uint8_t i=0;i<128;i++){
  Wire.beginTransmission(i);
  uint8_t ec=Wire.endTransmission(true);
  if(ec==0){
    if(i<16)Serial.print('0');
    Serial.print(i,HEX);
    cnt++;
  }
  else Serial.print("..");
  Serial.print(' ');
  if ((i&0x0f)==0x0f)Serial.println();
  }
Serial.print("Scan Completed, ");
Serial.print(cnt);
Serial.println(" I2C Devices found.");
}

//==============================================================================
/*! Uploads the firmware from ESP32 SPI flash to DSP.
 */
void uploadDspFirmware( void )
{
  Serial.print( "Init dsp......" );

  fileDspProgram = SPIFFS.open( "/dspinit.hex" );

  uint32_t numBytesToRead = 0;

  if( fileDspProgram )
  {
    int file_size = fileDspProgram.size();

    cntr = 0;

    while( fileDspProgram.available() )
    {
      uint32_t byteRead = fileDspProgram.read();
      numBytesToRead = (numBytesToRead << 8) + byteRead;
      byteRead = fileDspProgram.read();
      numBytesToRead = (numBytesToRead << 8) + byteRead;
      byteRead = fileDspProgram.read();
      numBytesToRead = (numBytesToRead << 8) + byteRead;
      byteRead = fileDspProgram.read();
      numBytesToRead = (numBytesToRead << 8) + byteRead;

      cntr += 4;

      //Serial.print( "numBytesToRead " );
      //Serial.println( numBytesToRead, HEX );

      //------------------------------------------------------------------------
      //--- Send register address
      //------------------------------------------------------------------------
      Wire.beginTransmission( DSP_ADDR );

      //Serial.println( "Register" );
      byteRead = fileDspProgram.read();
      Wire.write( byteRead );
      //Serial.println( byteRead, HEX );
      byteRead = fileDspProgram.read();
      Wire.write( byteRead );
      //Serial.println( byteRead, HEX );

      cntr += 2;

      //Serial.println( "Value" );
      for( uint32_t n = 0; n < numBytesToRead - 2; n++ )
      {
        byteRead = fileDspProgram.read();
        Wire.write( byteRead );
        cntr++;
        //Serial.println( byteRead, HEX );
      }

      Wire.endTransmission( true );

    }

    fileDspProgram.close();

  }
  else
    Serial.println( "\n[ERROR] Failed to open file dspinit.hex" );
  Serial.print( "[ok]\n" );
  //Serial.print( "Read ");
  //Serial.print( cntr );
  //Serial.println( " bytes");
}

//==============================================================================
/*! Uploads the parameters from ESP32 SPI flash to DSP.
 */
void uploadDspParameter( void )
{
  Serial.print( "Loading dsp parameter......" );

  fileDspParams = SPIFFS.open( "/dspparam.hex" );

  //uint32_t numBytesToRead = 0;

  if( fileDspParams )
  {
    int file_size = fileDspParams.size();

    cntr = 0;

    while( fileDspParams.available() )
    {
      //------------------------------------------------------------------------
      //--- Send register address
      //------------------------------------------------------------------------
      Wire.beginTransmission( DSP_ADDR );

      Serial.println( "Register" );
      uint32_t byteRead = fileDspParams.read();
      Wire.write( byteRead );
      Serial.println( byteRead, HEX );
      byteRead = fileDspParams.read();
      Wire.write( byteRead );
      Serial.println( byteRead, HEX );
      cntr += 2;

      //------------------------------------------------------------------------
      //--- Send value
      //------------------------------------------------------------------------
      Serial.println( "Value" );
      for( uint32_t n = 0; n < 4; n++ )
      {
        byteRead = fileDspParams.read();
        Wire.write( byteRead );
        cntr++;
        Serial.println( byteRead, HEX );
      }

      Wire.endTransmission( true );

    }

    Serial.print( cntr );
    Serial.println( "Bytes" );

    fileDspParams.close();

  }
  else
    Serial.println( "\n[ERROR] Failed to open file dspinit.hex" );
  Serial.print( "[ok]\n" );
}

//==============================================================================
/*! Returns the parameter to host.
 */
void returnDspParameters( void )
{
  Serial.print( "Returning dsp parameter......" );

  fileDspParams = SPIFFS.open( "/dspparam.hex" );

  if( fileDspParams )
  {
    int file_size = fileDspParams.size();

    cntr = 0;

    //--------------------------------------------------------------------------
    //--- Send file size
    //--------------------------------------------------------------------------
    SerialBT.write( (file_size>>24) & 0xFF );
    SerialBT.write( (file_size>>16) & 0xFF );
    SerialBT.write( (file_size>>8) & 0xFF );
    SerialBT.write( file_size & 0xFF );

    Serial.print( "File size:" );
    Serial.println( file_size, HEX );

    while( fileDspParams.available() )
    {
      //------------------------------------------------------------------------
      //--- Send register address
      //------------------------------------------------------------------------
      Serial.println( "Register" );
      uint32_t byteRead = fileDspParams.read();
      SerialBT.write( byteRead );
      Serial.println( byteRead, HEX );
      byteRead = fileDspParams.read();
      SerialBT.write( byteRead );
      Serial.println( byteRead, HEX );
      cntr += 2;


      //------------------------------------------------------------------------
      //--- Send value
      //------------------------------------------------------------------------
      Serial.println( "Value" );
      for( uint32_t n = 0; n < 4; n++ )
      {
        byteRead = fileDspParams.read();
        SerialBT.write( byteRead );
        cntr++;
        Serial.println( byteRead, HEX );
      }
    }

    Serial.print( cntr );
    Serial.println( "Bytes" );

    fileDspParams.close();
  }
  else
    Serial.println( "\n[ERROR] Failed to open file dspinit.hex" );
  Serial.print( "[ok]\n" );
}

//==============================================================================
/*! Arduino Setup
 */
void setup()
{
  Wire.begin( I2C_SDA_PIN, I2C_SCL_PIN );
  Wire.setClock( 100000 );

  Serial.begin(115200);
  Serial.println( "aurora Debug" );

  if( !SPIFFS.begin(FORMAT_SPIFFS_IF_FAILED) )
  {
    Serial.println( "An Error has occurred while mounting SPIFFS" );
    return;
  }

/*
  File file = SPIFFS.open( "/test.txt", FILE_WRITE );

  if (!file) {
    Serial.println("There was an error opening the file for writing");
    return;
  }
  if (file.print("TEST")) {
    Serial.println("File was written");
  } else {
    Serial.println("File write failed");
  }

  file.close();
 */

  //----------------------------------------------------------------------------
  //--- Download program to DSP
  //----------------------------------------------------------------------------
  uploadDspFirmware();

  //----------------------------------------------------------------------------
  //--- Download user parameter to DSP
  //----------------------------------------------------------------------------
  uploadDspParameter();

/*
  Wire.beginTransmission( DSP_ADDR ); // Initialize the Tx buffer
  Wire.write(0xF0);
  Wire.write(0x00);
  Wire.endTransmission( true ); // Send the Tx buffer, but send a restart to keep connection alive

  Wire.requestFrom( DSP_ADDR, 2 ); // Read two bytes from slave
  while ( Wire.available() )
    Serial.println( Wire.read(), HEX );

  Wire.endTransmission( true );

  Wire.beginTransmission( DSP_ADDR ); // Initialize the Tx buffer
  Wire.write(0xF0);
  Wire.write(0x20);
  Wire.endTransmission( true ); // Send the Tx buffer, but send a restart to keep connection alive

  Wire.requestFrom( DSP_ADDR, 2 ); // Read two bytes from slave
  while ( Wire.available() )
    Serial.println( Wire.read(), HEX );

  Wire.endTransmission( true );
*/

  state = STATUS_IDLE;

  SerialBT.begin( "freedsp-aurora" );

}

void loop()
{
  int rxByte;


  if( state == STATUS_IDLE )
  {
    if( SerialBT.available() )
    {
      rxByte = SerialBT.read();
      if( rxByte == NEWFW )
      {
        Serial.println( "Receiving new image" );
        numBytes = 0;
        cntr = 0;
        state = STATUS_WAITDATASIZE;
      }
      else if( rxByte == VERIFY )
      {
        Serial.println( "Verifying DSP firmware" );
        state = STATUS_VERIFY;
      }
      else if( rxByte == PARAM )
      {
        Serial.println( "Receiving Parameter" );
        numBytes = 0;
        cntr = 0;
        state = STATUS_PARAM_REG;
      }
      else if( rxByte == SAVEPARAMS )
      {
        Serial.println( "Storing Parameters" );
        numBytes = 0;
        cntr = 0;
        state = STATUS_WAIT_NUMBYTES;
      }
      else if( rxByte == GETPARAMS )
      {
        Serial.println( "Returning Parameters" );
        numBytes = 0;
        cntr = 0;
        status = STATUS_RETURN_PARAMS;
      }
      else
        Serial.println( "Unkown command" );
      SerialBT.write( rxByte );
    }
  }

  else if( state == STATUS_WAITDATASIZE )
  {
    if( SerialBT.available() )
    {
      rxByte = SerialBT.read();
      numBytes = (numBytes << 8) + rxByte;
      cntr++;

      if( cntr == 4 )
      {
        Serial.print( numBytes );
        Serial.println( "bytes" );

        if( SPIFFS.exists( "/dspinit.hex" ) )
        {
          if( SPIFFS.remove( "/dspinit.hex" ) )
            Serial.println( "dspinit.hex deleted" );
        }

        fileDspProgram = SPIFFS.open( "/dspinit.hex", FILE_APPEND );
        if( !fileDspProgram )
          Serial.println( "[ERROR] Failed to open file dspinit.hex" );
        cntr = 0;
        state = STATUS_RECVFW;
      }

      SerialBT.write( rxByte );
    }

  }

  else if( state == STATUS_RECVFW )
  {
    if( SerialBT.available() )
    {
      rxByte = SerialBT.read();

      size_t len = fileDspProgram.write( rxByte );
      if( len != 1 )
        Serial.println( "Error writing to file dspinit.hex" );
      else
      {
        Serial.print( cntr+1 );
        Serial.print( " : " );
        Serial.print( rxByte, HEX );
        Serial.print( "\n" );
      }

      cntr++;
      if( cntr == numBytes )
      {
        fileDspProgram.flush();
        fileDspProgram.close();
        Serial.println( "Closed dspinit.hex" );

        cntr = 0;
        state = STATUS_IDLE;
      }
      SerialBT.write( rxByte );
    }
  }

  else if( state == STATUS_VERIFY )
  {
    fileDspProgram = SPIFFS.open( "/dspinit.hex" );

    if( fileDspProgram )
    {
      int file_size = fileDspProgram.size();
      Serial.print( "File size: " );
      Serial.println( file_size );

      for( int ii = 0; ii < file_size; ii++ )
      {
        uint8_t nextByte = fileDspProgram.read();

        Serial.println( nextByte, HEX );
      }

      fileDspProgram.close();

    }
    else
      Serial.println( "[ERROR] Failed to open file dspinit.hex" );

    state = STATUS_IDLE;
  }

  else if( state == STATUS_PARAM_NUMBYTES )
  {
    if( SerialBT.available() )
    {
      rxByte = SerialBT.read();
      numBytes = (numBytes << 8) + rxByte;
      cntr++;

      if( cntr == 4 )
      {
        Serial.print( numBytes );
        Serial.println( "bytes" );
        cntr = 0;
        state = STATUS_PARAM_REG;
      }

      SerialBT.write( rxByte );
    }
  }

  else if( state == STATUS_PARAM_REG )
  {
    if( SerialBT.available() )
    {
      rxByte = SerialBT.read();
      dspRegister = (dspRegister << 8) + rxByte;
      cntr++;

      if( cntr == 2 )
      {
        Serial.println( dspRegister );
        cntr = 0;
        dspValueHex = 0;
        state = STATUS_PARAM_VALUE;
      }

      SerialBT.write( rxByte );
    }
  }

  //----------------------------------------------------------------------------
  //--- Get the register value
  //----------------------------------------------------------------------------
  else if( state == STATUS_PARAM_VALUE )
  {
    if( SerialBT.available() )
    {
      rxByte = SerialBT.read();
      dspValueHex = (dspValueHex << 8) + rxByte;
      cntr++;

      if( cntr == 4 )
      {
        memcpy( &dspValue, &dspValueHex, sizeof(float) );
        Serial.println( dspValue );
        cntr = 0;
        dspValueHex = 0;
        state = STATUS_IDLE;
      }

      SerialBT.write( rxByte );
    }
  }

  //----------------------------------------------------------------------------
  //--- Get the length of dspparams.hex in bytes
  //----------------------------------------------------------------------------
  else if( state == STATUS_WAIT_NUMBYTES )
  {
    if( SerialBT.available() )
    {
      rxByte = SerialBT.read();
      numBytes = (numBytes << 8) + rxByte;
      cntr++;

      if( cntr == 4 )
      {
        Serial.print( numBytes );
        Serial.println( "bytes" );

        if( SPIFFS.exists( "/dspparam.hex" ) )
        {
          if( SPIFFS.remove( "/dspparam.hex" ) )
            Serial.println( "dspparams.hex deleted" );
        }

        fileDspParams = SPIFFS.open( "/dspparam.hex", FILE_APPEND );
        if( !fileDspParams )
          Serial.println( "[ERROR] Failed to open file dspparam.hex" );

        cntr = 0;
        state = STATUS_STORE_PARAMS;
      }

      SerialBT.write( rxByte );
    }
  }

  //----------------------------------------------------------------------------
  //--- Get the file dspparams.hex byte by byte
  //----------------------------------------------------------------------------
  else if( state == STATUS_STORE_PARAMS )
  {
    if( SerialBT.available() )
    {
      rxByte = SerialBT.read();

      fileDspParams.write( rxByte );
      Serial.println( rxByte, HEX );

      cntr++;
      if( cntr == numBytes )
      {
        fileDspParams.flush();
        fileDspParams.close();
        Serial.println( "Closed dspparam.hex" );
        cntr = 0;
        state = STATUS_IDLE;
      }

      SerialBT.write( rxByte );
    }
  }

   //Wire.beginTransmission( DSP_ADDR );
   //Wire.endTransmission();

}
