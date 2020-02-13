#include <Wire.h>
#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <SPIFFS.h>
#include "AsyncJson.h"
#include <ArduinoJson.h>

#include "AK4458.h"
#include "AK5558.h"
#include "AudioFilterFactory.h"
#include "fallback.h"

#define VERSION_STR "v2.0.0-alpha.5"

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

#define MAX_NUM_INPUTS 8
#define MAX_NUM_HPS 8
#define MAX_NUM_LSHELVS 8
#define MAX_NUM_PEQS 80
#define MAX_NUM_HSHELVS 8
#define MAX_NUM_LPS 8
#define MAX_NUM_PHASES 8
#define MAX_NUM_DELAYS 8
#define MAX_NUM_GAINS 8

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
  int addonid;
  bool vpot;
};

tSettings Settings;

typedef uint8_t tFilterType;

struct tInput
{
  uint16_t addrChn;
  uint16_t addrPort;
  uint32_t sel;
};

struct tHPLP
{
  uint16_t addr[4];
  float fc;
  tFilterType typ;
  bool bypass;
};

struct tShelving
{
  uint16_t addr;
  float gain;
  float fc;
  float slope;
  bool bypass;
};

struct tPeq
{
  uint16_t addr;
  float gain;
  float fc;
  float Q;
  bool bypass;
};

struct tPhase
{
  uint16_t addr;
  float fc;
  float Q;
  bool inv;
  bool bypass;
};

struct tDelay
{
  uint16_t addr;
  float delay;
  bool bypass;
};

struct tGain
{
  uint16_t addr;
  float gain;
  bool mute;
};

struct tMasterVolume
{
  uint16_t addr;
  float val;
};

struct tInputSelector
{
  uint16_t analog[8];
  uint16_t spdif[8];
  uint16_t port[8];
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
tMasterVolume masterVolume = { 0x0000, -60.0 };
tInputSelector inputSelector;

int numInputs = MAX_NUM_INPUTS;
int numHPs;
int numLShelvs;
int numPEQs;
int numHShelvs;
int numLPs;
int numPhases;
int numDelays;
int numGains;

File fileDspProgram;
File fileUpload;

float sampleRate = 48000.0;
//float masterVolume = -60.0;
uint8_t currentPreset = 0;
byte currentAddOnCfg[3];

String presetUsrparamFile[4] = { "/usrparam.001", "/usrparam.002", "/usrparam.003", "/usrparam.004" };
String presetAddonCfgFile[4] = { "/addoncfg.001", "/addoncfg.002", "/addoncfg.003", "/addoncfg.004" };

AsyncWebServer server( 80 );


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
/*! Inits the default values for filters etc.
 */
void initUserParams( void )
{
  for( int ii = 0; ii < MAX_NUM_INPUTS; ii++ )
  {
    paramInputs[ii].sel = static_cast<uint32_t>(ii);
  }

  for( int ii = 0; ii < MAX_NUM_HPS; ii++ )
  {
    paramHP[ii].fc = 100.0;
    paramHP[ii].typ = 0;
    paramHP[ii].bypass = true;
  }

  for( int ii = 0; ii < MAX_NUM_LSHELVS; ii++ )
  {
    paramLshelv[ii].gain = 0.0;
    paramLshelv[ii].fc = 100.0;
    paramLshelv[ii].slope = 1.0;
    paramLshelv[ii].bypass = false;
  }

  for( int ii = 0; ii < MAX_NUM_PEQS; ii = ii + 8 )
  {
    for( int nn = 0; nn < 8; nn++ )
    {
      paramPeq[ii + nn].gain = 0.0;
      paramPeq[ii + nn].fc = static_cast<float>( (nn+1)*1000 );
      paramPeq[ii + nn].Q = 0.707;
      paramPeq[ii].bypass = false;
    }
  }

  for( int ii = 0; ii < MAX_NUM_HSHELVS; ii++ )
  {
    paramHshelv[ii].gain = 0.0;
    paramHshelv[ii].fc = 10000.0;
    paramHshelv[ii].slope = 1.0;
    paramHshelv[ii].bypass = false;
  }

  for( int ii = 0; ii < MAX_NUM_LPS; ii++ )
  {
    paramLP[ii].fc = 10000.0;
    paramLP[ii].typ = 0;
    paramLP[ii].bypass = false;
  }

  for( int ii = 0; ii < MAX_NUM_PHASES; ii++ )
  {
    paramPhase[ii].fc = 1000.0;
    paramPhase[ii].Q = 1.0;
    paramPhase[ii].inv = false;
    paramPhase[ii].bypass = false;
  }

  for( int ii = 0; ii < MAX_NUM_DELAYS; ii++ )
  {
    paramDelay[ii].delay = 0;
    paramDelay[ii].bypass = false;
  }

  for( int ii = 0; ii < MAX_NUM_GAINS; ii++ )
  {
    paramGain[ii].gain = 0.0;
    paramGain[ii].mute = false;
  }

  masterVolume.val = -60.0;

}

//==============================================================================
/*! Reads the device settings from JSON file.
 */
void readSettings( void )
{
  if( !SPIFFS.exists( "/settings.ini" ) )
  {
    Serial.print( "Writing default settings.ini..." );

    Settings.ssid = "";
    Settings.password = "";
    Settings.addonid = ADDON_CUSTOM;
    Settings.vpot = false;
    writeSettings();

    Serial.println( "[OK]" );
    return;
  }

  Serial.print( "Reading settings.ini..." );

  File fileSettings = SPIFFS.open( "/settings.ini" );

  if( fileSettings )
  {
    StaticJsonDocument<512> jsonDoc;
    DeserializationError err = deserializeJson( jsonDoc, fileSettings );
    if( err )
    {
      Serial.print( "[ERROR] readSettings(): Deserialization failed." );
      Serial.println( err.c_str() );
      return;
    }

    JsonObject jsonSettings = jsonDoc.as<JsonObject>();
    Settings.ssid = jsonSettings["ssid"].as<String>();
    Settings.password = jsonSettings["pwd"].as<String>();
    Settings.addonid = jsonSettings["aid"].as<String>().toInt();
    if( jsonSettings["vpot"].as<String>() == "true" )
      Settings.vpot = true;
    else
      Settings.vpot = false;

    Serial.println( "[OK]" );
    Serial.println( "Device config" );
    //Serial.print( "PID: " ); Serial.println( Settings.pid );
    Serial.print( "AID: " ); Serial.println( Settings.addonid );
    Serial.print( "Volume Poti: " ); Serial.println( Settings.vpot ); 
    Serial.println( "[OK]" );
  }
  else
    Serial.println( "[ERROR] readSettings(): Opening settings.ini failed." );

  fileSettings.close();

}

//==============================================================================
/*! Write the device settings to JSON file.
 */
void writeSettings( void )
{
  File fileSettings = SPIFFS.open( "/settings.ini", "w" );
  
  if( fileSettings )
  {
    StaticJsonDocument<512> jsonSettings;
    jsonSettings["ssid"] = Settings.ssid;
    jsonSettings["pwd"] = Settings.password;
    jsonSettings["aid"] = Settings.addonid;
    jsonSettings["vpot"] = Settings.vpot;

    if( serializeJson( jsonSettings, fileSettings ) == 0 )
      Serial.println( "[ERROR] writeSettings(): Failed to write settings to file" );
  }
  else
    Serial.println( "[ERROR] writeSettings(): Opening settings.ini failed." );

  fileSettings.close();
}

//==============================================================================
/*! Reads the plugin meta data from JSON file.
 */
void readPluginMeta( void )
{
  Serial.print( "Reading plugin.ini......" );

  if( !SPIFFS.exists( "/plugin.ini" ) )
  {
    Serial.println( "File does not exist yet" );
    return;
  }

  File filePluginMeta = SPIFFS.open( "/plugin.ini" );

  if( filePluginMeta )
  {
    StaticJsonDocument<4096> jsonDoc;
    DeserializationError err = deserializeJson( jsonDoc, filePluginMeta );
    if( err )
    {
      Serial.print( "[ERROR] readPluginMeta(): Deserialization failed." );
      Serial.println( err.c_str() );
      return;
    }

    JsonObject jsonPluginMeta = jsonDoc.as<JsonObject>();
    numHPs = jsonPluginMeta["nhp"].as<String>().toInt();
    numLShelvs = jsonPluginMeta["nlshelv"].as<String>().toInt();
    numPEQs = jsonPluginMeta["npeq"].as<String>().toInt();
    numHShelvs = jsonPluginMeta["nhshelv"].as<String>().toInt();
    numLPs = jsonPluginMeta["nlp"].as<String>().toInt();
    numPhases = jsonPluginMeta["nphase"].as<String>().toInt();
    numDelays = jsonPluginMeta["ndly"].as<String>().toInt();
    numGains = jsonPluginMeta["ngain"].as<String>().toInt();

    for( int ii = 0; ii < 8; ii++ )
      inputSelector.analog[ii] = static_cast<uint16_t>(jsonPluginMeta["analog"][ii].as<String>().toInt());
    
    for( int ii = 0; ii < 8; ii++ )
      inputSelector.spdif[ii] = static_cast<uint16_t>(jsonPluginMeta["spdif"][ii].as<String>().toInt());
 
    for( int ii = 0; ii < 8; ii++ )
      inputSelector.port[ii] = static_cast<uint16_t>(jsonPluginMeta["port"][ii].as<String>().toInt());

    for( int ii = 0; ii < numInputs; ii++ )
    {
      paramInputs[ii].addrChn = static_cast<uint16_t>(jsonPluginMeta["analog"][ii].as<String>().toInt());
      paramInputs[ii].addrPort = static_cast<uint16_t>(jsonPluginMeta["port"][ii].as<String>().toInt());
    }

    for( int ii = 0; ii < numHPs; ii++ )
    {
      paramHP[ii].addr[0] = static_cast<uint16_t>(jsonPluginMeta["hp"][0+ii*4]);
      paramHP[ii].addr[1] = static_cast<uint16_t>(jsonPluginMeta["hp"][1+ii*4]);
      paramHP[ii].addr[2] = static_cast<uint16_t>(jsonPluginMeta["hp"][2+ii*4]);
      paramHP[ii].addr[3] = static_cast<uint16_t>(jsonPluginMeta["hp"][3+ii*4]);
    }

    for( int ii = 0; ii < numLShelvs; ii++ )
      paramLshelv[ii].addr = static_cast<uint16_t>(jsonPluginMeta["lshelv"][ii]);

    for( int ii = 0; ii < numPEQs; ii++ )
      paramPeq[ii].addr = static_cast<uint16_t>(jsonPluginMeta["peq"][ii]);

    for( int ii = 0; ii < numHShelvs; ii++ )
      paramHshelv[ii].addr = static_cast<uint16_t>(jsonPluginMeta["hshelv"][ii]);

    for( int ii = 0; ii < numLPs; ii++ )
    {
      paramLP[ii].addr[0] = static_cast<uint16_t>(jsonPluginMeta["lp"][0+ii*4]);
      paramLP[ii].addr[1] = static_cast<uint16_t>(jsonPluginMeta["lp"][1+ii*4]);
      paramLP[ii].addr[2] = static_cast<uint16_t>(jsonPluginMeta["lp"][2+ii*4]);
      paramLP[ii].addr[3] = static_cast<uint16_t>(jsonPluginMeta["lp"][3+ii*4]);
    }

    for( int ii = 0; ii < numPhases; ii++ )
      paramPhase[ii].addr = static_cast<uint16_t>(jsonPluginMeta["phase"][ii]);

    for( int ii = 0; ii < numDelays; ii++ )
      paramDelay[ii].addr = static_cast<uint16_t>(jsonPluginMeta["dly"][ii]);

    for( int ii = 0; ii < numGains; ii++ )
      paramGain[ii].addr = static_cast<uint16_t>(jsonPluginMeta["gain"][ii]);

    masterVolume.addr = jsonPluginMeta["master"].as<String>().toInt();
  }
  else
  {
    Serial.println( "\n[ERROR] readPluginMeta(): Opening plugin.ini failed." );
    return;
  }

  filePluginMeta.close();
  Serial.println( "[OK]" );
}

//==============================================================================
/*! Uploads the firmware from ESP32 SPI flash to DSP.
 */
void uploadDspFirmware( void )
{
  Serial.print( "Init dsp......" );

  if( !SPIFFS.exists( "/dsp.fw" ) )
  {
    Serial.println( "File does not exist yet" );
    return;
  }

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
    Serial.println( "[OK]" );
    Serial.print( "File size: " );
    Serial.println( file_size );
  }
  else
    Serial.println( "\n[ERROR] Failed to open file dsp.fw" );
}


//==============================================================================
/*! Uploads the user parameters from ESP32 SPI flash to DSP.
 */
void uploadUserParams( void )
{
  String fileName = presetUsrparamFile[currentPreset];
 
  //--- Read the preset file
  if( !SPIFFS.exists( fileName ) )
    Serial.println( "Preset " + fileName + " not written yet" );
  else
  {
    File fileUserParams = SPIFFS.open( fileName );

    if( fileUserParams )
    {
      Serial.print( "Uploading user parameters from " + fileName );
      uint32_t totalSize = 0;
      for( int ii = 0; ii < numInputs; ii++ )
      {
        size_t len = fileUserParams.read( (uint8_t*)&(paramInputs[ii]), sizeof(tInput) );
        if( len != sizeof(tInput) )
          Serial.println( "[ERROR] Reading inputs from " + presetUsrparamFile[currentPreset] );
        totalSize += len;
      }

      for( int ii = 0; ii < numHPs; ii++ )
      {
        size_t len = fileUserParams.read( (uint8_t*)&(paramHP[ii]), sizeof(tHPLP) );
        if( len != sizeof(tHPLP) )
          Serial.println( "[ERROR] Reading HPs from " + presetUsrparamFile[currentPreset] );
        totalSize += len;
      }

      for( int ii = 0; ii < numLShelvs; ii++ )
      {
        size_t len = fileUserParams.read( (uint8_t*)&(paramLshelv[ii]), sizeof(tShelving) );
        if( len != sizeof(tShelving) )
          Serial.println( "[ERROR] Reading LShelvs from " + presetUsrparamFile[currentPreset] );
        totalSize += len;
      }

      for( int ii = 0; ii < numPEQs; ii++ )
      {
        size_t len = fileUserParams.read( (uint8_t*)&(paramPeq[ii]), sizeof(tPeq) );
        if( len != sizeof(tPeq) )
          Serial.println( "[ERROR] Reading PEQs from " + presetUsrparamFile[currentPreset] );
        totalSize += len;
      }

      for( int ii = 0; ii < numHShelvs; ii++ )
      {
        size_t len = fileUserParams.read( (uint8_t*)&(paramHshelv[ii]), sizeof(tShelving) );
        if( len != sizeof(tShelving) )
          Serial.println( "[ERROR] Reading HShelvs from " + presetUsrparamFile[currentPreset] );
        totalSize += len;
      }

      for( int ii = 0; ii < numLPs; ii++ )
      {
        size_t len = fileUserParams.read( (uint8_t*)&(paramLP[ii]), sizeof(tHPLP) );
        if( len != sizeof(tHPLP) )
          Serial.println( "[ERROR] Reading LPs from " + presetUsrparamFile[currentPreset] );
        totalSize += len;
      }

      for( int ii = 0; ii < numPhases; ii++ )
      {
        size_t len = fileUserParams.read( (uint8_t*)&(paramPhase[ii]), sizeof(tPhase) );
        if( len != sizeof(tPhase) )
          Serial.println( "[ERROR] Reading Phases from " + presetUsrparamFile[currentPreset] );
        totalSize += len;
      }

      for( int ii = 0; ii < numDelays; ii++ )
      {
        size_t len = fileUserParams.read( (uint8_t*)&(paramDelay[ii]), sizeof(tDelay) );
        if( len != sizeof(tDelay) )
          Serial.println( "[ERROR] Reading Delays from " + presetUsrparamFile[currentPreset] );
        totalSize += len;
      }

      for( int ii = 0; ii < numGains; ii++ )
      {
        size_t len = fileUserParams.read( (uint8_t*)&(paramGain[ii]), sizeof(tGain) );
        if( len != sizeof(tGain) )
          Serial.println( "[ERROR] Reading Gains from " + presetUsrparamFile[currentPreset] );
        totalSize += len;
      }

      size_t len = fileUserParams.read( (uint8_t*)&masterVolume, sizeof(tMasterVolume) );
      if( len != sizeof(tMasterVolume) )
        Serial.println( "[ERROR] Reading masterVolume from " + presetUsrparamFile[currentPreset] );
      totalSize += len;

      Serial.println( "[OK]" );
      Serial.print( "Read " );
      Serial.print( totalSize );
      Serial.println( "bytes" );
    }
    else
      Serial.println( "[ERROR] uploadUserParams(): Reading preset file failed." );

    fileUserParams.close();

  }

  //--- Now upload the parameters
  Serial.print( "Uploading user parameters..."  );
  for( int ii = 0; ii < numInputs; ii++ )
    setInput( paramInputs[ii].addrChn, paramInputs[ii].addrPort, paramInputs[ii].sel );
  Serial.print( "." );

  for( int ii = 0; ii < numHPs; ii++ )
    setHighPass( ii );
  Serial.print( "." );

  for( int ii = 0; ii < numLShelvs; ii++ )
    setLowShelving( ii );
  Serial.print( "." );

  for( int ii = 0; ii < numPEQs; ii++ )
    setPEQ( ii );
  Serial.print( "." );

  for( int ii = 0; ii < numHShelvs; ii++ )
    setHighShelving( ii );
  Serial.print( "." );

  for( int ii = 0; ii < numLPs; ii++ )
    setLowPass( ii );
  Serial.print( "." );

  for( int ii = 0; ii < numPhases; ii++ )
    setPhase( ii );
  Serial.print( "." );

  for( int ii = 0; ii < numDelays; ii++ )
    setDelay( ii );
  Serial.print( "." );

  for( int ii = 0; ii < numGains; ii++ )
    setGain( ii );
  Serial.print( "." );

  setMasterVolume();
  Serial.println( "[OK]" );
  
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
    JsonVariant& jsonResponse = response->getRoot();
    jsonResponse["typ"] = paramHP[offset].typ;
    jsonResponse["fc"] = paramHP[offset].fc;
    if( paramHP[offset].bypass )
      jsonResponse["bypass"] = String( "1" );
    else
      jsonResponse["bypass"] = String( "0" );
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
    if( paramLshelv[offset].bypass )
      jsonResponse["bypass"] = String( "1" );
    else
      jsonResponse["bypass"] = String( "0" );
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
    if( paramPeq[offset].bypass )
      jsonResponse["bypass"] = String( "1" );
    else
      jsonResponse["bypass"] = String( "0" );
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
    if( paramHshelv[offset].bypass )
      jsonResponse["bypass"] = String( "1" );
    else
      jsonResponse["bypass"] = String( "0" );
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
    if( paramLP[offset].bypass )
      jsonResponse["bypass"] = String( "1" );
    else
      jsonResponse["bypass"] = String( "0" );
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
    if( paramPhase[offset].bypass )
      jsonResponse["bypass"] = String( "1" );
    else
      jsonResponse["bypass"] = String( "0" );
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
    if( paramDelay[offset].bypass )
      jsonResponse["bypass"] = String( "1" );
    else
      jsonResponse["bypass"] = String( "0" );
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
    if( paramGain[offset].mute == true )
      jsonResponse["mute"] = String( "1" );
    else
      jsonResponse["mute"] = String( "0" );
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
  AsyncJsonResponse* response = new AsyncJsonResponse();
  JsonVariant& jsonResponse = response->getRoot();
  jsonResponse["vol"] = masterVolume.val;
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
/*! Handles the GET request for device configuration
 *
 */
void handleGetConfigJson( AsyncWebServerRequest* request )
{
  Serial.println( "GET /config" );

  AsyncJsonResponse* response = new AsyncJsonResponse();
  JsonVariant& jsonResponse = response->getRoot();
  jsonResponse["aid"] = Settings.addonid;
  jsonResponse["vpot"] = Settings.vpot;
  jsonResponse["fw"] = VERSION_STR;
  jsonResponse["ip"] = WiFi.localIP().toString();
  jsonResponse["pre"] = currentPreset;

  if( Settings.addonid == ADDON_B )
  {
    jsonResponse["addcfg"] = currentAddOnCfg[2];
  }
  else
    jsonResponse["addcfg"] = 0;

  response->setLength();
  request->send(response);
}

//==============================================================================
/*! Handles the GET request for all input selections
 *
 */
void handleGetAllInputsJson( AsyncWebServerRequest* request )
{
  Serial.println( "GET /allinputs" );

  AsyncJsonResponse* response = new AsyncJsonResponse();
  JsonVariant& jsonResponse = response->getRoot();

  String str;
  uint8_t val;
  String key[] = {"in0", "in1", "in2", "in3", "in4", "in5", "in6", "in7"};
  
  for( int nn = 0; nn < 8; nn++ )
  {
    str = String("0x");
    for( int ii = 0; ii < 4; ii++ )
    {
      val = (paramInputs[nn].sel>>(24-ii*8)) & 0xFF;
      if( val < 0x10 )
        str = str + String( "0") + String( val, HEX );
      else
        str = str + String( val, HEX );
    }
    jsonResponse[key[nn]] = str;
  }
/*
  Serial.println(jsonResponse["in0"].as<String>());
  Serial.println(jsonResponse["in1"].as<String>());
  Serial.println(jsonResponse["in2"].as<String>());
  Serial.println(jsonResponse["in3"].as<String>());
  Serial.println(jsonResponse["in4"].as<String>());
  Serial.println(jsonResponse["in5"].as<String>());
  Serial.println(jsonResponse["in6"].as<String>());
  Serial.println(jsonResponse["in7"].as<String>());
*/
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

  muteDAC();
  delay(500);

  DynamicJsonDocument jsonDoc(1024);
  DeserializationError err = deserializeJson( jsonDoc, (const char*)data );
  if( err )
  {
    Serial.print( "[ERROR] handlePostHpJson(): Deserialization failed. " );
    Serial.println( err.c_str() );
    request->send( 404, "text/plain", "" );
    unmuteDAC();
    return;
  }

  JsonObject root = jsonDoc.as<JsonObject>();
  //Serial.println( root["idx"].as<String>() );
  //Serial.println( root["chn"].as<String>() );
  //Serial.println( root["port"].as<String>() );
  //Serial.println( root["sel"].as<String>() );

  int idx = root["idx"].as<String>().toInt();
  paramInputs[idx].addrChn = static_cast<uint16_t>( root["chn"].as<String>().toInt() );
  paramInputs[idx].addrPort = static_cast<uint16_t>( root["port"].as<String>().toInt() );
  paramInputs[idx].sel = (uint32_t)strtoul( root["sel"].as<String>().c_str(), NULL, 16 );

  setInput( paramInputs[idx].addrChn, paramInputs[idx].addrPort, paramInputs[idx].sel );
       
  request->send(200, "text/plain", "");  

  unmuteDAC();
}

//==============================================================================
/*! Sets a new input selection on DSP.
 *
 */
void setInput( const uint16_t addrChn, const uint16_t addrPort, const uint32_t sel )
{
  byte val[4];
  uint32_t intval = sel & 0x0000ffff;
  val[0] = (intval >> 24 ) & 0xFF;
  val[1] = (intval >> 16 ) & 0xFF;
  val[2] = (intval >> 8 ) & 0xFF;
  val[3] =  intval & 0xFF;
  ADAU1452_WRITE_BLOCK( addrChn, val, 4 );

  intval = (sel >> 16) & 0x0000ffff;
  val[0] = (intval >> 24 ) & 0xFF;
  val[1] = (intval >> 16 ) & 0xFF;
  val[2] = (intval >> 8 ) & 0xFF;
  val[3] =  intval & 0xFF;
  ADAU1452_WRITE_BLOCK( addrPort, val, 4 );
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

  muteDAC();
  delay(500);

  DynamicJsonDocument jsonDoc(1024);
  DeserializationError err = deserializeJson( jsonDoc, (const char*)data );
  if( err )
  {
    Serial.print( "[ERROR] handlePostHpJson(): Deserialization failed. " );
    Serial.println( err.c_str() );
    request->send( 404, "text/plain", "" );
    unmuteDAC();
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
  if( root["bypass"].as<String>().toInt() == 0 )
    paramHP[idx].bypass = false;
  else
    paramHP[idx].bypass = true;

  setHighPass( idx );
       
  request->send(200, "text/plain", "");  

  unmuteDAC();

}

//==============================================================================
/*! Sets the values for a highpass block on DSP.
 *
 */
void setHighPass( int idx )
{
  float a[12] = { 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0 };
  float b[12] = { 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0 };
  byte val[4];
  uint32_t floatval;
  if( !(paramHP[idx].bypass) )
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

  muteDAC();
  delay(500);

  DynamicJsonDocument jsonDoc(1024);
  DeserializationError err = deserializeJson( jsonDoc, (const char*)data );
  if( err )
  {
    Serial.print( "[ERROR] handlePostHpJson(): Deserialization failed. " );
    Serial.println( err.c_str() );
    request->send( 404, "text/plain", "" );
    unmuteDAC();
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
  if( root["bypass"].as<String>().toInt() == 0 )
    paramLshelv[idx].bypass = false;
  else
    paramLshelv[idx].bypass = true;

  setLowShelving( idx );
       
  request->send(200, "text/plain", ""); 

  unmuteDAC(); 
}

//==============================================================================
/*! Sets the values for a low shelving block on DSP.
 *
 */
void setLowShelving( int idx )
{
  float a[3] = { 1.0, 0.0, 0.0 };
  float b[3] = { 1.0, 0.0, 0.0 };
  byte val[4];
  uint32_t floatval;
  if( !(paramLshelv[idx].bypass) )
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

  muteDAC();
  delay(500);

  DynamicJsonDocument jsonDoc(1024);
  DeserializationError err = deserializeJson( jsonDoc, (const char*)data );
  if( err )
  {
    Serial.print( "[ERROR] handlePostPeqJson(): Deserialization failed. " );
    Serial.println( err.c_str() );
    request->send( 404, "text/plain", "" );
    unmuteDAC();
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
  if( root["bypass"].as<String>().toInt() == 0 )
    paramPeq[idx].bypass = false;
  else
    paramPeq[idx].bypass = true;

  setPEQ( idx );

  request->send(200, "text/plain", "");  

  unmuteDAC();
}

//==============================================================================
/*! Sets the values for a peq block on DSP.
 *
 */
void setPEQ( int idx )
{
  float a[3] = { 1.0, 0.0, 0.0 };
  float b[3] = { 1.0, 0.0, 0.0 };
  byte val[4];
  uint32_t floatval;
  if( !(paramPeq[idx].bypass) )
    AudioFilterFactory::makeParametricEQ( a, b, paramPeq[idx].gain, paramPeq[idx].fc, paramPeq[idx].Q, sampleRate );

  uint32_t addr = paramPeq[idx].addr;
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

  muteDAC();
  delay(500);

  DynamicJsonDocument jsonDoc(1024);
  DeserializationError err = deserializeJson( jsonDoc, (const char*)data );
  if( err )
  {
    Serial.print( "[ERROR] handlePostHpJson(): Deserialization failed. " );
    Serial.println( err.c_str() );
    request->send( 404, "text/plain", "" );
    unmuteDAC();
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
  if( root["bypass"].as<String>().toInt() == 0 )
    paramHshelv[idx].bypass = false;
  else
    paramHshelv[idx].bypass = true;

  setHighShelving( idx );
       
  request->send(200, "text/plain", "");  

  unmuteDAC();
}

//==============================================================================
/*! Sets the values for a high shelving block on DSP.
 *
 */
void setHighShelving( int idx )
{
  float a[3] = { 1.0, 0.0, 0.0 };
  float b[3] = { 1.0, 0.0, 0.0 };
  byte val[4];
  uint32_t floatval;
  if( !(paramHshelv[idx].bypass) )
    AudioFilterFactory::makeHighShelv( a, b, paramHshelv[idx].gain, paramHshelv[idx].fc, paramHshelv[idx].slope, sampleRate );

  uint16_t addr = paramHshelv[idx].addr;
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

  muteDAC();
  delay(500);

  DynamicJsonDocument jsonDoc(1024);
  DeserializationError err = deserializeJson( jsonDoc, (const char*)data );
  if( err )
  {
    Serial.print( "[ERROR] handlePostLpJson(): Deserialization failed. " );
    Serial.println( err.c_str() );
    request->send( 404, "text/plain", "" );
    unmuteDAC();
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
  if( root["bypass"].as<String>().toInt() == 0 )
    paramLP[idx].bypass = false;
  else
    paramLP[idx].bypass = true;

  setLowPass( idx );

  request->send(200, "text/plain", ""); 

  unmuteDAC(); 
}

//==============================================================================
/*! Sets the values for a low pass block on DSP.
 *
 */
void setLowPass( int idx )
{
  float a[12] = { 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0 };
  float b[12] = { 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0 };
  byte val[4];
  uint32_t floatval;
  if( !(paramLP[idx].bypass) )
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

  muteDAC();
  delay(500);

  DynamicJsonDocument jsonDoc(1024);
  DeserializationError err = deserializeJson( jsonDoc, (const char*)data );
  if( err )
  {
    Serial.print( "[ERROR] handlePostPhaseJson(): Deserialization failed. " );
    Serial.println( err.c_str() );
    request->send( 404, "text/plain", "" );
    unmuteDAC();
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
  if( root["bypass"].as<String>().toInt() == 0 )
    paramPhase[idx].bypass = false;
  else
    paramPhase[idx].bypass = true;

  setPhase( idx );

  request->send(200, "text/plain", "");  

  unmuteDAC();
}

//==============================================================================
/*! Sets the values for a phase block on DSP.
 *
 */
void setPhase( int idx )
{
  float a[3] = { 1.0, 0.0, 0.0 };
  float b[3] = { 1.0, 0.0, 0.0 };
  byte val[4];
  uint32_t floatval;
  if( !paramPhase[idx].bypass )
    AudioFilterFactory::makeAllpass( a, b, paramPhase[idx].fc, paramPhase[idx].Q, sampleRate );

  uint16_t addr = paramPhase[idx].addr;
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

  muteDAC();
  delay(500);

  DynamicJsonDocument jsonDoc(1024);
  DeserializationError err = deserializeJson( jsonDoc, (const char*)data );
  if( err )
  {
    Serial.print( "[ERROR] handlePostDelayJson(): Deserialization failed. " );
    Serial.println( err.c_str() );
    request->send( 404, "text/plain", "" );
    unmuteDAC();
    return;
  }

  JsonObject root = jsonDoc.as<JsonObject>();
  Serial.println( root["idx"].as<String>() );
  Serial.println( root["delay"].as<String>() );

  uint32_t idx = static_cast<uint32_t>(root["idx"].as<String>().toInt());
  paramDelay[idx].delay = root["delay"].as<String>().toFloat();
  paramDelay[idx].addr = static_cast<uint16_t>(root["addr"].as<String>().toInt());
  if( root["bypass"].as<String>().toInt() == 0 )
    paramDelay[idx].bypass = false;
  else
    paramDelay[idx].bypass = true;
  
  setDelay( idx );
      
  request->send(200, "text/plain", "");  

  unmuteDAC();
}

//==============================================================================
/*! Sets the values for a delay block on DSP.
 *
 */
void setDelay( int idx )
{
  float dly = paramDelay[idx].delay/1000.0 * sampleRate;
  int32_t idly = static_cast<int32_t>(dly + 0.5);
  if( paramDelay[idx].bypass )
    idly = 0;

  uint16_t addr = paramDelay[idx].addr;
  byte val[4];
  val[0] = (idly >> 24 ) & 0xFF;
  val[1] = (idly >> 16 ) & 0xFF;
  val[2] = (idly >> 8 ) & 0xFF;
  val[3] =  idly & 0xFF;
  ADAU1452_WRITE_BLOCK( addr, val, 4 );
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

  muteDAC();
  delay(500);

  DynamicJsonDocument jsonDoc(1024);
  DeserializationError err = deserializeJson( jsonDoc, (const char*)data );
  if( err )
  {
    Serial.print( "[ERROR] handlePostGainJson(): Deserialization failed. " );
    Serial.println( err.c_str() );
    request->send( 404, "text/plain", "" );
    unmuteDAC();
    return;
  }

  JsonObject root = jsonDoc.as<JsonObject>();
  Serial.println( root["idx"].as<String>() );
  Serial.println( root["gain"].as<String>() );
  Serial.println( root["mute"].as<String>() );

  uint32_t idx = static_cast<uint32_t>(root["idx"].as<String>().toInt());
  paramGain[idx].addr = static_cast<uint16_t>(root["addr"].as<String>().toInt());
  paramGain[idx].gain = root["gain"].as<String>().toFloat();
  if( root["mute"].as<String>().toInt() == 0 )
    paramGain[idx].mute = false;
  else
    paramGain[idx].mute = true;

  setGain( idx );  
       
  request->send(200, "text/plain", "");  

  unmuteDAC();
}

//==============================================================================
/*! Sets the values for a gain block on DSP.
 *
 */
void setGain( int idx )
{
  uint32_t float824val;
  if( paramGain[idx].mute )
    float824val = convertTo824( 0.0 );
  else
    float824val = convertTo824( pow( 10.0, paramGain[idx].gain / 20.0 ) );
  
  byte val[4];
  val[0] = (float824val >> 24 ) & 0xFF;
  val[1] = (float824val >> 16 ) & 0xFF;
  val[2] = (float824val >> 8 ) & 0xFF;
  val[3] = float824val & 0xFF;
  ADAU1452_WRITE_BLOCK( paramGain[idx].addr, val, 4 );
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

  masterVolume.addr = static_cast<uint16_t>(root["addr"].as<String>().toInt());
  masterVolume.val = root["vol"].as<String>().toFloat();
  
  setMasterVolume(); 
    
  request->send(200, "text/plain", "");  
}

//==============================================================================
/*! Sets the value for master volume on DSP.
 *
 */
void setMasterVolume( void )
{
  if( masterVolume.addr != 0x0000 )
  {
    uint16_t reg = masterVolume.addr;
    uint32_t rxval = convertTo824( pow( 10.0, masterVolume.val / 20.0 ) );

    byte val[4];
    val[0] = (rxval >> 24 ) & 0xFF;
    val[1] = (rxval >> 16 ) & 0xFF;
    val[2] = (rxval >> 8 ) & 0xFF;
    val[3] = rxval & 0xFF;
    ADAU1452_WRITE_BLOCK( reg, val, 4 ); 
  }
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

  muteDAC();
  delay(500);

  DynamicJsonDocument jsonDoc(1024);
  DeserializationError err = deserializeJson( jsonDoc, (const char*)data );
  if( err )
  {
    Serial.print( "[ERROR] handlePostPresetJson(): Deserialization failed. " );
    Serial.println( err.c_str() );
    request->send( 404, "text/plain", "" );
    unmuteDAC();
    return;
  }

  JsonObject root = jsonDoc.as<JsonObject>();
  Serial.println( root["pre"].as<String>() );

  currentPreset = root["pre"].as<uint8_t>();

  initUserParams();
  uploadUserParams();
       
  request->send(200, "text/plain", "");
  unmuteDAC();  
}
 
//==============================================================================
/*! Handles the POST request for device configuration
 *
 */
void handlePostConfigJson( AsyncWebServerRequest* request, uint8_t* data )
{
  Serial.println( "POST /config" );
  //Serial.println( "Body:");
  //for(size_t i=0; i<len; i++)
  //  Serial.write(data[i]);
  //Serial.println();

  DynamicJsonDocument jsonDoc(1024);
  DeserializationError err = deserializeJson( jsonDoc, (const char*)data );
  if( err )
  {
    Serial.print( "[ERROR] handlePostConfigJson(): Deserialization failed. " );
    Serial.println( err.c_str() );
    request->send( 404, "text/plain", "" );
    return;
  }

  JsonObject root = jsonDoc.as<JsonObject>();
  Serial.println( root["aid"].as<String>() );
  Serial.println( root["vpot"].as<String>() );

  Settings.addonid = root["aid"].as<String>().toInt();
  if( root["vpot"].as<String>() == "true" )
    Settings.vpot = true;
  else
    Settings.vpot = false;

  writeSettings();
       
  request->send(200, "text/plain", "");  
}

//==============================================================================
/*! Handles the POST request for storing current preset
 *
 */
void handlePostStore( AsyncWebServerRequest* request, uint8_t* data )
{
  Serial.println( "POST /store" );

  muteDAC();
  delay(500);

  String fileName = presetUsrparamFile[currentPreset];

  if( SPIFFS.exists( fileName ) )
  {
    if( SPIFFS.remove( fileName ) )
      Serial.println( fileName + " deleted" );
    else
      Serial.println( "[ERROR] Deleting " + fileName );
  }

  Serial.println( "Writing " + fileName );
  File fileUserParams = SPIFFS.open( fileName, "w" );
  if( !fileUserParams )
    Serial.println( "[ERROR] Failed to open " + fileName );
  else
    Serial.println( "Opened " + fileName );

  uint32_t totalSize = 0;
  for( int ii = 0; ii < numInputs; ii++ )
  {
    size_t len = fileUserParams.write( (uint8_t*)&(paramInputs[ii]), sizeof(tInput) );
    if( len != sizeof(tInput) )
      Serial.println( "[ERROR] Writing inputs to " + presetUsrparamFile[currentPreset] );
    totalSize += len;
  }

  for( int ii = 0; ii < numHPs; ii++ )
  {
    size_t len = fileUserParams.write( (uint8_t*)&(paramHP[ii]), sizeof(tHPLP) );
    if( len != sizeof(tHPLP) )
      Serial.println( "[ERROR] Writing HPs to " + presetUsrparamFile[currentPreset] );
    totalSize += len;
  }

  for( int ii = 0; ii < numLShelvs; ii++ )
  {
    size_t len = fileUserParams.write( (uint8_t*)&(paramLshelv[ii]), sizeof(tShelving) );
    if( len != sizeof(tShelving) )
      Serial.println( "[ERROR] Writing LShelvs to " + presetUsrparamFile[currentPreset] );
    totalSize += len;
  }

  for( int ii = 0; ii < numPEQs; ii++ )
  {
    size_t len = fileUserParams.write( (uint8_t*)&(paramPeq[ii]), sizeof(tPeq) );
    if( len != sizeof(tPeq) )
      Serial.println( "[ERROR] Writing PEQs to " + presetUsrparamFile[currentPreset] );
    totalSize += len;
  }

  for( int ii = 0; ii < numHShelvs; ii++ )
  {
    size_t len = fileUserParams.write( (uint8_t*)&(paramHshelv[ii]), sizeof(tShelving) );
    if( len != sizeof(tShelving) )
      Serial.println( "[ERROR] Writing HShelvs to " + presetUsrparamFile[currentPreset] );
    totalSize += len;
  }

  for( int ii = 0; ii < numLPs; ii++ )
  {
    size_t len = fileUserParams.write( (uint8_t*)&(paramLP[ii]), sizeof(tHPLP) );
    if( len != sizeof(tHPLP) )
      Serial.println( "[ERROR] Writing LPs to " + presetUsrparamFile[currentPreset] );
    totalSize += len;
  }

  for( int ii = 0; ii < numPhases; ii++ )
  {
    size_t len = fileUserParams.write( (uint8_t*)&(paramPhase[ii]), sizeof(tPhase) );
    if( len != sizeof(tPhase) )
      Serial.println( "[ERROR] Writing Phases to " + presetUsrparamFile[currentPreset] );
    totalSize += len;
  }

  for( int ii = 0; ii < numDelays; ii++ )
  {
    size_t len = fileUserParams.write( (uint8_t*)&(paramDelay[ii]), sizeof(tDelay) );
    if( len != sizeof(tDelay) )
      Serial.println( "[ERROR] Writing Delays to " + presetUsrparamFile[currentPreset] );
    totalSize += len;
  }

  for( int ii = 0; ii < numGains; ii++ )
  {
    size_t len = fileUserParams.write( (uint8_t*)&(paramGain[ii]), sizeof(tGain) );
    if( len != sizeof(tGain) )
      Serial.println( "[ERROR] Writing Gains to " + presetUsrparamFile[currentPreset] );
    totalSize += len;
  }

  size_t len = fileUserParams.write( (uint8_t*)&masterVolume, sizeof(tMasterVolume) );
  if( len != sizeof(tMasterVolume) )
    Serial.println( "[ERROR] Writing masterVolume to " + presetUsrparamFile[currentPreset] );
  totalSize += len;

  fileUserParams.flush();
  fileUserParams.close();

  Serial.print( "Wrote " );
  Serial.print( totalSize );
  Serial.println( "bytes" );

  fileName = presetAddonCfgFile[currentPreset];

  if( SPIFFS.exists( fileName ) )
  {
    if( SPIFFS.remove( fileName ) )
      Serial.println( fileName + " deleted" );
    else
      Serial.println( "[ERROR] Deleting " + fileName );
  }

  Serial.println( "Writing " + fileName );
  File fileAddonConfig = SPIFFS.open( fileName, "w" );
  if( !fileAddonConfig )
    Serial.println( "[ERROR] Failed to open " + fileName );
  else
    Serial.println( "Opened " + fileName );

  totalSize = 0;

  if( Settings.addonid == ADDON_B )
  {
    size_t len = fileAddonConfig.write( currentAddOnCfg, 3 );
    if( len != 3 )
      Serial.println( "[ERROR] Writing AddOn config to " + fileName );
    totalSize += len;
  }

  fileAddonConfig.flush();
  fileAddonConfig.close();

  Serial.print( "Wrote " );
  Serial.print( totalSize );
  Serial.println( "bytes" );

  request->send(200, "text/plain", "");  

  unmuteDAC();
}

//==============================================================================
/*! Handles the POST request for storing addon configuration
 *
 */
void handlePostAddonConfigJson( AsyncWebServerRequest* request, uint8_t* data )
{
  Serial.println( "POST /addoncfg" );
  //Serial.println( "Body:");
  //for(size_t i=0; i<len; i++)
  //  Serial.write(data[i]);
  //Serial.println();

  muteDAC();
  delay(500);

  DynamicJsonDocument jsonDoc(1024);
  DeserializationError err = deserializeJson( jsonDoc, (const char*)data );
  if( err )
  {
    Serial.print( "[ERROR] handlePostAddonConfig(): Deserialization failed. " );
    Serial.println( err.c_str() );
    request->send( 404, "text/plain", "" );
    unmuteDAC();
    return;
  }

  if( Settings.addonid == ADDON_B )
  {
    JsonObject root = jsonDoc.as<JsonObject>();
    int len = root["len"].as<String>().toInt();
    for( int ii = 0; ii < len; ii++ )
      Serial.println( root["i2c"][ii].as<String>() );

    currentAddOnCfg[0] = (uint8_t)strtoul( root["i2c"][0].as<String>().c_str(), NULL, 16 );
    currentAddOnCfg[1] = (uint8_t)strtoul( root["i2c"][1].as<String>().c_str(), NULL, 16 );
    currentAddOnCfg[2] = (uint8_t)strtoul( root["i2c"][2].as<String>().c_str(), NULL, 16 );

    Wire.beginTransmission( currentAddOnCfg[0]>>1 ); //ADDONB_SPDIFMUX_ADDR
    Wire.write( currentAddOnCfg[1] ); // regaddr
    Wire.write( currentAddOnCfg[2] ); // data
    Wire.endTransmission( true );
  }

  request->send(200, "text/plain", "");  

  unmuteDAC();
}

//==============================================================================
/*! Handles the POST request for device configuration
 *
 */
void handlePostWifiConfigJson( AsyncWebServerRequest* request, uint8_t* data )
{
  Serial.println( "POST /config" );
  //Serial.println( "Body:");
  //for(size_t i=0; i<len; i++)
  //  Serial.write(data[i]);
  //Serial.println();

  DynamicJsonDocument jsonDoc(1024);
  DeserializationError err = deserializeJson( jsonDoc, (const char*)data );
  if( err )
  {
    Serial.print( "[ERROR] handlePostWifiConfigJson(): Deserialization failed. " );
    Serial.println( err.c_str() );
    request->send( 404, "text/plain", "" );
    return;
  }

  JsonObject root = jsonDoc.as<JsonObject>();

  Settings.ssid = root["ssid"].as<String>();
  Settings.password = root["pwd"].as<String>();

  writeSettings();
       
  request->send(200, "text/plain", "");  
}

//==============================================================================
/*! Setup AddOn A
 *
 */
void setupAddOnA( void )
{
  Wire.beginTransmission( ADDONA_SPDIFMUX_ADDR );
  Wire.write( 0x03 );
  Wire.write( 0xFF );
  Wire.endTransmission( true );

  Wire.beginTransmission( ADDONA_SPDIFMUX_ADDR );
  Wire.write( 0x00 );
  Wire.endTransmission();
  Wire.requestFrom( ADDONA_SPDIFMUX_ADDR, 1 );
  if( Wire.available() == 1 )
  {
    byte value = Wire.read();

    // Analog RCA
    if( (value == 0xfe) || (value == 0xff) )
    {
      uint32_t data = 0x00000004;
      byte val[4];
      val[0] = (data >> 24 ) & 0xFF;
      val[1] = (data >> 16 ) & 0xFF;
      val[2] = (data >> 8 ) & 0xFF;
      val[3] = data & 0xFF;
      for( int ii = 0; ii < 8; ii++ )
        ADAU1452_WRITE_BLOCK( inputSelector.analog[ii],  val, 4 ); 
      
      data = 0x00000000;
      val[0] = (data >> 24 ) & 0xFF;
      val[1] = (data >> 16 ) & 0xFF;
      val[2] = (data >> 8 ) & 0xFF;
      val[3] = data & 0xFF;
      for( int ii = 0; ii < 8; ii++ )
        ADAU1452_WRITE_BLOCK( inputSelector.port[ii], val, 4 );
    }
    // Analog XLR
    else if( value == 0xf7 )
    {
      uint32_t data = 0x00000000;
      byte val[4];
      val[0] = (data >> 24 ) & 0xFF;
      val[1] = (data >> 16 ) & 0xFF;
      val[2] = (data >> 8 ) & 0xFF;
      val[3] = data & 0xFF;
      for( int ii = 0; ii < 8; ii++ )
        ADAU1452_WRITE_BLOCK( inputSelector.analog[ii],  val, 4 ); 

      data = 0x00000000;
      val[0] = (data >> 24 ) & 0xFF;
      val[1] = (data >> 16 ) & 0xFF;
      val[2] = (data >> 8 ) & 0xFF;
      val[3] = data & 0xFF;
      for( int ii = 0; ii < 8; ii++ )
        ADAU1452_WRITE_BLOCK( inputSelector.port[ii], val, 4 );
    }
    // Toslink left channel
    else if( (value == 0xfa) || (value == 0xfb) )
    {
      uint32_t data = 0x00000000;
      byte val[4];
      val[0] = (data >> 24 ) & 0xFF;
      val[1] = (data >> 16 ) & 0xFF;
      val[2] = (data >> 8 ) & 0xFF;
      val[3] = data & 0xFF;
      for( int ii = 0; ii < 8; ii++ )
        ADAU1452_WRITE_BLOCK( inputSelector.spdif[ii],  val, 4 ); 

      data = 0x00000004;
      val[0] = (data >> 24 ) & 0xFF;
      val[1] = (data >> 16 ) & 0xFF;
      val[2] = (data >> 8 ) & 0xFF;
      val[3] = data & 0xFF;
      for( int ii = 0; ii < 8; ii++ )
        ADAU1452_WRITE_BLOCK( inputSelector.port[ii], val, 4 );
    }
    // Toslink right channel
    else if( value == 0xf3 )
    {
      uint32_t data = 0x00000001;
      byte val[4];
      val[0] = (data >> 24 ) & 0xFF;
      val[1] = (data >> 16 ) & 0xFF;
      val[2] = (data >> 8 ) & 0xFF;
      val[3] = data & 0xFF;
      for( int ii = 0; ii < 8; ii++ )
        ADAU1452_WRITE_BLOCK( inputSelector.spdif[ii],  val, 4 ); 

      data = 0x00000004;
      val[0] = (data >> 24 ) & 0xFF;
      val[1] = (data >> 16 ) & 0xFF;
      val[2] = (data >> 8 ) & 0xFF;
      val[3] = data & 0xFF;
      for( int ii = 0; ii < 8; ii++ )
        ADAU1452_WRITE_BLOCK( inputSelector.port[ii], val, 4 );
    }
    // Digital RCA left
    else if( (value == 0xfc) || (value == 0xfd) )
    {
      uint32_t data = 0x00000000;
      byte val[4];
      val[0] = (data >> 24 ) & 0xFF;
      val[1] = (data >> 16 ) & 0xFF;
      val[2] = (data >> 8 ) & 0xFF;
      val[3] = data & 0xFF;
      for( int ii = 0; ii < 8; ii++ )
        ADAU1452_WRITE_BLOCK( inputSelector.spdif[ii],  val, 4 ); 

      data = 0x00000004;
      val[0] = (data >> 24 ) & 0xFF;
      val[1] = (data >> 16 ) & 0xFF;
      val[2] = (data >> 8 ) & 0xFF;
      val[3] = data & 0xFF;
      for( int ii = 0; ii < 8; ii++ )
        ADAU1452_WRITE_BLOCK( inputSelector.port[ii], val, 4 );
    }
    // Digital RCA right
    else if( value == 0xf5 )
    {
      uint32_t data = 0x00000001;
      byte val[4];
      val[0] = (data >> 24 ) & 0xFF;
      val[1] = (data >> 16 ) & 0xFF;
      val[2] = (data >> 8 ) & 0xFF;
      val[3] = data & 0xFF;
      for( int ii = 0; ii < 8; ii++ )
        ADAU1452_WRITE_BLOCK( inputSelector.spdif[ii],  val, 4 ); 

      data = 0x00000004;
      val[0] = (data >> 24 ) & 0xFF;
      val[1] = (data >> 16 ) & 0xFF;
      val[2] = (data >> 8 ) & 0xFF;
      val[3] = data & 0xFF;
      for( int ii = 0; ii < 8; ii++ )
        ADAU1452_WRITE_BLOCK( inputSelector.port[ii], val, 4 );
    }
  }
}

//==============================================================================
/*! Setup AddOn B
 *
 */
void setupAddOnB( void )
{
  Serial.print( "Init AddOn B......" );
  Wire.beginTransmission( ADDONB_SPDIFMUX_ADDR );
  Wire.write( 0x03 );
  Wire.write( 0x00 );
  Wire.endTransmission( true );

  String fileName = presetAddonCfgFile[currentPreset];

  File fileAddonConfig = SPIFFS.open( fileName );
  if( !fileAddonConfig )
    Serial.println( "[ERROR] Failed to open " + fileName );
  else
    Serial.println( "Opened " + fileName );

  size_t len = fileAddonConfig.read( currentAddOnCfg, 3 );
  if( len != 3 )
    Serial.println( "[ERROR] Reading AddOn config " + fileName );

  fileAddonConfig.close();

  Serial.println( "[OK]" );
}

//==============================================================================
/*! Handles a file upload
 *
 */
void handleFileUpload( AsyncWebServerRequest* request, uint8_t* data, size_t len, size_t index, size_t total )
{
  if (!index)
  {
    Serial.println("POST /upload");

    if( request->hasParam( "fname" ) )
    {
      AsyncWebParameter* fname = request->getParam(0);
      String fileName = String( "/" ) + fname->value();
      Serial.println( fileName );
      if( SPIFFS.exists( fileName ) )
      {
        if( SPIFFS.remove( fileName ) )
          Serial.println( fileName + " deleted." );
        else
          Serial.println( "[ERROR] Deleting " + fileName );
      }
      fileUpload = SPIFFS.open( fileName, "w" );
      if( !fileUpload )
        Serial.println( "[ERROR] Failed to open " + fileName );
      else
        Serial.println( "Opened " + fileName );
    }
  }

  size_t written = 0;
  if( len > 0 )
    written = fileUpload.write( data, len );

  if( written != len )
    Serial.println( "[ERROR] Writing file" );
              
  Serial.print( "." );
    
  if( index + len >= total )
  {
    fileUpload.flush();
    fileUpload.close();

    AsyncWebParameter* fname = request->getParam(0);
    String fileName = String( "/" ) + fname->value();
    fileUpload = SPIFFS.open( fileName );
    written = fileUpload.size();
    fileUpload.close();

    Serial.println( "[OK]" );
    Serial.println( "Upload complete." + String(written) + "bytes written." );
  }
}

//==============================================================================
/*! Wifi connection task 
 *
 */
void myWiFiTask(void *pvParameters)
{
  wl_status_t state;
  bool firstConnectAttempt = true;
  bool myWiFiFirstConnect = true;
  int cntrAuthFailure = 0;
  
  WiFi.mode( WIFI_AP_STA );
  WiFi.setHostname( "freeDSP-aurora" );
  WiFi.persistent( false );
  WiFi.disconnect();
  // Start access point
  WiFi.softAP( "AP-freeDSP-aurora" );
  delay(100);

  if( !WiFi.softAPConfig( IPAddress(192, 168, 5, 1), IPAddress(192, 168, 5, 1), IPAddress(255, 255, 255, 0) ) )
    Serial.println("AP Config Failed");
  
  // Start server
  server.begin();

  while (true)
  {
    if( (Settings.ssid.length() > 0) &&  (cntrAuthFailure < 10) )
    {
      state = WiFi.status();
      if( state != WL_CONNECTED )
      {  
        //if (state == WL_NO_SHIELD)
        if( firstConnectAttempt )
        {
          firstConnectAttempt = false;
          Serial.print( "Connecting to " );
          Serial.println( Settings.ssid.c_str() );
          WiFi.begin(Settings.ssid.c_str(), Settings.password.c_str());  
          cntrAuthFailure++;
        } 
        else if( state == WL_IDLE_STATUS )
        {
          Serial.println( "Idle" );
        }
        else if( state == WL_NO_SSID_AVAIL )
        {
          Serial.println( "No SSID available" );
        }
        else if( state == WL_CONNECTION_LOST )
        {  
          Serial.println("WiFi connection lost");
          WiFi.disconnect(true);
          cntrAuthFailure++;
        } 
        // else if( state == WL_SCAN_COMPLETED )
        else if( state == WL_CONNECT_FAILED )
        {  
          Serial.println("WiFi connection failed");
          WiFi.disconnect(true);
          cntrAuthFailure++;
        } 
        else if( state == WL_DISCONNECTED )
        {  
          if (!myWiFiFirstConnect)
          {  
            myWiFiFirstConnect = true;
            Serial.println( "WiFi disconnected" );
          }
          Serial.println("No Connection -> Wifi Reset");
          WiFi.persistent(false);
          WiFi.disconnect();
          WiFi.mode(WIFI_OFF);
          WiFi.mode(WIFI_AP_STA);
          // WiFi.config(ip, gateway, subnet); // Only for fix IP needed
          WiFi.begin(Settings.ssid.c_str(), Settings.password.c_str());
          delay(3000);
          cntrAuthFailure++;
        }
        vTaskDelay (250); // Check again in about 250ms
      } 
      else // We have connection
      { 
        if( myWiFiFirstConnect ) // Report only once
        {  
          myWiFiFirstConnect = false;
          cntrAuthFailure = 0;
          Serial.println( "Connected" );
          Serial.print( "IP address: " );
          Serial.println( WiFi.localIP() );
          Serial.println( WiFi.getHostname() );
        }
        vTaskDelay (5000); // Check again in about 5s
      }
    }
    else
      vTaskDelay (5000);
  }
}

//==============================================================================
/*! Arduino Setup
 *
 */
void setup()
{
  Serial.begin(115200);
  Serial.println( "AURORA Debug Log" );
  Serial.println( VERSION_STR );

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

  File root = SPIFFS.open("/");
  File file = root.openNextFile();
  while(file)
  {
    Serial.println(file.name());
    file = root.openNextFile();
  }

  readSettings();

  Serial.print( "Init user parameter......" );
  initUserParams();
  Serial.println( "[OK]" );
  readPluginMeta();

  //----------------------------------------------------------------------------
  //--- Upload program to DSP
  //----------------------------------------------------------------------------
  uploadDspFirmware();

  //----------------------------------------------------------------------------
  //--- Upload user parameters to DSP
  //----------------------------------------------------------------------------
  uploadUserParams();

  //----------------------------------------------------------------------------
  //--- Configure AddOn
  //----------------------------------------------------------------------------
  if( Settings.addonid == ADDON_A )
    setupAddOnA();
  else if( Settings.addonid == ADDON_B )
    setupAddOnB();

  //----------------------------------------------------------------------------
  //--- Configure Webserver
  //----------------------------------------------------------------------------
  if( SPIFFS.exists( "/dsp.html" ) )
    server.on( "/",          HTTP_GET, [](AsyncWebServerRequest *request ) { request->send( SPIFFS, "/dsp.html", "text/html" ); });
  else
    server.on( "/",          HTTP_GET, [](AsyncWebServerRequest *request ) { request->send( 200, "text/html", fallback_html ); });
  server.on( "/dark.css",  HTTP_GET, [](AsyncWebServerRequest *request ) { request->send( SPIFFS, "/dark.css", "text/css" ); });
  server.on( "/input",     HTTP_GET, [](AsyncWebServerRequest *request ) { handleGetInputJson(request); });
  server.on( "/hp",        HTTP_GET, [](AsyncWebServerRequest *request ) { handleGetHpJson(request); });
  server.on( "/lshelv",    HTTP_GET, [](AsyncWebServerRequest *request ) { handleGetLshelvJson(request); });
  server.on( "/peq",       HTTP_GET, [](AsyncWebServerRequest *request ) { handleGetPeqJson(request); });
  server.on( "/hshelv",    HTTP_GET, [](AsyncWebServerRequest *request ) { handleGetHshelvJson(request); });
  server.on( "/lp",        HTTP_GET, [](AsyncWebServerRequest *request ) { handleGetLpJson(request); });
  server.on( "/phase",     HTTP_GET, [](AsyncWebServerRequest *request ) { handleGetPhaseJson(request); });
  server.on( "/delay",     HTTP_GET, [](AsyncWebServerRequest *request ) { handleGetDelayJson(request); });
  server.on( "/gain",      HTTP_GET, [](AsyncWebServerRequest *request ) { handleGetGainJson(request); });
  server.on( "/mvol",      HTTP_GET, [](AsyncWebServerRequest *request ) { handleGetMasterVolumeJson(request); });
  server.on( "/preset",    HTTP_GET, [](AsyncWebServerRequest *request ) { handleGetPresetJson(request); });
  server.on( "/config",    HTTP_GET, [](AsyncWebServerRequest *request ) { handleGetConfigJson(request); });
  server.on( "/allinputs", HTTP_GET, [](AsyncWebServerRequest *request ) { handleGetAllInputsJson(request); });
  
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
  server.on( "/config", HTTP_POST, [](AsyncWebServerRequest *request){}, NULL, [](AsyncWebServerRequest* request, uint8_t* data, size_t len, size_t index, size_t total )
  {
    handlePostConfigJson( request, data );
  });
  server.on( "/store", HTTP_POST, [](AsyncWebServerRequest *request){}, NULL, [](AsyncWebServerRequest* request, uint8_t* data, size_t len, size_t index, size_t total )
  {
    // \TODO Client does not send any JSON data
    handlePostStore( request, data );
  });
  server.on( "/addoncfg", HTTP_POST, [](AsyncWebServerRequest *request){}, NULL, [](AsyncWebServerRequest* request, uint8_t* data, size_t len, size_t index, size_t total )
  {
    handlePostAddonConfigJson( request, data );
  });
  server.on( "/wifi", HTTP_POST, [](AsyncWebServerRequest *request){}, NULL, [](AsyncWebServerRequest* request, uint8_t* data, size_t len, size_t index, size_t total )
  {
    handlePostWifiConfigJson( request, data );
  });
  server.on( "/upload", HTTP_POST, [](AsyncWebServerRequest *request){
    request->send(200, "text/plain", "OK"); 
    //AsyncWebServerResponse *response = request->beginResponse(200, "text/plain", "OK");
    //response->addHeader("Connection", "close");
    //request->send(response);
  }, NULL, [](AsyncWebServerRequest* request, uint8_t* data, size_t len, size_t index, size_t total )
  {
    handleFileUpload( request, data, len, index, total ); 
  });

//  server.onNotFound([](AsyncWebServerRequest *request){
//    Serial.println(request->url().c_str());
//  });

  //----------------------------------------------------------------------------
  //--- Configure ESP for WiFi access
  //----------------------------------------------------------------------------
  // Create a connection task with 8kB stack on core 0
  xTaskCreatePinnedToCore(myWiFiTask, "myWiFiTask", 8192, NULL, 3, NULL, 0);
  

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
