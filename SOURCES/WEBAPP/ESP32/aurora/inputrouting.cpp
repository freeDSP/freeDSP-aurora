#include <Arduino.h>
#include <ESPAsyncWebServer.h>
#include <AsyncJson.h>
#include <ArduinoJson.h>

#include "config.h"

static const int kNumSourceNames = 8;
const char* sourceNames[kNumSourceNames] = {"CD-A:", "Blueray:", "Phono:", "Aux:", "USB:", "SPDIF coax:", "SPDIF optical:", "Streaming:"};

//! TODO Make this dynamic depending on plugin
static const int kNumVirtualInputs = 2;

int sourceRouting[kNumSourceNames][kNumVirtualInputs] = {{0, 1}, {2, 3}, {4, 5}, {6, 7}, {8, 9}, {16, 17}, {24, 25}, {32, 33}};


//==============================================================================
/*! Builds the HTML page for the input routing by source names.
 *
 */
String createInputRoutingPage(int numinputs)
{
  String ret;
  int id = 0;
  
  ret += R"!^!(
    <!DOCTYPE html>
    <html lang="en">
    <meta name="viewport" content="width=device-width, initial-scale=1" charset="utf-8">
    <head>
    <title>AURORA DSP</title>
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
  )!^!";

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
  ret += String("\"SPDIF Coax 1 Left\", \"SPDIF Coax 1 Right\", \"SPDIF Coax 2 Left\", \"SPDIF Coax 2 Right\", \"SPDIF Coax 3 Left\", \"SPDIF Coax 3 Right\", \"SPDIF Coax 4 Left\", \"SPDIF Coax 4 Right\",");
  ret += String("\"SPDIF Optical 1 Left\", \"SPDIF Optical 1 Right\", \"SPDIF Optical 2 Left\", \"SPDIF Optical 2 Right\", \"SPDIF Optical 3 Left\", \"SPDIF Optical 3 Right\", \"SPDIF Optical 4 Left\", \"SPDIF Optical 4 Right\",");
  ret += String("\"Expansion 1\", \"Expansion 2\"");
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

  DynamicJsonDocument jsonDoc(1024);
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
    for(int nn = 0; nn < kNumVirtualInputs; nn++)
    {
      if((mm < root["select"].size()) && (nn < root["select"][mm].size()))
        sourceRouting[mm][nn] = root["select"][mm][nn];
    }
  }

  request->send(200, "text/plain", "");
}
