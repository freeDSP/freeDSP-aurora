/*
 * ak4458.h
 *
 *  Created on: 16.06.2018
 *      Author: rkn
 */

#ifndef AK4458_H_
#define AK4458_H_

// Register Addresses
#define AK4458_CONTROL1     (0x00)
#define AK4458_CONTROL2     (0x01)
#define AK4458_CONTROL3     (0x02)
#define AK4458_L1CHATT      (0x03)
#define AK4458_R1CHATT      (0x04)
#define AK4458_CONTROL4     (0x05)
#define AK4458_DSD1         (0x06)
#define AK4458_CONTROL5     (0x07)
#define AK4458_SOUNDCONTROL (0x08)
#define AK4458_DSD2         (0x09)
#define AK4458_CONTROL6     (0x0A)
#define AK4458_CONTROL7     (0x0B)
#define AK4458_CONTROL8     (0x0C)
#define AK4458_CONTROL9     (0x0D)
#define AK4458_CONTROL10    (0x0E)
#define AK4458_L2CHATT      (0x0F)
#define AK4458_R2CHATT      (0x10)
#define AK4458_L3CHATT      (0x11)
#define AK4458_R3CHATT      (0x12)
#define AK4458_L4CHATT      (0x13)
#define AK4458_R4CHATT      (0x14)

/*!
 */
void AK4458_REGWRITE( byte reg, byte val );

/*! Configure AK4458 DAC
 */
void configDAC( void );

/*! Set DAC into reset.
 */
void resetDAC( bool rst );

/*! Mute DAC
 */
void softMuteDAC( void );

/*! Unmute DAC
 */
void softUnmuteDAC( void );

#endif /* AK4458_H_ */
