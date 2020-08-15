/*
 * AK4118.h
 * Implements a software driver for the AK41818 transceiver chip.
 *
 *  Created on: 15.08.2020
 *  Author: Raphael Knoop
 */

#ifndef AK4118_H_
#define AK4118_H_

// Register Addresses
#define AK4118_CLK_PDN                    (0x00)
#define AK4118_FORMAT                     (0x01)
#define AK4118_IOCONTROL0                 (0x02)
#define AK4118_IOCONTROL1                 (0x03)
#define AK4118_INT0_MASK                  (0x04)
#define AK4118_INT1_MASK                  (0x05)
#define AK4118_RECEIVER_STATUS0           (0x06)
#define AK4118_RECEIVER_STATUS1           (0x07)
#define AK4118_RX_CHANNEL_STATUS_BYTE0    (0x08)
#define AK4118_RX_CHANNEL_STATUS_BYTE1    (0x09)
#define AK4118_RX_CHANNEL_STATUS_BYTE2    (0x0A)
#define AK4118_RX_CHANNEL_STATUS_BYTE3    (0x0B)
#define AK4118_RX_CHANNEL_STATUS_BYTE4    (0x0C)
#define AK4118_TX_CHANNEL_STATUS_BYTE0    (0x0D)
#define AK4118_TX_CHANNEL_STATUS_BYTE1    (0x0E)
#define AK4118_TX_CHANNEL_STATUS_BYTE2    (0x0F)
#define AK4118_TX_CHANNEL_STATUS_BYTE3    (0x10)
#define AK4118_TX_CHANNEL_STATUS_BYTE4    (0x11)
#define AK4118_TX_BURST_PREAMBLE_PC_BYTE0 (0x12)
#define AK4118_TX_BURST_PREAMBLE_PC_BYTE1 (0x13)
#define AK4118_TX_BURST_PREAMBLE_PD_BYTE0 (0x14)
#define AK4118_TX_BURST_PREAMBLE_PD_BYTE1 (0x15)
#define AK4118_Q_SUBCODE_ADDRESS_CONTROL  (0x16)
#define AK4118_Q_SUBCODE_TRACK            (0x17)
#define AK4118_Q_SUBCODE_INDEX            (0x18)
#define AK4118_Q_SUBCODE_MINUTE           (0x19)
#define AK4118_Q_SUBCODE_SECOND           (0x1A)
#define AK4118_Q_SUBCODE_FRAME            (0x1B)
#define AK4118_Q_SUBCODE_ZERO             (0x1C)
#define AK4118_Q_SUBCODE_ABS_MINUTE       (0x1D)
#define AK4118_Q_SUBCODE_ABS_SECOND       (0x1E)
#define AK4118_Q_SUBCODE_ABS_FRAME        (0x1F)
#define AK4118_GPE                        (0x20)
#define AK4118_GPDR                       (0x21)
#define AK4118_GPSCR                      (0x22)
#define AK4118_GPLR                       (0x23)
#define AK4118_DAT_MASK_DTS_DETECT        (0x24)
#define AK4118_RX_DETECT                  (0x25)
#define AK4118_STC_DAT_DETECT             (0x26)
#define AK4118_RX_CHANNEL_STATUS_BYTE5    (0x27)
#define AK4118_TX_CHANNEL_STATUS_BYTE5    (0x28)

class AK4118
{  
public:

  //============================================================================
  /*! Contructor
   *  \param addr Address of AK4118 on I2C bus.
   */
  AK4118(byte addr)
  {
    i2cAddr = addr;
  }

  //============================================================================
  /*! Writes a value to a register of AK4118.
   *  \param reg Address of register.
   *  \param val New value of register.
   */
  void write(byte reg, byte val)
  { 
    Wire.beginTransmission(i2cAddr);
    Wire.write(reg);
    Wire.write(val);
    Wire.endTransmission(true);
  }

  //============================================================================
  /*! Reads a value form a register of AK4118
   *  \param reg Address of register to be read.
   */
  byte read(byte reg)
  { 
    Wire.beginTransmission(i2cAddr);
    Wire.write(reg);
    Wire.endTransmission(false);
    Wire.requestFrom((int)i2cAddr, 1, (int)true); 
    byte val = Wire.read();
    return val;
  }




private:
  byte i2cAddr;    // Address of the AK4118 on the I2C bus


};

#endif