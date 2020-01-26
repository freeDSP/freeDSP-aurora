#include <Wire.h>
#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <SPIFFS.h>
#include "AsyncJson.h"
#include <ArduinoJson.h>

#include "AK4458.h"
#include "AK5558.h"
#include "AudioFilterFactory.h"

#define VERSION_STR 0.0.1

#define I2C_SDA_PIN 17
#define I2C_SCL_PIN 16

// DSP address on I2C bus
#define DSP_ADDR           (0x70>>1)
// ADC address on I2C bus
#define AK5558_I2C_ADDR    (0x22>>1)
// DAC address on I2C bus
#define AK4458_I2C_ADDR    (0x20>>1)
// S/P-DIF-Mux on AddOnA
#define ADDONA_SPDIFMUX_ADDR (0x82>>1)
// S/P-DIF-Mux on AddOnB
#define ADDONB_SPDIFMUX_ADDR (0x82>>1)

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
  String ssid;
  String password;
  uint32_t addonid;
  byte currentPreset;
};

tSettings Settings;

typedef uint8_t tFilterType;
typedef uint8_t tInputSelection;

struct tInput
{
  uint16_t addr;
  tInputSelection sel;
};

struct tHPLP
{
  uint16_t addr[4];
  float fc;
  tFilterType typ;
};

struct tShelving
{
  uint16_t addr;
  float gain;
  float fc;
  float slope;
};

struct tPeq
{
  uint16_t addr;
  float gain;
  float fc;
  float Q;
};

struct tPhase
{
  uint16_t addr;
  float fc;
  float Q;
  bool inv;
};

struct tDelay
{
  uint16_t addr;
  float delay;
};

struct tGain
{
  uint16_t addr;
  float gain;
};


tInput paramInputs[8];
tHPLP paramHP[8];
tShelving paramLshelv[8];
tPeq paramPeq[80];
tShelving paramHshelv[8];
tHPLP paramLP[8];
tPhase paramPhase[8];
tDelay paramDelay[8];
tGain paramGain[8];

File fileDspProgram;

float sampleRate = 48000.0;
float masterVolume = -60.0;
uint8_t currentPreset = 0;

AsyncWebServer server( 80 );

void readParams( void )
{
  for( int ii = 0; ii < 8; ii++ )
  {
    paramInputs[ii].sel = static_cast<tInputSelection>(ii);

    paramHP[ii].fc = 1000.0;
    paramHP[ii].typ = 0;
  }
}

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
 *
 */
uint32_t convertTo824( double val )
{
  double fractpart, intpart;
  uint32_t ret;

  if( val < 0.0 )
    val += 256.0;

  intpart = floor( val );
  fractpart = val - intpart;
  
  ret = ((( static_cast<uint32_t>(static_cast<int8_t>(intpart)) ) << 24) & 0xff000000)
      + ((static_cast<uint32_t>(fractpart * 16777216.0)) & 0x00ffffff);

  return ret;
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
/*! Uploads the firmware from ESP32 SPI flash to DSP.
 */
void uploadDspFirmware( void )
{
  Serial.print( "Init dsp......" );

  fileDspProgram = SPIFFS.open( "/dsp.fw" );

  uint32_t numBytesToRead = 0;
  byte byteReadMSB;
  byte byteReadLSB;
  byte byteRead;
  uint16_t regaddr;

  if( fileDspProgram )
  {
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
            delay( 500 );
          else
          {
            ADAU1452_WRITE_REGISTER( regaddr, byteReadMSB, byteReadLSB );
            if( cntr % 4096 == 0 )
              Serial.print( "." );
            /*if( cntr < 1000 )
            {
              Serial.print( cntr );
              Serial.print( " ");
              Serial.print(regaddr, HEX);
              Serial.print(" ");
              Serial.print( byteReadMSB, HEX );
              Serial.println( byteReadLSB, HEX );
            }*/
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
            /*if( cntr < 1000 )
            {
              Serial.print( cntr );
              Serial.print( " ");
              Serial.print(addr, HEX);
              Serial.print(" ");
              Serial.println(*(uint32_t*)val, HEX );
            }*/
            addr++;
          }
        }
        else
        {
          Serial.print( "[ERROR] Bad number of bytes: " );
          Serial.println( numBytesToRead );
        }
      }
    }
    int file_size = fileDspProgram.size();

    fileDspProgram.close();
    Serial.println( "[ok]" );
    Serial.print( "File size: " );
    Serial.println( file_size );
  }
  else
    Serial.println( "\n[ERROR] Failed to open file dsp.fw" );
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
  //AK4458_REGWRITE( AK4458_CONTROL1, 0b00001101 );
}

//==============================================================================
/*! Mute DAC
 */
void muteDAC( void )
{
  AK4458_REGWRITE( AK4458_CONTROL1, 0b00001100 );
}

//==============================================================================
/*! Unmute DAC
 */
void unmuteDAC( void )
{
  AK4458_REGWRITE( AK4458_CONTROL1, 0b00001101 );
}

//==============================================================================
/*! Handles the GET request for Input selection
 *
 */
void handleGetInputJson( AsyncWebServerRequest* request )
{
  Serial.println( "GET /input" );

  AsyncJsonResponse* response = new AsyncJsonResponse();

  JsonVariant& jsonResponse = response->getRoot();
  jsonResponse["chn0"] = paramInputs[0].sel;
  jsonResponse["chn1"] = paramInputs[1].sel;
  jsonResponse["chn2"] = paramInputs[2].sel;
  jsonResponse["chn3"] = paramInputs[3].sel;
  jsonResponse["chn4"] = paramInputs[4].sel;
  jsonResponse["chn5"] = paramInputs[5].sel;
  jsonResponse["chn6"] = paramInputs[6].sel;
  jsonResponse["chn7"] = paramInputs[7].sel;

  response->setLength();
  request->send(response);
}

//==============================================================================
/*! Handles the GET request for High Pass parameter
 *
 */
void handleGetHpJson( AsyncWebServerRequest* request )
{
  Serial.println( "GET /hp" );

  AsyncJsonResponse* response = new AsyncJsonResponse();

  if( request->hasParam( "idx" ) )
  {
    AsyncWebParameter* idx = request->getParam(0);
    int offset = idx->value().toInt();
    Serial.println( offset );
    JsonVariant& jsonResponse = response->getRoot();
    jsonResponse["typ"] = paramHP[offset].typ;
    jsonResponse["fc"] = paramHP[offset].fc;
  }
  else
    Serial.println( "[ERROR] handleGetHpJson(): No id param" );

  response->setLength();
  request->send(response);
}

//==============================================================================
/*! Handles the GET request for Low Shelving parameter
 *
 */
void handleGetLshelvJson( AsyncWebServerRequest* request )
{
  Serial.println( "GET /lshelv" );

  AsyncJsonResponse* response = new AsyncJsonResponse();

  if( request->hasParam( "idx" ) )
  {
    AsyncWebParameter* idx = request->getParam(0);
    int offset = idx->value().toInt();
    JsonVariant& jsonResponse = response->getRoot();
    jsonResponse["gain"] = paramLshelv[offset].gain;
    jsonResponse["fc"] = paramLshelv[offset].fc;
    jsonResponse["slope"] = paramLshelv[offset].slope;
  }
  else
    Serial.println( "[ERROR] handleGetLshelvJson(): No id param" );

  response->setLength();
  request->send(response);
}

//==============================================================================
/*! Handles the GET request for PEQ parameter
 *
 */
void handleGetPeqJson( AsyncWebServerRequest* request )
{
  Serial.println( "GET /peq" );

  AsyncJsonResponse* response = new AsyncJsonResponse();

  if( request->hasParam( "idx" ) )
  {
    AsyncWebParameter* idx = request->getParam(0);
    int offset = idx->value().toInt();
    JsonVariant& jsonResponse = response->getRoot();
    jsonResponse["gain"] = paramPeq[offset].gain;
    jsonResponse["fc"] = paramPeq[offset].fc;
    jsonResponse["Q"] = paramPeq[offset].Q;
  }
  else
    Serial.println( "[ERROR] handleGetPeqJson(): No id param" );

  response->setLength();
  request->send(response);
}

//==============================================================================
/*! Handles the GET request for High Shelving parameter
 *
 */
void handleGetHshelvJson( AsyncWebServerRequest* request )
{
  Serial.println( "GET /hshelv" );

  AsyncJsonResponse* response = new AsyncJsonResponse();

  if( request->hasParam( "idx" ) )
  {
    AsyncWebParameter* idx = request->getParam(0);
    int offset = idx->value().toInt();
    JsonVariant& jsonResponse = response->getRoot();
    jsonResponse["gain"] = paramHshelv[offset].gain;
    jsonResponse["fc"] = paramHshelv[offset].fc;
    jsonResponse["slope"] = paramHshelv[offset].slope;
  }
  else
    Serial.println( "[ERROR] handleGetHshelvJson(): No id param" );

  response->setLength();
  request->send(response);
}

//==============================================================================
/*! Handles the GET request for Low Pass parameter
 *
 */
void handleGetLpJson( AsyncWebServerRequest* request )
{
  Serial.println( "GET /lp" );

  AsyncJsonResponse* response = new AsyncJsonResponse();

  if( request->hasParam( "idx" ) )
  {
    AsyncWebParameter* idx = request->getParam(0);
    int offset = idx->value().toInt();
    JsonVariant& jsonResponse = response->getRoot();
    jsonResponse["typ"] = paramLP[offset].typ;
    jsonResponse["fc"] = paramLP[offset].fc;
  }
  else
    Serial.println( "[ERROR] handleGetLpJson(): No id param" );

  response->setLength();
  request->send(response);
}

//==============================================================================
/*! Handles the GET request for Allpass parameter
 *
 */
void handleGetPhaseJson( AsyncWebServerRequest* request )
{
  Serial.println( "GET /phase" );

  AsyncJsonResponse* response = new AsyncJsonResponse();

  if( request->hasParam( "idx" ) )
  {
    AsyncWebParameter* idx = request->getParam(0);
    int offset = idx->value().toInt();
    JsonVariant& jsonResponse = response->getRoot();
    jsonResponse["Q"] = paramPhase[offset].Q;
    jsonResponse["fc"] = paramPhase[offset].fc;
  }
  else
    Serial.println( "[ERROR] handleGetPhaseJson(): No id param" );

  response->setLength();
  request->send(response);
}

//==============================================================================
/*! Handles the GET request for Delay parameter
 *
 */
void handleGetDelayJson( AsyncWebServerRequest* request )
{
  Serial.println( "GET /delay" );

  AsyncJsonResponse* response = new AsyncJsonResponse();

  if( request->hasParam( "idx" ) )
  {
    AsyncWebParameter* idx = request->getParam(0);
    int offset = idx->value().toInt();
    JsonVariant& jsonResponse = response->getRoot();
    jsonResponse["dly"] = paramDelay[offset].delay;
  }
  else
    Serial.println( "[ERROR] handleGetDelayJson(): No id param" );

  response->setLength();
  request->send(response);
}

//==============================================================================
/*! Handles the GET request for Gain parameter
 *
 */
void handleGetGainJson( AsyncWebServerRequest* request )
{
  Serial.println( "GET /gain" );

  AsyncJsonResponse* response = new AsyncJsonResponse();

  if( request->hasParam( "idx" ) )
  {
    AsyncWebParameter* idx = request->getParam(0);
    int offset = idx->value().toInt();
    JsonVariant& jsonResponse = response->getRoot();
    jsonResponse["gain"] = paramGain[offset].gain;
  }
  else
    Serial.println( "[ERROR] handleGetGainJson(): No id param" );

  response->setLength();
  request->send(response);
}

//==============================================================================
/*! Handles the GET request for Master Volume parameter
 *
 */
void handleGetMasterVolumeJson( AsyncWebServerRequest* request )
{
  Serial.println( "GET /mvol" );
  Serial.println( masterVolume );
  AsyncJsonResponse* response = new AsyncJsonResponse();
  JsonVariant& jsonResponse = response->getRoot();
  jsonResponse["vol"] = masterVolume;
  response->setLength();
  request->send(response);
}

//==============================================================================
/*! Handles the GET request for Preset selection
 *
 */
void handleGetPresetJson( AsyncWebServerRequest* request )
{
  Serial.println( "GET /preset" );

  AsyncJsonResponse* response = new AsyncJsonResponse();
  JsonVariant& jsonResponse = response->getRoot();
  jsonResponse["pre"] = currentPreset;
  response->setLength();
  request->send(response);
}


//==============================================================================
/*! Handles the POST request for Input selection
 *
 */
void handlePostInputJson( AsyncWebServerRequest* request, uint8_t* data )
{
  Serial.println( "POST /input" );
  //Serial.println( "Body:");
  //for(size_t i=0; i<len; i++)
  //  Serial.write(data[i]);
  //Serial.println();

  DynamicJsonDocument jsonDoc(1024);
  DeserializationError err = deserializeJson( jsonDoc, (const char*)data );
  if( err )
  {
    Serial.print( "[ERROR] handlePostHpJson(): Deserialization failed. " );
    Serial.println( err.c_str() );
    request->send( 404, "text/plain", "" );
    return;
  }

  JsonObject root = jsonDoc.as<JsonObject>();
  Serial.println( root["idx"].as<String>() );
  Serial.println( root["sel"].as<String>() );

  uint32_t idx = static_cast<uint32_t>(root["idx"].as<String>().toInt());
  paramInputs[idx].addr = static_cast<uint16_t>(root["addr"].as<String>().toInt());
  paramInputs[idx].sel = static_cast<tInputSelection>(root["sel"].as<String>().toInt());
       
  request->send(200, "text/plain", "");  
}

//==============================================================================
/*! Handles the POST request for High Pass parameter
 *
 */
void handlePostHpJson( AsyncWebServerRequest* request, uint8_t* data )
{
  Serial.println( "POST /hp" );
  //Serial.println( "Body:");
  //for(size_t i=0; i<len; i++)
  //  Serial.write(data[i]);
  //Serial.println();

  DynamicJsonDocument jsonDoc(1024);
  DeserializationError err = deserializeJson( jsonDoc, (const char*)data );
  if( err )
  {
    Serial.print( "[ERROR] handlePostHpJson(): Deserialization failed. " );
    Serial.println( err.c_str() );
    request->send( 404, "text/plain", "" );
    return;
  }

  JsonObject root = jsonDoc.as<JsonObject>();
  Serial.println( root["idx"].as<String>() );
  Serial.println( root["addr"].as<String>() );
  Serial.println( root["fc"].as<String>() );
  Serial.println( root["typ"].as<String>() );

  uint32_t idx = static_cast<uint32_t>(root["idx"].as<String>().toInt());
  paramHP[idx].addr[0] = static_cast<uint16_t>(root["addr0"].as<String>().toInt());
  paramHP[idx].addr[1] = static_cast<uint16_t>(root["addr1"].as<String>().toInt());
  paramHP[idx].addr[2] = static_cast<uint16_t>(root["addr2"].as<String>().toInt());
  paramHP[idx].addr[3] = static_cast<uint16_t>(root["addr3"].as<String>().toInt());
  paramHP[idx].fc = root["fc"].as<String>().toFloat();
  paramHP[idx].typ = static_cast<tFilterType>(root["typ"].as<String>().toInt());

  float a[12] = { 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0 };
  float b[12] = { 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0 };
  byte val[4];
  uint32_t floatval;
  AudioFilterFactory::makeHighPass( a, b, paramHP[idx].typ, paramHP[idx].fc, sampleRate );

  for( int ii = 0; ii < 4; ii++ )
  {
    uint16_t addr = paramHP[idx].addr[ii];
    floatval = convertTo824(b[ 3*ii + 2 ]);
    val[0] = (floatval >> 24 ) & 0xFF;
    val[1] = (floatval >> 16 ) & 0xFF;
    val[2] = (floatval >> 8 ) & 0xFF;
    val[3] =  floatval & 0xFF;
    ADAU1452_WRITE_BLOCK( addr, val, 4 );  // B2
    addr++;

    floatval = convertTo824(b[ 3*ii + 1 ]);
    val[0] = (floatval >> 24 ) & 0xFF;
    val[1] = (floatval >> 16 ) & 0xFF;
    val[2] = (floatval >> 8 ) & 0xFF;
    val[3] =  floatval & 0xFF;
    ADAU1452_WRITE_BLOCK( addr, val, 4 );  // B1
    addr++;

    floatval = convertTo824(b[ 3*ii + 0 ]);
    val[0] = (floatval >> 24 ) & 0xFF;
    val[1] = (floatval >> 16 ) & 0xFF;
    val[2] = (floatval >> 8 ) & 0xFF;
    val[3] =  floatval & 0xFF;
    ADAU1452_WRITE_BLOCK( addr, val, 4 );  // B0
    addr++;

    floatval = convertTo824(a[ 3*ii + 2 ]);
    val[0] = (floatval >> 24 ) & 0xFF;
    val[1] = (floatval >> 16 ) & 0xFF;
    val[2] = (floatval >> 8 ) & 0xFF;
    val[3] =  floatval & 0xFF;
    ADAU1452_WRITE_BLOCK( addr, val, 4 );  // A2
    addr++;
    
    floatval = convertTo824(a[ 3*ii + 1 ]);
    val[0] = (floatval >> 24 ) & 0xFF;
    val[1] = (floatval >> 16 ) & 0xFF;
    val[2] = (floatval >> 8 ) & 0xFF;
    val[3] =  floatval & 0xFF;
    ADAU1452_WRITE_BLOCK( addr, val, 4 );  // A1
    addr++;
  }
       
  request->send(200, "text/plain", "");  
}

//==============================================================================
/*! Handles the POST request for Low Shelving parameter
 *
 */
void handlePostLshelvJson( AsyncWebServerRequest* request, uint8_t* data )
{
  Serial.println( "POST /lshelv" );
  //Serial.println( "Body:");
  //for(size_t i=0; i<len; i++)
  //  Serial.write(data[i]);
  //Serial.println();

  DynamicJsonDocument jsonDoc(1024);
  DeserializationError err = deserializeJson( jsonDoc, (const char*)data );
  if( err )
  {
    Serial.print( "[ERROR] handlePostHpJson(): Deserialization failed. " );
    Serial.println( err.c_str() );
    request->send( 404, "text/plain", "" );
    return;
  }

  JsonObject root = jsonDoc.as<JsonObject>();
  Serial.println( root["idx"].as<String>() );
  Serial.println( root["addr"].as<String>() );
  Serial.println( root["gain"].as<String>() );
  Serial.println( root["fc"].as<String>() );
  Serial.println( root["slope"].as<String>() );

  uint32_t idx = static_cast<uint32_t>(root["idx"].as<String>().toInt());
  paramLshelv[idx].addr = static_cast<uint16_t>(root["addr"].as<String>().toInt());
  paramLshelv[idx].gain = root["gain"].as<String>().toFloat();
  paramLshelv[idx].fc = root["fc"].as<String>().toFloat();
  paramLshelv[idx].slope = root["slope"].as<String>().toFloat();

  float a[3];
  float b[3];
  byte val[4];
  uint32_t floatval;
  AudioFilterFactory::makeLowShelv( a, b, paramLshelv[idx].gain, paramLshelv[idx].fc, paramLshelv[idx].slope, sampleRate );

  uint16_t addr = paramLshelv[idx].addr;
  floatval = convertTo824(b[2]);
  val[0] = (floatval >> 24 ) & 0xFF;
  val[1] = (floatval >> 16 ) & 0xFF;
  val[2] = (floatval >> 8 ) & 0xFF;
  val[3] =  floatval & 0xFF;
  ADAU1452_WRITE_BLOCK( addr, val, 4 );  // B2
  addr++;

  floatval = convertTo824(b[1]);
  val[0] = (floatval >> 24 ) & 0xFF;
  val[1] = (floatval >> 16 ) & 0xFF;
  val[2] = (floatval >> 8 ) & 0xFF;
  val[3] =  floatval & 0xFF;
  ADAU1452_WRITE_BLOCK( addr, val, 4 );  // B1
  addr++;

  floatval = convertTo824(b[0]);
  val[0] = (floatval >> 24 ) & 0xFF;
  val[1] = (floatval >> 16 ) & 0xFF;
  val[2] = (floatval >> 8 ) & 0xFF;
  val[3] =  floatval & 0xFF;
  ADAU1452_WRITE_BLOCK( addr, val, 4 );  // B0
  addr++;

  floatval = convertTo824(a[2]);
  val[0] = (floatval >> 24 ) & 0xFF;
  val[1] = (floatval >> 16 ) & 0xFF;
  val[2] = (floatval >> 8 ) & 0xFF;
  val[3] =  floatval & 0xFF;
  ADAU1452_WRITE_BLOCK( addr, val, 4 );  // A2
  addr++;
  
  floatval = convertTo824(a[1]);
  val[0] = (floatval >> 24 ) & 0xFF;
  val[1] = (floatval >> 16 ) & 0xFF;
  val[2] = (floatval >> 8 ) & 0xFF;
  val[3] =  floatval & 0xFF;
  ADAU1452_WRITE_BLOCK( addr, val, 4 );  // A1
       
  request->send(200, "text/plain", "");  
}

//==============================================================================
/*! Handles the POST request for PEQ parameter
 *
 */
void handlePostPeqJson( AsyncWebServerRequest* request, uint8_t* data )
{
  Serial.println( "POST /peq" );
  //Serial.println( "Body:");
  //for(size_t i=0; i<len; i++)
  //  Serial.write(data[i]);
  //Serial.println();

  DynamicJsonDocument jsonDoc(1024);
  DeserializationError err = deserializeJson( jsonDoc, (const char*)data );
  if( err )
  {
    Serial.print( "[ERROR] handlePostPeqJson(): Deserialization failed. " );
    Serial.println( err.c_str() );
    request->send( 404, "text/plain", "" );
    return;
  }

  JsonObject root = jsonDoc.as<JsonObject>();
  Serial.println( root["idx"].as<String>() );
  Serial.println( root["addr"].as<String>() );
  Serial.println( root["gain"].as<String>() );
  Serial.println( root["fc"].as<String>() );
  Serial.println( root["Q"].as<String>() );

  uint32_t idx = static_cast<uint32_t>(root["idx"].as<String>().toInt());
  paramPeq[idx].addr = static_cast<uint16_t>(root["addr"].as<String>().toInt());
  paramPeq[idx].gain = root["gain"].as<String>().toFloat();
  paramPeq[idx].fc = root["fc"].as<String>().toFloat();
  paramPeq[idx].Q = root["Q"].as<String>().toFloat();

  float a[3];
  float b[3];
  byte val[4];
  uint32_t floatval;
  AudioFilterFactory::makeParametricEQ( a, b, paramPeq[idx].gain, paramPeq[idx].fc, paramPeq[idx].Q, sampleRate );

  uint32_t addr = paramPeq[idx].addr;
  floatval = convertTo824(b[2]);
  val[0] = (floatval >> 24 ) & 0xFF;
  val[1] = (floatval >> 16 ) & 0xFF;
  val[2] = (floatval >> 8 ) & 0xFF;
  val[3] =  floatval & 0xFF;
  ADAU1452_WRITE_BLOCK( addr, val, 4 );  // B2
  Serial.println( addr );
  addr++;

  floatval = convertTo824(b[1]);
  val[0] = (floatval >> 24 ) & 0xFF;
  val[1] = (floatval >> 16 ) & 0xFF;
  val[2] = (floatval >> 8 ) & 0xFF;
  val[3] =  floatval & 0xFF;
  ADAU1452_WRITE_BLOCK( addr, val, 4 );  // B1
  Serial.println( addr );
  addr++;

  floatval = convertTo824(b[0]);
  val[0] = (floatval >> 24 ) & 0xFF;
  val[1] = (floatval >> 16 ) & 0xFF;
  val[2] = (floatval >> 8 ) & 0xFF;
  val[3] =  floatval & 0xFF;
  ADAU1452_WRITE_BLOCK( addr, val, 4 );  // B0
  Serial.println( addr );
  addr++;

  floatval = convertTo824(a[2]);
  val[0] = (floatval >> 24 ) & 0xFF;
  val[1] = (floatval >> 16 ) & 0xFF;
  val[2] = (floatval >> 8 ) & 0xFF;
  val[3] =  floatval & 0xFF;
  ADAU1452_WRITE_BLOCK( addr, val, 4 );  // A2
  Serial.println( addr );
  addr++;
  
  floatval = convertTo824(a[1]);
  val[0] = (floatval >> 24 ) & 0xFF;
  val[1] = (floatval >> 16 ) & 0xFF;
  val[2] = (floatval >> 8 ) & 0xFF;
  val[3] =  floatval & 0xFF;
  ADAU1452_WRITE_BLOCK( addr, val, 4 );  // A1
  Serial.println( addr );

  request->send(200, "text/plain", "");  
}

//==============================================================================
/*! Handles the POST request for High Shelving parameter
 *
 */
void handlePostHshelvJson( AsyncWebServerRequest* request, uint8_t* data )
{
  Serial.println( "POST /hshelv" );
  //Serial.println( "Body:");
  //for(size_t i=0; i<len; i++)
  //  Serial.write(data[i]);
  //Serial.println();

  DynamicJsonDocument jsonDoc(1024);
  DeserializationError err = deserializeJson( jsonDoc, (const char*)data );
  if( err )
  {
    Serial.print( "[ERROR] handlePostHpJson(): Deserialization failed. " );
    Serial.println( err.c_str() );
    request->send( 404, "text/plain", "" );
    return;
  }

  JsonObject root = jsonDoc.as<JsonObject>();
  Serial.println( root["idx"].as<String>() );
  Serial.println( root["addr"].as<String>() );
  Serial.println( root["gain"].as<String>() );
  Serial.println( root["fc"].as<String>() );
  Serial.println( root["slope"].as<String>() );

  uint32_t idx = static_cast<uint32_t>(root["idx"].as<String>().toInt());
  paramHshelv[idx].addr = static_cast<uint16_t>(root["addr"].as<String>().toInt());
  paramHshelv[idx].gain = root["gain"].as<String>().toFloat();
  paramHshelv[idx].fc = root["fc"].as<String>().toFloat();
  paramHshelv[idx].slope = root["slope"].as<String>().toFloat();

  float a[3];
  float b[3];
  byte val[4];
  uint32_t floatval;
  AudioFilterFactory::makeHighShelv( a, b, paramHshelv[idx].gain, paramHshelv[idx].fc, paramHshelv[idx].slope, sampleRate );

  uint16_t addr = paramHshelv[idx].addr;
  Serial.println( addr );
  floatval = convertTo824(b[2]);
  val[0] = (floatval >> 24 ) & 0xFF;
  val[1] = (floatval >> 16 ) & 0xFF;
  val[2] = (floatval >> 8 ) & 0xFF;
  val[3] =  floatval & 0xFF;
  ADAU1452_WRITE_BLOCK( addr, val, 4 );  // B2
  addr++;

  Serial.println( addr );
  floatval = convertTo824(b[1]);
  val[0] = (floatval >> 24 ) & 0xFF;
  val[1] = (floatval >> 16 ) & 0xFF;
  val[2] = (floatval >> 8 ) & 0xFF;
  val[3] =  floatval & 0xFF;
  ADAU1452_WRITE_BLOCK( addr, val, 4 );  // B1
  addr++;

  Serial.println( addr );
  floatval = convertTo824(b[0]);
  val[0] = (floatval >> 24 ) & 0xFF;
  val[1] = (floatval >> 16 ) & 0xFF;
  val[2] = (floatval >> 8 ) & 0xFF;
  val[3] =  floatval & 0xFF;
  ADAU1452_WRITE_BLOCK( addr, val, 4 );  // B0
  addr++;

  Serial.println( addr );
  floatval = convertTo824(a[2]);
  val[0] = (floatval >> 24 ) & 0xFF;
  val[1] = (floatval >> 16 ) & 0xFF;
  val[2] = (floatval >> 8 ) & 0xFF;
  val[3] =  floatval & 0xFF;
  ADAU1452_WRITE_BLOCK( addr, val, 4 );  // A2
  addr++;
  
  Serial.println( addr );
  floatval = convertTo824(a[1]);
  val[0] = (floatval >> 24 ) & 0xFF;
  val[1] = (floatval >> 16 ) & 0xFF;
  val[2] = (floatval >> 8 ) & 0xFF;
  val[3] =  floatval & 0xFF;
  ADAU1452_WRITE_BLOCK( addr, val, 4 );  // A1
       
  request->send(200, "text/plain", "");  
}

//==============================================================================
/*! Handles the POST request for Low Pass parameter
 *
 */
void handlePostLpJson( AsyncWebServerRequest* request, uint8_t* data )
{
  Serial.println( "POST /lp" );
  //Serial.println( "Body:");
  //for(size_t i=0; i<len; i++)
  //  Serial.write(data[i]);
  //Serial.println();

  DynamicJsonDocument jsonDoc(1024);
  DeserializationError err = deserializeJson( jsonDoc, (const char*)data );
  if( err )
  {
    Serial.print( "[ERROR] handlePostLpJson(): Deserialization failed. " );
    Serial.println( err.c_str() );
    request->send( 404, "text/plain", "" );
    return;
  }

  JsonObject root = jsonDoc.as<JsonObject>();
  Serial.println( root["idx"].as<String>() );
  Serial.println( root["addr"].as<String>() );
  Serial.println( root["fc"].as<String>() );
  Serial.println( root["typ"].as<String>() );

  uint32_t idx = static_cast<uint32_t>(root["idx"].as<String>().toInt());
  paramLP[idx].addr[0] = static_cast<uint16_t>(root["addr0"].as<String>().toInt());
  paramLP[idx].addr[1] = static_cast<uint16_t>(root["addr1"].as<String>().toInt());
  paramLP[idx].addr[2] = static_cast<uint16_t>(root["addr2"].as<String>().toInt());
  paramLP[idx].addr[3] = static_cast<uint16_t>(root["addr3"].as<String>().toInt());
  paramLP[idx].fc = root["fc"].as<String>().toFloat();
  paramLP[idx].typ = static_cast<tFilterType>(root["typ"].as<String>().toInt());

  float a[12] = { 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0 };
  float b[12] = { 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0 };
  byte val[4];
  uint32_t floatval;
  AudioFilterFactory::makeLowPass( a, b, paramLP[idx].typ, paramLP[idx].fc, sampleRate );

  for( int ii = 0; ii < 4; ii++ )
  {
    uint16_t addr = paramLP[idx].addr[ii];
    floatval = convertTo824(b[ 3*ii + 2 ]);
    val[0] = (floatval >> 24 ) & 0xFF;
    val[1] = (floatval >> 16 ) & 0xFF;
    val[2] = (floatval >> 8 ) & 0xFF;
    val[3] =  floatval & 0xFF;
    ADAU1452_WRITE_BLOCK( addr, val, 4 );  // B2
    addr++;

    floatval = convertTo824(b[ 3*ii + 1 ]);
    val[0] = (floatval >> 24 ) & 0xFF;
    val[1] = (floatval >> 16 ) & 0xFF;
    val[2] = (floatval >> 8 ) & 0xFF;
    val[3] =  floatval & 0xFF;
    ADAU1452_WRITE_BLOCK( addr, val, 4 );  // B1
    addr++;

    floatval = convertTo824(b[ 3*ii + 0 ]);
    val[0] = (floatval >> 24 ) & 0xFF;
    val[1] = (floatval >> 16 ) & 0xFF;
    val[2] = (floatval >> 8 ) & 0xFF;
    val[3] =  floatval & 0xFF;
    ADAU1452_WRITE_BLOCK( addr, val, 4 );  // B0
    addr++;

    floatval = convertTo824(a[ 3*ii + 2 ]);
    val[0] = (floatval >> 24 ) & 0xFF;
    val[1] = (floatval >> 16 ) & 0xFF;
    val[2] = (floatval >> 8 ) & 0xFF;
    val[3] =  floatval & 0xFF;
    ADAU1452_WRITE_BLOCK( addr, val, 4 );  // A2
    addr++;
    
    floatval = convertTo824(a[ 3*ii + 1 ]);
    val[0] = (floatval >> 24 ) & 0xFF;
    val[1] = (floatval >> 16 ) & 0xFF;
    val[2] = (floatval >> 8 ) & 0xFF;
    val[3] =  floatval & 0xFF;
    ADAU1452_WRITE_BLOCK( addr, val, 4 );  // A1
    addr++;
  }
  request->send(200, "text/plain", "");  
}

//==============================================================================
/*! Handles the POST request for Phase parameter
 *
 */
void handlePostPhaseJson( AsyncWebServerRequest* request, uint8_t* data )
{
  Serial.println( "POST /phase" );
  //Serial.println( "Body:");
  //for(size_t i=0; i<len; i++)
  //  Serial.write(data[i]);
  //Serial.println();

  DynamicJsonDocument jsonDoc(1024);
  DeserializationError err = deserializeJson( jsonDoc, (const char*)data );
  if( err )
  {
    Serial.print( "[ERROR] handlePostPhaseJson(): Deserialization failed. " );
    Serial.println( err.c_str() );
    request->send( 404, "text/plain", "" );
    return;
  }

  JsonObject root = jsonDoc.as<JsonObject>();
  Serial.println( root["idx"].as<String>() );
  Serial.println( root["addr"].as<String>() );
  Serial.println( root["fc"].as<String>() );
  Serial.println( root["Q"].as<String>() );

  uint32_t idx = static_cast<uint32_t>(root["idx"].as<String>().toInt());
  paramPhase[idx].addr = static_cast<uint16_t>(root["addr"].as<String>().toInt());
  paramPhase[idx].fc = root["fc"].as<String>().toFloat();
  paramPhase[idx].Q = root["Q"].as<String>().toFloat();

  float a[3];
  float b[3];
  byte val[4];
  uint32_t floatval;
  AudioFilterFactory::makeAllpass( a, b, paramPeq[idx].fc, paramPeq[idx].Q, sampleRate );

  uint16_t addr = paramPhase[idx].addr;
  floatval = convertTo824(b[2]);
  val[0] = (floatval >> 24 ) & 0xFF;
  val[1] = (floatval >> 16 ) & 0xFF;
  val[2] = (floatval >> 8 ) & 0xFF;
  val[3] =  floatval & 0xFF;
  ADAU1452_WRITE_BLOCK( addr, val, 4 );  // B2
  Serial.println( addr );
  addr++;

  floatval = convertTo824(b[1]);
  val[0] = (floatval >> 24 ) & 0xFF;
  val[1] = (floatval >> 16 ) & 0xFF;
  val[2] = (floatval >> 8 ) & 0xFF;
  val[3] =  floatval & 0xFF;
  ADAU1452_WRITE_BLOCK( addr, val, 4 );  // B1
  Serial.println( addr );
  addr++;

  floatval = convertTo824(b[0]);
  val[0] = (floatval >> 24 ) & 0xFF;
  val[1] = (floatval >> 16 ) & 0xFF;
  val[2] = (floatval >> 8 ) & 0xFF;
  val[3] =  floatval & 0xFF;
  ADAU1452_WRITE_BLOCK( addr, val, 4 );  // B0
  Serial.println( addr );
  addr++;

  floatval = convertTo824(a[2]);
  val[0] = (floatval >> 24 ) & 0xFF;
  val[1] = (floatval >> 16 ) & 0xFF;
  val[2] = (floatval >> 8 ) & 0xFF;
  val[3] =  floatval & 0xFF;
  ADAU1452_WRITE_BLOCK( addr, val, 4 );  // A2
  Serial.println( addr );
  addr++;
  
  floatval = convertTo824(a[1]);
  val[0] = (floatval >> 24 ) & 0xFF;
  val[1] = (floatval >> 16 ) & 0xFF;
  val[2] = (floatval >> 8 ) & 0xFF;
  val[3] =  floatval & 0xFF;
  ADAU1452_WRITE_BLOCK( addr, val, 4 );  // A1
  Serial.println( addr );

  request->send(200, "text/plain", "");  
}

//==============================================================================
/*! Handles the POST request for Delay parameter
 *
 */
void handlePostDelayJson( AsyncWebServerRequest* request, uint8_t* data )
{
  Serial.println( "POST /delay" );
  //Serial.println( "Body:");
  //for(size_t i=0; i<len; i++)
  //  Serial.write(data[i]);
  //Serial.println();

  DynamicJsonDocument jsonDoc(1024);
  DeserializationError err = deserializeJson( jsonDoc, (const char*)data );
  if( err )
  {
    Serial.print( "[ERROR] handlePostDelayJson(): Deserialization failed. " );
    Serial.println( err.c_str() );
    request->send( 404, "text/plain", "" );
    return;
  }

  JsonObject root = jsonDoc.as<JsonObject>();
  Serial.println( root["idx"].as<String>() );
  Serial.println( root["delay"].as<String>() );

  uint32_t idx = static_cast<uint32_t>(root["idx"].as<String>().toInt());
  paramDelay[idx].delay = root["delay"].as<String>().toFloat();
  paramDelay[idx].addr = static_cast<uint16_t>(root["addr"].as<String>().toInt());
  
  float dly = paramDelay[idx].delay/1000.0 * sampleRate;
  int32_t idly = static_cast<int32_t>(dly + 0.5);

  uint16_t addr = paramDelay[idx].addr;
  byte val[4];
  val[0] = (idly >> 24 ) & 0xFF;
  val[1] = (idly >> 16 ) & 0xFF;
  val[2] = (idly >> 8 ) & 0xFF;
  val[3] =  idly & 0xFF;
  ADAU1452_WRITE_BLOCK( addr, val, 4 );
      
  request->send(200, "text/plain", "");  
}

//==============================================================================
/*! Handles the POST request for Gain parameter
 *
 */
void handlePostGainJson( AsyncWebServerRequest* request, uint8_t* data )
{
  Serial.println( "POST /gain" );
  //Serial.println( "Body:");
  //for(size_t i=0; i<len; i++)
  //  Serial.write(data[i]);
  //Serial.println();

  DynamicJsonDocument jsonDoc(1024);
  DeserializationError err = deserializeJson( jsonDoc, (const char*)data );
  if( err )
  {
    Serial.print( "[ERROR] handlePostGainJson(): Deserialization failed. " );
    Serial.println( err.c_str() );
    request->send( 404, "text/plain", "" );
    return;
  }

  JsonObject root = jsonDoc.as<JsonObject>();
  Serial.println( root["idx"].as<String>() );
  Serial.println( root["gain"].as<String>() );

  uint32_t idx = static_cast<uint32_t>(root["idx"].as<String>().toInt());
  paramGain[idx].addr = static_cast<uint16_t>(root["addr"].as<String>().toInt());
  paramGain[idx].gain = root["gain"].as<String>().toFloat();
  uint32_t float824val = convertTo824( pow( 10.0, paramGain[idx].gain / 20.0 ) );

  byte val[4];
  val[0] = (float824val >> 24 ) & 0xFF;
  val[1] = (float824val >> 16 ) & 0xFF;
  val[2] = (float824val >> 8 ) & 0xFF;
  val[3] = float824val & 0xFF;
  ADAU1452_WRITE_BLOCK( paramGain[idx].addr, val, 4 );  
       
  request->send(200, "text/plain", "");  
}

//==============================================================================
/*! Handles the POST request for Master Volume
 *
 */
void handlePostMasterVolumeJson( AsyncWebServerRequest* request, uint8_t* data )
{
  Serial.println( "POST /mvol" );
  //Serial.println( "Body:");
  //for(size_t i=0; i<len; i++)
  //  Serial.write(data[i]);
  //Serial.println();

  DynamicJsonDocument jsonDoc(1024);
  DeserializationError err = deserializeJson( jsonDoc, (const char*)data );
  if( err )
  {
    Serial.print( "[ERROR] handlePostMasterVolumeJson(): Deserialization failed. " );
    Serial.println( err.c_str() );
    request->send( 404, "text/plain", "" );
    return;
  }

  JsonObject root = jsonDoc.as<JsonObject>();
  
  uint16_t reg = (uint16_t)strtoul( root["addr"].as<String>().c_str(), NULL, 10 );
  masterVolume = root["vol"].as<String>().toFloat();
  uint32_t rxval = convertTo824( pow( 10.0, masterVolume / 20.0 ) );

  byte val[4];
  val[0] = (rxval >> 24 ) & 0xFF;
  val[1] = (rxval >> 16 ) & 0xFF;
  val[2] = (rxval >> 8 ) & 0xFF;
  val[3] = rxval & 0xFF;
  ADAU1452_WRITE_BLOCK( reg, val, 4 );  

  Serial.println( masterVolume );
  Serial.println( reg, HEX );
  Serial.println( masterVolume );
  Serial.println( rxval, HEX );     
  request->send(200, "text/plain", "");  
}

//==============================================================================
/*! Handles the POST request for Preset Selection
 *
 */
void handlePostPresetJson( AsyncWebServerRequest* request, uint8_t* data )
{
  Serial.println( "POST /preset" );
  //Serial.println( "Body:");
  //for(size_t i=0; i<len; i++)
  //  Serial.write(data[i]);
  //Serial.println();

  DynamicJsonDocument jsonDoc(1024);
  DeserializationError err = deserializeJson( jsonDoc, (const char*)data );
  if( err )
  {
    Serial.print( "[ERROR] handlePostPresetJson(): Deserialization failed. " );
    Serial.println( err.c_str() );
    request->send( 404, "text/plain", "" );
    return;
  }

  JsonObject root = jsonDoc.as<JsonObject>();
  Serial.println( root["pre"].as<String>() );

  currentPreset = root["pre"].as<uint8_t>();
       
  request->send(200, "text/plain", "");  
}
 


//==============================================================================
/*! Arduino Setup
 *
 */
void setup()
{
  Serial.begin(115200);
  Serial.println( "AURORA Debug Log" );

  //----------------------------------------------------------------------------
  //--- Configure I2C
  //----------------------------------------------------------------------------
  Wire.begin( I2C_SDA_PIN, I2C_SCL_PIN );
  Wire.setClock( 100000 );

  // wait until everything is stable
  // might be a bit to defensive
  delay( 2000 );

  //----------------------------------------------------------------------------
  //--- Configure DAC
  //----------------------------------------------------------------------------
  Serial.println( "Config DAC" );
  configDAC();

  //----------------------------------------------------------------------------
  //--- Configure ADC
  //----------------------------------------------------------------------------
  Serial.println( "Config ADC" );
  configADC();

  //----------------------------------------------------------------------------
  //--- Start SPIFFS
  //----------------------------------------------------------------------------
  if( !SPIFFS.begin( true ) )
  {
    Serial.println("An Error has occurred while mounting SPIFFS");
    return;
  }
  Serial.print( "Free disk space: " );
  Serial.print( (SPIFFS.totalBytes() - SPIFFS.usedBytes()) / 1024 );
  Serial.println( "KiB" );

  readParams();

  //----------------------------------------------------------------------------
  //--- Configure ESP for WiFi access
  //----------------------------------------------------------------------------
  WiFi.mode( WIFI_AP );
  WiFi.setHostname( "freeDSP-aurora" );
  // Start access point
  WiFi.softAP( "AP-freeDSP-aurora" );
  delay(100);
  //wait for SYSTEM_EVENT_AP_START
  if( !WiFi.softAPConfig( IPAddress(192, 168, 5, 1), IPAddress(192, 168, 5, 1), IPAddress(255, 255, 255, 0) ) )
    Serial.println("AP Config Failed");

  // Print ESP32 Local IP Address
  //Serial.println(WiFi.localIP());

  //----------------------------------------------------------------------------
  //--- Upload program to DSP
  //----------------------------------------------------------------------------
  uploadDspFirmware();


  //----------------------------------------------------------------------------
  //--- Configure Webserver
  //----------------------------------------------------------------------------
  server.on( "/",       HTTP_GET, [](AsyncWebServerRequest *request ) { request->send( SPIFFS, "/dsp.html", "text/html" ); });
  server.on( "/input",  HTTP_GET, [](AsyncWebServerRequest *request ) { handleGetInputJson(request); });
  server.on( "/hp",     HTTP_GET, [](AsyncWebServerRequest *request ) { handleGetHpJson(request); });
  server.on( "/lshelv", HTTP_GET, [](AsyncWebServerRequest *request ) { handleGetLshelvJson(request); });
  server.on( "/peq",    HTTP_GET, [](AsyncWebServerRequest *request ) { handleGetPeqJson(request); });
  server.on( "/hshelv", HTTP_GET, [](AsyncWebServerRequest *request ) { handleGetHshelvJson(request); });
  server.on( "/lp",     HTTP_GET, [](AsyncWebServerRequest *request ) { handleGetLpJson(request); });
  server.on( "/phase",  HTTP_GET, [](AsyncWebServerRequest *request ) { handleGetPhaseJson(request); });
  server.on( "/delay",  HTTP_GET, [](AsyncWebServerRequest *request ) { handleGetDelayJson(request); });
  server.on( "/gain",   HTTP_GET, [](AsyncWebServerRequest *request ) { handleGetGainJson(request); });
  server.on( "/mvol",   HTTP_GET, [](AsyncWebServerRequest *request ) { handleGetMasterVolumeJson(request); });
  server.on( "/preset", HTTP_GET, [](AsyncWebServerRequest *request ) { handleGetPresetJson(request); });
  
  server.on( "/input", HTTP_POST, [](AsyncWebServerRequest *request){}, NULL, [](AsyncWebServerRequest* request, uint8_t* data, size_t len, size_t index, size_t total )
  {
    handlePostInputJson( request, data );
  });
  server.on( "/hp", HTTP_POST, [](AsyncWebServerRequest *request){}, NULL, [](AsyncWebServerRequest* request, uint8_t* data, size_t len, size_t index, size_t total )
  {
    handlePostHpJson( request, data );
  });
  server.on( "/lshelv", HTTP_POST, [](AsyncWebServerRequest *request){}, NULL, [](AsyncWebServerRequest* request, uint8_t* data, size_t len, size_t index, size_t total )
  {
    handlePostLshelvJson( request, data );
  });
  server.on( "/peq", HTTP_POST, [](AsyncWebServerRequest *request){}, NULL, [](AsyncWebServerRequest* request, uint8_t* data, size_t len, size_t index, size_t total )
  {
    handlePostPeqJson( request, data );
  });
  server.on( "/hshelv", HTTP_POST, [](AsyncWebServerRequest *request){}, NULL, [](AsyncWebServerRequest* request, uint8_t* data, size_t len, size_t index, size_t total )
  {
    handlePostHshelvJson( request, data );
  });
  server.on( "/lp", HTTP_POST, [](AsyncWebServerRequest *request){}, NULL, [](AsyncWebServerRequest* request, uint8_t* data, size_t len, size_t index, size_t total )
  {
    handlePostLpJson( request, data );
  });
  server.on( "/phase", HTTP_POST, [](AsyncWebServerRequest *request){}, NULL, [](AsyncWebServerRequest* request, uint8_t* data, size_t len, size_t index, size_t total )
  {
    handlePostPhaseJson( request, data );
  });
  server.on( "/delay", HTTP_POST, [](AsyncWebServerRequest *request){}, NULL, [](AsyncWebServerRequest* request, uint8_t* data, size_t len, size_t index, size_t total )
  {
    handlePostDelayJson( request, data );
  });
  server.on( "/gain", HTTP_POST, [](AsyncWebServerRequest *request){}, NULL, [](AsyncWebServerRequest* request, uint8_t* data, size_t len, size_t index, size_t total )
  {
    handlePostGainJson( request, data );
  });
  server.on( "/mvol", HTTP_POST, [](AsyncWebServerRequest *request){}, NULL, [](AsyncWebServerRequest* request, uint8_t* data, size_t len, size_t index, size_t total )
  {
    handlePostMasterVolumeJson( request, data );
  });
  server.on( "/preset", HTTP_POST, [](AsyncWebServerRequest *request){}, NULL, [](AsyncWebServerRequest* request, uint8_t* data, size_t len, size_t index, size_t total )
  {
    handlePostPresetJson( request, data );
  });

  // Start server
  server.begin();

  unmuteDAC();

  Serial.println( "Ready" );
}

//==============================================================================
/*! Arduino Main Loop
 *
 */ 
void loop()
{
  
}
