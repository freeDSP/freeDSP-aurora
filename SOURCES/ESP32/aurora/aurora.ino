
#include <Wire.h>
#include <WiFi.h>
#include <ArduinoJson.h>
//#include "BluetoothSerial.h"
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

enum twifistatus
{
  STATE_WIFI_IDLE,
  STATE_WIFI_PUTPARAM,
  STATE_WIFI_DSPFW,
  STATE_WIFI_RECEIVE_USERPARAM,

  STATE_WIFI_RECEIVE_SINGLEPARAM
};

struct tSettings
{
  byte pid;
};

tSettings Settings;

//BluetoothSerial SerialBT;

int state;
int numBytes = 0;
//int cntr = 0;
uint16_t dspRegister = 0;
uint32_t dspValueHex = 0;
float dspValue;

File fileDspProgram;
File fileDspParams;

File fileUserParams;

WiFiClient client;
WiFiServer server( 8088 );

twifistatus wifiStatus = STATE_WIFI_IDLE;
int cntrPackets = 0;
uint32_t totalBytesReceived;

//==============================================================================
/*! 
 */
String byte2string( byte val )
{
  String str( "0x" );
  if( val < 0x10 )
    str += "0";
  str += String( val, HEX );  
  return str;
}

String byte2string2( byte val )
{
  String str;
  if( val < 0x10 )
    str += "0";
  str += String( val, HEX );  
  return str;
}

//==============================================================================
/*! 
 */
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

  fileDspProgram = SPIFFS.open( "/dspfw.hex" );

  uint32_t numBytesToRead = 0;

  if( fileDspProgram )
  {

    //int file_size = fileDspProgram.size();
    Serial.print( "File size:");
    Serial.println( fileDspProgram.size() );

    size_t len = fileDspProgram.size();

    int cntr = 0;

    while( cntr < len )
    {
      //Serial.print( "Line: ");
      //Serial.println(cntr);
      uint8_t byteRead;
      fileDspProgram.read( &byteRead, 1 );
      numBytesToRead = (numBytesToRead << 8) + (uint32_t)byteRead;
      fileDspProgram.read( &byteRead, 1 );
      numBytesToRead = (numBytesToRead << 8) + (uint32_t)byteRead;
      fileDspProgram.read( &byteRead, 1 );
      numBytesToRead = (numBytesToRead << 8) + (uint32_t)byteRead;
      fileDspProgram.read( &byteRead, 1 );
      numBytesToRead = (numBytesToRead << 8) + (uint32_t)byteRead;

      cntr += 4;
      
      //Serial.print( "numBytesToRead " );
      //Serial.println( numBytesToRead, HEX );

      //------------------------------------------------------------------------
      //--- Send register address
      //------------------------------------------------------------------------
      Wire.beginTransmission( DSP_ADDR );

      fileDspProgram.read( &byteRead, 1 );
      cntr++;
      Wire.write( byteRead );
      //Serial.println( byteRead, HEX );

      fileDspProgram.read( &byteRead, 1 );
      cntr++;
      Wire.write( byteRead );
      //Serial.println( byteRead, HEX );


      //Serial.println( "Value" );
      for( uint32_t n = 2; n < numBytesToRead; n++ )
      {
        fileDspProgram.read( &byteRead, 1 );
        cntr++;
        Wire.write( byteRead );
        //Serial.println( byteRead, HEX );
      }

      Wire.endTransmission( true );

      Serial.print(".");
      
      //Serial.println( cntr );
     
    }

    fileDspProgram.close();

  }
  else
    Serial.println( "\n[ERROR] Failed to open file dspfw.hex" );
  Serial.print( "[ok]\n" );
}

#if 0
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
#endif

//==============================================================================
/*! Arduino Setup
 */
void setup()
{
  Wire.begin( I2C_SDA_PIN, I2C_SCL_PIN );
  Wire.setClock( 100000 );

  Serial.begin(115200);
  Serial.println( "aurora Debug" );

  if( !SPIFFS.begin( FORMAT_SPIFFS_IF_FAILED ) )
  {
    Serial.println( "An Error has occurred while mounting SPIFFS" );
    return;
  }
  Serial.print( "Free disk space: " );
  Serial.print( (SPIFFS.totalBytes() - SPIFFS.usedBytes()) / 1024 );
  Serial.println( "KiB" );

  //----------------------------------------------------------------------------
  //--- Configure ESP for WiFi access
  //----------------------------------------------------------------------------
  WiFi.mode( WIFI_AP_STA );
  // Start access point
  WiFi.softAP( "freeDSP-aurora" );
  delay(100);
  //wait for SYSTEM_EVENT_AP_START
  if( !WiFi.softAPConfig( IPAddress(192, 168, 5, 1), IPAddress(192, 168, 5, 1), IPAddress(255, 255, 255, 0) ) )
      Serial.println("AP Config Failed");
  // print the ESP32 IP-Address
  Serial.println( WiFi.softAPIP() );
  server.begin();

  //----------------------------------------------------------------------------
  //--- Load system settings
  //----------------------------------------------------------------------------
  if( SPIFFS.exists( "/settings.ini" ) )
  {
    File fileSettings = SPIFFS.open( "/settings.ini" );
    Serial.println( "Reading settings.ini" );
    // Allocate a temporary JsonDocument
    // Don't forget to change the capacity to match your requirements.
    // Use arduinojson.org/assistant to compute the capacity.
    StaticJsonDocument<256> jsonSettings;
    // Deserialize the JSON document
    DeserializationError error = deserializeJson( jsonSettings, fileSettings );
    if( error )
      Serial.println( "Failed to read settings.ini" );
    Settings.pid = jsonSettings["pid"];
    Serial.print( "pid: " );
    Serial.println( Settings.pid, HEX );
    fileSettings.close();
  }
  else
  {
    Serial.println( "Settings.ini not found, rewriting" );
    File fileSettings = SPIFFS.open( "/settings.ini", "w" );
    // Allocate a temporary JsonDocument
    // Don't forget to change the capacity to match your requirements.
    // Use arduinojson.org/assistant to compute the capacity.
    StaticJsonDocument<256> jsonSettings;
    jsonSettings["pid"] = 0x01;
    // Serialize JSON to file
    if( serializeJson( jsonSettings, fileSettings ) == 0 )
      Serial.println( "Failed to write to file" );
    fileSettings.close();
  }
  
  //----------------------------------------------------------------------------
  //--- Download program to DSP
  //----------------------------------------------------------------------------
  uploadDspFirmware();

  //----------------------------------------------------------------------------
  //--- Download user parameter to DSP
  //----------------------------------------------------------------------------
  //uploadDspParameter();



  //state = STATUS_IDLE;
  wifiStatus = STATE_WIFI_IDLE;
}

String WebRequestHostAddress;     // global variable used to store Server IP-Address of HTTP-Request

//==============================================================================
/*! Sends an ACK via WiFi
 *
 */
void sendAckWifi( void )
{
  String httpResponse = "";
  httpResponse += "HTTP/1.1 200 OK\r\n";
  httpResponse += "Content-type:text/plain\r\n\r\n";
  httpResponse += "ACK";
  httpResponse += "\r\n";
  client.println( httpResponse );
}

//  Call this function regularly to look for client requests
//  template see https://github.com/espressif/arduino-esp32/blob/master/libraries/WiFi/examples/SimpleWiFiServer/SimpleWiFiServer.ino
//  returns empty string if no request from any client
//  returns GET Parameter: everything after the "/?" if ADDRESS/?xxxx was entered by the user in the webbrowser
//  returns "-" if ADDRESS but no GET Parameter was entered by the user in the webbrowser
//  remark: client connection stays open after return
String Webserver_GetRequestGETParameter()
{
  String GETParameter = "";
  bool waitForData = false;
  uint32_t contentLength = 0;
  uint32_t receivedBytes = 0;
  
  client = server.available();               // listen for incoming clients
  
  if( client )                              // if you get a client,
  {
    //Serial.println("Webserver_GetRequestGETParameter(): New Client.");           // print a message out the serial port
    String currentLine = "";                 // make a String to hold incoming data from the client
    
    while( client.connected() )            // loop while the client's connected
    {  
      if( client.available() )            // if there's bytes to read from the client,
      {  
        char c = client.read();            // read a byte, then
        if (c != '\r')  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine

        if (c == '\n')                     // if the byte is a newline character
        {
          //Serial.println( currentLine );
          if( waitForData )
          {
            if( wifiStatus == STATE_WIFI_PUTPARAM )
            {
              //Serial.println( currentLine );
              //if( currentLine.length() < 12 )
              //  Serial.println( "Not enough data" );
              //else
              //{
              int sentBytes = 0;
              while( sentBytes + 12 < currentLine.length() )
              {
                String strReg = currentLine.substring( sentBytes + 0, sentBytes + 4 );
                String strData = currentLine.substring( sentBytes + 4, sentBytes + 12 );
                //Serial.println( strReg );
                //Serial.println( strData );
                uint16_t reg = (uint16_t)strtoul( strReg.c_str(), NULL, 16 );
                uint32_t data = (uint32_t)strtoul( strData.c_str(), NULL, 16 );
                
                Wire.beginTransmission( DSP_ADDR );
                Serial.print( "I2C " );
                byte byteTx = (reg>>8) & 0xff;
                Serial.print( byte2string2(byteTx) );
                Wire.write( byteTx );
                byteTx = reg & 0xff;
                Serial.print( byte2string2(byteTx) );
                Wire.write( byteTx );
                Serial.print( " " ); 
                
                byteTx = (data>>24) & 0xff;
                Serial.print( byte2string2(byteTx) );
                Wire.write( byteTx );
                byteTx = (data>>16) & 0xff;
                Serial.print( byte2string2(byteTx) );
                Wire.write( byteTx );
                byteTx = (data>>8) & 0xff;
                Serial.print( byte2string2(byteTx) );
                Wire.write( byteTx );
                byteTx = data & 0xff;
                Serial.println( byte2string2(byteTx) );
                Wire.write( byteTx );               
                Wire.endTransmission( true );
                sentBytes += 12;
              } 
              //}
              waitForData = false;
              client.stop();
            }

            else if( wifiStatus == STATE_WIFI_DSPFW )
            {
              int offset = 0;
              while( offset < currentLine.length() )
              {
                String str = currentLine.substring( offset, offset + 2 );
                if( receivedBytes < contentLength )
                {
                  //Serial.print( str );
                  uint8_t rxByte = (uint8_t)strtoul( str.c_str(), NULL, 16 );
                  Serial.print( rxByte, HEX );
                  size_t len = fileDspProgram.write( &rxByte, 1 );
                  if( len != 1 )
                    Serial.println( "[ERROR] Writing to dspfw.hex" );
                  receivedBytes += 2;
                  totalBytesReceived++;
                }
                else
                {
                  Serial.println("ACK");
                  fileDspProgram.flush();
                  //Serial.print( "\nreceivedBytes = ");
                  //Serial.println( receivedBytes );
                  //sendAckWifi();
                }
                offset += 2;
              }
              
              if( receivedBytes >= contentLength )
              {
                client.stop();
                waitForData = false;
                //wifiStatus = STATE_WIFI_IDLE;
              }
              //currentLine = "";
            }

            else if( wifiStatus == STATE_WIFI_RECEIVE_USERPARAM )
            {
              int offset = 0;
              while( offset < currentLine.length() )
              {
                String str = currentLine.substring( offset, offset + 2 );
                if( receivedBytes < contentLength )
                {
                  //Serial.print( str );
                  uint8_t rxByte = (uint8_t)strtoul( str.c_str(), NULL, 16 );
                  Serial.print( rxByte, HEX );
                  size_t len = fileUserParams.write( &rxByte, 1 );
                  if( len != 1 )
                    Serial.println( "[ERROR] Writing to usrparam.hex" );
                  receivedBytes += 2;
                  totalBytesReceived++;
                }
                else
                {
                  Serial.println("ACK");
                  fileUserParams.flush();
                }
                offset += 2;
              }
              
              if( receivedBytes >= contentLength )
              {
                client.stop();
                waitForData = false;
                //wifiStatus = STATE_WIFI_IDLE;
              }
            }

            currentLine = "";
            //Serial.println( cntrPackets );
            
          }

          else
          {
            //Serial.println( currentLine );
            //--- New single dsp parameter sent
            if( currentLine.startsWith("PUT /param") )
            {
              Serial.println( "PUT /param" );
              wifiStatus = STATE_WIFI_PUTPARAM;
              currentLine = "";
              cntrPackets++;
            }

            //--- New dsp firmware data block
            else if( currentLine.startsWith("PUT /dspfw") )
            {
              Serial.println( "PUT /dspfw" );
              if( wifiStatus != STATE_WIFI_DSPFW )                              // start a new transfer
              {
                if( SPIFFS.exists( "/dspfw.hex" ) )
                {
                  if( SPIFFS.remove( "/dspfw.hex" ) )
                    Serial.println( "dspfw.hex deleted" );
                  else
                    Serial.println( "[ERROR] Deleting dspfw.hex" );
                }

                fileDspProgram = SPIFFS.open( "/dspfw.hex", "w" );
                if( !fileDspProgram )
                  Serial.println( "[ERROR] Failed to open dspfw.hex" );
                else
                  Serial.println( "Opened dspfw.hex" );

                totalBytesReceived = 0;
              }
              wifiStatus = STATE_WIFI_DSPFW;
              currentLine = "";
              //cntrPackets++;
            }

            //--- Finish dsp firmware transfer
            else if( currentLine.startsWith("GET /finishdspfw") )
            {
              Serial.println( "GET /finishdspfw" );
              fileDspProgram.flush();
              fileDspProgram.close();
              String httpResponse = "";
              httpResponse += "HTTP/1.1 200 OK\r\n";
              httpResponse += "Content-type:text/plain\r\n\r\n";
              httpResponse += String( totalBytesReceived );
              httpResponse += "\r\n";
              client.println( httpResponse );
              client.stop();
              Serial.println( totalBytesReceived );
              wifiStatus = STATE_WIFI_IDLE;
              currentLine = "";
              //cntrPackets++;
            }

            //--- Request of PID
            else if( currentLine.startsWith("GET /pid") )
            {
              Serial.println( "GET /pid" );
              String httpResponse = "";
              httpResponse += "HTTP/1.1 200 OK\r\n";
              httpResponse += "Content-type:text/plain\r\n\r\n";
              httpResponse += String( Settings.pid );
              Serial.println( Settings.pid );
              httpResponse += "\r\n";
              client.println( httpResponse );
              client.stop();
              currentLine = "";
              //cntrPackets++;
            }

            //--- New user parameter block
            else if( currentLine.startsWith("PUT /userparam") )
            {
              Serial.println( "PUT /userparam" );
              if( wifiStatus != STATE_WIFI_RECEIVE_USERPARAM )                  // start a new transfer
              {
                if( SPIFFS.exists( "/usrparam.hex" ) )
                {
                  if( SPIFFS.remove( "/usrparam.hex" ) )
                    Serial.println( "usrparam.hex deleted" );
                  else
                    Serial.println( "[ERROR] Deleting usrparam.hex" );
                }

                fileUserParams = SPIFFS.open( "/usrparam.hex", "w" );
                if( !fileUserParams )
                  Serial.println( "[ERROR] Failed to open usrparam.hex" );
                else
                  Serial.println( "Opened usrparam.hex" );

                totalBytesReceived = 0;
              }
              wifiStatus = STATE_WIFI_RECEIVE_USERPARAM;
              currentLine = "";
              //cntrPackets++;
            }

            //--- Finish user parameters transfer
            else if( currentLine.startsWith("GET /finishuserparam") )
            {
              Serial.println( "GET /finishuserparam" );
              fileUserParams.flush();
              fileUserParams.close();
              String httpResponse = "";
              httpResponse += "HTTP/1.1 200 OK\r\n";
              httpResponse += "Content-type:text/plain\r\n\r\n";
              httpResponse += String( totalBytesReceived );
              httpResponse += "\r\n";
              client.println( httpResponse );
              client.stop();
              Serial.println( totalBytesReceived );
              wifiStatus = STATE_WIFI_IDLE;
              currentLine = "";
              //cntrPackets++;
            }

            //--- Request of user parameter file size
            else if( currentLine.startsWith("GET /sizeuserparam") )
            {
              Serial.println( "GET /sizeuserparam" );
              String httpResponse = "";
              httpResponse += "HTTP/1.1 200 OK\r\n";
              httpResponse += "Content-type:text/plain\r\n\r\n";
              if( SPIFFS.exists( "/usrparam.hex" ) )
              {
                fileUserParams = SPIFFS.open( "/usrparam.hex", "r" );
                httpResponse += String( fileUserParams.size() );
                fileUserParams.close();
              }
              else
                httpResponse += "0";
              httpResponse += "\r\n";
              client.println( httpResponse );
              client.stop();
              wifiStatus = STATE_WIFI_IDLE;
              currentLine = "";
              //cntrPackets++;
            }

            //--- Request of user parameter file
            else if( currentLine.startsWith("GET /userparam") )
            {
              Serial.println( "GET /userparam" );
              String httpResponse = "";
              httpResponse += "HTTP/1.1 200 OK\r\n";
              httpResponse += "Content-type:text/plain\r\n\r\n";
              if( SPIFFS.exists( "/usrparam.hex" ) )
              {
                fileUserParams = SPIFFS.open( "/usrparam.hex", "r" );
                if( fileUserParams )
                {
                  size_t len = fileUserParams.size();
                  Serial.println( len );
                  //len = 100;
                  int cntr = 0;

                  while( cntr < len )
                  {
                    byte byteRead;
                    fileUserParams.read( &byteRead, 1 );
                    //Serial.println( byte2string2( byteRead ) );
                    httpResponse += byte2string2( byteRead );
                    cntr++;
                  }
                }
                fileUserParams.close();
              }
              httpResponse += "\r\n";
              client.println( httpResponse );
              client.stop();
              wifiStatus = STATE_WIFI_IDLE;
              currentLine = "";
              //cntrPackets++;
            }

            else if( currentLine.startsWith("Host:") )
            {
              //Serial.println( currentLine );
              currentLine = "";
            }

            else if( currentLine.startsWith("Content-type:") )
            {
              //Serial.println( currentLine );
              currentLine = "";
            }

            //--- Content-length
            else if( currentLine.startsWith( "Content-length" ) )
            {
              //Serial.println( currentLine );
              String str = currentLine.substring( currentLine.indexOf(':') + 1, currentLine.length() );
              contentLength = (uint32_t)strtoul( str.c_str(), NULL, 10 );
              receivedBytes = 0;
              currentLine = "";
            }

            //--- Begin of Content line
            else if( currentLine.startsWith( "\n" ) )
            {
              waitForData = true;
              currentLine = "";
            }

            else
              currentLine = "";
          }
        } 
        
      }
      
    }
    
  }

  return GETParameter;
}


void loop()
{

  String GETParameter = Webserver_GetRequestGETParameter();   // look for client request




  delay( 50 );

#if 0
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

  #endif

   //Wire.beginTransmission( DSP_ADDR );
   //Wire.endTransmission();

}
