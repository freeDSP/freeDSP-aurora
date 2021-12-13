#ifndef DISPLAY_H_
#define DISPLAY_H_

#include "editmode.h"
#include "OLED128x64_SH1106.h"
#include "OLED128x64_SSD1309.h"

extern bool haveDisplay;
extern bool needUpdateUI;
extern int editMode;

extern OLED128x64_SH1106 SH1106;
extern OLED128x64_SSD1309 SSD1309;

class Display
{
public:
  Display(void) {}

  void begin(DisplayDriver* drv)
  {
    pDisplayDriver = drv;
    if(pDisplayDriver)
      pDisplayDriver->begin();
  }

  void drawBootScreen(void)
  { 
    if(pDisplayDriver)
      pDisplayDriver->drawBootScreen();
  }

  void drawUI(const char* plugin, const char* ip, const char* preset, float vol, int editMode = EDITMODE_DEFAULT)
  {
    if(pDisplayDriver)
      pDisplayDriver->drawUI(plugin, ip, preset, vol, editMode);
  }

  void drawSwitchingPreset(void)
  {
    if(pDisplayDriver)
      pDisplayDriver->drawSwitchingPreset();
  }

private:
  DisplayDriver* pDisplayDriver = nullptr;
};

#endif
