#include <Arduino.h>
#include <Wire.h>

#include "plugin.h"
#include "hwconfig.h"
#include "AK5558.h"

//==============================================================================
/*!
 */
void AK5558_REGWRITE( byte reg, byte val)
{
  Wire.beginTransmission( AK5558_I2C_ADDR );
  Wire.write( reg );
  Wire.write( val );
  Wire.endTransmission( true );
}

//==============================================================================
/*! Configure AK5558 ADC
 */
void configADC( void )
{
  /* Power Management1 (Address: 0x01)
   * bit[0]   : RSTN: Internal Timing Reset                           :   0 Reset
   * bit[2:1] : MONO2-1: Channel Summation mode Select                :  00 Not- Summation mode (default)
   */
  AK5558_REGWRITE( AK5558_POWERMANAGEMENT2, 0b00000000 );

  /* Control 1 (Address: 0x02)
   * bit[0]   : HPFE: High Pass Filter Enable                         :   1 High Pass Filter ON (default)
   * bit[2:1] : DIF1-0: Audio Data Interface Mode Select              :  10 32bit MSB
   * bit[6:3] : CKS3-0: Sampling Speed Mode and MCLK Frequency Select :0110 Normal Speed, 512fs
   */
  AK5558_REGWRITE( AK5558_CONTROL1, 0b00110101 );

  /* Control 2 (Address: 0x03)
   * bit[6:5] : TDM1-0: TDMModesSelect                                :  10 TDM256
   */
  AK5558_REGWRITE( AK5558_CONTROL2, 0b01000000 );

  /* Control 3 (Address: 0x04)
   * bit[0]   : SLOW: Slow Roll-off Filter Select                     :   0: Sharp Roll-off (default)
   * bit[1]   : SD: Short Delay Select                                :   0: Normal Delay (default)
   * bit[7]   : DSD Mode Select                                       :   0: PCM mode (default)
   */
  AK5558_REGWRITE( AK5558_CONTROL3, 0b00000000 );

  /* DSD (Address: 0x05)
   * bit[0:1] : DSDSEL1-0:Select the Frequency of DCLK                :  00: 64fs (default)
   * bit[2]   : DCKB: Polarity of DCLK                                :   0: DSD data is output from DCLK Falling Edge (default)
   * bit[3]   : PMOD: DSD Phase Modulation Mode                       :   0: Not Phase Modulation Mode (default)
   * bit[5]   : DCKS: Master Clock Frequency Select at DSD Mode       :   0: 512fs (default)
   */
  AK5558_REGWRITE( AK5558_DSD, 0b00000000 );

  /* Power Management1 (Address: 0x01)
   * bit[0]   : RSTN: Internal Timing Reset                           :   1 Normal operation
   * bit[2:1] : MONO2-1: Channel Summation mode Select                :  00 Not- Summation mode (default)
   */
  AK5558_REGWRITE( AK5558_POWERMANAGEMENT2, 0b00000001 );
}

//==============================================================================
/*! Change the channel summation of AK5558 ADC
 */
void changeChannelSummationADC( void )
{
  AK5558_REGWRITE( AK5558_POWERMANAGEMENT2, 0b00000000 );
  delay(100);

  // Normal operation
  if( Settings.adcsum == 0 )
    AK5558_REGWRITE( AK5558_POWERMANAGEMENT2, 0b00000001 );
  // 8-to-4 mode
  else if( Settings.adcsum == 1 )
    AK5558_REGWRITE( AK5558_POWERMANAGEMENT2, 0b00000101 );
  // 8-to-2 mode
  else if( Settings.adcsum == 2 )
    AK5558_REGWRITE( AK5558_POWERMANAGEMENT2, 0b00000011 );
  // 8-to-1 mode
  else if( Settings.adcsum == 3 )
    AK5558_REGWRITE( AK5558_POWERMANAGEMENT2, 0b00000111 );
  // fallback to normal operation
  else
    AK5558_REGWRITE( AK5558_POWERMANAGEMENT2, 0b00000001 );
}

