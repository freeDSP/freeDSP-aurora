#ifndef OLED128x64_SH1106_H_
#define OLED128x64_SH1106_H_

#include "displaydriver.h"

class OLED128x64_SH1106 : public DisplayDriver
{
public:
  virtual void begin(void);

  void setI2CAddress(uint8_t addr);

  void clearBuffer(void);
  void sendBuffer(void);

  virtual void drawBootScreen(void);
  virtual void drawUI(const char* plugin, const char* ip, const char* preset, float vol, int editMode = EDITMODE_DEFAULT);
  virtual void drawSwitchingPreset(void);

private:

};

#endif
