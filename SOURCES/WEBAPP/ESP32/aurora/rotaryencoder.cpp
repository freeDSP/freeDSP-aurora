#include <Arduino.h>

#include "hwconfig.h"
#include "rotaryencoder.h"

portMUX_TYPE gpioMux = portMUX_INITIALIZER_UNLOCKED;

RotaryEncoder rotaryEncoder;

void IRAM_ATTR isrRotaryEncoderAB( void )
{
  uint8_t masked_state = rotaryEncoder.getCurrentState() & 0b00000011;

  portENTER_CRITICAL_ISR( &gpioMux );

  if( digitalRead( ROTARYENCODER_PINA ) )
    masked_state |= 0b00000100;
  if( digitalRead( ROTARYENCODER_PINB ) )
    masked_state |= 0b00001000;

  switch( masked_state )
  {
    case 0b00000000:
    case 0b00000101:
    case 0b00001010:
    case 0b00001111:
      break;

    case 0b00000001:
    case 0b00000111:
    case 0b00001000:
    case 0b00001110:
      rotaryEncoder.setRotationValue( rotaryEncoder.getRotationValue() - 1 );
      break;

    case 0b00000010:
    case 0b00000100:
    case 0b00001011:
    case 0b00001101:
      rotaryEncoder.setRotationValue( rotaryEncoder.getRotationValue() + 1 );
      break;

    case 0b00000011:
    case 0b00001100:
      rotaryEncoder.setRotationValue( rotaryEncoder.getRotationValue() - 2 );
      break;

    default:
      rotaryEncoder.setRotationValue( rotaryEncoder.getRotationValue() + 2 );
      break;
  }

  rotaryEncoder.setCurrentState( masked_state >> 2 );
  portEXIT_CRITICAL_ISR( &gpioMux );
}

void IRAM_ATTR isrRotaryEncoderSwitch()
{
 portENTER_CRITICAL_ISR( &gpioMux );
 if( digitalRead( ROTARYENCODER_PINSW ) )
   rotaryEncoder.setSwitchValue( rotaryEncoder.getSwitchValue() + 1 );
 portEXIT_CRITICAL_ISR( &gpioMux );
}

RotaryEncoder::RotaryEncoder( void )
{

}

void RotaryEncoder::init( void )
{
  value = 0;
  sw = 0;
  state = 2;

  pinMode( ROTARYENCODER_PINA, INPUT_PULLUP );
  pinMode( ROTARYENCODER_PINB, INPUT_PULLUP );
  pinMode( ROTARYENCODER_PINSW, INPUT_PULLUP );

  attachInterrupt( ROTARYENCODER_PINA, isrRotaryEncoderAB, CHANGE );
  attachInterrupt( ROTARYENCODER_PINB, isrRotaryEncoderAB, CHANGE );
  attachInterrupt( ROTARYENCODER_PINSW, isrRotaryEncoderSwitch, CHANGE );
}
