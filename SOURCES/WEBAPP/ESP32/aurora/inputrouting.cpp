#include <Arduino.h>
#include <ESPAsyncWebServer.h>
#include <AsyncJson.h>
#include <ArduinoJson.h>
#include <SPIFFS.h>

#include "customdefines.h"
#include "config.h"
#include "hwconfig.h"
#include "plugin.h"
#include "adau1452.h"
#include "AK4458.h"
#include "display.h"

#include "inputrouting.h"

StaticJsonDocument<2048> jsonDoc;

String sourceNames[kNumSourceNames] = {"CD-A", "Blueray", "Phono", "Aux", "USB", "Streaming", "SPDIF coax", "SPDIF optical"};

//! TODO Make this dynamic depending on plugin
static const int kNumVirtualInputs = 2;

int sourceRouting[kNumSourceNames][kNumVirtualInputs] = {{0, 1}, {2, 3}, {4, 5}, {6, 7}, {8, 9}, {16, 17}, {18, 19}, {26, 27}};

uint32_t inputSelectionCmd[34] = {
  0x00000000, // Analog 1
  0x00000001, // Analog 2
  0x00000002, // Analog 3
  0x00000003, // Analog 4
  0x00000004, // Analog 5
  0x00000005, // Analog 6
  0x00000006, // Analog 7
  0x00000007, // Analog 8
  0x00010000, // USB 1
  0x00010001, // USB 2
  0x00010002, // USB 3
  0x00010003, // USB 4
  0x00010004, // USB 5
  0x00010005, // USB 6
  0x00010006, // USB 7
  0x00010007, // USB 8
  0x00020000, // Expansion 1
  0x00020001, // Expansion 2
  /*0x00020002, // Expansion 3
  0x00020003, // Expansion 4
  0x00020004, // Expansion 5
  0x00020005, // Expansion 6
  0x00020006, // Expansion 7
  0x00020007, // Expansion 8*/
  0x00040000, // SPDIF Coax 1 Left
  0x00040001, // SPDIF Coax 1 Right
  0x00040000, // SPDIF Coax 2 Left
  0x00040001, // SPDIF Coax 2 Right
  0x00040000, // SPDIF Coax 3 Left
  0x00040001, // SPDIF Coax 3 Right
  0x00040000, // SPDIF Coax 4 Left
  0x00040001, // SPDIF Coax 4 Right
  0x00040000, // SPDIF Optical 1 Left
  0x00040001, // SPDIF Optical 1 Right
  0x00040000, // SPDIF Optical 2 Left
  0x00040001, // SPDIF Optical 2 Right
  0x00040000, // SPDIF Optical 3 Left
  0x00040001, // SPDIF Optical 3 Right
  0x00040000, // SPDIF Optical 4 Left
  0x00040001  // SPDIF Optical 4 Right
};

int currentVirtualInput = 0;

//==============================================================================
/*! Builds the HTML page for the input routing by source names.
 *
 */
String createInputRoutingPage(int numinputs)
{
  String ret;
  int id = 0;
  
  ret += R""""(
    <!DOCTYPE html>
    <html lang="en">
    <meta name="viewport" content="width=device-width, initial-scale=1" charset="utf-8">
    <head>
    <title>)"""";
  ret += String(DSPNAME);
  ret += R""""(</title>
    <link rel="stylesheet" href="dark.css">
    <script type="text/javascript" src="aurora.js"></script>
    </head>
    <body onload="onLoadInputRouting()">
      <center>
      <div>
        <table>
        <tr><td><center><table style="border-bottom:1px solid;"><tr><td><h1>Aurora DSP</h1></td></tr></table></center></td></tr>
        <tr><td><h2>Routing</h2></td></tr>
        <tr><td>
        <table id="inputrouting">
          <tr><td></td><td>Left</td><td>Right</td></tr>
        </table>
        </td></tr>
        </table>
      </div>
      </center>

      <center>
      <table><tr>
        <td><button class="prebtn" style="height:40px;" id="cancel" onclick="window.location.href='/'">Cancel</button></td>
        <td><button class="prebtn" style="height:40px;" id="store" onclick="onStoreInputRouting()">Store</button></td>
      </tr></table>
      </center>
    </body>
    </html>
  )"""";

  return ret;
}

//==============================================================================
/*! Handles the GET request for input routing
 *
 */
String handleGetInputRoutingJson(void)
{
  #if DEBUG_PRINT
  Serial.println( "GET /inputrouting" );
  #endif

  // Build the JSON response manually. Via ArduinoJson it did not work somehow.
  String ret("{");

  ret += String("\"numSourceNames\":") + kNumSourceNames + String(",");
  ret += String("\"numInputs\":") + kNumVirtualInputs + String(",");

  ret += String("\"sourceNames\":[");
  for(int mm = 0; mm < kNumSourceNames; mm++)
  {
    ret += String("\"") + sourceNames[mm] + String("\"");
    if(mm < kNumSourceNames - 1)
      ret += String(",");
  }
  ret += String("],");

  ret += String("\"select\":[");
  for(int mm = 0; mm < kNumSourceNames; mm++)
  {
    ret += String("[");
    for(int nn = 0; nn < kNumVirtualInputs; nn++)
    {
      ret += sourceRouting[mm][nn];
      if(nn < kNumVirtualInputs - 1)
        ret += String(",");
    }
    if(mm < kNumSourceNames - 1)
      ret += String("],");
    else
      ret += String("]");
  }
  ret += String("],");

  ret += String("\"options\":[\"Analog 1\", \"Analog 2\", \"Analog 3\", \"Analog 4\", \"Analog 5\", \"Analog 6\", \"Analog 7\", \"Analog 8\",");
  ret += String("\"USB 1\", \"USB 2\", \"USB 3\", \"USB 4\", \"USB 5\", \"USB 6\", \"USB 7\", \"USB 8\",");
  ret += String("\"Expansion 1\", \"Expansion 2\",");
  ret += String("\"SPDIF Coax 1 Left\", \"SPDIF Coax 1 Right\", \"SPDIF Coax 2 Left\", \"SPDIF Coax 2 Right\", \"SPDIF Coax 3 Left\", \"SPDIF Coax 3 Right\", \"SPDIF Coax 4 Left\", \"SPDIF Coax 4 Right\",");
  ret += String("\"SPDIF Optical 1 Left\", \"SPDIF Optical 1 Right\", \"SPDIF Optical 2 Left\", \"SPDIF Optical 2 Right\", \"SPDIF Optical 3 Left\", \"SPDIF Optical 3 Right\", \"SPDIF Optical 4 Left\", \"SPDIF Optical 4 Right\"");
  ret += String("]");
  ret += String("}");

  return ret;
}

//==============================================================================
/*! Handles the POST request for input routing
 *
 */
void handlePostInputRoutingJson(AsyncWebServerRequest* request, uint8_t* data)
{
  #if DEBUG_PRINT
  Serial.println( "POST /inputrouting" );
  #endif

  softMuteDAC();

  //DynamicJsonDocument jsonDoc(1024);
  DeserializationError err = deserializeJson(jsonDoc, (const char*)data);
  if(err)
  {
    #if DEBUG_PRINT || ERROR_PRINT 
    Serial.print(F("[ERROR] handlePostInputRoutingJson(): Deserialization failed."));
    Serial.println(err.c_str());
    #endif
    request->send(400, "text/plain", err.c_str());
    return;
  }

  JsonObject root = jsonDoc.as<JsonObject>();

  for(int mm = 0; mm < kNumSourceNames; mm++)
  {
    sourceNames[mm] = root["sourceNames"][mm].as<String>().substring(0, 16);
    for(int nn = 0; nn < kNumVirtualInputs; nn++)
    {
      if((mm < root["select"].size()) && (nn < root["select"][mm].size()))
        sourceRouting[mm][nn] = root["select"][mm][nn];
    }
  }

  writeVirtualInputRouting();
  setVirtualInput();

  request->send(200, "text/plain", "");
  needUpdateUI = true;
  softUnmuteDAC();
}

//==============================================================================
/*! Handles the GET request for virtual input selection
 *
 */
void handleGetVirtualInputJson(AsyncWebServerRequest* request)
{
  #if DEBUG_PRINT
  Serial.println( "GET /vinput" );
  #endif

  AsyncJsonResponse* response = new AsyncJsonResponse();

  JsonVariant& jsonResponse = response->getRoot();
  jsonResponse["sel"] = currentVirtualInput;

  response->setLength();
  request->send(response);
}

//==============================================================================
/*! Handles the POST request for virtual input selection
 *
 */
void handlePostVirtualInputJson(AsyncWebServerRequest* request, uint8_t* data)
{
  #if DEBUG_PRINT
  Serial.println( "POST /vinput" );
  #endif

  //DynamicJsonDocument jsonDoc(1024);
  DeserializationError err = deserializeJson( jsonDoc, (const char*)data );
  if( err )
  {
    #if DEBUG_PRINT || ERROR_PRINT 
    Serial.print( "[ERROR] handlePostHpJson(): Deserialization failed. " );
    Serial.println( err.c_str() );
    #endif
    request->send( 400, "text/plain", err.c_str() );
    return;
  }

  softMuteDAC();
  JsonObject root = jsonDoc.as<JsonObject>();
  currentVirtualInput = (uint32_t)strtoul(root["sel"].as<String>().c_str(), NULL, 10);
  setVirtualInput(); 
  request->send(200, "text/plain", "");
  needUpdateUI = true;
  softUnmuteDAC();
}

//==============================================================================
/*! Saves the current assignment virtual <-> physical input to file
 *
 */
bool writeVirtualInputRouting(void)
{
  #if DEBUG_PRINT
  Serial.print(F("Writing virtual input routing..."));
  #endif

  File file = SPIFFS.open("/vinputs.txt", FILE_WRITE);
 
  if(!file)
  {
    #if DEBUG_PRINT || ERROR_PRINT 
    Serial.println(F("[ERROR] writeVirtualInputRouting(): Open vinputs.txt failed."));
    #endif
    return false;
  }

  for(int ii = 0; ii < kNumSourceNames; ii++)
    file.print(sourceNames[ii] + String("\n"));

  for(int mm = 0; mm < kNumSourceNames; mm++)
  {
    for(int nn = 0; nn < kNumVirtualInputs; nn++)
      file.print(String(sourceRouting[mm][nn]) + String("\n"));
  }

  file.close();
  #if DEBUG_PRINT
  Serial.println(F("[OK]"));
  #endif
  return true;
}

//==============================================================================
/*! Reads the saved assignment virtual <-> physical input from file
 *
 */
bool readVirtualInputRouting(void)
{
  #if DEBUG_PRINT
  Serial.print(F("Reading virtual input routing..."));
  #endif

  File file = SPIFFS.open("/vinputs.txt", FILE_READ);
 
  if(!file)
  {
    #if DEBUG_PRINT || ERROR_PRINT 
    Serial.println(F("[ERROR] readVirtualInputRouting(): Open vinput.txt failed."));
    #endif
    return false;
  }

  int ii = 0;
  if(file.available())
  {
    for(int ii = 0; ii < kNumSourceNames; ii++)
    {
      String str = file.readStringUntil('\n');
      sourceNames[ii] = str;
    }
    for(int mm = 0; mm < kNumSourceNames; mm++)
    {
      for(int nn = 0; nn < kNumVirtualInputs; nn++)
      {
        String str = file.readStringUntil('\n');
        sourceRouting[mm][nn] = (uint32_t)strtoul(str.c_str(), NULL, 10);
      }
    }
  }

  file.close();
  #if DEBUG_PRINT
  Serial.println(F("[OK]"));
  #endif
  return true;
}

//==============================================================================
/*! Sets the virtual input routing for current selection
 *
 */
void setVirtualInput(void)
{
  softMuteDAC();

  int idx = 0;
  for(int ii = 0; ii < numInputs; ii = ii + kNumVirtualInputs)
  {
    for(int nn = 0; nn < kNumVirtualInputs; nn++)
    {
      paramInputs[idx].sel = inputSelectionCmd[sourceRouting[currentVirtualInput][nn]];
      setInput(idx);
      if((paramInputs[idx].sel & 0xffff0000) == 0x00040000)
      {
        Wire.beginTransmission(ADDONB_SPDIFMUX_ADDR);
        Wire.write(0x01);
        if(sourceRouting[currentVirtualInput][nn] == 18) // SPDIF Coax 1 Left
          Wire.write(0x04);
        else if(sourceRouting[currentVirtualInput][nn] == 19) // SPDIF Coax 1 Right
          Wire.write(0x04);
        else if(sourceRouting[currentVirtualInput][nn] == 20) // SPDIF Coax 2 Left
          Wire.write(0x05);
        else if(sourceRouting[currentVirtualInput][nn] == 21) // SPDIF Coax 2 Right
          Wire.write(0x05);
        else if(sourceRouting[currentVirtualInput][nn] == 22) // SPDIF Coax 3 Left
          Wire.write(0x06);
        else if(sourceRouting[currentVirtualInput][nn] == 23) // SPDIF Coax 3 Right
          Wire.write(0x06);
        else if(sourceRouting[currentVirtualInput][nn] == 24) // SPDIF Coax 4 Left
          Wire.write(0x07);
        else if(sourceRouting[currentVirtualInput][nn] == 25) // SPDIF Coax 4 Right
          Wire.write(0x07);
        else if(sourceRouting[currentVirtualInput][nn] == 26) // SPDIF Optical 1 Left
          Wire.write(0x00);
        else if(sourceRouting[currentVirtualInput][nn] == 27) // SPDIF Optical 1 Right
          Wire.write(0x00);
        else if(sourceRouting[currentVirtualInput][nn] == 28) // SPDIF Optical 2 Left
          Wire.write(0x01);
        else if(sourceRouting[currentVirtualInput][nn] == 29) // SPDIF Optical 2 Right
          Wire.write(0x01);
        else if(sourceRouting[currentVirtualInput][nn] == 30) // SPDIF Optical 3 Left
          Wire.write(0x02);
        else if(sourceRouting[currentVirtualInput][nn] == 31) // SPDIF Optical 3 Right
          Wire.write(0x02);
        else if(sourceRouting[currentVirtualInput][nn] == 32) // SPDIF Optical 4 Left
          Wire.write(0x03);
        else if(sourceRouting[currentVirtualInput][nn] == 33) // SPDIF Optical 4 Right
          Wire.write(0x03);
        Wire.endTransmission(true);
      }
      idx++;
    }
  } 

  delay(250);
  softUnmuteDAC();
}

//==============================================================================
/*! Returns the name of the currently selected virtual input
 *
 */
String getCurrentVirtualInputName(void)
{
  return sourceNames[currentVirtualInput];
}

//==============================================================================
/*! Selects the next virtual input by incrementing
 *
 */
void incrementVirtualInput(void)
{
  currentVirtualInput++;
  if(currentVirtualInput >= kNumSourceNames)
    currentVirtualInput = 0;
}

//==============================================================================
/*! Selects the next virtual input by decrementing
 *
 */
void decrementVirtualInput(void)
{
  currentVirtualInput--;
  if(currentVirtualInput < 0)
    currentVirtualInput = kNumSourceNames - 1;
}