#ifndef DISPLAYDRIVER_H_
#define DISPLAYDRIVER_H_

#include "editmode.h"

// Base class for display driver
class DisplayDriver
{
public:
  virtual void begin(void) = 0;
  virtual void drawBootScreen(void) = 0;
  virtual void drawUI(const char* plugin, const char* ip, const int currentPreset, float vol, int editMode = EDITMODE_DEFAULT) = 0;
  virtual void drawSwitchingPreset(void) = 0;
};

#endif
