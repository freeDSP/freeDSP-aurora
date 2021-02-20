#include <Arduino.h>
#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <AsyncJson.h>
#include <SPIFFS.h>
#include <Update.h>
#include <ArduinoJson.h>

#include "plugin.h"
#include "web.h"
#include "webota.h"
#include "fallback.h"
#include "adau1452.h"
#include "AK4458.h"
#include "AK5558.h"
#include "settings.h"
#include "addons.h"
#include "display.h"

AsyncWebServer server( 80 );
uint8_t currentFirUploadIdx = 0;
File fileUpload;

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

  if(!numHPs && !numLShelvs && !numPEQs && !numHShelvs && !numLPs && !numPhases && !numDelays && !numGains)
    return String("{\"fc\":[]}");

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

  jsonResponse["num"] = numInputs;
  Serial.println(numInputs);

  for( int nn = 0; nn < numInputs; nn++ )
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
/*! Handles the POST request for a FIR impulse response
 *
 */
void handlePostFirBypassJson( AsyncWebServerRequest* request, uint8_t* data )
{
  Serial.println( "POST /firbypass" );

  DynamicJsonDocument jsonDoc(1024);
  DeserializationError err = deserializeJson( jsonDoc, (const char*)data );
  if( err )
  {
    Serial.print( "[ERROR] handlePostFirBypassJson(): Deserialization failed. " );
    Serial.println( err.c_str() );
    request->send( 400, "text/plain", err.c_str() );
    return;
  }

  softMuteDAC();

  JsonObject root = jsonDoc.as<JsonObject>();
  Serial.println( root["idx"].as<String>() );

  uint32_t idx = static_cast<uint32_t>(root["idx"].as<String>().toInt());
  if( root["bypass"].as<String>().toInt() == 0 )
    paramFir[idx].bypass = false;
  else
    paramFir[idx].bypass = true;

  if(paramFir[idx].bypass)
    Serial.println("Bypass");

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
    //size_t len = fileUserParams.write( (uint8_t*)&(paramFir[ii]), sizeof(tFir) );
    //if( len != sizeof(tFir) )
    //  Serial.println( "[ERROR] Writing FIRs to " + presetUsrparamFile[currentPreset] );
    //totalSize += len;

    size_t len = fileUserParams.write((uint8_t*)&(paramFir[ii].addr), sizeof(uint16_t));
    len += fileUserParams.write((uint8_t*)&(paramFir[ii].numCoeffs), sizeof(uint16_t));
    len += fileUserParams.write((uint8_t*)&(paramFir[ii].bypass), sizeof(bool));
    if(len != (2 * sizeof(uint16_t) + sizeof(bool)))
      Serial.println( "[ERROR] Writing FIRs to " + presetUsrparamFile[currentPreset] );
    else
    {
      len = fileUserParams.write((uint8_t*)(paramFir[ii].ir), sizeof(float) * paramFir[ii].numCoeffs);
      if(len != sizeof(float) * paramFir[ii].numCoeffs)
        Serial.println( "[ERROR] Reading FIR IR from " + presetUsrparamFile[currentPreset] );
    }
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
  if(!index)
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
    {
      if(index + kk < sizeof(float) * paramFir[currentFirUploadIdx].numCoeffs)
        ((uint8_t*)(paramFir[currentFirUploadIdx].ir))[index + kk] = data[kk];
    }
  }

  if( index + len >= total )
  {
    softMuteDAC();

    setFir( currentFirUploadIdx );

    delay(250);
    softUnmuteDAC();

    Serial.println( "[OK]" );
  }

}

void setupWebserver (void)
{
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
  server.on( "/firbypass", HTTP_POST, [](AsyncWebServerRequest *request){}, NULL, [](AsyncWebServerRequest* request, uint8_t* data, size_t len, size_t index, size_t total )
  {
    handlePostFirBypassJson( request, data );
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
}
