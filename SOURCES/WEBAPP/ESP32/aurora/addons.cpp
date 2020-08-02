#include <Arduino.h>
#include <Wire.h>
#include <SPIFFS.h>

#include "hwconfig.h"
#include "plugin.h"
#include "adau1452.h"
#include "addons.h"

//==============================================================================
/*! Setup AddOn B
 *
 */
void setupAddOnB( void )
{
  Serial.print( "Init AddOn B......" );
  Wire.beginTransmission( ADDONB_SPDIFMUX_ADDR );
  Wire.write( 0x03 );
  Wire.write( 0x00 );
  Wire.endTransmission( true );

  String fileName = presetAddonCfgFile[currentPreset];

  File fileAddonConfig = SPIFFS.open( fileName );
  if( !fileAddonConfig )
    Serial.println( "[ERROR] Failed to open " + fileName );
  else
    Serial.println( "Opened " + fileName );

  size_t len = fileAddonConfig.read( currentAddOnCfg, 3 );
  if( len != 3 )
    Serial.println( "[ERROR] Reading AddOn config " + fileName );

  fileAddonConfig.close();

  Wire.beginTransmission( currentAddOnCfg[0]>>1 ); //ADDONB_SPDIFMUX_ADDR
  Wire.write( currentAddOnCfg[1] ); // regaddr
  Wire.write( currentAddOnCfg[2] ); // data
  Wire.endTransmission( true );

  Serial.println( "[OK]" );
}

//==============================================================================
/*! Setup AddOn A
 *
 */
void setupAddOnA( void )
{
  Wire.beginTransmission( ADDONA_SPDIFMUX_ADDR );
  Wire.write( 0x03 );
  Wire.write( 0xFF );
  Wire.endTransmission( true );

  Wire.beginTransmission( ADDONA_SPDIFMUX_ADDR );
  Wire.write( 0x00 );
  Wire.endTransmission();
  Wire.requestFrom( ADDONA_SPDIFMUX_ADDR, 1 );
  if( Wire.available() == 1 )
  {
    byte value = Wire.read();

    // Analog RCA
    if( (value == 0xfe) || (value == 0xff) )
    {
      Serial.println( "Analog RCA" );
      uint32_t data = 0x00000004;
      byte val[4];
      val[0] = (data >> 24 ) & 0xFF;
      val[1] = (data >> 16 ) & 0xFF;
      val[2] = (data >> 8 ) & 0xFF;
      val[3] = data & 0xFF;
      for( int ii = 0; ii < numInputs; ii++ )
        ADAU1452_WRITE_BLOCK( inputSelector.analog[ii],  val, 4 );

      data = 0x00000000;
      val[0] = (data >> 24 ) & 0xFF;
      val[1] = (data >> 16 ) & 0xFF;
      val[2] = (data >> 8 ) & 0xFF;
      val[3] = data & 0xFF;
      for( int ii = 0; ii < numInputs; ii++ )
        ADAU1452_WRITE_BLOCK( inputSelector.port[ii], val, 4 );

      for( int ii = 0; ii < numInputs; ii++ )
        paramInputs[ii].sel = 0x00000004;
    }
    // Analog XLR
    else if( value == 0xf7 )
    {
      Serial.println( "Analog XLR" );
      uint32_t data = 0x00000000;
      byte val[4];
      val[0] = (data >> 24 ) & 0xFF;
      val[1] = (data >> 16 ) & 0xFF;
      val[2] = (data >> 8 ) & 0xFF;
      val[3] = data & 0xFF;
      for( int ii = 0; ii < 8; ii++ )
        ADAU1452_WRITE_BLOCK( inputSelector.analog[ii],  val, 4 );

      data = 0x00000000;
      val[0] = (data >> 24 ) & 0xFF;
      val[1] = (data >> 16 ) & 0xFF;
      val[2] = (data >> 8 ) & 0xFF;
      val[3] = data & 0xFF;
      for( int ii = 0; ii < 8; ii++ )
        ADAU1452_WRITE_BLOCK( inputSelector.port[ii], val, 4 );

      for( int ii = 0; ii < numInputs; ii++ )
        paramInputs[ii].sel = 0x00000000;
    }
    // Toslink left channel
    else if( (value == 0xfa) || (value == 0xfb) )
    {
      Serial.println( "Toslink left channel" );
      uint32_t data = 0x00000000;
      byte val[4];
      val[0] = (data >> 24 ) & 0xFF;
      val[1] = (data >> 16 ) & 0xFF;
      val[2] = (data >> 8 ) & 0xFF;
      val[3] = data & 0xFF;
      for( int ii = 0; ii < 8; ii++ )
        ADAU1452_WRITE_BLOCK( inputSelector.spdif[ii],  val, 4 );

      data = 0x00000004;
      val[0] = (data >> 24 ) & 0xFF;
      val[1] = (data >> 16 ) & 0xFF;
      val[2] = (data >> 8 ) & 0xFF;
      val[3] = data & 0xFF;
      for( int ii = 0; ii < 8; ii++ )
        ADAU1452_WRITE_BLOCK( inputSelector.port[ii], val, 4 );

      for( int ii = 0; ii < numInputs; ii++ )
        paramInputs[ii].sel = 0x00040000;
    }
    // Toslink right channel
    else if( value == 0xf3 )
    {
      Serial.println( "Toslink right channel" );
      uint32_t data = 0x00000001;
      byte val[4];
      val[0] = (data >> 24 ) & 0xFF;
      val[1] = (data >> 16 ) & 0xFF;
      val[2] = (data >> 8 ) & 0xFF;
      val[3] = data & 0xFF;
      for( int ii = 0; ii < 8; ii++ )
        ADAU1452_WRITE_BLOCK( inputSelector.spdif[ii],  val, 4 );

      data = 0x00000004;
      val[0] = (data >> 24 ) & 0xFF;
      val[1] = (data >> 16 ) & 0xFF;
      val[2] = (data >> 8 ) & 0xFF;
      val[3] = data & 0xFF;
      for( int ii = 0; ii < 8; ii++ )
        ADAU1452_WRITE_BLOCK( inputSelector.port[ii], val, 4 );

      for( int ii = 0; ii < numInputs; ii++ )
        paramInputs[ii].sel = 0x00040001;
    }
    // Digital RCA left
    else if( (value == 0xfc) || (value == 0xfd) )
    {
      Serial.println( "Digital RCA left" );
      uint32_t data = 0x00000000;
      byte val[4];
      val[0] = (data >> 24 ) & 0xFF;
      val[1] = (data >> 16 ) & 0xFF;
      val[2] = (data >> 8 ) & 0xFF;
      val[3] = data & 0xFF;
      for( int ii = 0; ii < 8; ii++ )
        ADAU1452_WRITE_BLOCK( inputSelector.spdif[ii],  val, 4 );

      data = 0x00000004;
      val[0] = (data >> 24 ) & 0xFF;
      val[1] = (data >> 16 ) & 0xFF;
      val[2] = (data >> 8 ) & 0xFF;
      val[3] = data & 0xFF;
      for( int ii = 0; ii < 8; ii++ )
        ADAU1452_WRITE_BLOCK( inputSelector.port[ii], val, 4 );

      for( int ii = 0; ii < numInputs; ii++ )
        paramInputs[ii].sel = 0x00040000;
    }
    // Digital RCA right
    else if( value == 0xf5 )
    {
      Serial.println( "Digital RCA right" );
      uint32_t data = 0x00000001;
      byte val[4];
      val[0] = (data >> 24 ) & 0xFF;
      val[1] = (data >> 16 ) & 0xFF;
      val[2] = (data >> 8 ) & 0xFF;
      val[3] = data & 0xFF;
      for( int ii = 0; ii < 8; ii++ )
        ADAU1452_WRITE_BLOCK( inputSelector.spdif[ii],  val, 4 );

      data = 0x00000004;
      val[0] = (data >> 24 ) & 0xFF;
      val[1] = (data >> 16 ) & 0xFF;
      val[2] = (data >> 8 ) & 0xFF;
      val[3] = data & 0xFF;
      for( int ii = 0; ii < 8; ii++ )
        ADAU1452_WRITE_BLOCK( inputSelector.port[ii], val, 4 );

      for( int ii = 0; ii < numInputs; ii++ )
        paramInputs[ii].sel = 0x00040001;
    }
  }
}

//==============================================================================
/*! Setup the AddOn
 *
 */
void updateAddOn( void )
{
  switch( Settings.addonid )
  {
  case ADDON_A:
    // Nothing to do
    break;
  case ADDON_B:
    setupAddOnB();
    break;
  case ADDON_C:
    // Nothing to do
    break;
  case ADDON_D:
    // Nothing to do
    break;
  case ADDON_CUSTOM:
    // Nothing to do
    break;
  }
}
