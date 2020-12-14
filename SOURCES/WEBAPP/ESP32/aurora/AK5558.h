/*
 * ak5558.h
 *
 *  Created on: 04.10.2018
 *      Author: rkn
 */

#ifndef AK5558_H_
#define AK5558_H_

// Register Addresses
#define AK5558_POWERMANAGEMENT1     (0x00)
#define AK5558_POWERMANAGEMENT2     (0x01)
#define AK5558_CONTROL1             (0x02)
#define AK5558_CONTROL2             (0x03)
#define AK5558_CONTROL3             (0x04)
#define AK5558_DSD                  (0x05)
#define AK5558_TEST1                (0x06)
#define AK5558_TEST2                (0x07)

/*! Configure AK5558 ADC
 */
void configADC( void );

/*! Change the channel summation of AK5558 ADC
 */
void changeChannelSummationADC( void );

#endif /* AK5558_H_ */
