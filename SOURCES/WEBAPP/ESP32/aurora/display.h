#ifndef DISPLAY_H_
#define DISPLAY_H_
#include "OLED128x64_SH1106.h"

extern OLED128x64_SH1106 myDisplay;
extern bool haveDisplay;
extern bool needUpdateUI;
extern int editMode;

void updateUI( void );

#endif
