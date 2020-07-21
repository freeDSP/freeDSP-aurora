#ifndef ROTARYENCODER_H_
#define ROTARYENCODER_H_

class RotaryEncoder
{
public:
  RotaryEncoder( void );
  ~RotaryEncoder( void ) {}

  long int getRotationValue( void ) { return value; }

  void setRotationValue( long int val ) { value = val; }

  long int getSwitchValue( void ) { return sw; }

  void setSwitchValue( long int val ) { sw = val; }

  uint8_t getCurrentState( void ) { return state; }

  void setCurrentState( uint8_t s ) { state = s; }

  void init( void );

private:
  long int value;
  long int sw;
  uint8_t state;
};

extern RotaryEncoder rotaryEncoder;

#endif
