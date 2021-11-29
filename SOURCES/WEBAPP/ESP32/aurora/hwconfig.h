#ifndef HWCONFIG_H_
#define HWCONFIG_H_

// Defines the GPIO for SW-I2C
#define I2C_SDA_PIN 17
#define I2C_SCL_PIN 16

// The I2C addresses that are in use
// DSP address on I2C bus
#define DSP_ADDR           (0x70>>1)
// ADC address on I2C bus
#define AK5558_I2C_ADDR    (0x22>>1)
// DAC address on I2C bus
#define AK4458_I2C_ADDR    (0x20>>1)
// S/P-DIF-Mux on AddOnA
#define ADDONA_SPDIFMUX_ADDR (0x82>>1)
// S/P-DIF-Mux on AddOnB
#define ADDONB_SPDIFMUX_ADDR (0x82>>1)

#define HAVE_DISPLAY (1)
// SH1106 I2C display controller
#define SH1106_I2C_ADDR (0x3C) // 0x78 >> 1
// SSD1309 I2C display controller
#define SSD1309_I2C_ADDR (0x3D) // 0x7A >> 1

// KY-040 rotary encoder
#define HAVE_ROTARYENCODER (1)  // Enable Rotary Encoder
#define ROTARYENCODER_PINA  21 // DT Pin
#define ROTARYENCODER_PINB  19 // CLK Pin
#define ROTARYENCODER_PINSW 18 // SW Pin

// KY-022 IR Receiver Module
#define HAVE_IRRECEIVER (1)
#define IR_RECEIVER_PIN 5

#define APPLE_REMOTE_UP          0x77E1D055
#define APPLE_REMOTE_DOWN        0x77E1B055
#define APPLE_REMOTE_LEFT        0x77E11055
#define APPLE_REMOTE_RIGHT       0x77E1E055
#define APPLE_REMOTE_CENTER_DOWN 0x77E1BA55
#define APPLE_REMOTE_CENTER_UP   0x77E12055
#define APPLE_REMOTE_MENU        0x77E14055
#define APPLE_REMOTE_PLAY_DOWN   0x77E17A55
#define APPLE_REMOTE_PLAY_UP     0x77E12055
#define REMOTE_REPEAT_CODE       0xFFFFFFFF


#endif