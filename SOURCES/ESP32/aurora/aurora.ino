
#include <Wire.h>
#include <WiFi.h>
#include <ArduinoJson.h>
#include <ArduinoOTA.h>
#include <ESPmDNS.h>
#include "SPIFFS.h"

#include "AK4458.h"
#include "AK5558.h"
#include "WebOTA.h"

// Configuration for hardware rev. 0.9.x
//#define I2C_SDA_PIN 16
//#define I2C_SCL_PIN 4
//#define I2C_SCL_DSP_PIN 33

// Configuration for hardware rev. 1.0.0
#define I2C_SDA_PIN 17
#define I2C_SCL_PIN 16

#define VERSION_STR "1.1.1"

#define FORMAT_SPIFFS_IF_FAILED true

// DSP address on I2C bus
#define DSP_ADDR           (0x70>>1)
// ADC address on I2C bus
#define AK5558_I2C_ADDR    (0x22>>1)
// DAC address on I2C bus
#define AK4458_I2C_ADDR    (0x20>>1)
// S/P-DIF-Mux on AddOnB
#define ADDONB_SPDIFMUX_ADDR (0x82>>1)

#define NUMPRESETS (4)

#define POST_WRITEI2C     "POST /writei2c"
#define POST_READI2C      "POST /readi2c"
#define POST_ADDONCONFIG  "POST /aconfig"
#define GET_ADDONCONFIG   "GET /aconfig"

enum twifistatus
{
  STATE_WIFI_IDLE,
  STATE_WIFI_RECEIVE_PARAMETER,
  STATE_WIFI_DSPFW,
  STATE_WIFI_RECEIVE_USERPARAM,
  STATE_WIFI_RECEIVE_CONFIG,
  STATE_WIFI_RECEIVE_PID,
  STATE_WIFI_RECEIVE_DSPPARAM,
  STATE_WIFI_RECEIVE_AID,
  STATE_WIFI_RECEIVE_PRESETID,
  STATE_WIFI_RECEIVE_WRITEI2C,
  STATE_WIFI_RECEIVE_READI2C,
  STATE_WIFI_POST_ADDONCONFIG,
  STATE_WIFI_GET_ADDONCONFIG
};

enum taddonid
{
  ADDON_CUSTOM = 0x00,
  ADDON_A = 0x01,
  ADDON_B = 0x02,
  ADDON_C = 0x03,
  ADDON_D = 0x04
};

struct tSettings
{
  byte pid;
  String ssid;
  String password;
  uint32_t addonid;
  byte currentPreset;
  String version;
};

tSettings Settings;

int state;
int numBytes = 0;
uint16_t dspRegister = 0;
uint32_t dspValueHex = 0;
float dspValue;

File fileDspProgram;
File fileDspParams;
File fileUserParams;
File fileAddOnConfig;

WiFiClient client;
WiFiServer server( 80 );

twifistatus wifiStatus = STATE_WIFI_IDLE;
int cntrPackets = 0;
uint32_t totalBytesReceived;
String receivedPostRequest;

String presetUsrparamFile[4] = { "/usrparam.001", "/usrparam.002", "/usrparam.003", "/usrparam.004" };
String presetDspparamFile[4] = { "/dspparam.001", "/dspparam.002", "/dspparam.003", "/dspparam.004" };
String presetAddonCfgFile[4] = { "/addoncfg.001", "/addoncfg.002", "/addoncfg.003", "/addoncfg.004" };

//==============================================================================
/*! 
 */
void ADAU1452_WRITE_REGISTER( uint16_t reg, byte msb, byte lsb ) 
{
  Wire.beginTransmission( DSP_ADDR );
  Wire.write( (byte)( (reg >> 8) & 0xFF ) );
  Wire.write( (byte)(  reg       & 0xFF ) );
  Wire.write( msb );
  Wire.write( lsb ); 
  Wire.endTransmission( true );
}

//==============================================================================
/*! 
 */
void ADAU1452_WRITE_BLOCK( uint16_t regaddr, byte val[], uint16_t len ) 
{
  for( uint16_t ii = 0; ii < len; ii = ii + 4 )
  {
    Wire.beginTransmission( DSP_ADDR );
    Wire.write( (byte)( (regaddr >> 8) & 0xFF ) );
    Wire.write( (byte)(  regaddr       & 0xFF ) );
    Wire.write( (byte)( val[ii] & 0xFF ) );
    Wire.write( (byte)( val[ii+1] & 0xFF ) );
    Wire.write( (byte)( val[ii+2] & 0xFF ) );
    Wire.write( (byte)( val[ii+3] & 0xFF ) );
    Wire.endTransmission( true );
  }
}

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
  str += ", ";
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
  jsonSettings["aid"] = Settings.addonid;
  jsonSettings["preset"] = Settings.currentPreset;
  jsonSettings["version"] = Settings.version;
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
  byte byteReadMSB;
  byte byteReadLSB;
  byte byteRead;
  uint16_t regaddr;

  if( fileDspProgram )
  {
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
      //Serial.println( numBytesToRead );

      //------------------------------------------------------------------------
      //--- Send register address and value
      //------------------------------------------------------------------------
      if( numBytesToRead > 0 )
      {
        fileDspProgram.read( &byteRead, 1 );
        regaddr = ((uint16_t)byteRead) << 8;
        cntr++;
        
        fileDspProgram.read( &byteRead, 1 );
        regaddr += byteRead;
        cntr++;

        if( numBytesToRead == 4 )
        {
          fileDspProgram.read( &byteReadMSB, 1 );
          cntr++;
          fileDspProgram.read( &byteReadLSB, 1 );
          cntr++;

          if( regaddr == 0x0000 )
          {
            //Serial.println( "DELAY" );
            delay( 500 );
          }
          else
          {
            ADAU1452_WRITE_REGISTER( regaddr, byteReadMSB, byteReadLSB );
            if( cntr % 4096 == 0 )
              Serial.print( "." );
          }
        }
        else if( numBytesToRead > 4 )
        {
          uint16_t addr = regaddr;
          byte val[4];

          for( uint32_t ii = 0; ii < numBytesToRead - 2; ii = ii + 4 )
          {
            fileDspProgram.read( &(val[0]), 1 );
            fileDspProgram.read( &(val[1]), 1 );
            fileDspProgram.read( &(val[2]), 1 );
            fileDspProgram.read( &(val[3]), 1 );
            cntr += 4;
            ADAU1452_WRITE_BLOCK( addr, val, 4 );
            if( cntr % 4096 == 0 )
              Serial.print( "." );
            //Serial.println(ii);
            addr++;
          }
        }
        else
        {
          Serial.print( "[ERROR] Bad number of bytes: " );
          Serial.println( numBytesToRead );
        }
      }

      //Serial.print(".");
      
      //Serial.println( cntr );
     
    }

    fileDspProgram.close();

  }
  else
    Serial.println( "\n[ERROR] Failed to open file dspfw.hex" );
  Serial.print( "[ok]\n" );
}


//==============================================================================
/*! Uploads the parameters from ESP32 SPI flash to DSP.
 */
void uploadDspParameter( void )
{
  Serial.print( "Loading dsp parameter preset " + presetDspparamFile[Settings.currentPreset] + "......" );

  fileDspParams = SPIFFS.open( presetDspparamFile[Settings.currentPreset] );

  if( fileDspParams )
  {
    Serial.print( "File size:");
    Serial.println( fileDspParams.size() );

    int file_size = fileDspParams.size();

    int cntr = 0;

    while( fileDspParams.available() )
    {
      //Serial.print( "I2C " );
      byte byteRead; 
      fileDspParams.read( &byteRead, 1 );
      //Serial.print( "0x" );
      //Serial.print( byte2string2(byteRead) );
      uint16_t regaddr = ((uint16_t)byteRead) << 8;
      fileDspParams.read( &byteRead, 1 );
      //Serial.print( byte2string2(byteRead) );
      //Serial.print( " " ); 
      regaddr += byteRead;

      byte val[4];
      fileDspParams.read( &(val[0]), 1 );
      fileDspParams.read( &(val[1]), 1 );
      fileDspParams.read( &(val[2]), 1 );
      fileDspParams.read( &(val[3]), 1 );
      ADAU1452_WRITE_BLOCK( regaddr, val, 4 );  

      //Serial.print( "0x" );
      //Serial.print( byte2string2(val[0]) );
      //Serial.print( byte2string2(val[1]) );
      //Serial.print( byte2string2(val[2]) );
      //Serial.println( byte2string2(val[3]) );

    }

    //Serial.print( cntr );
    //Serial.println( "Bytes" );

    fileDspParams.close();

  }
  else
    Serial.println( "\n[ERROR] Failed to open file " + presetDspparamFile[Settings.currentPreset] );
  Serial.print( "[ok]\n" );
}

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

  AK4458_REGWRITE( AK4458_L1CHATT, 0xFF );
  AK4458_REGWRITE( AK4458_R1CHATT, 0xFF );

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

  /* DSD1 (Address: 0x06)
   */
  AK4458_REGWRITE( AK4458_DSD1, 0b00000000 );

  /* Control 5 (Address: 0x07)
   * bit[0]   : SYNCE SYNCModeEnable                                  :   1 SYNC Mode Enable
   * bit[7:4] : L3-4,R3-4 Zero Detect Flag Enable Bit for the DZF pin :   0 Disable
   */
  AK4458_REGWRITE( AK4458_CONTROL5, 0b00000011 );

  /* Sound Control (Address: 0x08)
   * bit[1:0] : SC1-0 Sound Control                                   :  00 Mode 1
   * bit[7:4] : L1-2,R1-2 Zero Detect Flag Enable Bit for the DZF pin :   0 Disable
   */
  AK4458_REGWRITE( AK4458_SOUNDCONTROL, 0b00000000 );

  /* DSD1 (Address: 0x09)
   */
  AK4458_REGWRITE( AK4458_DSD2, 0b00000000 );

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

  AK4458_REGWRITE( AK4458_L2CHATT, 0xFF );
  AK4458_REGWRITE( AK4458_R2CHATT, 0xFF );
  AK4458_REGWRITE( AK4458_L3CHATT, 0xFF );
  AK4458_REGWRITE( AK4458_R3CHATT, 0xFF );
  AK4458_REGWRITE( AK4458_L4CHATT, 0xFF );
  AK4458_REGWRITE( AK4458_R4CHATT, 0xFF );

  // Release Reset by rewriting Control1
  /* Control 1 (Address: 0x00)
   * bit[0]   : RSTN: Internal Timing Reset                           :   1 Normal Operation
   * bit[3:1] : DIF2-0: Audio Data Interface Modes                    : 110 Mode 18
   * bit[7]   : ACKS: Master Clock Frequency Auto Setting Mode Enable :   0 Manual Setting Mode
   */
  AK4458_REGWRITE( AK4458_CONTROL1, 0b00001101 );
}

//==============================================================================
/*! Sends the current addon configuration. 
 */
void sendAddOnConfiguration( void )
{
  String httpResponse = "";
  httpResponse += "HTTP/1.1 200 OK\r\n";
  httpResponse += "Content-type:text/plain\r\n\r\n";

  if( SPIFFS.exists( presetAddonCfgFile[Settings.currentPreset] ) )
  {
    fileAddOnConfig = SPIFFS.open( presetAddonCfgFile[Settings.currentPreset], "r" );
    if( fileAddOnConfig )
    {
      size_t len = fileAddOnConfig.size();
      int cntr = 0;
      while( cntr < len )
      {
        byte byteRead;
        fileAddOnConfig.read( &byteRead, 1 );
        httpResponse += byte2string2( byteRead );
        cntr++;
      }
      fileAddOnConfig.close();
    }
  }

  httpResponse += "\r\n";
  client.println( httpResponse );            
}

//==============================================================================
/*! Write default values to settings.ini
 *
 */
void writeDefaultSettings( void )
{
  File fileSettings = SPIFFS.open( "/settings.ini", "w" );
  // Allocate a temporary JsonDocument
  // Don't forget to change the capacity to match your requirements.
  // Use arduinojson.org/assistant to compute the capacity.
  StaticJsonDocument<256> jsonSettings;
  jsonSettings["pid"] = 0x01;
  jsonSettings["ssid"] = "";
  jsonSettings["pwd"] = "";
  jsonSettings["aid"] = ADDON_CUSTOM;
  jsonSettings["preset"] = 0x00;
  jsonSettings["version"] = VERSION_STR;
  // Serialize JSON to file
  if( serializeJson( jsonSettings, fileSettings ) == 0 )
    Serial.println( "Failed to write to file" );
  fileSettings.close();
  Settings.pid = jsonSettings["pid"];
  Settings.ssid = jsonSettings["ssid"].as<String>();
  Settings.password = jsonSettings["pwd"].as<String>();
  Settings.addonid = jsonSettings["aid"];
  Settings.currentPreset = jsonSettings["preset"];
  Settings.version = jsonSettings["version"].as<String>();
}

//==============================================================================
/*! Set up the addon. 
 *
 */
void setupAddOn( void )
{
  if( SPIFFS.exists( presetAddonCfgFile[Settings.currentPreset] ) )
  {
    fileAddOnConfig = SPIFFS.open( presetAddonCfgFile[Settings.currentPreset], "r" );
    if( fileAddOnConfig )
    {
      size_t len = fileAddOnConfig.size();
      
      if( len > 3 )
      {
        byte readBytes[4];
        fileAddOnConfig.read( readBytes, 4 );
        Wire.beginTransmission( readBytes[1]>>1 ); //ADDONB_SPDIFMUX_ADDR
        Wire.write( readBytes[2] ); // regaddr
        Wire.write( readBytes[3] ); // data
        Wire.endTransmission( true );  

        /*Serial.print( readBytes[1], HEX );
        Serial.print( " " );
        Serial.print( readBytes[2], HEX );
        Serial.print( " " );
        Serial.println( readBytes[3], HEX );
        Serial.print( " " );*/
      }
      fileAddOnConfig.close();
    }
  }            
}

//==============================================================================
/*! Arduino Setup
 *
 */
void setup( void )
{
  Serial.begin(115200);
  Serial.println( "aurora Debug" );
  Serial.println( VERSION_STR );

  if( !SPIFFS.begin( FORMAT_SPIFFS_IF_FAILED ) )
  {
    Serial.println( "An Error has occurred while mounting SPIFFS" );
    return;
  }
  Serial.print( "Free disk space: " );
  Serial.print( (SPIFFS.totalBytes() - SPIFFS.usedBytes()) / 1024 );
  Serial.println( "KiB" );

  Settings.pid = 0x01;
  Settings.ssid = "";
  Settings.password = "";
  Settings.addonid = ADDON_CUSTOM;

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
    {
      Serial.println( "Settings.ini corrupted" );
      fileSettings.close();
      bool formatted = SPIFFS.format();
      if( formatted )
      {
        Serial.println( "Rewriting settings.ini" );
        writeDefaultSettings();
      }
      else
        Serial.println( "Error formatting" );
    }  
    else
    {
      Settings.pid = jsonSettings["pid"];
      Settings.ssid = jsonSettings["ssid"].as<String>();
      Settings.password = jsonSettings["pwd"].as<String>();
      Settings.addonid = jsonSettings["aid"];
      Settings.currentPreset = jsonSettings["preset"];
      Settings.version = jsonSettings["version"].as<String>();
      fileSettings.close();
      if( Settings.version != VERSION_STR )
      {
        Serial.println( "New firmware, reformatting fs" );
        bool formatted = SPIFFS.format();
        if( formatted )
        {
          Serial.println( "Rewriting settings.ini" );
          writeDefaultSettings();
        }
        else
          Serial.println( "Error formatting" );
      }
    }
  }
  else
  {
    Serial.println( "Settings.ini not found, rewriting" );
    writeDefaultSettings();
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

  Serial.print( "Connecting to \"" );
  Serial.print( Settings.ssid.c_str() );
  Serial.println( "\"" );
  WiFi.begin( Settings.ssid.c_str(), Settings.password.c_str() );

  int cntrConnect = 0;
  if( Settings.ssid.length() > 0 )
  {
    while( (WiFi.waitForConnectResult() != WL_CONNECTED) && (cntrConnect < 3) )
    {
      Serial.println("WiFi Connection Failed! Trying again..");
      delay(100);
      cntrConnect++;
    }
  }
  
  // print the ESP32 IP-Address
  Serial.print( "Soft AP IP:" );
  Serial.println( WiFi.softAPIP() );
  Serial.print( "Local IP:" );
  Serial.println( WiFi.localIP() );
  Serial.println( WiFi.getHostname() );

  server.begin();  

  Wire.begin( I2C_SDA_PIN, I2C_SCL_PIN );
  Wire.setClock( 100000 );

  //----------------------------------------------------------------------------
  //--- Download program to DSP
  //----------------------------------------------------------------------------
  uploadDspFirmware();

  //----------------------------------------------------------------------------
  //--- Download user parameter to DSP
  //----------------------------------------------------------------------------
  uploadDspParameter();

  //----------------------------------------------------------------------------
  //--- Configure ADC
  //----------------------------------------------------------------------------
  Serial.println( "Config ADC" );
  configADC();

  //----------------------------------------------------------------------------
  //--- Configure DAC
  //----------------------------------------------------------------------------
  Serial.println( "Config DAC" );
  configDAC();

  //----------------------------------------------------------------------------
  //--- Configure MUX on AddOnB
  //----------------------------------------------------------------------------
  if( Settings.addonid == ADDON_B )
  {
    Serial.println( "Config MUX" );
 
    Wire.beginTransmission( ADDONB_SPDIFMUX_ADDR );
    Wire.write( 0x03 );
    Wire.write( 0x00 );
    Wire.endTransmission( true );

    setupAddOn();
  }
  
  //----------------------------------------------------------------------------
  //--- Start OTA
  //----------------------------------------------------------------------------
  // Port defaults to 3232
  // ArduinoOTA.setPort(3232);
#if 0
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
#endif

  webota.init( 9999, "/webota" );

  wifiStatus = STATE_WIFI_IDLE;

  Serial.println( "Ready" );

}

//==============================================================================
/*! Handle any HTTP request.
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
    String currentLine = "";                // make a string to hold incoming data from the client
    
    while( client.connected() )             // loop while the client's connected
    {  
      if( client.available() )              // if there's bytes to read from the client,
      {  
        char c = client.read();             // read a byte, then

        if(c != '\r')   // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine

        if (c == '\n')                     // if the byte is a newline character
        {
          //Serial.println( currentLine );
          if( waitForData )
          {
            //-----------------------------------------------------------------
            //--- Receiving new parameters
            //-----------------------------------------------------------------
            if( wifiStatus == STATE_WIFI_RECEIVE_PARAMETER )
            {
              receivedPostRequest += currentLine;

              if( receivedPostRequest.length() > contentLength )
              {
                int sentBytes = 0;
                while( sentBytes + 12 < currentLine.length() )
                {
                  String strReg = currentLine.substring( sentBytes + 0, sentBytes + 4 );
                  String strData = currentLine.substring( sentBytes + 4, sentBytes + 12 );
                  Serial.println( strReg );
                  Serial.println( strData );
                  uint16_t reg = (uint16_t)strtoul( strReg.c_str(), NULL, 16 );
                  uint32_t data = (uint32_t)strtoul( strData.c_str(), NULL, 16 );

                  byte val[4];
                  val[0] = (data >> 24 ) & 0xFF;
                  val[1] = (data >> 16 ) & 0xFF;
                  val[2] = (data >> 8 ) & 0xFF;
                  val[3] = data & 0xFF;
                  ADAU1452_WRITE_BLOCK( reg, val, 4 );         

                  sentBytes += 12;
                } 

                String httpResponse = "";
                httpResponse += "HTTP/1.1 200 OK\r\n";
                httpResponse += "Content-type:text/plain\r\n\r\n";
                httpResponse += "ACK";
                httpResponse += "\r\n";
                client.println( httpResponse );
          
                waitForData = false;
                wifiStatus = STATE_WIFI_IDLE;
                client.stop();
              }
            }

            //-----------------------------------------------------------------
            //--- Receiving new DSP firmware block
            //-----------------------------------------------------------------
            else if( wifiStatus == STATE_WIFI_DSPFW )
            {
              receivedPostRequest += currentLine;
              if( receivedPostRequest.length() > contentLength )
              {
                receivedPostRequest = receivedPostRequest.substring( 0, receivedPostRequest.length()-1 );
                totalBytesReceived += receivedPostRequest.length();

                int offset = 0;
                Serial.print( "Writing to file..." );
                while( offset < receivedPostRequest.length() )
                {
                  String str = receivedPostRequest.substring( offset, offset + 2 );
                  uint8_t rxByte = (uint8_t)strtoul( str.c_str(), NULL, 16 );
                  size_t len = fileDspProgram.write( &rxByte, 1 );
                  if( len != 1 )
                    Serial.println( "[ERROR] Writing to dspfw.hex" );
                  offset += 2;
                }
                Serial.println("OK");
                fileDspProgram.flush();

                Serial.print( "Received bytes:" );
                Serial.println( receivedPostRequest.length() );
                receivedPostRequest = "";

                String httpResponse = "";
                httpResponse += "HTTP/1.1 200 OK\r\n";
                httpResponse += "Content-type:text/plain\r\n\r\n";
                httpResponse += "ACK";
                httpResponse += "\r\n";
                client.println( httpResponse );

                client.stop();
                waitForData = false;
              }
              //currentLine = "";
            }

            //-----------------------------------------------------------------
            //--- Receiving new DSP parameter block
            //-----------------------------------------------------------------
            else if( wifiStatus == STATE_WIFI_RECEIVE_DSPPARAM )
            {
              receivedPostRequest += currentLine;
              if( receivedPostRequest.length() > contentLength )
              {
                receivedPostRequest = receivedPostRequest.substring( 0, receivedPostRequest.length()-1 );
                totalBytesReceived += receivedPostRequest.length();

                int offset = 0;
                Serial.print( "Writing to file..." );
                while( offset < receivedPostRequest.length() )
                {
                  String str = receivedPostRequest.substring( offset, offset + 2 );
                  uint8_t rxByte = (uint8_t)strtoul( str.c_str(), NULL, 16 );
                  size_t len = fileDspParams.write( &rxByte, 1 );
                  if( len != 1 )
                    Serial.println( "[ERROR] Writing to " + presetDspparamFile[Settings.currentPreset] );
                  offset += 2;
                }
                Serial.println("OK");
                fileDspParams.flush();

                Serial.print( "Received bytes:" );
                Serial.println( receivedPostRequest.length() );
                receivedPostRequest = "";

                String httpResponse = "";
                httpResponse += "HTTP/1.1 200 OK\r\n";
                httpResponse += "Content-type:text/plain\r\n\r\n";
                httpResponse += "ACK";
                httpResponse += "\r\n";
                client.println( httpResponse );

                client.stop();
                waitForData = false;
              }
              //currentLine = "";
            }

            //-----------------------------------------------------------------
            //--- Receiving new User parameter block
            //-----------------------------------------------------------------
            else if( wifiStatus == STATE_WIFI_RECEIVE_USERPARAM )
            {
              receivedPostRequest += currentLine;
              if( receivedPostRequest.length() > contentLength )
              {
                receivedPostRequest = receivedPostRequest.substring( 0, receivedPostRequest.length()-1 );
                totalBytesReceived += receivedPostRequest.length();

                int offset = 0;
                Serial.print( "Writing to file..." );
                while( offset < receivedPostRequest.length() )
                {
                  String str = receivedPostRequest.substring( offset, offset + 2 );
                  uint8_t rxByte = (uint8_t)strtoul( str.c_str(), NULL, 16 );
                  size_t len = fileUserParams.write( &rxByte, 1 );
                  if( len != 1 )
                    Serial.println( "[ERROR] Writing to " + presetUsrparamFile[Settings.currentPreset] );
                  offset += 2;
                }
                Serial.println("OK");
                fileUserParams.flush();

                Serial.print( "Received bytes:" );
                Serial.println( receivedPostRequest.length() );
                receivedPostRequest = "";

                String httpResponse = "";
                httpResponse += "HTTP/1.1 200 OK\r\n";
                httpResponse += "Content-type:text/plain\r\n\r\n";
                httpResponse += "ACK";
                httpResponse += "\r\n";
                client.println( httpResponse );

                client.stop();
                waitForData = false;
              }
              //currentLine = "";
            }
            
            //-----------------------------------------------------------------
            //--- 
            //-----------------------------------------------------------------
            else if( wifiStatus == STATE_WIFI_RECEIVE_CONFIG )
            {
              receivedPostRequest += currentLine;

              if( receivedPostRequest.length() > contentLength )
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

                WiFi.disconnect();
                Serial.println( "Connecting to new network..." );
                WiFi.begin( Settings.ssid.c_str(), Settings.password.c_str() );
                int cntrConnect = 0;
                while( WiFi.waitForConnectResult() != WL_CONNECTED && cntrConnect < 3 )
                {
                  Serial.println( "WiFi Connection Failed! Trying again..." );
                  cntrConnect++;
                }
                Serial.println( WiFi.localIP() );

                String httpResponse = "";
                httpResponse += "HTTP/1.1 200 OK\r\n";
                httpResponse += "Content-type:text/plain\r\n\r\n";
                if( WiFi.status() == WL_CONNECTED )
                  httpResponse += "CONNECTED";
                else
                  httpResponse += "FAILED";
                httpResponse += "?";
                httpResponse += WiFi.localIP().toString();
                httpResponse += "\r\n";
                client.println( httpResponse );
                
                client.stop();
                waitForData = false;
                Serial.println( "OK" );
              }
                
            }

            //-----------------------------------------------------------------
            //--- 
            //-----------------------------------------------------------------
            else if( wifiStatus == STATE_WIFI_RECEIVE_PID )
            {
              receivedPostRequest += currentLine;

              if( receivedPostRequest.length() > contentLength )
              {
                receivedPostRequest = receivedPostRequest.substring( 0, receivedPostRequest.length()-1 );

                Settings.pid = (byte)strtoul( receivedPostRequest.c_str(), NULL, 16 );

                Serial.print( "PID: " );
                Serial.println( Settings.pid, HEX );

                saveSettings();

                String httpResponse = "";
                httpResponse += "HTTP/1.1 200 OK\r\n";
                httpResponse += "Content-type:text/plain\r\n\r\n";
                httpResponse += "ACK";
                httpResponse += "\r\n";
                client.println( httpResponse );

                client.stop();
                waitForData = false;
                wifiStatus = STATE_WIFI_IDLE;
              }
            }

            //-----------------------------------------------------------------
            //--- Receiving new AddOn-ID
            //-----------------------------------------------------------------
            else if( wifiStatus == STATE_WIFI_RECEIVE_AID )
            {
              receivedPostRequest += currentLine;

              if( receivedPostRequest.length() > contentLength )
              {
                receivedPostRequest = receivedPostRequest.substring( 0, receivedPostRequest.length()-1 );

                Settings.addonid = (uint32_t)strtoul( receivedPostRequest.c_str(), NULL, 16 );

                Serial.print( "AID: " );
                Serial.println( Settings.addonid, HEX );

                saveSettings();

                String httpResponse = "";
                httpResponse += "HTTP/1.1 200 OK\r\n";
                httpResponse += "Content-type:text/plain\r\n\r\n";
                httpResponse += "ACK";
                httpResponse += "\r\n";
                client.println( httpResponse );

                client.stop();
                waitForData = false;
                wifiStatus = STATE_WIFI_IDLE;
              }
            }
            
            //-----------------------------------------------------------------
            //--- Receiving new preset selection
            //-----------------------------------------------------------------
            else if( wifiStatus == STATE_WIFI_RECEIVE_PRESETID )
            {
              receivedPostRequest += currentLine;

              if( receivedPostRequest.length() > contentLength )
              {
                receivedPostRequest = receivedPostRequest.substring( 0, receivedPostRequest.length()-1 );

                Settings.currentPreset = (byte)strtoul( receivedPostRequest.c_str(), NULL, 16 );
                if( Settings.currentPreset > 3 )
                  Settings.currentPreset = 3;

                uploadDspParameter();
                setupAddOn();

                String httpResponse = "";
                httpResponse += "HTTP/1.1 200 OK\r\n";
                httpResponse += "Content-type:text/plain\r\n\r\n";
                httpResponse += "ACK";
                httpResponse += "\r\n";
                client.println( httpResponse );
                Serial.print( "[OK]" );

                client.stop();
                waitForData = false;
                wifiStatus = STATE_WIFI_IDLE;
              }
            }

            //-----------------------------------------------------------------
            //--- Receiving I2C write sequence
            //-----------------------------------------------------------------
            else if( wifiStatus == STATE_WIFI_RECEIVE_WRITEI2C )
            {
              receivedPostRequest += currentLine;

              if( receivedPostRequest.length() > contentLength )
              {
                receivedPostRequest = receivedPostRequest.substring( 0, receivedPostRequest.length()-1 );

                if( receivedPostRequest.length() >= 6 )
                {
                  int offset = 0;
                  String str = receivedPostRequest.substring( offset, offset + 2 );
                  uint8_t addr = (uint8_t)strtoul( str.c_str(), NULL, 16 );
                  offset += 2;
                  str = receivedPostRequest.substring( offset, offset + 2 );
                  byte regaddr = (byte)strtoul( str.c_str(), NULL, 16 );
                  offset += 2;
                  str = receivedPostRequest.substring( offset, offset + 2 );
                  byte data = (byte)strtoul( str.c_str(), NULL, 16 );
                  offset += 2;

                  Wire.beginTransmission( addr>>1 );
                  Wire.write( regaddr );
                  Wire.write( data );
                  Wire.endTransmission( true );

                  Serial.print( "I2C: " );
                  Serial.print( addr, HEX );
                  Serial.print( " " );
                  Serial.print( regaddr, HEX );
                  Serial.print( " " );
                  Serial.println( data, HEX );
                  Serial.print( " " );

                  String httpResponse = "";
                  httpResponse += "HTTP/1.1 200 OK\r\n";
                  httpResponse += "Content-type:text/plain\r\n\r\n";
                  httpResponse += "ACK";
                  httpResponse += "\r\n";
                  client.println( httpResponse );
                  Serial.println( "[OK]" );

                  client.stop();
                  waitForData = false;
                  wifiStatus = STATE_WIFI_IDLE;
                }

              }
            }

            //-----------------------------------------------------------------
            //--- Receiving a new addon configuration
            //-----------------------------------------------------------------
            else if( wifiStatus == STATE_WIFI_POST_ADDONCONFIG )
            {
              receivedPostRequest += currentLine;

              if( receivedPostRequest.length() > contentLength )
              {
                receivedPostRequest = receivedPostRequest.substring( 0, receivedPostRequest.length()-1 );

                if( receivedPostRequest.length() >= 6 )
                {
                  int offset = 0;
                  String str = receivedPostRequest.substring( offset, offset + 2 );
                  uint8_t addr = (uint8_t)strtoul( str.c_str(), NULL, 16 );
                  offset += 2;
                  str = receivedPostRequest.substring( offset, offset + 2 );
                  byte regaddr = (byte)strtoul( str.c_str(), NULL, 16 );
                  offset += 2;
                  str = receivedPostRequest.substring( offset, offset + 2 );
                  byte data = (byte)strtoul( str.c_str(), NULL, 16 );
                  offset += 2;

                  bool haveError = false;
                  if( SPIFFS.exists( presetAddonCfgFile[Settings.currentPreset] ) )
                  {
                    if( !SPIFFS.remove( presetAddonCfgFile[Settings.currentPreset] ) )
                    {
                      Serial.println( "<ERR> Delete file" ); 
                      haveError = true;
                    } 
                  }

                  fileAddOnConfig = SPIFFS.open( presetAddonCfgFile[Settings.currentPreset], "w" );
                  if( !fileAddOnConfig )
                  {
                    Serial.println( "<ERR> Open file" ); 
                    haveError = true;
                  } 
                  else
                  {
                    byte writeBytes[4];
                    writeBytes[0] = 3;
                    writeBytes[1] = addr;
                    writeBytes[2] = regaddr;
                    writeBytes[3] = data;
                    /*
                    Serial.print( "I2C: " );
                    Serial.print( addr, HEX );
                    Serial.print( " " );
                    Serial.print( regaddr, HEX );
                    Serial.print( " " );
                    Serial.println( data, HEX );
                    Serial.print( " " );
                    */
                    size_t len = fileAddOnConfig.write( writeBytes, 4 );
                    if( len != 4 )
                    {
                      Serial.println( "<ERR> Write file" ); 
                      haveError = true;
                    }

                    fileAddOnConfig.flush();
                    fileAddOnConfig.close();
                  }

                  if( !haveError )
                  {
                    String httpResponse = "";
                    httpResponse += "HTTP/1.1 200 OK\r\n";
                    httpResponse += "Content-type:text/plain\r\n\r\n";
                    httpResponse += "ACK";
                    httpResponse += "\r\n";
                    client.println( httpResponse );
                    Serial.println( "[OK]" );
                  }
                  else
                  {
                    String httpResponse = "";
                    httpResponse += "HTTP/1.1 200 OK\r\n";
                    httpResponse += "Content-type:text/plain\r\n\r\n";
                    httpResponse += "ERR";
                    httpResponse += "\r\n";
                    client.println( httpResponse );
                  }
                  client.stop();
                  waitForData = false;
                  wifiStatus = STATE_WIFI_IDLE;
                }
              }
            }

            //-----------------------------------------------------------------
            //--- Request of addon configuration
            //-----------------------------------------------------------------
            else if( wifiStatus == STATE_WIFI_GET_ADDONCONFIG )
            {
              receivedPostRequest += currentLine;
              sendAddOnConfiguration();
              client.stop();
              waitForData = false;
              wifiStatus = STATE_WIFI_IDLE;
            }
            

            currentLine = "";
            //Serial.println( cntrPackets );
            
          }

          else
          {
            //-----------------------------------------------------------------
            //--- New single dsp parameter sent
            //-----------------------------------------------------------------
            if( currentLine.startsWith("POST /parameter") )
            {
              Serial.println( "POST /parameter" );
              receivedPostRequest = "";
              wifiStatus = STATE_WIFI_RECEIVE_PARAMETER;
              currentLine = "";
              //cntrPackets++;
            }

            //-----------------------------------------------------------------
            //--- Request of PID
            //-----------------------------------------------------------------
            else if( currentLine.startsWith("GET /pid") )
            {
              Serial.println( "GET /pid" );
              String httpResponse = "";
              httpResponse += "HTTP/1.1 200 OK\r\n";
              httpResponse += "Content-type:text/plain\r\n\r\n";
              httpResponse += String( Settings.pid );
              httpResponse += "\r\n";
              client.println( httpResponse );
              client.stop();
              currentLine = "";
              //cntrPackets++;
            }

            //-----------------------------------------------------------------
            //--- New PID
            //-----------------------------------------------------------------
            else if( currentLine.startsWith("POST /pid") )
            {
              Serial.println( "POST /pid" );
              receivedPostRequest = "";
              wifiStatus = STATE_WIFI_RECEIVE_PID;
              currentLine = "";
              //cntrPackets++;
            }

            //-----------------------------------------------------------------
            //--- New dsp firmware data block
            //-----------------------------------------------------------------
            else if( currentLine.startsWith("PUT /dspfw") )
            {
              Serial.println( "PUT /dspfw" );
              receivedPostRequest = "";
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

              }
              if( wifiStatus != STATE_WIFI_DSPFW )
                totalBytesReceived = 0;
              wifiStatus = STATE_WIFI_DSPFW;
              currentLine = "";
              //cntrPackets++;
            }

            //-----------------------------------------------------------------
            //--- Finish dsp firmware file transfer
            //-----------------------------------------------------------------
            else if( currentLine.startsWith("GET /finishdspfw") )
            {
              Serial.println( "GET /finishdspfw" );
              fileDspProgram.flush();
              fileDspProgram.close();

              if( SPIFFS.exists( presetDspparamFile[Settings.currentPreset] ) )
              {
                if( SPIFFS.remove( presetDspparamFile[Settings.currentPreset] ) )
                  Serial.println( presetDspparamFile[Settings.currentPreset] + " deleted" );
                else
                  Serial.println( "[ERROR] Deleting " + presetDspparamFile[Settings.currentPreset] + " failed." );
              }

              for( int p = 0; p < NUMPRESETS; p++ )
              {
                if( SPIFFS.exists( presetDspparamFile[p] ) )
                {
                  if( SPIFFS.remove( presetDspparamFile[p] ) )
                    Serial.println( presetDspparamFile[p] + " deleted" );
                  else
                    Serial.println( "[ERROR] Deleting " + presetDspparamFile[p] );
                }

                if( SPIFFS.exists( presetUsrparamFile[p] ) )
                {
                  if( SPIFFS.remove( presetUsrparamFile[p] ) )
                    Serial.println( presetUsrparamFile[p] + " deleted" );
                  else
                    Serial.println( "[ERROR] Deleting " + presetUsrparamFile[p] );
                }
              }

              String httpResponse = "";
              httpResponse += "HTTP/1.1 200 OK\r\n";
              httpResponse += "Content-type:text/plain\r\n\r\n";
              httpResponse += String( totalBytesReceived );
              httpResponse += "\r\n";
              client.println( httpResponse );
              client.stop();
              Serial.println( totalBytesReceived );
              wifiStatus = STATE_WIFI_IDLE;
              totalBytesReceived = 0;
              currentLine = "";
              //cntrPackets++;
            }

            //-----------------------------------------------------------------
            //--- New dsp parameter data block
            //-----------------------------------------------------------------
            else if( currentLine.startsWith("PUT /dspparam") )
            {
              Serial.println( "PUT /dspparam" );
              receivedPostRequest = "";
              if( wifiStatus != STATE_WIFI_RECEIVE_DSPPARAM )                   // start a new transfer
              {
                String fileName = presetDspparamFile[Settings.currentPreset];

                if( SPIFFS.exists( fileName ) )
                {
                  if( SPIFFS.remove( fileName ) )
                    Serial.println( fileName + " deleted" );
                  else
                    Serial.println( "[ERROR] Deleting " + fileName );
                }

                Serial.println( "Writing " + fileName );

                //fileDspParams = SPIFFS.open( "/dspparam.hex", "w" );
                fileDspParams = SPIFFS.open( fileName, "w" );
                if( !fileDspParams )
                  Serial.println( "[ERROR] Opening " + fileName + " failed." );
                else
                  Serial.println( "Opened " + fileName );

                totalBytesReceived = 0;
              }
                
              wifiStatus = STATE_WIFI_RECEIVE_DSPPARAM;
              currentLine = "";
              //cntrPackets++;
            }

            //-----------------------------------------------------------------
            //--- Finish dsp parameter file transfer
            //-----------------------------------------------------------------
            else if( currentLine.startsWith("GET /finishdspparameter") )
            {
              Serial.println( "GET /finishdspparameter" );
              fileDspParams.flush();
              fileDspParams.close();
              String httpResponse = "";
              httpResponse += "HTTP/1.1 200 OK\r\n";
              httpResponse += "Content-type:text/plain\r\n\r\n";
              httpResponse += String( totalBytesReceived );
              httpResponse += "\r\n";
              client.println( httpResponse );
              client.stop();
              Serial.println( totalBytesReceived );
              wifiStatus = STATE_WIFI_IDLE;
              totalBytesReceived = 0;
              currentLine = "";
              //cntrPackets++;
            }

            //-----------------------------------------------------------------
            //--- New user parameter block
            //-----------------------------------------------------------------
            else if( currentLine.startsWith("PUT /userparam") )
            {
              Serial.println( "PUT /userparam" );
              receivedPostRequest = "";
              if( wifiStatus != STATE_WIFI_RECEIVE_USERPARAM )                  // start a new transfer
              {
                String fileName = presetUsrparamFile[Settings.currentPreset];

                if( SPIFFS.exists( fileName ) )
                {
                  if( SPIFFS.remove( fileName ) )
                    Serial.println( fileName + " deleted" );
                  else
                    Serial.println( "[ERROR] Deleting " + fileName );
                }

                Serial.println( "Writing " + fileName );
                fileUserParams = SPIFFS.open( fileName, "w" );
                if( !fileUserParams )
                  Serial.println( "[ERROR] Failed to open " + fileName );
                else
                  Serial.println( "Opened " + fileName );

                totalBytesReceived = 0;
              }
              wifiStatus = STATE_WIFI_RECEIVE_USERPARAM;
              currentLine = "";
              //cntrPackets++;
            }

            //-----------------------------------------------------------------
            //--- Finish user parameters transfer
            //-----------------------------------------------------------------
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

            //-----------------------------------------------------------------
            //--- Request of AddOn-ID
            //-----------------------------------------------------------------
            else if( currentLine.startsWith("GET /aid") )
            {
              Serial.println( "GET /aid" );
              String httpResponse = "";
              httpResponse += "HTTP/1.1 200 OK\r\n";
              httpResponse += "Content-type:text/plain\r\n\r\n";
              httpResponse += String( Settings.addonid );
              httpResponse += "\r\n";
              client.println( httpResponse );
              client.stop();
              currentLine = "";
              //cntrPackets++;
            }

            //-----------------------------------------------------------------
            //--- Request of firmware version
            //-----------------------------------------------------------------
            else if( currentLine.startsWith("GET /version") )
            {
              Serial.println( "GET /version" );
              String httpResponse = "";
              httpResponse += "HTTP/1.1 200 OK\r\n";
              httpResponse += "Content-type:text/plain\r\n\r\n";
              httpResponse += VERSION_STR;
              httpResponse += "\r\n";
              client.println( httpResponse );
              client.stop();
              currentLine = "";
              //cntrPackets++;
            }

            //-----------------------------------------------------------------
            //--- New AID
            //-----------------------------------------------------------------
            else if( currentLine.startsWith("POST /aid") )
            {
              Serial.println( "POST /aid" );
              receivedPostRequest = "";
              wifiStatus = STATE_WIFI_RECEIVE_AID;
              currentLine = "";
              //cntrPackets++;
            }

            //-----------------------------------------------------------------
            //--- Request of user parameter file size
            //-----------------------------------------------------------------
            else if( currentLine.startsWith("GET /sizeuserparam") )
            {
              Serial.println( "GET /sizeuserparam" );
              String httpResponse = "";
              httpResponse += "HTTP/1.1 200 OK\r\n";
              httpResponse += "Content-type:text/plain\r\n\r\n";
              if( SPIFFS.exists( presetUsrparamFile[Settings.currentPreset] ) )
              {
                fileUserParams = SPIFFS.open( presetUsrparamFile[Settings.currentPreset], "r" );
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

            //-----------------------------------------------------------------
            //--- Request of user parameter file
            //-----------------------------------------------------------------
            else if( currentLine.startsWith("GET /userparam") )
            {
              Serial.println( "GET /userparam" );
              String httpResponse = "";
              httpResponse += "HTTP/1.1 200 OK\r\n";
              httpResponse += "Content-type:text/plain\r\n\r\n";
              if( SPIFFS.exists( presetUsrparamFile[Settings.currentPreset] ) )
              {
                fileUserParams = SPIFFS.open( presetUsrparamFile[Settings.currentPreset], "r" );
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

            //-----------------------------------------------------------------
            //--- Request of DSP firmware size
            //-----------------------------------------------------------------
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

            //-----------------------------------------------------------------
            //--- Request of DSP firmware
            //-----------------------------------------------------------------
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

            //-----------------------------------------------------------------
            //--- Receiving new Wifi Configuration
            //-----------------------------------------------------------------
            else if( currentLine.startsWith("POST /wificonfig") )
            {
              Serial.println( "POST /wificonfig" );
              receivedPostRequest = "";
              wifiStatus = STATE_WIFI_RECEIVE_CONFIG;
              currentLine = "";
              //cntrPackets++;
            }

            //-----------------------------------------------------------------
            //--- Received a ping
            //-----------------------------------------------------------------
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

            //-----------------------------------------------------------------
            //--- Preset select
            //-----------------------------------------------------------------
            else if( currentLine.startsWith("POST /preset") )
            {
              Serial.println( "POST /preset" );
              receivedPostRequest = "";
              wifiStatus = STATE_WIFI_RECEIVE_PRESETID;
              currentLine = "";
              //cntrPackets++;
            }

            //-----------------------------------------------------------------
            //--- Save preset selection
            //-----------------------------------------------------------------
            else if( currentLine.startsWith("POST /savepreset") )
            {
              Serial.println( "POST /savepreset" );
              saveSettings();
              String httpResponse = "";
              httpResponse += "HTTP/1.1 200 OK\r\n";
              httpResponse += "Content-type:text/plain\r\n\r\n";
              httpResponse += "ACK";
              httpResponse += "\r\n";
              client.println( httpResponse );
              client.stop();
              wifiStatus = STATE_WIFI_IDLE;
              currentLine = "";
              //cntrPackets++;
            }

            //-----------------------------------------------------------------
            //--- Request of current preset
            //-----------------------------------------------------------------
            else if( currentLine.startsWith("GET /currentpreset") )
            {
              Serial.println( "GET /currentpreset" );
              String httpResponse = "";
              httpResponse += "HTTP/1.1 200 OK\r\n";
              httpResponse += "Content-type:text/plain\r\n\r\n";
              httpResponse += String( Settings.currentPreset );
              httpResponse += "\r\n";
              client.println( httpResponse );
              client.stop();
              currentLine = "";
              //cntrPackets++;
            }

            //-----------------------------------------------------------------
            //--- Receiving a new i2c write sequence
            //-----------------------------------------------------------------
            else if( currentLine.startsWith( POST_WRITEI2C ) )
            {
              Serial.println( POST_WRITEI2C );
              receivedPostRequest = "";
              wifiStatus = STATE_WIFI_RECEIVE_WRITEI2C;
              currentLine = "";
              //cntrPackets++;
            }

            //-----------------------------------------------------------------
            //--- Receiving a new i2c read sequence
            //-----------------------------------------------------------------
            else if( currentLine.startsWith( POST_READI2C ) )
            {
              // NOT FINISHED YET
              Serial.println( POST_READI2C );
              receivedPostRequest = "";
              wifiStatus = STATE_WIFI_RECEIVE_READI2C;
              currentLine = "";
              //cntrPackets++;
            }

            //-----------------------------------------------------------------
            //--- Receiving a new addon configuration
            //-----------------------------------------------------------------
            else if( currentLine.startsWith( POST_ADDONCONFIG ) )
            {
              Serial.println( POST_ADDONCONFIG );
              receivedPostRequest = "";
              wifiStatus = STATE_WIFI_POST_ADDONCONFIG;
              currentLine = "";
              //cntrPackets++;
            }

            //-----------------------------------------------------------------
            //--- Request of addon configuration
            //-----------------------------------------------------------------
            else if( currentLine.startsWith( GET_ADDONCONFIG ) )
            {
              Serial.println( GET_ADDONCONFIG );
              receivedPostRequest = "";
              wifiStatus = STATE_WIFI_GET_ADDONCONFIG;
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

//==============================================================================
/* 
 * Main Loop
 */
void loop()
{

  handleHttpRequest();

  //delay( 50 );

  webota.handle();
  webota.delay( 5 );
	

}
