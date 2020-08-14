#ifndef _ADAU1452_H_
#define _ADAU1452_H_

#include <Wire.h>

/*!
 */
void ADAU1452_WRITE_REGISTER( uint16_t reg, byte msb, byte lsb );

/*!
 */
void ADAU1452_WRITE_BLOCK( uint16_t regaddr, byte val[], uint16_t len );

/*! Sets a new input selection on DSP.
 */
void setInput( const int idx );

/*! Sets the ir for a fir block on DSP.
 */
void setFir( int idx );

/*! Enables or disables the volume potentiometer
 */
void enableVolPot( void );

/*! Sets the value for master volume on DSP.
 */
void setMasterVolume( void );

/*! Sets the values for a crossover block on DSP.
 */
void setCrossover( int idx );

/*! Sets the values for a gain block on DSP.
 */
void setGain( int idx );

/*! Sets the values for a delay block on DSP.
 */
void setDelay( int idx );

/*! Sets the values for a phase block on DSP.
 */
void setPhase( int idx );

/*! Sets the values for a highpass block on DSP.
 */
void setHighPass( int idx );

/*! Sets the values for a low pass block on DSP.
 */
void setLowPass( int idx );

/*! Sets the values for a low shelving block on DSP.
 */
void setLowShelving( int idx );

/*! Sets the values for a high shelving block on DSP.
 */
void setHighShelving( int idx );

/*! Sets the values for a peq block on DSP.
 */
void setPEQ( int idx );

/*! Changes the routing for the SPDIF output
 */
void setSpdifOutputRouting( void );

/*! Uploads the user parameters from ESP32 SPI flash to DSP.
 */
void uploadUserParams( void );

#endif
