#include <Arduino.h>
#include <WiFi.h>

#include "display.h"
#include "plugin.h"

OLED128x64_SH1106 myDisplay;
bool haveDisplay = true;
bool needUpdateUI = false;
int editMode = 0;

//==============================================================================
/*! Updates the user interface on the display
 *
 */
void updateUI( void )
{
  if( haveDisplay )
  {
    String ip;
    if( WiFi.status() != WL_CONNECTED )
      ip = "Not Connected";
    else
      ip = WiFi.localIP().toString();

    if( (editMode == 0) || (editMode == 1) )
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
