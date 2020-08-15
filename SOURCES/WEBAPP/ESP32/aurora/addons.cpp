#include <Arduino.h>
#include <Wire.h>
#include <SPIFFS.h>

#include "hwconfig.h"
#include "plugin.h"
#include "adau1452.h"
#include "addons.h"
#include "ak4118.h"

extern AK4118 AddOnC;

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
/*! Setup AddOn C
 *
 */
void setupAddOnC( void )
{
  Serial.print( "Init AddOn C......" );

  //--- Reset AK4118
  AddOnC.write(AK4118_CLK_PDN, 0b01000010);
  delay(100);

  /* CLK & Power Down Control
   * bit[0]   : RSTN: Timing Reset & Register Initialize              :   1 Normal Operation
   * bit[1]   : PWN: Power Down                                       :   1 Normal Operation
   * bit[3:2] : OCKS1-0: Master Clock Frequency Select                :  10 X'tal = 512fs (default)
   * bit[5:4] : CM1-0: Master Clock Operation Mode Select             :  00 Mode0 (default)
   * bit[6]   : BCU: Block start & C/U Output Mode                    :   1 BOUT, COUT, UOUT enabled (default)
   * bit[7]   : CS12: Channel Status Select                           :   0 Channel 1 (default)
   */
  AddOnC.write(AK4118_CLK_PDN, 0b01001011);

  /* Format & De-emphasis Control
   * bit[0]   : DFS: 96kHz De-emphasis Control                        :   0 (defaut)
   * bit[2:1] : DEM1-0: 32, 44.1, 48kHz De-emphasis Control           :  01 (default)
   * bit[3]   : DEAU: De-emphasis Auto Detect Enable                  :   1 Enable (default)
   * bit[6:4] : DIF2-0: Audio Data Format Control                     : 100 Mode4 24bit LJ H/L Master BCK 64fs
   * bit[7]   : MONO: Double sampling frequency mode enable           :   0 Stereo mode (default)
   */
  AddOnC.write(AK4118_FORMAT, 0b01001010);

  /* Input/ Output Control 0
   * bit[2:0] : OPS02-00: Output Through Data Select for TX0 pin      : 000 RX0 (defaut)
   * bit[3]   : TX0E: TX0 Output Enable                               :   1 Enable (default) 
   * bit[6:4] : OPS12-10: Output Through Data Select for TX1 pin      : 000 DAUX (default)
   * bit[7]   : TX1E: TX1 Output Enable                               :   1 Enable (default)
   */
  AddOnC.write(AK4118_IOCONTROL0, 0b10001000);

  /* Input/ Output Control 1
   * bit[2:0] : IPS02-00: IPS2-0: Input Recovery Data Select          : 000 RX0 (defaut)
   * bit[3]   : DIT: Through data/Transmit data select for TX1 pin    :   1 Transmit data (DAUX data) (default) 
   * bit[4]   : TLR: Double sampling frequency mode channel select for DIT(stereo) : 0 L channel (default)
   * bit[5]   : UDIT: U bit control for DIT                           :   0 U bit is fixed to “0” (default)
   * bit[7:6] : EFH1-0: Interrupt 0 Pin Hold Count Select             :  01 1024 LRCK (default)
   */
  AddOnC.write(AK4118_IOCONTROL1, 0b01001000);

  String fileName = presetAddonCfgFile[currentPreset];
  File fileAddonConfig = SPIFFS.open( fileName );
  if( !fileAddonConfig )
    Serial.println( "[ERROR] Failed to open " + fileName );
  else
  {
    Serial.println( "Opened " + fileName );

    size_t len = fileAddonConfig.read( currentAddOnCfg, 3 );
    if( len != 3 )
      Serial.println( "[ERROR] Reading AddOn config " + fileName );

    fileAddonConfig.close();

    AddOnC.write( AK4118_IOCONTROL1, currentAddOnCfg[2] );
  }

  Serial.println( "[OK]" );
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
    setupAddOnC();
    break;
  case ADDON_D:
    // Nothing to do
    break;
  case ADDON_CUSTOM:
    // Nothing to do
    break;
  }
}
