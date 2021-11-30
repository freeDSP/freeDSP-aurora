#include <Wire.h>
#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <SPIFFS.h>
#include "AsyncJson.h"
#include <ArduinoJson.h>
#include "soc/timer_group_struct.h"
#include "soc/timer_group_reg.h"

#include "hwconfig.h"
#include "AK4458.h"
#include "AK5558.h"

#if HAVE_ROTARYENCODER
#include "rotaryencoder.h"
#endif

#if HAVE_IRRECEIVER
#include <IRremote.h>
#endif

#include "config.h"
#include "settings.h"
#include "adau1452.h"
#include "addons.h"
#include "display.h"
#include "plugin.h"
#include "web.h"
#include "display.h"
#include "channelnames.h"
#include "inputrouting.h"

/**
 * These are required for the espmake32 automatic library resolver
 * It's less powerful than the one from the Arduino IDE.
 * The if-guards can stay
 * see https://github.com/plerup/makeEspArduino
 */
#if 0
#include <FS.h>
#include <WebServer.h>
#include <AsyncTCP.h>
#include <u8g2.h>
#endif

File fileDspProgram;

bool changeWifiState = false;

//------------------------------------------------------------------------------
//
// Display
//
//------------------------------------------------------------------------------
#if HAVE_DISPLAY
Display myDisplay;
#endif

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

//==============================================================================
/*! Uploads the firmware from ESP32 SPI flash to DSP.
 */
void uploadDspFirmware( void )
{
  Serial.print(F("Init dsp......"));

  if(!SPIFFS.exists(F("/dsp.fw")))
  {
    Serial.println(F("File does not exist yet"));
    return;
  }

  fileDspProgram = SPIFFS.open(F("/dsp.fw"));

  uint32_t numBytesToRead = 0;
  byte byteReadMSB;
  byte byteReadLSB;
  uint16_t regaddr;

  if(fileDspProgram)
  {
    size_t len = fileDspProgram.size();
    int cntr = 0;
    while(cntr < len)
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

      //------------------------------------------------------------------------
      //--- Send register address and value
      //------------------------------------------------------------------------
      if(numBytesToRead > 0)
      {
        fileDspProgram.read(&byteRead, 1);
        regaddr = ((uint16_t)byteRead) << 8;
        cntr++;

        fileDspProgram.read(&byteRead, 1);
        regaddr += byteRead;
        cntr++;

        if(numBytesToRead == 4)
        {
          fileDspProgram.read(&byteReadMSB, 1);
          cntr++;
          fileDspProgram.read(&byteReadLSB, 1);
          cntr++;

          if(regaddr == 0x0000)
            delay(500);
          else
          {
            ADAU1452_WRITE_REGISTER(regaddr, byteReadMSB, byteReadLSB);
            if(cntr % 4096 == 0)
              Serial.print(F("."));
          }
        }
        else if(numBytesToRead > 4)
        {
          uint16_t addr = regaddr;
          byte val[4];

          for(uint32_t ii = 0; ii < numBytesToRead - 2; ii = ii + 4)
          {
            fileDspProgram.read(&(val[0]), 1);
            fileDspProgram.read(&(val[1]), 1);
            fileDspProgram.read(&(val[2]), 1);
            fileDspProgram.read(&(val[3]), 1);
            cntr += 4;
            ADAU1452_WRITE_BLOCK(addr, val, 4);
            if(cntr % 4096 == 0)
              Serial.print(F("."));
            addr++;
          }
        }
        else
        {
          Serial.print(F("[ERROR] Bad number of bytes: "));
          Serial.println(numBytesToRead);
        }
      }
    }
    int file_size = fileDspProgram.size();

    fileDspProgram.close();
    Serial.println(F("[OK]"));
    Serial.print(F("File size: "));
    Serial.println(file_size);
  }
  else
    Serial.println(F("\n[ERROR] Failed to open file dsp.fw"));
}

#if HAVE_DISPLAY
//==============================================================================
/*! Updates the user interface on the display
 *
 */
void updateUI( void )
{
  if(haveDisplay)
  {
    String ip;
    if( WiFi.status() != WL_CONNECTED )
      ip = "Not Connected";
    else
      ip = WiFi.localIP().toString();

    if( (editMode == 0) || (editMode == 1) || (editMode == 2) )
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
#endif

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
  WiFi.setHostname("freeDSP-aurora");
  // Start access point
  if( Settings.pwdap.length() > 0 )
  {
    Serial.print(F("AP password protected "));
    Serial.println(Settings.apname);
    WiFi.softAP(Settings.apname.c_str(), Settings.pwdap.c_str());
  }
  else
  {
    Serial.print(F("AP open: "));
    Serial.println(Settings.apname);
    WiFi.softAP(Settings.apname.c_str());
  }
  delay(100);

  if(!WiFi.softAPConfig(ip, ip, subnet))
    Serial.println(F("AP Config Failed"));

  // Start server
  server.begin();

  while(true)
  {
    if((Settings.ssid.length() > 0) &&  (cntrAuthFailure < 10))
    {
      state = WiFi.status();
      if(state != WL_CONNECTED)
      {
        //if (state == WL_NO_SHIELD)
        if(firstConnectAttempt)
        {
          firstConnectAttempt = false;
          Serial.print(F("Connecting to "));
          Serial.println(Settings.ssid.c_str());
          WiFi.begin(Settings.ssid.c_str(), Settings.password.c_str());
          cntrAuthFailure++;
        }
        else if(state == WL_IDLE_STATUS)
        {
          Serial.println(F("Idle"));
        }
        else if(state == WL_NO_SSID_AVAIL)
        {
          Serial.println(F("No SSID available"));
        }
        else if(state == WL_CONNECTION_LOST)
        {
          Serial.println(F("WiFi connection lost"));
          WiFi.disconnect(true);
          cntrAuthFailure++;
        }
        // else if( state == WL_SCAN_COMPLETED )
        else if(state == WL_CONNECT_FAILED)
        {
          Serial.println(F("WiFi connection failed"));
          WiFi.disconnect(true);
          cntrAuthFailure++;
        }
        else if(state == WL_DISCONNECTED)
        {
          if(!myWiFiFirstConnect)
          {
            myWiFiFirstConnect = true;
            Serial.println(F("WiFi disconnected"));
          }
          Serial.println(F("No Connection -> Wifi Reset"));
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
        if(myWiFiFirstConnect) // Report only once
        {
          myWiFiFirstConnect = false;
          cntrAuthFailure = 0;
          Serial.println(F("Connected"));
          Serial.print(F("IP address: "));
          Serial.println(WiFi.localIP());
          Serial.println(WiFi.getHostname());
          needUpdateUI = true;
        }
        vTaskDelay(5000); // Check again in about 5s
      }
    }
    else
      vTaskDelay(5000);
  }
}


//==============================================================================
/*! Arduino Setup
 *
 */
void setup()
{
  Serial.begin(115200);
  Serial.println(F("AURORA Debug Log"));
  Serial.println( VERSION_STR );
  #if DEBUG_PRINT
  Serial.print("Heap: ");
  Serial.println(xPortGetFreeHeapSize());
  #endif

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
  #if HAVE_DISPLAY
  haveDisplay = false;
  Wire.beginTransmission(SSD1309_I2C_ADDR);
  if(Wire.endTransmission(true) == 0)
  {
    Serial.println(F("Detected SSD1309 display"));
    SSD1309.setI2CAddress(SSD1309_I2C_ADDR<<1);
    myDisplay.begin(&SSD1309);
    haveDisplay = true;
  }
  if(!haveDisplay)
  {
    Wire.beginTransmission(SH1106_I2C_ADDR);
    if(Wire.endTransmission(true) == 0)
    {
      Serial.println(F("Detected SH1106 display"));
      myDisplay.begin(&SH1106);
      haveDisplay = true;
    }
  }

  //----------------------------------------------------------------------------
  //--- Init Display (if present)
  //----------------------------------------------------------------------------
  if(haveDisplay)
    myDisplay.drawBootScreen();
  #endif

  // wait until everything is stable
  // might be a bit to defensive
  delay(2000);

  //----------------------------------------------------------------------------
  //--- Configure DAC
  //----------------------------------------------------------------------------
  Serial.println(F("Config DAC"));
  configDAC();

  //----------------------------------------------------------------------------
  //--- Configure ADC
  //----------------------------------------------------------------------------
  Serial.println(F("Config ADC"));
  configADC();

  //----------------------------------------------------------------------------
  //--- Start SPIFFS
  //----------------------------------------------------------------------------
  if(!SPIFFS.begin(true))
  {
    Serial.println(F("An Error has occurred while mounting SPIFFS"));
    return;
  }

  //--- check for old stuff (version == 1.x.x)
  String fileName = "/dspfw.hex";
  if(SPIFFS.exists(fileName))
  {
    if( SPIFFS.remove(fileName))
      Serial.println(fileName + " deleted.");
    else
      Serial.println("[ERROR] Deleting " + fileName );
  }
  fileName = "/dspparam.001";
  if(SPIFFS.exists(fileName))
  {
    if(SPIFFS.remove(fileName))
      Serial.println(fileName + " deleted.");
    else
      Serial.println("[ERROR] Deleting " + fileName);
  }
  fileName = "/dspparam.002";
  if(SPIFFS.exists(fileName))
  {
    if(SPIFFS.remove(fileName))
      Serial.println(fileName + F(" deleted."));
    else
      Serial.println("[ERROR] Deleting " + fileName);
  }
  fileName = "/dspparam.003";
  if(SPIFFS.exists(fileName))
  {
    if(SPIFFS.remove(fileName))
      Serial.println(fileName + " deleted.");
    else
      Serial.println("[ERROR] Deleting " + fileName);
  }
  fileName = "/dspparam.004";
  if(SPIFFS.exists(fileName))
  {
    if(SPIFFS.remove(fileName))
      Serial.println(fileName + F(" deleted."));
    else
      Serial.println("[ERROR] Deleting " + fileName);
  }

  Serial.print(F("Free disk space: "));
  Serial.print( (SPIFFS.totalBytes() - SPIFFS.usedBytes()) / 1024 );
  Serial.println(F("KiB"));

  File root = SPIFFS.open("/");
  File file = root.openNextFile();
  while(file)
  {
    Serial.print(file.name());
    Serial.print(F(" "));
    Serial.print(file.size());
    Serial.println(F(" Bytes"));
    file = root.openNextFile();
  }

  //----------------------------------------------------------------------------
  //--- Read settings file
  //----------------------------------------------------------------------------
  readSettings();
  changeChannelSummationADC();
  if( changeWifiState )
  {
    Serial.print(F("Changing WiFi status......"));
    Settings.wifiOn = Settings.wifiOn ? false : true;
    writeSettings();
    Serial.println(F("[OK]"));
  }

  Serial.print(F("Init user parameter......"));
  initUserParams();
  Serial.println(F("[OK]"));
  readPluginMeta();

  //----------------------------------------------------------------------------
  //--- Read virtual input channel routing (only if supported by plugin)
  //----------------------------------------------------------------------------
  if(currentPlugInName == String(F("stereoforever")))
  {
    if(!SPIFFS.exists(F("/vinputs.txt")))
      // if file does not exist, write it with defautl values
      writeVirtualInputRouting();
    else
      readVirtualInputRouting();
  }

  readChannelNames();

  //----------------------------------------------------------------------------
  //--- Configure AddOn
  //----------------------------------------------------------------------------
  updateAddOn();

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
  setupWebserver();

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

  resetDAC(false);

  updateUI();

  lastREsw = rotaryEncoder.getSwitchValue();
  lastREval = rotaryEncoder.getRotationValue();

  #if DEBUG_PRINT
  Serial.print("Heap: ");
  Serial.println(xPortGetFreeHeapSize());
  #endif

  Serial.println(F("Ready"));
}

//==============================================================================
/*! Helpers
 *
 */

void update_preset(void) {
  softMuteDAC();
  initUserParams();
  uploadUserParams();
  updateAddOn();
  softUnmuteDAC();
}

void next_preset(void) {
  currentPreset++;
  if( currentPreset >= MAX_NUM_PRESETS )
    currentPreset = 0;

  update_preset();
}

void prev_preset(void) {
  if( currentPreset == 0 )
    currentPreset = MAX_NUM_PRESETS - 1;
  else
    currentPreset--;

  update_preset();
}

void increase_volume(void) {
  masterVolume.val += 0.5f;
  if( masterVolume.val > 0.f )
    masterVolume.val = 0.f;
  setMasterVolume();
}

void decrease_volume(void) {
  masterVolume.val -= 0.5f;
  if( masterVolume.val <= -80.f )
    masterVolume.val = -80.f;
  setMasterVolume();
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
    if(changeWifiState)
      changeWifiState = false;
    else
    {
      editMode++;
      if(currentPlugInName == String(F("stereoforever")))
      {
        if(editMode > 2)
          editMode = 0;
      }
      else
      {
        // we may have more then two modes in the future.
        if(editMode > 1)
          editMode = 0;
      }
      
      delay(300);
      needUpdateUI = true;
    }
    lastREsw = rotaryEncoder.getSwitchValue();
    lastREval = rotaryEncoder.getRotationValue();
  }
  else if( rotaryEncoder.getRotationValue() > lastREval + 1 )
  {
    if(editMode == 0)
    {
      increase_volume();
      lastREval = rotaryEncoder.getRotationValue();
      needUpdateUI = true;
    }
    else if( editMode == 1 )
    {
      myDisplay.drawSwitchingPreset();

      next_preset();

      lastREval = rotaryEncoder.getRotationValue();
      needUpdateUI = true;
    }
    else if(editMode == 2)
    {
      if(currentPlugInName == String(F("stereoforever")))
      {
        incrementVirtualInput();
        softMuteDAC();
        updateUI();
        softUnmuteDAC();
        lastREval = rotaryEncoder.getRotationValue();
        needUpdateUI = true;
      }
    }
  }
  else if( rotaryEncoder.getRotationValue() < lastREval - 1 )
  {
    if( editMode == 0 )
    {
      decrease_volume();
      lastREval = rotaryEncoder.getRotationValue();
      needUpdateUI = true;
    }
    else if( editMode == 1 )
    {
      myDisplay.drawSwitchingPreset();

      prev_preset();

      lastREval = rotaryEncoder.getRotationValue();
      needUpdateUI = true;
    }
    else if(editMode == 2)
    {
      if(currentPlugInName == String(F("stereoforever")))
      {
        decrementVirtualInput();
        softMuteDAC();
        updateUI();
        softUnmuteDAC();
        lastREval = rotaryEncoder.getRotationValue();
        needUpdateUI = true;
      }
    }
  }
  #endif

  #if HAVE_IRRECEIVER
  decode_results irResults;
  if( irReceiver.decode( &irResults ) )
  {
    if( irResults.value == APPLE_REMOTE_UP )
    {
      increase_volume();
      needUpdateUI = true;
    }
    else if( irResults.value == APPLE_REMOTE_DOWN )
    {
      decrease_volume();
      needUpdateUI = true;
    }
    else if( irResults.value == APPLE_REMOTE_LEFT )
    {
      myDisplay.drawSwitchingPreset();

      prev_preset();

      needUpdateUI = true;
    }
    else if( irResults.value == APPLE_REMOTE_RIGHT )
    {
      myDisplay.drawSwitchingPreset();

      next_preset();

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
