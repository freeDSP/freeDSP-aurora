#ifndef OLED128x64_SH1106_H_
#define OLED128x64_SH1106_H_

//#include <U8g2lib.h>

//#ifdef U8X8_HAVE_HW_I2C
//#include <Wire.h>
//#endif


class OLED128x64_SH1106
{
public:
  void begin( void );

  void clearBuffer( void );
  void sendBuffer(void );

  void drawBootScreen( void );
  void drawUI( const char* plugin, const char* ip, const char* preset, float vol, int editMode = 0 );
  void drawSwitchingPreset( void );

private:

};

#endif
