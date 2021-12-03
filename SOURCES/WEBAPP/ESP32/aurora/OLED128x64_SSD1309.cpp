#include <U8g2lib.h>

#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif

#include "hwconfig.h"
#include "OLED128x64_SSD1309.h"

extern String getCurrentVirtualInputName(void);
extern String currentPlugInName;

U8G2_SSD1309_128X64_NONAME0_F_HW_I2C u8g2_ssd1309( U8G2_R0, /* clock=*/ I2C_SCL_PIN, /* data=*/ I2C_SDA_PIN, /* reset=*/ U8X8_PIN_NONE );

void OLED128x64_SSD1309::begin(void)
{
  u8g2_ssd1309.setBusClock(100000);
  u8g2_ssd1309.begin();
  u8g2_ssd1309.setFont(u8g2_font_6x10_tf);
  u8g2_ssd1309.setFontRefHeightExtendedText();
  u8g2_ssd1309.setDrawColor(1);
  u8g2_ssd1309.setFontPosTop();
  u8g2_ssd1309.setFontDirection(0);

}

void OLED128x64_SSD1309::setI2CAddress(uint8_t addr)
{
  u8g2_SetI2CAddress(u8g2_ssd1309.getU8g2(), addr);
}

void OLED128x64_SSD1309::clearBuffer(void)
{
  u8g2_ssd1309.clearBuffer();
}

void OLED128x64_SSD1309::sendBuffer(void)
{
  u8g2_ssd1309.sendBuffer();
}

void OLED128x64_SSD1309::drawBootScreen(void)
{
  u8g2_ssd1309.clearBuffer();

  u8g2_ssd1309.setFont(u8g2_font_helvR14_tf);
  u8g2_ssd1309.setFontRefHeightExtendedText();
  u8g2_ssd1309.drawStr(23, 10, "AURORA");

  u8g2_ssd1309.setFont(u8g2_font_6x10_tf);
  u8g2_ssd1309.setFontRefHeightExtendedText();
  u8g2_ssd1309.drawStr(0, 54, "Booting...");

  u8g2_ssd1309.sendBuffer();
}

void OLED128x64_SSD1309::drawUI(const char* plugin, const char* ip, const char* preset, float vol, int editMode)
{
  u8g2_ssd1309.clearBuffer();
  if(currentPlugInName == String(F("stereoforever")) || currentPlugInName == String(F("The Room")))
  {
    //u8g2_ssd1309.setFont(u8g2_font_5x7_tf);
    u8g2_ssd1309.setFont( u8g2_font_helvR08_tf );
    u8g2_ssd1309.setFontRefHeightExtendedText();
    u8g2_ssd1309.drawStr(0,  0, plugin);
    String str = String("Input:  ") + getCurrentVirtualInputName();
    u8g2_ssd1309.drawStr(0, 14, str.c_str());
    str = String("Preset:  ") + String(preset);
    u8g2_ssd1309.drawStr(0, 26, str.c_str());
    char buf[10];
    dtostrf( vol, 4, 1, buf );
    str = String("Volume:  ") + String(buf) + String("dB");
    u8g2_ssd1309.drawStr(0, 38, str.c_str());

    u8g2_ssd1309.drawLine(0, 11, 127, 11);
    u8g2_ssd1309.drawLine(0, 53, 127, 53);

    if( editMode == 1 )
    {
      u8g2_ssd1309.drawLine( 13, 44, 31, 44 );
      u8g2_ssd1309.drawLine( 13, 45, 31, 45 );
    }
    
    u8g2_ssd1309.setFont(u8g2_font_5x7_tf);
    u8g2_ssd1309.setFontRefHeightExtendedText();
    u8g2_ssd1309.drawStr( 0, 54, ip );
  }
  else
  {
    u8g2_ssd1309.drawLine(42, 12, 42, 52);

    u8g2_ssd1309.drawLine(0, 53, 127, 53);


    u8g2_ssd1309.setFont(u8g2_font_helvB18_tf);
    u8g2_ssd1309.drawStr(13, 20, preset);
    if( editMode == 1 )
    {
      u8g2_ssd1309.drawLine(13, 44, 31, 44);
      u8g2_ssd1309.drawLine(13, 45, 31, 45);
    }
    char buf[10];
    dtostrf(vol, 4, 1, buf);
    u8g2_ssd1309.drawStr(60, 20, buf);

    u8g2_ssd1309.setFont(u8g2_font_helvR08_tf);
    u8g2_ssd1309.drawStr(116, 31, "dB");

    u8g2_ssd1309.setFont(u8g2_font_5x7_tf);
    u8g2_ssd1309.setFontRefHeightExtendedText();
    u8g2_ssd1309.drawStr(0,  0, plugin);
    u8g2_ssd1309.drawStr(0, 54, ip);

  }
  u8g2_ssd1309.sendBuffer();
}

void OLED128x64_SSD1309::drawSwitchingPreset(void)
{
  u8g2_ssd1309.clearBuffer();

  u8g2_ssd1309.setFont(u8g2_font_helvR08_tf);
  u8g2_ssd1309.setFontRefHeightExtendedText();
  u8g2_ssd1309.drawStr(5, 10, "Switching Preset...");

  u8g2_ssd1309.sendBuffer();
}
