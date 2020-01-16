#include <Wire.h>
#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <SPIFFS.h>
#include "AsyncJson.h"
#include <ArduinoJson.h>

#define VERSION_STR 0.0.1


// Replace with your network credentials
const char* ssid = "REPLACE_WITH_YOUR_SSID";
const char* password = "REPLACE_WITH_YOUR_PASSWORD";

typedef uint8_t tFilterType;
typedef uint8_t tInputSelection;

struct tInput
{
  tInputSelection sel;
};

struct tHPLP
{
  float fc;
  tFilterType typ;
};

struct tShelving
{
  float gain;
  float fc;
  float slope;
};

struct tPeq
{
  float gain;
  float fc;
  float Q;
};

struct tPhase
{
  float fc;
  float Q;
  bool inv;
};

struct tDelay
{
  float delay;
};

struct tGain
{
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

  uint32_t idx = root["idx"].as<uint32_t>();
  paramInputs[idx].sel = root["sel"].as<tInputSelection>();
       
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
  Serial.println( root["fc"].as<String>() );
  Serial.println( root["typ"].as<String>() );

  uint32_t idx = root["idx"].as<uint32_t>();
  paramHP[idx].fc = root["fc"].as<float>();
  paramHP[idx].typ = root["typ"].as<tFilterType>();
       
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
  Serial.println( root["gain"].as<String>() );
  Serial.println( root["fc"].as<String>() );
  Serial.println( root["slope"].as<String>() );

  uint32_t idx = root["idx"].as<uint32_t>();
  paramLshelv[idx].gain = root["gain"].as<float>();
  paramLshelv[idx].fc = root["fc"].as<float>();
  paramLshelv[idx].slope = root["slop"].as<float>();
       
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
  Serial.println( root["gain"].as<String>() );
  Serial.println( root["fc"].as<String>() );
  Serial.println( root["Q"].as<String>() );

  uint32_t idx = root["idx"].as<uint32_t>();
  paramPeq[idx].gain = root["gain"].as<float>();
  paramPeq[idx].fc = root["fc"].as<float>();
  paramPeq[idx].Q = root["Q"].as<float>();
       
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
  Serial.println( root["gain"].as<String>() );
  Serial.println( root["fc"].as<String>() );
  Serial.println( root["slope"].as<String>() );

  uint32_t idx = root["idx"].as<uint32_t>();
  paramHshelv[idx].gain = root["gain"].as<float>();
  paramHshelv[idx].fc = root["fc"].as<float>();
  paramHshelv[idx].slope = root["slop"].as<float>();
       
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
  Serial.println( root["fc"].as<String>() );
  Serial.println( root["typ"].as<String>() );

  uint32_t idx = root["idx"].as<uint32_t>();
  paramLP[idx].fc = root["fc"].as<float>();
  paramLP[idx].typ = root["typ"].as<tFilterType>();
       
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
  Serial.println( root["fc"].as<String>() );
  Serial.println( root["Q"].as<String>() );

  uint32_t idx = root["idx"].as<uint32_t>();
  paramPhase[idx].fc = root["fc"].as<float>();
  paramPhase[idx].Q = root["Q"].as<tFilterType>();
  paramPhase[idx].inv = root["inv"].as<bool>();

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

  uint32_t idx = root["idx"].as<uint32_t>();
  paramDelay[idx].delay = root["delay"].as<float>();
       
  request->send(200, "text/plain", "");  
}

//==============================================================================
/*! Handles the POST request for Gain parameter
 *
 */
void handlePostGainJson( AsyncWebServerRequest* request, uint8_t* data )
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
    Serial.print( "[ERROR] handlePostGainJson(): Deserialization failed. " );
    Serial.println( err.c_str() );
    request->send( 404, "text/plain", "" );
    return;
  }

  JsonObject root = jsonDoc.as<JsonObject>();
  Serial.println( root["idx"].as<String>() );
  Serial.println( root["gain"].as<String>() );

  uint32_t idx = root["idx"].as<uint32_t>();
  paramGain[idx].gain = root["gain"].as<float>();
       
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
  masterVolume = root["vol"].as<String>().toFloat();
  Serial.println( masterVolume );
       
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
  Serial.println(" AURORA Debug Log" ); 

  if( !SPIFFS.begin( true ) )
  {
    Serial.println("An Error has occurred while mounting SPIFFS");
    return;
  }

  readParams();


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


  server.on( "/",       HTTP_GET, [](AsyncWebServerRequest *request ) { request->send( SPIFFS, "/dsp.html", "text/html" ); });
  server.on( "/input",  HTTP_GET, [](AsyncWebServerRequest *request ) { handleGetInputJson(request); });
  server.on( "/hp",     HTTP_GET, [](AsyncWebServerRequest *request ) { handleGetHpJson(request); });
  server.on( "/lshelv", HTTP_GET, [](AsyncWebServerRequest *request ) { handleGetLshelvJson(request); });
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
}

//==============================================================================
/*! Arduino Main Loop
 *
 */ 
void loop()
{
  
}
