#include <Wire.h>
#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <SPIFFS.h>
#include "AsyncJson.h"
#include <ArduinoJson.h>
#include <Update.h>
#include "soc/timer_group_struct.h"
#include "soc/timer_group_reg.h"

#include "hwconfig.h"
#include "AK4458.h"
#include "AK5558.h"
#include "AudioFilterFactory.h"
#include "fallback.h"
#include "webota.h"
#include "OLED128x64_SH1106.h"

#if HAVE_ROTARYENCODER
#include "rotaryencoder.h"
#endif

#if HAVE_IRRECEIVER
#include <IRremote.h>
#endif

#define VERSION_STR "v2.1.1"

#define MAX_NUM_INPUTS 8
#define MAX_NUM_HPS 8
#define MAX_NUM_LSHELVS 8
#define MAX_NUM_PEQS 80
#define MAX_NUM_HSHELVS 8
#define MAX_NUM_LPS 8
#define MAX_NUM_PHASES 8
#define MAX_NUM_DELAYS 8
#define MAX_NUM_GAINS 8
#define MAX_NUM_CROSSOVER 8
#define MAX_NUM_FIRS 4

#define MAX_LENGTH_IR 4096

#define MAX_NUM_PRESETS 4

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
  String pwdap;
  String apname;
  int adcsum;
  bool wifiOn;
};

tSettings Settings;

typedef uint8_t tFilterType;

enum tMuxAddr
{
  ADDR_ANALOG,
  ADDR_UAC,
  ADDR_EXP,
  ADDR_ESP,
  ADDR_SPDIF,
  ADDR_OUT
};

struct tInput
{
  uint16_t addrChn[5];
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

struct tCrossover
{
  uint16_t hp_addr[4];
  float hp_fc;
  tFilterType hp_typ;
  bool hp_bypass;

  uint16_t lp_addr[4];
  float lp_fc;
  tFilterType lp_typ;
  bool lp_bypass;
};

struct tFir
{
  uint16_t addr;
  float ir[MAX_LENGTH_IR];
  bool bypass;
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
  uint16_t uac[8];
  uint16_t exp[8];
  uint16_t port[8];
};

struct tSpdifOutputSelector
{
  uint16_t addrChnLeft[6];
  uint16_t addrPortLeft;
  uint16_t addrChnRight[6];
  uint16_t addrPortRight;
};

struct tSpdifOutput
{
  uint32_t selectionLeft;
  uint32_t selectionRight;
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
tCrossover paramCrossover[8];
tFir paramFir[MAX_NUM_FIRS];
tMasterVolume masterVolume = { 0x0000, -60.0 };
tInputSelector inputSelector;
tSpdifOutput spdifOutput;
tSpdifOutputSelector spdifOutputSelector;

int numInputs = 0;
int numHPs = 0;
int numLShelvs = 0;
int numPEQs = 0;
int numHShelvs = 0;
int numLPs = 0;
int numPhases = 0;
int numDelays = 0;
int numGains = 0;
int numCrossovers = 0;
int numFIRs = 0;

File fileDspProgram;
File fileUpload;

float sampleRate = 48000.0;

uint8_t currentPreset = 0;
uint8_t currentFirUploadIdx = 0;
byte currentAddOnCfg[3];
String currentPlugInName;

uint16_t addrVPot = 0x0000;

String presetUsrparamFile[MAX_NUM_PRESETS] = { "/usrparam.001", "/usrparam.002", "/usrparam.003", "/usrparam.004" };
String presetAddonCfgFile[MAX_NUM_PRESETS] = { "/addoncfg.001", "/addoncfg.002", "/addoncfg.003", "/addoncfg.004" };

AsyncWebServer server( 80 );

bool changeWifiState = false;

//------------------------------------------------------------------------------
//
// Display Driver
//
//------------------------------------------------------------------------------
OLED128x64_SH1106 myDisplay;
bool haveDisplay = true;
bool needUpdateUI = false;

//------------------------------------------------------------------------------
//
// Rotary Encoder
//
//------------------------------------------------------------------------------
#if HAVE_ROTARYENCODER
long int lastREval = 0;
long int lastREsw = 0;
#endif

//------------------------------------------------------------------------------
//
// IR Receiver
//
//------------------------------------------------------------------------------
#if HAVE_IRRECEIVER
IRrecv irReceiver( IR_RECEIVER_PIN );
#endif

int editMode = 0;


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
/*! Converts a uint32 to a hex string with leading 0x
 *
 * \param uintval Value to be converted
 * \return Hex string
 */
String uinttohexstring( uint32_t uintval )
{
  String str = String("0x");
  for( int ii = 0; ii < 4; ii++ )
  {
    uint8_t val = (uintval>>(24-ii*8)) & 0xFF;
    if( val < 0x10 )
      str = str + String( "0") + String( val, HEX );
    else
      str = str + String( val, HEX );
  }
  return str;
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

  for( int ii = 0; ii < MAX_NUM_FIRS; ii++ )
  {
    paramFir[ii].bypass = false;
    for( int kk = 0; kk < MAX_LENGTH_IR; kk++ )
      paramFir[ii].ir[kk] = 0.0;
    paramFir[ii].ir[0] = 1.0;
  }

  for( int ii = 0; ii < MAX_NUM_HPS; ii++ )
  {
    paramHP[ii].fc = 1000.0;
    paramHP[ii].typ = 0;
    paramHP[ii].bypass = false;
  }

  for( int ii = 0; ii < MAX_NUM_LSHELVS; ii++ )
  {
    paramLshelv[ii].gain = 0.0;
    paramLshelv[ii].fc = 100.0;
    paramLshelv[ii].slope = 1.0;
    paramLshelv[ii].bypass = false;
  }

  for( int ii = 0; ii < MAX_NUM_PEQS; ii = ii + 10 )
  {
    for( int nn = 0; nn < 10; nn++ )
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
    paramLP[ii].fc = 1000.0;
    paramLP[ii].typ = 0;
    paramLP[ii].bypass = true;
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

  for( int ii = 0; ii < MAX_NUM_CROSSOVER; ii++ )
  {
    paramCrossover[ii].lp_fc = 1000.0;
    paramCrossover[ii].lp_typ = 0;
    paramCrossover[ii].lp_bypass = false;

    paramCrossover[ii].hp_fc = 1000.0;
    paramCrossover[ii].hp_typ = 0;
    paramCrossover[ii].hp_bypass = false;
  }

  masterVolume.val = -60.0;

  spdifOutput.selectionLeft = 0x00000000;
  spdifOutput.selectionRight = 0x00000000;

}

//==============================================================================
/*! Reads the device settings from JSON file.
 */
void readSettings( void )
{
  Settings.ssid = "";
  Settings.password = "";
  Settings.addonid = ADDON_CUSTOM;
  Settings.vpot = false;
  Settings.pwdap = "";
  Settings.apname = "AP-freeDSP-aurora";
  Settings.adcsum = 0;
  Settings.wifiOn = true;

  if( !SPIFFS.exists( "/settings.ini" ) )
  {
    Serial.print( "Writing default settings.ini..." );

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
    fileSettings.close();

    JsonObject jsonSettings = jsonDoc.as<JsonObject>();

    if( jsonSettings["version"].as<String>().startsWith( "1." ) )
    {
      Serial.println( "Updating from 1.x.x" );
      writeSettings();
    }

    Settings.ssid = jsonSettings["ssid"].as<String>();
    Settings.password = jsonSettings["pwd"].as<String>();
    Settings.addonid = jsonSettings["aid"].as<String>().toInt();
    if( jsonSettings["vpot"].as<String>() == "true" )
      Settings.vpot = true;
    else
      Settings.vpot = false;
    Settings.pwdap = jsonSettings["pwdap"].as<String>();
    if( !jsonSettings["apname"].isNull() )
      Settings.apname = jsonSettings["apname"].as<String>();
    Settings.adcsum = jsonSettings["adcsum"].as<String>().toInt();
    // When updating from earlier version jsonSettings["wifion"] could return "null".
    // Then it should use the default value
    if( jsonSettings["wifion"].as<String>() == "true" )
      Settings.wifiOn = true;
    else if( jsonSettings["wifion"].as<String>() == "false" )
      Settings.wifiOn = false;

    Serial.println( "[OK]" );
    Serial.println( "Device config" );
    Serial.print( "AID: " ); Serial.println( Settings.addonid );
    Serial.print( "Volume Poti: " ); Serial.println( Settings.vpot );
    Serial.print( "ADC Channel Sum: " );Serial.println( Settings.adcsum );
    Serial.println( "[OK]" );
  }
  else
    Serial.println( "[ERROR] readSettings(): Opening settings.ini failed." );
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
    jsonSettings["pwdap"] = Settings.pwdap;
    jsonSettings["apname"] = Settings.apname;
    jsonSettings["adcsum"] = Settings.adcsum;
    jsonSettings["wifion"] = Settings.wifiOn;

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
    StaticJsonDocument<5000> jsonDoc;
    DeserializationError err = deserializeJson( jsonDoc, filePluginMeta );
    if( err )
    {
      Serial.print( "[ERROR] readPluginMeta(): Deserialization failed." );
      Serial.println( err.c_str() );
      return;
    }

    JsonObject jsonPluginMeta = jsonDoc.as<JsonObject>();

    currentPlugInName = jsonPluginMeta["name"].as<String>();
    numInputs = jsonPluginMeta["nchn"].as<String>().toInt();
    numHPs = jsonPluginMeta["nhp"].as<String>().toInt();
    numLShelvs = jsonPluginMeta["nlshelv"].as<String>().toInt();
    numPEQs = jsonPluginMeta["npeq"].as<String>().toInt();
    numHShelvs = jsonPluginMeta["nhshelv"].as<String>().toInt();
    numLPs = jsonPluginMeta["nlp"].as<String>().toInt();
    numPhases = jsonPluginMeta["nphase"].as<String>().toInt();
    numDelays = jsonPluginMeta["ndly"].as<String>().toInt();
    numGains = jsonPluginMeta["ngain"].as<String>().toInt();
    numCrossovers = jsonPluginMeta["nxo"].as<String>().toInt();
    numFIRs = jsonPluginMeta["nfir"].as<String>().toInt();

    for( int ii = 0; ii < numInputs; ii++ )
      inputSelector.analog[ii] = static_cast<uint16_t>(jsonPluginMeta["analog"][ii].as<String>().toInt());

    for( int ii = 0; ii < numInputs; ii++ )
      inputSelector.spdif[ii] = static_cast<uint16_t>(jsonPluginMeta["spdif"][ii].as<String>().toInt());

    for( int ii = 0; ii < numInputs; ii++ )
      inputSelector.uac[ii] = static_cast<uint16_t>(jsonPluginMeta["uac"][ii].as<String>().toInt());

    for( int ii = 0; ii < numInputs; ii++ )
      inputSelector.exp[ii] = static_cast<uint16_t>(jsonPluginMeta["exp"][ii].as<String>().toInt());

    for( int ii = 0; ii < numInputs; ii++ )
      inputSelector.port[ii] = static_cast<uint16_t>(jsonPluginMeta["port"][ii].as<String>().toInt());

    for( int ii = 0; ii < numInputs; ii++ )
    {
      paramInputs[ii].addrChn[ADDR_ANALOG] = static_cast<uint16_t>(jsonPluginMeta["analog"][ii].as<String>().toInt());
      paramInputs[ii].addrChn[ADDR_UAC] = static_cast<uint16_t>(jsonPluginMeta["uac"][ii].as<String>().toInt());
      paramInputs[ii].addrChn[ADDR_EXP] = static_cast<uint16_t>(jsonPluginMeta["exp"][ii].as<String>().toInt());
      //paramInputs[ii].addrChn[ADDR_ESP] = static_cast<uint16_t>(jsonPluginMeta["esp"][ii].as<String>().toInt());
      paramInputs[ii].addrChn[ADDR_SPDIF] = static_cast<uint16_t>(jsonPluginMeta["spdif"][ii].as<String>().toInt());
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

    for( int ii = 0; ii < numCrossovers; ii++ )
    {
      paramCrossover[ii].hp_addr[0] = static_cast<uint16_t>(jsonPluginMeta["xohp"][0+ii*4]);
      paramCrossover[ii].hp_addr[1] = static_cast<uint16_t>(jsonPluginMeta["xohp"][1+ii*4]);
      paramCrossover[ii].hp_addr[2] = static_cast<uint16_t>(jsonPluginMeta["xohp"][2+ii*4]);
      paramCrossover[ii].hp_addr[3] = static_cast<uint16_t>(jsonPluginMeta["xohp"][3+ii*4]);

      paramCrossover[ii].lp_addr[0] = static_cast<uint16_t>(jsonPluginMeta["xolp"][0+ii*4]);
      paramCrossover[ii].lp_addr[1] = static_cast<uint16_t>(jsonPluginMeta["xolp"][1+ii*4]);
      paramCrossover[ii].lp_addr[2] = static_cast<uint16_t>(jsonPluginMeta["xolp"][2+ii*4]);
      paramCrossover[ii].lp_addr[3] = static_cast<uint16_t>(jsonPluginMeta["xolp"][3+ii*4]);
    }

    for( int ii = 0; ii < numFIRs; ii++ )
      paramFir[ii].addr = static_cast<uint16_t>(jsonPluginMeta["fir"][ii]);

    masterVolume.addr = jsonPluginMeta["master"].as<String>().toInt();
    addrVPot = jsonPluginMeta["vpot"].as<String>().toInt();

    //--- Read the addresses of the SPDIF output multiplexer
    spdifOutputSelector.addrChnLeft[ADDR_ANALOG] = static_cast<uint16_t>(jsonPluginMeta["spdifout"][ADDR_ANALOG]);
    spdifOutputSelector.addrChnLeft[ADDR_UAC] = static_cast<uint16_t>(jsonPluginMeta["spdifout"][ADDR_UAC]);
    spdifOutputSelector.addrChnLeft[ADDR_EXP] = static_cast<uint16_t>(jsonPluginMeta["spdifout"][ADDR_EXP]);
    spdifOutputSelector.addrChnLeft[ADDR_ESP] = static_cast<uint16_t>(jsonPluginMeta["spdifout"][ADDR_ESP]);
    spdifOutputSelector.addrChnLeft[ADDR_SPDIF] = static_cast<uint16_t>(jsonPluginMeta["spdifout"][ADDR_SPDIF]);
    spdifOutputSelector.addrChnLeft[ADDR_OUT] = static_cast<uint16_t>(jsonPluginMeta["spdifout"][ADDR_OUT]);

    spdifOutputSelector.addrChnRight[ADDR_ANALOG] = static_cast<uint16_t>(jsonPluginMeta["spdifout"][6+ADDR_ANALOG]);
    spdifOutputSelector.addrChnRight[ADDR_UAC] = static_cast<uint16_t>(jsonPluginMeta["spdifout"][6+ADDR_UAC]);
    spdifOutputSelector.addrChnRight[ADDR_EXP] = static_cast<uint16_t>(jsonPluginMeta["spdifout"][6+ADDR_EXP]);
    spdifOutputSelector.addrChnRight[ADDR_ESP] = static_cast<uint16_t>(jsonPluginMeta["spdifout"][6+ADDR_ESP]);
    spdifOutputSelector.addrChnRight[ADDR_SPDIF] = static_cast<uint16_t>(jsonPluginMeta["spdifout"][6+ADDR_SPDIF]);
    spdifOutputSelector.addrChnRight[ADDR_OUT] = static_cast<uint16_t>(jsonPluginMeta["spdifout"][6+ADDR_OUT]);

    spdifOutputSelector.addrPortLeft = static_cast<uint16_t>(jsonPluginMeta["spdifout"][12]);
    spdifOutputSelector.addrPortRight = static_cast<uint16_t>(jsonPluginMeta["spdifout"][13]);
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
      // IMPRTANT: don't copy the addresses, they may have changed by dsp firmware
      // and are defined by meta data of plugin. Reading it from usrparam file may 
      // go wrong after firmware update.
      Serial.print( "Uploading user parameters from " + fileName );
      uint32_t totalSize = 0;
      for( int ii = 0; ii < numInputs; ii++ )
      {
        tInput paramInputTemp;
        size_t len = fileUserParams.read( (uint8_t*)&(paramInputTemp), sizeof(tInput) );
        if( len != sizeof(tInput) )
          Serial.println( "[ERROR] Reading inputs from " + presetUsrparamFile[currentPreset] );
        else
          paramInputs[ii].sel = paramInputTemp.sel;     
        totalSize += len;
      }

      for( int ii = 0; ii < numFIRs; ii++ )
      {
        // save the old address
        uint16_t addrTemp = paramFir[ii].addr;
        size_t len = fileUserParams.read( (uint8_t*)&(paramFir[ii]), sizeof(tFir) );
        if( len != sizeof(tFir) )
        {
          Serial.println( "[ERROR] Reading FIR from " + presetUsrparamFile[currentPreset] );
          for( int kk = 0; kk < MAX_LENGTH_IR; kk++ )
            paramFir[ii].ir[kk] = 0.0;
          paramFir[ii].ir[0] = 1.0;
        }
        else
          paramFir[ii].addr = addrTemp;
        totalSize += len;
      }

      for( int ii = 0; ii < numHPs; ii++ )
      {
        tHPLP paramHpTemp;
        size_t len = fileUserParams.read( (uint8_t*)&(paramHpTemp), sizeof(tHPLP) );
        if( len != sizeof(tHPLP) )
          Serial.println( "[ERROR] Reading HPs from " + presetUsrparamFile[currentPreset] );
        else
        {
          paramHP[ii].fc = paramHpTemp.fc;
          paramHP[ii].typ = paramHpTemp.typ;
          paramHP[ii].bypass = paramHpTemp.bypass;
        }
        totalSize += len;
      }

      for( int ii = 0; ii < numLShelvs; ii++ )
      {
        tShelving paramLShelvTemp;
        size_t len = fileUserParams.read( (uint8_t*)&(paramLShelvTemp), sizeof(tShelving) );
        if( len != sizeof(tShelving) )
          Serial.println( "[ERROR] Reading LShelvs from " + presetUsrparamFile[currentPreset] );
        else
        {
          paramLshelv[ii].gain = paramLShelvTemp.gain;
          paramLshelv[ii].fc = paramLShelvTemp.fc;
          paramLshelv[ii].slope = paramLShelvTemp.slope;
          paramLshelv[ii].bypass = paramLShelvTemp.bypass;
        }
        totalSize += len;
      }

      for( int ii = 0; ii < numPEQs; ii++ )
      {
        tPeq paramPeqTemp;
        size_t len = fileUserParams.read( (uint8_t*)&(paramPeqTemp), sizeof(tPeq) );
        if( len != sizeof(tPeq) )
          Serial.println( "[ERROR] Reading PEQs from " + presetUsrparamFile[currentPreset] );
        else
        {
          paramPeq[ii].gain = paramPeqTemp.gain;
          paramPeq[ii].fc = paramPeqTemp.fc;
          paramPeq[ii].Q = paramPeqTemp.Q;
          paramPeq[ii].bypass = paramPeqTemp.bypass;
        }
        totalSize += len;
      }

      for( int ii = 0; ii < numHShelvs; ii++ )
      {
        tShelving paramHShelvTemp;
        size_t len = fileUserParams.read( (uint8_t*)&(paramHShelvTemp), sizeof(tShelving) );
        if( len != sizeof(tShelving) )
          Serial.println( "[ERROR] Reading HShelvs from " + presetUsrparamFile[currentPreset] );
        else
        {
          paramHshelv[ii].gain = paramHShelvTemp.gain;
          paramHshelv[ii].fc = paramHShelvTemp.fc;
          paramHshelv[ii].slope = paramHShelvTemp.slope;
          paramHshelv[ii].bypass = paramHShelvTemp.bypass;
        }
        totalSize += len;
      }

      for( int ii = 0; ii < numCrossovers; ii++ )
      {
        tCrossover paramCrossoverTemp;
        size_t len = fileUserParams.read( (uint8_t*)&(paramCrossoverTemp), sizeof(tCrossover) );
        if( len != sizeof(tCrossover) )
          Serial.println( "[ERROR] Reading XO from " + presetUsrparamFile[currentPreset] );
        else
        {
          paramCrossover[ii].hp_fc = paramCrossoverTemp.hp_fc;
          paramCrossover[ii].hp_typ = paramCrossoverTemp.hp_typ;
          paramCrossover[ii].hp_bypass = paramCrossoverTemp.hp_bypass;
          paramCrossover[ii].lp_fc = paramCrossoverTemp.lp_fc;
          paramCrossover[ii].lp_typ = paramCrossoverTemp.lp_typ;
          paramCrossover[ii].lp_bypass = paramCrossoverTemp.lp_bypass;
        }
        totalSize += len;
      }

      for( int ii = 0; ii < numLPs; ii++ )
      {
        tHPLP paramLpTemp;
        size_t len = fileUserParams.read( (uint8_t*)&(paramLpTemp), sizeof(tHPLP) );
        if( len != sizeof(tHPLP) )
          Serial.println( "[ERROR] Reading LPs from " + presetUsrparamFile[currentPreset] );
        else
        {
          paramLP[ii].fc = paramLpTemp.fc;
          paramLP[ii].typ = paramLpTemp.typ;
          paramLP[ii].bypass = paramLpTemp.bypass;
        }
        totalSize += len;
      }

      for( int ii = 0; ii < numPhases; ii++ )
      {
        tPhase paramPhaseTemp;
        size_t len = fileUserParams.read( (uint8_t*)&(paramPhaseTemp), sizeof(tPhase) );
        if( len != sizeof(tPhase) )
          Serial.println( "[ERROR] Reading Phases from " + presetUsrparamFile[currentPreset] );
        else
        {
          paramPhase[ii].fc = paramPhaseTemp.fc;
          paramPhase[ii].inv = paramPhaseTemp.inv;
          paramPhase[ii].Q = paramPhaseTemp.Q;
        }
        totalSize += len;
      }

      for( int ii = 0; ii < numDelays; ii++ )
      {
        tDelay paramDelayTemp;
        size_t len = fileUserParams.read( (uint8_t*)&(paramDelayTemp), sizeof(tDelay) );
        if( len != sizeof(tDelay) )
          Serial.println( "[ERROR] Reading Delays from " + presetUsrparamFile[currentPreset] );
        else
        {
          paramDelay[ii].delay = paramDelayTemp.delay;
          paramDelay[ii].bypass = paramDelayTemp.bypass;
        }
        totalSize += len;
      }

      for( int ii = 0; ii < numGains; ii++ )
      {
        tGain paramGainTemp;
        size_t len = fileUserParams.read( (uint8_t*)&(paramGainTemp), sizeof(tGain) );
        if( len != sizeof(tGain) )
          Serial.println( "[ERROR] Reading Gains from " + presetUsrparamFile[currentPreset] );
        else
        {
          paramGain[ii].gain = paramGainTemp.gain;
          paramGain[ii].mute = paramGainTemp.mute;
        }
        totalSize += len;
      }

      tMasterVolume masterVolumeTemp;
      size_t len = fileUserParams.read( (uint8_t*)&masterVolumeTemp, sizeof(tMasterVolume) );
      if( len != sizeof(tMasterVolume) )
        Serial.println( "[ERROR] Reading masterVolume from " + presetUsrparamFile[currentPreset] );
      else
        masterVolume.val = masterVolumeTemp.val;
      totalSize += len;

      tSpdifOutput spdifOutputTemp;
      len = fileUserParams.read( (uint8_t*)&spdifOutputTemp, sizeof(tSpdifOutput) );
      if( len != sizeof(tSpdifOutput) )
        Serial.println( "[ERROR] Reading spdifOutput from " + presetUsrparamFile[currentPreset] );
      else
      {
        spdifOutput.selectionLeft = spdifOutputTemp.selectionLeft;
        spdifOutput.selectionRight = spdifOutputTemp.selectionRight;
      }
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
    setInput( ii );
  Serial.print( "." );

  for( int ii = 0; ii < numFIRs; ii++ )
  {
    setFir( ii );
    Serial.print( "." );
  }

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

  for( int ii = 0; ii < numCrossovers; ii++ )
    setCrossover( ii );
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

  setSpdifOutputRouting();

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
/*! Change the channel summation of AK5558 ADC
 */
void changeChannelSummationADC( void )
{
  AK5558_REGWRITE( AK5558_POWERMANAGEMENT2, 0b00000000 );
  delay(100);

  // Normal operation
  if( Settings.adcsum == 0 )
    AK5558_REGWRITE( AK5558_POWERMANAGEMENT2, 0b00000001 );
  // 8-to-4 mode
  else if( Settings.adcsum == 1 )
    AK5558_REGWRITE( AK5558_POWERMANAGEMENT2, 0b00000101 );
  // 8-to-2 mode
  else if( Settings.adcsum == 2 )
    AK5558_REGWRITE( AK5558_POWERMANAGEMENT2, 0b00000011 );
  // 8-to-1 mode
  else if( Settings.adcsum == 3 )
    AK5558_REGWRITE( AK5558_POWERMANAGEMENT2, 0b00000111 );
  // fallback to normal operation
  else
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
/*! Set DAC into reset.
 */
void resetDAC( bool rst )
{
  if( rst )
    AK4458_REGWRITE( AK4458_CONTROL1, 0b00001100 );
  else
    AK4458_REGWRITE( AK4458_CONTROL1, 0b00001101 );
}

//==============================================================================
/*! Mute DAC
 */
void softMuteDAC( void )
{
  AK4458_REGWRITE( AK4458_CONTROL2, 0b00100011 );
  delay( 500 );
}

//==============================================================================
/*! Unmute DAC
 */
void softUnmuteDAC( void )
{
  AK4458_REGWRITE( AK4458_CONTROL2, 0b00100010 );
}

//==============================================================================
/*! Changes the routing for the SPDIF output
 */
void setSpdifOutputRouting( void )
{
  uint32_t sel = (spdifOutput.selectionLeft >> 16) & 0x0000ffff;
  uint16_t addrChn = spdifOutputSelector.addrChnLeft[sel];
  uint16_t addrPort = spdifOutputSelector.addrPortLeft;
  sel = spdifOutput.selectionLeft;

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

  sel = (spdifOutput.selectionRight >> 16) & 0x0000ffff;
  addrChn = spdifOutputSelector.addrChnRight[sel];
  addrPort = spdifOutputSelector.addrPortRight;
  sel = spdifOutput.selectionRight;

  intval = sel & 0x0000ffff;
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
    if( paramPhase[offset].inv )
      jsonResponse["inv"] = String( "1" );
    else
      jsonResponse["inv"] = String( "0" );

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
/*! Handles the GET request for crossover parameters
 *
 */
void handleGetXoJson( AsyncWebServerRequest* request )
{
  Serial.println( "GET /xo" );

  AsyncJsonResponse* response = new AsyncJsonResponse();

  if( request->hasParam( "idx" ) )
  {
    AsyncWebParameter* idx = request->getParam(0);
    int offset = idx->value().toInt();
    JsonVariant& jsonResponse = response->getRoot();
    jsonResponse["lp_typ"] = paramCrossover[offset].lp_typ;
    jsonResponse["lp_fc"] = paramCrossover[offset].lp_fc;
    if( paramCrossover[offset].lp_bypass )
      jsonResponse["lp_bypass"] = String( "1" );
    else
      jsonResponse["lp_bypass"] = String( "0" );
    jsonResponse["hp_typ"] = paramCrossover[offset].hp_typ;
    jsonResponse["hp_fc"] = paramCrossover[offset].hp_fc;
    if( paramCrossover[offset].hp_bypass )
      jsonResponse["hp_bypass"] = String( "1" );
    else
      jsonResponse["hp_bypass"] = String( "0" );
  }
  else
    Serial.println( "[ERROR] handleGetXoJson(): No id param" );

  response->setLength();
  request->send(response);
}

//==============================================================================
/*! Handles the GET request for a FIR impulse response
 *
 */
void handleGetFirJson( AsyncWebServerRequest* request )
{
  Serial.println( "GET /fir" );

  AsyncJsonResponse* response = new AsyncJsonResponse();

  if( request->hasParam( "idx" ) )
  {
    AsyncWebParameter* idx = request->getParam(0);
    int offset = idx->value().toInt();
    JsonVariant& jsonResponse = response->getRoot();

    if( paramFir[offset].bypass )
      jsonResponse["bypass"] = String( "1" );
    else
      jsonResponse["bypass"] = String( "0" );
  }
  else
    Serial.println( "[ERROR] handleGetFirJson(): No id param" );

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

  jsonResponse["adcsum"] = Settings.adcsum;

  response->setLength();
  request->send(response);
}

//==============================================================================
/*! Handles the GET request for device configuration
 *
 */
void handleGetAddonConfigJson( AsyncWebServerRequest* request )
{
  Serial.println( "GET /addoncfg" );

  AsyncJsonResponse* response = new AsyncJsonResponse();
  JsonVariant& jsonResponse = response->getRoot();

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
/*! Handles the GET request for bypass status of all dsp blocks
 *
 */
String handleGetAllBypJson( void )
{
  Serial.println( "GET /allbyp" );

  // Build the JSON response manually. Via ArduinoJson it did not work somehow.
  String array( "{\"byp\":[" );
  for( int ii = 0; ii < numHPs; ii++ )
  {
    array += String("{\"name\":\"hp") + String(ii) + String("\",\"val\":");

    if( paramHP[ii].bypass )
      array += String( "1}" );
    else
      array += String( "0}" );

    array += String( "," );
  }
  for( int ii = 0; ii < numLShelvs; ii++ )
  {
    array += String("{\"name\":\"ls") + String(ii) + String("\",\"val\":");

    if( paramLshelv[ii].bypass )
      array += String( "1}" );
    else
      array += String( "0}" );

    array += String( "," );
  }
  for( int ii = 0; ii < numPEQs; ii++ )
  {
    array += String("{\"name\":\"peq") + String(ii) + String("\",\"val\":");

    if( paramPeq[ii].bypass )
      array += String( "1}" );
    else
      array += String( "0}" );

    array += String( "," );
  }
  for( int ii = 0; ii < numHShelvs; ii++ )
  {
    array += String("{\"name\":\"hs") + String(ii) + String("\",\"val\":");

    if( paramHshelv[ii].bypass )
      array += String( "1}" );
    else
      array += String( "0}" );

    array += String( "," );
  }
  for( int ii = 0; ii < numLPs; ii++ )
  {
    array += String("{\"name\":\"lp") + String(ii) + String("\",\"val\":");

    if( paramLP[ii].bypass )
      array += String( "1}" );
    else
      array += String( "0}" );

   array += String( "," );
  }
  for( int ii = 0; ii < numPhases; ii++ )
  {
    array += String("{\"name\":\"ph") + String(ii) + String("\",\"val\":");

    if( paramPhase[ii].bypass )
      array += String( "1}" );
    else
      array += String( "0}" );

    array += String( "," );
  }
  for( int ii = 0; ii < numDelays; ii++ )
  {
    array += String("{\"name\":\"dly") + String(ii) + String("\",\"val\":");

    if( paramDelay[ii].bypass )
      array += String( "1}" );
    else
      array += String( "0}" );

   array += String( "," );
  }
  for( int ii = 0; ii < numGains; ii++ )
  {
    array += String("{\"name\":\"gn") + String(ii) + String("\",\"val\":");

    if( paramGain[ii].mute )
      array += String( "1}" );
    else
      array += String( "0}" );

    array += String( "," );
  }
  for( int ii = 0; ii < numCrossovers; ii++ )
  {
    array += String("{\"name\":\"xo") + String(ii) + String("\",\"val\":");

    if( paramCrossover[ii].lp_bypass || paramCrossover[ii].hp_bypass )
      array += String( "1}" );
    else
      array += String( "0}" );

    array += String( "," );
  }
  for( int ii = 0; ii < numFIRs; ii++ )
  {
    array += String("{\"name\":\"fir") + String(ii) + String("\",\"val\":");

    if( paramFir[ii].bypass )
      array += String( "1}" );
    else
      array += String( "0}" );

    array += String( "," );
  }

  if( array.length() > 1 )
   array = array.substring( 0, array.length()-1 );

  array += String( "]}" );

  return array;
}

//==============================================================================
/*! Handles the GET request for fc of all dsp blocks
 *
 */
String handleGetAllFcJson( void )
{
  Serial.println( "GET /allfc" );

  // Build the JSON response manually. Via ArduinoJson it did not work somehow.
  String array( "{\"fc\":[" );
  for( int ii = 0; ii < numHPs; ii++ )
  {
    array += String("{\"name\":\"hp") + String(ii) + String("\",\"val\":");
    if( paramHP[ii].fc < 1000.0 )
      array += String( "\"HP<br><h4>" ) + String( static_cast<int>(paramHP[ii].fc) ) + String( " Hz</h4>\"}" );
    else
    {
      char buf[20];
      dtostrf( paramHP[ii].fc/1000.0 , 1, 1, buf );
      array += String( "\"HP<br><h4>" ) + String( buf ) + String( " kHz</h4>\"}" );
    }
    array += String( "," );
  }
  for( int ii = 0; ii < numLShelvs; ii++ )
  {
    array += String("{\"name\":\"ls") + String(ii) + String("\",\"val\":");
    char buf[20];
    dtostrf( paramLshelv[ii].gain , 1, 1, buf );
    array += String( "\"LShlv<br><h4>" ) + String( buf ) + String( " dB</h4>\"}" );
    array += String( "," );
  }
  for( int ii = 0; ii < numPEQs; ii++ )
  {
    array += String("{\"name\":\"peq") + String(ii) + String("\",\"val\":");
    if( paramPeq[ii].fc < 1000.0 )
      array += String( "\"PEQ<br><h4>" ) + String( static_cast<int>(paramPeq[ii].fc) ) + String( " Hz</h4>\"}" );
    else
    {
      char buf[20];
      dtostrf( paramPeq[ii].fc/1000.0 , 1, 1, buf );
      array += String( "\"PEQ<br><h4>" ) + String( buf ) + String( " kHz</h4>\"}" );
    }
    array += String( "," );
  }
  for( int ii = 0; ii < numHShelvs; ii++ )
  {
    array += String("{\"name\":\"hs") + String(ii) + String("\",\"val\":");
    char buf[20];
    dtostrf( paramHshelv[ii].gain , 1, 1, buf );
    array += String( "\"HShlv<br><h4>" ) + String( buf ) + String( " dB</h4>\"}" );
    array += String( "," );
  }
  for( int ii = 0; ii < numLPs; ii++ )
  {
    array += String("{\"name\":\"lp") + String(ii) + String("\",\"val\":");
    if( paramLP[ii].fc < 1000.0 )
      array += String( "\"LP<br><h4>" ) + String( static_cast<int>(paramLP[ii].fc) ) + String( " Hz</h4>\"}" );
    else
    {
      char buf[20];
      dtostrf( paramLP[ii].fc/1000.0 , 1, 1, buf );
      array += String( "\"LP<br><h4>" ) + String( buf ) + String( " kHz</h4>\"}" );
    }
    array += String( "," );
  }
  for( int ii = 0; ii < numPhases; ii++ )
  {
    array += String("{\"name\":\"ph") + String(ii) + String("\",\"val\":");
    if( paramPhase[ii].fc < 1000.0 )
      array += String( "\"Phase<br><h4>" ) + String( static_cast<int>(paramPhase[ii].fc) ) + String( " Hz</h4>\"}" );
    else
    {
      char buf[20];
      dtostrf( paramPhase[ii].fc/1000.0 , 1, 1, buf );
      array += String( "\"Phase<br><h4>" ) + String( buf ) + String( " kHz</h4>\"}" );
    }
    array += String( "," );
  }
  for( int ii = 0; ii < numDelays; ii++ )
  {
    array += String("{\"name\":\"dly") + String(ii) + String("\",\"val\":");
    char buf[20];
    dtostrf( paramDelay[ii].delay, 1, 1, buf );
    array += String( "\"Delay<br><h4>" ) + String( buf ) + String( " ms</h4>\"}" );
    array += String( "," );
  }
  for( int ii = 0; ii < numGains; ii++ )
  {
    array += String("{\"name\":\"gn") + String(ii) + String("\",\"val\":");
    char buf[20];
    dtostrf( paramGain[ii].gain , 1, 1, buf );
    array += String( "\"Gain<br><h4>" ) + String( buf ) + String( " dB</h4>\"}" );
    array += String( "," );
  }

  if( array.length() > 1 )
   array = array.substring( 0, array.length()-1 );

  array += String( "]}" );

  return array;
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

  response->setLength();
  request->send(response);
}

//==============================================================================
/*! Handles the GET request for SPDIF output multiplexer
 *
 */
void handleGetSpdifOutJson( AsyncWebServerRequest* request )
{
  Serial.println( "GET /spdifout" );

  AsyncJsonResponse* response = new AsyncJsonResponse();
  JsonVariant& jsonResponse = response->getRoot();

  jsonResponse["spdifleft"] = uinttohexstring( spdifOutput.selectionLeft );
  jsonResponse["spdifright"] = uinttohexstring( spdifOutput.selectionRight );

  response->setLength();
  request->send(response);
}

//==============================================================================
/*! Handles the GET request for access point configuration
 *
 */
void handleGetWifiConfigJson( AsyncWebServerRequest* request )
{
  Serial.println( "GET /wificonfig" );

  AsyncJsonResponse* response = new AsyncJsonResponse();
  JsonVariant& jsonResponse = response->getRoot();
  jsonResponse["apname"] = Settings.apname;
  jsonResponse["ssid"] = Settings.ssid;

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
    request->send( 400, "text/plain", err.c_str() );
    return;
  }

  softMuteDAC();

  JsonObject root = jsonDoc.as<JsonObject>();

  int idx = root["idx"].as<String>().toInt();
  paramInputs[idx].sel = (uint32_t)strtoul( root["sel"].as<String>().c_str(), NULL, 16 );

  setInput( idx );

  request->send(200, "text/plain", "");

  softUnmuteDAC();
}

//==============================================================================
/*! Sets a new input selection on DSP.
 *
 */
void setInput( const int idx )
{
  uint32_t sel = (paramInputs[idx].sel >> 16) & 0x0000ffff;
  uint16_t addrChn = paramInputs[idx].addrChn[sel];
  uint16_t addrPort = paramInputs[idx].addrPort;
  sel = paramInputs[idx].sel;

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

  DynamicJsonDocument jsonDoc(1024);
  DeserializationError err = deserializeJson( jsonDoc, (const char*)data );
  if( err )
  {
    Serial.print( "[ERROR] handlePostHpJson(): Deserialization failed. " );
    Serial.println( err.c_str() );
    request->send( 400, "text/plain", err.c_str() );
    return;
  }

  softMuteDAC();

  JsonObject root = jsonDoc.as<JsonObject>();

  uint32_t idx = static_cast<uint32_t>(root["idx"].as<String>().toInt());
  paramHP[idx].fc = root["fc"].as<String>().toFloat();
  paramHP[idx].typ = static_cast<tFilterType>(root["typ"].as<String>().toInt());
  if( root["bypass"].as<String>().toInt() == 0 )
    paramHP[idx].bypass = false;
  else
    paramHP[idx].bypass = true;

  setHighPass( idx );

  request->send(200, "text/plain", "");

  softUnmuteDAC();

}

//==============================================================================
/*! Sets the values for a highpass block on DSP.
 *
 */
void setHighPass( int idx )
{
  if( (paramHP[idx].fc > 0.0) && (paramHP[idx].fc < 20000.0)
      && (paramHP[idx].typ >= 0) && (paramHP[idx].typ < AudioFilterFactory::kNumFilterDesigns) )
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
    request->send( 400, "text/plain", err.c_str() );
    return;
  }

  softMuteDAC();

  JsonObject root = jsonDoc.as<JsonObject>();
  Serial.println( root["idx"].as<String>() );
  Serial.println( root["addr"].as<String>() );
  Serial.println( root["gain"].as<String>() );
  Serial.println( root["fc"].as<String>() );
  Serial.println( root["slope"].as<String>() );

  uint32_t idx = static_cast<uint32_t>(root["idx"].as<String>().toInt());
  paramLshelv[idx].gain = root["gain"].as<String>().toFloat();
  paramLshelv[idx].fc = root["fc"].as<String>().toFloat();
  paramLshelv[idx].slope = root["slope"].as<String>().toFloat();
  if( root["bypass"].as<String>().toInt() == 0 )
    paramLshelv[idx].bypass = false;
  else
    paramLshelv[idx].bypass = true;

  setLowShelving( idx );

  request->send(200, "text/plain", "");

  softUnmuteDAC();
}

//==============================================================================
/*! Sets the values for a low shelving block on DSP.
 *
 */
void setLowShelving( int idx )
{
  if( (paramLshelv[idx].fc > 0) && (paramLshelv[idx].fc < 20000)
      && (paramLshelv[idx].gain >= -24.0) && (paramLshelv[idx].gain <= 24.0)
      && (paramLshelv[idx].slope >= 0.1) && (paramLshelv[idx].slope <= 2.0) )
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
    request->send( 400, "text/plain", err.c_str() );
    return;
  }

  softMuteDAC();

  JsonObject root = jsonDoc.as<JsonObject>();
  Serial.println( root["idx"].as<String>() );
  Serial.println( root["gain"].as<String>() );
  Serial.println( root["fc"].as<String>() );
  Serial.println( root["Q"].as<String>() );

  uint32_t idx = static_cast<uint32_t>(root["idx"].as<String>().toInt());
  paramPeq[idx].gain = root["gain"].as<String>().toFloat();
  paramPeq[idx].fc = root["fc"].as<String>().toFloat();
  paramPeq[idx].Q = root["Q"].as<String>().toFloat();
  if( root["bypass"].as<String>().toInt() == 0 )
    paramPeq[idx].bypass = false;
  else
    paramPeq[idx].bypass = true;

  setPEQ( idx );

  request->send(200, "text/plain", "");

  softUnmuteDAC();
}

//==============================================================================
/*! Sets the values for a peq block on DSP.
 *
 */
void setPEQ( int idx )
{
  if( (paramPeq[idx].fc > 0.0) && (paramPeq[idx].fc < 20000.0)
    && (paramPeq[idx].gain >= -24.0) && (paramPeq[idx].gain <= 24.0)
    && (paramPeq[idx].Q >= 0.1) && (paramPeq[idx].Q <= 100.0) )
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
    request->send( 400, "text/plain", err.c_str() );
    return;
  }

  softMuteDAC();

  JsonObject root = jsonDoc.as<JsonObject>();
  Serial.println( root["idx"].as<String>() );
  Serial.println( root["addr"].as<String>() );
  Serial.println( root["gain"].as<String>() );
  Serial.println( root["fc"].as<String>() );
  Serial.println( root["slope"].as<String>() );

  uint32_t idx = static_cast<uint32_t>(root["idx"].as<String>().toInt());
  paramHshelv[idx].gain = root["gain"].as<String>().toFloat();
  paramHshelv[idx].fc = root["fc"].as<String>().toFloat();
  paramHshelv[idx].slope = root["slope"].as<String>().toFloat();
  if( root["bypass"].as<String>().toInt() == 0 )
    paramHshelv[idx].bypass = false;
  else
    paramHshelv[idx].bypass = true;

  setHighShelving( idx );

  request->send(200, "text/plain", "");

  softUnmuteDAC();
}

//==============================================================================
/*! Sets the values for a high shelving block on DSP.
 *
 */
void setHighShelving( int idx )
{
  if( (paramHshelv[idx].fc > 0.0) && (paramHshelv[idx].fc < 20000.0)
      && (paramHshelv[idx].gain >= -24.0) && (paramHshelv[idx].gain <= 24.0)
      && (paramHshelv[idx].slope >= 0.1) && (paramHshelv[idx].slope <= 2.0) )
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
    request->send( 400, "text/plain", err.c_str() );
    return;
  }

  softMuteDAC();

  JsonObject root = jsonDoc.as<JsonObject>();
  Serial.println( root["idx"].as<String>() );
  Serial.println( root["addr"].as<String>() );
  Serial.println( root["fc"].as<String>() );
  Serial.println( root["typ"].as<String>() );
  Serial.println( root["bypass"].as<String>() );

  uint32_t idx = static_cast<uint32_t>(root["idx"].as<String>().toInt());
  paramLP[idx].fc = root["fc"].as<String>().toFloat();
  paramLP[idx].typ = static_cast<tFilterType>(root["typ"].as<String>().toInt());
  if( root["bypass"].as<String>().toInt() == 0 )
    paramLP[idx].bypass = false;
  else
    paramLP[idx].bypass = true;

  setLowPass( idx );

  request->send(200, "text/plain", "");

  softUnmuteDAC();
}

//==============================================================================
/*! Sets the values for a low pass block on DSP.
 *
 */
void setLowPass( int idx )
{
  if( (paramLP[idx].fc > 0.0) && (paramLP[idx].fc < 20000.0)
      && (paramLP[idx].typ >= 0) && (paramLP[idx].typ < AudioFilterFactory::kNumFilterDesigns) )
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
    request->send( 400, "text/plain", err.c_str() );
    return;
  }

  softMuteDAC();

  JsonObject root = jsonDoc.as<JsonObject>();
  Serial.println( root["idx"].as<String>() );
  Serial.println( root["fc"].as<String>() );
  Serial.println( root["Q"].as<String>() );
  Serial.println( root["inv"].as<String>() );
  Serial.println( root["bypass"].as<String>() );

  uint32_t idx = static_cast<uint32_t>(root["idx"].as<String>().toInt());
  paramPhase[idx].fc = root["fc"].as<String>().toFloat();
  paramPhase[idx].Q = root["Q"].as<String>().toFloat();
  if( root["inv"].as<String>() == "true" )
    paramPhase[idx].inv = true;
  else
    paramPhase[idx].inv = false;

  if( root["bypass"].as<String>().toInt() == 0 )
    paramPhase[idx].bypass = false;
  else
    paramPhase[idx].bypass = true;

  setPhase( idx );

  request->send(200, "text/plain", "");

  softUnmuteDAC();
}

//==============================================================================
/*! Sets the values for a phase block on DSP.
 *
 */
void setPhase( int idx )
{
  if( (paramPhase[idx].fc > 0.0) && (paramPhase[idx].fc < 20000.0)
    && (paramPhase[idx].Q >= 0.1) && (paramPhase[idx].Q <= 100.0) )
  {
    float a[3] = { 1.0, 0.0, 0.0 };
    float b[3] = { 1.0, 0.0, 0.0 };
    byte val[4];
    uint32_t floatval;
    if( !paramPhase[idx].bypass )
      AudioFilterFactory::makeAllpass( a, b, paramPhase[idx].fc, paramPhase[idx].Q, sampleRate );

    if( paramPhase[idx].inv == true )
    {
      Serial.println("Inverting");
      b[0] *= -1.0;
      b[1] *= -1.0;
      b[2] *= -1.0;
    }

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
    request->send( 400, "text/plain", err.c_str() );
    return;
  }

  softMuteDAC();

  JsonObject root = jsonDoc.as<JsonObject>();
  Serial.println( root["idx"].as<String>() );
  Serial.println( root["delay"].as<String>() );

  uint32_t idx = static_cast<uint32_t>(root["idx"].as<String>().toInt());
  paramDelay[idx].delay = root["delay"].as<String>().toFloat();
  if( root["bypass"].as<String>().toInt() == 0 )
    paramDelay[idx].bypass = false;
  else
    paramDelay[idx].bypass = true;

  setDelay( idx );

  request->send(200, "text/plain", "");

  softUnmuteDAC();
}

//==============================================================================
/*! Sets the values for a delay block on DSP.
 *
 */
void setDelay( int idx )
{
  if( (paramDelay[idx].delay >= 0) && (paramDelay[idx].delay <= 100) )
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
    request->send( 400, "text/plain", err.c_str() );
    return;
  }

  softMuteDAC();

  JsonObject root = jsonDoc.as<JsonObject>();
  Serial.println( root["idx"].as<String>() );
  Serial.println( root["gain"].as<String>() );
  Serial.println( root["mute"].as<String>() );

  uint32_t idx = static_cast<uint32_t>(root["idx"].as<String>().toInt());
  paramGain[idx].gain = root["gain"].as<String>().toFloat();
  if( root["mute"].as<String>().toInt() == 0 )
    paramGain[idx].mute = false;
  else
    paramGain[idx].mute = true;

  setGain( idx );

  request->send(200, "text/plain", "");

  softUnmuteDAC();
}

//==============================================================================
/*! Sets the values for a gain block on DSP.
 *
 */
void setGain( int idx )
{
  if( (paramGain[idx].gain >= -120.0) && (paramGain[idx].gain <= 0.0) )
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
}

//==============================================================================
/*! Handles the POST request for Low Pass parameter
 *
 */
void handlePostXoJson( AsyncWebServerRequest* request, uint8_t* data )
{
  Serial.println( "POST /xo" );
  //Serial.println( "Body:");
  //for(size_t i=0; i<len; i++)
  //  Serial.write(data[i]);
  //Serial.println();

  DynamicJsonDocument jsonDoc(1024);
  DeserializationError err = deserializeJson( jsonDoc, (const char*)data );
  if( err )
  {
    Serial.print( "[ERROR] handlePostXoJson(): Deserialization failed. " );
    Serial.println( err.c_str() );
    request->send( 400, "text/plain", err.c_str() );
    return;
  }

  softMuteDAC();

  JsonObject root = jsonDoc.as<JsonObject>();
  Serial.println( root["idx"].as<String>() );
  Serial.println( root["lp_fc"].as<String>() );
  Serial.println( root["lp_typ"].as<String>() );
  Serial.println( root["hp_fc"].as<String>() );
  Serial.println( root["hp_typ"].as<String>() );

  uint32_t idx = static_cast<uint32_t>(root["idx"].as<String>().toInt());
  paramCrossover[idx].lp_fc = root["lp_fc"].as<String>().toFloat();
  paramCrossover[idx].lp_typ = static_cast<tFilterType>(root["lp_typ"].as<String>().toInt());
  if( root["lp_bypass"].as<String>().toInt() == 0 )
    paramCrossover[idx].lp_bypass = false;
  else
    paramCrossover[idx].lp_bypass = true;

  paramCrossover[idx].hp_fc = root["hp_fc"].as<String>().toFloat();
  paramCrossover[idx].hp_typ = static_cast<tFilterType>(root["hp_typ"].as<String>().toInt());
  if( root["hp_bypass"].as<String>().toInt() == 0 )
    paramCrossover[idx].hp_bypass = false;
  else
    paramCrossover[idx].hp_bypass = true;

  setCrossover( idx );

  request->send(200, "text/plain", "");

  softUnmuteDAC();
}

//==============================================================================
/*! Sets the values for a crossover block on DSP.
 *
 */
void setCrossover( int idx )
{
  if( (paramCrossover[idx].lp_fc > 0) && (paramCrossover[idx].lp_fc < 20000)
      && (paramCrossover[idx].lp_typ >= 0) && (paramCrossover[idx].lp_typ < AudioFilterFactory::kNumFilterDesigns) )
  {
    float a[12] = { 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0 };
    float b[12] = { 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0 };
    byte val[4];
    uint32_t floatval;

    if( !(paramCrossover[idx].lp_bypass) )
      AudioFilterFactory::makeLowPass( a, b, paramCrossover[idx].lp_typ, paramCrossover[idx].lp_fc, sampleRate );

    for( int ii = 0; ii < 4; ii++ )
    {
      uint16_t addr = paramCrossover[idx].lp_addr[ii];
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

  if( (paramCrossover[idx].hp_fc > 0) && (paramCrossover[idx].hp_fc < 20000)
    && (paramCrossover[idx].hp_typ >= 0) && (paramCrossover[idx].hp_typ < AudioFilterFactory::kNumFilterDesigns) )
  {
    float a[12] = { 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0 };
    float b[12] = { 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0 };
    byte val[4];
    uint32_t floatval;
    if( !(paramCrossover[idx].hp_bypass) )
      AudioFilterFactory::makeHighPass( a, b, paramCrossover[idx].hp_typ, paramCrossover[idx].hp_fc, sampleRate );

    for( int ii = 0; ii < 4; ii++ )
    {
      uint16_t addr = paramCrossover[idx].hp_addr[ii];
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

}

//==============================================================================
/*! Handles the POST request for a FIR impulse response
 *
 */
void handlePostFirJson( AsyncWebServerRequest* request, uint8_t* data )
{
  Serial.println( "POST /fir" );
  //Serial.println( "Body:");
  //for(size_t i=0; i<len; i++)
  //  Serial.write(data[i]);
  //Serial.println();

  DynamicJsonDocument jsonDoc(1024);
  DeserializationError err = deserializeJson( jsonDoc, (const char*)data );
  if( err )
  {
    Serial.print( "[ERROR] handlePostFirJson(): Deserialization failed. " );
    Serial.println( err.c_str() );
    request->send( 400, "text/plain", err.c_str() );
    return;
  }

  softMuteDAC();

  JsonObject root = jsonDoc.as<JsonObject>();
  Serial.println( root["idx"].as<String>() );

  uint32_t idx = static_cast<uint32_t>(root["idx"].as<String>().toInt());

  setFir( idx );

  request->send(200, "text/plain", "");

  softUnmuteDAC();
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
    request->send( 400, "text/plain", err.c_str() );
    return;
  }

  JsonObject root = jsonDoc.as<JsonObject>();

  masterVolume.val = root["vol"].as<String>().toFloat();

  setMasterVolume();
  updateUI();

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
    if( (masterVolume.val >= -120.0) && (masterVolume.val <= 0.0) )
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

  if( haveDisplay )
    myDisplay.drawSwitchingPreset();

  DynamicJsonDocument jsonDoc(1024);
  DeserializationError err = deserializeJson( jsonDoc, (const char*)data );
  if( err )
  {
    Serial.print( "[ERROR] handlePostPresetJson(): Deserialization failed. " );
    Serial.println( err.c_str() );
    request->send( 400, "text/plain", err.c_str() );
    return;
  }

  softMuteDAC();

  JsonObject root = jsonDoc.as<JsonObject>();
  Serial.println( root["pre"].as<String>() );

  currentPreset = root["pre"].as<uint8_t>();

  initUserParams();
  uploadUserParams();

  updateAddOn();

  request->send(200, "text/plain", "");

  updateUI();

  softUnmuteDAC();
}

//==============================================================================
/*! Handles the POST request for device configuration
 *
 */
void handlePostConfigJson( AsyncWebServerRequest* request, uint8_t* data )
{
  Serial.println( "POST /config" );

  DynamicJsonDocument jsonDoc(1024);
  DeserializationError err = deserializeJson( jsonDoc, (const char*)data );
  if( err )
  {
    Serial.print( "[ERROR] handlePostConfigJson(): Deserialization failed. " );
    Serial.println( err.c_str() );
    request->send( 400, "text/plain", err.c_str() );
    return;
  }

  JsonObject root = jsonDoc.as<JsonObject>();
  Serial.println( root["aid"].as<String>() );
  Serial.println( root["vpot"].as<String>() );
  Serial.println( root["adcsum"].as<String>().toInt() );
  Serial.println( (uint32_t)strtoul( root["spdifleft"].as<String>().c_str(), NULL, 16 ) );
  Serial.println( (uint32_t)strtoul( root["spdifright"].as<String>().c_str(), NULL, 16 ) );

  Settings.addonid = root["aid"].as<String>().toInt();
  if( root["vpot"].as<String>() == "true" )
    Settings.vpot = true;
  else
    Settings.vpot = false;
  Settings.adcsum = root["adcsum"].as<String>().toInt();

  writeSettings();

  enableVolPot();
  changeChannelSummationADC();

  request->send(200, "text/plain", "");
}

//==============================================================================
/*! Handles the POST request for storing current preset
 *
 */
void handlePostStore( AsyncWebServerRequest* request, uint8_t* data )
{
  Serial.println( "POST /store" );

  softMuteDAC();

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

  for( int ii = 0; ii < numFIRs; ii++ )
  {
    size_t len = fileUserParams.write( (uint8_t*)&(paramFir[ii]), sizeof(tFir) );
    if( len != sizeof(tFir) )
      Serial.println( "[ERROR] Writing FIRs to " + presetUsrparamFile[currentPreset] );
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

  for( int ii = 0; ii < numCrossovers; ii++ )
  {
    size_t len = fileUserParams.write( (uint8_t*)&(paramCrossover[ii]), sizeof(tCrossover) );
    if( len != sizeof(tCrossover) )
      Serial.println( "[ERROR] Writing XOs to " + presetUsrparamFile[currentPreset] );
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

  len = fileUserParams.write( (uint8_t*)&spdifOutput, sizeof(tSpdifOutput) );
  if( len != sizeof(tSpdifOutput) )
    Serial.println( "[ERROR] Writing SPDIF out to " + presetUsrparamFile[currentPreset] );
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

  softUnmuteDAC();
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

  DynamicJsonDocument jsonDoc(1024);
  DeserializationError err = deserializeJson( jsonDoc, (const char*)data );
  if( err )
  {
    Serial.print( "[ERROR] handlePostAddonConfig(): Deserialization failed. " );
    Serial.println( err.c_str() );
    request->send( 400, "text/plain", err.c_str() );
    return;
  }

  softMuteDAC();

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

  softUnmuteDAC();
}

//==============================================================================
/*! Handles the POST request for device configuration
 *
 */
void handlePostWifiConfigJson( AsyncWebServerRequest* request, uint8_t* data )
{
  Serial.println( "POST /wifi" );
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
    request->send( 400, "text/plain", err.c_str() );
    return;
  }

  JsonObject root = jsonDoc.as<JsonObject>();

  Settings.ssid = root["ssid"].as<String>();
  Settings.password = root["pwd"].as<String>();

  writeSettings();

  request->send(200, "text/plain", "");
}

//==============================================================================
/*! Handles the POST request for access point password
 *
 */
void handlePostPasswordApJson( AsyncWebServerRequest* request, uint8_t* data )
{
  Serial.println( "POST /pwdap" );
  //Serial.println( "Body:");
  //for(size_t i=0; i<len; i++)
  //  Serial.write(data[i]);
  //Serial.println();

  DynamicJsonDocument jsonDoc(1024);
  DeserializationError err = deserializeJson( jsonDoc, (const char*)data );
  if( err )
  {
    Serial.print( "[ERROR] handlePostPasswordApJson(): Deserialization failed. " );
    Serial.println( err.c_str() );
    request->send( 400, "text/plain", err.c_str() );
    return;
  }

  JsonObject root = jsonDoc.as<JsonObject>();

  Settings.pwdap = root["pwdap"].as<String>();
  Settings.apname = root["apname"].as<String>();

  writeSettings();

  request->send(200, "text/plain", "");
}

//==============================================================================
/*! Handles the POST request for SPDIF output multiplexer
 *
 */
void handlePostSpdifOutJson( AsyncWebServerRequest* request, uint8_t* data )
{
  Serial.println( "POST /spdifout" );

  DynamicJsonDocument jsonDoc(1024);
  DeserializationError err = deserializeJson( jsonDoc, (const char*)data );
  if( err )
  {
    Serial.print( "[ERROR] handlePostConfigJson(): Deserialization failed. " );
    Serial.println( err.c_str() );
    request->send( 400, "text/plain", err.c_str() );
    return;
  }

  JsonObject root = jsonDoc.as<JsonObject>();

  Serial.println( (uint32_t)strtoul( root["spdifleft"].as<String>().c_str(), NULL, 16 ) );
  Serial.println( (uint32_t)strtoul( root["spdifright"].as<String>().c_str(), NULL, 16 ) );

  spdifOutput.selectionLeft = (uint32_t)strtoul( root["spdifleft"].as<String>().c_str(), NULL, 16 );
  spdifOutput.selectionRight = (uint32_t)strtoul( root["spdifright"].as<String>().c_str(), NULL, 16 );

  setSpdifOutputRouting();

  request->send(200, "text/plain", "");
}

//==============================================================================
/*! Setup the AddOn
 *
 */
void updateAddOn( void )
{
  switch( Settings.addonid )
  {
  case ADDON_A:
    // Nothing to do
    break;
  case ADDON_B:
    setupAddOnB();
    break;
  case ADDON_C:
    // Nothing to do
    break;
  case ADDON_D:
    // Nothing to do
    break;
  case ADDON_CUSTOM:
    // Nothing to do
    break;
  }
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
      Serial.println( "Analog RCA" );
      uint32_t data = 0x00000004;
      byte val[4];
      val[0] = (data >> 24 ) & 0xFF;
      val[1] = (data >> 16 ) & 0xFF;
      val[2] = (data >> 8 ) & 0xFF;
      val[3] = data & 0xFF;
      for( int ii = 0; ii < numInputs; ii++ )
        ADAU1452_WRITE_BLOCK( inputSelector.analog[ii],  val, 4 );

      data = 0x00000000;
      val[0] = (data >> 24 ) & 0xFF;
      val[1] = (data >> 16 ) & 0xFF;
      val[2] = (data >> 8 ) & 0xFF;
      val[3] = data & 0xFF;
      for( int ii = 0; ii < numInputs; ii++ )
        ADAU1452_WRITE_BLOCK( inputSelector.port[ii], val, 4 );

      for( int ii = 0; ii < numInputs; ii++ )
        paramInputs[ii].sel = 0x00000004;
    }
    // Analog XLR
    else if( value == 0xf7 )
    {
      Serial.println( "Analog XLR" );
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

      for( int ii = 0; ii < numInputs; ii++ )
        paramInputs[ii].sel = 0x00000000;
    }
    // Toslink left channel
    else if( (value == 0xfa) || (value == 0xfb) )
    {
      Serial.println( "Toslink left channel" );
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

      for( int ii = 0; ii < numInputs; ii++ )
        paramInputs[ii].sel = 0x00040000;
    }
    // Toslink right channel
    else if( value == 0xf3 )
    {
      Serial.println( "Toslink right channel" );
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

      for( int ii = 0; ii < numInputs; ii++ )
        paramInputs[ii].sel = 0x00040001;
    }
    // Digital RCA left
    else if( (value == 0xfc) || (value == 0xfd) )
    {
      Serial.println( "Digital RCA left" );
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

      for( int ii = 0; ii < numInputs; ii++ )
        paramInputs[ii].sel = 0x00040000;
    }
    // Digital RCA right
    else if( value == 0xf5 )
    {
      Serial.println( "Digital RCA right" );
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

      for( int ii = 0; ii < numInputs; ii++ )
        paramInputs[ii].sel = 0x00040001;
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

  Wire.beginTransmission( currentAddOnCfg[0]>>1 ); //ADDONB_SPDIFMUX_ADDR
  Wire.write( currentAddOnCfg[1] ); // regaddr
  Wire.write( currentAddOnCfg[2] ); // data
  Wire.endTransmission( true );

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

      // Delete old presets and addon configuration if uploading new plugin
      if( fileName == String( "/dsp.fw") )
      {
        for( int ii = 0; ii < MAX_NUM_PRESETS; ii++ )
        {
          if( SPIFFS.exists( presetUsrparamFile[ii] ) )
          {
            if( SPIFFS.remove( presetUsrparamFile[ii] ) )
              Serial.println( presetUsrparamFile[ii] + " deleted." );
            else
              Serial.println( "[ERROR] Deleting " + presetUsrparamFile[ii] );
          }

          if( SPIFFS.exists( presetAddonCfgFile[ii] ) )
          {
            if( SPIFFS.remove( presetAddonCfgFile[ii] ) )
              Serial.println( presetAddonCfgFile[ii] + " deleted." );
            else
              Serial.println( "[ERROR] Deleting " + presetAddonCfgFile[ii] );
          }
        }
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
/*! Handles upload of an ir file
 *
 */
void handleIrUpload( AsyncWebServerRequest* request, uint8_t* data, size_t len, size_t index, size_t total )
{
  if (!index)
  {
    Serial.println("POST /fir");
    if( request->hasParam( "idx" ) )
    {
      AsyncWebParameter* idx = request->getParam(0);
      currentFirUploadIdx = idx->value().toInt();
    }
    if( request->hasParam( "bypass" ) )
    {
      AsyncWebParameter* bypass = request->getParam(1);
      if( bypass->value().toInt() )
        paramFir[currentFirUploadIdx].bypass = true;
      else
        paramFir[currentFirUploadIdx].bypass = false;
    }
  }

  if( len > 0 )
  {
    for( int kk = 0; kk < len; kk++ )
      ((uint8_t*)(paramFir[currentFirUploadIdx].ir))[index + kk] = data[kk];
  }

  if( index + len >= total )
  {
    softMuteDAC();

    setFir( currentFirUploadIdx );

    delay(250);
    softUnmuteDAC();

    Serial.println( "[OK]" );
    Serial.println( index + len );
  }

}

//==============================================================================
/*! Sets the ir for a fir block on DSP.
 *
 */
void setFir( int idx )
{
  byte val[4];
  uint32_t floatval;

  for( uint16_t kk = 0; kk < MAX_LENGTH_IR; kk++ )
  {
    uint16_t addr = paramFir[idx].addr + kk;
    if( paramFir[idx].bypass )
    {
      if( kk == 0 )
        floatval = convertTo824( 1.0 );
      else
        floatval = convertTo824( 0.0 );
    }
    else
      floatval = convertTo824( paramFir[idx].ir[kk] );

    val[0] = (floatval >> 24 ) & 0xFF;
    val[1] = (floatval >> 16 ) & 0xFF;
    val[2] = (floatval >> 8 ) & 0xFF;
    val[3] =  floatval & 0xFF;
    ADAU1452_WRITE_BLOCK( addr, val, 4 );
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
  IPAddress ip(192, 168, 5, 1);
  IPAddress subnet(255, 255, 255, 0);

  WiFi.mode(WIFI_AP_STA);
  WiFi.setHostname( "freeDSP-aurora" );
  // Start access point
  if( Settings.pwdap.length() > 0 )
  {
    Serial.print( "AP password protected " );
    Serial.println( Settings.apname );
    WiFi.softAP( Settings.apname.c_str(), Settings.pwdap.c_str() );
  }
  else
  {
    Serial.print( "AP open: " );
    Serial.println( Settings.apname );
    WiFi.softAP( Settings.apname.c_str() );
  }
  delay(100);

  if( !WiFi.softAPConfig( ip, ip, subnet ) )
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
          delay(1000);
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
          needUpdateUI = true;
        }
        vTaskDelay (5000); // Check again in about 5s
      }
    }
    else
      vTaskDelay (5000);
  }
}

//==============================================================================
/*! Enables or disables the volume potentiometer
 *
 */
void enableVolPot( void )
{
  if( addrVPot )
  {
    uint32_t vpot;
    if( Settings.vpot == true )
      vpot = 0x00000000;
    else
      vpot = 0x00000001;

    byte val[4];
    val[0] = (vpot >> 24 ) & 0xFF;
    val[1] = (vpot >> 16 ) & 0xFF;
    val[2] = (vpot >> 8 ) & 0xFF;
    val[3] =  vpot & 0xFF;
    ADAU1452_WRITE_BLOCK( addrVPot, val, 4 );
  }
}

//==============================================================================
/*! Updates the user interface on the display
 *
 */
void updateUI( void )
{
  if( haveDisplay )
  {
    String ip;
    if( WiFi.status() != WL_CONNECTED )
      ip = "Not Connected";
    else
      ip = WiFi.localIP().toString();

    if( (editMode == 0) || (editMode == 1) )
    {
      switch( currentPreset )
      {
      case 0:
        myDisplay.drawUI( currentPlugInName.c_str(), ip.c_str(), "A", masterVolume.val, editMode );
        break;
      case 1:
        myDisplay.drawUI( currentPlugInName.c_str(), ip.c_str(), "B", masterVolume.val, editMode );
        break;
      case 2:
        myDisplay.drawUI( currentPlugInName.c_str(), ip.c_str(), "C", masterVolume.val, editMode );
        break;
      case 3:
        myDisplay.drawUI( currentPlugInName.c_str(), ip.c_str(), "D", masterVolume.val, editMode );
        break;
      default:
        myDisplay.drawUI( currentPlugInName.c_str(), ip.c_str(), "A", masterVolume.val, editMode );
        break;
      }
    }

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
  //--- Init Rotary Encoder Handling
  //----------------------------------------------------------------------------
  #if HAVE_ROTARYENCODER
  rotaryEncoder.init();
  lastREsw = rotaryEncoder.getSwitchValue();
  lastREval = rotaryEncoder.getRotationValue();
  #endif

  //----------------------------------------------------------------------------
  //--- Is user pressing the rotary encoder switch during boot?
  //----------------------------------------------------------------------------
  //rotaryEncoder.init();
  //pinMode( ROTARYENCODER_PINSW, INPUT_PULLUP );
  if( !digitalRead( ROTARYENCODER_PINSW ) )
    changeWifiState = true;
  
  //----------------------------------------------------------------------------
  //--- Configure I2C
  //----------------------------------------------------------------------------
  Wire.begin( I2C_SDA_PIN, I2C_SCL_PIN );
  Wire.setClock( 100000 );
  delay( 100 );

  //----------------------------------------------------------------------------
  //--- Scan for I2C display connected?
  //----------------------------------------------------------------------------
  Wire.beginTransmission( SH1106_I2C_ADDR );
  uint8_t ec = Wire.endTransmission( true );
  if( ec == 0 )
  {
    Serial.println( "Detected SH1106 display" );
    haveDisplay = true;
  }
  else
    haveDisplay = false;

  //----------------------------------------------------------------------------
  //--- Init Display (if present)
  //----------------------------------------------------------------------------
  if( haveDisplay )
  {
    myDisplay.begin();
    myDisplay.drawBootScreen();
  }

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

  //--- check for old stuff (version == 1.x.x)
  String fileName = "/dspfw.hex";
  if( SPIFFS.exists( fileName ) )
  {
    if( SPIFFS.remove( fileName ) )
      Serial.println( fileName + " deleted." );
    else
      Serial.println( "[ERROR] Deleting " + fileName );
  }
  fileName = "/dspparam.001";
  if( SPIFFS.exists( fileName ) )
  {
    if( SPIFFS.remove( fileName ) )
      Serial.println( fileName + " deleted." );
    else
      Serial.println( "[ERROR] Deleting " + fileName );
  }
  fileName = "/dspparam.002";
  if( SPIFFS.exists( fileName ) )
  {
    if( SPIFFS.remove( fileName ) )
      Serial.println( fileName + " deleted." );
    else
      Serial.println( "[ERROR] Deleting " + fileName );
  }
  fileName = "/dspparam.003";
  if( SPIFFS.exists( fileName ) )
  {
    if( SPIFFS.remove( fileName ) )
      Serial.println( fileName + " deleted." );
    else
      Serial.println( "[ERROR] Deleting " + fileName );
  }
  fileName = "/dspparam.004";
  if( SPIFFS.exists( fileName ) )
  {
    if( SPIFFS.remove( fileName ) )
      Serial.println( fileName + " deleted." );
    else
      Serial.println( "[ERROR] Deleting " + fileName );
  }

  Serial.print( "Free disk space: " );
  Serial.print( (SPIFFS.totalBytes() - SPIFFS.usedBytes()) / 1024 );
  Serial.println( "KiB" );

  File root = SPIFFS.open("/");
  File file = root.openNextFile();
  while(file)
  {
    Serial.print( file.name() );
    Serial.print( " " );
    Serial.print( file.size() );
    Serial.println( " Bytes" );
    file = root.openNextFile();
  }

  //----------------------------------------------------------------------------
  //--- Read settings file
  //----------------------------------------------------------------------------
  readSettings();
  changeChannelSummationADC();
  if( changeWifiState )
  {
    Serial.print( F("Changing WiFi status......") );
    Settings.wifiOn = Settings.wifiOn ? false : true;
    writeSettings();
    Serial.println( F("[OK]") );
  }

  Serial.print( F("Init user parameter......") );
  initUserParams();
  Serial.println( F("[OK]") );
  readPluginMeta();

  //----------------------------------------------------------------------------
  //--- Configure AddOn
  //----------------------------------------------------------------------------
  if( Settings.addonid == ADDON_A )
    setupAddOnA();
  else if( Settings.addonid == ADDON_B )
    setupAddOnB();

  //----------------------------------------------------------------------------
  //--- Upload program to DSP
  //----------------------------------------------------------------------------
  uploadDspFirmware();

  //----------------------------------------------------------------------------
  //--- Upload user parameters to DSP
  //----------------------------------------------------------------------------
  uploadUserParams();

  //----------------------------------------------------------------------------
  //--- Configure Webserver
  //----------------------------------------------------------------------------
  if( SPIFFS.exists( "/dsp.html" ) )
    server.on( "/",          HTTP_GET, [](AsyncWebServerRequest *request ) { request->send( SPIFFS, "/dsp.html", "text/html" ); });
  else
    server.on( "/",          HTTP_GET, [](AsyncWebServerRequest *request ) { request->send( 200, "text/html", fallback_html ); });
  server.on( "/fallback",  HTTP_GET, [](AsyncWebServerRequest *request ) { request->send( 200, "text/html", fallback_html ); });
  server.on( "/dark.css",  HTTP_GET, [](AsyncWebServerRequest *request ) { request->send( SPIFFS, "/dark.css", "text/css" ); });
  server.on( "/aurora.js", HTTP_GET, [](AsyncWebServerRequest *request )
  {
    //request->send( SPIFFS, "/aurora.js", "text/javascript" );
    AsyncWebServerResponse* response = request->beginResponse(SPIFFS, "/aurora.jgz", "text/javascript");
    response->addHeader( "Content-Encoding", "gzip" );
    request->send( response );
  });
  server.on( "/input",     HTTP_GET, [](AsyncWebServerRequest *request ) { handleGetInputJson(request); });
  server.on( "/hp",        HTTP_GET, [](AsyncWebServerRequest *request ) { handleGetHpJson(request); });
  server.on( "/lshelv",    HTTP_GET, [](AsyncWebServerRequest *request ) { handleGetLshelvJson(request); });
  server.on( "/peq",       HTTP_GET, [](AsyncWebServerRequest *request ) { handleGetPeqJson(request); });
  server.on( "/hshelv",    HTTP_GET, [](AsyncWebServerRequest *request ) { handleGetHshelvJson(request); });
  server.on( "/lp",        HTTP_GET, [](AsyncWebServerRequest *request ) { handleGetLpJson(request); });
  server.on( "/phase",     HTTP_GET, [](AsyncWebServerRequest *request ) { handleGetPhaseJson(request); });
  server.on( "/delay",     HTTP_GET, [](AsyncWebServerRequest *request ) { handleGetDelayJson(request); });
  server.on( "/gain",      HTTP_GET, [](AsyncWebServerRequest *request ) { handleGetGainJson(request); });
  server.on( "/xo",        HTTP_GET, [](AsyncWebServerRequest *request ) { handleGetXoJson(request); });
  server.on( "/mvol",      HTTP_GET, [](AsyncWebServerRequest *request ) { handleGetMasterVolumeJson(request); });
  server.on( "/preset",    HTTP_GET, [](AsyncWebServerRequest *request ) { handleGetPresetJson(request); });
  server.on( "/config",    HTTP_GET, [](AsyncWebServerRequest *request ) { handleGetConfigJson(request); });
  server.on( "/allinputs", HTTP_GET, [](AsyncWebServerRequest *request ) { handleGetAllInputsJson(request); });
  server.on( "/addoncfg",  HTTP_GET, [](AsyncWebServerRequest *request ) { handleGetAddonConfigJson(request); });
  server.on( "/fir",       HTTP_GET, [](AsyncWebServerRequest *request ) { handleGetFirJson(request); });
  server.on( "/allbyp",    HTTP_GET, [](AsyncWebServerRequest *request ) { request->send( 200, "text/plain", handleGetAllBypJson() ); });
  server.on( "/allfc",     HTTP_GET, [](AsyncWebServerRequest *request ) { request->send( 200, "text/plain", handleGetAllFcJson() ); });
  server.on( "/preset.param", HTTP_GET, [](AsyncWebServerRequest *request )
  {
    Serial.println( "/preset.param" );
    request->send( SPIFFS, presetUsrparamFile[currentPreset], "application/octet-stream" );
  });
  server.on( "/spdifout",   HTTP_GET, [](AsyncWebServerRequest *request ) { handleGetSpdifOutJson(request); });
  server.on( "/wificonfig", HTTP_GET, [](AsyncWebServerRequest *request ) { handleGetWifiConfigJson(request); });

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
  server.on( "/xo", HTTP_POST, [](AsyncWebServerRequest *request){}, NULL, [](AsyncWebServerRequest* request, uint8_t* data, size_t len, size_t index, size_t total )
  {
    handlePostXoJson( request, data );
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
  server.on( "/pwdap", HTTP_POST, [](AsyncWebServerRequest *request){}, NULL, [](AsyncWebServerRequest* request, uint8_t* data, size_t len, size_t index, size_t total )
  {
    handlePostPasswordApJson( request, data );
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
  server.on( "/fir", HTTP_POST, [](AsyncWebServerRequest *request){
    request->send(200, "text/plain", "OK");
  }, NULL, [](AsyncWebServerRequest* request, uint8_t* data, size_t len, size_t index, size_t total )
  {
    handleIrUpload( request, data, len, index, total );
  });
  server.on( "/spdifout", HTTP_POST, [](AsyncWebServerRequest *request){}, NULL, [](AsyncWebServerRequest* request, uint8_t* data, size_t len, size_t index, size_t total )
  {
    handlePostSpdifOutJson( request, data );
  });

  //--- webOTA stuff ---
  server.on( "/webota", HTTP_GET, [](AsyncWebServerRequest *request ) { request->send( 200, "text/html", webota_html ); });
  server.on( "/update", HTTP_POST, [](AsyncWebServerRequest *request){
    request->send(200, "text/plain", "OK");
    //AsyncWebServerResponse *response = request->beginResponse(200, "text/plain", "OK");
    //response->addHeader("Connection", "close");
    //request->send(response);
  }, NULL, [](AsyncWebServerRequest* request, uint8_t* data, size_t len, size_t index, size_t total )
  {
    if (!index)
    {
      Serial.println("POST /update");
      Serial.setDebugOutput( true );
      if( !Update.begin() )
        Update.printError(Serial);
    }

    if( len > 0 )
    {
      if( Update.write( data, len ) != len )
        Update.printError(Serial);
    }

    Serial.print( "." );

    if( index + len >= total )
    {
      if( Update.end(true) )
        Serial.printf( "Update Success: %u\nPlease reboot\n", total );
      else
        Update.printError( Serial );

      Serial.setDebugOutput( false );
    }

  });

//  server.onNotFound([](AsyncWebServerRequest *request){
//    Serial.println(request->url().c_str());
//  });

  //----------------------------------------------------------------------------
  //--- Configure ESP for WiFi access
  //----------------------------------------------------------------------------
  // Create a connection task with 8kB stack on core 0
  if( Settings.wifiOn )
    xTaskCreatePinnedToCore(myWiFiTask, "myWiFiTask", 8192, NULL, 3, NULL, 0);

  //----------------------------------------------------------------------------
  //--- Enable Volume Potentiometer
  //----------------------------------------------------------------------------
  enableVolPot();

  //----------------------------------------------------------------------------
  //--- Init IR Receiver
  //----------------------------------------------------------------------------
  #if HAVE_IRRECEIVER
  irReceiver.enableIRIn();
  #endif

  resetDAC( false );

  updateUI();

  lastREsw = rotaryEncoder.getSwitchValue();
  lastREval = rotaryEncoder.getRotationValue();

  Serial.println( "Ready" );
}

//==============================================================================
/*! Arduino Main Loop
 *
 */
void loop()
{
  TIMERG0.wdt_wprotect=TIMG_WDT_WKEY_VALUE;
  TIMERG0.wdt_feed=1;
  TIMERG0.wdt_wprotect=0;


  #if HAVE_ROTARYENCODER
  if( rotaryEncoder.getSwitchValue() != lastREsw )
  {
    if( changeWifiState )
      changeWifiState = false;
    else
    {
      editMode++;
      // we may have more then two modes in the future.
      if( editMode > 1 )
        editMode = 0;
      delay( 300 );
      needUpdateUI = true;
    }
    lastREsw = rotaryEncoder.getSwitchValue();
    lastREval = rotaryEncoder.getRotationValue();
  }
  else if( rotaryEncoder.getRotationValue() > lastREval + 1 )
  {
    if( editMode == 0 )
    {
      masterVolume.val += 0.5f;
      if( masterVolume.val > 0.f )
        masterVolume.val = 0.f;
      setMasterVolume();
      lastREval = rotaryEncoder.getRotationValue();
      needUpdateUI = true;
    }
    else if( editMode == 1 )
    {
      myDisplay.drawSwitchingPreset();

      currentPreset++;
      if( currentPreset >= MAX_NUM_PRESETS )
        currentPreset = 0;

      softMuteDAC();
      initUserParams();
      uploadUserParams();
      updateAddOn();
      softUnmuteDAC();

      lastREval = rotaryEncoder.getRotationValue();
      needUpdateUI = true;
    }
  }
  else if( rotaryEncoder.getRotationValue() < lastREval - 1 )
  {
    if( editMode == 0 )
    {
      masterVolume.val -= 0.5f;
      if( masterVolume.val <= -80.f )
        masterVolume.val = -80.f;
      setMasterVolume();
      lastREval = rotaryEncoder.getRotationValue();
      needUpdateUI = true;
    }
    else if( editMode == 1 )
    {
      myDisplay.drawSwitchingPreset();

      if( currentPreset == 0 )
        currentPreset = MAX_NUM_PRESETS - 1;
      else
        currentPreset--;

      softMuteDAC();
      initUserParams();
      uploadUserParams();
      updateAddOn();
      softUnmuteDAC();

      lastREval = rotaryEncoder.getRotationValue();
      needUpdateUI = true;
    }
  }
  #endif

  #if HAVE_IRRECEIVER
  decode_results irResults;
  if( irReceiver.decode( &irResults ) )
  {
    if( irResults.value == APPLE_REMOTE_UP )
    {
      masterVolume.val += 0.5f;
      if( masterVolume.val > 0.f )
        masterVolume.val = 0.f;
      setMasterVolume();
      needUpdateUI = true;
    }
    else if( irResults.value == APPLE_REMOTE_DOWN )
    {
      masterVolume.val -= 0.5f;
      if( masterVolume.val <= -80.f )
        masterVolume.val = -80.f;
      setMasterVolume();
      needUpdateUI = true;
    }
    else if( irResults.value == APPLE_REMOTE_LEFT )
    {
      myDisplay.drawSwitchingPreset();

      if( currentPreset == 0 )
        currentPreset = MAX_NUM_PRESETS - 1;
      else
        currentPreset--;

      softMuteDAC();
      initUserParams();
      uploadUserParams();
      updateAddOn();
      softUnmuteDAC();

      needUpdateUI = true;
    }
    else if( irResults.value == APPLE_REMOTE_RIGHT )
    {
      myDisplay.drawSwitchingPreset();

      currentPreset++;
      if( currentPreset >= MAX_NUM_PRESETS )
        currentPreset = 0;

      softMuteDAC();
      initUserParams();
      uploadUserParams();
      updateAddOn();
      softUnmuteDAC();

      needUpdateUI = true;
    }
    //else
    //  Serial.println(irResults.value, HEX);
    irReceiver.resume();
  }
  #endif

  if( needUpdateUI )
  {
    updateUI();
    needUpdateUI = false;
  }

}
