#include <Arduino.h>
#include <WiFi.h>

#include "display.h"
#include "plugin.h"

OLED128x64_SH1106 SH1106;
OLED128x64_SSD1309 SSD1309;

bool haveDisplay = true;
bool needUpdateUI = false;
int editMode = EDITMODE_DEFAULT;
