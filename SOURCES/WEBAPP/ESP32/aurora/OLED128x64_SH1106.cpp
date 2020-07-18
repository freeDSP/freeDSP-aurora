#include <U8g2lib.h>

#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif

//#include "u8g2_esp32_hal.h"

#include "hwconfig.h"
#include "OLED128x64_SH1106.h"

U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2( U8G2_R0, /* clock=*/ I2C_SCL_PIN, /* data=*/ I2C_SDA_PIN, /* reset=*/ U8X8_PIN_NONE );

void OLED128x64_SH1106::begin( void )
{
  u8g2.setBusClock(100000);
  u8g2.begin();
  u8g2.setFont(u8g2_font_6x10_tf);
  u8g2.setFontRefHeightExtendedText();
  u8g2.setDrawColor(1);
  u8g2.setFontPosTop();
  u8g2.setFontDirection(0);
}

void OLED128x64_SH1106::clearBuffer( void )
{
  u8g2.clearBuffer();
}

void OLED128x64_SH1106::sendBuffer(void )
{
  u8g2.sendBuffer();
}

void OLED128x64_SH1106::drawBootScreen( void )
{
  u8g2.clearBuffer();

  u8g2.setFont( u8g2_font_helvR14_tf );
  u8g2.setFontRefHeightExtendedText();
  u8g2.drawStr( 23, 10, "AURORA");

  u8g2.setFont(u8g2_font_6x10_tf);
  u8g2.setFontRefHeightExtendedText();
  u8g2.drawStr( 0, 54, "Booting...");

  u8g2.sendBuffer();
}

void OLED128x64_SH1106::drawUI( const char* plugin, const char* ip, const char* preset, float vol, int editMode )
{
  u8g2.clearBuffer();

  u8g2.drawLine( 42, 12, 42, 52 );

  u8g2.drawLine( 0, 53, 127, 53 );


  u8g2.setFont( u8g2_font_helvB18_tf );
  u8g2.drawStr( 13, 20, preset );
  if( editMode == 1 )
  {
    u8g2.drawLine( 13, 44, 31, 44 );
    u8g2.drawLine( 13, 45, 31, 45 );
  }
  char buf[10];
  dtostrf( vol, 4, 1, buf );
  u8g2.drawStr( 60, 20, buf );

  u8g2.setFont( u8g2_font_helvR08_tf );
  u8g2.drawStr( 116, 31, "dB" );

  u8g2.setFont(u8g2_font_5x7_tf);
  u8g2.setFontRefHeightExtendedText();
  u8g2.drawStr( 0,  0, plugin );
  u8g2.drawStr( 0, 54, ip );

  u8g2.sendBuffer();
}

void OLED128x64_SH1106::drawSwitchingPreset( void )
{
  u8g2.clearBuffer();

  u8g2.setFont( u8g2_font_helvR08_tf );
  u8g2.setFontRefHeightExtendedText();
  u8g2.drawStr( 5, 10, "Switching Preset...");

  u8g2.sendBuffer();
}
