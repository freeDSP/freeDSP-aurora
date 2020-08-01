#ifndef JSON_H_
#define JSON_H_

/**
 * json.h + json.cpp covers all routines that take care of handling the json file(s)
 * (It's a mindless copy&paste from the original aurora.ino, plus added headers)
 */

//==============================================================================
/*! Write the device settings to JSON file.
 */
void writeSettings( void );

//==============================================================================
/*! Reads the device settings from JSON file.
 */
void readSettings( void );

#endif
