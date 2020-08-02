#include <Arduino.h>
#include <ArduinoJson.h>
#include <SPIFFS.h>

#include "addons.h"
#include "plugin.h"
#include "settings.h"
#include "config.h"

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
