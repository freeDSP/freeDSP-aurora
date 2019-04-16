
#include <Wire.h>
#include <WiFi.h>
#include <ArduinoJson.h>
#include <ArduinoOTA.h>
#include <ESPmDNS.h>
#include "SPIFFS.h"

#include "AK4458.h"
#include "AK5558.h"

#define I2C_SDA_PIN 16
#define I2C_SCL_PIN 4

#define FORMAT_SPIFFS_IF_FAILED true

// DSP address on I2C bus
#define DSP_ADDR           (0x70>>1)
// ADC address on I2C bus
#define AK5558_I2C_ADDR    (0x22>>1)
// DAC address on I2C bus
#define AK4458_I2C_ADDR    (0x20>>1)

//


//#define AK4458_REGREAD(reg, val)  { AKM_i2c_shared_master_read_reg(r_i2c, AK4458_I2C_ADDR, reg, val, 1);}

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
  STATE_WIFI_RECEIVE_PARAMETER,
  STATE_WIFI_DSPFW,
  STATE_WIFI_RECEIVE_USERPARAM,
  STATE_WIFI_RECEIVE_CONFIG

  //STATE_WIFI_RECEIVE_SINGLEPARAM
};

struct tSettings
{
  byte pid;
  String ssid;
  String password;
};

tSettings Settings;

//BluetoothSerial SerialBT;

int state;
int numBytes = 0;
uint16_t dspRegister = 0;
uint32_t dspValueHex = 0;
float dspValue;

File fileDspProgram;
File fileDspParams;
File fileUserParams;

WiFiClient client;
WiFiServer server( 80 );

twifistatus wifiStatus = STATE_WIFI_IDLE;
int cntrPackets = 0;
uint32_t totalBytesReceived;
String receivedPostRequest;

//==============================================================================
/*! 
 */
void AK4458_REGWRITE( byte reg, byte val ) 
{ 
  Wire.beginTransmission( AK4458_I2C_ADDR );
  Wire.write( reg );
  Wire.write( val );
  Wire.endTransmission( true );
}

//==============================================================================
/*! 
 */
void AK5558_REGWRITE( byte reg, byte val)
{ 
  Wire.beginTransmission( AK5558_I2C_ADDR );
  Wire.write( reg );
  Wire.write( val );
  Wire.endTransmission( true );
}

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
/*! Saves the global settings
 */
void saveSettings( void )
{
  if( SPIFFS.exists( "/settings.ini" ) )
    SPIFFS.remove( "/settings.ini" );

  File fileSettings = SPIFFS.open( "/settings.ini", "w" );
  // Allocate a temporary JsonDocument
  // Don't forget to change the capacity to match your requirements.
  // Use arduinojson.org/assistant to compute the capacity.
  StaticJsonDocument<256> jsonSettings;
  jsonSettings["pid"] = Settings.pid;
  jsonSettings["ssid"] = Settings.ssid; // max 32 charachters
  jsonSettings["pwd"] = Settings.password;  // max 64 charachters
  // Serialize JSON to file
  if( serializeJson( jsonSettings, fileSettings ) == 0 )
    Serial.println( "Failed to write to file" );
  fileSettings.close();
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
/*! Configure AK5558 ADC
 */
void configADC( void )
{
  /* Power Management1 (Address: 0x01)
   * bit[0]   : RSTN: Internal Timing Reset                           :   0 Reset
   * bit[2:1] : MONO2-1: Channel Summation mode Select                :  00 Not- Summation mode (default)
   */
  AK5558_REGWRITE( AK5558_POWERMANAGEMENT2, 0b00000000 );

  /* Control 1 (Address: 0x02)
   * bit[0]   : HPFE: High Pass Filter Enable                         :   1 High Pass Filter ON (default)
   * bit[2:1] : DIF1-0: Audio Data Interface Mode Select              :  10 32bit MSB
   * bit[6:3] : CKS3-0: Sampling Speed Mode and MCLK Frequency Select :0110 Normal Speed, 512fs
   */
  AK5558_REGWRITE( AK5558_CONTROL1, 0b00110101 );

  /* Control 2 (Address: 0x03)
   * bit[6:5] : TDM1-0: TDMModesSelect                                :  10 TDM256
   */
  AK5558_REGWRITE( AK5558_CONTROL2, 0b01000000 );

  /* Control 3 (Address: 0x04)
   * bit[0]   : SLOW: Slow Roll-off Filter Select                     :   0: Sharp Roll-off (default)
   * bit[1]   : SD: Short Delay Select                                :   0: Normal Delay (default)
   * bit[7]   : DSD Mode Select                                       :   0: PCM mode (default)
   */
  AK5558_REGWRITE( AK5558_CONTROL3, 0b00000000 );

  /* DSD (Address: 0x05)
   * bit[0:1] : DSDSEL1-0:Select the Frequency of DCLK                :  00: 64fs (default)
   * bit[2]   : DCKB: Polarity of DCLK                                :   0: DSD data is output from DCLK Falling Edge (default)
   * bit[3]   : PMOD: DSD Phase Modulation Mode                       :   0: Not Phase Modulation Mode (default)
   * bit[5]   : DCKS: Master Clock Frequency Select at DSD Mode       :   0: 512fs (default)
   */
  AK5558_REGWRITE( AK5558_DSD, 0b00000000 );

  /* Power Management1 (Address: 0x01)
   * bit[0]   : RSTN: Internal Timing Reset                           :   1 Normal operation
   * bit[2:1] : MONO2-1: Channel Summation mode Select                :  00 Not- Summation mode (default)
   */
  AK5558_REGWRITE( AK5558_POWERMANAGEMENT2, 0b00000001 );

}

//==============================================================================
/*! Configure AK4458 DAC
 */
void configDAC( void )
{
  /* Control 1 (Address: 0x00)
   * bit[0]   : RSTN: Internal Timing Reset                           :   0 Reset
   * bit[3:1] : DIF2-0: Audio Data Interface Modes                    : 110 Mode 18
   * bit[7]   : ACKS: Master Clock Frequency Auto Setting Mode Enable :   0 Manual Setting Mode
   */
  AK4458_REGWRITE( AK4458_CONTROL1, 0b00001100 );

  /* Control 2 (Address: 0x01)
   * bit[0]   : SMUTE Soft Mute Enable                                :   0 Normal Operation
   * bit[2:1] : DEM11-0 DAC1 De-emphasis Response                     :  01 Off
   * bit[4:3] : DFS1-0 Sampling Speed Control                         :  00 Normal Speed
   * bit[5]   : SD Short delay Filter Enable                          :   1 Short delay filter
   */
  AK4458_REGWRITE( AK4458_CONTROL2, 0b00100010 );

  /* Control 3 (Address: 0x02)
   * bit[0]   : SLOW Slow Roll-off Filter Enable                      :   0 Sharp roll-off filter
   * bit[1]   : SELLR1 Data selection of DAC1 L & R, when MONO mode   :   0 Default
   * bit[2]   : DZFB Inverting Enable of DZF                          :   0 DZF pin goes “H” at Zero Detection
   * bit[3]   : MONO1 DAC1 enters monaural output mode                :   0 Stereo mode
   * bit[4]   : DCKBPolarity of DCLK (DSD Only)                       :   0 DSD data is output from DCLK falling edge
   * bit[5]   : DCKS Master Clock Frequency Select at DSD mode        :   0 512fs
   * bit[7]   : DP DSD/PCM Mode Select                                :   0 PCM Mode
   */
  AK4458_REGWRITE( AK4458_CONTROL3, 0b00000000 );

  /* Control 4 (Address: 0x05)
   * bit[0]   : SSLOW Digital Filter Bypass Mode Enable               :   0 Enable digital filter selected by SD and SLOW bits
   * bit[1]   : DFS2 Sampling Speed Control                           :   0 Normal Speed
   * bit[3]   : SELLR2 Data selection of DAC2 L & R, when MONO mode   :   0 Default
   * bit[4]   : INVL1 AOUTL1 Output Phase Inverting Bit               :   0 Normal
   * bit[5]   : INVR1 AOUTR1 Output Phase Inverting Bit               :   0 Normal
   * bit[6]   : INVL2 AOUTL2 Output Phase Inverting Bit               :   0 Normal
   * bit[7]   : INVR2 AOUTR2 Output Phase Inverting Bit               :   0 Normal
   */
  AK4458_REGWRITE( AK4458_CONTROL4, 0b00000000 );

  /* Control 5 (Address: 0x07)
   * bit[0]   : SYNCE SYNCModeEnable                                  :   1 SYNC Mode Enable
   * bit[7:4] : L3-4,R3-4 Zero Detect Flag Enable Bit for the DZF pin :   0 Disable
   */
  AK4458_REGWRITE( AK4458_CONTROL5, 0b00000011 );

  /* Sound Control (Address: 0x08)
   * bit[1:0] : SC1-0 Sound Control                                   :  00 Mode 1
   * bit[7:4] : L1-2,R1-2 Zero Detect Flag Enable Bit for the DZF pin :   0 Disable
   */
  AK4458_REGWRITE( AK4458_CONTROL5, 0b00000000 );

  /* Control 6 (Address: 0x0A)
   * bit[1:0] : DEM21-0 DAC2 De-emphasis Response                     :  01 Off
   * bit[2]   : PW1 Power management for DAC1                         :   1 On
   * bit[3]   : PW2 Power management for DAC2                         :   1 On
   * bit[5:4] : SDS2-1 DAC1-4 Data Select                             :  00 Normal Operation
   * bit[7:6] : TDM Mode Select                                       :  10 TDM256
   */
  AK4458_REGWRITE( AK4458_CONTROL6, 0b10001101 );

  /* Control 7 (Address: 0x0B)
   * bit[1]   : DCHAIN Daisy Chain Mode Enable                        :   0 Daisy Chain Mode Disable
   * bit[2]   : PW3 Power management for DAC3                         :   1 On
   * bit[3]   : PW4 Power management for DAC4                         :   1 On
   * bit[4]   : SDS0 DAC1-4 Data Select                               :   0 Normal Operation
   * bit[7:6] : ATS1-0 DAC Digital attenuator transition time setting :  00 Mode 0 4080/fs
   */
  AK4458_REGWRITE( AK4458_CONTROL7, 0b00001100 );

  /* Control 8 (Address: 0x0C)
   * bit[0:2] : FIR2-0: FIR Filter Control                            : 000 Default
   * bit[4]   : INVL3 AOUTL3 Output Phase Inverting Bit               :   0 Normal
   * bit[5]   : INVR3 AOUTR3 Output Phase Inverting Bit               :   0 Normal
   * bit[6]   : INVL4 AOUTL4 Output Phase Inverting Bit               :   0 Normal
   * bit[7]   : INVR4 AOUTR4 Output Phase Inverting Bit               :   0 Normal
   */
  AK4458_REGWRITE( AK4458_CONTROL8, 0b00000000 );

  /* Control 9 (Address: 0x0D)
   * bit[2]   : SELLR3 Data selection of DAC3 L & R, when MONO mode   :   0 Default
   * bit[3]   : SELLR4 Data selection of DAC4 L & R, when MONO mode   :   0 Default
   * bit[5]   : MONO2 DAC2 enters monaural output mode                :   0 Stereo mode
   * bit[6]   : MONO3 DAC3 enters monaural output mode                :   0 Stereo mode
   * bit[7]   : MONO4 DAC4 enters monaural output mode                :   0 Stereo mode
   */
  AK4458_REGWRITE( AK4458_CONTROL9, 0b00000000 );

  /* Control 10 (Address: 0x0E)
   * bit[5:4] : DEM31-0 DAC3 De-emphasis Response                     :  01 Off
   * bit[7:6] : DEM41-0 DAC4 De-emphasis Response                     :  01 Off
   */
  AK4458_REGWRITE( AK4458_CONTROL10, 0b01010000 );


  // Release Reset by rewriting Control1
  /* Control 1 (Address: 0x00)
   * bit[0]   : RSTN: Internal Timing Reset                           :   1 Normal Operation
   * bit[3:1] : DIF2-0: Audio Data Interface Modes                    : 110 Mode 18
   * bit[7]   : ACKS: Master Clock Frequency Auto Setting Mode Enable :   0 Manual Setting Mode
   */
  AK4458_REGWRITE( AK4458_CONTROL1, 0b00001101 );
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

  if( !SPIFFS.begin( FORMAT_SPIFFS_IF_FAILED ) )
  {
    Serial.println( "An Error has occurred while mounting SPIFFS" );
    return;
  }
  Serial.print( "Free disk space: " );
  Serial.print( (SPIFFS.totalBytes() - SPIFFS.usedBytes()) / 1024 );
  Serial.println( "KiB" );

  //Settings.pid = 0x01;
  //Settings.ssid = "";
  //Settings.password = "";
  //saveSettings();

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
    Settings.ssid = jsonSettings["ssid"].as<String>();
    Settings.password = jsonSettings["pwd"].as<String>();
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
    jsonSettings["ssid"] = "";
    jsonSettings["pwd"] = "";
    // Serialize JSON to file
    if( serializeJson( jsonSettings, fileSettings ) == 0 )
      Serial.println( "Failed to write to file" );
    fileSettings.close();
  }

  //----------------------------------------------------------------------------
  //--- Configure ESP for WiFi access
  //----------------------------------------------------------------------------
  //if( !MDNS.begin("freeDSP-aurora-mdns") ) 
  //  Serial.println( "[ERROR] Could not set up mDNS responder!" );   

  WiFi.disconnect();
  WiFi.mode( WIFI_AP_STA );
  WiFi.setHostname( "freeDSP-aurora" );
  // Start access point
  WiFi.softAP( "AP-freeDSP-aurora" );
  delay(100);
  //wait for SYSTEM_EVENT_AP_START
  if( !WiFi.softAPConfig( IPAddress(192, 168, 5, 1), IPAddress(192, 168, 5, 1), IPAddress(255, 255, 255, 0) ) )
      Serial.println("AP Config Failed");

  Serial.println( Settings.ssid.c_str() );
  Serial.println( Settings.password.c_str() );
  WiFi.begin( Settings.ssid.c_str(), Settings.password.c_str() );

  int cntrConnect = 0;
  /*while( WiFi.waitForConnectResult() != WL_CONNECTED && cntrConnect < 3 )
  {
    Serial.println("WiFi Connection Failed! Trying again..");
    //delay(1000);
    cntrConnect++;
  }*/
  
  // print the ESP32 IP-Address
  Serial.print( "Soft AP IP:" );
  Serial.println( WiFi.softAPIP() );
  Serial.print( "Local IP:" );
  Serial.println( WiFi.localIP() );
  Serial.println(WiFi.getHostname());

  server.begin();

  // Add service to MDNS-SD
  //MDNS.addService( "http", "tcp", 8088 );
  
  //----------------------------------------------------------------------------
  //--- Download program to DSP
  //----------------------------------------------------------------------------
  uploadDspFirmware();

  //----------------------------------------------------------------------------
  //--- Download user parameter to DSP
  //----------------------------------------------------------------------------
  //uploadDspParameter();

  //----------------------------------------------------------------------------
  //--- Configure ADC
  //----------------------------------------------------------------------------
  configADC();

  //----------------------------------------------------------------------------
  //--- Configure DAC
  //----------------------------------------------------------------------------
  configDAC();

  //----------------------------------------------------------------------------
  //--- Start OTA
  //----------------------------------------------------------------------------
  // Port defaults to 3232
  // ArduinoOTA.setPort(3232);

  // Hostname
  ArduinoOTA.setHostname( "OTA-freeDSP-aurora" );
  ArduinoOTA.setPassword( "admin" );

  // Password can be set with it's md5 value as well
  // MD5(admin) = 21232f297a57a5a743894a0e4a801fc3
  // ArduinoOTA.setPasswordHash("21232f297a57a5a743894a0e4a801fc3");

  ArduinoOTA
    .onStart([]() {
      String type;
      if (ArduinoOTA.getCommand() == U_FLASH)
        type = "sketch";
      else // U_SPIFFS
        type = "filesystem";

      // NOTE: if updating SPIFFS this would be the place to unmount SPIFFS using SPIFFS.end()
      SPIFFS.end();
      Serial.println("[OTA] Start updating " + type);
    })
    .onEnd([]() {
      Serial.println("\n[OTA] End");
    })
    .onProgress([](unsigned int progress, unsigned int total) {
      Serial.printf("[OTA] Progress: %u%%\r", (progress / (total / 100)));
    })
    .onError([](ota_error_t error) {
      Serial.printf("[OTA] Error[%u]: ", error);
      if (error == OTA_AUTH_ERROR) Serial.println("Auth Failed");
      else if (error == OTA_BEGIN_ERROR) Serial.println("Begin Failed");
      else if (error == OTA_CONNECT_ERROR) Serial.println("Connect Failed");
      else if (error == OTA_RECEIVE_ERROR) Serial.println("Receive Failed");
      else if (error == OTA_END_ERROR) Serial.println("End Failed");
    });

  ArduinoOTA.begin();

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

//==============================================================================
/*! Handles any HTTP request.
 *
 */
void handleHttpRequest()
{
  bool waitForData = false;
  uint32_t contentLength = 0;
  uint32_t receivedBytes = 0;
  
  client = server.available();               // listen for incoming clients
  
  if( client )                              // if you get a client,
  {
    String currentLine = "";                 // make a String to hold incoming data from the client
    
    while( client.connected() )            // loop while the client's connected
    {  
      if( client.available() )            // if there's bytes to read from the client,
      {  
        char c = client.read();            // read a byte, then

        if(c != '\r')   // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine

        if (c == '\n')                     // if the byte is a newline character
        {
          //Serial.println( currentLine );
          if( waitForData )
          {
            if( wifiStatus == STATE_WIFI_RECEIVE_PARAMETER )
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
                Serial.println( strReg );
                Serial.println( strData );
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
              wifiStatus = STATE_WIFI_IDLE;
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
                  Serial.println("OK");
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
                  Serial.println("OK");
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

            else if( wifiStatus = STATE_WIFI_RECEIVE_CONFIG )
            {
              receivedPostRequest += currentLine;

              if( receivedPostRequest.length() >= contentLength )
              {
                receivedPostRequest = receivedPostRequest.substring( 0, receivedPostRequest.length()-1 );
                int posStartSearch = 0;
                String paramName;
                String paramValue;
                int posSeparator;
                int posValue;
                // search for '&' in received line
                while( receivedPostRequest.indexOf( '&', posStartSearch) > -1 )
                {
                  posSeparator = receivedPostRequest.indexOf( '&', posStartSearch );
                  posValue = receivedPostRequest.indexOf( '=', posStartSearch );
                
                  paramName = receivedPostRequest.substring( posStartSearch, posValue );
                  paramValue = receivedPostRequest.substring( posValue + 1, posSeparator );
                  if( paramName == "SSID" )
                    Settings.ssid = paramValue;
                  else if( paramName == "Password" )
                    Settings.password = paramValue;
                  posStartSearch = posSeparator + 1;
                }
                posValue = receivedPostRequest.indexOf( '=', posStartSearch );
                paramName = receivedPostRequest.substring( posStartSearch, posValue );
                paramValue = receivedPostRequest.substring( posValue + 1, receivedPostRequest.length() );
                if( paramName == "SSID" )
                  Settings.ssid = paramValue;
                else if( paramName == "Password" )
                  Settings.password = paramValue;
                saveSettings();
                sendAckWifi();
                client.stop();
                waitForData = false;
                Serial.println( "OK" );
              }
                
            }

            currentLine = "";
            //Serial.println( cntrPackets );
            
          }

          else
          {
            //Serial.println( currentLine );
            //--- New single dsp parameter sent
            if( currentLine.startsWith("POST /parameter") )
            {
              Serial.println( "POST /parameter" );
              wifiStatus = STATE_WIFI_RECEIVE_PARAMETER;
              currentLine = "";
              //cntrPackets++;
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

            //--- Request of DSP firmware size
            else if( currentLine.startsWith("GET /sizedspfw") )
            {
              Serial.println( "GET /sizedspfw" );
              String httpResponse = "";
              httpResponse += "HTTP/1.1 200 OK\r\n";
              httpResponse += "Content-type:text/plain\r\n\r\n";
              if( SPIFFS.exists( "/dspfw.hex" ) )
              {
                fileDspProgram = SPIFFS.open( "/dspfw.hex", "r" );
                httpResponse += String( fileDspProgram.size() );
                fileDspProgram.close();
              }
              else
              {
                Serial.println( "[ERROR] dspfw.hex does not exist." );
                httpResponse += "0";
              }
              httpResponse += "\r\n";
              client.println( httpResponse );
              client.stop();
              wifiStatus = STATE_WIFI_IDLE;
              currentLine = "";
              //cntrPackets++;
            }

            //--- Request of DSP firmware
            else if( currentLine.startsWith("GET /dspfw") )
            {
              Serial.println( "GET /dspfw" );
              String httpResponse = "";
              httpResponse += "HTTP/1.1 200 OK\r\n";
              httpResponse += "Content-type:text/plain\r\n\r\n";
              if( SPIFFS.exists( "/dspfw.hex" ) )
              {
                fileDspProgram = SPIFFS.open( "/dspfw.hex", "r" );
                if( fileDspProgram )
                {
                  size_t len = fileDspProgram.size();
                  Serial.println( len );
                  int cntr = 0;

                  while( cntr < len )
                  {
                    byte byteRead;
                    fileDspProgram.read( &byteRead, 1 );
                    Serial.print( cntr );
                    Serial.print( ": " );
                    Serial.println( byte2string2( byteRead ) );
                    httpResponse += byte2string2( byteRead );
                    cntr++;
                    if( cntr % 1024 == 0 )
                    {
                      client.print( httpResponse );
                      httpResponse = "";
                    }
                  }
                  httpResponse += "\r\n";
                  client.println( httpResponse );
                }
                fileDspProgram.close();
              }
              //httpResponse += "\r\n";
              //client.println( httpResponse );
              client.stop();
              wifiStatus = STATE_WIFI_IDLE;
              currentLine = "";
              //cntrPackets++;
            }

            //--- Receiving new Wifi Configuration
            else if( currentLine.startsWith("POST /wificonfig") )
            {
              Serial.println( "POST /wificonfig" );
              receivedPostRequest = "";
              wifiStatus = STATE_WIFI_RECEIVE_CONFIG;
              waitForData = false;
              currentLine = "";
              //cntrPackets++;
            }

            //--- Received a ping
            else if( currentLine.startsWith("GET /ping") )
            {
              Serial.println( "GET /ping" );
              String httpResponse = "";
              httpResponse += "HTTP/1.1 200 OK\r\n";
              httpResponse += "Content-type:text/plain\r\n\r\n";
              httpResponse += WiFi.localIP().toString();
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
}


void loop()
{

  handleHttpRequest();

  ArduinoOTA.handle();

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
