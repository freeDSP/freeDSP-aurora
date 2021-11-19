#ifndef CHANNELNAMES_H_
#define CHANNELNAMES_H_

extern String channelNames[NUMCHANNELNAMES];
extern String presetNames[NUMPRESETS];

//==============================================================================
/*! Write the channel names to file.
 */
void writeChannelNames(void);

//==============================================================================
/*! Reads the channel names from file.
 */
void readChannelNames(void);

//==============================================================================
/*! Creates a page for editing the channel names
 *
 */
String createChannelNamesPage(void);

#endif