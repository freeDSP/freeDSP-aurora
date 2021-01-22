#include <Arduino.h>
#include <SPIFFS.h>

#include "channelnames.h"

String channelNames[NUMCHANNELNAMES];

//==============================================================================
/*! Write the channel names to file.
 */
void writeChannelNames(void)
{
  Serial.println("writeChannelNames");
  File file = SPIFFS.open("/chnames.txt", FILE_WRITE);
 
  if(!file)
  {
    Serial.println(F("[ERROR] writeChannelNames(): Open channels.txt failed."));
    return;
  }

  for(int ii = 0; ii < NUMCHANNELNAMES; ii++)
    file.print(channelNames[ii] + String("\n"));

  file.close();
}

//==============================================================================
/*! Reads the channel names from file.
 */
void readChannelNames(void)
{
  File file = SPIFFS.open("/chnames.txt", FILE_READ);
 
  if(!file)
  {
    Serial.println(F("[ERROR] readChannelNames(): Open channels.txt failed."));
    return;
  }

  int ii = 0;
  while(file.available())
  {
    String str = file.readStringUntil('\n');
    channelNames[ii] = str;
    ii++;
  }

  file.close();
}