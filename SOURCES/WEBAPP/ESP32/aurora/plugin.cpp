#include <Arduino.h>
#include <ArduinoJson.h>
#include <SPIFFS.h>

#include "plugin.h"

tSettings Settings;

tInput paramInputs[MAX_NUM_INPUTS];
tHPLP paramHP[MAX_NUM_HPS];
tShelving paramLshelv[MAX_NUM_LSHELVS];
tPeq paramPeq[MAX_NUM_PEQS];
tPeqBank paramPeqBank[MAX_NUM_PEQBANKS];
tShelving paramHshelv[MAX_NUM_HSHELVS];
tHPLP paramLP[MAX_NUM_LPS];
tPhase paramPhase[MAX_NUM_PHASES];
tDelay paramDelay[MAX_NUM_DELAYS];
tGain paramGain[MAX_NUM_GAINS];
tCrossover paramCrossover[MAX_NUM_CROSSOVER];
tFir paramFir[MAX_NUM_FIRS];
tMasterVolume masterVolume = { 0x0000, -60.0 };
tInputSelector inputSelector;
tSpdifOutput spdifOutput;
tSpdifOutputSelector spdifOutputSelector;

int numInputs = 0;
int numOutputs = 0;
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
int numPeqBanks = 0;

float sampleRate = 48000.0;

uint16_t addrVPot = 0x0000;

String currentPlugInName;
String pluginVersion = "0.0.0";

String presetUsrparamFile[MAX_NUM_PRESETS] = { "/usrparam.001", "/usrparam.002", "/usrparam.003", "/usrparam.004" };
String presetAddonCfgFile[MAX_NUM_PRESETS] = { "/addoncfg.001", "/addoncfg.002", "/addoncfg.003", "/addoncfg.004" };

uint8_t currentPreset = 0;

byte currentAddOnCfg[3];

//float memIR[SIZE_IR_MEMORY];

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
    pluginVersion = jsonPluginMeta["version"].as<String>();
    numInputs = jsonPluginMeta["ninputs"].as<String>().toInt();
    numOutputs = jsonPluginMeta["noutputs"].as<String>().toInt();
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
    numPeqBanks = jsonPluginMeta["npeqbank"].as<String>().toInt();

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

    int peqoffset = 0;
    for( int ii = 0; ii < numPeqBanks; ii++ )
    {
      paramPeqBank[ii].numBands = static_cast<uint16_t>(jsonPluginMeta["peqbands"][ii]);
      for(int nn = 0; nn < paramPeqBank[ii].numBands; nn++)
      {
        paramPeqBank[ii].addr[nn] = static_cast<uint16_t>(jsonPluginMeta["peqbank"][peqoffset]);
        peqoffset++;
      }
    }
     
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

    int idx = 0;
    for(int ii = 0; ii < numFIRs; ii++)
    {
      paramFir[ii].addr = static_cast<uint16_t>(jsonPluginMeta["fir"][ii]);
      paramFir[ii].numCoeffs = static_cast<uint16_t>(jsonPluginMeta["firlen"][ii]);
      paramFir[ii].ir = (float*)malloc(paramFir[ii].numCoeffs * sizeof(float));
      if(paramFir[ii].ir == NULL)
        Serial.println("[ERROR] Not enough IR memory on heap.");
      else
      {
        for( int kk = 0; kk < paramFir[ii].numCoeffs; kk++ )
          paramFir[ii].ir[kk] = 0.0;
        paramFir[ii].ir[0] = 1.0;
      }
      /*paramFir[ii].ir = &(memIR[idx]);
      idx += paramFir[ii].numCoeffs;
      if(idx > SIZE_IR_MEMORY)
        Serial.println("[ERROR] Not enough IR memory.");*/
    }

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
    paramFir[ii].bypass = true;
    //for( int kk = 0; kk < MAX_LENGTH_IR; kk++ )
    //  paramFir[ii].ir[kk] = 0.0;
    //paramFir[ii].ir[0] = 1.0;
  }
  //for(int nn = 0; nn < SIZE_IR_MEMORY; nn++)
  //  memIR[nn] = 0.0f;


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

  for( int ii = 0; ii < MAX_NUM_PEQBANKS; ii++ )
  {
    for( int nn = 0; nn < MAX_BANDS_PER_PEQBANK; nn++ )
    {
      paramPeqBank[ii].gain[nn] = 0.0;
      paramPeqBank[ii].fc[nn] = static_cast<float>( (nn+1)*1000 );
      paramPeqBank[ii].Q[nn] = 0.707;
      paramPeqBank[ii].bypass[nn] = false;
    }
    paramPeqBank[ii].numBands = MAX_BANDS_PER_PEQBANK;
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
