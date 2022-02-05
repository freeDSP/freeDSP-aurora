#ifndef HWCONFIG_H_
#define HWCONFIG_H_

#include "customdefines.h"

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

#if HAVE_DISPLAY
// SH1106 I2C display controller
#define SH1106_I2C_ADDR (0x3C) // 0x78 >> 1
// SSD1309 I2C display controller
#define SSD1309_I2C_ADDR (0x3D) // 0x7A >> 1
#endif

// KY-040 rotary encoder
#if HAVE_ROTARYENCODER
#define ROTARYENCODER_PINA  21 // DT Pin
#define ROTARYENCODER_PINB  19 // CLK Pin
#define ROTARYENCODER_PINSW 18 // SW Pin
#endif

// KY-022 IR Receiver Module
#if HAVE_IRRECEIVER
#define IR_RECEIVER_PIN 5
#endif

#define APPLE_A_REMOTE_LEFT        0x10
#define APPLE_A_REMOTE_RIGHT       0xE0
#define APPLE_A_REMOTE_UP          0xD0
#define APPLE_A_REMOTE_DOWN        0xB0
#define APPLE_A_REMOTE_MENU        0x40
#define APPLE_A_REMOTE_PLAY_DOWN   0x7A
#define APPLE_A_REMOTE_PLAY_UP     0x20
#define APPLE_A_REMOTE_CENTER_DOWN 0xBA
#define APPLE_A_REMOTE_CENTER_UP   0x20

#define APPLE_B_REMOTE_LEFT        0x90
#define APPLE_B_REMOTE_RIGHT       0x60
#define APPLE_B_REMOTE_UP          0x50
#define APPLE_B_REMOTE_DOWN        0x30
#define APPLE_B_REMOTE_MENU        0xC0
#define APPLE_B_REMOTE_PLAY_DOWN   0xFA
#define APPLE_B_REMOTE_PLAY_UP     0x20
#define APPLE_B_REMOTE_CENTER_DOWN 0x3A
#define APPLE_B_REMOTE_CENTER_UP   0x20



#endif