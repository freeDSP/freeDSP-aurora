/*
 * File:           Z:\Documents\freeDSP\freeDSP-aurora\SOURCES\SIGMASTUDIO\4FIRs\4FIRs_IC_1_REG.h
 *
 * Created:        Monday, July 20, 2020 11:41:02 AM
 * Description:    4FIRs:IC 1 control register definitions.
 *
 * This software is distributed in the hope that it will be useful,
 * but is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
 * CONDITIONS OF ANY KIND, without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 * This software may only be used to program products purchased from
 * Analog Devices for incorporation by you into audio products that
 * are intended for resale to audio product end users. This software
 * may not be distributed whole or in any part to third parties.
 *
 * Copyright ©2020 Analog Devices, Inc. All rights reserved.
 */
#ifndef __4FIRS_IC_1_REG_H__
#define __4FIRS_IC_1_REG_H__


/* PLL_CTRL0  - Registers (IC 1) */
#define REG_PLL_CTRL0_IC_1_ADDR                   0xF000
#define REG_PLL_CTRL0_IC_1_BYTE                   2
#define REG_PLL_CTRL0_IC_1_VALUE                  0x60

/* PLL_CTRL1  - Registers (IC 1) */
#define REG_PLL_CTRL1_IC_1_ADDR                   0xF001
#define REG_PLL_CTRL1_IC_1_BYTE                   2
#define REG_PLL_CTRL1_IC_1_VALUE                  0x3

/* PLL_CLK_SRC  - Registers (IC 1) */
#define REG_PLL_CLK_SRC_IC_1_ADDR                 0xF002
#define REG_PLL_CLK_SRC_IC_1_BYTE                 2
#define REG_PLL_CLK_SRC_IC_1_VALUE                0x1

/* PLL_ENABLE  - Registers (IC 1) */
#define REG_PLL_ENABLE_IC_1_ADDR                  0xF003
#define REG_PLL_ENABLE_IC_1_BYTE                  2
#define REG_PLL_ENABLE_IC_1_VALUE                 0x1

/* PLL_LOCK  - Registers (IC 1) */
#define REG_PLL_LOCK_IC_1_ADDR                    0xF004
#define REG_PLL_LOCK_IC_1_BYTE                    0
#define REG_PLL_LOCK_IC_1_VALUE                   0x1

/* MCLK_OUT  - Registers (IC 1) */
#define REG_MCLK_OUT_IC_1_ADDR                    0xF005
#define REG_MCLK_OUT_IC_1_BYTE                    2
#define REG_MCLK_OUT_IC_1_VALUE                   0x7

/* PLL_WATCHDOG  - Registers (IC 1) */
#define REG_PLL_WATCHDOG_IC_1_ADDR                0xF006
#define REG_PLL_WATCHDOG_IC_1_BYTE                2
#define REG_PLL_WATCHDOG_IC_1_VALUE               0x1

/* CLK_GEN1_M  - Registers (IC 1) */
#define REG_CLK_GEN1_M_IC_1_ADDR                  0xF020
#define REG_CLK_GEN1_M_IC_1_BYTE                  2
#define REG_CLK_GEN1_M_IC_1_VALUE                 0x6

/* CLK_GEN1_N  - Registers (IC 1) */
#define REG_CLK_GEN1_N_IC_1_ADDR                  0xF021
#define REG_CLK_GEN1_N_IC_1_BYTE                  2
#define REG_CLK_GEN1_N_IC_1_VALUE                 0x1

/* CLK_GEN2_M  - Registers (IC 1) */
#define REG_CLK_GEN2_M_IC_1_ADDR                  0xF022
#define REG_CLK_GEN2_M_IC_1_BYTE                  2
#define REG_CLK_GEN2_M_IC_1_VALUE                 0x9

/* CLK_GEN2_N  - Registers (IC 1) */
#define REG_CLK_GEN2_N_IC_1_ADDR                  0xF023
#define REG_CLK_GEN2_N_IC_1_BYTE                  2
#define REG_CLK_GEN2_N_IC_1_VALUE                 0x1

/* CLK_GEN3_M  - Registers (IC 1) */
#define REG_CLK_GEN3_M_IC_1_ADDR                  0xF024
#define REG_CLK_GEN3_M_IC_1_BYTE                  2
#define REG_CLK_GEN3_M_IC_1_VALUE                 0x0

/* CLK_GEN3_N  - Registers (IC 1) */
#define REG_CLK_GEN3_N_IC_1_ADDR                  0xF025
#define REG_CLK_GEN3_N_IC_1_BYTE                  2
#define REG_CLK_GEN3_N_IC_1_VALUE                 0x0

/* CLK_GEN3_SRC  - Registers (IC 1) */
#define REG_CLK_GEN3_SRC_IC_1_ADDR                0xF026
#define REG_CLK_GEN3_SRC_IC_1_BYTE                2
#define REG_CLK_GEN3_SRC_IC_1_VALUE               0xE

/* CLK_GEN3_LOCK  - Registers (IC 1) */
#define REG_CLK_GEN3_LOCK_IC_1_ADDR               0xF027
#define REG_CLK_GEN3_LOCK_IC_1_BYTE               0
#define REG_CLK_GEN3_LOCK_IC_1_VALUE              0x1

/* POWER_ENABLE0  - Registers (IC 1) */
#define REG_POWER_ENABLE0_IC_1_ADDR               0xF050
#define REG_POWER_ENABLE0_IC_1_BYTE               2
#define REG_POWER_ENABLE0_IC_1_VALUE              0x5FF

/* POWER_ENABLE1  - Registers (IC 1) */
#define REG_POWER_ENABLE1_IC_1_ADDR               0xF051
#define REG_POWER_ENABLE1_IC_1_BYTE               2
#define REG_POWER_ENABLE1_IC_1_VALUE              0x7

/* ASRC_INPUT0  - Registers (IC 1) */
#define REG_ASRC_INPUT0_IC_1_ADDR                 0xF100
#define REG_ASRC_INPUT0_IC_1_BYTE                 2
#define REG_ASRC_INPUT0_IC_1_VALUE                0x3

/* ASRC_INPUT1  - Registers (IC 1) */
#define REG_ASRC_INPUT1_IC_1_ADDR                 0xF101
#define REG_ASRC_INPUT1_IC_1_BYTE                 2
#define REG_ASRC_INPUT1_IC_1_VALUE                0x0

/* ASRC_INPUT2  - Registers (IC 1) */
#define REG_ASRC_INPUT2_IC_1_ADDR                 0xF102
#define REG_ASRC_INPUT2_IC_1_BYTE                 2
#define REG_ASRC_INPUT2_IC_1_VALUE                0x0

/* ASRC_INPUT3  - Registers (IC 1) */
#define REG_ASRC_INPUT3_IC_1_ADDR                 0xF103
#define REG_ASRC_INPUT3_IC_1_BYTE                 2
#define REG_ASRC_INPUT3_IC_1_VALUE                0x0

/* ASRC_INPUT4  - Registers (IC 1) */
#define REG_ASRC_INPUT4_IC_1_ADDR                 0xF104
#define REG_ASRC_INPUT4_IC_1_BYTE                 2
#define REG_ASRC_INPUT4_IC_1_VALUE                0x0

/* ASRC_INPUT5  - Registers (IC 1) */
#define REG_ASRC_INPUT5_IC_1_ADDR                 0xF105
#define REG_ASRC_INPUT5_IC_1_BYTE                 2
#define REG_ASRC_INPUT5_IC_1_VALUE                0x0

/* ASRC_INPUT6  - Registers (IC 1) */
#define REG_ASRC_INPUT6_IC_1_ADDR                 0xF106
#define REG_ASRC_INPUT6_IC_1_BYTE                 2
#define REG_ASRC_INPUT6_IC_1_VALUE                0x0

/* ASRC_INPUT7  - Registers (IC 1) */
#define REG_ASRC_INPUT7_IC_1_ADDR                 0xF107
#define REG_ASRC_INPUT7_IC_1_BYTE                 2
#define REG_ASRC_INPUT7_IC_1_VALUE                0x0

/* ASRC_OUT_RATE0  - Registers (IC 1) */
#define REG_ASRC_OUT_RATE0_IC_1_ADDR              0xF140
#define REG_ASRC_OUT_RATE0_IC_1_BYTE              2
#define REG_ASRC_OUT_RATE0_IC_1_VALUE             0x6

/* ASRC_OUT_RATE1  - Registers (IC 1) */
#define REG_ASRC_OUT_RATE1_IC_1_ADDR              0xF141
#define REG_ASRC_OUT_RATE1_IC_1_BYTE              2
#define REG_ASRC_OUT_RATE1_IC_1_VALUE             0x0

/* ASRC_OUT_RATE2  - Registers (IC 1) */
#define REG_ASRC_OUT_RATE2_IC_1_ADDR              0xF142
#define REG_ASRC_OUT_RATE2_IC_1_BYTE              2
#define REG_ASRC_OUT_RATE2_IC_1_VALUE             0x0

/* ASRC_OUT_RATE3  - Registers (IC 1) */
#define REG_ASRC_OUT_RATE3_IC_1_ADDR              0xF143
#define REG_ASRC_OUT_RATE3_IC_1_BYTE              2
#define REG_ASRC_OUT_RATE3_IC_1_VALUE             0x0

/* ASRC_OUT_RATE4  - Registers (IC 1) */
#define REG_ASRC_OUT_RATE4_IC_1_ADDR              0xF144
#define REG_ASRC_OUT_RATE4_IC_1_BYTE              2
#define REG_ASRC_OUT_RATE4_IC_1_VALUE             0x0

/* ASRC_OUT_RATE5  - Registers (IC 1) */
#define REG_ASRC_OUT_RATE5_IC_1_ADDR              0xF145
#define REG_ASRC_OUT_RATE5_IC_1_BYTE              2
#define REG_ASRC_OUT_RATE5_IC_1_VALUE             0x0

/* ASRC_OUT_RATE6  - Registers (IC 1) */
#define REG_ASRC_OUT_RATE6_IC_1_ADDR              0xF146
#define REG_ASRC_OUT_RATE6_IC_1_BYTE              2
#define REG_ASRC_OUT_RATE6_IC_1_VALUE             0x0

/* ASRC_OUT_RATE7  - Registers (IC 1) */
#define REG_ASRC_OUT_RATE7_IC_1_ADDR              0xF147
#define REG_ASRC_OUT_RATE7_IC_1_BYTE              2
#define REG_ASRC_OUT_RATE7_IC_1_VALUE             0x0

/* SOUT_SOURCE0  - Registers (IC 1) */
#define REG_SOUT_SOURCE0_IC_1_ADDR                0xF180
#define REG_SOUT_SOURCE0_IC_1_BYTE                2
#define REG_SOUT_SOURCE0_IC_1_VALUE               0x2

/* SOUT_SOURCE1  - Registers (IC 1) */
#define REG_SOUT_SOURCE1_IC_1_ADDR                0xF181
#define REG_SOUT_SOURCE1_IC_1_BYTE                2
#define REG_SOUT_SOURCE1_IC_1_VALUE               0x2

/* SOUT_SOURCE2  - Registers (IC 1) */
#define REG_SOUT_SOURCE2_IC_1_ADDR                0xF182
#define REG_SOUT_SOURCE2_IC_1_BYTE                2
#define REG_SOUT_SOURCE2_IC_1_VALUE               0x2

/* SOUT_SOURCE3  - Registers (IC 1) */
#define REG_SOUT_SOURCE3_IC_1_ADDR                0xF183
#define REG_SOUT_SOURCE3_IC_1_BYTE                2
#define REG_SOUT_SOURCE3_IC_1_VALUE               0x2

/* SOUT_SOURCE4  - Registers (IC 1) */
#define REG_SOUT_SOURCE4_IC_1_ADDR                0xF184
#define REG_SOUT_SOURCE4_IC_1_BYTE                2
#define REG_SOUT_SOURCE4_IC_1_VALUE               0x2

/* SOUT_SOURCE5  - Registers (IC 1) */
#define REG_SOUT_SOURCE5_IC_1_ADDR                0xF185
#define REG_SOUT_SOURCE5_IC_1_BYTE                2
#define REG_SOUT_SOURCE5_IC_1_VALUE               0x2

/* SOUT_SOURCE6  - Registers (IC 1) */
#define REG_SOUT_SOURCE6_IC_1_ADDR                0xF186
#define REG_SOUT_SOURCE6_IC_1_BYTE                2
#define REG_SOUT_SOURCE6_IC_1_VALUE               0x2

/* SOUT_SOURCE7  - Registers (IC 1) */
#define REG_SOUT_SOURCE7_IC_1_ADDR                0xF187
#define REG_SOUT_SOURCE7_IC_1_BYTE                2
#define REG_SOUT_SOURCE7_IC_1_VALUE               0x2

/* SOUT_SOURCE8  - Registers (IC 1) */
#define REG_SOUT_SOURCE8_IC_1_ADDR                0xF188
#define REG_SOUT_SOURCE8_IC_1_BYTE                2
#define REG_SOUT_SOURCE8_IC_1_VALUE               0x2A

/* SOUT_SOURCE9  - Registers (IC 1) */
#define REG_SOUT_SOURCE9_IC_1_ADDR                0xF189
#define REG_SOUT_SOURCE9_IC_1_BYTE                2
#define REG_SOUT_SOURCE9_IC_1_VALUE               0x2

/* SOUT_SOURCE10  - Registers (IC 1) */
#define REG_SOUT_SOURCE10_IC_1_ADDR               0xF18A
#define REG_SOUT_SOURCE10_IC_1_BYTE               2
#define REG_SOUT_SOURCE10_IC_1_VALUE              0x2

/* SOUT_SOURCE11  - Registers (IC 1) */
#define REG_SOUT_SOURCE11_IC_1_ADDR               0xF18B
#define REG_SOUT_SOURCE11_IC_1_BYTE               2
#define REG_SOUT_SOURCE11_IC_1_VALUE              0x2

/* SOUT_SOURCE12  - Registers (IC 1) */
#define REG_SOUT_SOURCE12_IC_1_ADDR               0xF18C
#define REG_SOUT_SOURCE12_IC_1_BYTE               2
#define REG_SOUT_SOURCE12_IC_1_VALUE              0x2

/* SOUT_SOURCE13  - Registers (IC 1) */
#define REG_SOUT_SOURCE13_IC_1_ADDR               0xF18D
#define REG_SOUT_SOURCE13_IC_1_BYTE               2
#define REG_SOUT_SOURCE13_IC_1_VALUE              0x2

/* SOUT_SOURCE14  - Registers (IC 1) */
#define REG_SOUT_SOURCE14_IC_1_ADDR               0xF18E
#define REG_SOUT_SOURCE14_IC_1_BYTE               2
#define REG_SOUT_SOURCE14_IC_1_VALUE              0x2

/* SOUT_SOURCE15  - Registers (IC 1) */
#define REG_SOUT_SOURCE15_IC_1_ADDR               0xF18F
#define REG_SOUT_SOURCE15_IC_1_BYTE               2
#define REG_SOUT_SOURCE15_IC_1_VALUE              0x2

/* SOUT_SOURCE16  - Registers (IC 1) */
#define REG_SOUT_SOURCE16_IC_1_ADDR               0xF190
#define REG_SOUT_SOURCE16_IC_1_BYTE               2
#define REG_SOUT_SOURCE16_IC_1_VALUE              0x0

/* SOUT_SOURCE17  - Registers (IC 1) */
#define REG_SOUT_SOURCE17_IC_1_ADDR               0xF191
#define REG_SOUT_SOURCE17_IC_1_BYTE               2
#define REG_SOUT_SOURCE17_IC_1_VALUE              0x0

/* SOUT_SOURCE18  - Registers (IC 1) */
#define REG_SOUT_SOURCE18_IC_1_ADDR               0xF192
#define REG_SOUT_SOURCE18_IC_1_BYTE               2
#define REG_SOUT_SOURCE18_IC_1_VALUE              0x0

/* SOUT_SOURCE19  - Registers (IC 1) */
#define REG_SOUT_SOURCE19_IC_1_ADDR               0xF193
#define REG_SOUT_SOURCE19_IC_1_BYTE               2
#define REG_SOUT_SOURCE19_IC_1_VALUE              0x0

/* SOUT_SOURCE20  - Registers (IC 1) */
#define REG_SOUT_SOURCE20_IC_1_ADDR               0xF194
#define REG_SOUT_SOURCE20_IC_1_BYTE               2
#define REG_SOUT_SOURCE20_IC_1_VALUE              0x0

/* SOUT_SOURCE21  - Registers (IC 1) */
#define REG_SOUT_SOURCE21_IC_1_ADDR               0xF195
#define REG_SOUT_SOURCE21_IC_1_BYTE               2
#define REG_SOUT_SOURCE21_IC_1_VALUE              0x0

/* SOUT_SOURCE22  - Registers (IC 1) */
#define REG_SOUT_SOURCE22_IC_1_ADDR               0xF196
#define REG_SOUT_SOURCE22_IC_1_BYTE               2
#define REG_SOUT_SOURCE22_IC_1_VALUE              0x0

/* SOUT_SOURCE23  - Registers (IC 1) */
#define REG_SOUT_SOURCE23_IC_1_ADDR               0xF197
#define REG_SOUT_SOURCE23_IC_1_BYTE               2
#define REG_SOUT_SOURCE23_IC_1_VALUE              0x0

/* SPDIFTX_INPUT  - Registers (IC 1) */
#define REG_SPDIFTX_INPUT_IC_1_ADDR               0xF1C0
#define REG_SPDIFTX_INPUT_IC_1_BYTE               2
#define REG_SPDIFTX_INPUT_IC_1_VALUE              0x1

/* SERIAL_BYTE_0_0  - Registers (IC 1) */
#define REG_SERIAL_BYTE_0_0_IC_1_ADDR             0xF200
#define REG_SERIAL_BYTE_0_0_IC_1_BYTE             2
#define REG_SERIAL_BYTE_0_0_IC_1_VALUE            0x93CA

/* SERIAL_BYTE_0_1  - Registers (IC 1) */
#define REG_SERIAL_BYTE_0_1_IC_1_ADDR             0xF201
#define REG_SERIAL_BYTE_0_1_IC_1_BYTE             2
#define REG_SERIAL_BYTE_0_1_IC_1_VALUE            0x2

/* SERIAL_BYTE_1_0  - Registers (IC 1) */
#define REG_SERIAL_BYTE_1_0_IC_1_ADDR             0xF204
#define REG_SERIAL_BYTE_1_0_IC_1_BYTE             2
#define REG_SERIAL_BYTE_1_0_IC_1_VALUE            0x260A

/* SERIAL_BYTE_1_1  - Registers (IC 1) */
#define REG_SERIAL_BYTE_1_1_IC_1_ADDR             0xF205
#define REG_SERIAL_BYTE_1_1_IC_1_BYTE             2
#define REG_SERIAL_BYTE_1_1_IC_1_VALUE            0x2

/* SERIAL_BYTE_2_0  - Registers (IC 1) */
#define REG_SERIAL_BYTE_2_0_IC_1_ADDR             0xF208
#define REG_SERIAL_BYTE_2_0_IC_1_BYTE             2
#define REG_SERIAL_BYTE_2_0_IC_1_VALUE            0x93CA

/* SERIAL_BYTE_2_1  - Registers (IC 1) */
#define REG_SERIAL_BYTE_2_1_IC_1_ADDR             0xF209
#define REG_SERIAL_BYTE_2_1_IC_1_BYTE             2
#define REG_SERIAL_BYTE_2_1_IC_1_VALUE            0x2

/* SERIAL_BYTE_3_0  - Registers (IC 1) */
#define REG_SERIAL_BYTE_3_0_IC_1_ADDR             0xF20C
#define REG_SERIAL_BYTE_3_0_IC_1_BYTE             2
#define REG_SERIAL_BYTE_3_0_IC_1_VALUE            0x93CA

/* SERIAL_BYTE_3_1  - Registers (IC 1) */
#define REG_SERIAL_BYTE_3_1_IC_1_ADDR             0xF20D
#define REG_SERIAL_BYTE_3_1_IC_1_BYTE             2
#define REG_SERIAL_BYTE_3_1_IC_1_VALUE            0x2

/* SERIAL_BYTE_4_0  - Registers (IC 1) */
#define REG_SERIAL_BYTE_4_0_IC_1_ADDR             0xF210
#define REG_SERIAL_BYTE_4_0_IC_1_BYTE             2
#define REG_SERIAL_BYTE_4_0_IC_1_VALUE            0x93CA

/* SERIAL_BYTE_4_1  - Registers (IC 1) */
#define REG_SERIAL_BYTE_4_1_IC_1_ADDR             0xF211
#define REG_SERIAL_BYTE_4_1_IC_1_BYTE             2
#define REG_SERIAL_BYTE_4_1_IC_1_VALUE            0x2

/* SERIAL_BYTE_5_0  - Registers (IC 1) */
#define REG_SERIAL_BYTE_5_0_IC_1_ADDR             0xF214
#define REG_SERIAL_BYTE_5_0_IC_1_BYTE             2
#define REG_SERIAL_BYTE_5_0_IC_1_VALUE            0x260A

/* SERIAL_BYTE_5_1  - Registers (IC 1) */
#define REG_SERIAL_BYTE_5_1_IC_1_ADDR             0xF215
#define REG_SERIAL_BYTE_5_1_IC_1_BYTE             2
#define REG_SERIAL_BYTE_5_1_IC_1_VALUE            0x2

/* SERIAL_BYTE_6_0  - Registers (IC 1) */
#define REG_SERIAL_BYTE_6_0_IC_1_ADDR             0xF218
#define REG_SERIAL_BYTE_6_0_IC_1_BYTE             2
#define REG_SERIAL_BYTE_6_0_IC_1_VALUE            0x0

/* SERIAL_BYTE_6_1  - Registers (IC 1) */
#define REG_SERIAL_BYTE_6_1_IC_1_ADDR             0xF219
#define REG_SERIAL_BYTE_6_1_IC_1_BYTE             2
#define REG_SERIAL_BYTE_6_1_IC_1_VALUE            0x2

/* SERIAL_BYTE_7_0  - Registers (IC 1) */
#define REG_SERIAL_BYTE_7_0_IC_1_ADDR             0xF21C
#define REG_SERIAL_BYTE_7_0_IC_1_BYTE             2
#define REG_SERIAL_BYTE_7_0_IC_1_VALUE            0x0

/* SERIAL_BYTE_7_1  - Registers (IC 1) */
#define REG_SERIAL_BYTE_7_1_IC_1_ADDR             0xF21D
#define REG_SERIAL_BYTE_7_1_IC_1_BYTE             2
#define REG_SERIAL_BYTE_7_1_IC_1_VALUE            0x2

/* FTDM_IN0  - Registers (IC 1) */
#define REG_FTDM_IN0_IC_1_ADDR                    0xF300
#define REG_FTDM_IN0_IC_1_BYTE                    2
#define REG_FTDM_IN0_IC_1_VALUE                   0x0

/* FTDM_IN1  - Registers (IC 1) */
#define REG_FTDM_IN1_IC_1_ADDR                    0xF301
#define REG_FTDM_IN1_IC_1_BYTE                    2
#define REG_FTDM_IN1_IC_1_VALUE                   0x0

/* FTDM_IN2  - Registers (IC 1) */
#define REG_FTDM_IN2_IC_1_ADDR                    0xF302
#define REG_FTDM_IN2_IC_1_BYTE                    2
#define REG_FTDM_IN2_IC_1_VALUE                   0x0

/* FTDM_IN3  - Registers (IC 1) */
#define REG_FTDM_IN3_IC_1_ADDR                    0xF303
#define REG_FTDM_IN3_IC_1_BYTE                    2
#define REG_FTDM_IN3_IC_1_VALUE                   0x0

/* FTDM_IN4  - Registers (IC 1) */
#define REG_FTDM_IN4_IC_1_ADDR                    0xF304
#define REG_FTDM_IN4_IC_1_BYTE                    2
#define REG_FTDM_IN4_IC_1_VALUE                   0x0

/* FTDM_IN5  - Registers (IC 1) */
#define REG_FTDM_IN5_IC_1_ADDR                    0xF305
#define REG_FTDM_IN5_IC_1_BYTE                    2
#define REG_FTDM_IN5_IC_1_VALUE                   0x0

/* FTDM_IN6  - Registers (IC 1) */
#define REG_FTDM_IN6_IC_1_ADDR                    0xF306
#define REG_FTDM_IN6_IC_1_BYTE                    2
#define REG_FTDM_IN6_IC_1_VALUE                   0x0

/* FTDM_IN7  - Registers (IC 1) */
#define REG_FTDM_IN7_IC_1_ADDR                    0xF307
#define REG_FTDM_IN7_IC_1_BYTE                    2
#define REG_FTDM_IN7_IC_1_VALUE                   0x0

/* FTDM_IN8  - Registers (IC 1) */
#define REG_FTDM_IN8_IC_1_ADDR                    0xF308
#define REG_FTDM_IN8_IC_1_BYTE                    2
#define REG_FTDM_IN8_IC_1_VALUE                   0x0

/* FTDM_IN9  - Registers (IC 1) */
#define REG_FTDM_IN9_IC_1_ADDR                    0xF309
#define REG_FTDM_IN9_IC_1_BYTE                    2
#define REG_FTDM_IN9_IC_1_VALUE                   0x0

/* FTDM_IN10  - Registers (IC 1) */
#define REG_FTDM_IN10_IC_1_ADDR                   0xF30A
#define REG_FTDM_IN10_IC_1_BYTE                   2
#define REG_FTDM_IN10_IC_1_VALUE                  0x0

/* FTDM_IN11  - Registers (IC 1) */
#define REG_FTDM_IN11_IC_1_ADDR                   0xF30B
#define REG_FTDM_IN11_IC_1_BYTE                   2
#define REG_FTDM_IN11_IC_1_VALUE                  0x0

/* FTDM_IN12  - Registers (IC 1) */
#define REG_FTDM_IN12_IC_1_ADDR                   0xF30C
#define REG_FTDM_IN12_IC_1_BYTE                   2
#define REG_FTDM_IN12_IC_1_VALUE                  0x0

/* FTDM_IN13  - Registers (IC 1) */
#define REG_FTDM_IN13_IC_1_ADDR                   0xF30D
#define REG_FTDM_IN13_IC_1_BYTE                   2
#define REG_FTDM_IN13_IC_1_VALUE                  0x0

/* FTDM_IN14  - Registers (IC 1) */
#define REG_FTDM_IN14_IC_1_ADDR                   0xF30E
#define REG_FTDM_IN14_IC_1_BYTE                   2
#define REG_FTDM_IN14_IC_1_VALUE                  0x0

/* FTDM_IN15  - Registers (IC 1) */
#define REG_FTDM_IN15_IC_1_ADDR                   0xF30F
#define REG_FTDM_IN15_IC_1_BYTE                   2
#define REG_FTDM_IN15_IC_1_VALUE                  0x0

/* FTDM_IN16  - Registers (IC 1) */
#define REG_FTDM_IN16_IC_1_ADDR                   0xF310
#define REG_FTDM_IN16_IC_1_BYTE                   2
#define REG_FTDM_IN16_IC_1_VALUE                  0x0

/* FTDM_IN17  - Registers (IC 1) */
#define REG_FTDM_IN17_IC_1_ADDR                   0xF311
#define REG_FTDM_IN17_IC_1_BYTE                   2
#define REG_FTDM_IN17_IC_1_VALUE                  0x0

/* FTDM_IN18  - Registers (IC 1) */
#define REG_FTDM_IN18_IC_1_ADDR                   0xF312
#define REG_FTDM_IN18_IC_1_BYTE                   2
#define REG_FTDM_IN18_IC_1_VALUE                  0x0

/* FTDM_IN19  - Registers (IC 1) */
#define REG_FTDM_IN19_IC_1_ADDR                   0xF313
#define REG_FTDM_IN19_IC_1_BYTE                   2
#define REG_FTDM_IN19_IC_1_VALUE                  0x0

/* FTDM_IN20  - Registers (IC 1) */
#define REG_FTDM_IN20_IC_1_ADDR                   0xF314
#define REG_FTDM_IN20_IC_1_BYTE                   2
#define REG_FTDM_IN20_IC_1_VALUE                  0x0

/* FTDM_IN21  - Registers (IC 1) */
#define REG_FTDM_IN21_IC_1_ADDR                   0xF315
#define REG_FTDM_IN21_IC_1_BYTE                   2
#define REG_FTDM_IN21_IC_1_VALUE                  0x0

/* FTDM_IN22  - Registers (IC 1) */
#define REG_FTDM_IN22_IC_1_ADDR                   0xF316
#define REG_FTDM_IN22_IC_1_BYTE                   2
#define REG_FTDM_IN22_IC_1_VALUE                  0x0

/* FTDM_IN23  - Registers (IC 1) */
#define REG_FTDM_IN23_IC_1_ADDR                   0xF317
#define REG_FTDM_IN23_IC_1_BYTE                   2
#define REG_FTDM_IN23_IC_1_VALUE                  0x0

/* FTDM_IN24  - Registers (IC 1) */
#define REG_FTDM_IN24_IC_1_ADDR                   0xF318
#define REG_FTDM_IN24_IC_1_BYTE                   2
#define REG_FTDM_IN24_IC_1_VALUE                  0x0

/* FTDM_IN25  - Registers (IC 1) */
#define REG_FTDM_IN25_IC_1_ADDR                   0xF319
#define REG_FTDM_IN25_IC_1_BYTE                   2
#define REG_FTDM_IN25_IC_1_VALUE                  0x0

/* FTDM_IN26  - Registers (IC 1) */
#define REG_FTDM_IN26_IC_1_ADDR                   0xF31A
#define REG_FTDM_IN26_IC_1_BYTE                   2
#define REG_FTDM_IN26_IC_1_VALUE                  0x0

/* FTDM_IN27  - Registers (IC 1) */
#define REG_FTDM_IN27_IC_1_ADDR                   0xF31B
#define REG_FTDM_IN27_IC_1_BYTE                   2
#define REG_FTDM_IN27_IC_1_VALUE                  0x0

/* FTDM_IN28  - Registers (IC 1) */
#define REG_FTDM_IN28_IC_1_ADDR                   0xF31C
#define REG_FTDM_IN28_IC_1_BYTE                   2
#define REG_FTDM_IN28_IC_1_VALUE                  0x0

/* FTDM_IN29  - Registers (IC 1) */
#define REG_FTDM_IN29_IC_1_ADDR                   0xF31D
#define REG_FTDM_IN29_IC_1_BYTE                   2
#define REG_FTDM_IN29_IC_1_VALUE                  0x0

/* FTDM_IN30  - Registers (IC 1) */
#define REG_FTDM_IN30_IC_1_ADDR                   0xF31E
#define REG_FTDM_IN30_IC_1_BYTE                   2
#define REG_FTDM_IN30_IC_1_VALUE                  0x0

/* FTDM_IN31  - Registers (IC 1) */
#define REG_FTDM_IN31_IC_1_ADDR                   0xF31F
#define REG_FTDM_IN31_IC_1_BYTE                   2
#define REG_FTDM_IN31_IC_1_VALUE                  0x0

/* FTDM_IN32  - Registers (IC 1) */
#define REG_FTDM_IN32_IC_1_ADDR                   0xF320
#define REG_FTDM_IN32_IC_1_BYTE                   2
#define REG_FTDM_IN32_IC_1_VALUE                  0x0

/* FTDM_IN33  - Registers (IC 1) */
#define REG_FTDM_IN33_IC_1_ADDR                   0xF321
#define REG_FTDM_IN33_IC_1_BYTE                   2
#define REG_FTDM_IN33_IC_1_VALUE                  0x0

/* FTDM_IN34  - Registers (IC 1) */
#define REG_FTDM_IN34_IC_1_ADDR                   0xF322
#define REG_FTDM_IN34_IC_1_BYTE                   2
#define REG_FTDM_IN34_IC_1_VALUE                  0x0

/* FTDM_IN35  - Registers (IC 1) */
#define REG_FTDM_IN35_IC_1_ADDR                   0xF323
#define REG_FTDM_IN35_IC_1_BYTE                   2
#define REG_FTDM_IN35_IC_1_VALUE                  0x0

/* FTDM_IN36  - Registers (IC 1) */
#define REG_FTDM_IN36_IC_1_ADDR                   0xF324
#define REG_FTDM_IN36_IC_1_BYTE                   2
#define REG_FTDM_IN36_IC_1_VALUE                  0x0

/* FTDM_IN37  - Registers (IC 1) */
#define REG_FTDM_IN37_IC_1_ADDR                   0xF325
#define REG_FTDM_IN37_IC_1_BYTE                   2
#define REG_FTDM_IN37_IC_1_VALUE                  0x0

/* FTDM_IN38  - Registers (IC 1) */
#define REG_FTDM_IN38_IC_1_ADDR                   0xF326
#define REG_FTDM_IN38_IC_1_BYTE                   2
#define REG_FTDM_IN38_IC_1_VALUE                  0x0

/* FTDM_IN39  - Registers (IC 1) */
#define REG_FTDM_IN39_IC_1_ADDR                   0xF327
#define REG_FTDM_IN39_IC_1_BYTE                   2
#define REG_FTDM_IN39_IC_1_VALUE                  0x0

/* FTDM_IN40  - Registers (IC 1) */
#define REG_FTDM_IN40_IC_1_ADDR                   0xF328
#define REG_FTDM_IN40_IC_1_BYTE                   2
#define REG_FTDM_IN40_IC_1_VALUE                  0x0

/* FTDM_IN41  - Registers (IC 1) */
#define REG_FTDM_IN41_IC_1_ADDR                   0xF329
#define REG_FTDM_IN41_IC_1_BYTE                   2
#define REG_FTDM_IN41_IC_1_VALUE                  0x0

/* FTDM_IN42  - Registers (IC 1) */
#define REG_FTDM_IN42_IC_1_ADDR                   0xF32A
#define REG_FTDM_IN42_IC_1_BYTE                   2
#define REG_FTDM_IN42_IC_1_VALUE                  0x0

/* FTDM_IN43  - Registers (IC 1) */
#define REG_FTDM_IN43_IC_1_ADDR                   0xF32B
#define REG_FTDM_IN43_IC_1_BYTE                   2
#define REG_FTDM_IN43_IC_1_VALUE                  0x0

/* FTDM_IN44  - Registers (IC 1) */
#define REG_FTDM_IN44_IC_1_ADDR                   0xF32C
#define REG_FTDM_IN44_IC_1_BYTE                   2
#define REG_FTDM_IN44_IC_1_VALUE                  0x0

/* FTDM_IN45  - Registers (IC 1) */
#define REG_FTDM_IN45_IC_1_ADDR                   0xF32D
#define REG_FTDM_IN45_IC_1_BYTE                   2
#define REG_FTDM_IN45_IC_1_VALUE                  0x0

/* FTDM_IN46  - Registers (IC 1) */
#define REG_FTDM_IN46_IC_1_ADDR                   0xF32E
#define REG_FTDM_IN46_IC_1_BYTE                   2
#define REG_FTDM_IN46_IC_1_VALUE                  0x0

/* FTDM_IN47  - Registers (IC 1) */
#define REG_FTDM_IN47_IC_1_ADDR                   0xF32F
#define REG_FTDM_IN47_IC_1_BYTE                   2
#define REG_FTDM_IN47_IC_1_VALUE                  0x0

/* FTDM_IN48  - Registers (IC 1) */
#define REG_FTDM_IN48_IC_1_ADDR                   0xF330
#define REG_FTDM_IN48_IC_1_BYTE                   2
#define REG_FTDM_IN48_IC_1_VALUE                  0x0

/* FTDM_IN49  - Registers (IC 1) */
#define REG_FTDM_IN49_IC_1_ADDR                   0xF331
#define REG_FTDM_IN49_IC_1_BYTE                   2
#define REG_FTDM_IN49_IC_1_VALUE                  0x0

/* FTDM_IN50  - Registers (IC 1) */
#define REG_FTDM_IN50_IC_1_ADDR                   0xF332
#define REG_FTDM_IN50_IC_1_BYTE                   2
#define REG_FTDM_IN50_IC_1_VALUE                  0x0

/* FTDM_IN51  - Registers (IC 1) */
#define REG_FTDM_IN51_IC_1_ADDR                   0xF333
#define REG_FTDM_IN51_IC_1_BYTE                   2
#define REG_FTDM_IN51_IC_1_VALUE                  0x0

/* FTDM_IN52  - Registers (IC 1) */
#define REG_FTDM_IN52_IC_1_ADDR                   0xF334
#define REG_FTDM_IN52_IC_1_BYTE                   2
#define REG_FTDM_IN52_IC_1_VALUE                  0x0

/* FTDM_IN53  - Registers (IC 1) */
#define REG_FTDM_IN53_IC_1_ADDR                   0xF335
#define REG_FTDM_IN53_IC_1_BYTE                   2
#define REG_FTDM_IN53_IC_1_VALUE                  0x0

/* FTDM_IN54  - Registers (IC 1) */
#define REG_FTDM_IN54_IC_1_ADDR                   0xF336
#define REG_FTDM_IN54_IC_1_BYTE                   2
#define REG_FTDM_IN54_IC_1_VALUE                  0x0

/* FTDM_IN55  - Registers (IC 1) */
#define REG_FTDM_IN55_IC_1_ADDR                   0xF337
#define REG_FTDM_IN55_IC_1_BYTE                   2
#define REG_FTDM_IN55_IC_1_VALUE                  0x0

/* FTDM_IN56  - Registers (IC 1) */
#define REG_FTDM_IN56_IC_1_ADDR                   0xF338
#define REG_FTDM_IN56_IC_1_BYTE                   2
#define REG_FTDM_IN56_IC_1_VALUE                  0x0

/* FTDM_IN57  - Registers (IC 1) */
#define REG_FTDM_IN57_IC_1_ADDR                   0xF339
#define REG_FTDM_IN57_IC_1_BYTE                   2
#define REG_FTDM_IN57_IC_1_VALUE                  0x0

/* FTDM_IN58  - Registers (IC 1) */
#define REG_FTDM_IN58_IC_1_ADDR                   0xF33A
#define REG_FTDM_IN58_IC_1_BYTE                   2
#define REG_FTDM_IN58_IC_1_VALUE                  0x0

/* FTDM_IN59  - Registers (IC 1) */
#define REG_FTDM_IN59_IC_1_ADDR                   0xF33B
#define REG_FTDM_IN59_IC_1_BYTE                   2
#define REG_FTDM_IN59_IC_1_VALUE                  0x0

/* FTDM_IN60  - Registers (IC 1) */
#define REG_FTDM_IN60_IC_1_ADDR                   0xF33C
#define REG_FTDM_IN60_IC_1_BYTE                   2
#define REG_FTDM_IN60_IC_1_VALUE                  0x0

/* FTDM_IN61  - Registers (IC 1) */
#define REG_FTDM_IN61_IC_1_ADDR                   0xF33D
#define REG_FTDM_IN61_IC_1_BYTE                   2
#define REG_FTDM_IN61_IC_1_VALUE                  0x0

/* FTDM_IN62  - Registers (IC 1) */
#define REG_FTDM_IN62_IC_1_ADDR                   0xF33E
#define REG_FTDM_IN62_IC_1_BYTE                   2
#define REG_FTDM_IN62_IC_1_VALUE                  0x0

/* FTDM_IN63  - Registers (IC 1) */
#define REG_FTDM_IN63_IC_1_ADDR                   0xF33F
#define REG_FTDM_IN63_IC_1_BYTE                   2
#define REG_FTDM_IN63_IC_1_VALUE                  0x0

/* FTDM_OUT0  - Registers (IC 1) */
#define REG_FTDM_OUT0_IC_1_ADDR                   0xF380
#define REG_FTDM_OUT0_IC_1_BYTE                   2
#define REG_FTDM_OUT0_IC_1_VALUE                  0x0

/* FTDM_OUT1  - Registers (IC 1) */
#define REG_FTDM_OUT1_IC_1_ADDR                   0xF381
#define REG_FTDM_OUT1_IC_1_BYTE                   2
#define REG_FTDM_OUT1_IC_1_VALUE                  0x0

/* FTDM_OUT2  - Registers (IC 1) */
#define REG_FTDM_OUT2_IC_1_ADDR                   0xF382
#define REG_FTDM_OUT2_IC_1_BYTE                   2
#define REG_FTDM_OUT2_IC_1_VALUE                  0x0

/* FTDM_OUT3  - Registers (IC 1) */
#define REG_FTDM_OUT3_IC_1_ADDR                   0xF383
#define REG_FTDM_OUT3_IC_1_BYTE                   2
#define REG_FTDM_OUT3_IC_1_VALUE                  0x0

/* FTDM_OUT4  - Registers (IC 1) */
#define REG_FTDM_OUT4_IC_1_ADDR                   0xF384
#define REG_FTDM_OUT4_IC_1_BYTE                   2
#define REG_FTDM_OUT4_IC_1_VALUE                  0x0

/* FTDM_OUT5  - Registers (IC 1) */
#define REG_FTDM_OUT5_IC_1_ADDR                   0xF385
#define REG_FTDM_OUT5_IC_1_BYTE                   2
#define REG_FTDM_OUT5_IC_1_VALUE                  0x0

/* FTDM_OUT6  - Registers (IC 1) */
#define REG_FTDM_OUT6_IC_1_ADDR                   0xF386
#define REG_FTDM_OUT6_IC_1_BYTE                   2
#define REG_FTDM_OUT6_IC_1_VALUE                  0x0

/* FTDM_OUT7  - Registers (IC 1) */
#define REG_FTDM_OUT7_IC_1_ADDR                   0xF387
#define REG_FTDM_OUT7_IC_1_BYTE                   2
#define REG_FTDM_OUT7_IC_1_VALUE                  0x0

/* FTDM_OUT8  - Registers (IC 1) */
#define REG_FTDM_OUT8_IC_1_ADDR                   0xF388
#define REG_FTDM_OUT8_IC_1_BYTE                   2
#define REG_FTDM_OUT8_IC_1_VALUE                  0x0

/* FTDM_OUT9  - Registers (IC 1) */
#define REG_FTDM_OUT9_IC_1_ADDR                   0xF389
#define REG_FTDM_OUT9_IC_1_BYTE                   2
#define REG_FTDM_OUT9_IC_1_VALUE                  0x0

/* FTDM_OUT10  - Registers (IC 1) */
#define REG_FTDM_OUT10_IC_1_ADDR                  0xF38A
#define REG_FTDM_OUT10_IC_1_BYTE                  2
#define REG_FTDM_OUT10_IC_1_VALUE                 0x0

/* FTDM_OUT11  - Registers (IC 1) */
#define REG_FTDM_OUT11_IC_1_ADDR                  0xF38B
#define REG_FTDM_OUT11_IC_1_BYTE                  2
#define REG_FTDM_OUT11_IC_1_VALUE                 0x0

/* FTDM_OUT12  - Registers (IC 1) */
#define REG_FTDM_OUT12_IC_1_ADDR                  0xF38C
#define REG_FTDM_OUT12_IC_1_BYTE                  2
#define REG_FTDM_OUT12_IC_1_VALUE                 0x0

/* FTDM_OUT13  - Registers (IC 1) */
#define REG_FTDM_OUT13_IC_1_ADDR                  0xF38D
#define REG_FTDM_OUT13_IC_1_BYTE                  2
#define REG_FTDM_OUT13_IC_1_VALUE                 0x0

/* FTDM_OUT14  - Registers (IC 1) */
#define REG_FTDM_OUT14_IC_1_ADDR                  0xF38E
#define REG_FTDM_OUT14_IC_1_BYTE                  2
#define REG_FTDM_OUT14_IC_1_VALUE                 0x0

/* FTDM_OUT15  - Registers (IC 1) */
#define REG_FTDM_OUT15_IC_1_ADDR                  0xF38F
#define REG_FTDM_OUT15_IC_1_BYTE                  2
#define REG_FTDM_OUT15_IC_1_VALUE                 0x0

/* FTDM_OUT16  - Registers (IC 1) */
#define REG_FTDM_OUT16_IC_1_ADDR                  0xF390
#define REG_FTDM_OUT16_IC_1_BYTE                  2
#define REG_FTDM_OUT16_IC_1_VALUE                 0x0

/* FTDM_OUT17  - Registers (IC 1) */
#define REG_FTDM_OUT17_IC_1_ADDR                  0xF391
#define REG_FTDM_OUT17_IC_1_BYTE                  2
#define REG_FTDM_OUT17_IC_1_VALUE                 0x0

/* FTDM_OUT18  - Registers (IC 1) */
#define REG_FTDM_OUT18_IC_1_ADDR                  0xF392
#define REG_FTDM_OUT18_IC_1_BYTE                  2
#define REG_FTDM_OUT18_IC_1_VALUE                 0x0

/* FTDM_OUT19  - Registers (IC 1) */
#define REG_FTDM_OUT19_IC_1_ADDR                  0xF393
#define REG_FTDM_OUT19_IC_1_BYTE                  2
#define REG_FTDM_OUT19_IC_1_VALUE                 0x0

/* FTDM_OUT20  - Registers (IC 1) */
#define REG_FTDM_OUT20_IC_1_ADDR                  0xF394
#define REG_FTDM_OUT20_IC_1_BYTE                  2
#define REG_FTDM_OUT20_IC_1_VALUE                 0x0

/* FTDM_OUT21  - Registers (IC 1) */
#define REG_FTDM_OUT21_IC_1_ADDR                  0xF395
#define REG_FTDM_OUT21_IC_1_BYTE                  2
#define REG_FTDM_OUT21_IC_1_VALUE                 0x0

/* FTDM_OUT22  - Registers (IC 1) */
#define REG_FTDM_OUT22_IC_1_ADDR                  0xF396
#define REG_FTDM_OUT22_IC_1_BYTE                  2
#define REG_FTDM_OUT22_IC_1_VALUE                 0x0

/* FTDM_OUT23  - Registers (IC 1) */
#define REG_FTDM_OUT23_IC_1_ADDR                  0xF397
#define REG_FTDM_OUT23_IC_1_BYTE                  2
#define REG_FTDM_OUT23_IC_1_VALUE                 0x0

/* FTDM_OUT24  - Registers (IC 1) */
#define REG_FTDM_OUT24_IC_1_ADDR                  0xF398
#define REG_FTDM_OUT24_IC_1_BYTE                  2
#define REG_FTDM_OUT24_IC_1_VALUE                 0x0

/* FTDM_OUT25  - Registers (IC 1) */
#define REG_FTDM_OUT25_IC_1_ADDR                  0xF399
#define REG_FTDM_OUT25_IC_1_BYTE                  2
#define REG_FTDM_OUT25_IC_1_VALUE                 0x0

/* FTDM_OUT26  - Registers (IC 1) */
#define REG_FTDM_OUT26_IC_1_ADDR                  0xF39A
#define REG_FTDM_OUT26_IC_1_BYTE                  2
#define REG_FTDM_OUT26_IC_1_VALUE                 0x0

/* FTDM_OUT27  - Registers (IC 1) */
#define REG_FTDM_OUT27_IC_1_ADDR                  0xF39B
#define REG_FTDM_OUT27_IC_1_BYTE                  2
#define REG_FTDM_OUT27_IC_1_VALUE                 0x0

/* FTDM_OUT28  - Registers (IC 1) */
#define REG_FTDM_OUT28_IC_1_ADDR                  0xF39C
#define REG_FTDM_OUT28_IC_1_BYTE                  2
#define REG_FTDM_OUT28_IC_1_VALUE                 0x0

/* FTDM_OUT29  - Registers (IC 1) */
#define REG_FTDM_OUT29_IC_1_ADDR                  0xF39D
#define REG_FTDM_OUT29_IC_1_BYTE                  2
#define REG_FTDM_OUT29_IC_1_VALUE                 0x0

/* FTDM_OUT30  - Registers (IC 1) */
#define REG_FTDM_OUT30_IC_1_ADDR                  0xF39E
#define REG_FTDM_OUT30_IC_1_BYTE                  2
#define REG_FTDM_OUT30_IC_1_VALUE                 0x0

/* FTDM_OUT31  - Registers (IC 1) */
#define REG_FTDM_OUT31_IC_1_ADDR                  0xF39F
#define REG_FTDM_OUT31_IC_1_BYTE                  2
#define REG_FTDM_OUT31_IC_1_VALUE                 0x0

/* FTDM_OUT32  - Registers (IC 1) */
#define REG_FTDM_OUT32_IC_1_ADDR                  0xF3A0
#define REG_FTDM_OUT32_IC_1_BYTE                  2
#define REG_FTDM_OUT32_IC_1_VALUE                 0x0

/* FTDM_OUT33  - Registers (IC 1) */
#define REG_FTDM_OUT33_IC_1_ADDR                  0xF3A1
#define REG_FTDM_OUT33_IC_1_BYTE                  2
#define REG_FTDM_OUT33_IC_1_VALUE                 0x0

/* FTDM_OUT34  - Registers (IC 1) */
#define REG_FTDM_OUT34_IC_1_ADDR                  0xF3A2
#define REG_FTDM_OUT34_IC_1_BYTE                  2
#define REG_FTDM_OUT34_IC_1_VALUE                 0x0

/* FTDM_OUT35  - Registers (IC 1) */
#define REG_FTDM_OUT35_IC_1_ADDR                  0xF3A3
#define REG_FTDM_OUT35_IC_1_BYTE                  2
#define REG_FTDM_OUT35_IC_1_VALUE                 0x0

/* FTDM_OUT36  - Registers (IC 1) */
#define REG_FTDM_OUT36_IC_1_ADDR                  0xF3A4
#define REG_FTDM_OUT36_IC_1_BYTE                  2
#define REG_FTDM_OUT36_IC_1_VALUE                 0x0

/* FTDM_OUT37  - Registers (IC 1) */
#define REG_FTDM_OUT37_IC_1_ADDR                  0xF3A5
#define REG_FTDM_OUT37_IC_1_BYTE                  2
#define REG_FTDM_OUT37_IC_1_VALUE                 0x0

/* FTDM_OUT38  - Registers (IC 1) */
#define REG_FTDM_OUT38_IC_1_ADDR                  0xF3A6
#define REG_FTDM_OUT38_IC_1_BYTE                  2
#define REG_FTDM_OUT38_IC_1_VALUE                 0x0

/* FTDM_OUT39  - Registers (IC 1) */
#define REG_FTDM_OUT39_IC_1_ADDR                  0xF3A7
#define REG_FTDM_OUT39_IC_1_BYTE                  2
#define REG_FTDM_OUT39_IC_1_VALUE                 0x0

/* FTDM_OUT40  - Registers (IC 1) */
#define REG_FTDM_OUT40_IC_1_ADDR                  0xF3A8
#define REG_FTDM_OUT40_IC_1_BYTE                  2
#define REG_FTDM_OUT40_IC_1_VALUE                 0x0

/* FTDM_OUT41  - Registers (IC 1) */
#define REG_FTDM_OUT41_IC_1_ADDR                  0xF3A9
#define REG_FTDM_OUT41_IC_1_BYTE                  2
#define REG_FTDM_OUT41_IC_1_VALUE                 0x0

/* FTDM_OUT42  - Registers (IC 1) */
#define REG_FTDM_OUT42_IC_1_ADDR                  0xF3AA
#define REG_FTDM_OUT42_IC_1_BYTE                  2
#define REG_FTDM_OUT42_IC_1_VALUE                 0x0

/* FTDM_OUT43  - Registers (IC 1) */
#define REG_FTDM_OUT43_IC_1_ADDR                  0xF3AB
#define REG_FTDM_OUT43_IC_1_BYTE                  2
#define REG_FTDM_OUT43_IC_1_VALUE                 0x0

/* FTDM_OUT44  - Registers (IC 1) */
#define REG_FTDM_OUT44_IC_1_ADDR                  0xF3AC
#define REG_FTDM_OUT44_IC_1_BYTE                  2
#define REG_FTDM_OUT44_IC_1_VALUE                 0x0

/* FTDM_OUT45  - Registers (IC 1) */
#define REG_FTDM_OUT45_IC_1_ADDR                  0xF3AD
#define REG_FTDM_OUT45_IC_1_BYTE                  2
#define REG_FTDM_OUT45_IC_1_VALUE                 0x0

/* FTDM_OUT46  - Registers (IC 1) */
#define REG_FTDM_OUT46_IC_1_ADDR                  0xF3AE
#define REG_FTDM_OUT46_IC_1_BYTE                  2
#define REG_FTDM_OUT46_IC_1_VALUE                 0x0

/* FTDM_OUT47  - Registers (IC 1) */
#define REG_FTDM_OUT47_IC_1_ADDR                  0xF3AF
#define REG_FTDM_OUT47_IC_1_BYTE                  2
#define REG_FTDM_OUT47_IC_1_VALUE                 0x0

/* FTDM_OUT48  - Registers (IC 1) */
#define REG_FTDM_OUT48_IC_1_ADDR                  0xF3B0
#define REG_FTDM_OUT48_IC_1_BYTE                  2
#define REG_FTDM_OUT48_IC_1_VALUE                 0x0

/* FTDM_OUT49  - Registers (IC 1) */
#define REG_FTDM_OUT49_IC_1_ADDR                  0xF3B1
#define REG_FTDM_OUT49_IC_1_BYTE                  2
#define REG_FTDM_OUT49_IC_1_VALUE                 0x0

/* FTDM_OUT50  - Registers (IC 1) */
#define REG_FTDM_OUT50_IC_1_ADDR                  0xF3B2
#define REG_FTDM_OUT50_IC_1_BYTE                  2
#define REG_FTDM_OUT50_IC_1_VALUE                 0x0

/* FTDM_OUT51  - Registers (IC 1) */
#define REG_FTDM_OUT51_IC_1_ADDR                  0xF3B3
#define REG_FTDM_OUT51_IC_1_BYTE                  2
#define REG_FTDM_OUT51_IC_1_VALUE                 0x0

/* FTDM_OUT52  - Registers (IC 1) */
#define REG_FTDM_OUT52_IC_1_ADDR                  0xF3B4
#define REG_FTDM_OUT52_IC_1_BYTE                  2
#define REG_FTDM_OUT52_IC_1_VALUE                 0x0

/* FTDM_OUT53  - Registers (IC 1) */
#define REG_FTDM_OUT53_IC_1_ADDR                  0xF3B5
#define REG_FTDM_OUT53_IC_1_BYTE                  2
#define REG_FTDM_OUT53_IC_1_VALUE                 0x0

/* FTDM_OUT54  - Registers (IC 1) */
#define REG_FTDM_OUT54_IC_1_ADDR                  0xF3B6
#define REG_FTDM_OUT54_IC_1_BYTE                  2
#define REG_FTDM_OUT54_IC_1_VALUE                 0x0

/* FTDM_OUT55  - Registers (IC 1) */
#define REG_FTDM_OUT55_IC_1_ADDR                  0xF3B7
#define REG_FTDM_OUT55_IC_1_BYTE                  2
#define REG_FTDM_OUT55_IC_1_VALUE                 0x0

/* FTDM_OUT56  - Registers (IC 1) */
#define REG_FTDM_OUT56_IC_1_ADDR                  0xF3B8
#define REG_FTDM_OUT56_IC_1_BYTE                  2
#define REG_FTDM_OUT56_IC_1_VALUE                 0x0

/* FTDM_OUT57  - Registers (IC 1) */
#define REG_FTDM_OUT57_IC_1_ADDR                  0xF3B9
#define REG_FTDM_OUT57_IC_1_BYTE                  2
#define REG_FTDM_OUT57_IC_1_VALUE                 0x0

/* FTDM_OUT58  - Registers (IC 1) */
#define REG_FTDM_OUT58_IC_1_ADDR                  0xF3BA
#define REG_FTDM_OUT58_IC_1_BYTE                  2
#define REG_FTDM_OUT58_IC_1_VALUE                 0x0

/* FTDM_OUT59  - Registers (IC 1) */
#define REG_FTDM_OUT59_IC_1_ADDR                  0xF3BB
#define REG_FTDM_OUT59_IC_1_BYTE                  2
#define REG_FTDM_OUT59_IC_1_VALUE                 0x0

/* FTDM_OUT60  - Registers (IC 1) */
#define REG_FTDM_OUT60_IC_1_ADDR                  0xF3BC
#define REG_FTDM_OUT60_IC_1_BYTE                  2
#define REG_FTDM_OUT60_IC_1_VALUE                 0x0

/* FTDM_OUT61  - Registers (IC 1) */
#define REG_FTDM_OUT61_IC_1_ADDR                  0xF3BD
#define REG_FTDM_OUT61_IC_1_BYTE                  2
#define REG_FTDM_OUT61_IC_1_VALUE                 0x0

/* FTDM_OUT62  - Registers (IC 1) */
#define REG_FTDM_OUT62_IC_1_ADDR                  0xF3BE
#define REG_FTDM_OUT62_IC_1_BYTE                  2
#define REG_FTDM_OUT62_IC_1_VALUE                 0x0

/* FTDM_OUT63  - Registers (IC 1) */
#define REG_FTDM_OUT63_IC_1_ADDR                  0xF3BF
#define REG_FTDM_OUT63_IC_1_BYTE                  2
#define REG_FTDM_OUT63_IC_1_VALUE                 0x0

/* HIBERNATE  - Registers (IC 1) */
#define REG_HIBERNATE_IC_1_ADDR                   0xF400
#define REG_HIBERNATE_IC_1_BYTE                   2
#define REG_HIBERNATE_IC_1_VALUE                  0x0

/* START_PULSE  - Registers (IC 1) */
#define REG_START_PULSE_IC_1_ADDR                 0xF401
#define REG_START_PULSE_IC_1_BYTE                 2
#define REG_START_PULSE_IC_1_VALUE                0x2

/* START_CORE  - Registers (IC 1) */
#define REG_START_CORE_IC_1_ADDR                  0xF402
#define REG_START_CORE_IC_1_BYTE                  2
#define REG_START_CORE_IC_1_VALUE                 0x1

/* KILL_CORE  - Registers (IC 1) */
#define REG_KILL_CORE_IC_1_ADDR                   0xF403
#define REG_KILL_CORE_IC_1_BYTE                   2
#define REG_KILL_CORE_IC_1_VALUE                  0x0

/* START_ADDRESS  - Registers (IC 1) */
#define REG_START_ADDRESS_IC_1_ADDR               0xF404
#define REG_START_ADDRESS_IC_1_BYTE               2
#define REG_START_ADDRESS_IC_1_VALUE              0x0

/* CORE_STATUS  - Registers (IC 1) */
#define REG_CORE_STATUS_IC_1_ADDR                 0xF405
#define REG_CORE_STATUS_IC_1_BYTE                 0
#define REG_CORE_STATUS_IC_1_VALUE                0x1

/* DEBUG_MODE  - Registers (IC 1) */
#define REG_DEBUG_MODE_IC_1_ADDR                  0xF420
#define REG_DEBUG_MODE_IC_1_BYTE                  2
#define REG_DEBUG_MODE_IC_1_VALUE                 0x0

/* PANIC_CLEAR  - Registers (IC 1) */
#define REG_PANIC_CLEAR_IC_1_ADDR                 0xF421
#define REG_PANIC_CLEAR_IC_1_BYTE                 2
#define REG_PANIC_CLEAR_IC_1_VALUE                0x0

/* PANIC_PARITY_MASK  - Registers (IC 1) */
#define REG_PANIC_PARITY_MASK_IC_1_ADDR           0xF422
#define REG_PANIC_PARITY_MASK_IC_1_BYTE           2
#define REG_PANIC_PARITY_MASK_IC_1_VALUE          0x3

/* PANIC_SOFTWARE_MASK  - Registers (IC 1) */
#define REG_PANIC_SOFTWARE_MASK_IC_1_ADDR         0xF423
#define REG_PANIC_SOFTWARE_MASK_IC_1_BYTE         2
#define REG_PANIC_SOFTWARE_MASK_IC_1_VALUE        0x0

/* PANIC_WD_MASK  - Registers (IC 1) */
#define REG_PANIC_WD_MASK_IC_1_ADDR               0xF424
#define REG_PANIC_WD_MASK_IC_1_BYTE               2
#define REG_PANIC_WD_MASK_IC_1_VALUE              0x0

/* PANIC_STACK_MASK  - Registers (IC 1) */
#define REG_PANIC_STACK_MASK_IC_1_ADDR            0xF425
#define REG_PANIC_STACK_MASK_IC_1_BYTE            2
#define REG_PANIC_STACK_MASK_IC_1_VALUE           0x0

/* PANIC_LOOP_MASK  - Registers (IC 1) */
#define REG_PANIC_LOOP_MASK_IC_1_ADDR             0xF426
#define REG_PANIC_LOOP_MASK_IC_1_BYTE             2
#define REG_PANIC_LOOP_MASK_IC_1_VALUE            0x0

/* PANIC_FLAG  - Registers (IC 1) */
#define REG_PANIC_FLAG_IC_1_ADDR                  0xF427
#define REG_PANIC_FLAG_IC_1_BYTE                  0
#define REG_PANIC_FLAG_IC_1_VALUE                 0x1

/* PANIC_CODE  - Registers (IC 1) */
#define REG_PANIC_CODE_IC_1_ADDR                  0xF428
#define REG_PANIC_CODE_IC_1_BYTE                  0
#define REG_PANIC_CODE_IC_1_VALUE                 0x80

/* DECODE_OP0  - Registers (IC 1) */
#define REG_DECODE_OP0_IC_1_ADDR                  0xF429
#define REG_DECODE_OP0_IC_1_BYTE                  0
#define REG_DECODE_OP0_IC_1_VALUE                 0x0

/* DECODE_OP1  - Registers (IC 1) */
#define REG_DECODE_OP1_IC_1_ADDR                  0xF42A
#define REG_DECODE_OP1_IC_1_BYTE                  0
#define REG_DECODE_OP1_IC_1_VALUE                 0x0

/* DECODE_OP2  - Registers (IC 1) */
#define REG_DECODE_OP2_IC_1_ADDR                  0xF42B
#define REG_DECODE_OP2_IC_1_BYTE                  0
#define REG_DECODE_OP2_IC_1_VALUE                 0xFFA8

/* DECODE_OP3  - Registers (IC 1) */
#define REG_DECODE_OP3_IC_1_ADDR                  0xF42C
#define REG_DECODE_OP3_IC_1_BYTE                  0
#define REG_DECODE_OP3_IC_1_VALUE                 0xA40

/* EXECUTE_OP0  - Registers (IC 1) */
#define REG_EXECUTE_OP0_IC_1_ADDR                 0xF42D
#define REG_EXECUTE_OP0_IC_1_BYTE                 0
#define REG_EXECUTE_OP0_IC_1_VALUE                0x0

/* EXECUTE_OP1  - Registers (IC 1) */
#define REG_EXECUTE_OP1_IC_1_ADDR                 0xF42E
#define REG_EXECUTE_OP1_IC_1_BYTE                 0
#define REG_EXECUTE_OP1_IC_1_VALUE                0x0

/* EXECUTE_OP2  - Registers (IC 1) */
#define REG_EXECUTE_OP2_IC_1_ADDR                 0xF42F
#define REG_EXECUTE_OP2_IC_1_BYTE                 0
#define REG_EXECUTE_OP2_IC_1_VALUE                0x0

/* EXECUTE_OP3  - Registers (IC 1) */
#define REG_EXECUTE_OP3_IC_1_ADDR                 0xF430
#define REG_EXECUTE_OP3_IC_1_BYTE                 0
#define REG_EXECUTE_OP3_IC_1_VALUE                0x0

/* DECODE_COUNT  - Registers (IC 1) */
#define REG_DECODE_COUNT_IC_1_ADDR                0xF431
#define REG_DECODE_COUNT_IC_1_BYTE                0
#define REG_DECODE_COUNT_IC_1_VALUE               0xC0FF

/* EXECUTE_COUNT  - Registers (IC 1) */
#define REG_EXECUTE_COUNT_IC_1_ADDR               0xF432
#define REG_EXECUTE_COUNT_IC_1_BYTE               0
#define REG_EXECUTE_COUNT_IC_1_VALUE              0x0

/* SOFTWARE_VALUE_0  - Registers (IC 1) */
#define REG_SOFTWARE_VALUE_0_IC_1_ADDR            0xF433
#define REG_SOFTWARE_VALUE_0_IC_1_BYTE            0
#define REG_SOFTWARE_VALUE_0_IC_1_VALUE           0x0

/* SOFTWARE_VALUE_1  - Registers (IC 1) */
#define REG_SOFTWARE_VALUE_1_IC_1_ADDR            0xF434
#define REG_SOFTWARE_VALUE_1_IC_1_BYTE            0
#define REG_SOFTWARE_VALUE_1_IC_1_VALUE           0x0

/* WATCHDOG_MAXCOUNT  - Registers (IC 1) */
#define REG_WATCHDOG_MAXCOUNT_IC_1_ADDR           0xF443
#define REG_WATCHDOG_MAXCOUNT_IC_1_BYTE           2
#define REG_WATCHDOG_MAXCOUNT_IC_1_VALUE          0x0

/* WATCHDOG_PRESCALE  - Registers (IC 1) */
#define REG_WATCHDOG_PRESCALE_IC_1_ADDR           0xF444
#define REG_WATCHDOG_PRESCALE_IC_1_BYTE           2
#define REG_WATCHDOG_PRESCALE_IC_1_VALUE          0x0

/* BLOCKINT_EN  - Registers (IC 1) */
#define REG_BLOCKINT_EN_IC_1_ADDR                 0xF450
#define REG_BLOCKINT_EN_IC_1_BYTE                 2
#define REG_BLOCKINT_EN_IC_1_VALUE                0x0

/* BLOCKINT_VALUE  - Registers (IC 1) */
#define REG_BLOCKINT_VALUE_IC_1_ADDR              0xF451
#define REG_BLOCKINT_VALUE_IC_1_BYTE              2
#define REG_BLOCKINT_VALUE_IC_1_VALUE             0x0

/* PROG_CNTR0  - Registers (IC 1) */
#define REG_PROG_CNTR0_IC_1_ADDR                  0xF460
#define REG_PROG_CNTR0_IC_1_BYTE                  0
#define REG_PROG_CNTR0_IC_1_VALUE                 0x0

/* PROG_CNTR1  - Registers (IC 1) */
#define REG_PROG_CNTR1_IC_1_ADDR                  0xF461
#define REG_PROG_CNTR1_IC_1_BYTE                  0
#define REG_PROG_CNTR1_IC_1_VALUE                 0x86C

/* PROG_CNTR_CLEAR  - Registers (IC 1) */
#define REG_PROG_CNTR_CLEAR_IC_1_ADDR             0xF462
#define REG_PROG_CNTR_CLEAR_IC_1_BYTE             2
#define REG_PROG_CNTR_CLEAR_IC_1_VALUE            0x0

/* PROG_CNTR_LENGTH0  - Registers (IC 1) */
#define REG_PROG_CNTR_LENGTH0_IC_1_ADDR           0xF463
#define REG_PROG_CNTR_LENGTH0_IC_1_BYTE           0
#define REG_PROG_CNTR_LENGTH0_IC_1_VALUE          0x0

/* PROG_CNTR_LENGTH1  - Registers (IC 1) */
#define REG_PROG_CNTR_LENGTH1_IC_1_ADDR           0xF464
#define REG_PROG_CNTR_LENGTH1_IC_1_BYTE           0
#define REG_PROG_CNTR_LENGTH1_IC_1_VALUE          0x66A

/* PROG_CNTR_MAXLENGTH0  - Registers (IC 1) */
#define REG_PROG_CNTR_MAXLENGTH0_IC_1_ADDR        0xF465
#define REG_PROG_CNTR_MAXLENGTH0_IC_1_BYTE        0
#define REG_PROG_CNTR_MAXLENGTH0_IC_1_VALUE       0x0

/* PROG_CNTR_MAXLENGTH1  - Registers (IC 1) */
#define REG_PROG_CNTR_MAXLENGTH1_IC_1_ADDR        0xF466
#define REG_PROG_CNTR_MAXLENGTH1_IC_1_BYTE        0
#define REG_PROG_CNTR_MAXLENGTH1_IC_1_VALUE       0x120A

/* MP0_MODE  - Registers (IC 1) */
#define REG_MP0_MODE_IC_1_ADDR                    0xF510
#define REG_MP0_MODE_IC_1_BYTE                    2
#define REG_MP0_MODE_IC_1_VALUE                   0xD

/* MP1_MODE  - Registers (IC 1) */
#define REG_MP1_MODE_IC_1_ADDR                    0xF511
#define REG_MP1_MODE_IC_1_BYTE                    2
#define REG_MP1_MODE_IC_1_VALUE                   0x0

/* MP2_MODE  - Registers (IC 1) */
#define REG_MP2_MODE_IC_1_ADDR                    0xF512
#define REG_MP2_MODE_IC_1_BYTE                    2
#define REG_MP2_MODE_IC_1_VALUE                   0x0

/* MP3_MODE  - Registers (IC 1) */
#define REG_MP3_MODE_IC_1_ADDR                    0xF513
#define REG_MP3_MODE_IC_1_BYTE                    2
#define REG_MP3_MODE_IC_1_VALUE                   0x0

/* MP4_MODE  - Registers (IC 1) */
#define REG_MP4_MODE_IC_1_ADDR                    0xF514
#define REG_MP4_MODE_IC_1_BYTE                    2
#define REG_MP4_MODE_IC_1_VALUE                   0x0

/* MP5_MODE  - Registers (IC 1) */
#define REG_MP5_MODE_IC_1_ADDR                    0xF515
#define REG_MP5_MODE_IC_1_BYTE                    2
#define REG_MP5_MODE_IC_1_VALUE                   0x0

/* MP6_MODE  - Registers (IC 1) */
#define REG_MP6_MODE_IC_1_ADDR                    0xF516
#define REG_MP6_MODE_IC_1_BYTE                    2
#define REG_MP6_MODE_IC_1_VALUE                   0x0

/* MP7_MODE  - Registers (IC 1) */
#define REG_MP7_MODE_IC_1_ADDR                    0xF517
#define REG_MP7_MODE_IC_1_BYTE                    2
#define REG_MP7_MODE_IC_1_VALUE                   0x0

/* MP8_MODE  - Registers (IC 1) */
#define REG_MP8_MODE_IC_1_ADDR                    0xF518
#define REG_MP8_MODE_IC_1_BYTE                    2
#define REG_MP8_MODE_IC_1_VALUE                   0x0

/* MP9_MODE  - Registers (IC 1) */
#define REG_MP9_MODE_IC_1_ADDR                    0xF519
#define REG_MP9_MODE_IC_1_BYTE                    2
#define REG_MP9_MODE_IC_1_VALUE                   0x0

/* MP10_MODE  - Registers (IC 1) */
#define REG_MP10_MODE_IC_1_ADDR                   0xF51A
#define REG_MP10_MODE_IC_1_BYTE                   2
#define REG_MP10_MODE_IC_1_VALUE                  0x0

/* MP11_MODE  - Registers (IC 1) */
#define REG_MP11_MODE_IC_1_ADDR                   0xF51B
#define REG_MP11_MODE_IC_1_BYTE                   2
#define REG_MP11_MODE_IC_1_VALUE                  0x0

/* MP12_MODE  - Registers (IC 1) */
#define REG_MP12_MODE_IC_1_ADDR                   0xF51C
#define REG_MP12_MODE_IC_1_BYTE                   2
#define REG_MP12_MODE_IC_1_VALUE                  0x0

/* MP13_MODE  - Registers (IC 1) */
#define REG_MP13_MODE_IC_1_ADDR                   0xF51D
#define REG_MP13_MODE_IC_1_BYTE                   2
#define REG_MP13_MODE_IC_1_VALUE                  0x0

/* MP0_WRITE  - Registers (IC 1) */
#define REG_MP0_WRITE_IC_1_ADDR                   0xF520
#define REG_MP0_WRITE_IC_1_BYTE                   2
#define REG_MP0_WRITE_IC_1_VALUE                  0x0

/* MP1_WRITE  - Registers (IC 1) */
#define REG_MP1_WRITE_IC_1_ADDR                   0xF521
#define REG_MP1_WRITE_IC_1_BYTE                   2
#define REG_MP1_WRITE_IC_1_VALUE                  0x0

/* MP2_WRITE  - Registers (IC 1) */
#define REG_MP2_WRITE_IC_1_ADDR                   0xF522
#define REG_MP2_WRITE_IC_1_BYTE                   2
#define REG_MP2_WRITE_IC_1_VALUE                  0x0

/* MP3_WRITE  - Registers (IC 1) */
#define REG_MP3_WRITE_IC_1_ADDR                   0xF523
#define REG_MP3_WRITE_IC_1_BYTE                   2
#define REG_MP3_WRITE_IC_1_VALUE                  0x0

/* MP4_WRITE  - Registers (IC 1) */
#define REG_MP4_WRITE_IC_1_ADDR                   0xF524
#define REG_MP4_WRITE_IC_1_BYTE                   2
#define REG_MP4_WRITE_IC_1_VALUE                  0x0

/* MP5_WRITE  - Registers (IC 1) */
#define REG_MP5_WRITE_IC_1_ADDR                   0xF525
#define REG_MP5_WRITE_IC_1_BYTE                   2
#define REG_MP5_WRITE_IC_1_VALUE                  0x0

/* MP6_WRITE  - Registers (IC 1) */
#define REG_MP6_WRITE_IC_1_ADDR                   0xF526
#define REG_MP6_WRITE_IC_1_BYTE                   2
#define REG_MP6_WRITE_IC_1_VALUE                  0x0

/* MP7_WRITE  - Registers (IC 1) */
#define REG_MP7_WRITE_IC_1_ADDR                   0xF527
#define REG_MP7_WRITE_IC_1_BYTE                   2
#define REG_MP7_WRITE_IC_1_VALUE                  0x0

/* MP8_WRITE  - Registers (IC 1) */
#define REG_MP8_WRITE_IC_1_ADDR                   0xF528
#define REG_MP8_WRITE_IC_1_BYTE                   2
#define REG_MP8_WRITE_IC_1_VALUE                  0x0

/* MP9_WRITE  - Registers (IC 1) */
#define REG_MP9_WRITE_IC_1_ADDR                   0xF529
#define REG_MP9_WRITE_IC_1_BYTE                   2
#define REG_MP9_WRITE_IC_1_VALUE                  0x0

/* MP10_WRITE  - Registers (IC 1) */
#define REG_MP10_WRITE_IC_1_ADDR                  0xF52A
#define REG_MP10_WRITE_IC_1_BYTE                  2
#define REG_MP10_WRITE_IC_1_VALUE                 0x0

/* MP11_WRITE  - Registers (IC 1) */
#define REG_MP11_WRITE_IC_1_ADDR                  0xF52B
#define REG_MP11_WRITE_IC_1_BYTE                  2
#define REG_MP11_WRITE_IC_1_VALUE                 0x0

/* MP12_WRITE  - Registers (IC 1) */
#define REG_MP12_WRITE_IC_1_ADDR                  0xF52C
#define REG_MP12_WRITE_IC_1_BYTE                  2
#define REG_MP12_WRITE_IC_1_VALUE                 0x0

/* MP13_WRITE  - Registers (IC 1) */
#define REG_MP13_WRITE_IC_1_ADDR                  0xF52D
#define REG_MP13_WRITE_IC_1_BYTE                  2
#define REG_MP13_WRITE_IC_1_VALUE                 0x0

/* MP0_READ  - Registers (IC 1) */
#define REG_MP0_READ_IC_1_ADDR                    0xF530
#define REG_MP0_READ_IC_1_BYTE                    0
#define REG_MP0_READ_IC_1_VALUE                   0x1

/* MP1_READ  - Registers (IC 1) */
#define REG_MP1_READ_IC_1_ADDR                    0xF531
#define REG_MP1_READ_IC_1_BYTE                    0
#define REG_MP1_READ_IC_1_VALUE                   0x0

/* MP2_READ  - Registers (IC 1) */
#define REG_MP2_READ_IC_1_ADDR                    0xF532
#define REG_MP2_READ_IC_1_BYTE                    0
#define REG_MP2_READ_IC_1_VALUE                   0x0

/* MP3_READ  - Registers (IC 1) */
#define REG_MP3_READ_IC_1_ADDR                    0xF533
#define REG_MP3_READ_IC_1_BYTE                    0
#define REG_MP3_READ_IC_1_VALUE                   0x0

/* MP4_READ  - Registers (IC 1) */
#define REG_MP4_READ_IC_1_ADDR                    0xF534
#define REG_MP4_READ_IC_1_BYTE                    0
#define REG_MP4_READ_IC_1_VALUE                   0x0

/* MP5_READ  - Registers (IC 1) */
#define REG_MP5_READ_IC_1_ADDR                    0xF535
#define REG_MP5_READ_IC_1_BYTE                    0
#define REG_MP5_READ_IC_1_VALUE                   0x0

/* MP6_READ  - Registers (IC 1) */
#define REG_MP6_READ_IC_1_ADDR                    0xF536
#define REG_MP6_READ_IC_1_BYTE                    0
#define REG_MP6_READ_IC_1_VALUE                   0x0

/* MP7_READ  - Registers (IC 1) */
#define REG_MP7_READ_IC_1_ADDR                    0xF537
#define REG_MP7_READ_IC_1_BYTE                    0
#define REG_MP7_READ_IC_1_VALUE                   0x0

/* MP8_READ  - Registers (IC 1) */
#define REG_MP8_READ_IC_1_ADDR                    0xF538
#define REG_MP8_READ_IC_1_BYTE                    0
#define REG_MP8_READ_IC_1_VALUE                   0x0

/* MP9_READ  - Registers (IC 1) */
#define REG_MP9_READ_IC_1_ADDR                    0xF539
#define REG_MP9_READ_IC_1_BYTE                    0
#define REG_MP9_READ_IC_1_VALUE                   0x0

/* MP10_READ  - Registers (IC 1) */
#define REG_MP10_READ_IC_1_ADDR                   0xF53A
#define REG_MP10_READ_IC_1_BYTE                   0
#define REG_MP10_READ_IC_1_VALUE                  0x0

/* MP11_READ  - Registers (IC 1) */
#define REG_MP11_READ_IC_1_ADDR                   0xF53B
#define REG_MP11_READ_IC_1_BYTE                   0
#define REG_MP11_READ_IC_1_VALUE                  0x0

/* MP12_READ  - Registers (IC 1) */
#define REG_MP12_READ_IC_1_ADDR                   0xF53C
#define REG_MP12_READ_IC_1_BYTE                   0
#define REG_MP12_READ_IC_1_VALUE                  0x0

/* MP13_READ  - Registers (IC 1) */
#define REG_MP13_READ_IC_1_ADDR                   0xF53D
#define REG_MP13_READ_IC_1_BYTE                   0
#define REG_MP13_READ_IC_1_VALUE                  0x0

/* DMIC_CTRL0  - Registers (IC 1) */
#define REG_DMIC_CTRL0_IC_1_ADDR                  0xF560
#define REG_DMIC_CTRL0_IC_1_BYTE                  2
#define REG_DMIC_CTRL0_IC_1_VALUE                 0x4000

/* DMIC_CTRL1  - Registers (IC 1) */
#define REG_DMIC_CTRL1_IC_1_ADDR                  0xF561
#define REG_DMIC_CTRL1_IC_1_BYTE                  2
#define REG_DMIC_CTRL1_IC_1_VALUE                 0x4000

/* ASRC_LOCK  - Registers (IC 1) */
#define REG_ASRC_LOCK_IC_1_ADDR                   0xF580
#define REG_ASRC_LOCK_IC_1_BYTE                   0
#define REG_ASRC_LOCK_IC_1_VALUE                  0x1

/* ASRC_MUTE  - Registers (IC 1) */
#define REG_ASRC_MUTE_IC_1_ADDR                   0xF581
#define REG_ASRC_MUTE_IC_1_BYTE                   2
#define REG_ASRC_MUTE_IC_1_VALUE                  0x0

/* ASRC0_RATIO  - Registers (IC 1) */
#define REG_ASRC0_RATIO_IC_1_ADDR                 0xF582
#define REG_ASRC0_RATIO_IC_1_BYTE                 0
#define REG_ASRC0_RATIO_IC_1_VALUE                0x1000

/* ASRC1_RATIO  - Registers (IC 1) */
#define REG_ASRC1_RATIO_IC_1_ADDR                 0xF583
#define REG_ASRC1_RATIO_IC_1_BYTE                 0
#define REG_ASRC1_RATIO_IC_1_VALUE                0x0

/* ASRC2_RATIO  - Registers (IC 1) */
#define REG_ASRC2_RATIO_IC_1_ADDR                 0xF584
#define REG_ASRC2_RATIO_IC_1_BYTE                 0
#define REG_ASRC2_RATIO_IC_1_VALUE                0x0

/* ASRC3_RATIO  - Registers (IC 1) */
#define REG_ASRC3_RATIO_IC_1_ADDR                 0xF585
#define REG_ASRC3_RATIO_IC_1_BYTE                 0
#define REG_ASRC3_RATIO_IC_1_VALUE                0x0

/* ASRC4_RATIO  - Registers (IC 1) */
#define REG_ASRC4_RATIO_IC_1_ADDR                 0xF586
#define REG_ASRC4_RATIO_IC_1_BYTE                 0
#define REG_ASRC4_RATIO_IC_1_VALUE                0x0

/* ASRC5_RATIO  - Registers (IC 1) */
#define REG_ASRC5_RATIO_IC_1_ADDR                 0xF587
#define REG_ASRC5_RATIO_IC_1_BYTE                 0
#define REG_ASRC5_RATIO_IC_1_VALUE                0x0

/* ASRC6_RATIO  - Registers (IC 1) */
#define REG_ASRC6_RATIO_IC_1_ADDR                 0xF588
#define REG_ASRC6_RATIO_IC_1_BYTE                 0
#define REG_ASRC6_RATIO_IC_1_VALUE                0x0

/* ASRC7_RATIO  - Registers (IC 1) */
#define REG_ASRC7_RATIO_IC_1_ADDR                 0xF589
#define REG_ASRC7_RATIO_IC_1_BYTE                 0
#define REG_ASRC7_RATIO_IC_1_VALUE                0x0

/* ADC_READ0  - Registers (IC 1) */
#define REG_ADC_READ0_IC_1_ADDR                   0xF5A0
#define REG_ADC_READ0_IC_1_BYTE                   0
#define REG_ADC_READ0_IC_1_VALUE                  0x26

/* ADC_READ1  - Registers (IC 1) */
#define REG_ADC_READ1_IC_1_ADDR                   0xF5A1
#define REG_ADC_READ1_IC_1_BYTE                   0
#define REG_ADC_READ1_IC_1_VALUE                  0x39

/* ADC_READ2  - Registers (IC 1) */
#define REG_ADC_READ2_IC_1_ADDR                   0xF5A2
#define REG_ADC_READ2_IC_1_BYTE                   0
#define REG_ADC_READ2_IC_1_VALUE                  0xEA

/* ADC_READ3  - Registers (IC 1) */
#define REG_ADC_READ3_IC_1_ADDR                   0xF5A3
#define REG_ADC_READ3_IC_1_BYTE                   0
#define REG_ADC_READ3_IC_1_VALUE                  0xBC

/* ADC_READ4  - Registers (IC 1) */
#define REG_ADC_READ4_IC_1_ADDR                   0xF5A4
#define REG_ADC_READ4_IC_1_BYTE                   0
#define REG_ADC_READ4_IC_1_VALUE                  0x11D

/* ADC_READ5  - Registers (IC 1) */
#define REG_ADC_READ5_IC_1_ADDR                   0xF5A5
#define REG_ADC_READ5_IC_1_BYTE                   0
#define REG_ADC_READ5_IC_1_VALUE                  0xE9

/* SPDIF_LOCK_DET  - Registers (IC 1) */
#define REG_SPDIF_LOCK_DET_IC_1_ADDR              0xF600
#define REG_SPDIF_LOCK_DET_IC_1_BYTE              0
#define REG_SPDIF_LOCK_DET_IC_1_VALUE             0x1

/* SPDIF_RX_CTRL  - Registers (IC 1) */
#define REG_SPDIF_RX_CTRL_IC_1_ADDR               0xF601
#define REG_SPDIF_RX_CTRL_IC_1_BYTE               2
#define REG_SPDIF_RX_CTRL_IC_1_VALUE              0x3

/* SPDIF_RX_DECODE  - Registers (IC 1) */
#define REG_SPDIF_RX_DECODE_IC_1_ADDR             0xF602
#define REG_SPDIF_RX_DECODE_IC_1_BYTE             0
#define REG_SPDIF_RX_DECODE_IC_1_VALUE            0x2EC

/* SPDIF_RX_COMPRMODE  - Registers (IC 1) */
#define REG_SPDIF_RX_COMPRMODE_IC_1_ADDR          0xF603
#define REG_SPDIF_RX_COMPRMODE_IC_1_BYTE          0
#define REG_SPDIF_RX_COMPRMODE_IC_1_VALUE         0x0

/* SPDIF_RESTART  - Registers (IC 1) */
#define REG_SPDIF_RESTART_IC_1_ADDR               0xF604
#define REG_SPDIF_RESTART_IC_1_BYTE               2
#define REG_SPDIF_RESTART_IC_1_VALUE              0x1

/* SPDIF_LOSS_OF_LOCK  - Registers (IC 1) */
#define REG_SPDIF_LOSS_OF_LOCK_IC_1_ADDR          0xF605
#define REG_SPDIF_LOSS_OF_LOCK_IC_1_BYTE          0
#define REG_SPDIF_LOSS_OF_LOCK_IC_1_VALUE         0x0

/* SPDIF_AUX_EN  - Registers (IC 1) */
#define REG_SPDIF_AUX_EN_IC_1_ADDR                0xF608
#define REG_SPDIF_AUX_EN_IC_1_BYTE                2
#define REG_SPDIF_AUX_EN_IC_1_VALUE               0x0

/* SPDIF_RX_AUXBIT_READY  - Registers (IC 1) */
#define REG_SPDIF_RX_AUXBIT_READY_IC_1_ADDR       0xF60F
#define REG_SPDIF_RX_AUXBIT_READY_IC_1_BYTE       0
#define REG_SPDIF_RX_AUXBIT_READY_IC_1_VALUE      0x1

/* SPDIF_RX_CS_LEFT_0  - Registers (IC 1) */
#define REG_SPDIF_RX_CS_LEFT_0_IC_1_ADDR          0xF610
#define REG_SPDIF_RX_CS_LEFT_0_IC_1_BYTE          0
#define REG_SPDIF_RX_CS_LEFT_0_IC_1_VALUE         0x0

/* SPDIF_RX_CS_LEFT_1  - Registers (IC 1) */
#define REG_SPDIF_RX_CS_LEFT_1_IC_1_ADDR          0xF611
#define REG_SPDIF_RX_CS_LEFT_1_IC_1_BYTE          0
#define REG_SPDIF_RX_CS_LEFT_1_IC_1_VALUE         0x0

/* SPDIF_RX_CS_LEFT_2  - Registers (IC 1) */
#define REG_SPDIF_RX_CS_LEFT_2_IC_1_ADDR          0xF612
#define REG_SPDIF_RX_CS_LEFT_2_IC_1_BYTE          0
#define REG_SPDIF_RX_CS_LEFT_2_IC_1_VALUE         0x0

/* SPDIF_RX_CS_LEFT_3  - Registers (IC 1) */
#define REG_SPDIF_RX_CS_LEFT_3_IC_1_ADDR          0xF613
#define REG_SPDIF_RX_CS_LEFT_3_IC_1_BYTE          0
#define REG_SPDIF_RX_CS_LEFT_3_IC_1_VALUE         0x0

/* SPDIF_RX_CS_LEFT_4  - Registers (IC 1) */
#define REG_SPDIF_RX_CS_LEFT_4_IC_1_ADDR          0xF614
#define REG_SPDIF_RX_CS_LEFT_4_IC_1_BYTE          0
#define REG_SPDIF_RX_CS_LEFT_4_IC_1_VALUE         0x0

/* SPDIF_RX_CS_LEFT_5  - Registers (IC 1) */
#define REG_SPDIF_RX_CS_LEFT_5_IC_1_ADDR          0xF615
#define REG_SPDIF_RX_CS_LEFT_5_IC_1_BYTE          0
#define REG_SPDIF_RX_CS_LEFT_5_IC_1_VALUE         0x0

/* SPDIF_RX_CS_LEFT_6  - Registers (IC 1) */
#define REG_SPDIF_RX_CS_LEFT_6_IC_1_ADDR          0xF616
#define REG_SPDIF_RX_CS_LEFT_6_IC_1_BYTE          0
#define REG_SPDIF_RX_CS_LEFT_6_IC_1_VALUE         0x0

/* SPDIF_RX_CS_LEFT_7  - Registers (IC 1) */
#define REG_SPDIF_RX_CS_LEFT_7_IC_1_ADDR          0xF617
#define REG_SPDIF_RX_CS_LEFT_7_IC_1_BYTE          0
#define REG_SPDIF_RX_CS_LEFT_7_IC_1_VALUE         0x0

/* SPDIF_RX_CS_LEFT_8  - Registers (IC 1) */
#define REG_SPDIF_RX_CS_LEFT_8_IC_1_ADDR          0xF618
#define REG_SPDIF_RX_CS_LEFT_8_IC_1_BYTE          0
#define REG_SPDIF_RX_CS_LEFT_8_IC_1_VALUE         0x0

/* SPDIF_RX_CS_LEFT_9  - Registers (IC 1) */
#define REG_SPDIF_RX_CS_LEFT_9_IC_1_ADDR          0xF619
#define REG_SPDIF_RX_CS_LEFT_9_IC_1_BYTE          0
#define REG_SPDIF_RX_CS_LEFT_9_IC_1_VALUE         0xB

/* SPDIF_RX_CS_LEFT_10  - Registers (IC 1) */
#define REG_SPDIF_RX_CS_LEFT_10_IC_1_ADDR         0xF61A
#define REG_SPDIF_RX_CS_LEFT_10_IC_1_BYTE         0
#define REG_SPDIF_RX_CS_LEFT_10_IC_1_VALUE        0x210

/* SPDIF_RX_CS_LEFT_11  - Registers (IC 1) */
#define REG_SPDIF_RX_CS_LEFT_11_IC_1_ADDR         0xF61B
#define REG_SPDIF_RX_CS_LEFT_11_IC_1_BYTE         0
#define REG_SPDIF_RX_CS_LEFT_11_IC_1_VALUE        0x7A04

/* SPDIF_RX_CS_RIGHT_0  - Registers (IC 1) */
#define REG_SPDIF_RX_CS_RIGHT_0_IC_1_ADDR         0xF620
#define REG_SPDIF_RX_CS_RIGHT_0_IC_1_BYTE         0
#define REG_SPDIF_RX_CS_RIGHT_0_IC_1_VALUE        0x0

/* SPDIF_RX_CS_RIGHT_1  - Registers (IC 1) */
#define REG_SPDIF_RX_CS_RIGHT_1_IC_1_ADDR         0xF621
#define REG_SPDIF_RX_CS_RIGHT_1_IC_1_BYTE         0
#define REG_SPDIF_RX_CS_RIGHT_1_IC_1_VALUE        0x0

/* SPDIF_RX_CS_RIGHT_2  - Registers (IC 1) */
#define REG_SPDIF_RX_CS_RIGHT_2_IC_1_ADDR         0xF622
#define REG_SPDIF_RX_CS_RIGHT_2_IC_1_BYTE         0
#define REG_SPDIF_RX_CS_RIGHT_2_IC_1_VALUE        0x0

/* SPDIF_RX_CS_RIGHT_3  - Registers (IC 1) */
#define REG_SPDIF_RX_CS_RIGHT_3_IC_1_ADDR         0xF623
#define REG_SPDIF_RX_CS_RIGHT_3_IC_1_BYTE         0
#define REG_SPDIF_RX_CS_RIGHT_3_IC_1_VALUE        0x0

/* SPDIF_RX_CS_RIGHT_4  - Registers (IC 1) */
#define REG_SPDIF_RX_CS_RIGHT_4_IC_1_ADDR         0xF624
#define REG_SPDIF_RX_CS_RIGHT_4_IC_1_BYTE         0
#define REG_SPDIF_RX_CS_RIGHT_4_IC_1_VALUE        0x0

/* SPDIF_RX_CS_RIGHT_5  - Registers (IC 1) */
#define REG_SPDIF_RX_CS_RIGHT_5_IC_1_ADDR         0xF625
#define REG_SPDIF_RX_CS_RIGHT_5_IC_1_BYTE         0
#define REG_SPDIF_RX_CS_RIGHT_5_IC_1_VALUE        0x0

/* SPDIF_RX_CS_RIGHT_6  - Registers (IC 1) */
#define REG_SPDIF_RX_CS_RIGHT_6_IC_1_ADDR         0xF626
#define REG_SPDIF_RX_CS_RIGHT_6_IC_1_BYTE         0
#define REG_SPDIF_RX_CS_RIGHT_6_IC_1_VALUE        0x0

/* SPDIF_RX_CS_RIGHT_7  - Registers (IC 1) */
#define REG_SPDIF_RX_CS_RIGHT_7_IC_1_ADDR         0xF627
#define REG_SPDIF_RX_CS_RIGHT_7_IC_1_BYTE         0
#define REG_SPDIF_RX_CS_RIGHT_7_IC_1_VALUE        0x0

/* SPDIF_RX_CS_RIGHT_8  - Registers (IC 1) */
#define REG_SPDIF_RX_CS_RIGHT_8_IC_1_ADDR         0xF628
#define REG_SPDIF_RX_CS_RIGHT_8_IC_1_BYTE         0
#define REG_SPDIF_RX_CS_RIGHT_8_IC_1_VALUE        0x0

/* SPDIF_RX_CS_RIGHT_9  - Registers (IC 1) */
#define REG_SPDIF_RX_CS_RIGHT_9_IC_1_ADDR         0xF629
#define REG_SPDIF_RX_CS_RIGHT_9_IC_1_BYTE         0
#define REG_SPDIF_RX_CS_RIGHT_9_IC_1_VALUE        0xB

/* SPDIF_RX_CS_RIGHT_10  - Registers (IC 1) */
#define REG_SPDIF_RX_CS_RIGHT_10_IC_1_ADDR        0xF62A
#define REG_SPDIF_RX_CS_RIGHT_10_IC_1_BYTE        0
#define REG_SPDIF_RX_CS_RIGHT_10_IC_1_VALUE       0x220

/* SPDIF_RX_CS_RIGHT_11  - Registers (IC 1) */
#define REG_SPDIF_RX_CS_RIGHT_11_IC_1_ADDR        0xF62B
#define REG_SPDIF_RX_CS_RIGHT_11_IC_1_BYTE        0
#define REG_SPDIF_RX_CS_RIGHT_11_IC_1_VALUE       0x7A04

/* SPDIF_RX_UD_LEFT_0  - Registers (IC 1) */
#define REG_SPDIF_RX_UD_LEFT_0_IC_1_ADDR          0xF630
#define REG_SPDIF_RX_UD_LEFT_0_IC_1_BYTE          0
#define REG_SPDIF_RX_UD_LEFT_0_IC_1_VALUE         0x0

/* SPDIF_RX_UD_LEFT_1  - Registers (IC 1) */
#define REG_SPDIF_RX_UD_LEFT_1_IC_1_ADDR          0xF631
#define REG_SPDIF_RX_UD_LEFT_1_IC_1_BYTE          0
#define REG_SPDIF_RX_UD_LEFT_1_IC_1_VALUE         0x0

/* SPDIF_RX_UD_LEFT_2  - Registers (IC 1) */
#define REG_SPDIF_RX_UD_LEFT_2_IC_1_ADDR          0xF632
#define REG_SPDIF_RX_UD_LEFT_2_IC_1_BYTE          0
#define REG_SPDIF_RX_UD_LEFT_2_IC_1_VALUE         0x0

/* SPDIF_RX_UD_LEFT_3  - Registers (IC 1) */
#define REG_SPDIF_RX_UD_LEFT_3_IC_1_ADDR          0xF633
#define REG_SPDIF_RX_UD_LEFT_3_IC_1_BYTE          0
#define REG_SPDIF_RX_UD_LEFT_3_IC_1_VALUE         0x0

/* SPDIF_RX_UD_LEFT_4  - Registers (IC 1) */
#define REG_SPDIF_RX_UD_LEFT_4_IC_1_ADDR          0xF634
#define REG_SPDIF_RX_UD_LEFT_4_IC_1_BYTE          0
#define REG_SPDIF_RX_UD_LEFT_4_IC_1_VALUE         0x0

/* SPDIF_RX_UD_LEFT_5  - Registers (IC 1) */
#define REG_SPDIF_RX_UD_LEFT_5_IC_1_ADDR          0xF635
#define REG_SPDIF_RX_UD_LEFT_5_IC_1_BYTE          0
#define REG_SPDIF_RX_UD_LEFT_5_IC_1_VALUE         0x0

/* SPDIF_RX_UD_LEFT_6  - Registers (IC 1) */
#define REG_SPDIF_RX_UD_LEFT_6_IC_1_ADDR          0xF636
#define REG_SPDIF_RX_UD_LEFT_6_IC_1_BYTE          0
#define REG_SPDIF_RX_UD_LEFT_6_IC_1_VALUE         0x0

/* SPDIF_RX_UD_LEFT_7  - Registers (IC 1) */
#define REG_SPDIF_RX_UD_LEFT_7_IC_1_ADDR          0xF637
#define REG_SPDIF_RX_UD_LEFT_7_IC_1_BYTE          0
#define REG_SPDIF_RX_UD_LEFT_7_IC_1_VALUE         0x0

/* SPDIF_RX_UD_LEFT_8  - Registers (IC 1) */
#define REG_SPDIF_RX_UD_LEFT_8_IC_1_ADDR          0xF638
#define REG_SPDIF_RX_UD_LEFT_8_IC_1_BYTE          0
#define REG_SPDIF_RX_UD_LEFT_8_IC_1_VALUE         0x0

/* SPDIF_RX_UD_LEFT_9  - Registers (IC 1) */
#define REG_SPDIF_RX_UD_LEFT_9_IC_1_ADDR          0xF639
#define REG_SPDIF_RX_UD_LEFT_9_IC_1_BYTE          0
#define REG_SPDIF_RX_UD_LEFT_9_IC_1_VALUE         0x0

/* SPDIF_RX_UD_LEFT_10  - Registers (IC 1) */
#define REG_SPDIF_RX_UD_LEFT_10_IC_1_ADDR         0xF63A
#define REG_SPDIF_RX_UD_LEFT_10_IC_1_BYTE         0
#define REG_SPDIF_RX_UD_LEFT_10_IC_1_VALUE        0x0

/* SPDIF_RX_UD_LEFT_11  - Registers (IC 1) */
#define REG_SPDIF_RX_UD_LEFT_11_IC_1_ADDR         0xF63B
#define REG_SPDIF_RX_UD_LEFT_11_IC_1_BYTE         0
#define REG_SPDIF_RX_UD_LEFT_11_IC_1_VALUE        0x0

/* SPDIF_RX_UD_RIGHT_0  - Registers (IC 1) */
#define REG_SPDIF_RX_UD_RIGHT_0_IC_1_ADDR         0xF640
#define REG_SPDIF_RX_UD_RIGHT_0_IC_1_BYTE         0
#define REG_SPDIF_RX_UD_RIGHT_0_IC_1_VALUE        0x0

/* SPDIF_RX_UD_RIGHT_1  - Registers (IC 1) */
#define REG_SPDIF_RX_UD_RIGHT_1_IC_1_ADDR         0xF641
#define REG_SPDIF_RX_UD_RIGHT_1_IC_1_BYTE         0
#define REG_SPDIF_RX_UD_RIGHT_1_IC_1_VALUE        0x0

/* SPDIF_RX_UD_RIGHT_2  - Registers (IC 1) */
#define REG_SPDIF_RX_UD_RIGHT_2_IC_1_ADDR         0xF642
#define REG_SPDIF_RX_UD_RIGHT_2_IC_1_BYTE         0
#define REG_SPDIF_RX_UD_RIGHT_2_IC_1_VALUE        0x0

/* SPDIF_RX_UD_RIGHT_3  - Registers (IC 1) */
#define REG_SPDIF_RX_UD_RIGHT_3_IC_1_ADDR         0xF643
#define REG_SPDIF_RX_UD_RIGHT_3_IC_1_BYTE         0
#define REG_SPDIF_RX_UD_RIGHT_3_IC_1_VALUE        0x0

/* SPDIF_RX_UD_RIGHT_4  - Registers (IC 1) */
#define REG_SPDIF_RX_UD_RIGHT_4_IC_1_ADDR         0xF644
#define REG_SPDIF_RX_UD_RIGHT_4_IC_1_BYTE         0
#define REG_SPDIF_RX_UD_RIGHT_4_IC_1_VALUE        0x0

/* SPDIF_RX_UD_RIGHT_5  - Registers (IC 1) */
#define REG_SPDIF_RX_UD_RIGHT_5_IC_1_ADDR         0xF645
#define REG_SPDIF_RX_UD_RIGHT_5_IC_1_BYTE         0
#define REG_SPDIF_RX_UD_RIGHT_5_IC_1_VALUE        0x0

/* SPDIF_RX_UD_RIGHT_6  - Registers (IC 1) */
#define REG_SPDIF_RX_UD_RIGHT_6_IC_1_ADDR         0xF646
#define REG_SPDIF_RX_UD_RIGHT_6_IC_1_BYTE         0
#define REG_SPDIF_RX_UD_RIGHT_6_IC_1_VALUE        0x0

/* SPDIF_RX_UD_RIGHT_7  - Registers (IC 1) */
#define REG_SPDIF_RX_UD_RIGHT_7_IC_1_ADDR         0xF647
#define REG_SPDIF_RX_UD_RIGHT_7_IC_1_BYTE         0
#define REG_SPDIF_RX_UD_RIGHT_7_IC_1_VALUE        0x0

/* SPDIF_RX_UD_RIGHT_8  - Registers (IC 1) */
#define REG_SPDIF_RX_UD_RIGHT_8_IC_1_ADDR         0xF648
#define REG_SPDIF_RX_UD_RIGHT_8_IC_1_BYTE         0
#define REG_SPDIF_RX_UD_RIGHT_8_IC_1_VALUE        0x0

/* SPDIF_RX_UD_RIGHT_9  - Registers (IC 1) */
#define REG_SPDIF_RX_UD_RIGHT_9_IC_1_ADDR         0xF649
#define REG_SPDIF_RX_UD_RIGHT_9_IC_1_BYTE         0
#define REG_SPDIF_RX_UD_RIGHT_9_IC_1_VALUE        0x0

/* SPDIF_RX_UD_RIGHT_10  - Registers (IC 1) */
#define REG_SPDIF_RX_UD_RIGHT_10_IC_1_ADDR        0xF64A
#define REG_SPDIF_RX_UD_RIGHT_10_IC_1_BYTE        0
#define REG_SPDIF_RX_UD_RIGHT_10_IC_1_VALUE       0x0

/* SPDIF_RX_UD_RIGHT_11  - Registers (IC 1) */
#define REG_SPDIF_RX_UD_RIGHT_11_IC_1_ADDR        0xF64B
#define REG_SPDIF_RX_UD_RIGHT_11_IC_1_BYTE        0
#define REG_SPDIF_RX_UD_RIGHT_11_IC_1_VALUE       0x0

/* SPDIF_RX_VB_LEFT_0  - Registers (IC 1) */
#define REG_SPDIF_RX_VB_LEFT_0_IC_1_ADDR          0xF650
#define REG_SPDIF_RX_VB_LEFT_0_IC_1_BYTE          0
#define REG_SPDIF_RX_VB_LEFT_0_IC_1_VALUE         0x0

/* SPDIF_RX_VB_LEFT_1  - Registers (IC 1) */
#define REG_SPDIF_RX_VB_LEFT_1_IC_1_ADDR          0xF651
#define REG_SPDIF_RX_VB_LEFT_1_IC_1_BYTE          0
#define REG_SPDIF_RX_VB_LEFT_1_IC_1_VALUE         0x0

/* SPDIF_RX_VB_LEFT_2  - Registers (IC 1) */
#define REG_SPDIF_RX_VB_LEFT_2_IC_1_ADDR          0xF652
#define REG_SPDIF_RX_VB_LEFT_2_IC_1_BYTE          0
#define REG_SPDIF_RX_VB_LEFT_2_IC_1_VALUE         0x0

/* SPDIF_RX_VB_LEFT_3  - Registers (IC 1) */
#define REG_SPDIF_RX_VB_LEFT_3_IC_1_ADDR          0xF653
#define REG_SPDIF_RX_VB_LEFT_3_IC_1_BYTE          0
#define REG_SPDIF_RX_VB_LEFT_3_IC_1_VALUE         0x0

/* SPDIF_RX_VB_LEFT_4  - Registers (IC 1) */
#define REG_SPDIF_RX_VB_LEFT_4_IC_1_ADDR          0xF654
#define REG_SPDIF_RX_VB_LEFT_4_IC_1_BYTE          0
#define REG_SPDIF_RX_VB_LEFT_4_IC_1_VALUE         0x0

/* SPDIF_RX_VB_LEFT_5  - Registers (IC 1) */
#define REG_SPDIF_RX_VB_LEFT_5_IC_1_ADDR          0xF655
#define REG_SPDIF_RX_VB_LEFT_5_IC_1_BYTE          0
#define REG_SPDIF_RX_VB_LEFT_5_IC_1_VALUE         0x0

/* SPDIF_RX_VB_LEFT_6  - Registers (IC 1) */
#define REG_SPDIF_RX_VB_LEFT_6_IC_1_ADDR          0xF656
#define REG_SPDIF_RX_VB_LEFT_6_IC_1_BYTE          0
#define REG_SPDIF_RX_VB_LEFT_6_IC_1_VALUE         0x0

/* SPDIF_RX_VB_LEFT_7  - Registers (IC 1) */
#define REG_SPDIF_RX_VB_LEFT_7_IC_1_ADDR          0xF657
#define REG_SPDIF_RX_VB_LEFT_7_IC_1_BYTE          0
#define REG_SPDIF_RX_VB_LEFT_7_IC_1_VALUE         0x0

/* SPDIF_RX_VB_LEFT_8  - Registers (IC 1) */
#define REG_SPDIF_RX_VB_LEFT_8_IC_1_ADDR          0xF658
#define REG_SPDIF_RX_VB_LEFT_8_IC_1_BYTE          0
#define REG_SPDIF_RX_VB_LEFT_8_IC_1_VALUE         0x0

/* SPDIF_RX_VB_LEFT_9  - Registers (IC 1) */
#define REG_SPDIF_RX_VB_LEFT_9_IC_1_ADDR          0xF659
#define REG_SPDIF_RX_VB_LEFT_9_IC_1_BYTE          0
#define REG_SPDIF_RX_VB_LEFT_9_IC_1_VALUE         0x0

/* SPDIF_RX_VB_LEFT_10  - Registers (IC 1) */
#define REG_SPDIF_RX_VB_LEFT_10_IC_1_ADDR         0xF65A
#define REG_SPDIF_RX_VB_LEFT_10_IC_1_BYTE         0
#define REG_SPDIF_RX_VB_LEFT_10_IC_1_VALUE        0x0

/* SPDIF_RX_VB_LEFT_11  - Registers (IC 1) */
#define REG_SPDIF_RX_VB_LEFT_11_IC_1_ADDR         0xF65B
#define REG_SPDIF_RX_VB_LEFT_11_IC_1_BYTE         0
#define REG_SPDIF_RX_VB_LEFT_11_IC_1_VALUE        0x0

/* SPDIF_RX_VB_RIGHT_0  - Registers (IC 1) */
#define REG_SPDIF_RX_VB_RIGHT_0_IC_1_ADDR         0xF660
#define REG_SPDIF_RX_VB_RIGHT_0_IC_1_BYTE         0
#define REG_SPDIF_RX_VB_RIGHT_0_IC_1_VALUE        0x0

/* SPDIF_RX_VB_RIGHT_1  - Registers (IC 1) */
#define REG_SPDIF_RX_VB_RIGHT_1_IC_1_ADDR         0xF661
#define REG_SPDIF_RX_VB_RIGHT_1_IC_1_BYTE         0
#define REG_SPDIF_RX_VB_RIGHT_1_IC_1_VALUE        0x0

/* SPDIF_RX_VB_RIGHT_2  - Registers (IC 1) */
#define REG_SPDIF_RX_VB_RIGHT_2_IC_1_ADDR         0xF662
#define REG_SPDIF_RX_VB_RIGHT_2_IC_1_BYTE         0
#define REG_SPDIF_RX_VB_RIGHT_2_IC_1_VALUE        0x0

/* SPDIF_RX_VB_RIGHT_3  - Registers (IC 1) */
#define REG_SPDIF_RX_VB_RIGHT_3_IC_1_ADDR         0xF663
#define REG_SPDIF_RX_VB_RIGHT_3_IC_1_BYTE         0
#define REG_SPDIF_RX_VB_RIGHT_3_IC_1_VALUE        0x0

/* SPDIF_RX_VB_RIGHT_4  - Registers (IC 1) */
#define REG_SPDIF_RX_VB_RIGHT_4_IC_1_ADDR         0xF664
#define REG_SPDIF_RX_VB_RIGHT_4_IC_1_BYTE         0
#define REG_SPDIF_RX_VB_RIGHT_4_IC_1_VALUE        0x0

/* SPDIF_RX_VB_RIGHT_5  - Registers (IC 1) */
#define REG_SPDIF_RX_VB_RIGHT_5_IC_1_ADDR         0xF665
#define REG_SPDIF_RX_VB_RIGHT_5_IC_1_BYTE         0
#define REG_SPDIF_RX_VB_RIGHT_5_IC_1_VALUE        0x0

/* SPDIF_RX_VB_RIGHT_6  - Registers (IC 1) */
#define REG_SPDIF_RX_VB_RIGHT_6_IC_1_ADDR         0xF666
#define REG_SPDIF_RX_VB_RIGHT_6_IC_1_BYTE         0
#define REG_SPDIF_RX_VB_RIGHT_6_IC_1_VALUE        0x0

/* SPDIF_RX_VB_RIGHT_7  - Registers (IC 1) */
#define REG_SPDIF_RX_VB_RIGHT_7_IC_1_ADDR         0xF667
#define REG_SPDIF_RX_VB_RIGHT_7_IC_1_BYTE         0
#define REG_SPDIF_RX_VB_RIGHT_7_IC_1_VALUE        0x0

/* SPDIF_RX_VB_RIGHT_8  - Registers (IC 1) */
#define REG_SPDIF_RX_VB_RIGHT_8_IC_1_ADDR         0xF668
#define REG_SPDIF_RX_VB_RIGHT_8_IC_1_BYTE         0
#define REG_SPDIF_RX_VB_RIGHT_8_IC_1_VALUE        0x0

/* SPDIF_RX_VB_RIGHT_9  - Registers (IC 1) */
#define REG_SPDIF_RX_VB_RIGHT_9_IC_1_ADDR         0xF669
#define REG_SPDIF_RX_VB_RIGHT_9_IC_1_BYTE         0
#define REG_SPDIF_RX_VB_RIGHT_9_IC_1_VALUE        0x0

/* SPDIF_RX_VB_RIGHT_10  - Registers (IC 1) */
#define REG_SPDIF_RX_VB_RIGHT_10_IC_1_ADDR        0xF66A
#define REG_SPDIF_RX_VB_RIGHT_10_IC_1_BYTE        0
#define REG_SPDIF_RX_VB_RIGHT_10_IC_1_VALUE       0x0

/* SPDIF_RX_VB_RIGHT_11  - Registers (IC 1) */
#define REG_SPDIF_RX_VB_RIGHT_11_IC_1_ADDR        0xF66B
#define REG_SPDIF_RX_VB_RIGHT_11_IC_1_BYTE        0
#define REG_SPDIF_RX_VB_RIGHT_11_IC_1_VALUE       0x0

/* SPDIF_RX_PB_LEFT_0  - Registers (IC 1) */
#define REG_SPDIF_RX_PB_LEFT_0_IC_1_ADDR          0xF670
#define REG_SPDIF_RX_PB_LEFT_0_IC_1_BYTE          0
#define REG_SPDIF_RX_PB_LEFT_0_IC_1_VALUE         0x0

/* SPDIF_RX_PB_LEFT_1  - Registers (IC 1) */
#define REG_SPDIF_RX_PB_LEFT_1_IC_1_ADDR          0xF671
#define REG_SPDIF_RX_PB_LEFT_1_IC_1_BYTE          0
#define REG_SPDIF_RX_PB_LEFT_1_IC_1_VALUE         0x0

/* SPDIF_RX_PB_LEFT_2  - Registers (IC 1) */
#define REG_SPDIF_RX_PB_LEFT_2_IC_1_ADDR          0xF672
#define REG_SPDIF_RX_PB_LEFT_2_IC_1_BYTE          0
#define REG_SPDIF_RX_PB_LEFT_2_IC_1_VALUE         0x0

/* SPDIF_RX_PB_LEFT_3  - Registers (IC 1) */
#define REG_SPDIF_RX_PB_LEFT_3_IC_1_ADDR          0xF673
#define REG_SPDIF_RX_PB_LEFT_3_IC_1_BYTE          0
#define REG_SPDIF_RX_PB_LEFT_3_IC_1_VALUE         0x0

/* SPDIF_RX_PB_LEFT_4  - Registers (IC 1) */
#define REG_SPDIF_RX_PB_LEFT_4_IC_1_ADDR          0xF674
#define REG_SPDIF_RX_PB_LEFT_4_IC_1_BYTE          0
#define REG_SPDIF_RX_PB_LEFT_4_IC_1_VALUE         0x0

/* SPDIF_RX_PB_LEFT_5  - Registers (IC 1) */
#define REG_SPDIF_RX_PB_LEFT_5_IC_1_ADDR          0xF675
#define REG_SPDIF_RX_PB_LEFT_5_IC_1_BYTE          0
#define REG_SPDIF_RX_PB_LEFT_5_IC_1_VALUE         0x0

/* SPDIF_RX_PB_LEFT_6  - Registers (IC 1) */
#define REG_SPDIF_RX_PB_LEFT_6_IC_1_ADDR          0xF676
#define REG_SPDIF_RX_PB_LEFT_6_IC_1_BYTE          0
#define REG_SPDIF_RX_PB_LEFT_6_IC_1_VALUE         0x0

/* SPDIF_RX_PB_LEFT_7  - Registers (IC 1) */
#define REG_SPDIF_RX_PB_LEFT_7_IC_1_ADDR          0xF677
#define REG_SPDIF_RX_PB_LEFT_7_IC_1_BYTE          0
#define REG_SPDIF_RX_PB_LEFT_7_IC_1_VALUE         0x0

/* SPDIF_RX_PB_LEFT_8  - Registers (IC 1) */
#define REG_SPDIF_RX_PB_LEFT_8_IC_1_ADDR          0xF678
#define REG_SPDIF_RX_PB_LEFT_8_IC_1_BYTE          0
#define REG_SPDIF_RX_PB_LEFT_8_IC_1_VALUE         0x0

/* SPDIF_RX_PB_LEFT_9  - Registers (IC 1) */
#define REG_SPDIF_RX_PB_LEFT_9_IC_1_ADDR          0xF679
#define REG_SPDIF_RX_PB_LEFT_9_IC_1_BYTE          0
#define REG_SPDIF_RX_PB_LEFT_9_IC_1_VALUE         0xB

/* SPDIF_RX_PB_LEFT_10  - Registers (IC 1) */
#define REG_SPDIF_RX_PB_LEFT_10_IC_1_ADDR         0xF67A
#define REG_SPDIF_RX_PB_LEFT_10_IC_1_BYTE         0
#define REG_SPDIF_RX_PB_LEFT_10_IC_1_VALUE        0x210

/* SPDIF_RX_PB_LEFT_11  - Registers (IC 1) */
#define REG_SPDIF_RX_PB_LEFT_11_IC_1_ADDR         0xF67B
#define REG_SPDIF_RX_PB_LEFT_11_IC_1_BYTE         0
#define REG_SPDIF_RX_PB_LEFT_11_IC_1_VALUE        0x7A04

/* SPDIF_RX_PB_RIGHT_0  - Registers (IC 1) */
#define REG_SPDIF_RX_PB_RIGHT_0_IC_1_ADDR         0xF680
#define REG_SPDIF_RX_PB_RIGHT_0_IC_1_BYTE         0
#define REG_SPDIF_RX_PB_RIGHT_0_IC_1_VALUE        0x0

/* SPDIF_RX_PB_RIGHT_1  - Registers (IC 1) */
#define REG_SPDIF_RX_PB_RIGHT_1_IC_1_ADDR         0xF681
#define REG_SPDIF_RX_PB_RIGHT_1_IC_1_BYTE         0
#define REG_SPDIF_RX_PB_RIGHT_1_IC_1_VALUE        0x0

/* SPDIF_RX_PB_RIGHT_2  - Registers (IC 1) */
#define REG_SPDIF_RX_PB_RIGHT_2_IC_1_ADDR         0xF682
#define REG_SPDIF_RX_PB_RIGHT_2_IC_1_BYTE         0
#define REG_SPDIF_RX_PB_RIGHT_2_IC_1_VALUE        0x0

/* SPDIF_RX_PB_RIGHT_3  - Registers (IC 1) */
#define REG_SPDIF_RX_PB_RIGHT_3_IC_1_ADDR         0xF683
#define REG_SPDIF_RX_PB_RIGHT_3_IC_1_BYTE         0
#define REG_SPDIF_RX_PB_RIGHT_3_IC_1_VALUE        0x0

/* SPDIF_RX_PB_RIGHT_4  - Registers (IC 1) */
#define REG_SPDIF_RX_PB_RIGHT_4_IC_1_ADDR         0xF684
#define REG_SPDIF_RX_PB_RIGHT_4_IC_1_BYTE         0
#define REG_SPDIF_RX_PB_RIGHT_4_IC_1_VALUE        0x0

/* SPDIF_RX_PB_RIGHT_5  - Registers (IC 1) */
#define REG_SPDIF_RX_PB_RIGHT_5_IC_1_ADDR         0xF685
#define REG_SPDIF_RX_PB_RIGHT_5_IC_1_BYTE         0
#define REG_SPDIF_RX_PB_RIGHT_5_IC_1_VALUE        0x0

/* SPDIF_RX_PB_RIGHT_6  - Registers (IC 1) */
#define REG_SPDIF_RX_PB_RIGHT_6_IC_1_ADDR         0xF686
#define REG_SPDIF_RX_PB_RIGHT_6_IC_1_BYTE         0
#define REG_SPDIF_RX_PB_RIGHT_6_IC_1_VALUE        0x0

/* SPDIF_RX_PB_RIGHT_7  - Registers (IC 1) */
#define REG_SPDIF_RX_PB_RIGHT_7_IC_1_ADDR         0xF687
#define REG_SPDIF_RX_PB_RIGHT_7_IC_1_BYTE         0
#define REG_SPDIF_RX_PB_RIGHT_7_IC_1_VALUE        0x0

/* SPDIF_RX_PB_RIGHT_8  - Registers (IC 1) */
#define REG_SPDIF_RX_PB_RIGHT_8_IC_1_ADDR         0xF688
#define REG_SPDIF_RX_PB_RIGHT_8_IC_1_BYTE         0
#define REG_SPDIF_RX_PB_RIGHT_8_IC_1_VALUE        0x0

/* SPDIF_RX_PB_RIGHT_9  - Registers (IC 1) */
#define REG_SPDIF_RX_PB_RIGHT_9_IC_1_ADDR         0xF689
#define REG_SPDIF_RX_PB_RIGHT_9_IC_1_BYTE         0
#define REG_SPDIF_RX_PB_RIGHT_9_IC_1_VALUE        0xB

/* SPDIF_RX_PB_RIGHT_10  - Registers (IC 1) */
#define REG_SPDIF_RX_PB_RIGHT_10_IC_1_ADDR        0xF68A
#define REG_SPDIF_RX_PB_RIGHT_10_IC_1_BYTE        0
#define REG_SPDIF_RX_PB_RIGHT_10_IC_1_VALUE       0x220

/* SPDIF_RX_PB_RIGHT_11  - Registers (IC 1) */
#define REG_SPDIF_RX_PB_RIGHT_11_IC_1_ADDR        0xF68B
#define REG_SPDIF_RX_PB_RIGHT_11_IC_1_BYTE        0
#define REG_SPDIF_RX_PB_RIGHT_11_IC_1_VALUE       0x7A04

/* SPDIF_TX_EN  - Registers (IC 1) */
#define REG_SPDIF_TX_EN_IC_1_ADDR                 0xF690
#define REG_SPDIF_TX_EN_IC_1_BYTE                 2
#define REG_SPDIF_TX_EN_IC_1_VALUE                0x1

/* SPDIF_TX_CTRL  - Registers (IC 1) */
#define REG_SPDIF_TX_CTRL_IC_1_ADDR               0xF691
#define REG_SPDIF_TX_CTRL_IC_1_BYTE               2
#define REG_SPDIF_TX_CTRL_IC_1_VALUE              0x0

/* SPDIF_TX_AUXBIT_SOURCE  - Registers (IC 1) */
#define REG_SPDIF_TX_AUXBIT_SOURCE_IC_1_ADDR      0xF69F
#define REG_SPDIF_TX_AUXBIT_SOURCE_IC_1_BYTE      2
#define REG_SPDIF_TX_AUXBIT_SOURCE_IC_1_VALUE     0x0

/* SPDIF_TX_CS_LEFT_0  - Registers (IC 1) */
#define REG_SPDIF_TX_CS_LEFT_0_IC_1_ADDR          0xF6A0
#define REG_SPDIF_TX_CS_LEFT_0_IC_1_BYTE          2
#define REG_SPDIF_TX_CS_LEFT_0_IC_1_VALUE         0x0

/* SPDIF_TX_CS_LEFT_1  - Registers (IC 1) */
#define REG_SPDIF_TX_CS_LEFT_1_IC_1_ADDR          0xF6A1
#define REG_SPDIF_TX_CS_LEFT_1_IC_1_BYTE          2
#define REG_SPDIF_TX_CS_LEFT_1_IC_1_VALUE         0x0

/* SPDIF_TX_CS_LEFT_2  - Registers (IC 1) */
#define REG_SPDIF_TX_CS_LEFT_2_IC_1_ADDR          0xF6A2
#define REG_SPDIF_TX_CS_LEFT_2_IC_1_BYTE          2
#define REG_SPDIF_TX_CS_LEFT_2_IC_1_VALUE         0x0

/* SPDIF_TX_CS_LEFT_3  - Registers (IC 1) */
#define REG_SPDIF_TX_CS_LEFT_3_IC_1_ADDR          0xF6A3
#define REG_SPDIF_TX_CS_LEFT_3_IC_1_BYTE          2
#define REG_SPDIF_TX_CS_LEFT_3_IC_1_VALUE         0x0

/* SPDIF_TX_CS_LEFT_4  - Registers (IC 1) */
#define REG_SPDIF_TX_CS_LEFT_4_IC_1_ADDR          0xF6A4
#define REG_SPDIF_TX_CS_LEFT_4_IC_1_BYTE          2
#define REG_SPDIF_TX_CS_LEFT_4_IC_1_VALUE         0x0

/* SPDIF_TX_CS_LEFT_5  - Registers (IC 1) */
#define REG_SPDIF_TX_CS_LEFT_5_IC_1_ADDR          0xF6A5
#define REG_SPDIF_TX_CS_LEFT_5_IC_1_BYTE          2
#define REG_SPDIF_TX_CS_LEFT_5_IC_1_VALUE         0x0

/* SPDIF_TX_CS_LEFT_6  - Registers (IC 1) */
#define REG_SPDIF_TX_CS_LEFT_6_IC_1_ADDR          0xF6A6
#define REG_SPDIF_TX_CS_LEFT_6_IC_1_BYTE          2
#define REG_SPDIF_TX_CS_LEFT_6_IC_1_VALUE         0x0

/* SPDIF_TX_CS_LEFT_7  - Registers (IC 1) */
#define REG_SPDIF_TX_CS_LEFT_7_IC_1_ADDR          0xF6A7
#define REG_SPDIF_TX_CS_LEFT_7_IC_1_BYTE          2
#define REG_SPDIF_TX_CS_LEFT_7_IC_1_VALUE         0x0

/* SPDIF_TX_CS_LEFT_8  - Registers (IC 1) */
#define REG_SPDIF_TX_CS_LEFT_8_IC_1_ADDR          0xF6A8
#define REG_SPDIF_TX_CS_LEFT_8_IC_1_BYTE          2
#define REG_SPDIF_TX_CS_LEFT_8_IC_1_VALUE         0x0

/* SPDIF_TX_CS_LEFT_9  - Registers (IC 1) */
#define REG_SPDIF_TX_CS_LEFT_9_IC_1_ADDR          0xF6A9
#define REG_SPDIF_TX_CS_LEFT_9_IC_1_BYTE          2
#define REG_SPDIF_TX_CS_LEFT_9_IC_1_VALUE         0x0

/* SPDIF_TX_CS_LEFT_10  - Registers (IC 1) */
#define REG_SPDIF_TX_CS_LEFT_10_IC_1_ADDR         0xF6AA
#define REG_SPDIF_TX_CS_LEFT_10_IC_1_BYTE         2
#define REG_SPDIF_TX_CS_LEFT_10_IC_1_VALUE        0x0

/* SPDIF_TX_CS_LEFT_11  - Registers (IC 1) */
#define REG_SPDIF_TX_CS_LEFT_11_IC_1_ADDR         0xF6AB
#define REG_SPDIF_TX_CS_LEFT_11_IC_1_BYTE         2
#define REG_SPDIF_TX_CS_LEFT_11_IC_1_VALUE        0x0

/* SPDIF_TX_CS_RIGHT_0  - Registers (IC 1) */
#define REG_SPDIF_TX_CS_RIGHT_0_IC_1_ADDR         0xF6B0
#define REG_SPDIF_TX_CS_RIGHT_0_IC_1_BYTE         2
#define REG_SPDIF_TX_CS_RIGHT_0_IC_1_VALUE        0x0

/* SPDIF_TX_CS_RIGHT_1  - Registers (IC 1) */
#define REG_SPDIF_TX_CS_RIGHT_1_IC_1_ADDR         0xF6B1
#define REG_SPDIF_TX_CS_RIGHT_1_IC_1_BYTE         2
#define REG_SPDIF_TX_CS_RIGHT_1_IC_1_VALUE        0x0

/* SPDIF_TX_CS_RIGHT_2  - Registers (IC 1) */
#define REG_SPDIF_TX_CS_RIGHT_2_IC_1_ADDR         0xF6B2
#define REG_SPDIF_TX_CS_RIGHT_2_IC_1_BYTE         2
#define REG_SPDIF_TX_CS_RIGHT_2_IC_1_VALUE        0x0

/* SPDIF_TX_CS_RIGHT_3  - Registers (IC 1) */
#define REG_SPDIF_TX_CS_RIGHT_3_IC_1_ADDR         0xF6B3
#define REG_SPDIF_TX_CS_RIGHT_3_IC_1_BYTE         2
#define REG_SPDIF_TX_CS_RIGHT_3_IC_1_VALUE        0x0

/* SPDIF_TX_CS_RIGHT_4  - Registers (IC 1) */
#define REG_SPDIF_TX_CS_RIGHT_4_IC_1_ADDR         0xF6B4
#define REG_SPDIF_TX_CS_RIGHT_4_IC_1_BYTE         2
#define REG_SPDIF_TX_CS_RIGHT_4_IC_1_VALUE        0x0

/* SPDIF_TX_CS_RIGHT_5  - Registers (IC 1) */
#define REG_SPDIF_TX_CS_RIGHT_5_IC_1_ADDR         0xF6B5
#define REG_SPDIF_TX_CS_RIGHT_5_IC_1_BYTE         2
#define REG_SPDIF_TX_CS_RIGHT_5_IC_1_VALUE        0x0

/* SPDIF_TX_CS_RIGHT_6  - Registers (IC 1) */
#define REG_SPDIF_TX_CS_RIGHT_6_IC_1_ADDR         0xF6B6
#define REG_SPDIF_TX_CS_RIGHT_6_IC_1_BYTE         2
#define REG_SPDIF_TX_CS_RIGHT_6_IC_1_VALUE        0x0

/* SPDIF_TX_CS_RIGHT_7  - Registers (IC 1) */
#define REG_SPDIF_TX_CS_RIGHT_7_IC_1_ADDR         0xF6B7
#define REG_SPDIF_TX_CS_RIGHT_7_IC_1_BYTE         2
#define REG_SPDIF_TX_CS_RIGHT_7_IC_1_VALUE        0x0

/* SPDIF_TX_CS_RIGHT_8  - Registers (IC 1) */
#define REG_SPDIF_TX_CS_RIGHT_8_IC_1_ADDR         0xF6B8
#define REG_SPDIF_TX_CS_RIGHT_8_IC_1_BYTE         2
#define REG_SPDIF_TX_CS_RIGHT_8_IC_1_VALUE        0x0

/* SPDIF_TX_CS_RIGHT_9  - Registers (IC 1) */
#define REG_SPDIF_TX_CS_RIGHT_9_IC_1_ADDR         0xF6B9
#define REG_SPDIF_TX_CS_RIGHT_9_IC_1_BYTE         2
#define REG_SPDIF_TX_CS_RIGHT_9_IC_1_VALUE        0x0

/* SPDIF_TX_CS_RIGHT_10  - Registers (IC 1) */
#define REG_SPDIF_TX_CS_RIGHT_10_IC_1_ADDR        0xF6BA
#define REG_SPDIF_TX_CS_RIGHT_10_IC_1_BYTE        2
#define REG_SPDIF_TX_CS_RIGHT_10_IC_1_VALUE       0x0

/* SPDIF_TX_CS_RIGHT_11  - Registers (IC 1) */
#define REG_SPDIF_TX_CS_RIGHT_11_IC_1_ADDR        0xF6BB
#define REG_SPDIF_TX_CS_RIGHT_11_IC_1_BYTE        2
#define REG_SPDIF_TX_CS_RIGHT_11_IC_1_VALUE       0x0

/* SPDIF_TX_UD_LEFT_0  - Registers (IC 1) */
#define REG_SPDIF_TX_UD_LEFT_0_IC_1_ADDR          0xF6C0
#define REG_SPDIF_TX_UD_LEFT_0_IC_1_BYTE          2
#define REG_SPDIF_TX_UD_LEFT_0_IC_1_VALUE         0x0

/* SPDIF_TX_UD_LEFT_1  - Registers (IC 1) */
#define REG_SPDIF_TX_UD_LEFT_1_IC_1_ADDR          0xF6C1
#define REG_SPDIF_TX_UD_LEFT_1_IC_1_BYTE          2
#define REG_SPDIF_TX_UD_LEFT_1_IC_1_VALUE         0x0

/* SPDIF_TX_UD_LEFT_2  - Registers (IC 1) */
#define REG_SPDIF_TX_UD_LEFT_2_IC_1_ADDR          0xF6C2
#define REG_SPDIF_TX_UD_LEFT_2_IC_1_BYTE          2
#define REG_SPDIF_TX_UD_LEFT_2_IC_1_VALUE         0x0

/* SPDIF_TX_UD_LEFT_3  - Registers (IC 1) */
#define REG_SPDIF_TX_UD_LEFT_3_IC_1_ADDR          0xF6C3
#define REG_SPDIF_TX_UD_LEFT_3_IC_1_BYTE          2
#define REG_SPDIF_TX_UD_LEFT_3_IC_1_VALUE         0x0

/* SPDIF_TX_UD_LEFT_4  - Registers (IC 1) */
#define REG_SPDIF_TX_UD_LEFT_4_IC_1_ADDR          0xF6C4
#define REG_SPDIF_TX_UD_LEFT_4_IC_1_BYTE          2
#define REG_SPDIF_TX_UD_LEFT_4_IC_1_VALUE         0x0

/* SPDIF_TX_UD_LEFT_5  - Registers (IC 1) */
#define REG_SPDIF_TX_UD_LEFT_5_IC_1_ADDR          0xF6C5
#define REG_SPDIF_TX_UD_LEFT_5_IC_1_BYTE          2
#define REG_SPDIF_TX_UD_LEFT_5_IC_1_VALUE         0x0

/* SPDIF_TX_UD_LEFT_6  - Registers (IC 1) */
#define REG_SPDIF_TX_UD_LEFT_6_IC_1_ADDR          0xF6C6
#define REG_SPDIF_TX_UD_LEFT_6_IC_1_BYTE          2
#define REG_SPDIF_TX_UD_LEFT_6_IC_1_VALUE         0x0

/* SPDIF_TX_UD_LEFT_7  - Registers (IC 1) */
#define REG_SPDIF_TX_UD_LEFT_7_IC_1_ADDR          0xF6C7
#define REG_SPDIF_TX_UD_LEFT_7_IC_1_BYTE          2
#define REG_SPDIF_TX_UD_LEFT_7_IC_1_VALUE         0x0

/* SPDIF_TX_UD_LEFT_8  - Registers (IC 1) */
#define REG_SPDIF_TX_UD_LEFT_8_IC_1_ADDR          0xF6C8
#define REG_SPDIF_TX_UD_LEFT_8_IC_1_BYTE          2
#define REG_SPDIF_TX_UD_LEFT_8_IC_1_VALUE         0x0

/* SPDIF_TX_UD_LEFT_9  - Registers (IC 1) */
#define REG_SPDIF_TX_UD_LEFT_9_IC_1_ADDR          0xF6C9
#define REG_SPDIF_TX_UD_LEFT_9_IC_1_BYTE          2
#define REG_SPDIF_TX_UD_LEFT_9_IC_1_VALUE         0x0

/* SPDIF_TX_UD_LEFT_10  - Registers (IC 1) */
#define REG_SPDIF_TX_UD_LEFT_10_IC_1_ADDR         0xF6CA
#define REG_SPDIF_TX_UD_LEFT_10_IC_1_BYTE         2
#define REG_SPDIF_TX_UD_LEFT_10_IC_1_VALUE        0x0

/* SPDIF_TX_UD_LEFT_11  - Registers (IC 1) */
#define REG_SPDIF_TX_UD_LEFT_11_IC_1_ADDR         0xF6CB
#define REG_SPDIF_TX_UD_LEFT_11_IC_1_BYTE         2
#define REG_SPDIF_TX_UD_LEFT_11_IC_1_VALUE        0x0

/* SPDIF_TX_UD_RIGHT_0  - Registers (IC 1) */
#define REG_SPDIF_TX_UD_RIGHT_0_IC_1_ADDR         0xF6D0
#define REG_SPDIF_TX_UD_RIGHT_0_IC_1_BYTE         2
#define REG_SPDIF_TX_UD_RIGHT_0_IC_1_VALUE        0x0

/* SPDIF_TX_UD_RIGHT_1  - Registers (IC 1) */
#define REG_SPDIF_TX_UD_RIGHT_1_IC_1_ADDR         0xF6D1
#define REG_SPDIF_TX_UD_RIGHT_1_IC_1_BYTE         2
#define REG_SPDIF_TX_UD_RIGHT_1_IC_1_VALUE        0x0

/* SPDIF_TX_UD_RIGHT_2  - Registers (IC 1) */
#define REG_SPDIF_TX_UD_RIGHT_2_IC_1_ADDR         0xF6D2
#define REG_SPDIF_TX_UD_RIGHT_2_IC_1_BYTE         2
#define REG_SPDIF_TX_UD_RIGHT_2_IC_1_VALUE        0x0

/* SPDIF_TX_UD_RIGHT_3  - Registers (IC 1) */
#define REG_SPDIF_TX_UD_RIGHT_3_IC_1_ADDR         0xF6D3
#define REG_SPDIF_TX_UD_RIGHT_3_IC_1_BYTE         2
#define REG_SPDIF_TX_UD_RIGHT_3_IC_1_VALUE        0x0

/* SPDIF_TX_UD_RIGHT_4  - Registers (IC 1) */
#define REG_SPDIF_TX_UD_RIGHT_4_IC_1_ADDR         0xF6D4
#define REG_SPDIF_TX_UD_RIGHT_4_IC_1_BYTE         2
#define REG_SPDIF_TX_UD_RIGHT_4_IC_1_VALUE        0x0

/* SPDIF_TX_UD_RIGHT_5  - Registers (IC 1) */
#define REG_SPDIF_TX_UD_RIGHT_5_IC_1_ADDR         0xF6D5
#define REG_SPDIF_TX_UD_RIGHT_5_IC_1_BYTE         2
#define REG_SPDIF_TX_UD_RIGHT_5_IC_1_VALUE        0x0

/* SPDIF_TX_UD_RIGHT_6  - Registers (IC 1) */
#define REG_SPDIF_TX_UD_RIGHT_6_IC_1_ADDR         0xF6D6
#define REG_SPDIF_TX_UD_RIGHT_6_IC_1_BYTE         2
#define REG_SPDIF_TX_UD_RIGHT_6_IC_1_VALUE        0x0

/* SPDIF_TX_UD_RIGHT_7  - Registers (IC 1) */
#define REG_SPDIF_TX_UD_RIGHT_7_IC_1_ADDR         0xF6D7
#define REG_SPDIF_TX_UD_RIGHT_7_IC_1_BYTE         2
#define REG_SPDIF_TX_UD_RIGHT_7_IC_1_VALUE        0x0

/* SPDIF_TX_UD_RIGHT_8  - Registers (IC 1) */
#define REG_SPDIF_TX_UD_RIGHT_8_IC_1_ADDR         0xF6D8
#define REG_SPDIF_TX_UD_RIGHT_8_IC_1_BYTE         2
#define REG_SPDIF_TX_UD_RIGHT_8_IC_1_VALUE        0x0

/* SPDIF_TX_UD_RIGHT_9  - Registers (IC 1) */
#define REG_SPDIF_TX_UD_RIGHT_9_IC_1_ADDR         0xF6D9
#define REG_SPDIF_TX_UD_RIGHT_9_IC_1_BYTE         2
#define REG_SPDIF_TX_UD_RIGHT_9_IC_1_VALUE        0x0

/* SPDIF_TX_UD_RIGHT_10  - Registers (IC 1) */
#define REG_SPDIF_TX_UD_RIGHT_10_IC_1_ADDR        0xF6DA
#define REG_SPDIF_TX_UD_RIGHT_10_IC_1_BYTE        2
#define REG_SPDIF_TX_UD_RIGHT_10_IC_1_VALUE       0x0

/* SPDIF_TX_UD_RIGHT_11  - Registers (IC 1) */
#define REG_SPDIF_TX_UD_RIGHT_11_IC_1_ADDR        0xF6DB
#define REG_SPDIF_TX_UD_RIGHT_11_IC_1_BYTE        2
#define REG_SPDIF_TX_UD_RIGHT_11_IC_1_VALUE       0x0

/* SPDIF_TX_VB_LEFT_0  - Registers (IC 1) */
#define REG_SPDIF_TX_VB_LEFT_0_IC_1_ADDR          0xF6E0
#define REG_SPDIF_TX_VB_LEFT_0_IC_1_BYTE          2
#define REG_SPDIF_TX_VB_LEFT_0_IC_1_VALUE         0x0

/* SPDIF_TX_VB_LEFT_1  - Registers (IC 1) */
#define REG_SPDIF_TX_VB_LEFT_1_IC_1_ADDR          0xF6E1
#define REG_SPDIF_TX_VB_LEFT_1_IC_1_BYTE          2
#define REG_SPDIF_TX_VB_LEFT_1_IC_1_VALUE         0x0

/* SPDIF_TX_VB_LEFT_2  - Registers (IC 1) */
#define REG_SPDIF_TX_VB_LEFT_2_IC_1_ADDR          0xF6E2
#define REG_SPDIF_TX_VB_LEFT_2_IC_1_BYTE          2
#define REG_SPDIF_TX_VB_LEFT_2_IC_1_VALUE         0x0

/* SPDIF_TX_VB_LEFT_3  - Registers (IC 1) */
#define REG_SPDIF_TX_VB_LEFT_3_IC_1_ADDR          0xF6E3
#define REG_SPDIF_TX_VB_LEFT_3_IC_1_BYTE          2
#define REG_SPDIF_TX_VB_LEFT_3_IC_1_VALUE         0x0

/* SPDIF_TX_VB_LEFT_4  - Registers (IC 1) */
#define REG_SPDIF_TX_VB_LEFT_4_IC_1_ADDR          0xF6E4
#define REG_SPDIF_TX_VB_LEFT_4_IC_1_BYTE          2
#define REG_SPDIF_TX_VB_LEFT_4_IC_1_VALUE         0x0

/* SPDIF_TX_VB_LEFT_5  - Registers (IC 1) */
#define REG_SPDIF_TX_VB_LEFT_5_IC_1_ADDR          0xF6E5
#define REG_SPDIF_TX_VB_LEFT_5_IC_1_BYTE          2
#define REG_SPDIF_TX_VB_LEFT_5_IC_1_VALUE         0x0

/* SPDIF_TX_VB_LEFT_6  - Registers (IC 1) */
#define REG_SPDIF_TX_VB_LEFT_6_IC_1_ADDR          0xF6E6
#define REG_SPDIF_TX_VB_LEFT_6_IC_1_BYTE          2
#define REG_SPDIF_TX_VB_LEFT_6_IC_1_VALUE         0x0

/* SPDIF_TX_VB_LEFT_7  - Registers (IC 1) */
#define REG_SPDIF_TX_VB_LEFT_7_IC_1_ADDR          0xF6E7
#define REG_SPDIF_TX_VB_LEFT_7_IC_1_BYTE          2
#define REG_SPDIF_TX_VB_LEFT_7_IC_1_VALUE         0x0

/* SPDIF_TX_VB_LEFT_8  - Registers (IC 1) */
#define REG_SPDIF_TX_VB_LEFT_8_IC_1_ADDR          0xF6E8
#define REG_SPDIF_TX_VB_LEFT_8_IC_1_BYTE          2
#define REG_SPDIF_TX_VB_LEFT_8_IC_1_VALUE         0x0

/* SPDIF_TX_VB_LEFT_9  - Registers (IC 1) */
#define REG_SPDIF_TX_VB_LEFT_9_IC_1_ADDR          0xF6E9
#define REG_SPDIF_TX_VB_LEFT_9_IC_1_BYTE          2
#define REG_SPDIF_TX_VB_LEFT_9_IC_1_VALUE         0x0

/* SPDIF_TX_VB_LEFT_10  - Registers (IC 1) */
#define REG_SPDIF_TX_VB_LEFT_10_IC_1_ADDR         0xF6EA
#define REG_SPDIF_TX_VB_LEFT_10_IC_1_BYTE         2
#define REG_SPDIF_TX_VB_LEFT_10_IC_1_VALUE        0x0

/* SPDIF_TX_VB_LEFT_11  - Registers (IC 1) */
#define REG_SPDIF_TX_VB_LEFT_11_IC_1_ADDR         0xF6EB
#define REG_SPDIF_TX_VB_LEFT_11_IC_1_BYTE         2
#define REG_SPDIF_TX_VB_LEFT_11_IC_1_VALUE        0x0

/* SPDIF_TX_VB_RIGHT_0  - Registers (IC 1) */
#define REG_SPDIF_TX_VB_RIGHT_0_IC_1_ADDR         0xF6F0
#define REG_SPDIF_TX_VB_RIGHT_0_IC_1_BYTE         2
#define REG_SPDIF_TX_VB_RIGHT_0_IC_1_VALUE        0x0

/* SPDIF_TX_VB_RIGHT_1  - Registers (IC 1) */
#define REG_SPDIF_TX_VB_RIGHT_1_IC_1_ADDR         0xF6F1
#define REG_SPDIF_TX_VB_RIGHT_1_IC_1_BYTE         2
#define REG_SPDIF_TX_VB_RIGHT_1_IC_1_VALUE        0x0

/* SPDIF_TX_VB_RIGHT_2  - Registers (IC 1) */
#define REG_SPDIF_TX_VB_RIGHT_2_IC_1_ADDR         0xF6F2
#define REG_SPDIF_TX_VB_RIGHT_2_IC_1_BYTE         2
#define REG_SPDIF_TX_VB_RIGHT_2_IC_1_VALUE        0x0

/* SPDIF_TX_VB_RIGHT_3  - Registers (IC 1) */
#define REG_SPDIF_TX_VB_RIGHT_3_IC_1_ADDR         0xF6F3
#define REG_SPDIF_TX_VB_RIGHT_3_IC_1_BYTE         2
#define REG_SPDIF_TX_VB_RIGHT_3_IC_1_VALUE        0x0

/* SPDIF_TX_VB_RIGHT_4  - Registers (IC 1) */
#define REG_SPDIF_TX_VB_RIGHT_4_IC_1_ADDR         0xF6F4
#define REG_SPDIF_TX_VB_RIGHT_4_IC_1_BYTE         2
#define REG_SPDIF_TX_VB_RIGHT_4_IC_1_VALUE        0x0

/* SPDIF_TX_VB_RIGHT_5  - Registers (IC 1) */
#define REG_SPDIF_TX_VB_RIGHT_5_IC_1_ADDR         0xF6F5
#define REG_SPDIF_TX_VB_RIGHT_5_IC_1_BYTE         2
#define REG_SPDIF_TX_VB_RIGHT_5_IC_1_VALUE        0x0

/* SPDIF_TX_VB_RIGHT_6  - Registers (IC 1) */
#define REG_SPDIF_TX_VB_RIGHT_6_IC_1_ADDR         0xF6F6
#define REG_SPDIF_TX_VB_RIGHT_6_IC_1_BYTE         2
#define REG_SPDIF_TX_VB_RIGHT_6_IC_1_VALUE        0x0

/* SPDIF_TX_VB_RIGHT_7  - Registers (IC 1) */
#define REG_SPDIF_TX_VB_RIGHT_7_IC_1_ADDR         0xF6F7
#define REG_SPDIF_TX_VB_RIGHT_7_IC_1_BYTE         2
#define REG_SPDIF_TX_VB_RIGHT_7_IC_1_VALUE        0x0

/* SPDIF_TX_VB_RIGHT_8  - Registers (IC 1) */
#define REG_SPDIF_TX_VB_RIGHT_8_IC_1_ADDR         0xF6F8
#define REG_SPDIF_TX_VB_RIGHT_8_IC_1_BYTE         2
#define REG_SPDIF_TX_VB_RIGHT_8_IC_1_VALUE        0x0

/* SPDIF_TX_VB_RIGHT_9  - Registers (IC 1) */
#define REG_SPDIF_TX_VB_RIGHT_9_IC_1_ADDR         0xF6F9
#define REG_SPDIF_TX_VB_RIGHT_9_IC_1_BYTE         2
#define REG_SPDIF_TX_VB_RIGHT_9_IC_1_VALUE        0x0

/* SPDIF_TX_VB_RIGHT_10  - Registers (IC 1) */
#define REG_SPDIF_TX_VB_RIGHT_10_IC_1_ADDR        0xF6FA
#define REG_SPDIF_TX_VB_RIGHT_10_IC_1_BYTE        2
#define REG_SPDIF_TX_VB_RIGHT_10_IC_1_VALUE       0x0

/* SPDIF_TX_VB_RIGHT_11  - Registers (IC 1) */
#define REG_SPDIF_TX_VB_RIGHT_11_IC_1_ADDR        0xF6FB
#define REG_SPDIF_TX_VB_RIGHT_11_IC_1_BYTE        2
#define REG_SPDIF_TX_VB_RIGHT_11_IC_1_VALUE       0x0

/* SPDIF_TX_PB_LEFT_0  - Registers (IC 1) */
#define REG_SPDIF_TX_PB_LEFT_0_IC_1_ADDR          0xF700
#define REG_SPDIF_TX_PB_LEFT_0_IC_1_BYTE          2
#define REG_SPDIF_TX_PB_LEFT_0_IC_1_VALUE         0x0

/* SPDIF_TX_PB_LEFT_1  - Registers (IC 1) */
#define REG_SPDIF_TX_PB_LEFT_1_IC_1_ADDR          0xF701
#define REG_SPDIF_TX_PB_LEFT_1_IC_1_BYTE          2
#define REG_SPDIF_TX_PB_LEFT_1_IC_1_VALUE         0x0

/* SPDIF_TX_PB_LEFT_2  - Registers (IC 1) */
#define REG_SPDIF_TX_PB_LEFT_2_IC_1_ADDR          0xF702
#define REG_SPDIF_TX_PB_LEFT_2_IC_1_BYTE          2
#define REG_SPDIF_TX_PB_LEFT_2_IC_1_VALUE         0x0

/* SPDIF_TX_PB_LEFT_3  - Registers (IC 1) */
#define REG_SPDIF_TX_PB_LEFT_3_IC_1_ADDR          0xF703
#define REG_SPDIF_TX_PB_LEFT_3_IC_1_BYTE          2
#define REG_SPDIF_TX_PB_LEFT_3_IC_1_VALUE         0x0

/* SPDIF_TX_PB_LEFT_4  - Registers (IC 1) */
#define REG_SPDIF_TX_PB_LEFT_4_IC_1_ADDR          0xF704
#define REG_SPDIF_TX_PB_LEFT_4_IC_1_BYTE          2
#define REG_SPDIF_TX_PB_LEFT_4_IC_1_VALUE         0x0

/* SPDIF_TX_PB_LEFT_5  - Registers (IC 1) */
#define REG_SPDIF_TX_PB_LEFT_5_IC_1_ADDR          0xF705
#define REG_SPDIF_TX_PB_LEFT_5_IC_1_BYTE          2
#define REG_SPDIF_TX_PB_LEFT_5_IC_1_VALUE         0x0

/* SPDIF_TX_PB_LEFT_6  - Registers (IC 1) */
#define REG_SPDIF_TX_PB_LEFT_6_IC_1_ADDR          0xF706
#define REG_SPDIF_TX_PB_LEFT_6_IC_1_BYTE          2
#define REG_SPDIF_TX_PB_LEFT_6_IC_1_VALUE         0x0

/* SPDIF_TX_PB_LEFT_7  - Registers (IC 1) */
#define REG_SPDIF_TX_PB_LEFT_7_IC_1_ADDR          0xF707
#define REG_SPDIF_TX_PB_LEFT_7_IC_1_BYTE          2
#define REG_SPDIF_TX_PB_LEFT_7_IC_1_VALUE         0x0

/* SPDIF_TX_PB_LEFT_8  - Registers (IC 1) */
#define REG_SPDIF_TX_PB_LEFT_8_IC_1_ADDR          0xF708
#define REG_SPDIF_TX_PB_LEFT_8_IC_1_BYTE          2
#define REG_SPDIF_TX_PB_LEFT_8_IC_1_VALUE         0x0

/* SPDIF_TX_PB_LEFT_9  - Registers (IC 1) */
#define REG_SPDIF_TX_PB_LEFT_9_IC_1_ADDR          0xF709
#define REG_SPDIF_TX_PB_LEFT_9_IC_1_BYTE          2
#define REG_SPDIF_TX_PB_LEFT_9_IC_1_VALUE         0x0

/* SPDIF_TX_PB_LEFT_10  - Registers (IC 1) */
#define REG_SPDIF_TX_PB_LEFT_10_IC_1_ADDR         0xF70A
#define REG_SPDIF_TX_PB_LEFT_10_IC_1_BYTE         2
#define REG_SPDIF_TX_PB_LEFT_10_IC_1_VALUE        0x0

/* SPDIF_TX_PB_LEFT_11  - Registers (IC 1) */
#define REG_SPDIF_TX_PB_LEFT_11_IC_1_ADDR         0xF70B
#define REG_SPDIF_TX_PB_LEFT_11_IC_1_BYTE         2
#define REG_SPDIF_TX_PB_LEFT_11_IC_1_VALUE        0x0

/* SPDIF_TX_PB_RIGHT_0  - Registers (IC 1) */
#define REG_SPDIF_TX_PB_RIGHT_0_IC_1_ADDR         0xF710
#define REG_SPDIF_TX_PB_RIGHT_0_IC_1_BYTE         2
#define REG_SPDIF_TX_PB_RIGHT_0_IC_1_VALUE        0x0

/* SPDIF_TX_PB_RIGHT_1  - Registers (IC 1) */
#define REG_SPDIF_TX_PB_RIGHT_1_IC_1_ADDR         0xF711
#define REG_SPDIF_TX_PB_RIGHT_1_IC_1_BYTE         2
#define REG_SPDIF_TX_PB_RIGHT_1_IC_1_VALUE        0x0

/* SPDIF_TX_PB_RIGHT_2  - Registers (IC 1) */
#define REG_SPDIF_TX_PB_RIGHT_2_IC_1_ADDR         0xF712
#define REG_SPDIF_TX_PB_RIGHT_2_IC_1_BYTE         2
#define REG_SPDIF_TX_PB_RIGHT_2_IC_1_VALUE        0x0

/* SPDIF_TX_PB_RIGHT_3  - Registers (IC 1) */
#define REG_SPDIF_TX_PB_RIGHT_3_IC_1_ADDR         0xF713
#define REG_SPDIF_TX_PB_RIGHT_3_IC_1_BYTE         2
#define REG_SPDIF_TX_PB_RIGHT_3_IC_1_VALUE        0x0

/* SPDIF_TX_PB_RIGHT_4  - Registers (IC 1) */
#define REG_SPDIF_TX_PB_RIGHT_4_IC_1_ADDR         0xF714
#define REG_SPDIF_TX_PB_RIGHT_4_IC_1_BYTE         2
#define REG_SPDIF_TX_PB_RIGHT_4_IC_1_VALUE        0x0

/* SPDIF_TX_PB_RIGHT_5  - Registers (IC 1) */
#define REG_SPDIF_TX_PB_RIGHT_5_IC_1_ADDR         0xF715
#define REG_SPDIF_TX_PB_RIGHT_5_IC_1_BYTE         2
#define REG_SPDIF_TX_PB_RIGHT_5_IC_1_VALUE        0x0

/* SPDIF_TX_PB_RIGHT_6  - Registers (IC 1) */
#define REG_SPDIF_TX_PB_RIGHT_6_IC_1_ADDR         0xF716
#define REG_SPDIF_TX_PB_RIGHT_6_IC_1_BYTE         2
#define REG_SPDIF_TX_PB_RIGHT_6_IC_1_VALUE        0x0

/* SPDIF_TX_PB_RIGHT_7  - Registers (IC 1) */
#define REG_SPDIF_TX_PB_RIGHT_7_IC_1_ADDR         0xF717
#define REG_SPDIF_TX_PB_RIGHT_7_IC_1_BYTE         2
#define REG_SPDIF_TX_PB_RIGHT_7_IC_1_VALUE        0x0

/* SPDIF_TX_PB_RIGHT_8  - Registers (IC 1) */
#define REG_SPDIF_TX_PB_RIGHT_8_IC_1_ADDR         0xF718
#define REG_SPDIF_TX_PB_RIGHT_8_IC_1_BYTE         2
#define REG_SPDIF_TX_PB_RIGHT_8_IC_1_VALUE        0x0

/* SPDIF_TX_PB_RIGHT_9  - Registers (IC 1) */
#define REG_SPDIF_TX_PB_RIGHT_9_IC_1_ADDR         0xF719
#define REG_SPDIF_TX_PB_RIGHT_9_IC_1_BYTE         2
#define REG_SPDIF_TX_PB_RIGHT_9_IC_1_VALUE        0x0

/* SPDIF_TX_PB_RIGHT_10  - Registers (IC 1) */
#define REG_SPDIF_TX_PB_RIGHT_10_IC_1_ADDR        0xF71A
#define REG_SPDIF_TX_PB_RIGHT_10_IC_1_BYTE        2
#define REG_SPDIF_TX_PB_RIGHT_10_IC_1_VALUE       0x0

/* SPDIF_TX_PB_RIGHT_11  - Registers (IC 1) */
#define REG_SPDIF_TX_PB_RIGHT_11_IC_1_ADDR        0xF71B
#define REG_SPDIF_TX_PB_RIGHT_11_IC_1_BYTE        2
#define REG_SPDIF_TX_PB_RIGHT_11_IC_1_VALUE       0x0

/* BCLK_IN0_PIN  - Registers (IC 1) */
#define REG_BCLK_IN0_PIN_IC_1_ADDR                0xF780
#define REG_BCLK_IN0_PIN_IC_1_BYTE                2
#define REG_BCLK_IN0_PIN_IC_1_VALUE               0x18

/* BCLK_IN1_PIN  - Registers (IC 1) */
#define REG_BCLK_IN1_PIN_IC_1_ADDR                0xF781
#define REG_BCLK_IN1_PIN_IC_1_BYTE                2
#define REG_BCLK_IN1_PIN_IC_1_VALUE               0x18

/* BCLK_IN2_PIN  - Registers (IC 1) */
#define REG_BCLK_IN2_PIN_IC_1_ADDR                0xF782
#define REG_BCLK_IN2_PIN_IC_1_BYTE                2
#define REG_BCLK_IN2_PIN_IC_1_VALUE               0x18

/* BCLK_IN3_PIN  - Registers (IC 1) */
#define REG_BCLK_IN3_PIN_IC_1_ADDR                0xF783
#define REG_BCLK_IN3_PIN_IC_1_BYTE                2
#define REG_BCLK_IN3_PIN_IC_1_VALUE               0x18

/* BCLK_OUT0_PIN  - Registers (IC 1) */
#define REG_BCLK_OUT0_PIN_IC_1_ADDR               0xF784
#define REG_BCLK_OUT0_PIN_IC_1_BYTE               2
#define REG_BCLK_OUT0_PIN_IC_1_VALUE              0x18

/* BCLK_OUT1_PIN  - Registers (IC 1) */
#define REG_BCLK_OUT1_PIN_IC_1_ADDR               0xF785
#define REG_BCLK_OUT1_PIN_IC_1_BYTE               2
#define REG_BCLK_OUT1_PIN_IC_1_VALUE              0x18

/* BCLK_OUT2_PIN  - Registers (IC 1) */
#define REG_BCLK_OUT2_PIN_IC_1_ADDR               0xF786
#define REG_BCLK_OUT2_PIN_IC_1_BYTE               2
#define REG_BCLK_OUT2_PIN_IC_1_VALUE              0x18

/* BCLK_OUT3_PIN  - Registers (IC 1) */
#define REG_BCLK_OUT3_PIN_IC_1_ADDR               0xF787
#define REG_BCLK_OUT3_PIN_IC_1_BYTE               2
#define REG_BCLK_OUT3_PIN_IC_1_VALUE              0x18

/* LRCLK_IN0_PIN  - Registers (IC 1) */
#define REG_LRCLK_IN0_PIN_IC_1_ADDR               0xF788
#define REG_LRCLK_IN0_PIN_IC_1_BYTE               2
#define REG_LRCLK_IN0_PIN_IC_1_VALUE              0x18

/* LRCLK_IN1_PIN  - Registers (IC 1) */
#define REG_LRCLK_IN1_PIN_IC_1_ADDR               0xF789
#define REG_LRCLK_IN1_PIN_IC_1_BYTE               2
#define REG_LRCLK_IN1_PIN_IC_1_VALUE              0x18

/* LRCLK_IN2_PIN  - Registers (IC 1) */
#define REG_LRCLK_IN2_PIN_IC_1_ADDR               0xF78A
#define REG_LRCLK_IN2_PIN_IC_1_BYTE               2
#define REG_LRCLK_IN2_PIN_IC_1_VALUE              0x18

/* LRCLK_IN3_PIN  - Registers (IC 1) */
#define REG_LRCLK_IN3_PIN_IC_1_ADDR               0xF78B
#define REG_LRCLK_IN3_PIN_IC_1_BYTE               2
#define REG_LRCLK_IN3_PIN_IC_1_VALUE              0x18

/* LRCLK_OUT0_PIN  - Registers (IC 1) */
#define REG_LRCLK_OUT0_PIN_IC_1_ADDR              0xF78C
#define REG_LRCLK_OUT0_PIN_IC_1_BYTE              2
#define REG_LRCLK_OUT0_PIN_IC_1_VALUE             0x18

/* LRCLK_OUT1_PIN  - Registers (IC 1) */
#define REG_LRCLK_OUT1_PIN_IC_1_ADDR              0xF78D
#define REG_LRCLK_OUT1_PIN_IC_1_BYTE              2
#define REG_LRCLK_OUT1_PIN_IC_1_VALUE             0x18

/* LRCLK_OUT2_PIN  - Registers (IC 1) */
#define REG_LRCLK_OUT2_PIN_IC_1_ADDR              0xF78E
#define REG_LRCLK_OUT2_PIN_IC_1_BYTE              2
#define REG_LRCLK_OUT2_PIN_IC_1_VALUE             0x18

/* LRCLK_OUT3_PIN  - Registers (IC 1) */
#define REG_LRCLK_OUT3_PIN_IC_1_ADDR              0xF78F
#define REG_LRCLK_OUT3_PIN_IC_1_BYTE              2
#define REG_LRCLK_OUT3_PIN_IC_1_VALUE             0x18

/* SDATA_IN0_PIN  - Registers (IC 1) */
#define REG_SDATA_IN0_PIN_IC_1_ADDR               0xF790
#define REG_SDATA_IN0_PIN_IC_1_BYTE               2
#define REG_SDATA_IN0_PIN_IC_1_VALUE              0x18

/* SDATA_IN1_PIN  - Registers (IC 1) */
#define REG_SDATA_IN1_PIN_IC_1_ADDR               0xF791
#define REG_SDATA_IN1_PIN_IC_1_BYTE               2
#define REG_SDATA_IN1_PIN_IC_1_VALUE              0x18

/* SDATA_IN2_PIN  - Registers (IC 1) */
#define REG_SDATA_IN2_PIN_IC_1_ADDR               0xF792
#define REG_SDATA_IN2_PIN_IC_1_BYTE               2
#define REG_SDATA_IN2_PIN_IC_1_VALUE              0x18

/* SDATA_IN3_PIN  - Registers (IC 1) */
#define REG_SDATA_IN3_PIN_IC_1_ADDR               0xF793
#define REG_SDATA_IN3_PIN_IC_1_BYTE               2
#define REG_SDATA_IN3_PIN_IC_1_VALUE              0x18

/* SDATA_OUT0_PIN  - Registers (IC 1) */
#define REG_SDATA_OUT0_PIN_IC_1_ADDR              0xF794
#define REG_SDATA_OUT0_PIN_IC_1_BYTE              2
#define REG_SDATA_OUT0_PIN_IC_1_VALUE             0x8

/* SDATA_OUT1_PIN  - Registers (IC 1) */
#define REG_SDATA_OUT1_PIN_IC_1_ADDR              0xF795
#define REG_SDATA_OUT1_PIN_IC_1_BYTE              2
#define REG_SDATA_OUT1_PIN_IC_1_VALUE             0x8

/* SDATA_OUT2_PIN  - Registers (IC 1) */
#define REG_SDATA_OUT2_PIN_IC_1_ADDR              0xF796
#define REG_SDATA_OUT2_PIN_IC_1_BYTE              2
#define REG_SDATA_OUT2_PIN_IC_1_VALUE             0x8

/* SDATA_OUT3_PIN  - Registers (IC 1) */
#define REG_SDATA_OUT3_PIN_IC_1_ADDR              0xF797
#define REG_SDATA_OUT3_PIN_IC_1_BYTE              2
#define REG_SDATA_OUT3_PIN_IC_1_VALUE             0x8

/* SPDIF_TX_PIN  - Registers (IC 1) */
#define REG_SPDIF_TX_PIN_IC_1_ADDR                0xF798
#define REG_SPDIF_TX_PIN_IC_1_BYTE                2
#define REG_SPDIF_TX_PIN_IC_1_VALUE               0x8

/* SCLK_SCL_PIN  - Registers (IC 1) */
#define REG_SCLK_SCL_PIN_IC_1_ADDR                0xF799
#define REG_SCLK_SCL_PIN_IC_1_BYTE                2
#define REG_SCLK_SCL_PIN_IC_1_VALUE               0x8

/* MISO_SDA_PIN  - Registers (IC 1) */
#define REG_MISO_SDA_PIN_IC_1_ADDR                0xF79A
#define REG_MISO_SDA_PIN_IC_1_BYTE                2
#define REG_MISO_SDA_PIN_IC_1_VALUE               0x8

/* SS_PIN  - Registers (IC 1) */
#define REG_SS_PIN_IC_1_ADDR                      0xF79B
#define REG_SS_PIN_IC_1_BYTE                      2
#define REG_SS_PIN_IC_1_VALUE                     0x18

/* MOSI_ADDR1_PIN  - Registers (IC 1) */
#define REG_MOSI_ADDR1_PIN_IC_1_ADDR              0xF79C
#define REG_MOSI_ADDR1_PIN_IC_1_BYTE              2
#define REG_MOSI_ADDR1_PIN_IC_1_VALUE             0x18

/* SCLK_SCL_M_PIN  - Registers (IC 1) */
#define REG_SCLK_SCL_M_PIN_IC_1_ADDR              0xF79D
#define REG_SCLK_SCL_M_PIN_IC_1_BYTE              2
#define REG_SCLK_SCL_M_PIN_IC_1_VALUE             0xF

/* MISO_SDA_M_PIN  - Registers (IC 1) */
#define REG_MISO_SDA_M_PIN_IC_1_ADDR              0xF79E
#define REG_MISO_SDA_M_PIN_IC_1_BYTE              2
#define REG_MISO_SDA_M_PIN_IC_1_VALUE             0xF

/* SS_M_PIN  - Registers (IC 1) */
#define REG_SS_M_PIN_IC_1_ADDR                    0xF79F
#define REG_SS_M_PIN_IC_1_BYTE                    2
#define REG_SS_M_PIN_IC_1_VALUE                   0xF

/* MOSI_M_PIN  - Registers (IC 1) */
#define REG_MOSI_M_PIN_IC_1_ADDR                  0xF7A0
#define REG_MOSI_M_PIN_IC_1_BYTE                  2
#define REG_MOSI_M_PIN_IC_1_VALUE                 0xF

/* MP6_PIN  - Registers (IC 1) */
#define REG_MP6_PIN_IC_1_ADDR                     0xF7A1
#define REG_MP6_PIN_IC_1_BYTE                     2
#define REG_MP6_PIN_IC_1_VALUE                    0x18

/* MP7_PIN  - Registers (IC 1) */
#define REG_MP7_PIN_IC_1_ADDR                     0xF7A2
#define REG_MP7_PIN_IC_1_BYTE                     2
#define REG_MP7_PIN_IC_1_VALUE                    0x18

/* CLKOUT_PIN  - Registers (IC 1) */
#define REG_CLKOUT_PIN_IC_1_ADDR                  0xF7A3
#define REG_CLKOUT_PIN_IC_1_BYTE                  2
#define REG_CLKOUT_PIN_IC_1_VALUE                 0x8

/* SOFT_RESET  - Registers (IC 1) */
#define REG_SOFT_RESET_IC_1_ADDR                  0xF890
#define REG_SOFT_RESET_IC_1_BYTE                  2
#define REG_SOFT_RESET_IC_1_VALUE                 0x1


/*
 *
 * Control register's field descriptions
 *
 */

/* PLL_CTRL0 (IC 1) */
#define R0_PLL_CTRL0_PLL_FBDIVIDER_IC_1           0x60   /* 1100000b	[6:0] */
#define R0_PLL_CTRL0_PLL_FBDIVIDER_IC_1_MASK      0x7F
#define R0_PLL_CTRL0_PLL_FBDIVIDER_IC_1_SHIFT     0

/* PLL_CTRL1 (IC 1) */
#define R1_PLL_CTRL1_PLL_DIV_IC_1                 0x3    /* 11b	[1:0] */
#define R1_PLL_CTRL1_PLL_DIV_IC_1_MASK            0x3
#define R1_PLL_CTRL1_PLL_DIV_IC_1_SHIFT           0

/* PLL_CLK_SRC (IC 1) */
#define R2_PLL_CLK_SRC_CLKSRC_IC_1                0x1    /* 1b	[0] */
#define R2_PLL_CLK_SRC_CLKSRC_IC_1_MASK           0x1
#define R2_PLL_CLK_SRC_CLKSRC_IC_1_SHIFT          0

/* PLL_ENABLE (IC 1) */
#define R3_PLL_ENABLE_PLL_ENABLE_IC_1             0x1    /* 1b	[0] */
#define R3_PLL_ENABLE_PLL_ENABLE_IC_1_MASK        0x1
#define R3_PLL_ENABLE_PLL_ENABLE_IC_1_SHIFT       0

/* PLL_LOCK (IC 1) */
#define R4_PLL_LOCK_PLL_LOCK_IC_1                 0x1    /* 1b	[0] */
#define R4_PLL_LOCK_PLL_LOCK_IC_1_MASK            0x1
#define R4_PLL_LOCK_PLL_LOCK_IC_1_SHIFT           0

/* MCLK_OUT (IC 1) */
#define R5_MCLK_OUT_CLKOUT_ENABLE_IC_1            0x1    /* 1b	[0] */
#define R5_MCLK_OUT_CLKOUT_RATE_IC_1              0x3    /* 11b	[2:1] */
#define R5_MCLK_OUT_CLKOUT_ENABLE_IC_1_MASK       0x1
#define R5_MCLK_OUT_CLKOUT_ENABLE_IC_1_SHIFT      0
#define R5_MCLK_OUT_CLKOUT_RATE_IC_1_MASK         0x6
#define R5_MCLK_OUT_CLKOUT_RATE_IC_1_SHIFT        1

/* PLL_WATCHDOG (IC 1) */
#define R6_PLL_WATCHDOG_PLL_WATCHDOG_IC_1         0x1    /* 1b	[0] */
#define R6_PLL_WATCHDOG_PLL_WATCHDOG_IC_1_MASK    0x1
#define R6_PLL_WATCHDOG_PLL_WATCHDOG_IC_1_SHIFT   0

/* CLK_GEN1_M (IC 1) */
#define R7_CLK_GEN1_M_CLOCKGEN1_M_IC_1            0x06   /* 000000110b	[8:0] */
#define R7_CLK_GEN1_M_CLOCKGEN1_M_IC_1_MASK       0x1FF
#define R7_CLK_GEN1_M_CLOCKGEN1_M_IC_1_SHIFT      0

/* CLK_GEN1_N (IC 1) */
#define R8_CLK_GEN1_N_CLOCKGEN1_N_IC_1            0x01   /* 000000001b	[8:0] */
#define R8_CLK_GEN1_N_CLOCKGEN1_N_IC_1_MASK       0x1FF
#define R8_CLK_GEN1_N_CLOCKGEN1_N_IC_1_SHIFT      0

/* CLK_GEN2_M (IC 1) */
#define R9_CLK_GEN2_M_CLOCKGEN2_M_IC_1            0x09   /* 000001001b	[8:0] */
#define R9_CLK_GEN2_M_CLOCKGEN2_M_IC_1_MASK       0x1FF
#define R9_CLK_GEN2_M_CLOCKGEN2_M_IC_1_SHIFT      0

/* CLK_GEN2_N (IC 1) */
#define R10_CLK_GEN2_N_CLOCKGEN2_N_IC_1           0x01   /* 000000001b	[8:0] */
#define R10_CLK_GEN2_N_CLOCKGEN2_N_IC_1_MASK      0x1FF
#define R10_CLK_GEN2_N_CLOCKGEN2_N_IC_1_SHIFT     0

/* CLK_GEN3_M (IC 1) */
#define R11_CLK_GEN3_M_CLOCKGEN3_M_IC_1           0x0000 /* 0000000000000000b	[15:0] */
#define R11_CLK_GEN3_M_CLOCKGEN3_M_IC_1_MASK      0xFFFF
#define R11_CLK_GEN3_M_CLOCKGEN3_M_IC_1_SHIFT     0

/* CLK_GEN3_N (IC 1) */
#define R12_CLK_GEN3_N_CLOCKGEN3_N_IC_1           0x0000 /* 0000000000000000b	[15:0] */
#define R12_CLK_GEN3_N_CLOCKGEN3_N_IC_1_MASK      0xFFFF
#define R12_CLK_GEN3_N_CLOCKGEN3_N_IC_1_SHIFT     0

/* CLK_GEN3_SRC (IC 1) */
#define R13_CLK_GEN3_SRC_FREF_PIN_IC_1            0xE    /* 1110b	[3:0] */
#define R13_CLK_GEN3_SRC_CLK_GEN3_SRC_IC_1        0x0    /* 0b	[4] */
#define R13_CLK_GEN3_SRC_FREF_PIN_IC_1_MASK       0xF
#define R13_CLK_GEN3_SRC_FREF_PIN_IC_1_SHIFT      0
#define R13_CLK_GEN3_SRC_CLK_GEN3_SRC_IC_1_MASK   0x10
#define R13_CLK_GEN3_SRC_CLK_GEN3_SRC_IC_1_SHIFT  4

/* CLK_GEN3_LOCK (IC 1) */
#define R14_CLK_GEN3_LOCK_GEN3_LOCK_IC_1          0x1    /* 1b	[0] */
#define R14_CLK_GEN3_LOCK_GEN3_LOCK_IC_1_MASK     0x1
#define R14_CLK_GEN3_LOCK_GEN3_LOCK_IC_1_SHIFT    0

/* POWER_ENABLE0 (IC 1) */
#define R15_POWER_ENABLE0_SIN0_PWR_IC_1           0x1    /* 1b	[0] */
#define R15_POWER_ENABLE0_SIN1_PWR_IC_1           0x1    /* 1b	[1] */
#define R15_POWER_ENABLE0_SIN2_PWR_IC_1           0x1    /* 1b	[2] */
#define R15_POWER_ENABLE0_SIN3_PWR_IC_1           0x1    /* 1b	[3] */
#define R15_POWER_ENABLE0_SOUT0_PWR_IC_1          0x1    /* 1b	[4] */
#define R15_POWER_ENABLE0_SOUT1_PWR_IC_1          0x1    /* 1b	[5] */
#define R15_POWER_ENABLE0_SOUT2_PWR_IC_1          0x1    /* 1b	[6] */
#define R15_POWER_ENABLE0_SOUT3_PWR_IC_1          0x1    /* 1b	[7] */
#define R15_POWER_ENABLE0_ASRCBANK0_PWR_IC_1      0x1    /* 1b	[8] */
#define R15_POWER_ENABLE0_ASRCBANK1_PWR_IC_1      0x0    /* 0b	[9] */
#define R15_POWER_ENABLE0_CLK_GEN1_PWR_IC_1       0x1    /* 1b	[10] */
#define R15_POWER_ENABLE0_CLK_GEN2_PWR_IC_1       0x0    /* 0b	[11] */
#define R15_POWER_ENABLE0_CLK_GEN3_PWR_IC_1       0x0    /* 0b	[12] */
#define R15_POWER_ENABLE0_SIN0_PWR_IC_1_MASK      0x1
#define R15_POWER_ENABLE0_SIN0_PWR_IC_1_SHIFT     0
#define R15_POWER_ENABLE0_SIN1_PWR_IC_1_MASK      0x2
#define R15_POWER_ENABLE0_SIN1_PWR_IC_1_SHIFT     1
#define R15_POWER_ENABLE0_SIN2_PWR_IC_1_MASK      0x4
#define R15_POWER_ENABLE0_SIN2_PWR_IC_1_SHIFT     2
#define R15_POWER_ENABLE0_SIN3_PWR_IC_1_MASK      0x8
#define R15_POWER_ENABLE0_SIN3_PWR_IC_1_SHIFT     3
#define R15_POWER_ENABLE0_SOUT0_PWR_IC_1_MASK     0x10
#define R15_POWER_ENABLE0_SOUT0_PWR_IC_1_SHIFT    4
#define R15_POWER_ENABLE0_SOUT1_PWR_IC_1_MASK     0x20
#define R15_POWER_ENABLE0_SOUT1_PWR_IC_1_SHIFT    5
#define R15_POWER_ENABLE0_SOUT2_PWR_IC_1_MASK     0x40
#define R15_POWER_ENABLE0_SOUT2_PWR_IC_1_SHIFT    6
#define R15_POWER_ENABLE0_SOUT3_PWR_IC_1_MASK     0x80
#define R15_POWER_ENABLE0_SOUT3_PWR_IC_1_SHIFT    7
#define R15_POWER_ENABLE0_ASRCBANK0_PWR_IC_1_MASK 0x100
#define R15_POWER_ENABLE0_ASRCBANK0_PWR_IC_1_SHIFT 8
#define R15_POWER_ENABLE0_ASRCBANK1_PWR_IC_1_MASK 0x200
#define R15_POWER_ENABLE0_ASRCBANK1_PWR_IC_1_SHIFT 9
#define R15_POWER_ENABLE0_CLK_GEN1_PWR_IC_1_MASK  0x400
#define R15_POWER_ENABLE0_CLK_GEN1_PWR_IC_1_SHIFT 10
#define R15_POWER_ENABLE0_CLK_GEN2_PWR_IC_1_MASK  0x800
#define R15_POWER_ENABLE0_CLK_GEN2_PWR_IC_1_SHIFT 11
#define R15_POWER_ENABLE0_CLK_GEN3_PWR_IC_1_MASK  0x1000
#define R15_POWER_ENABLE0_CLK_GEN3_PWR_IC_1_SHIFT 12

/* POWER_ENABLE1 (IC 1) */
#define R16_POWER_ENABLE1_ADC_PWR_IC_1            0x1    /* 1b	[0] */
#define R16_POWER_ENABLE1_RX_PWR_IC_1             0x1    /* 1b	[1] */
#define R16_POWER_ENABLE1_TX_PWR_IC_1             0x1    /* 1b	[2] */
#define R16_POWER_ENABLE1_PDM0_PWR_IC_1           0x0    /* 0b	[3] */
#define R16_POWER_ENABLE1_PDM1_PWR_IC_1           0x0    /* 0b	[4] */
#define R16_POWER_ENABLE1_ADC_PWR_IC_1_MASK       0x1
#define R16_POWER_ENABLE1_ADC_PWR_IC_1_SHIFT      0
#define R16_POWER_ENABLE1_RX_PWR_IC_1_MASK        0x2
#define R16_POWER_ENABLE1_RX_PWR_IC_1_SHIFT       1
#define R16_POWER_ENABLE1_TX_PWR_IC_1_MASK        0x4
#define R16_POWER_ENABLE1_TX_PWR_IC_1_SHIFT       2
#define R16_POWER_ENABLE1_PDM0_PWR_IC_1_MASK      0x8
#define R16_POWER_ENABLE1_PDM0_PWR_IC_1_SHIFT     3
#define R16_POWER_ENABLE1_PDM1_PWR_IC_1_MASK      0x10
#define R16_POWER_ENABLE1_PDM1_PWR_IC_1_SHIFT     4

/* ASRC_INPUT0 (IC 1) */
#define R17_ASRC_INPUT0_ASRC_SOURCE_IC_1          0x3    /* 011b	[2:0] */
#define R17_ASRC_INPUT0_ASRC_SIN_CHANNEL_IC_1     0x0    /* 00000b	[7:3] */
#define R17_ASRC_INPUT0_ASRC_SOURCE_IC_1_MASK     0x7
#define R17_ASRC_INPUT0_ASRC_SOURCE_IC_1_SHIFT    0
#define R17_ASRC_INPUT0_ASRC_SIN_CHANNEL_IC_1_MASK 0xF8
#define R17_ASRC_INPUT0_ASRC_SIN_CHANNEL_IC_1_SHIFT 3

/* ASRC_INPUT1 (IC 1) */
#define R18_ASRC_INPUT1_ASRC_SOURCE_IC_1          0x0    /* 000b	[2:0] */
#define R18_ASRC_INPUT1_ASRC_SIN_CHANNEL_IC_1     0x0    /* 00000b	[7:3] */
#define R18_ASRC_INPUT1_ASRC_SOURCE_IC_1_MASK     0x7
#define R18_ASRC_INPUT1_ASRC_SOURCE_IC_1_SHIFT    0
#define R18_ASRC_INPUT1_ASRC_SIN_CHANNEL_IC_1_MASK 0xF8
#define R18_ASRC_INPUT1_ASRC_SIN_CHANNEL_IC_1_SHIFT 3

/* ASRC_INPUT2 (IC 1) */
#define R19_ASRC_INPUT2_ASRC_SOURCE_IC_1          0x0    /* 000b	[2:0] */
#define R19_ASRC_INPUT2_ASRC_SIN_CHANNEL_IC_1     0x0    /* 00000b	[7:3] */
#define R19_ASRC_INPUT2_ASRC_SOURCE_IC_1_MASK     0x7
#define R19_ASRC_INPUT2_ASRC_SOURCE_IC_1_SHIFT    0
#define R19_ASRC_INPUT2_ASRC_SIN_CHANNEL_IC_1_MASK 0xF8
#define R19_ASRC_INPUT2_ASRC_SIN_CHANNEL_IC_1_SHIFT 3

/* ASRC_INPUT3 (IC 1) */
#define R20_ASRC_INPUT3_ASRC_SOURCE_IC_1          0x0    /* 000b	[2:0] */
#define R20_ASRC_INPUT3_ASRC_SIN_CHANNEL_IC_1     0x0    /* 00000b	[7:3] */
#define R20_ASRC_INPUT3_ASRC_SOURCE_IC_1_MASK     0x7
#define R20_ASRC_INPUT3_ASRC_SOURCE_IC_1_SHIFT    0
#define R20_ASRC_INPUT3_ASRC_SIN_CHANNEL_IC_1_MASK 0xF8
#define R20_ASRC_INPUT3_ASRC_SIN_CHANNEL_IC_1_SHIFT 3

/* ASRC_INPUT4 (IC 1) */
#define R21_ASRC_INPUT4_ASRC_SOURCE_IC_1          0x0    /* 000b	[2:0] */
#define R21_ASRC_INPUT4_ASRC_SIN_CHANNEL_IC_1     0x0    /* 00000b	[7:3] */
#define R21_ASRC_INPUT4_ASRC_SOURCE_IC_1_MASK     0x7
#define R21_ASRC_INPUT4_ASRC_SOURCE_IC_1_SHIFT    0
#define R21_ASRC_INPUT4_ASRC_SIN_CHANNEL_IC_1_MASK 0xF8
#define R21_ASRC_INPUT4_ASRC_SIN_CHANNEL_IC_1_SHIFT 3

/* ASRC_INPUT5 (IC 1) */
#define R22_ASRC_INPUT5_ASRC_SOURCE_IC_1          0x0    /* 000b	[2:0] */
#define R22_ASRC_INPUT5_ASRC_SIN_CHANNEL_IC_1     0x0    /* 00000b	[7:3] */
#define R22_ASRC_INPUT5_ASRC_SOURCE_IC_1_MASK     0x7
#define R22_ASRC_INPUT5_ASRC_SOURCE_IC_1_SHIFT    0
#define R22_ASRC_INPUT5_ASRC_SIN_CHANNEL_IC_1_MASK 0xF8
#define R22_ASRC_INPUT5_ASRC_SIN_CHANNEL_IC_1_SHIFT 3

/* ASRC_INPUT6 (IC 1) */
#define R23_ASRC_INPUT6_ASRC_SOURCE_IC_1          0x0    /* 000b	[2:0] */
#define R23_ASRC_INPUT6_ASRC_SIN_CHANNEL_IC_1     0x0    /* 00000b	[7:3] */
#define R23_ASRC_INPUT6_ASRC_SOURCE_IC_1_MASK     0x7
#define R23_ASRC_INPUT6_ASRC_SOURCE_IC_1_SHIFT    0
#define R23_ASRC_INPUT6_ASRC_SIN_CHANNEL_IC_1_MASK 0xF8
#define R23_ASRC_INPUT6_ASRC_SIN_CHANNEL_IC_1_SHIFT 3

/* ASRC_INPUT7 (IC 1) */
#define R24_ASRC_INPUT7_ASRC_SOURCE_IC_1          0x0    /* 000b	[2:0] */
#define R24_ASRC_INPUT7_ASRC_SIN_CHANNEL_IC_1     0x0    /* 00000b	[7:3] */
#define R24_ASRC_INPUT7_ASRC_SOURCE_IC_1_MASK     0x7
#define R24_ASRC_INPUT7_ASRC_SOURCE_IC_1_SHIFT    0
#define R24_ASRC_INPUT7_ASRC_SIN_CHANNEL_IC_1_MASK 0xF8
#define R24_ASRC_INPUT7_ASRC_SIN_CHANNEL_IC_1_SHIFT 3

/* ASRC_OUT_RATE0 (IC 1) */
#define R25_ASRC_OUT_RATE0_ASRC_RATE_IC_1         0x6    /* 0110b	[3:0] */
#define R25_ASRC_OUT_RATE0_ASRC_RATE_IC_1_MASK    0xF
#define R25_ASRC_OUT_RATE0_ASRC_RATE_IC_1_SHIFT   0

/* ASRC_OUT_RATE1 (IC 1) */
#define R26_ASRC_OUT_RATE1_ASRC_RATE_IC_1         0x0    /* 0000b	[3:0] */
#define R26_ASRC_OUT_RATE1_ASRC_RATE_IC_1_MASK    0xF
#define R26_ASRC_OUT_RATE1_ASRC_RATE_IC_1_SHIFT   0

/* ASRC_OUT_RATE2 (IC 1) */
#define R27_ASRC_OUT_RATE2_ASRC_RATE_IC_1         0x0    /* 0000b	[3:0] */
#define R27_ASRC_OUT_RATE2_ASRC_RATE_IC_1_MASK    0xF
#define R27_ASRC_OUT_RATE2_ASRC_RATE_IC_1_SHIFT   0

/* ASRC_OUT_RATE3 (IC 1) */
#define R28_ASRC_OUT_RATE3_ASRC_RATE_IC_1         0x0    /* 0000b	[3:0] */
#define R28_ASRC_OUT_RATE3_ASRC_RATE_IC_1_MASK    0xF
#define R28_ASRC_OUT_RATE3_ASRC_RATE_IC_1_SHIFT   0

/* ASRC_OUT_RATE4 (IC 1) */
#define R29_ASRC_OUT_RATE4_ASRC_RATE_IC_1         0x0    /* 0000b	[3:0] */
#define R29_ASRC_OUT_RATE4_ASRC_RATE_IC_1_MASK    0xF
#define R29_ASRC_OUT_RATE4_ASRC_RATE_IC_1_SHIFT   0

/* ASRC_OUT_RATE5 (IC 1) */
#define R30_ASRC_OUT_RATE5_ASRC_RATE_IC_1         0x0    /* 0000b	[3:0] */
#define R30_ASRC_OUT_RATE5_ASRC_RATE_IC_1_MASK    0xF
#define R30_ASRC_OUT_RATE5_ASRC_RATE_IC_1_SHIFT   0

/* ASRC_OUT_RATE6 (IC 1) */
#define R31_ASRC_OUT_RATE6_ASRC_RATE_IC_1         0x0    /* 0000b	[3:0] */
#define R31_ASRC_OUT_RATE6_ASRC_RATE_IC_1_MASK    0xF
#define R31_ASRC_OUT_RATE6_ASRC_RATE_IC_1_SHIFT   0

/* ASRC_OUT_RATE7 (IC 1) */
#define R32_ASRC_OUT_RATE7_ASRC_RATE_IC_1         0x0    /* 0000b	[3:0] */
#define R32_ASRC_OUT_RATE7_ASRC_RATE_IC_1_MASK    0xF
#define R32_ASRC_OUT_RATE7_ASRC_RATE_IC_1_SHIFT   0

/* SOUT_SOURCE0 (IC 1) */
#define R33_SOUT_SOURCE0_SOUT_SOURCE_IC_1         0x2    /* 010b	[2:0] */
#define R33_SOUT_SOURCE0_SOUT_ASRC_SELECT_IC_1    0x0    /* 000b	[5:3] */
#define R33_SOUT_SOURCE0_SOUT_SOURCE_IC_1_MASK    0x7
#define R33_SOUT_SOURCE0_SOUT_SOURCE_IC_1_SHIFT   0
#define R33_SOUT_SOURCE0_SOUT_ASRC_SELECT_IC_1_MASK 0x38
#define R33_SOUT_SOURCE0_SOUT_ASRC_SELECT_IC_1_SHIFT 3

/* SOUT_SOURCE1 (IC 1) */
#define R34_SOUT_SOURCE1_SOUT_SOURCE_IC_1         0x2    /* 010b	[2:0] */
#define R34_SOUT_SOURCE1_SOUT_ASRC_SELECT_IC_1    0x0    /* 000b	[5:3] */
#define R34_SOUT_SOURCE1_SOUT_SOURCE_IC_1_MASK    0x7
#define R34_SOUT_SOURCE1_SOUT_SOURCE_IC_1_SHIFT   0
#define R34_SOUT_SOURCE1_SOUT_ASRC_SELECT_IC_1_MASK 0x38
#define R34_SOUT_SOURCE1_SOUT_ASRC_SELECT_IC_1_SHIFT 3

/* SOUT_SOURCE2 (IC 1) */
#define R35_SOUT_SOURCE2_SOUT_SOURCE_IC_1         0x2    /* 010b	[2:0] */
#define R35_SOUT_SOURCE2_SOUT_ASRC_SELECT_IC_1    0x0    /* 000b	[5:3] */
#define R35_SOUT_SOURCE2_SOUT_SOURCE_IC_1_MASK    0x7
#define R35_SOUT_SOURCE2_SOUT_SOURCE_IC_1_SHIFT   0
#define R35_SOUT_SOURCE2_SOUT_ASRC_SELECT_IC_1_MASK 0x38
#define R35_SOUT_SOURCE2_SOUT_ASRC_SELECT_IC_1_SHIFT 3

/* SOUT_SOURCE3 (IC 1) */
#define R36_SOUT_SOURCE3_SOUT_SOURCE_IC_1         0x2    /* 010b	[2:0] */
#define R36_SOUT_SOURCE3_SOUT_ASRC_SELECT_IC_1    0x0    /* 000b	[5:3] */
#define R36_SOUT_SOURCE3_SOUT_SOURCE_IC_1_MASK    0x7
#define R36_SOUT_SOURCE3_SOUT_SOURCE_IC_1_SHIFT   0
#define R36_SOUT_SOURCE3_SOUT_ASRC_SELECT_IC_1_MASK 0x38
#define R36_SOUT_SOURCE3_SOUT_ASRC_SELECT_IC_1_SHIFT 3

/* SOUT_SOURCE4 (IC 1) */
#define R37_SOUT_SOURCE4_SOUT_SOURCE_IC_1         0x2    /* 010b	[2:0] */
#define R37_SOUT_SOURCE4_SOUT_ASRC_SELECT_IC_1    0x0    /* 000b	[5:3] */
#define R37_SOUT_SOURCE4_SOUT_SOURCE_IC_1_MASK    0x7
#define R37_SOUT_SOURCE4_SOUT_SOURCE_IC_1_SHIFT   0
#define R37_SOUT_SOURCE4_SOUT_ASRC_SELECT_IC_1_MASK 0x38
#define R37_SOUT_SOURCE4_SOUT_ASRC_SELECT_IC_1_SHIFT 3

/* SOUT_SOURCE5 (IC 1) */
#define R38_SOUT_SOURCE5_SOUT_SOURCE_IC_1         0x2    /* 010b	[2:0] */
#define R38_SOUT_SOURCE5_SOUT_ASRC_SELECT_IC_1    0x0    /* 000b	[5:3] */
#define R38_SOUT_SOURCE5_SOUT_SOURCE_IC_1_MASK    0x7
#define R38_SOUT_SOURCE5_SOUT_SOURCE_IC_1_SHIFT   0
#define R38_SOUT_SOURCE5_SOUT_ASRC_SELECT_IC_1_MASK 0x38
#define R38_SOUT_SOURCE5_SOUT_ASRC_SELECT_IC_1_SHIFT 3

/* SOUT_SOURCE6 (IC 1) */
#define R39_SOUT_SOURCE6_SOUT_SOURCE_IC_1         0x2    /* 010b	[2:0] */
#define R39_SOUT_SOURCE6_SOUT_ASRC_SELECT_IC_1    0x0    /* 000b	[5:3] */
#define R39_SOUT_SOURCE6_SOUT_SOURCE_IC_1_MASK    0x7
#define R39_SOUT_SOURCE6_SOUT_SOURCE_IC_1_SHIFT   0
#define R39_SOUT_SOURCE6_SOUT_ASRC_SELECT_IC_1_MASK 0x38
#define R39_SOUT_SOURCE6_SOUT_ASRC_SELECT_IC_1_SHIFT 3

/* SOUT_SOURCE7 (IC 1) */
#define R40_SOUT_SOURCE7_SOUT_SOURCE_IC_1         0x2    /* 010b	[2:0] */
#define R40_SOUT_SOURCE7_SOUT_ASRC_SELECT_IC_1    0x0    /* 000b	[5:3] */
#define R40_SOUT_SOURCE7_SOUT_SOURCE_IC_1_MASK    0x7
#define R40_SOUT_SOURCE7_SOUT_SOURCE_IC_1_SHIFT   0
#define R40_SOUT_SOURCE7_SOUT_ASRC_SELECT_IC_1_MASK 0x38
#define R40_SOUT_SOURCE7_SOUT_ASRC_SELECT_IC_1_SHIFT 3

/* SOUT_SOURCE8 (IC 1) */
#define R41_SOUT_SOURCE8_SOUT_SOURCE_IC_1         0x2    /* 010b	[2:0] */
#define R41_SOUT_SOURCE8_SOUT_ASRC_SELECT_IC_1    0x5    /* 101b	[5:3] */
#define R41_SOUT_SOURCE8_SOUT_SOURCE_IC_1_MASK    0x7
#define R41_SOUT_SOURCE8_SOUT_SOURCE_IC_1_SHIFT   0
#define R41_SOUT_SOURCE8_SOUT_ASRC_SELECT_IC_1_MASK 0x38
#define R41_SOUT_SOURCE8_SOUT_ASRC_SELECT_IC_1_SHIFT 3

/* SOUT_SOURCE9 (IC 1) */
#define R42_SOUT_SOURCE9_SOUT_SOURCE_IC_1         0x2    /* 010b	[2:0] */
#define R42_SOUT_SOURCE9_SOUT_ASRC_SELECT_IC_1    0x0    /* 000b	[5:3] */
#define R42_SOUT_SOURCE9_SOUT_SOURCE_IC_1_MASK    0x7
#define R42_SOUT_SOURCE9_SOUT_SOURCE_IC_1_SHIFT   0
#define R42_SOUT_SOURCE9_SOUT_ASRC_SELECT_IC_1_MASK 0x38
#define R42_SOUT_SOURCE9_SOUT_ASRC_SELECT_IC_1_SHIFT 3

/* SOUT_SOURCE10 (IC 1) */
#define R43_SOUT_SOURCE10_SOUT_SOURCE_IC_1        0x2    /* 010b	[2:0] */
#define R43_SOUT_SOURCE10_SOUT_ASRC_SELECT_IC_1   0x0    /* 000b	[5:3] */
#define R43_SOUT_SOURCE10_SOUT_SOURCE_IC_1_MASK   0x7
#define R43_SOUT_SOURCE10_SOUT_SOURCE_IC_1_SHIFT  0
#define R43_SOUT_SOURCE10_SOUT_ASRC_SELECT_IC_1_MASK 0x38
#define R43_SOUT_SOURCE10_SOUT_ASRC_SELECT_IC_1_SHIFT 3

/* SOUT_SOURCE11 (IC 1) */
#define R44_SOUT_SOURCE11_SOUT_SOURCE_IC_1        0x2    /* 010b	[2:0] */
#define R44_SOUT_SOURCE11_SOUT_ASRC_SELECT_IC_1   0x0    /* 000b	[5:3] */
#define R44_SOUT_SOURCE11_SOUT_SOURCE_IC_1_MASK   0x7
#define R44_SOUT_SOURCE11_SOUT_SOURCE_IC_1_SHIFT  0
#define R44_SOUT_SOURCE11_SOUT_ASRC_SELECT_IC_1_MASK 0x38
#define R44_SOUT_SOURCE11_SOUT_ASRC_SELECT_IC_1_SHIFT 3

/* SOUT_SOURCE12 (IC 1) */
#define R45_SOUT_SOURCE12_SOUT_SOURCE_IC_1        0x2    /* 010b	[2:0] */
#define R45_SOUT_SOURCE12_SOUT_ASRC_SELECT_IC_1   0x0    /* 000b	[5:3] */
#define R45_SOUT_SOURCE12_SOUT_SOURCE_IC_1_MASK   0x7
#define R45_SOUT_SOURCE12_SOUT_SOURCE_IC_1_SHIFT  0
#define R45_SOUT_SOURCE12_SOUT_ASRC_SELECT_IC_1_MASK 0x38
#define R45_SOUT_SOURCE12_SOUT_ASRC_SELECT_IC_1_SHIFT 3

/* SOUT_SOURCE13 (IC 1) */
#define R46_SOUT_SOURCE13_SOUT_SOURCE_IC_1        0x2    /* 010b	[2:0] */
#define R46_SOUT_SOURCE13_SOUT_ASRC_SELECT_IC_1   0x0    /* 000b	[5:3] */
#define R46_SOUT_SOURCE13_SOUT_SOURCE_IC_1_MASK   0x7
#define R46_SOUT_SOURCE13_SOUT_SOURCE_IC_1_SHIFT  0
#define R46_SOUT_SOURCE13_SOUT_ASRC_SELECT_IC_1_MASK 0x38
#define R46_SOUT_SOURCE13_SOUT_ASRC_SELECT_IC_1_SHIFT 3

/* SOUT_SOURCE14 (IC 1) */
#define R47_SOUT_SOURCE14_SOUT_SOURCE_IC_1        0x2    /* 010b	[2:0] */
#define R47_SOUT_SOURCE14_SOUT_ASRC_SELECT_IC_1   0x0    /* 000b	[5:3] */
#define R47_SOUT_SOURCE14_SOUT_SOURCE_IC_1_MASK   0x7
#define R47_SOUT_SOURCE14_SOUT_SOURCE_IC_1_SHIFT  0
#define R47_SOUT_SOURCE14_SOUT_ASRC_SELECT_IC_1_MASK 0x38
#define R47_SOUT_SOURCE14_SOUT_ASRC_SELECT_IC_1_SHIFT 3

/* SOUT_SOURCE15 (IC 1) */
#define R48_SOUT_SOURCE15_SOUT_SOURCE_IC_1        0x2    /* 010b	[2:0] */
#define R48_SOUT_SOURCE15_SOUT_ASRC_SELECT_IC_1   0x0    /* 000b	[5:3] */
#define R48_SOUT_SOURCE15_SOUT_SOURCE_IC_1_MASK   0x7
#define R48_SOUT_SOURCE15_SOUT_SOURCE_IC_1_SHIFT  0
#define R48_SOUT_SOURCE15_SOUT_ASRC_SELECT_IC_1_MASK 0x38
#define R48_SOUT_SOURCE15_SOUT_ASRC_SELECT_IC_1_SHIFT 3

/* SOUT_SOURCE16 (IC 1) */
#define R49_SOUT_SOURCE16_SOUT_SOURCE_IC_1        0x0    /* 000b	[2:0] */
#define R49_SOUT_SOURCE16_SOUT_ASRC_SELECT_IC_1   0x0    /* 000b	[5:3] */
#define R49_SOUT_SOURCE16_SOUT_SOURCE_IC_1_MASK   0x7
#define R49_SOUT_SOURCE16_SOUT_SOURCE_IC_1_SHIFT  0
#define R49_SOUT_SOURCE16_SOUT_ASRC_SELECT_IC_1_MASK 0x38
#define R49_SOUT_SOURCE16_SOUT_ASRC_SELECT_IC_1_SHIFT 3

/* SOUT_SOURCE17 (IC 1) */
#define R50_SOUT_SOURCE17_SOUT_SOURCE_IC_1        0x0    /* 000b	[2:0] */
#define R50_SOUT_SOURCE17_SOUT_ASRC_SELECT_IC_1   0x0    /* 000b	[5:3] */
#define R50_SOUT_SOURCE17_SOUT_SOURCE_IC_1_MASK   0x7
#define R50_SOUT_SOURCE17_SOUT_SOURCE_IC_1_SHIFT  0
#define R50_SOUT_SOURCE17_SOUT_ASRC_SELECT_IC_1_MASK 0x38
#define R50_SOUT_SOURCE17_SOUT_ASRC_SELECT_IC_1_SHIFT 3

/* SOUT_SOURCE18 (IC 1) */
#define R51_SOUT_SOURCE18_SOUT_SOURCE_IC_1        0x0    /* 000b	[2:0] */
#define R51_SOUT_SOURCE18_SOUT_ASRC_SELECT_IC_1   0x0    /* 000b	[5:3] */
#define R51_SOUT_SOURCE18_SOUT_SOURCE_IC_1_MASK   0x7
#define R51_SOUT_SOURCE18_SOUT_SOURCE_IC_1_SHIFT  0
#define R51_SOUT_SOURCE18_SOUT_ASRC_SELECT_IC_1_MASK 0x38
#define R51_SOUT_SOURCE18_SOUT_ASRC_SELECT_IC_1_SHIFT 3

/* SOUT_SOURCE19 (IC 1) */
#define R52_SOUT_SOURCE19_SOUT_SOURCE_IC_1        0x0    /* 000b	[2:0] */
#define R52_SOUT_SOURCE19_SOUT_ASRC_SELECT_IC_1   0x0    /* 000b	[5:3] */
#define R52_SOUT_SOURCE19_SOUT_SOURCE_IC_1_MASK   0x7
#define R52_SOUT_SOURCE19_SOUT_SOURCE_IC_1_SHIFT  0
#define R52_SOUT_SOURCE19_SOUT_ASRC_SELECT_IC_1_MASK 0x38
#define R52_SOUT_SOURCE19_SOUT_ASRC_SELECT_IC_1_SHIFT 3

/* SOUT_SOURCE20 (IC 1) */
#define R53_SOUT_SOURCE20_SOUT_SOURCE_IC_1        0x0    /* 000b	[2:0] */
#define R53_SOUT_SOURCE20_SOUT_ASRC_SELECT_IC_1   0x0    /* 000b	[5:3] */
#define R53_SOUT_SOURCE20_SOUT_SOURCE_IC_1_MASK   0x7
#define R53_SOUT_SOURCE20_SOUT_SOURCE_IC_1_SHIFT  0
#define R53_SOUT_SOURCE20_SOUT_ASRC_SELECT_IC_1_MASK 0x38
#define R53_SOUT_SOURCE20_SOUT_ASRC_SELECT_IC_1_SHIFT 3

/* SOUT_SOURCE21 (IC 1) */
#define R54_SOUT_SOURCE21_SOUT_SOURCE_IC_1        0x0    /* 000b	[2:0] */
#define R54_SOUT_SOURCE21_SOUT_ASRC_SELECT_IC_1   0x0    /* 000b	[5:3] */
#define R54_SOUT_SOURCE21_SOUT_SOURCE_IC_1_MASK   0x7
#define R54_SOUT_SOURCE21_SOUT_SOURCE_IC_1_SHIFT  0
#define R54_SOUT_SOURCE21_SOUT_ASRC_SELECT_IC_1_MASK 0x38
#define R54_SOUT_SOURCE21_SOUT_ASRC_SELECT_IC_1_SHIFT 3

/* SOUT_SOURCE22 (IC 1) */
#define R55_SOUT_SOURCE22_SOUT_SOURCE_IC_1        0x0    /* 000b	[2:0] */
#define R55_SOUT_SOURCE22_SOUT_ASRC_SELECT_IC_1   0x0    /* 000b	[5:3] */
#define R55_SOUT_SOURCE22_SOUT_SOURCE_IC_1_MASK   0x7
#define R55_SOUT_SOURCE22_SOUT_SOURCE_IC_1_SHIFT  0
#define R55_SOUT_SOURCE22_SOUT_ASRC_SELECT_IC_1_MASK 0x38
#define R55_SOUT_SOURCE22_SOUT_ASRC_SELECT_IC_1_SHIFT 3

/* SOUT_SOURCE23 (IC 1) */
#define R56_SOUT_SOURCE23_SOUT_SOURCE_IC_1        0x0    /* 000b	[2:0] */
#define R56_SOUT_SOURCE23_SOUT_ASRC_SELECT_IC_1   0x0    /* 000b	[5:3] */
#define R56_SOUT_SOURCE23_SOUT_SOURCE_IC_1_MASK   0x7
#define R56_SOUT_SOURCE23_SOUT_SOURCE_IC_1_SHIFT  0
#define R56_SOUT_SOURCE23_SOUT_ASRC_SELECT_IC_1_MASK 0x38
#define R56_SOUT_SOURCE23_SOUT_ASRC_SELECT_IC_1_SHIFT 3

/* SPDIFTX_INPUT (IC 1) */
#define R57_SPDIFTX_INPUT_SPDIFTX_SOURCE_IC_1     0x1    /* 01b	[1:0] */
#define R57_SPDIFTX_INPUT_SPDIFTX_SOURCE_IC_1_MASK 0x3
#define R57_SPDIFTX_INPUT_SPDIFTX_SOURCE_IC_1_SHIFT 0

/* SERIAL_BYTE_0_0 (IC 1) */
#define R58_SERIAL_BYTE_0_0_TDM_MODE_IC_1         0x2    /* 010b	[2:0] */
#define R58_SERIAL_BYTE_0_0_DATA_FMT_IC_1         0x1    /* 01b	[4:3] */
#define R58_SERIAL_BYTE_0_0_WORD_LEN_IC_1         0x2    /* 10b	[6:5] */
#define R58_SERIAL_BYTE_0_0_BCLK_POL_IC_1         0x1    /* 1b	[7] */
#define R58_SERIAL_BYTE_0_0_LRCLK_POL_IC_1        0x1    /* 1b	[8] */
#define R58_SERIAL_BYTE_0_0_LRCLK_MODE_IC_1       0x1    /* 1b	[9] */
#define R58_SERIAL_BYTE_0_0_BCLK_SRC_IC_1         0x4    /* 100b	[12:10] */
#define R58_SERIAL_BYTE_0_0_LRCLK_SRC_IC_1        0x4    /* 100b	[15:13] */
#define R58_SERIAL_BYTE_0_0_TDM_MODE_IC_1_MASK    0x7
#define R58_SERIAL_BYTE_0_0_TDM_MODE_IC_1_SHIFT   0
#define R58_SERIAL_BYTE_0_0_DATA_FMT_IC_1_MASK    0x18
#define R58_SERIAL_BYTE_0_0_DATA_FMT_IC_1_SHIFT   3
#define R58_SERIAL_BYTE_0_0_WORD_LEN_IC_1_MASK    0x60
#define R58_SERIAL_BYTE_0_0_WORD_LEN_IC_1_SHIFT   5
#define R58_SERIAL_BYTE_0_0_BCLK_POL_IC_1_MASK    0x80
#define R58_SERIAL_BYTE_0_0_BCLK_POL_IC_1_SHIFT   7
#define R58_SERIAL_BYTE_0_0_LRCLK_POL_IC_1_MASK   0x100
#define R58_SERIAL_BYTE_0_0_LRCLK_POL_IC_1_SHIFT  8
#define R58_SERIAL_BYTE_0_0_LRCLK_MODE_IC_1_MASK  0x200
#define R58_SERIAL_BYTE_0_0_LRCLK_MODE_IC_1_SHIFT 9
#define R58_SERIAL_BYTE_0_0_BCLK_SRC_IC_1_MASK    0x1C00
#define R58_SERIAL_BYTE_0_0_BCLK_SRC_IC_1_SHIFT   10
#define R58_SERIAL_BYTE_0_0_LRCLK_SRC_IC_1_MASK   0xE000
#define R58_SERIAL_BYTE_0_0_LRCLK_SRC_IC_1_SHIFT  13

/* SERIAL_BYTE_0_1 (IC 1) */
#define R59_SERIAL_BYTE_0_1_FS_IC_1               0x2    /* 010b	[2:0] */
#define R59_SERIAL_BYTE_0_1_CLK_DOMAIN_IC_1       0x0    /* 00b	[4:3] */
#define R59_SERIAL_BYTE_0_1_TRISTATE_IC_1         0x0    /* 0b	[5] */
#define R59_SERIAL_BYTE_0_1_FS_IC_1_MASK          0x7
#define R59_SERIAL_BYTE_0_1_FS_IC_1_SHIFT         0
#define R59_SERIAL_BYTE_0_1_CLK_DOMAIN_IC_1_MASK  0x18
#define R59_SERIAL_BYTE_0_1_CLK_DOMAIN_IC_1_SHIFT 3
#define R59_SERIAL_BYTE_0_1_TRISTATE_IC_1_MASK    0x20
#define R59_SERIAL_BYTE_0_1_TRISTATE_IC_1_SHIFT   5

/* SERIAL_BYTE_1_0 (IC 1) */
#define R60_SERIAL_BYTE_1_0_TDM_MODE_IC_1         0x2    /* 010b	[2:0] */
#define R60_SERIAL_BYTE_1_0_DATA_FMT_IC_1         0x1    /* 01b	[4:3] */
#define R60_SERIAL_BYTE_1_0_WORD_LEN_IC_1         0x0    /* 00b	[6:5] */
#define R60_SERIAL_BYTE_1_0_BCLK_POL_IC_1         0x0    /* 0b	[7] */
#define R60_SERIAL_BYTE_1_0_LRCLK_POL_IC_1        0x0    /* 0b	[8] */
#define R60_SERIAL_BYTE_1_0_LRCLK_MODE_IC_1       0x1    /* 1b	[9] */
#define R60_SERIAL_BYTE_1_0_BCLK_SRC_IC_1         0x1    /* 001b	[12:10] */
#define R60_SERIAL_BYTE_1_0_LRCLK_SRC_IC_1        0x1    /* 001b	[15:13] */
#define R60_SERIAL_BYTE_1_0_TDM_MODE_IC_1_MASK    0x7
#define R60_SERIAL_BYTE_1_0_TDM_MODE_IC_1_SHIFT   0
#define R60_SERIAL_BYTE_1_0_DATA_FMT_IC_1_MASK    0x18
#define R60_SERIAL_BYTE_1_0_DATA_FMT_IC_1_SHIFT   3
#define R60_SERIAL_BYTE_1_0_WORD_LEN_IC_1_MASK    0x60
#define R60_SERIAL_BYTE_1_0_WORD_LEN_IC_1_SHIFT   5
#define R60_SERIAL_BYTE_1_0_BCLK_POL_IC_1_MASK    0x80
#define R60_SERIAL_BYTE_1_0_BCLK_POL_IC_1_SHIFT   7
#define R60_SERIAL_BYTE_1_0_LRCLK_POL_IC_1_MASK   0x100
#define R60_SERIAL_BYTE_1_0_LRCLK_POL_IC_1_SHIFT  8
#define R60_SERIAL_BYTE_1_0_LRCLK_MODE_IC_1_MASK  0x200
#define R60_SERIAL_BYTE_1_0_LRCLK_MODE_IC_1_SHIFT 9
#define R60_SERIAL_BYTE_1_0_BCLK_SRC_IC_1_MASK    0x1C00
#define R60_SERIAL_BYTE_1_0_BCLK_SRC_IC_1_SHIFT   10
#define R60_SERIAL_BYTE_1_0_LRCLK_SRC_IC_1_MASK   0xE000
#define R60_SERIAL_BYTE_1_0_LRCLK_SRC_IC_1_SHIFT  13

/* SERIAL_BYTE_1_1 (IC 1) */
#define R61_SERIAL_BYTE_1_1_FS_IC_1               0x2    /* 010b	[2:0] */
#define R61_SERIAL_BYTE_1_1_CLK_DOMAIN_IC_1       0x0    /* 00b	[4:3] */
#define R61_SERIAL_BYTE_1_1_TRISTATE_IC_1         0x0    /* 0b	[5] */
#define R61_SERIAL_BYTE_1_1_FS_IC_1_MASK          0x7
#define R61_SERIAL_BYTE_1_1_FS_IC_1_SHIFT         0
#define R61_SERIAL_BYTE_1_1_CLK_DOMAIN_IC_1_MASK  0x18
#define R61_SERIAL_BYTE_1_1_CLK_DOMAIN_IC_1_SHIFT 3
#define R61_SERIAL_BYTE_1_1_TRISTATE_IC_1_MASK    0x20
#define R61_SERIAL_BYTE_1_1_TRISTATE_IC_1_SHIFT   5

/* SERIAL_BYTE_2_0 (IC 1) */
#define R62_SERIAL_BYTE_2_0_TDM_MODE_IC_1         0x2    /* 010b	[2:0] */
#define R62_SERIAL_BYTE_2_0_DATA_FMT_IC_1         0x1    /* 01b	[4:3] */
#define R62_SERIAL_BYTE_2_0_WORD_LEN_IC_1         0x2    /* 10b	[6:5] */
#define R62_SERIAL_BYTE_2_0_BCLK_POL_IC_1         0x1    /* 1b	[7] */
#define R62_SERIAL_BYTE_2_0_LRCLK_POL_IC_1        0x1    /* 1b	[8] */
#define R62_SERIAL_BYTE_2_0_LRCLK_MODE_IC_1       0x1    /* 1b	[9] */
#define R62_SERIAL_BYTE_2_0_BCLK_SRC_IC_1         0x4    /* 100b	[12:10] */
#define R62_SERIAL_BYTE_2_0_LRCLK_SRC_IC_1        0x4    /* 100b	[15:13] */
#define R62_SERIAL_BYTE_2_0_TDM_MODE_IC_1_MASK    0x7
#define R62_SERIAL_BYTE_2_0_TDM_MODE_IC_1_SHIFT   0
#define R62_SERIAL_BYTE_2_0_DATA_FMT_IC_1_MASK    0x18
#define R62_SERIAL_BYTE_2_0_DATA_FMT_IC_1_SHIFT   3
#define R62_SERIAL_BYTE_2_0_WORD_LEN_IC_1_MASK    0x60
#define R62_SERIAL_BYTE_2_0_WORD_LEN_IC_1_SHIFT   5
#define R62_SERIAL_BYTE_2_0_BCLK_POL_IC_1_MASK    0x80
#define R62_SERIAL_BYTE_2_0_BCLK_POL_IC_1_SHIFT   7
#define R62_SERIAL_BYTE_2_0_LRCLK_POL_IC_1_MASK   0x100
#define R62_SERIAL_BYTE_2_0_LRCLK_POL_IC_1_SHIFT  8
#define R62_SERIAL_BYTE_2_0_LRCLK_MODE_IC_1_MASK  0x200
#define R62_SERIAL_BYTE_2_0_LRCLK_MODE_IC_1_SHIFT 9
#define R62_SERIAL_BYTE_2_0_BCLK_SRC_IC_1_MASK    0x1C00
#define R62_SERIAL_BYTE_2_0_BCLK_SRC_IC_1_SHIFT   10
#define R62_SERIAL_BYTE_2_0_LRCLK_SRC_IC_1_MASK   0xE000
#define R62_SERIAL_BYTE_2_0_LRCLK_SRC_IC_1_SHIFT  13

/* SERIAL_BYTE_2_1 (IC 1) */
#define R63_SERIAL_BYTE_2_1_FS_IC_1               0x2    /* 010b	[2:0] */
#define R63_SERIAL_BYTE_2_1_CLK_DOMAIN_IC_1       0x0    /* 00b	[4:3] */
#define R63_SERIAL_BYTE_2_1_TRISTATE_IC_1         0x0    /* 0b	[5] */
#define R63_SERIAL_BYTE_2_1_FS_IC_1_MASK          0x7
#define R63_SERIAL_BYTE_2_1_FS_IC_1_SHIFT         0
#define R63_SERIAL_BYTE_2_1_CLK_DOMAIN_IC_1_MASK  0x18
#define R63_SERIAL_BYTE_2_1_CLK_DOMAIN_IC_1_SHIFT 3
#define R63_SERIAL_BYTE_2_1_TRISTATE_IC_1_MASK    0x20
#define R63_SERIAL_BYTE_2_1_TRISTATE_IC_1_SHIFT   5

/* SERIAL_BYTE_3_0 (IC 1) */
#define R64_SERIAL_BYTE_3_0_TDM_MODE_IC_1         0x2    /* 010b	[2:0] */
#define R64_SERIAL_BYTE_3_0_DATA_FMT_IC_1         0x1    /* 01b	[4:3] */
#define R64_SERIAL_BYTE_3_0_WORD_LEN_IC_1         0x2    /* 10b	[6:5] */
#define R64_SERIAL_BYTE_3_0_BCLK_POL_IC_1         0x1    /* 1b	[7] */
#define R64_SERIAL_BYTE_3_0_LRCLK_POL_IC_1        0x1    /* 1b	[8] */
#define R64_SERIAL_BYTE_3_0_LRCLK_MODE_IC_1       0x1    /* 1b	[9] */
#define R64_SERIAL_BYTE_3_0_BCLK_SRC_IC_1         0x4    /* 100b	[12:10] */
#define R64_SERIAL_BYTE_3_0_LRCLK_SRC_IC_1        0x4    /* 100b	[15:13] */
#define R64_SERIAL_BYTE_3_0_TDM_MODE_IC_1_MASK    0x7
#define R64_SERIAL_BYTE_3_0_TDM_MODE_IC_1_SHIFT   0
#define R64_SERIAL_BYTE_3_0_DATA_FMT_IC_1_MASK    0x18
#define R64_SERIAL_BYTE_3_0_DATA_FMT_IC_1_SHIFT   3
#define R64_SERIAL_BYTE_3_0_WORD_LEN_IC_1_MASK    0x60
#define R64_SERIAL_BYTE_3_0_WORD_LEN_IC_1_SHIFT   5
#define R64_SERIAL_BYTE_3_0_BCLK_POL_IC_1_MASK    0x80
#define R64_SERIAL_BYTE_3_0_BCLK_POL_IC_1_SHIFT   7
#define R64_SERIAL_BYTE_3_0_LRCLK_POL_IC_1_MASK   0x100
#define R64_SERIAL_BYTE_3_0_LRCLK_POL_IC_1_SHIFT  8
#define R64_SERIAL_BYTE_3_0_LRCLK_MODE_IC_1_MASK  0x200
#define R64_SERIAL_BYTE_3_0_LRCLK_MODE_IC_1_SHIFT 9
#define R64_SERIAL_BYTE_3_0_BCLK_SRC_IC_1_MASK    0x1C00
#define R64_SERIAL_BYTE_3_0_BCLK_SRC_IC_1_SHIFT   10
#define R64_SERIAL_BYTE_3_0_LRCLK_SRC_IC_1_MASK   0xE000
#define R64_SERIAL_BYTE_3_0_LRCLK_SRC_IC_1_SHIFT  13

/* SERIAL_BYTE_3_1 (IC 1) */
#define R65_SERIAL_BYTE_3_1_FS_IC_1               0x2    /* 010b	[2:0] */
#define R65_SERIAL_BYTE_3_1_CLK_DOMAIN_IC_1       0x0    /* 00b	[4:3] */
#define R65_SERIAL_BYTE_3_1_TRISTATE_IC_1         0x0    /* 0b	[5] */
#define R65_SERIAL_BYTE_3_1_FS_IC_1_MASK          0x7
#define R65_SERIAL_BYTE_3_1_FS_IC_1_SHIFT         0
#define R65_SERIAL_BYTE_3_1_CLK_DOMAIN_IC_1_MASK  0x18
#define R65_SERIAL_BYTE_3_1_CLK_DOMAIN_IC_1_SHIFT 3
#define R65_SERIAL_BYTE_3_1_TRISTATE_IC_1_MASK    0x20
#define R65_SERIAL_BYTE_3_1_TRISTATE_IC_1_SHIFT   5

/* SERIAL_BYTE_4_0 (IC 1) */
#define R66_SERIAL_BYTE_4_0_TDM_MODE_IC_1         0x2    /* 010b	[2:0] */
#define R66_SERIAL_BYTE_4_0_DATA_FMT_IC_1         0x1    /* 01b	[4:3] */
#define R66_SERIAL_BYTE_4_0_WORD_LEN_IC_1         0x2    /* 10b	[6:5] */
#define R66_SERIAL_BYTE_4_0_BCLK_POL_IC_1         0x1    /* 1b	[7] */
#define R66_SERIAL_BYTE_4_0_LRCLK_POL_IC_1        0x1    /* 1b	[8] */
#define R66_SERIAL_BYTE_4_0_LRCLK_MODE_IC_1       0x1    /* 1b	[9] */
#define R66_SERIAL_BYTE_4_0_BCLK_SRC_IC_1         0x4    /* 100b	[12:10] */
#define R66_SERIAL_BYTE_4_0_LRCLK_SRC_IC_1        0x4    /* 100b	[15:13] */
#define R66_SERIAL_BYTE_4_0_TDM_MODE_IC_1_MASK    0x7
#define R66_SERIAL_BYTE_4_0_TDM_MODE_IC_1_SHIFT   0
#define R66_SERIAL_BYTE_4_0_DATA_FMT_IC_1_MASK    0x18
#define R66_SERIAL_BYTE_4_0_DATA_FMT_IC_1_SHIFT   3
#define R66_SERIAL_BYTE_4_0_WORD_LEN_IC_1_MASK    0x60
#define R66_SERIAL_BYTE_4_0_WORD_LEN_IC_1_SHIFT   5
#define R66_SERIAL_BYTE_4_0_BCLK_POL_IC_1_MASK    0x80
#define R66_SERIAL_BYTE_4_0_BCLK_POL_IC_1_SHIFT   7
#define R66_SERIAL_BYTE_4_0_LRCLK_POL_IC_1_MASK   0x100
#define R66_SERIAL_BYTE_4_0_LRCLK_POL_IC_1_SHIFT  8
#define R66_SERIAL_BYTE_4_0_LRCLK_MODE_IC_1_MASK  0x200
#define R66_SERIAL_BYTE_4_0_LRCLK_MODE_IC_1_SHIFT 9
#define R66_SERIAL_BYTE_4_0_BCLK_SRC_IC_1_MASK    0x1C00
#define R66_SERIAL_BYTE_4_0_BCLK_SRC_IC_1_SHIFT   10
#define R66_SERIAL_BYTE_4_0_LRCLK_SRC_IC_1_MASK   0xE000
#define R66_SERIAL_BYTE_4_0_LRCLK_SRC_IC_1_SHIFT  13

/* SERIAL_BYTE_4_1 (IC 1) */
#define R67_SERIAL_BYTE_4_1_FS_IC_1               0x2    /* 010b	[2:0] */
#define R67_SERIAL_BYTE_4_1_CLK_DOMAIN_IC_1       0x0    /* 00b	[4:3] */
#define R67_SERIAL_BYTE_4_1_TRISTATE_IC_1         0x0    /* 0b	[5] */
#define R67_SERIAL_BYTE_4_1_FS_IC_1_MASK          0x7
#define R67_SERIAL_BYTE_4_1_FS_IC_1_SHIFT         0
#define R67_SERIAL_BYTE_4_1_CLK_DOMAIN_IC_1_MASK  0x18
#define R67_SERIAL_BYTE_4_1_CLK_DOMAIN_IC_1_SHIFT 3
#define R67_SERIAL_BYTE_4_1_TRISTATE_IC_1_MASK    0x20
#define R67_SERIAL_BYTE_4_1_TRISTATE_IC_1_SHIFT   5

/* SERIAL_BYTE_5_0 (IC 1) */
#define R68_SERIAL_BYTE_5_0_TDM_MODE_IC_1         0x2    /* 010b	[2:0] */
#define R68_SERIAL_BYTE_5_0_DATA_FMT_IC_1         0x1    /* 01b	[4:3] */
#define R68_SERIAL_BYTE_5_0_WORD_LEN_IC_1         0x0    /* 00b	[6:5] */
#define R68_SERIAL_BYTE_5_0_BCLK_POL_IC_1         0x0    /* 0b	[7] */
#define R68_SERIAL_BYTE_5_0_LRCLK_POL_IC_1        0x0    /* 0b	[8] */
#define R68_SERIAL_BYTE_5_0_LRCLK_MODE_IC_1       0x1    /* 1b	[9] */
#define R68_SERIAL_BYTE_5_0_BCLK_SRC_IC_1         0x1    /* 001b	[12:10] */
#define R68_SERIAL_BYTE_5_0_LRCLK_SRC_IC_1        0x1    /* 001b	[15:13] */
#define R68_SERIAL_BYTE_5_0_TDM_MODE_IC_1_MASK    0x7
#define R68_SERIAL_BYTE_5_0_TDM_MODE_IC_1_SHIFT   0
#define R68_SERIAL_BYTE_5_0_DATA_FMT_IC_1_MASK    0x18
#define R68_SERIAL_BYTE_5_0_DATA_FMT_IC_1_SHIFT   3
#define R68_SERIAL_BYTE_5_0_WORD_LEN_IC_1_MASK    0x60
#define R68_SERIAL_BYTE_5_0_WORD_LEN_IC_1_SHIFT   5
#define R68_SERIAL_BYTE_5_0_BCLK_POL_IC_1_MASK    0x80
#define R68_SERIAL_BYTE_5_0_BCLK_POL_IC_1_SHIFT   7
#define R68_SERIAL_BYTE_5_0_LRCLK_POL_IC_1_MASK   0x100
#define R68_SERIAL_BYTE_5_0_LRCLK_POL_IC_1_SHIFT  8
#define R68_SERIAL_BYTE_5_0_LRCLK_MODE_IC_1_MASK  0x200
#define R68_SERIAL_BYTE_5_0_LRCLK_MODE_IC_1_SHIFT 9
#define R68_SERIAL_BYTE_5_0_BCLK_SRC_IC_1_MASK    0x1C00
#define R68_SERIAL_BYTE_5_0_BCLK_SRC_IC_1_SHIFT   10
#define R68_SERIAL_BYTE_5_0_LRCLK_SRC_IC_1_MASK   0xE000
#define R68_SERIAL_BYTE_5_0_LRCLK_SRC_IC_1_SHIFT  13

/* SERIAL_BYTE_5_1 (IC 1) */
#define R69_SERIAL_BYTE_5_1_FS_IC_1               0x2    /* 010b	[2:0] */
#define R69_SERIAL_BYTE_5_1_CLK_DOMAIN_IC_1       0x0    /* 00b	[4:3] */
#define R69_SERIAL_BYTE_5_1_TRISTATE_IC_1         0x0    /* 0b	[5] */
#define R69_SERIAL_BYTE_5_1_FS_IC_1_MASK          0x7
#define R69_SERIAL_BYTE_5_1_FS_IC_1_SHIFT         0
#define R69_SERIAL_BYTE_5_1_CLK_DOMAIN_IC_1_MASK  0x18
#define R69_SERIAL_BYTE_5_1_CLK_DOMAIN_IC_1_SHIFT 3
#define R69_SERIAL_BYTE_5_1_TRISTATE_IC_1_MASK    0x20
#define R69_SERIAL_BYTE_5_1_TRISTATE_IC_1_SHIFT   5

/* SERIAL_BYTE_6_0 (IC 1) */
#define R70_SERIAL_BYTE_6_0_TDM_MODE_IC_1         0x0    /* 000b	[2:0] */
#define R70_SERIAL_BYTE_6_0_DATA_FMT_IC_1         0x0    /* 00b	[4:3] */
#define R70_SERIAL_BYTE_6_0_WORD_LEN_IC_1         0x0    /* 00b	[6:5] */
#define R70_SERIAL_BYTE_6_0_BCLK_POL_IC_1         0x0    /* 0b	[7] */
#define R70_SERIAL_BYTE_6_0_LRCLK_POL_IC_1        0x0    /* 0b	[8] */
#define R70_SERIAL_BYTE_6_0_LRCLK_MODE_IC_1       0x0    /* 0b	[9] */
#define R70_SERIAL_BYTE_6_0_BCLK_SRC_IC_1         0x0    /* 000b	[12:10] */
#define R70_SERIAL_BYTE_6_0_LRCLK_SRC_IC_1        0x0    /* 000b	[15:13] */
#define R70_SERIAL_BYTE_6_0_TDM_MODE_IC_1_MASK    0x7
#define R70_SERIAL_BYTE_6_0_TDM_MODE_IC_1_SHIFT   0
#define R70_SERIAL_BYTE_6_0_DATA_FMT_IC_1_MASK    0x18
#define R70_SERIAL_BYTE_6_0_DATA_FMT_IC_1_SHIFT   3
#define R70_SERIAL_BYTE_6_0_WORD_LEN_IC_1_MASK    0x60
#define R70_SERIAL_BYTE_6_0_WORD_LEN_IC_1_SHIFT   5
#define R70_SERIAL_BYTE_6_0_BCLK_POL_IC_1_MASK    0x80
#define R70_SERIAL_BYTE_6_0_BCLK_POL_IC_1_SHIFT   7
#define R70_SERIAL_BYTE_6_0_LRCLK_POL_IC_1_MASK   0x100
#define R70_SERIAL_BYTE_6_0_LRCLK_POL_IC_1_SHIFT  8
#define R70_SERIAL_BYTE_6_0_LRCLK_MODE_IC_1_MASK  0x200
#define R70_SERIAL_BYTE_6_0_LRCLK_MODE_IC_1_SHIFT 9
#define R70_SERIAL_BYTE_6_0_BCLK_SRC_IC_1_MASK    0x1C00
#define R70_SERIAL_BYTE_6_0_BCLK_SRC_IC_1_SHIFT   10
#define R70_SERIAL_BYTE_6_0_LRCLK_SRC_IC_1_MASK   0xE000
#define R70_SERIAL_BYTE_6_0_LRCLK_SRC_IC_1_SHIFT  13

/* SERIAL_BYTE_6_1 (IC 1) */
#define R71_SERIAL_BYTE_6_1_FS_IC_1               0x2    /* 010b	[2:0] */
#define R71_SERIAL_BYTE_6_1_CLK_DOMAIN_IC_1       0x0    /* 00b	[4:3] */
#define R71_SERIAL_BYTE_6_1_TRISTATE_IC_1         0x0    /* 0b	[5] */
#define R71_SERIAL_BYTE_6_1_FS_IC_1_MASK          0x7
#define R71_SERIAL_BYTE_6_1_FS_IC_1_SHIFT         0
#define R71_SERIAL_BYTE_6_1_CLK_DOMAIN_IC_1_MASK  0x18
#define R71_SERIAL_BYTE_6_1_CLK_DOMAIN_IC_1_SHIFT 3
#define R71_SERIAL_BYTE_6_1_TRISTATE_IC_1_MASK    0x20
#define R71_SERIAL_BYTE_6_1_TRISTATE_IC_1_SHIFT   5

/* SERIAL_BYTE_7_0 (IC 1) */
#define R72_SERIAL_BYTE_7_0_TDM_MODE_IC_1         0x0    /* 000b	[2:0] */
#define R72_SERIAL_BYTE_7_0_DATA_FMT_IC_1         0x0    /* 00b	[4:3] */
#define R72_SERIAL_BYTE_7_0_WORD_LEN_IC_1         0x0    /* 00b	[6:5] */
#define R72_SERIAL_BYTE_7_0_BCLK_POL_IC_1         0x0    /* 0b	[7] */
#define R72_SERIAL_BYTE_7_0_LRCLK_POL_IC_1        0x0    /* 0b	[8] */
#define R72_SERIAL_BYTE_7_0_LRCLK_MODE_IC_1       0x0    /* 0b	[9] */
#define R72_SERIAL_BYTE_7_0_BCLK_SRC_IC_1         0x0    /* 000b	[12:10] */
#define R72_SERIAL_BYTE_7_0_LRCLK_SRC_IC_1        0x0    /* 000b	[15:13] */
#define R72_SERIAL_BYTE_7_0_TDM_MODE_IC_1_MASK    0x7
#define R72_SERIAL_BYTE_7_0_TDM_MODE_IC_1_SHIFT   0
#define R72_SERIAL_BYTE_7_0_DATA_FMT_IC_1_MASK    0x18
#define R72_SERIAL_BYTE_7_0_DATA_FMT_IC_1_SHIFT   3
#define R72_SERIAL_BYTE_7_0_WORD_LEN_IC_1_MASK    0x60
#define R72_SERIAL_BYTE_7_0_WORD_LEN_IC_1_SHIFT   5
#define R72_SERIAL_BYTE_7_0_BCLK_POL_IC_1_MASK    0x80
#define R72_SERIAL_BYTE_7_0_BCLK_POL_IC_1_SHIFT   7
#define R72_SERIAL_BYTE_7_0_LRCLK_POL_IC_1_MASK   0x100
#define R72_SERIAL_BYTE_7_0_LRCLK_POL_IC_1_SHIFT  8
#define R72_SERIAL_BYTE_7_0_LRCLK_MODE_IC_1_MASK  0x200
#define R72_SERIAL_BYTE_7_0_LRCLK_MODE_IC_1_SHIFT 9
#define R72_SERIAL_BYTE_7_0_BCLK_SRC_IC_1_MASK    0x1C00
#define R72_SERIAL_BYTE_7_0_BCLK_SRC_IC_1_SHIFT   10
#define R72_SERIAL_BYTE_7_0_LRCLK_SRC_IC_1_MASK   0xE000
#define R72_SERIAL_BYTE_7_0_LRCLK_SRC_IC_1_SHIFT  13

/* SERIAL_BYTE_7_1 (IC 1) */
#define R73_SERIAL_BYTE_7_1_FS_IC_1               0x2    /* 010b	[2:0] */
#define R73_SERIAL_BYTE_7_1_CLK_DOMAIN_IC_1       0x0    /* 00b	[4:3] */
#define R73_SERIAL_BYTE_7_1_TRISTATE_IC_1         0x0    /* 0b	[5] */
#define R73_SERIAL_BYTE_7_1_FS_IC_1_MASK          0x7
#define R73_SERIAL_BYTE_7_1_FS_IC_1_SHIFT         0
#define R73_SERIAL_BYTE_7_1_CLK_DOMAIN_IC_1_MASK  0x18
#define R73_SERIAL_BYTE_7_1_CLK_DOMAIN_IC_1_SHIFT 3
#define R73_SERIAL_BYTE_7_1_TRISTATE_IC_1_MASK    0x20
#define R73_SERIAL_BYTE_7_1_TRISTATE_IC_1_SHIFT   5

/* FTDM_IN0 (IC 1) */
#define R74_FTDM_IN0_BYTE_IN_POS_IC_1             0x0    /* 00b	[1:0] */
#define R74_FTDM_IN0_CHANNEL_IN_POS_IC_1          0x0    /* 000b	[4:2] */
#define R74_FTDM_IN0_SERIAL_IN_SEL_IC_1           0x0    /* 0b	[5] */
#define R74_FTDM_IN0_REVERSE_IN_BYTE_IC_1         0x0    /* 0b	[6] */
#define R74_FTDM_IN0_SLOT_ENABLE_IN_IC_1          0x0    /* 0b	[7] */
#define R74_FTDM_IN0_BYTE_IN_POS_IC_1_MASK        0x3
#define R74_FTDM_IN0_BYTE_IN_POS_IC_1_SHIFT       0
#define R74_FTDM_IN0_CHANNEL_IN_POS_IC_1_MASK     0x1C
#define R74_FTDM_IN0_CHANNEL_IN_POS_IC_1_SHIFT    2
#define R74_FTDM_IN0_SERIAL_IN_SEL_IC_1_MASK      0x20
#define R74_FTDM_IN0_SERIAL_IN_SEL_IC_1_SHIFT     5
#define R74_FTDM_IN0_REVERSE_IN_BYTE_IC_1_MASK    0x40
#define R74_FTDM_IN0_REVERSE_IN_BYTE_IC_1_SHIFT   6
#define R74_FTDM_IN0_SLOT_ENABLE_IN_IC_1_MASK     0x80
#define R74_FTDM_IN0_SLOT_ENABLE_IN_IC_1_SHIFT    7

/* FTDM_IN1 (IC 1) */
#define R75_FTDM_IN1_BYTE_IN_POS_IC_1             0x0    /* 00b	[1:0] */
#define R75_FTDM_IN1_CHANNEL_IN_POS_IC_1          0x0    /* 000b	[4:2] */
#define R75_FTDM_IN1_SERIAL_IN_SEL_IC_1           0x0    /* 0b	[5] */
#define R75_FTDM_IN1_REVERSE_IN_BYTE_IC_1         0x0    /* 0b	[6] */
#define R75_FTDM_IN1_SLOT_ENABLE_IN_IC_1          0x0    /* 0b	[7] */
#define R75_FTDM_IN1_BYTE_IN_POS_IC_1_MASK        0x3
#define R75_FTDM_IN1_BYTE_IN_POS_IC_1_SHIFT       0
#define R75_FTDM_IN1_CHANNEL_IN_POS_IC_1_MASK     0x1C
#define R75_FTDM_IN1_CHANNEL_IN_POS_IC_1_SHIFT    2
#define R75_FTDM_IN1_SERIAL_IN_SEL_IC_1_MASK      0x20
#define R75_FTDM_IN1_SERIAL_IN_SEL_IC_1_SHIFT     5
#define R75_FTDM_IN1_REVERSE_IN_BYTE_IC_1_MASK    0x40
#define R75_FTDM_IN1_REVERSE_IN_BYTE_IC_1_SHIFT   6
#define R75_FTDM_IN1_SLOT_ENABLE_IN_IC_1_MASK     0x80
#define R75_FTDM_IN1_SLOT_ENABLE_IN_IC_1_SHIFT    7

/* FTDM_IN2 (IC 1) */
#define R76_FTDM_IN2_BYTE_IN_POS_IC_1             0x0    /* 00b	[1:0] */
#define R76_FTDM_IN2_CHANNEL_IN_POS_IC_1          0x0    /* 000b	[4:2] */
#define R76_FTDM_IN2_SERIAL_IN_SEL_IC_1           0x0    /* 0b	[5] */
#define R76_FTDM_IN2_REVERSE_IN_BYTE_IC_1         0x0    /* 0b	[6] */
#define R76_FTDM_IN2_SLOT_ENABLE_IN_IC_1          0x0    /* 0b	[7] */
#define R76_FTDM_IN2_BYTE_IN_POS_IC_1_MASK        0x3
#define R76_FTDM_IN2_BYTE_IN_POS_IC_1_SHIFT       0
#define R76_FTDM_IN2_CHANNEL_IN_POS_IC_1_MASK     0x1C
#define R76_FTDM_IN2_CHANNEL_IN_POS_IC_1_SHIFT    2
#define R76_FTDM_IN2_SERIAL_IN_SEL_IC_1_MASK      0x20
#define R76_FTDM_IN2_SERIAL_IN_SEL_IC_1_SHIFT     5
#define R76_FTDM_IN2_REVERSE_IN_BYTE_IC_1_MASK    0x40
#define R76_FTDM_IN2_REVERSE_IN_BYTE_IC_1_SHIFT   6
#define R76_FTDM_IN2_SLOT_ENABLE_IN_IC_1_MASK     0x80
#define R76_FTDM_IN2_SLOT_ENABLE_IN_IC_1_SHIFT    7

/* FTDM_IN3 (IC 1) */
#define R77_FTDM_IN3_BYTE_IN_POS_IC_1             0x0    /* 00b	[1:0] */
#define R77_FTDM_IN3_CHANNEL_IN_POS_IC_1          0x0    /* 000b	[4:2] */
#define R77_FTDM_IN3_SERIAL_IN_SEL_IC_1           0x0    /* 0b	[5] */
#define R77_FTDM_IN3_REVERSE_IN_BYTE_IC_1         0x0    /* 0b	[6] */
#define R77_FTDM_IN3_SLOT_ENABLE_IN_IC_1          0x0    /* 0b	[7] */
#define R77_FTDM_IN3_BYTE_IN_POS_IC_1_MASK        0x3
#define R77_FTDM_IN3_BYTE_IN_POS_IC_1_SHIFT       0
#define R77_FTDM_IN3_CHANNEL_IN_POS_IC_1_MASK     0x1C
#define R77_FTDM_IN3_CHANNEL_IN_POS_IC_1_SHIFT    2
#define R77_FTDM_IN3_SERIAL_IN_SEL_IC_1_MASK      0x20
#define R77_FTDM_IN3_SERIAL_IN_SEL_IC_1_SHIFT     5
#define R77_FTDM_IN3_REVERSE_IN_BYTE_IC_1_MASK    0x40
#define R77_FTDM_IN3_REVERSE_IN_BYTE_IC_1_SHIFT   6
#define R77_FTDM_IN3_SLOT_ENABLE_IN_IC_1_MASK     0x80
#define R77_FTDM_IN3_SLOT_ENABLE_IN_IC_1_SHIFT    7

/* FTDM_IN4 (IC 1) */
#define R78_FTDM_IN4_BYTE_IN_POS_IC_1             0x0    /* 00b	[1:0] */
#define R78_FTDM_IN4_CHANNEL_IN_POS_IC_1          0x0    /* 000b	[4:2] */
#define R78_FTDM_IN4_SERIAL_IN_SEL_IC_1           0x0    /* 0b	[5] */
#define R78_FTDM_IN4_REVERSE_IN_BYTE_IC_1         0x0    /* 0b	[6] */
#define R78_FTDM_IN4_SLOT_ENABLE_IN_IC_1          0x0    /* 0b	[7] */
#define R78_FTDM_IN4_BYTE_IN_POS_IC_1_MASK        0x3
#define R78_FTDM_IN4_BYTE_IN_POS_IC_1_SHIFT       0
#define R78_FTDM_IN4_CHANNEL_IN_POS_IC_1_MASK     0x1C
#define R78_FTDM_IN4_CHANNEL_IN_POS_IC_1_SHIFT    2
#define R78_FTDM_IN4_SERIAL_IN_SEL_IC_1_MASK      0x20
#define R78_FTDM_IN4_SERIAL_IN_SEL_IC_1_SHIFT     5
#define R78_FTDM_IN4_REVERSE_IN_BYTE_IC_1_MASK    0x40
#define R78_FTDM_IN4_REVERSE_IN_BYTE_IC_1_SHIFT   6
#define R78_FTDM_IN4_SLOT_ENABLE_IN_IC_1_MASK     0x80
#define R78_FTDM_IN4_SLOT_ENABLE_IN_IC_1_SHIFT    7

/* FTDM_IN5 (IC 1) */
#define R79_FTDM_IN5_BYTE_IN_POS_IC_1             0x0    /* 00b	[1:0] */
#define R79_FTDM_IN5_CHANNEL_IN_POS_IC_1          0x0    /* 000b	[4:2] */
#define R79_FTDM_IN5_SERIAL_IN_SEL_IC_1           0x0    /* 0b	[5] */
#define R79_FTDM_IN5_REVERSE_IN_BYTE_IC_1         0x0    /* 0b	[6] */
#define R79_FTDM_IN5_SLOT_ENABLE_IN_IC_1          0x0    /* 0b	[7] */
#define R79_FTDM_IN5_BYTE_IN_POS_IC_1_MASK        0x3
#define R79_FTDM_IN5_BYTE_IN_POS_IC_1_SHIFT       0
#define R79_FTDM_IN5_CHANNEL_IN_POS_IC_1_MASK     0x1C
#define R79_FTDM_IN5_CHANNEL_IN_POS_IC_1_SHIFT    2
#define R79_FTDM_IN5_SERIAL_IN_SEL_IC_1_MASK      0x20
#define R79_FTDM_IN5_SERIAL_IN_SEL_IC_1_SHIFT     5
#define R79_FTDM_IN5_REVERSE_IN_BYTE_IC_1_MASK    0x40
#define R79_FTDM_IN5_REVERSE_IN_BYTE_IC_1_SHIFT   6
#define R79_FTDM_IN5_SLOT_ENABLE_IN_IC_1_MASK     0x80
#define R79_FTDM_IN5_SLOT_ENABLE_IN_IC_1_SHIFT    7

/* FTDM_IN6 (IC 1) */
#define R80_FTDM_IN6_BYTE_IN_POS_IC_1             0x0    /* 00b	[1:0] */
#define R80_FTDM_IN6_CHANNEL_IN_POS_IC_1          0x0    /* 000b	[4:2] */
#define R80_FTDM_IN6_SERIAL_IN_SEL_IC_1           0x0    /* 0b	[5] */
#define R80_FTDM_IN6_REVERSE_IN_BYTE_IC_1         0x0    /* 0b	[6] */
#define R80_FTDM_IN6_SLOT_ENABLE_IN_IC_1          0x0    /* 0b	[7] */
#define R80_FTDM_IN6_BYTE_IN_POS_IC_1_MASK        0x3
#define R80_FTDM_IN6_BYTE_IN_POS_IC_1_SHIFT       0
#define R80_FTDM_IN6_CHANNEL_IN_POS_IC_1_MASK     0x1C
#define R80_FTDM_IN6_CHANNEL_IN_POS_IC_1_SHIFT    2
#define R80_FTDM_IN6_SERIAL_IN_SEL_IC_1_MASK      0x20
#define R80_FTDM_IN6_SERIAL_IN_SEL_IC_1_SHIFT     5
#define R80_FTDM_IN6_REVERSE_IN_BYTE_IC_1_MASK    0x40
#define R80_FTDM_IN6_REVERSE_IN_BYTE_IC_1_SHIFT   6
#define R80_FTDM_IN6_SLOT_ENABLE_IN_IC_1_MASK     0x80
#define R80_FTDM_IN6_SLOT_ENABLE_IN_IC_1_SHIFT    7

/* FTDM_IN7 (IC 1) */
#define R81_FTDM_IN7_BYTE_IN_POS_IC_1             0x0    /* 00b	[1:0] */
#define R81_FTDM_IN7_CHANNEL_IN_POS_IC_1          0x0    /* 000b	[4:2] */
#define R81_FTDM_IN7_SERIAL_IN_SEL_IC_1           0x0    /* 0b	[5] */
#define R81_FTDM_IN7_REVERSE_IN_BYTE_IC_1         0x0    /* 0b	[6] */
#define R81_FTDM_IN7_SLOT_ENABLE_IN_IC_1          0x0    /* 0b	[7] */
#define R81_FTDM_IN7_BYTE_IN_POS_IC_1_MASK        0x3
#define R81_FTDM_IN7_BYTE_IN_POS_IC_1_SHIFT       0
#define R81_FTDM_IN7_CHANNEL_IN_POS_IC_1_MASK     0x1C
#define R81_FTDM_IN7_CHANNEL_IN_POS_IC_1_SHIFT    2
#define R81_FTDM_IN7_SERIAL_IN_SEL_IC_1_MASK      0x20
#define R81_FTDM_IN7_SERIAL_IN_SEL_IC_1_SHIFT     5
#define R81_FTDM_IN7_REVERSE_IN_BYTE_IC_1_MASK    0x40
#define R81_FTDM_IN7_REVERSE_IN_BYTE_IC_1_SHIFT   6
#define R81_FTDM_IN7_SLOT_ENABLE_IN_IC_1_MASK     0x80
#define R81_FTDM_IN7_SLOT_ENABLE_IN_IC_1_SHIFT    7

/* FTDM_IN8 (IC 1) */
#define R82_FTDM_IN8_BYTE_IN_POS_IC_1             0x0    /* 00b	[1:0] */
#define R82_FTDM_IN8_CHANNEL_IN_POS_IC_1          0x0    /* 000b	[4:2] */
#define R82_FTDM_IN8_SERIAL_IN_SEL_IC_1           0x0    /* 0b	[5] */
#define R82_FTDM_IN8_REVERSE_IN_BYTE_IC_1         0x0    /* 0b	[6] */
#define R82_FTDM_IN8_SLOT_ENABLE_IN_IC_1          0x0    /* 0b	[7] */
#define R82_FTDM_IN8_BYTE_IN_POS_IC_1_MASK        0x3
#define R82_FTDM_IN8_BYTE_IN_POS_IC_1_SHIFT       0
#define R82_FTDM_IN8_CHANNEL_IN_POS_IC_1_MASK     0x1C
#define R82_FTDM_IN8_CHANNEL_IN_POS_IC_1_SHIFT    2
#define R82_FTDM_IN8_SERIAL_IN_SEL_IC_1_MASK      0x20
#define R82_FTDM_IN8_SERIAL_IN_SEL_IC_1_SHIFT     5
#define R82_FTDM_IN8_REVERSE_IN_BYTE_IC_1_MASK    0x40
#define R82_FTDM_IN8_REVERSE_IN_BYTE_IC_1_SHIFT   6
#define R82_FTDM_IN8_SLOT_ENABLE_IN_IC_1_MASK     0x80
#define R82_FTDM_IN8_SLOT_ENABLE_IN_IC_1_SHIFT    7

/* FTDM_IN9 (IC 1) */
#define R83_FTDM_IN9_BYTE_IN_POS_IC_1             0x0    /* 00b	[1:0] */
#define R83_FTDM_IN9_CHANNEL_IN_POS_IC_1          0x0    /* 000b	[4:2] */
#define R83_FTDM_IN9_SERIAL_IN_SEL_IC_1           0x0    /* 0b	[5] */
#define R83_FTDM_IN9_REVERSE_IN_BYTE_IC_1         0x0    /* 0b	[6] */
#define R83_FTDM_IN9_SLOT_ENABLE_IN_IC_1          0x0    /* 0b	[7] */
#define R83_FTDM_IN9_BYTE_IN_POS_IC_1_MASK        0x3
#define R83_FTDM_IN9_BYTE_IN_POS_IC_1_SHIFT       0
#define R83_FTDM_IN9_CHANNEL_IN_POS_IC_1_MASK     0x1C
#define R83_FTDM_IN9_CHANNEL_IN_POS_IC_1_SHIFT    2
#define R83_FTDM_IN9_SERIAL_IN_SEL_IC_1_MASK      0x20
#define R83_FTDM_IN9_SERIAL_IN_SEL_IC_1_SHIFT     5
#define R83_FTDM_IN9_REVERSE_IN_BYTE_IC_1_MASK    0x40
#define R83_FTDM_IN9_REVERSE_IN_BYTE_IC_1_SHIFT   6
#define R83_FTDM_IN9_SLOT_ENABLE_IN_IC_1_MASK     0x80
#define R83_FTDM_IN9_SLOT_ENABLE_IN_IC_1_SHIFT    7

/* FTDM_IN10 (IC 1) */
#define R84_FTDM_IN10_BYTE_IN_POS_IC_1            0x0    /* 00b	[1:0] */
#define R84_FTDM_IN10_CHANNEL_IN_POS_IC_1         0x0    /* 000b	[4:2] */
#define R84_FTDM_IN10_SERIAL_IN_SEL_IC_1          0x0    /* 0b	[5] */
#define R84_FTDM_IN10_REVERSE_IN_BYTE_IC_1        0x0    /* 0b	[6] */
#define R84_FTDM_IN10_SLOT_ENABLE_IN_IC_1         0x0    /* 0b	[7] */
#define R84_FTDM_IN10_BYTE_IN_POS_IC_1_MASK       0x3
#define R84_FTDM_IN10_BYTE_IN_POS_IC_1_SHIFT      0
#define R84_FTDM_IN10_CHANNEL_IN_POS_IC_1_MASK    0x1C
#define R84_FTDM_IN10_CHANNEL_IN_POS_IC_1_SHIFT   2
#define R84_FTDM_IN10_SERIAL_IN_SEL_IC_1_MASK     0x20
#define R84_FTDM_IN10_SERIAL_IN_SEL_IC_1_SHIFT    5
#define R84_FTDM_IN10_REVERSE_IN_BYTE_IC_1_MASK   0x40
#define R84_FTDM_IN10_REVERSE_IN_BYTE_IC_1_SHIFT  6
#define R84_FTDM_IN10_SLOT_ENABLE_IN_IC_1_MASK    0x80
#define R84_FTDM_IN10_SLOT_ENABLE_IN_IC_1_SHIFT   7

/* FTDM_IN11 (IC 1) */
#define R85_FTDM_IN11_BYTE_IN_POS_IC_1            0x0    /* 00b	[1:0] */
#define R85_FTDM_IN11_CHANNEL_IN_POS_IC_1         0x0    /* 000b	[4:2] */
#define R85_FTDM_IN11_SERIAL_IN_SEL_IC_1          0x0    /* 0b	[5] */
#define R85_FTDM_IN11_REVERSE_IN_BYTE_IC_1        0x0    /* 0b	[6] */
#define R85_FTDM_IN11_SLOT_ENABLE_IN_IC_1         0x0    /* 0b	[7] */
#define R85_FTDM_IN11_BYTE_IN_POS_IC_1_MASK       0x3
#define R85_FTDM_IN11_BYTE_IN_POS_IC_1_SHIFT      0
#define R85_FTDM_IN11_CHANNEL_IN_POS_IC_1_MASK    0x1C
#define R85_FTDM_IN11_CHANNEL_IN_POS_IC_1_SHIFT   2
#define R85_FTDM_IN11_SERIAL_IN_SEL_IC_1_MASK     0x20
#define R85_FTDM_IN11_SERIAL_IN_SEL_IC_1_SHIFT    5
#define R85_FTDM_IN11_REVERSE_IN_BYTE_IC_1_MASK   0x40
#define R85_FTDM_IN11_REVERSE_IN_BYTE_IC_1_SHIFT  6
#define R85_FTDM_IN11_SLOT_ENABLE_IN_IC_1_MASK    0x80
#define R85_FTDM_IN11_SLOT_ENABLE_IN_IC_1_SHIFT   7

/* FTDM_IN12 (IC 1) */
#define R86_FTDM_IN12_BYTE_IN_POS_IC_1            0x0    /* 00b	[1:0] */
#define R86_FTDM_IN12_CHANNEL_IN_POS_IC_1         0x0    /* 000b	[4:2] */
#define R86_FTDM_IN12_SERIAL_IN_SEL_IC_1          0x0    /* 0b	[5] */
#define R86_FTDM_IN12_REVERSE_IN_BYTE_IC_1        0x0    /* 0b	[6] */
#define R86_FTDM_IN12_SLOT_ENABLE_IN_IC_1         0x0    /* 0b	[7] */
#define R86_FTDM_IN12_BYTE_IN_POS_IC_1_MASK       0x3
#define R86_FTDM_IN12_BYTE_IN_POS_IC_1_SHIFT      0
#define R86_FTDM_IN12_CHANNEL_IN_POS_IC_1_MASK    0x1C
#define R86_FTDM_IN12_CHANNEL_IN_POS_IC_1_SHIFT   2
#define R86_FTDM_IN12_SERIAL_IN_SEL_IC_1_MASK     0x20
#define R86_FTDM_IN12_SERIAL_IN_SEL_IC_1_SHIFT    5
#define R86_FTDM_IN12_REVERSE_IN_BYTE_IC_1_MASK   0x40
#define R86_FTDM_IN12_REVERSE_IN_BYTE_IC_1_SHIFT  6
#define R86_FTDM_IN12_SLOT_ENABLE_IN_IC_1_MASK    0x80
#define R86_FTDM_IN12_SLOT_ENABLE_IN_IC_1_SHIFT   7

/* FTDM_IN13 (IC 1) */
#define R87_FTDM_IN13_BYTE_IN_POS_IC_1            0x0    /* 00b	[1:0] */
#define R87_FTDM_IN13_CHANNEL_IN_POS_IC_1         0x0    /* 000b	[4:2] */
#define R87_FTDM_IN13_SERIAL_IN_SEL_IC_1          0x0    /* 0b	[5] */
#define R87_FTDM_IN13_REVERSE_IN_BYTE_IC_1        0x0    /* 0b	[6] */
#define R87_FTDM_IN13_SLOT_ENABLE_IN_IC_1         0x0    /* 0b	[7] */
#define R87_FTDM_IN13_BYTE_IN_POS_IC_1_MASK       0x3
#define R87_FTDM_IN13_BYTE_IN_POS_IC_1_SHIFT      0
#define R87_FTDM_IN13_CHANNEL_IN_POS_IC_1_MASK    0x1C
#define R87_FTDM_IN13_CHANNEL_IN_POS_IC_1_SHIFT   2
#define R87_FTDM_IN13_SERIAL_IN_SEL_IC_1_MASK     0x20
#define R87_FTDM_IN13_SERIAL_IN_SEL_IC_1_SHIFT    5
#define R87_FTDM_IN13_REVERSE_IN_BYTE_IC_1_MASK   0x40
#define R87_FTDM_IN13_REVERSE_IN_BYTE_IC_1_SHIFT  6
#define R87_FTDM_IN13_SLOT_ENABLE_IN_IC_1_MASK    0x80
#define R87_FTDM_IN13_SLOT_ENABLE_IN_IC_1_SHIFT   7

/* FTDM_IN14 (IC 1) */
#define R88_FTDM_IN14_BYTE_IN_POS_IC_1            0x0    /* 00b	[1:0] */
#define R88_FTDM_IN14_CHANNEL_IN_POS_IC_1         0x0    /* 000b	[4:2] */
#define R88_FTDM_IN14_SERIAL_IN_SEL_IC_1          0x0    /* 0b	[5] */
#define R88_FTDM_IN14_REVERSE_IN_BYTE_IC_1        0x0    /* 0b	[6] */
#define R88_FTDM_IN14_SLOT_ENABLE_IN_IC_1         0x0    /* 0b	[7] */
#define R88_FTDM_IN14_BYTE_IN_POS_IC_1_MASK       0x3
#define R88_FTDM_IN14_BYTE_IN_POS_IC_1_SHIFT      0
#define R88_FTDM_IN14_CHANNEL_IN_POS_IC_1_MASK    0x1C
#define R88_FTDM_IN14_CHANNEL_IN_POS_IC_1_SHIFT   2
#define R88_FTDM_IN14_SERIAL_IN_SEL_IC_1_MASK     0x20
#define R88_FTDM_IN14_SERIAL_IN_SEL_IC_1_SHIFT    5
#define R88_FTDM_IN14_REVERSE_IN_BYTE_IC_1_MASK   0x40
#define R88_FTDM_IN14_REVERSE_IN_BYTE_IC_1_SHIFT  6
#define R88_FTDM_IN14_SLOT_ENABLE_IN_IC_1_MASK    0x80
#define R88_FTDM_IN14_SLOT_ENABLE_IN_IC_1_SHIFT   7

/* FTDM_IN15 (IC 1) */
#define R89_FTDM_IN15_BYTE_IN_POS_IC_1            0x0    /* 00b	[1:0] */
#define R89_FTDM_IN15_CHANNEL_IN_POS_IC_1         0x0    /* 000b	[4:2] */
#define R89_FTDM_IN15_SERIAL_IN_SEL_IC_1          0x0    /* 0b	[5] */
#define R89_FTDM_IN15_REVERSE_IN_BYTE_IC_1        0x0    /* 0b	[6] */
#define R89_FTDM_IN15_SLOT_ENABLE_IN_IC_1         0x0    /* 0b	[7] */
#define R89_FTDM_IN15_BYTE_IN_POS_IC_1_MASK       0x3
#define R89_FTDM_IN15_BYTE_IN_POS_IC_1_SHIFT      0
#define R89_FTDM_IN15_CHANNEL_IN_POS_IC_1_MASK    0x1C
#define R89_FTDM_IN15_CHANNEL_IN_POS_IC_1_SHIFT   2
#define R89_FTDM_IN15_SERIAL_IN_SEL_IC_1_MASK     0x20
#define R89_FTDM_IN15_SERIAL_IN_SEL_IC_1_SHIFT    5
#define R89_FTDM_IN15_REVERSE_IN_BYTE_IC_1_MASK   0x40
#define R89_FTDM_IN15_REVERSE_IN_BYTE_IC_1_SHIFT  6
#define R89_FTDM_IN15_SLOT_ENABLE_IN_IC_1_MASK    0x80
#define R89_FTDM_IN15_SLOT_ENABLE_IN_IC_1_SHIFT   7

/* FTDM_IN16 (IC 1) */
#define R90_FTDM_IN16_BYTE_IN_POS_IC_1            0x0    /* 00b	[1:0] */
#define R90_FTDM_IN16_CHANNEL_IN_POS_IC_1         0x0    /* 000b	[4:2] */
#define R90_FTDM_IN16_SERIAL_IN_SEL_IC_1          0x0    /* 0b	[5] */
#define R90_FTDM_IN16_REVERSE_IN_BYTE_IC_1        0x0    /* 0b	[6] */
#define R90_FTDM_IN16_SLOT_ENABLE_IN_IC_1         0x0    /* 0b	[7] */
#define R90_FTDM_IN16_BYTE_IN_POS_IC_1_MASK       0x3
#define R90_FTDM_IN16_BYTE_IN_POS_IC_1_SHIFT      0
#define R90_FTDM_IN16_CHANNEL_IN_POS_IC_1_MASK    0x1C
#define R90_FTDM_IN16_CHANNEL_IN_POS_IC_1_SHIFT   2
#define R90_FTDM_IN16_SERIAL_IN_SEL_IC_1_MASK     0x20
#define R90_FTDM_IN16_SERIAL_IN_SEL_IC_1_SHIFT    5
#define R90_FTDM_IN16_REVERSE_IN_BYTE_IC_1_MASK   0x40
#define R90_FTDM_IN16_REVERSE_IN_BYTE_IC_1_SHIFT  6
#define R90_FTDM_IN16_SLOT_ENABLE_IN_IC_1_MASK    0x80
#define R90_FTDM_IN16_SLOT_ENABLE_IN_IC_1_SHIFT   7

/* FTDM_IN17 (IC 1) */
#define R91_FTDM_IN17_BYTE_IN_POS_IC_1            0x0    /* 00b	[1:0] */
#define R91_FTDM_IN17_CHANNEL_IN_POS_IC_1         0x0    /* 000b	[4:2] */
#define R91_FTDM_IN17_SERIAL_IN_SEL_IC_1          0x0    /* 0b	[5] */
#define R91_FTDM_IN17_REVERSE_IN_BYTE_IC_1        0x0    /* 0b	[6] */
#define R91_FTDM_IN17_SLOT_ENABLE_IN_IC_1         0x0    /* 0b	[7] */
#define R91_FTDM_IN17_BYTE_IN_POS_IC_1_MASK       0x3
#define R91_FTDM_IN17_BYTE_IN_POS_IC_1_SHIFT      0
#define R91_FTDM_IN17_CHANNEL_IN_POS_IC_1_MASK    0x1C
#define R91_FTDM_IN17_CHANNEL_IN_POS_IC_1_SHIFT   2
#define R91_FTDM_IN17_SERIAL_IN_SEL_IC_1_MASK     0x20
#define R91_FTDM_IN17_SERIAL_IN_SEL_IC_1_SHIFT    5
#define R91_FTDM_IN17_REVERSE_IN_BYTE_IC_1_MASK   0x40
#define R91_FTDM_IN17_REVERSE_IN_BYTE_IC_1_SHIFT  6
#define R91_FTDM_IN17_SLOT_ENABLE_IN_IC_1_MASK    0x80
#define R91_FTDM_IN17_SLOT_ENABLE_IN_IC_1_SHIFT   7

/* FTDM_IN18 (IC 1) */
#define R92_FTDM_IN18_BYTE_IN_POS_IC_1            0x0    /* 00b	[1:0] */
#define R92_FTDM_IN18_CHANNEL_IN_POS_IC_1         0x0    /* 000b	[4:2] */
#define R92_FTDM_IN18_SERIAL_IN_SEL_IC_1          0x0    /* 0b	[5] */
#define R92_FTDM_IN18_REVERSE_IN_BYTE_IC_1        0x0    /* 0b	[6] */
#define R92_FTDM_IN18_SLOT_ENABLE_IN_IC_1         0x0    /* 0b	[7] */
#define R92_FTDM_IN18_BYTE_IN_POS_IC_1_MASK       0x3
#define R92_FTDM_IN18_BYTE_IN_POS_IC_1_SHIFT      0
#define R92_FTDM_IN18_CHANNEL_IN_POS_IC_1_MASK    0x1C
#define R92_FTDM_IN18_CHANNEL_IN_POS_IC_1_SHIFT   2
#define R92_FTDM_IN18_SERIAL_IN_SEL_IC_1_MASK     0x20
#define R92_FTDM_IN18_SERIAL_IN_SEL_IC_1_SHIFT    5
#define R92_FTDM_IN18_REVERSE_IN_BYTE_IC_1_MASK   0x40
#define R92_FTDM_IN18_REVERSE_IN_BYTE_IC_1_SHIFT  6
#define R92_FTDM_IN18_SLOT_ENABLE_IN_IC_1_MASK    0x80
#define R92_FTDM_IN18_SLOT_ENABLE_IN_IC_1_SHIFT   7

/* FTDM_IN19 (IC 1) */
#define R93_FTDM_IN19_BYTE_IN_POS_IC_1            0x0    /* 00b	[1:0] */
#define R93_FTDM_IN19_CHANNEL_IN_POS_IC_1         0x0    /* 000b	[4:2] */
#define R93_FTDM_IN19_SERIAL_IN_SEL_IC_1          0x0    /* 0b	[5] */
#define R93_FTDM_IN19_REVERSE_IN_BYTE_IC_1        0x0    /* 0b	[6] */
#define R93_FTDM_IN19_SLOT_ENABLE_IN_IC_1         0x0    /* 0b	[7] */
#define R93_FTDM_IN19_BYTE_IN_POS_IC_1_MASK       0x3
#define R93_FTDM_IN19_BYTE_IN_POS_IC_1_SHIFT      0
#define R93_FTDM_IN19_CHANNEL_IN_POS_IC_1_MASK    0x1C
#define R93_FTDM_IN19_CHANNEL_IN_POS_IC_1_SHIFT   2
#define R93_FTDM_IN19_SERIAL_IN_SEL_IC_1_MASK     0x20
#define R93_FTDM_IN19_SERIAL_IN_SEL_IC_1_SHIFT    5
#define R93_FTDM_IN19_REVERSE_IN_BYTE_IC_1_MASK   0x40
#define R93_FTDM_IN19_REVERSE_IN_BYTE_IC_1_SHIFT  6
#define R93_FTDM_IN19_SLOT_ENABLE_IN_IC_1_MASK    0x80
#define R93_FTDM_IN19_SLOT_ENABLE_IN_IC_1_SHIFT   7

/* FTDM_IN20 (IC 1) */
#define R94_FTDM_IN20_BYTE_IN_POS_IC_1            0x0    /* 00b	[1:0] */
#define R94_FTDM_IN20_CHANNEL_IN_POS_IC_1         0x0    /* 000b	[4:2] */
#define R94_FTDM_IN20_SERIAL_IN_SEL_IC_1          0x0    /* 0b	[5] */
#define R94_FTDM_IN20_REVERSE_IN_BYTE_IC_1        0x0    /* 0b	[6] */
#define R94_FTDM_IN20_SLOT_ENABLE_IN_IC_1         0x0    /* 0b	[7] */
#define R94_FTDM_IN20_BYTE_IN_POS_IC_1_MASK       0x3
#define R94_FTDM_IN20_BYTE_IN_POS_IC_1_SHIFT      0
#define R94_FTDM_IN20_CHANNEL_IN_POS_IC_1_MASK    0x1C
#define R94_FTDM_IN20_CHANNEL_IN_POS_IC_1_SHIFT   2
#define R94_FTDM_IN20_SERIAL_IN_SEL_IC_1_MASK     0x20
#define R94_FTDM_IN20_SERIAL_IN_SEL_IC_1_SHIFT    5
#define R94_FTDM_IN20_REVERSE_IN_BYTE_IC_1_MASK   0x40
#define R94_FTDM_IN20_REVERSE_IN_BYTE_IC_1_SHIFT  6
#define R94_FTDM_IN20_SLOT_ENABLE_IN_IC_1_MASK    0x80
#define R94_FTDM_IN20_SLOT_ENABLE_IN_IC_1_SHIFT   7

/* FTDM_IN21 (IC 1) */
#define R95_FTDM_IN21_BYTE_IN_POS_IC_1            0x0    /* 00b	[1:0] */
#define R95_FTDM_IN21_CHANNEL_IN_POS_IC_1         0x0    /* 000b	[4:2] */
#define R95_FTDM_IN21_SERIAL_IN_SEL_IC_1          0x0    /* 0b	[5] */
#define R95_FTDM_IN21_REVERSE_IN_BYTE_IC_1        0x0    /* 0b	[6] */
#define R95_FTDM_IN21_SLOT_ENABLE_IN_IC_1         0x0    /* 0b	[7] */
#define R95_FTDM_IN21_BYTE_IN_POS_IC_1_MASK       0x3
#define R95_FTDM_IN21_BYTE_IN_POS_IC_1_SHIFT      0
#define R95_FTDM_IN21_CHANNEL_IN_POS_IC_1_MASK    0x1C
#define R95_FTDM_IN21_CHANNEL_IN_POS_IC_1_SHIFT   2
#define R95_FTDM_IN21_SERIAL_IN_SEL_IC_1_MASK     0x20
#define R95_FTDM_IN21_SERIAL_IN_SEL_IC_1_SHIFT    5
#define R95_FTDM_IN21_REVERSE_IN_BYTE_IC_1_MASK   0x40
#define R95_FTDM_IN21_REVERSE_IN_BYTE_IC_1_SHIFT  6
#define R95_FTDM_IN21_SLOT_ENABLE_IN_IC_1_MASK    0x80
#define R95_FTDM_IN21_SLOT_ENABLE_IN_IC_1_SHIFT   7

/* FTDM_IN22 (IC 1) */
#define R96_FTDM_IN22_BYTE_IN_POS_IC_1            0x0    /* 00b	[1:0] */
#define R96_FTDM_IN22_CHANNEL_IN_POS_IC_1         0x0    /* 000b	[4:2] */
#define R96_FTDM_IN22_SERIAL_IN_SEL_IC_1          0x0    /* 0b	[5] */
#define R96_FTDM_IN22_REVERSE_IN_BYTE_IC_1        0x0    /* 0b	[6] */
#define R96_FTDM_IN22_SLOT_ENABLE_IN_IC_1         0x0    /* 0b	[7] */
#define R96_FTDM_IN22_BYTE_IN_POS_IC_1_MASK       0x3
#define R96_FTDM_IN22_BYTE_IN_POS_IC_1_SHIFT      0
#define R96_FTDM_IN22_CHANNEL_IN_POS_IC_1_MASK    0x1C
#define R96_FTDM_IN22_CHANNEL_IN_POS_IC_1_SHIFT   2
#define R96_FTDM_IN22_SERIAL_IN_SEL_IC_1_MASK     0x20
#define R96_FTDM_IN22_SERIAL_IN_SEL_IC_1_SHIFT    5
#define R96_FTDM_IN22_REVERSE_IN_BYTE_IC_1_MASK   0x40
#define R96_FTDM_IN22_REVERSE_IN_BYTE_IC_1_SHIFT  6
#define R96_FTDM_IN22_SLOT_ENABLE_IN_IC_1_MASK    0x80
#define R96_FTDM_IN22_SLOT_ENABLE_IN_IC_1_SHIFT   7

/* FTDM_IN23 (IC 1) */
#define R97_FTDM_IN23_BYTE_IN_POS_IC_1            0x0    /* 00b	[1:0] */
#define R97_FTDM_IN23_CHANNEL_IN_POS_IC_1         0x0    /* 000b	[4:2] */
#define R97_FTDM_IN23_SERIAL_IN_SEL_IC_1          0x0    /* 0b	[5] */
#define R97_FTDM_IN23_REVERSE_IN_BYTE_IC_1        0x0    /* 0b	[6] */
#define R97_FTDM_IN23_SLOT_ENABLE_IN_IC_1         0x0    /* 0b	[7] */
#define R97_FTDM_IN23_BYTE_IN_POS_IC_1_MASK       0x3
#define R97_FTDM_IN23_BYTE_IN_POS_IC_1_SHIFT      0
#define R97_FTDM_IN23_CHANNEL_IN_POS_IC_1_MASK    0x1C
#define R97_FTDM_IN23_CHANNEL_IN_POS_IC_1_SHIFT   2
#define R97_FTDM_IN23_SERIAL_IN_SEL_IC_1_MASK     0x20
#define R97_FTDM_IN23_SERIAL_IN_SEL_IC_1_SHIFT    5
#define R97_FTDM_IN23_REVERSE_IN_BYTE_IC_1_MASK   0x40
#define R97_FTDM_IN23_REVERSE_IN_BYTE_IC_1_SHIFT  6
#define R97_FTDM_IN23_SLOT_ENABLE_IN_IC_1_MASK    0x80
#define R97_FTDM_IN23_SLOT_ENABLE_IN_IC_1_SHIFT   7

/* FTDM_IN24 (IC 1) */
#define R98_FTDM_IN24_BYTE_IN_POS_IC_1            0x0    /* 00b	[1:0] */
#define R98_FTDM_IN24_CHANNEL_IN_POS_IC_1         0x0    /* 000b	[4:2] */
#define R98_FTDM_IN24_SERIAL_IN_SEL_IC_1          0x0    /* 0b	[5] */
#define R98_FTDM_IN24_REVERSE_IN_BYTE_IC_1        0x0    /* 0b	[6] */
#define R98_FTDM_IN24_SLOT_ENABLE_IN_IC_1         0x0    /* 0b	[7] */
#define R98_FTDM_IN24_BYTE_IN_POS_IC_1_MASK       0x3
#define R98_FTDM_IN24_BYTE_IN_POS_IC_1_SHIFT      0
#define R98_FTDM_IN24_CHANNEL_IN_POS_IC_1_MASK    0x1C
#define R98_FTDM_IN24_CHANNEL_IN_POS_IC_1_SHIFT   2
#define R98_FTDM_IN24_SERIAL_IN_SEL_IC_1_MASK     0x20
#define R98_FTDM_IN24_SERIAL_IN_SEL_IC_1_SHIFT    5
#define R98_FTDM_IN24_REVERSE_IN_BYTE_IC_1_MASK   0x40
#define R98_FTDM_IN24_REVERSE_IN_BYTE_IC_1_SHIFT  6
#define R98_FTDM_IN24_SLOT_ENABLE_IN_IC_1_MASK    0x80
#define R98_FTDM_IN24_SLOT_ENABLE_IN_IC_1_SHIFT   7

/* FTDM_IN25 (IC 1) */
#define R99_FTDM_IN25_BYTE_IN_POS_IC_1            0x0    /* 00b	[1:0] */
#define R99_FTDM_IN25_CHANNEL_IN_POS_IC_1         0x0    /* 000b	[4:2] */
#define R99_FTDM_IN25_SERIAL_IN_SEL_IC_1          0x0    /* 0b	[5] */
#define R99_FTDM_IN25_REVERSE_IN_BYTE_IC_1        0x0    /* 0b	[6] */
#define R99_FTDM_IN25_SLOT_ENABLE_IN_IC_1         0x0    /* 0b	[7] */
#define R99_FTDM_IN25_BYTE_IN_POS_IC_1_MASK       0x3
#define R99_FTDM_IN25_BYTE_IN_POS_IC_1_SHIFT      0
#define R99_FTDM_IN25_CHANNEL_IN_POS_IC_1_MASK    0x1C
#define R99_FTDM_IN25_CHANNEL_IN_POS_IC_1_SHIFT   2
#define R99_FTDM_IN25_SERIAL_IN_SEL_IC_1_MASK     0x20
#define R99_FTDM_IN25_SERIAL_IN_SEL_IC_1_SHIFT    5
#define R99_FTDM_IN25_REVERSE_IN_BYTE_IC_1_MASK   0x40
#define R99_FTDM_IN25_REVERSE_IN_BYTE_IC_1_SHIFT  6
#define R99_FTDM_IN25_SLOT_ENABLE_IN_IC_1_MASK    0x80
#define R99_FTDM_IN25_SLOT_ENABLE_IN_IC_1_SHIFT   7

/* FTDM_IN26 (IC 1) */
#define R100_FTDM_IN26_BYTE_IN_POS_IC_1           0x0    /* 00b	[1:0] */
#define R100_FTDM_IN26_CHANNEL_IN_POS_IC_1        0x0    /* 000b	[4:2] */
#define R100_FTDM_IN26_SERIAL_IN_SEL_IC_1         0x0    /* 0b	[5] */
#define R100_FTDM_IN26_REVERSE_IN_BYTE_IC_1       0x0    /* 0b	[6] */
#define R100_FTDM_IN26_SLOT_ENABLE_IN_IC_1        0x0    /* 0b	[7] */
#define R100_FTDM_IN26_BYTE_IN_POS_IC_1_MASK      0x3
#define R100_FTDM_IN26_BYTE_IN_POS_IC_1_SHIFT     0
#define R100_FTDM_IN26_CHANNEL_IN_POS_IC_1_MASK   0x1C
#define R100_FTDM_IN26_CHANNEL_IN_POS_IC_1_SHIFT  2
#define R100_FTDM_IN26_SERIAL_IN_SEL_IC_1_MASK    0x20
#define R100_FTDM_IN26_SERIAL_IN_SEL_IC_1_SHIFT   5
#define R100_FTDM_IN26_REVERSE_IN_BYTE_IC_1_MASK  0x40
#define R100_FTDM_IN26_REVERSE_IN_BYTE_IC_1_SHIFT 6
#define R100_FTDM_IN26_SLOT_ENABLE_IN_IC_1_MASK   0x80
#define R100_FTDM_IN26_SLOT_ENABLE_IN_IC_1_SHIFT  7

/* FTDM_IN27 (IC 1) */
#define R101_FTDM_IN27_BYTE_IN_POS_IC_1           0x0    /* 00b	[1:0] */
#define R101_FTDM_IN27_CHANNEL_IN_POS_IC_1        0x0    /* 000b	[4:2] */
#define R101_FTDM_IN27_SERIAL_IN_SEL_IC_1         0x0    /* 0b	[5] */
#define R101_FTDM_IN27_REVERSE_IN_BYTE_IC_1       0x0    /* 0b	[6] */
#define R101_FTDM_IN27_SLOT_ENABLE_IN_IC_1        0x0    /* 0b	[7] */
#define R101_FTDM_IN27_BYTE_IN_POS_IC_1_MASK      0x3
#define R101_FTDM_IN27_BYTE_IN_POS_IC_1_SHIFT     0
#define R101_FTDM_IN27_CHANNEL_IN_POS_IC_1_MASK   0x1C
#define R101_FTDM_IN27_CHANNEL_IN_POS_IC_1_SHIFT  2
#define R101_FTDM_IN27_SERIAL_IN_SEL_IC_1_MASK    0x20
#define R101_FTDM_IN27_SERIAL_IN_SEL_IC_1_SHIFT   5
#define R101_FTDM_IN27_REVERSE_IN_BYTE_IC_1_MASK  0x40
#define R101_FTDM_IN27_REVERSE_IN_BYTE_IC_1_SHIFT 6
#define R101_FTDM_IN27_SLOT_ENABLE_IN_IC_1_MASK   0x80
#define R101_FTDM_IN27_SLOT_ENABLE_IN_IC_1_SHIFT  7

/* FTDM_IN28 (IC 1) */
#define R102_FTDM_IN28_BYTE_IN_POS_IC_1           0x0    /* 00b	[1:0] */
#define R102_FTDM_IN28_CHANNEL_IN_POS_IC_1        0x0    /* 000b	[4:2] */
#define R102_FTDM_IN28_SERIAL_IN_SEL_IC_1         0x0    /* 0b	[5] */
#define R102_FTDM_IN28_REVERSE_IN_BYTE_IC_1       0x0    /* 0b	[6] */
#define R102_FTDM_IN28_SLOT_ENABLE_IN_IC_1        0x0    /* 0b	[7] */
#define R102_FTDM_IN28_BYTE_IN_POS_IC_1_MASK      0x3
#define R102_FTDM_IN28_BYTE_IN_POS_IC_1_SHIFT     0
#define R102_FTDM_IN28_CHANNEL_IN_POS_IC_1_MASK   0x1C
#define R102_FTDM_IN28_CHANNEL_IN_POS_IC_1_SHIFT  2
#define R102_FTDM_IN28_SERIAL_IN_SEL_IC_1_MASK    0x20
#define R102_FTDM_IN28_SERIAL_IN_SEL_IC_1_SHIFT   5
#define R102_FTDM_IN28_REVERSE_IN_BYTE_IC_1_MASK  0x40
#define R102_FTDM_IN28_REVERSE_IN_BYTE_IC_1_SHIFT 6
#define R102_FTDM_IN28_SLOT_ENABLE_IN_IC_1_MASK   0x80
#define R102_FTDM_IN28_SLOT_ENABLE_IN_IC_1_SHIFT  7

/* FTDM_IN29 (IC 1) */
#define R103_FTDM_IN29_BYTE_IN_POS_IC_1           0x0    /* 00b	[1:0] */
#define R103_FTDM_IN29_CHANNEL_IN_POS_IC_1        0x0    /* 000b	[4:2] */
#define R103_FTDM_IN29_SERIAL_IN_SEL_IC_1         0x0    /* 0b	[5] */
#define R103_FTDM_IN29_REVERSE_IN_BYTE_IC_1       0x0    /* 0b	[6] */
#define R103_FTDM_IN29_SLOT_ENABLE_IN_IC_1        0x0    /* 0b	[7] */
#define R103_FTDM_IN29_BYTE_IN_POS_IC_1_MASK      0x3
#define R103_FTDM_IN29_BYTE_IN_POS_IC_1_SHIFT     0
#define R103_FTDM_IN29_CHANNEL_IN_POS_IC_1_MASK   0x1C
#define R103_FTDM_IN29_CHANNEL_IN_POS_IC_1_SHIFT  2
#define R103_FTDM_IN29_SERIAL_IN_SEL_IC_1_MASK    0x20
#define R103_FTDM_IN29_SERIAL_IN_SEL_IC_1_SHIFT   5
#define R103_FTDM_IN29_REVERSE_IN_BYTE_IC_1_MASK  0x40
#define R103_FTDM_IN29_REVERSE_IN_BYTE_IC_1_SHIFT 6
#define R103_FTDM_IN29_SLOT_ENABLE_IN_IC_1_MASK   0x80
#define R103_FTDM_IN29_SLOT_ENABLE_IN_IC_1_SHIFT  7

/* FTDM_IN30 (IC 1) */
#define R104_FTDM_IN30_BYTE_IN_POS_IC_1           0x0    /* 00b	[1:0] */
#define R104_FTDM_IN30_CHANNEL_IN_POS_IC_1        0x0    /* 000b	[4:2] */
#define R104_FTDM_IN30_SERIAL_IN_SEL_IC_1         0x0    /* 0b	[5] */
#define R104_FTDM_IN30_REVERSE_IN_BYTE_IC_1       0x0    /* 0b	[6] */
#define R104_FTDM_IN30_SLOT_ENABLE_IN_IC_1        0x0    /* 0b	[7] */
#define R104_FTDM_IN30_BYTE_IN_POS_IC_1_MASK      0x3
#define R104_FTDM_IN30_BYTE_IN_POS_IC_1_SHIFT     0
#define R104_FTDM_IN30_CHANNEL_IN_POS_IC_1_MASK   0x1C
#define R104_FTDM_IN30_CHANNEL_IN_POS_IC_1_SHIFT  2
#define R104_FTDM_IN30_SERIAL_IN_SEL_IC_1_MASK    0x20
#define R104_FTDM_IN30_SERIAL_IN_SEL_IC_1_SHIFT   5
#define R104_FTDM_IN30_REVERSE_IN_BYTE_IC_1_MASK  0x40
#define R104_FTDM_IN30_REVERSE_IN_BYTE_IC_1_SHIFT 6
#define R104_FTDM_IN30_SLOT_ENABLE_IN_IC_1_MASK   0x80
#define R104_FTDM_IN30_SLOT_ENABLE_IN_IC_1_SHIFT  7

/* FTDM_IN31 (IC 1) */
#define R105_FTDM_IN31_BYTE_IN_POS_IC_1           0x0    /* 00b	[1:0] */
#define R105_FTDM_IN31_CHANNEL_IN_POS_IC_1        0x0    /* 000b	[4:2] */
#define R105_FTDM_IN31_SERIAL_IN_SEL_IC_1         0x0    /* 0b	[5] */
#define R105_FTDM_IN31_REVERSE_IN_BYTE_IC_1       0x0    /* 0b	[6] */
#define R105_FTDM_IN31_SLOT_ENABLE_IN_IC_1        0x0    /* 0b	[7] */
#define R105_FTDM_IN31_BYTE_IN_POS_IC_1_MASK      0x3
#define R105_FTDM_IN31_BYTE_IN_POS_IC_1_SHIFT     0
#define R105_FTDM_IN31_CHANNEL_IN_POS_IC_1_MASK   0x1C
#define R105_FTDM_IN31_CHANNEL_IN_POS_IC_1_SHIFT  2
#define R105_FTDM_IN31_SERIAL_IN_SEL_IC_1_MASK    0x20
#define R105_FTDM_IN31_SERIAL_IN_SEL_IC_1_SHIFT   5
#define R105_FTDM_IN31_REVERSE_IN_BYTE_IC_1_MASK  0x40
#define R105_FTDM_IN31_REVERSE_IN_BYTE_IC_1_SHIFT 6
#define R105_FTDM_IN31_SLOT_ENABLE_IN_IC_1_MASK   0x80
#define R105_FTDM_IN31_SLOT_ENABLE_IN_IC_1_SHIFT  7

/* FTDM_IN32 (IC 1) */
#define R106_FTDM_IN32_BYTE_IN_POS_IC_1           0x0    /* 00b	[1:0] */
#define R106_FTDM_IN32_CHANNEL_IN_POS_IC_1        0x0    /* 000b	[4:2] */
#define R106_FTDM_IN32_SERIAL_IN_SEL_IC_1         0x0    /* 0b	[5] */
#define R106_FTDM_IN32_REVERSE_IN_BYTE_IC_1       0x0    /* 0b	[6] */
#define R106_FTDM_IN32_SLOT_ENABLE_IN_IC_1        0x0    /* 0b	[7] */
#define R106_FTDM_IN32_BYTE_IN_POS_IC_1_MASK      0x3
#define R106_FTDM_IN32_BYTE_IN_POS_IC_1_SHIFT     0
#define R106_FTDM_IN32_CHANNEL_IN_POS_IC_1_MASK   0x1C
#define R106_FTDM_IN32_CHANNEL_IN_POS_IC_1_SHIFT  2
#define R106_FTDM_IN32_SERIAL_IN_SEL_IC_1_MASK    0x20
#define R106_FTDM_IN32_SERIAL_IN_SEL_IC_1_SHIFT   5
#define R106_FTDM_IN32_REVERSE_IN_BYTE_IC_1_MASK  0x40
#define R106_FTDM_IN32_REVERSE_IN_BYTE_IC_1_SHIFT 6
#define R106_FTDM_IN32_SLOT_ENABLE_IN_IC_1_MASK   0x80
#define R106_FTDM_IN32_SLOT_ENABLE_IN_IC_1_SHIFT  7

/* FTDM_IN33 (IC 1) */
#define R107_FTDM_IN33_BYTE_IN_POS_IC_1           0x0    /* 00b	[1:0] */
#define R107_FTDM_IN33_CHANNEL_IN_POS_IC_1        0x0    /* 000b	[4:2] */
#define R107_FTDM_IN33_SERIAL_IN_SEL_IC_1         0x0    /* 0b	[5] */
#define R107_FTDM_IN33_REVERSE_IN_BYTE_IC_1       0x0    /* 0b	[6] */
#define R107_FTDM_IN33_SLOT_ENABLE_IN_IC_1        0x0    /* 0b	[7] */
#define R107_FTDM_IN33_BYTE_IN_POS_IC_1_MASK      0x3
#define R107_FTDM_IN33_BYTE_IN_POS_IC_1_SHIFT     0
#define R107_FTDM_IN33_CHANNEL_IN_POS_IC_1_MASK   0x1C
#define R107_FTDM_IN33_CHANNEL_IN_POS_IC_1_SHIFT  2
#define R107_FTDM_IN33_SERIAL_IN_SEL_IC_1_MASK    0x20
#define R107_FTDM_IN33_SERIAL_IN_SEL_IC_1_SHIFT   5
#define R107_FTDM_IN33_REVERSE_IN_BYTE_IC_1_MASK  0x40
#define R107_FTDM_IN33_REVERSE_IN_BYTE_IC_1_SHIFT 6
#define R107_FTDM_IN33_SLOT_ENABLE_IN_IC_1_MASK   0x80
#define R107_FTDM_IN33_SLOT_ENABLE_IN_IC_1_SHIFT  7

/* FTDM_IN34 (IC 1) */
#define R108_FTDM_IN34_BYTE_IN_POS_IC_1           0x0    /* 00b	[1:0] */
#define R108_FTDM_IN34_CHANNEL_IN_POS_IC_1        0x0    /* 000b	[4:2] */
#define R108_FTDM_IN34_SERIAL_IN_SEL_IC_1         0x0    /* 0b	[5] */
#define R108_FTDM_IN34_REVERSE_IN_BYTE_IC_1       0x0    /* 0b	[6] */
#define R108_FTDM_IN34_SLOT_ENABLE_IN_IC_1        0x0    /* 0b	[7] */
#define R108_FTDM_IN34_BYTE_IN_POS_IC_1_MASK      0x3
#define R108_FTDM_IN34_BYTE_IN_POS_IC_1_SHIFT     0
#define R108_FTDM_IN34_CHANNEL_IN_POS_IC_1_MASK   0x1C
#define R108_FTDM_IN34_CHANNEL_IN_POS_IC_1_SHIFT  2
#define R108_FTDM_IN34_SERIAL_IN_SEL_IC_1_MASK    0x20
#define R108_FTDM_IN34_SERIAL_IN_SEL_IC_1_SHIFT   5
#define R108_FTDM_IN34_REVERSE_IN_BYTE_IC_1_MASK  0x40
#define R108_FTDM_IN34_REVERSE_IN_BYTE_IC_1_SHIFT 6
#define R108_FTDM_IN34_SLOT_ENABLE_IN_IC_1_MASK   0x80
#define R108_FTDM_IN34_SLOT_ENABLE_IN_IC_1_SHIFT  7

/* FTDM_IN35 (IC 1) */
#define R109_FTDM_IN35_BYTE_IN_POS_IC_1           0x0    /* 00b	[1:0] */
#define R109_FTDM_IN35_CHANNEL_IN_POS_IC_1        0x0    /* 000b	[4:2] */
#define R109_FTDM_IN35_SERIAL_IN_SEL_IC_1         0x0    /* 0b	[5] */
#define R109_FTDM_IN35_REVERSE_IN_BYTE_IC_1       0x0    /* 0b	[6] */
#define R109_FTDM_IN35_SLOT_ENABLE_IN_IC_1        0x0    /* 0b	[7] */
#define R109_FTDM_IN35_BYTE_IN_POS_IC_1_MASK      0x3
#define R109_FTDM_IN35_BYTE_IN_POS_IC_1_SHIFT     0
#define R109_FTDM_IN35_CHANNEL_IN_POS_IC_1_MASK   0x1C
#define R109_FTDM_IN35_CHANNEL_IN_POS_IC_1_SHIFT  2
#define R109_FTDM_IN35_SERIAL_IN_SEL_IC_1_MASK    0x20
#define R109_FTDM_IN35_SERIAL_IN_SEL_IC_1_SHIFT   5
#define R109_FTDM_IN35_REVERSE_IN_BYTE_IC_1_MASK  0x40
#define R109_FTDM_IN35_REVERSE_IN_BYTE_IC_1_SHIFT 6
#define R109_FTDM_IN35_SLOT_ENABLE_IN_IC_1_MASK   0x80
#define R109_FTDM_IN35_SLOT_ENABLE_IN_IC_1_SHIFT  7

/* FTDM_IN36 (IC 1) */
#define R110_FTDM_IN36_BYTE_IN_POS_IC_1           0x0    /* 00b	[1:0] */
#define R110_FTDM_IN36_CHANNEL_IN_POS_IC_1        0x0    /* 000b	[4:2] */
#define R110_FTDM_IN36_SERIAL_IN_SEL_IC_1         0x0    /* 0b	[5] */
#define R110_FTDM_IN36_REVERSE_IN_BYTE_IC_1       0x0    /* 0b	[6] */
#define R110_FTDM_IN36_SLOT_ENABLE_IN_IC_1        0x0    /* 0b	[7] */
#define R110_FTDM_IN36_BYTE_IN_POS_IC_1_MASK      0x3
#define R110_FTDM_IN36_BYTE_IN_POS_IC_1_SHIFT     0
#define R110_FTDM_IN36_CHANNEL_IN_POS_IC_1_MASK   0x1C
#define R110_FTDM_IN36_CHANNEL_IN_POS_IC_1_SHIFT  2
#define R110_FTDM_IN36_SERIAL_IN_SEL_IC_1_MASK    0x20
#define R110_FTDM_IN36_SERIAL_IN_SEL_IC_1_SHIFT   5
#define R110_FTDM_IN36_REVERSE_IN_BYTE_IC_1_MASK  0x40
#define R110_FTDM_IN36_REVERSE_IN_BYTE_IC_1_SHIFT 6
#define R110_FTDM_IN36_SLOT_ENABLE_IN_IC_1_MASK   0x80
#define R110_FTDM_IN36_SLOT_ENABLE_IN_IC_1_SHIFT  7

/* FTDM_IN37 (IC 1) */
#define R111_FTDM_IN37_BYTE_IN_POS_IC_1           0x0    /* 00b	[1:0] */
#define R111_FTDM_IN37_CHANNEL_IN_POS_IC_1        0x0    /* 000b	[4:2] */
#define R111_FTDM_IN37_SERIAL_IN_SEL_IC_1         0x0    /* 0b	[5] */
#define R111_FTDM_IN37_REVERSE_IN_BYTE_IC_1       0x0    /* 0b	[6] */
#define R111_FTDM_IN37_SLOT_ENABLE_IN_IC_1        0x0    /* 0b	[7] */
#define R111_FTDM_IN37_BYTE_IN_POS_IC_1_MASK      0x3
#define R111_FTDM_IN37_BYTE_IN_POS_IC_1_SHIFT     0
#define R111_FTDM_IN37_CHANNEL_IN_POS_IC_1_MASK   0x1C
#define R111_FTDM_IN37_CHANNEL_IN_POS_IC_1_SHIFT  2
#define R111_FTDM_IN37_SERIAL_IN_SEL_IC_1_MASK    0x20
#define R111_FTDM_IN37_SERIAL_IN_SEL_IC_1_SHIFT   5
#define R111_FTDM_IN37_REVERSE_IN_BYTE_IC_1_MASK  0x40
#define R111_FTDM_IN37_REVERSE_IN_BYTE_IC_1_SHIFT 6
#define R111_FTDM_IN37_SLOT_ENABLE_IN_IC_1_MASK   0x80
#define R111_FTDM_IN37_SLOT_ENABLE_IN_IC_1_SHIFT  7

/* FTDM_IN38 (IC 1) */
#define R112_FTDM_IN38_BYTE_IN_POS_IC_1           0x0    /* 00b	[1:0] */
#define R112_FTDM_IN38_CHANNEL_IN_POS_IC_1        0x0    /* 000b	[4:2] */
#define R112_FTDM_IN38_SERIAL_IN_SEL_IC_1         0x0    /* 0b	[5] */
#define R112_FTDM_IN38_REVERSE_IN_BYTE_IC_1       0x0    /* 0b	[6] */
#define R112_FTDM_IN38_SLOT_ENABLE_IN_IC_1        0x0    /* 0b	[7] */
#define R112_FTDM_IN38_BYTE_IN_POS_IC_1_MASK      0x3
#define R112_FTDM_IN38_BYTE_IN_POS_IC_1_SHIFT     0
#define R112_FTDM_IN38_CHANNEL_IN_POS_IC_1_MASK   0x1C
#define R112_FTDM_IN38_CHANNEL_IN_POS_IC_1_SHIFT  2
#define R112_FTDM_IN38_SERIAL_IN_SEL_IC_1_MASK    0x20
#define R112_FTDM_IN38_SERIAL_IN_SEL_IC_1_SHIFT   5
#define R112_FTDM_IN38_REVERSE_IN_BYTE_IC_1_MASK  0x40
#define R112_FTDM_IN38_REVERSE_IN_BYTE_IC_1_SHIFT 6
#define R112_FTDM_IN38_SLOT_ENABLE_IN_IC_1_MASK   0x80
#define R112_FTDM_IN38_SLOT_ENABLE_IN_IC_1_SHIFT  7

/* FTDM_IN39 (IC 1) */
#define R113_FTDM_IN39_BYTE_IN_POS_IC_1           0x0    /* 00b	[1:0] */
#define R113_FTDM_IN39_CHANNEL_IN_POS_IC_1        0x0    /* 000b	[4:2] */
#define R113_FTDM_IN39_SERIAL_IN_SEL_IC_1         0x0    /* 0b	[5] */
#define R113_FTDM_IN39_REVERSE_IN_BYTE_IC_1       0x0    /* 0b	[6] */
#define R113_FTDM_IN39_SLOT_ENABLE_IN_IC_1        0x0    /* 0b	[7] */
#define R113_FTDM_IN39_BYTE_IN_POS_IC_1_MASK      0x3
#define R113_FTDM_IN39_BYTE_IN_POS_IC_1_SHIFT     0
#define R113_FTDM_IN39_CHANNEL_IN_POS_IC_1_MASK   0x1C
#define R113_FTDM_IN39_CHANNEL_IN_POS_IC_1_SHIFT  2
#define R113_FTDM_IN39_SERIAL_IN_SEL_IC_1_MASK    0x20
#define R113_FTDM_IN39_SERIAL_IN_SEL_IC_1_SHIFT   5
#define R113_FTDM_IN39_REVERSE_IN_BYTE_IC_1_MASK  0x40
#define R113_FTDM_IN39_REVERSE_IN_BYTE_IC_1_SHIFT 6
#define R113_FTDM_IN39_SLOT_ENABLE_IN_IC_1_MASK   0x80
#define R113_FTDM_IN39_SLOT_ENABLE_IN_IC_1_SHIFT  7

/* FTDM_IN40 (IC 1) */
#define R114_FTDM_IN40_BYTE_IN_POS_IC_1           0x0    /* 00b	[1:0] */
#define R114_FTDM_IN40_CHANNEL_IN_POS_IC_1        0x0    /* 000b	[4:2] */
#define R114_FTDM_IN40_SERIAL_IN_SEL_IC_1         0x0    /* 0b	[5] */
#define R114_FTDM_IN40_REVERSE_IN_BYTE_IC_1       0x0    /* 0b	[6] */
#define R114_FTDM_IN40_SLOT_ENABLE_IN_IC_1        0x0    /* 0b	[7] */
#define R114_FTDM_IN40_BYTE_IN_POS_IC_1_MASK      0x3
#define R114_FTDM_IN40_BYTE_IN_POS_IC_1_SHIFT     0
#define R114_FTDM_IN40_CHANNEL_IN_POS_IC_1_MASK   0x1C
#define R114_FTDM_IN40_CHANNEL_IN_POS_IC_1_SHIFT  2
#define R114_FTDM_IN40_SERIAL_IN_SEL_IC_1_MASK    0x20
#define R114_FTDM_IN40_SERIAL_IN_SEL_IC_1_SHIFT   5
#define R114_FTDM_IN40_REVERSE_IN_BYTE_IC_1_MASK  0x40
#define R114_FTDM_IN40_REVERSE_IN_BYTE_IC_1_SHIFT 6
#define R114_FTDM_IN40_SLOT_ENABLE_IN_IC_1_MASK   0x80
#define R114_FTDM_IN40_SLOT_ENABLE_IN_IC_1_SHIFT  7

/* FTDM_IN41 (IC 1) */
#define R115_FTDM_IN41_BYTE_IN_POS_IC_1           0x0    /* 00b	[1:0] */
#define R115_FTDM_IN41_CHANNEL_IN_POS_IC_1        0x0    /* 000b	[4:2] */
#define R115_FTDM_IN41_SERIAL_IN_SEL_IC_1         0x0    /* 0b	[5] */
#define R115_FTDM_IN41_REVERSE_IN_BYTE_IC_1       0x0    /* 0b	[6] */
#define R115_FTDM_IN41_SLOT_ENABLE_IN_IC_1        0x0    /* 0b	[7] */
#define R115_FTDM_IN41_BYTE_IN_POS_IC_1_MASK      0x3
#define R115_FTDM_IN41_BYTE_IN_POS_IC_1_SHIFT     0
#define R115_FTDM_IN41_CHANNEL_IN_POS_IC_1_MASK   0x1C
#define R115_FTDM_IN41_CHANNEL_IN_POS_IC_1_SHIFT  2
#define R115_FTDM_IN41_SERIAL_IN_SEL_IC_1_MASK    0x20
#define R115_FTDM_IN41_SERIAL_IN_SEL_IC_1_SHIFT   5
#define R115_FTDM_IN41_REVERSE_IN_BYTE_IC_1_MASK  0x40
#define R115_FTDM_IN41_REVERSE_IN_BYTE_IC_1_SHIFT 6
#define R115_FTDM_IN41_SLOT_ENABLE_IN_IC_1_MASK   0x80
#define R115_FTDM_IN41_SLOT_ENABLE_IN_IC_1_SHIFT  7

/* FTDM_IN42 (IC 1) */
#define R116_FTDM_IN42_BYTE_IN_POS_IC_1           0x0    /* 00b	[1:0] */
#define R116_FTDM_IN42_CHANNEL_IN_POS_IC_1        0x0    /* 000b	[4:2] */
#define R116_FTDM_IN42_SERIAL_IN_SEL_IC_1         0x0    /* 0b	[5] */
#define R116_FTDM_IN42_REVERSE_IN_BYTE_IC_1       0x0    /* 0b	[6] */
#define R116_FTDM_IN42_SLOT_ENABLE_IN_IC_1        0x0    /* 0b	[7] */
#define R116_FTDM_IN42_BYTE_IN_POS_IC_1_MASK      0x3
#define R116_FTDM_IN42_BYTE_IN_POS_IC_1_SHIFT     0
#define R116_FTDM_IN42_CHANNEL_IN_POS_IC_1_MASK   0x1C
#define R116_FTDM_IN42_CHANNEL_IN_POS_IC_1_SHIFT  2
#define R116_FTDM_IN42_SERIAL_IN_SEL_IC_1_MASK    0x20
#define R116_FTDM_IN42_SERIAL_IN_SEL_IC_1_SHIFT   5
#define R116_FTDM_IN42_REVERSE_IN_BYTE_IC_1_MASK  0x40
#define R116_FTDM_IN42_REVERSE_IN_BYTE_IC_1_SHIFT 6
#define R116_FTDM_IN42_SLOT_ENABLE_IN_IC_1_MASK   0x80
#define R116_FTDM_IN42_SLOT_ENABLE_IN_IC_1_SHIFT  7

/* FTDM_IN43 (IC 1) */
#define R117_FTDM_IN43_BYTE_IN_POS_IC_1           0x0    /* 00b	[1:0] */
#define R117_FTDM_IN43_CHANNEL_IN_POS_IC_1        0x0    /* 000b	[4:2] */
#define R117_FTDM_IN43_SERIAL_IN_SEL_IC_1         0x0    /* 0b	[5] */
#define R117_FTDM_IN43_REVERSE_IN_BYTE_IC_1       0x0    /* 0b	[6] */
#define R117_FTDM_IN43_SLOT_ENABLE_IN_IC_1        0x0    /* 0b	[7] */
#define R117_FTDM_IN43_BYTE_IN_POS_IC_1_MASK      0x3
#define R117_FTDM_IN43_BYTE_IN_POS_IC_1_SHIFT     0
#define R117_FTDM_IN43_CHANNEL_IN_POS_IC_1_MASK   0x1C
#define R117_FTDM_IN43_CHANNEL_IN_POS_IC_1_SHIFT  2
#define R117_FTDM_IN43_SERIAL_IN_SEL_IC_1_MASK    0x20
#define R117_FTDM_IN43_SERIAL_IN_SEL_IC_1_SHIFT   5
#define R117_FTDM_IN43_REVERSE_IN_BYTE_IC_1_MASK  0x40
#define R117_FTDM_IN43_REVERSE_IN_BYTE_IC_1_SHIFT 6
#define R117_FTDM_IN43_SLOT_ENABLE_IN_IC_1_MASK   0x80
#define R117_FTDM_IN43_SLOT_ENABLE_IN_IC_1_SHIFT  7

/* FTDM_IN44 (IC 1) */
#define R118_FTDM_IN44_BYTE_IN_POS_IC_1           0x0    /* 00b	[1:0] */
#define R118_FTDM_IN44_CHANNEL_IN_POS_IC_1        0x0    /* 000b	[4:2] */
#define R118_FTDM_IN44_SERIAL_IN_SEL_IC_1         0x0    /* 0b	[5] */
#define R118_FTDM_IN44_REVERSE_IN_BYTE_IC_1       0x0    /* 0b	[6] */
#define R118_FTDM_IN44_SLOT_ENABLE_IN_IC_1        0x0    /* 0b	[7] */
#define R118_FTDM_IN44_BYTE_IN_POS_IC_1_MASK      0x3
#define R118_FTDM_IN44_BYTE_IN_POS_IC_1_SHIFT     0
#define R118_FTDM_IN44_CHANNEL_IN_POS_IC_1_MASK   0x1C
#define R118_FTDM_IN44_CHANNEL_IN_POS_IC_1_SHIFT  2
#define R118_FTDM_IN44_SERIAL_IN_SEL_IC_1_MASK    0x20
#define R118_FTDM_IN44_SERIAL_IN_SEL_IC_1_SHIFT   5
#define R118_FTDM_IN44_REVERSE_IN_BYTE_IC_1_MASK  0x40
#define R118_FTDM_IN44_REVERSE_IN_BYTE_IC_1_SHIFT 6
#define R118_FTDM_IN44_SLOT_ENABLE_IN_IC_1_MASK   0x80
#define R118_FTDM_IN44_SLOT_ENABLE_IN_IC_1_SHIFT  7

/* FTDM_IN45 (IC 1) */
#define R119_FTDM_IN45_BYTE_IN_POS_IC_1           0x0    /* 00b	[1:0] */
#define R119_FTDM_IN45_CHANNEL_IN_POS_IC_1        0x0    /* 000b	[4:2] */
#define R119_FTDM_IN45_SERIAL_IN_SEL_IC_1         0x0    /* 0b	[5] */
#define R119_FTDM_IN45_REVERSE_IN_BYTE_IC_1       0x0    /* 0b	[6] */
#define R119_FTDM_IN45_SLOT_ENABLE_IN_IC_1        0x0    /* 0b	[7] */
#define R119_FTDM_IN45_BYTE_IN_POS_IC_1_MASK      0x3
#define R119_FTDM_IN45_BYTE_IN_POS_IC_1_SHIFT     0
#define R119_FTDM_IN45_CHANNEL_IN_POS_IC_1_MASK   0x1C
#define R119_FTDM_IN45_CHANNEL_IN_POS_IC_1_SHIFT  2
#define R119_FTDM_IN45_SERIAL_IN_SEL_IC_1_MASK    0x20
#define R119_FTDM_IN45_SERIAL_IN_SEL_IC_1_SHIFT   5
#define R119_FTDM_IN45_REVERSE_IN_BYTE_IC_1_MASK  0x40
#define R119_FTDM_IN45_REVERSE_IN_BYTE_IC_1_SHIFT 6
#define R119_FTDM_IN45_SLOT_ENABLE_IN_IC_1_MASK   0x80
#define R119_FTDM_IN45_SLOT_ENABLE_IN_IC_1_SHIFT  7

/* FTDM_IN46 (IC 1) */
#define R120_FTDM_IN46_BYTE_IN_POS_IC_1           0x0    /* 00b	[1:0] */
#define R120_FTDM_IN46_CHANNEL_IN_POS_IC_1        0x0    /* 000b	[4:2] */
#define R120_FTDM_IN46_SERIAL_IN_SEL_IC_1         0x0    /* 0b	[5] */
#define R120_FTDM_IN46_REVERSE_IN_BYTE_IC_1       0x0    /* 0b	[6] */
#define R120_FTDM_IN46_SLOT_ENABLE_IN_IC_1        0x0    /* 0b	[7] */
#define R120_FTDM_IN46_BYTE_IN_POS_IC_1_MASK      0x3
#define R120_FTDM_IN46_BYTE_IN_POS_IC_1_SHIFT     0
#define R120_FTDM_IN46_CHANNEL_IN_POS_IC_1_MASK   0x1C
#define R120_FTDM_IN46_CHANNEL_IN_POS_IC_1_SHIFT  2
#define R120_FTDM_IN46_SERIAL_IN_SEL_IC_1_MASK    0x20
#define R120_FTDM_IN46_SERIAL_IN_SEL_IC_1_SHIFT   5
#define R120_FTDM_IN46_REVERSE_IN_BYTE_IC_1_MASK  0x40
#define R120_FTDM_IN46_REVERSE_IN_BYTE_IC_1_SHIFT 6
#define R120_FTDM_IN46_SLOT_ENABLE_IN_IC_1_MASK   0x80
#define R120_FTDM_IN46_SLOT_ENABLE_IN_IC_1_SHIFT  7

/* FTDM_IN47 (IC 1) */
#define R121_FTDM_IN47_BYTE_IN_POS_IC_1           0x0    /* 00b	[1:0] */
#define R121_FTDM_IN47_CHANNEL_IN_POS_IC_1        0x0    /* 000b	[4:2] */
#define R121_FTDM_IN47_SERIAL_IN_SEL_IC_1         0x0    /* 0b	[5] */
#define R121_FTDM_IN47_REVERSE_IN_BYTE_IC_1       0x0    /* 0b	[6] */
#define R121_FTDM_IN47_SLOT_ENABLE_IN_IC_1        0x0    /* 0b	[7] */
#define R121_FTDM_IN47_BYTE_IN_POS_IC_1_MASK      0x3
#define R121_FTDM_IN47_BYTE_IN_POS_IC_1_SHIFT     0
#define R121_FTDM_IN47_CHANNEL_IN_POS_IC_1_MASK   0x1C
#define R121_FTDM_IN47_CHANNEL_IN_POS_IC_1_SHIFT  2
#define R121_FTDM_IN47_SERIAL_IN_SEL_IC_1_MASK    0x20
#define R121_FTDM_IN47_SERIAL_IN_SEL_IC_1_SHIFT   5
#define R121_FTDM_IN47_REVERSE_IN_BYTE_IC_1_MASK  0x40
#define R121_FTDM_IN47_REVERSE_IN_BYTE_IC_1_SHIFT 6
#define R121_FTDM_IN47_SLOT_ENABLE_IN_IC_1_MASK   0x80
#define R121_FTDM_IN47_SLOT_ENABLE_IN_IC_1_SHIFT  7

/* FTDM_IN48 (IC 1) */
#define R122_FTDM_IN48_BYTE_IN_POS_IC_1           0x0    /* 00b	[1:0] */
#define R122_FTDM_IN48_CHANNEL_IN_POS_IC_1        0x0    /* 000b	[4:2] */
#define R122_FTDM_IN48_SERIAL_IN_SEL_IC_1         0x0    /* 0b	[5] */
#define R122_FTDM_IN48_REVERSE_IN_BYTE_IC_1       0x0    /* 0b	[6] */
#define R122_FTDM_IN48_SLOT_ENABLE_IN_IC_1        0x0    /* 0b	[7] */
#define R122_FTDM_IN48_BYTE_IN_POS_IC_1_MASK      0x3
#define R122_FTDM_IN48_BYTE_IN_POS_IC_1_SHIFT     0
#define R122_FTDM_IN48_CHANNEL_IN_POS_IC_1_MASK   0x1C
#define R122_FTDM_IN48_CHANNEL_IN_POS_IC_1_SHIFT  2
#define R122_FTDM_IN48_SERIAL_IN_SEL_IC_1_MASK    0x20
#define R122_FTDM_IN48_SERIAL_IN_SEL_IC_1_SHIFT   5
#define R122_FTDM_IN48_REVERSE_IN_BYTE_IC_1_MASK  0x40
#define R122_FTDM_IN48_REVERSE_IN_BYTE_IC_1_SHIFT 6
#define R122_FTDM_IN48_SLOT_ENABLE_IN_IC_1_MASK   0x80
#define R122_FTDM_IN48_SLOT_ENABLE_IN_IC_1_SHIFT  7

/* FTDM_IN49 (IC 1) */
#define R123_FTDM_IN49_BYTE_IN_POS_IC_1           0x0    /* 00b	[1:0] */
#define R123_FTDM_IN49_CHANNEL_IN_POS_IC_1        0x0    /* 000b	[4:2] */
#define R123_FTDM_IN49_SERIAL_IN_SEL_IC_1         0x0    /* 0b	[5] */
#define R123_FTDM_IN49_REVERSE_IN_BYTE_IC_1       0x0    /* 0b	[6] */
#define R123_FTDM_IN49_SLOT_ENABLE_IN_IC_1        0x0    /* 0b	[7] */
#define R123_FTDM_IN49_BYTE_IN_POS_IC_1_MASK      0x3
#define R123_FTDM_IN49_BYTE_IN_POS_IC_1_SHIFT     0
#define R123_FTDM_IN49_CHANNEL_IN_POS_IC_1_MASK   0x1C
#define R123_FTDM_IN49_CHANNEL_IN_POS_IC_1_SHIFT  2
#define R123_FTDM_IN49_SERIAL_IN_SEL_IC_1_MASK    0x20
#define R123_FTDM_IN49_SERIAL_IN_SEL_IC_1_SHIFT   5
#define R123_FTDM_IN49_REVERSE_IN_BYTE_IC_1_MASK  0x40
#define R123_FTDM_IN49_REVERSE_IN_BYTE_IC_1_SHIFT 6
#define R123_FTDM_IN49_SLOT_ENABLE_IN_IC_1_MASK   0x80
#define R123_FTDM_IN49_SLOT_ENABLE_IN_IC_1_SHIFT  7

/* FTDM_IN50 (IC 1) */
#define R124_FTDM_IN50_BYTE_IN_POS_IC_1           0x0    /* 00b	[1:0] */
#define R124_FTDM_IN50_CHANNEL_IN_POS_IC_1        0x0    /* 000b	[4:2] */
#define R124_FTDM_IN50_SERIAL_IN_SEL_IC_1         0x0    /* 0b	[5] */
#define R124_FTDM_IN50_REVERSE_IN_BYTE_IC_1       0x0    /* 0b	[6] */
#define R124_FTDM_IN50_SLOT_ENABLE_IN_IC_1        0x0    /* 0b	[7] */
#define R124_FTDM_IN50_BYTE_IN_POS_IC_1_MASK      0x3
#define R124_FTDM_IN50_BYTE_IN_POS_IC_1_SHIFT     0
#define R124_FTDM_IN50_CHANNEL_IN_POS_IC_1_MASK   0x1C
#define R124_FTDM_IN50_CHANNEL_IN_POS_IC_1_SHIFT  2
#define R124_FTDM_IN50_SERIAL_IN_SEL_IC_1_MASK    0x20
#define R124_FTDM_IN50_SERIAL_IN_SEL_IC_1_SHIFT   5
#define R124_FTDM_IN50_REVERSE_IN_BYTE_IC_1_MASK  0x40
#define R124_FTDM_IN50_REVERSE_IN_BYTE_IC_1_SHIFT 6
#define R124_FTDM_IN50_SLOT_ENABLE_IN_IC_1_MASK   0x80
#define R124_FTDM_IN50_SLOT_ENABLE_IN_IC_1_SHIFT  7

/* FTDM_IN51 (IC 1) */
#define R125_FTDM_IN51_BYTE_IN_POS_IC_1           0x0    /* 00b	[1:0] */
#define R125_FTDM_IN51_CHANNEL_IN_POS_IC_1        0x0    /* 000b	[4:2] */
#define R125_FTDM_IN51_SERIAL_IN_SEL_IC_1         0x0    /* 0b	[5] */
#define R125_FTDM_IN51_REVERSE_IN_BYTE_IC_1       0x0    /* 0b	[6] */
#define R125_FTDM_IN51_SLOT_ENABLE_IN_IC_1        0x0    /* 0b	[7] */
#define R125_FTDM_IN51_BYTE_IN_POS_IC_1_MASK      0x3
#define R125_FTDM_IN51_BYTE_IN_POS_IC_1_SHIFT     0
#define R125_FTDM_IN51_CHANNEL_IN_POS_IC_1_MASK   0x1C
#define R125_FTDM_IN51_CHANNEL_IN_POS_IC_1_SHIFT  2
#define R125_FTDM_IN51_SERIAL_IN_SEL_IC_1_MASK    0x20
#define R125_FTDM_IN51_SERIAL_IN_SEL_IC_1_SHIFT   5
#define R125_FTDM_IN51_REVERSE_IN_BYTE_IC_1_MASK  0x40
#define R125_FTDM_IN51_REVERSE_IN_BYTE_IC_1_SHIFT 6
#define R125_FTDM_IN51_SLOT_ENABLE_IN_IC_1_MASK   0x80
#define R125_FTDM_IN51_SLOT_ENABLE_IN_IC_1_SHIFT  7

/* FTDM_IN52 (IC 1) */
#define R126_FTDM_IN52_BYTE_IN_POS_IC_1           0x0    /* 00b	[1:0] */
#define R126_FTDM_IN52_CHANNEL_IN_POS_IC_1        0x0    /* 000b	[4:2] */
#define R126_FTDM_IN52_SERIAL_IN_SEL_IC_1         0x0    /* 0b	[5] */
#define R126_FTDM_IN52_REVERSE_IN_BYTE_IC_1       0x0    /* 0b	[6] */
#define R126_FTDM_IN52_SLOT_ENABLE_IN_IC_1        0x0    /* 0b	[7] */
#define R126_FTDM_IN52_BYTE_IN_POS_IC_1_MASK      0x3
#define R126_FTDM_IN52_BYTE_IN_POS_IC_1_SHIFT     0
#define R126_FTDM_IN52_CHANNEL_IN_POS_IC_1_MASK   0x1C
#define R126_FTDM_IN52_CHANNEL_IN_POS_IC_1_SHIFT  2
#define R126_FTDM_IN52_SERIAL_IN_SEL_IC_1_MASK    0x20
#define R126_FTDM_IN52_SERIAL_IN_SEL_IC_1_SHIFT   5
#define R126_FTDM_IN52_REVERSE_IN_BYTE_IC_1_MASK  0x40
#define R126_FTDM_IN52_REVERSE_IN_BYTE_IC_1_SHIFT 6
#define R126_FTDM_IN52_SLOT_ENABLE_IN_IC_1_MASK   0x80
#define R126_FTDM_IN52_SLOT_ENABLE_IN_IC_1_SHIFT  7

/* FTDM_IN53 (IC 1) */
#define R127_FTDM_IN53_BYTE_IN_POS_IC_1           0x0    /* 00b	[1:0] */
#define R127_FTDM_IN53_CHANNEL_IN_POS_IC_1        0x0    /* 000b	[4:2] */
#define R127_FTDM_IN53_SERIAL_IN_SEL_IC_1         0x0    /* 0b	[5] */
#define R127_FTDM_IN53_REVERSE_IN_BYTE_IC_1       0x0    /* 0b	[6] */
#define R127_FTDM_IN53_SLOT_ENABLE_IN_IC_1        0x0    /* 0b	[7] */
#define R127_FTDM_IN53_BYTE_IN_POS_IC_1_MASK      0x3
#define R127_FTDM_IN53_BYTE_IN_POS_IC_1_SHIFT     0
#define R127_FTDM_IN53_CHANNEL_IN_POS_IC_1_MASK   0x1C
#define R127_FTDM_IN53_CHANNEL_IN_POS_IC_1_SHIFT  2
#define R127_FTDM_IN53_SERIAL_IN_SEL_IC_1_MASK    0x20
#define R127_FTDM_IN53_SERIAL_IN_SEL_IC_1_SHIFT   5
#define R127_FTDM_IN53_REVERSE_IN_BYTE_IC_1_MASK  0x40
#define R127_FTDM_IN53_REVERSE_IN_BYTE_IC_1_SHIFT 6
#define R127_FTDM_IN53_SLOT_ENABLE_IN_IC_1_MASK   0x80
#define R127_FTDM_IN53_SLOT_ENABLE_IN_IC_1_SHIFT  7

/* FTDM_IN54 (IC 1) */
#define R128_FTDM_IN54_BYTE_IN_POS_IC_1           0x0    /* 00b	[1:0] */
#define R128_FTDM_IN54_CHANNEL_IN_POS_IC_1        0x0    /* 000b	[4:2] */
#define R128_FTDM_IN54_SERIAL_IN_SEL_IC_1         0x0    /* 0b	[5] */
#define R128_FTDM_IN54_REVERSE_IN_BYTE_IC_1       0x0    /* 0b	[6] */
#define R128_FTDM_IN54_SLOT_ENABLE_IN_IC_1        0x0    /* 0b	[7] */
#define R128_FTDM_IN54_BYTE_IN_POS_IC_1_MASK      0x3
#define R128_FTDM_IN54_BYTE_IN_POS_IC_1_SHIFT     0
#define R128_FTDM_IN54_CHANNEL_IN_POS_IC_1_MASK   0x1C
#define R128_FTDM_IN54_CHANNEL_IN_POS_IC_1_SHIFT  2
#define R128_FTDM_IN54_SERIAL_IN_SEL_IC_1_MASK    0x20
#define R128_FTDM_IN54_SERIAL_IN_SEL_IC_1_SHIFT   5
#define R128_FTDM_IN54_REVERSE_IN_BYTE_IC_1_MASK  0x40
#define R128_FTDM_IN54_REVERSE_IN_BYTE_IC_1_SHIFT 6
#define R128_FTDM_IN54_SLOT_ENABLE_IN_IC_1_MASK   0x80
#define R128_FTDM_IN54_SLOT_ENABLE_IN_IC_1_SHIFT  7

/* FTDM_IN55 (IC 1) */
#define R129_FTDM_IN55_BYTE_IN_POS_IC_1           0x0    /* 00b	[1:0] */
#define R129_FTDM_IN55_CHANNEL_IN_POS_IC_1        0x0    /* 000b	[4:2] */
#define R129_FTDM_IN55_SERIAL_IN_SEL_IC_1         0x0    /* 0b	[5] */
#define R129_FTDM_IN55_REVERSE_IN_BYTE_IC_1       0x0    /* 0b	[6] */
#define R129_FTDM_IN55_SLOT_ENABLE_IN_IC_1        0x0    /* 0b	[7] */
#define R129_FTDM_IN55_BYTE_IN_POS_IC_1_MASK      0x3
#define R129_FTDM_IN55_BYTE_IN_POS_IC_1_SHIFT     0
#define R129_FTDM_IN55_CHANNEL_IN_POS_IC_1_MASK   0x1C
#define R129_FTDM_IN55_CHANNEL_IN_POS_IC_1_SHIFT  2
#define R129_FTDM_IN55_SERIAL_IN_SEL_IC_1_MASK    0x20
#define R129_FTDM_IN55_SERIAL_IN_SEL_IC_1_SHIFT   5
#define R129_FTDM_IN55_REVERSE_IN_BYTE_IC_1_MASK  0x40
#define R129_FTDM_IN55_REVERSE_IN_BYTE_IC_1_SHIFT 6
#define R129_FTDM_IN55_SLOT_ENABLE_IN_IC_1_MASK   0x80
#define R129_FTDM_IN55_SLOT_ENABLE_IN_IC_1_SHIFT  7

/* FTDM_IN56 (IC 1) */
#define R130_FTDM_IN56_BYTE_IN_POS_IC_1           0x0    /* 00b	[1:0] */
#define R130_FTDM_IN56_CHANNEL_IN_POS_IC_1        0x0    /* 000b	[4:2] */
#define R130_FTDM_IN56_SERIAL_IN_SEL_IC_1         0x0    /* 0b	[5] */
#define R130_FTDM_IN56_REVERSE_IN_BYTE_IC_1       0x0    /* 0b	[6] */
#define R130_FTDM_IN56_SLOT_ENABLE_IN_IC_1        0x0    /* 0b	[7] */
#define R130_FTDM_IN56_BYTE_IN_POS_IC_1_MASK      0x3
#define R130_FTDM_IN56_BYTE_IN_POS_IC_1_SHIFT     0
#define R130_FTDM_IN56_CHANNEL_IN_POS_IC_1_MASK   0x1C
#define R130_FTDM_IN56_CHANNEL_IN_POS_IC_1_SHIFT  2
#define R130_FTDM_IN56_SERIAL_IN_SEL_IC_1_MASK    0x20
#define R130_FTDM_IN56_SERIAL_IN_SEL_IC_1_SHIFT   5
#define R130_FTDM_IN56_REVERSE_IN_BYTE_IC_1_MASK  0x40
#define R130_FTDM_IN56_REVERSE_IN_BYTE_IC_1_SHIFT 6
#define R130_FTDM_IN56_SLOT_ENABLE_IN_IC_1_MASK   0x80
#define R130_FTDM_IN56_SLOT_ENABLE_IN_IC_1_SHIFT  7

/* FTDM_IN57 (IC 1) */
#define R131_FTDM_IN57_BYTE_IN_POS_IC_1           0x0    /* 00b	[1:0] */
#define R131_FTDM_IN57_CHANNEL_IN_POS_IC_1        0x0    /* 000b	[4:2] */
#define R131_FTDM_IN57_SERIAL_IN_SEL_IC_1         0x0    /* 0b	[5] */
#define R131_FTDM_IN57_REVERSE_IN_BYTE_IC_1       0x0    /* 0b	[6] */
#define R131_FTDM_IN57_SLOT_ENABLE_IN_IC_1        0x0    /* 0b	[7] */
#define R131_FTDM_IN57_BYTE_IN_POS_IC_1_MASK      0x3
#define R131_FTDM_IN57_BYTE_IN_POS_IC_1_SHIFT     0
#define R131_FTDM_IN57_CHANNEL_IN_POS_IC_1_MASK   0x1C
#define R131_FTDM_IN57_CHANNEL_IN_POS_IC_1_SHIFT  2
#define R131_FTDM_IN57_SERIAL_IN_SEL_IC_1_MASK    0x20
#define R131_FTDM_IN57_SERIAL_IN_SEL_IC_1_SHIFT   5
#define R131_FTDM_IN57_REVERSE_IN_BYTE_IC_1_MASK  0x40
#define R131_FTDM_IN57_REVERSE_IN_BYTE_IC_1_SHIFT 6
#define R131_FTDM_IN57_SLOT_ENABLE_IN_IC_1_MASK   0x80
#define R131_FTDM_IN57_SLOT_ENABLE_IN_IC_1_SHIFT  7

/* FTDM_IN58 (IC 1) */
#define R132_FTDM_IN58_BYTE_IN_POS_IC_1           0x0    /* 00b	[1:0] */
#define R132_FTDM_IN58_CHANNEL_IN_POS_IC_1        0x0    /* 000b	[4:2] */
#define R132_FTDM_IN58_SERIAL_IN_SEL_IC_1         0x0    /* 0b	[5] */
#define R132_FTDM_IN58_REVERSE_IN_BYTE_IC_1       0x0    /* 0b	[6] */
#define R132_FTDM_IN58_SLOT_ENABLE_IN_IC_1        0x0    /* 0b	[7] */
#define R132_FTDM_IN58_BYTE_IN_POS_IC_1_MASK      0x3
#define R132_FTDM_IN58_BYTE_IN_POS_IC_1_SHIFT     0
#define R132_FTDM_IN58_CHANNEL_IN_POS_IC_1_MASK   0x1C
#define R132_FTDM_IN58_CHANNEL_IN_POS_IC_1_SHIFT  2
#define R132_FTDM_IN58_SERIAL_IN_SEL_IC_1_MASK    0x20
#define R132_FTDM_IN58_SERIAL_IN_SEL_IC_1_SHIFT   5
#define R132_FTDM_IN58_REVERSE_IN_BYTE_IC_1_MASK  0x40
#define R132_FTDM_IN58_REVERSE_IN_BYTE_IC_1_SHIFT 6
#define R132_FTDM_IN58_SLOT_ENABLE_IN_IC_1_MASK   0x80
#define R132_FTDM_IN58_SLOT_ENABLE_IN_IC_1_SHIFT  7

/* FTDM_IN59 (IC 1) */
#define R133_FTDM_IN59_BYTE_IN_POS_IC_1           0x0    /* 00b	[1:0] */
#define R133_FTDM_IN59_CHANNEL_IN_POS_IC_1        0x0    /* 000b	[4:2] */
#define R133_FTDM_IN59_SERIAL_IN_SEL_IC_1         0x0    /* 0b	[5] */
#define R133_FTDM_IN59_REVERSE_IN_BYTE_IC_1       0x0    /* 0b	[6] */
#define R133_FTDM_IN59_SLOT_ENABLE_IN_IC_1        0x0    /* 0b	[7] */
#define R133_FTDM_IN59_BYTE_IN_POS_IC_1_MASK      0x3
#define R133_FTDM_IN59_BYTE_IN_POS_IC_1_SHIFT     0
#define R133_FTDM_IN59_CHANNEL_IN_POS_IC_1_MASK   0x1C
#define R133_FTDM_IN59_CHANNEL_IN_POS_IC_1_SHIFT  2
#define R133_FTDM_IN59_SERIAL_IN_SEL_IC_1_MASK    0x20
#define R133_FTDM_IN59_SERIAL_IN_SEL_IC_1_SHIFT   5
#define R133_FTDM_IN59_REVERSE_IN_BYTE_IC_1_MASK  0x40
#define R133_FTDM_IN59_REVERSE_IN_BYTE_IC_1_SHIFT 6
#define R133_FTDM_IN59_SLOT_ENABLE_IN_IC_1_MASK   0x80
#define R133_FTDM_IN59_SLOT_ENABLE_IN_IC_1_SHIFT  7

/* FTDM_IN60 (IC 1) */
#define R134_FTDM_IN60_BYTE_IN_POS_IC_1           0x0    /* 00b	[1:0] */
#define R134_FTDM_IN60_CHANNEL_IN_POS_IC_1        0x0    /* 000b	[4:2] */
#define R134_FTDM_IN60_SERIAL_IN_SEL_IC_1         0x0    /* 0b	[5] */
#define R134_FTDM_IN60_REVERSE_IN_BYTE_IC_1       0x0    /* 0b	[6] */
#define R134_FTDM_IN60_SLOT_ENABLE_IN_IC_1        0x0    /* 0b	[7] */
#define R134_FTDM_IN60_BYTE_IN_POS_IC_1_MASK      0x3
#define R134_FTDM_IN60_BYTE_IN_POS_IC_1_SHIFT     0
#define R134_FTDM_IN60_CHANNEL_IN_POS_IC_1_MASK   0x1C
#define R134_FTDM_IN60_CHANNEL_IN_POS_IC_1_SHIFT  2
#define R134_FTDM_IN60_SERIAL_IN_SEL_IC_1_MASK    0x20
#define R134_FTDM_IN60_SERIAL_IN_SEL_IC_1_SHIFT   5
#define R134_FTDM_IN60_REVERSE_IN_BYTE_IC_1_MASK  0x40
#define R134_FTDM_IN60_REVERSE_IN_BYTE_IC_1_SHIFT 6
#define R134_FTDM_IN60_SLOT_ENABLE_IN_IC_1_MASK   0x80
#define R134_FTDM_IN60_SLOT_ENABLE_IN_IC_1_SHIFT  7

/* FTDM_IN61 (IC 1) */
#define R135_FTDM_IN61_BYTE_IN_POS_IC_1           0x0    /* 00b	[1:0] */
#define R135_FTDM_IN61_CHANNEL_IN_POS_IC_1        0x0    /* 000b	[4:2] */
#define R135_FTDM_IN61_SERIAL_IN_SEL_IC_1         0x0    /* 0b	[5] */
#define R135_FTDM_IN61_REVERSE_IN_BYTE_IC_1       0x0    /* 0b	[6] */
#define R135_FTDM_IN61_SLOT_ENABLE_IN_IC_1        0x0    /* 0b	[7] */
#define R135_FTDM_IN61_BYTE_IN_POS_IC_1_MASK      0x3
#define R135_FTDM_IN61_BYTE_IN_POS_IC_1_SHIFT     0
#define R135_FTDM_IN61_CHANNEL_IN_POS_IC_1_MASK   0x1C
#define R135_FTDM_IN61_CHANNEL_IN_POS_IC_1_SHIFT  2
#define R135_FTDM_IN61_SERIAL_IN_SEL_IC_1_MASK    0x20
#define R135_FTDM_IN61_SERIAL_IN_SEL_IC_1_SHIFT   5
#define R135_FTDM_IN61_REVERSE_IN_BYTE_IC_1_MASK  0x40
#define R135_FTDM_IN61_REVERSE_IN_BYTE_IC_1_SHIFT 6
#define R135_FTDM_IN61_SLOT_ENABLE_IN_IC_1_MASK   0x80
#define R135_FTDM_IN61_SLOT_ENABLE_IN_IC_1_SHIFT  7

/* FTDM_IN62 (IC 1) */
#define R136_FTDM_IN62_BYTE_IN_POS_IC_1           0x0    /* 00b	[1:0] */
#define R136_FTDM_IN62_CHANNEL_IN_POS_IC_1        0x0    /* 000b	[4:2] */
#define R136_FTDM_IN62_SERIAL_IN_SEL_IC_1         0x0    /* 0b	[5] */
#define R136_FTDM_IN62_REVERSE_IN_BYTE_IC_1       0x0    /* 0b	[6] */
#define R136_FTDM_IN62_SLOT_ENABLE_IN_IC_1        0x0    /* 0b	[7] */
#define R136_FTDM_IN62_BYTE_IN_POS_IC_1_MASK      0x3
#define R136_FTDM_IN62_BYTE_IN_POS_IC_1_SHIFT     0
#define R136_FTDM_IN62_CHANNEL_IN_POS_IC_1_MASK   0x1C
#define R136_FTDM_IN62_CHANNEL_IN_POS_IC_1_SHIFT  2
#define R136_FTDM_IN62_SERIAL_IN_SEL_IC_1_MASK    0x20
#define R136_FTDM_IN62_SERIAL_IN_SEL_IC_1_SHIFT   5
#define R136_FTDM_IN62_REVERSE_IN_BYTE_IC_1_MASK  0x40
#define R136_FTDM_IN62_REVERSE_IN_BYTE_IC_1_SHIFT 6
#define R136_FTDM_IN62_SLOT_ENABLE_IN_IC_1_MASK   0x80
#define R136_FTDM_IN62_SLOT_ENABLE_IN_IC_1_SHIFT  7

/* FTDM_IN63 (IC 1) */
#define R137_FTDM_IN63_BYTE_IN_POS_IC_1           0x0    /* 00b	[1:0] */
#define R137_FTDM_IN63_CHANNEL_IN_POS_IC_1        0x0    /* 000b	[4:2] */
#define R137_FTDM_IN63_SERIAL_IN_SEL_IC_1         0x0    /* 0b	[5] */
#define R137_FTDM_IN63_REVERSE_IN_BYTE_IC_1       0x0    /* 0b	[6] */
#define R137_FTDM_IN63_SLOT_ENABLE_IN_IC_1        0x0    /* 0b	[7] */
#define R137_FTDM_IN63_BYTE_IN_POS_IC_1_MASK      0x3
#define R137_FTDM_IN63_BYTE_IN_POS_IC_1_SHIFT     0
#define R137_FTDM_IN63_CHANNEL_IN_POS_IC_1_MASK   0x1C
#define R137_FTDM_IN63_CHANNEL_IN_POS_IC_1_SHIFT  2
#define R137_FTDM_IN63_SERIAL_IN_SEL_IC_1_MASK    0x20
#define R137_FTDM_IN63_SERIAL_IN_SEL_IC_1_SHIFT   5
#define R137_FTDM_IN63_REVERSE_IN_BYTE_IC_1_MASK  0x40
#define R137_FTDM_IN63_REVERSE_IN_BYTE_IC_1_SHIFT 6
#define R137_FTDM_IN63_SLOT_ENABLE_IN_IC_1_MASK   0x80
#define R137_FTDM_IN63_SLOT_ENABLE_IN_IC_1_SHIFT  7

/* FTDM_OUT0 (IC 1) */
#define R138_FTDM_OUT0_BYTE_OUT_POS_IC_1          0x0    /* 00b	[1:0] */
#define R138_FTDM_OUT0_CHANNEL_OUT_POS_IC_1       0x0    /* 000b	[4:2] */
#define R138_FTDM_OUT0_SERIAL_OUT_SEL_IC_1        0x0    /* 0b	[5] */
#define R138_FTDM_OUT0_REVERSE_OUT_BYTE_IC_1      0x0    /* 0b	[6] */
#define R138_FTDM_OUT0_SLOT_ENABLE_OUT_IC_1       0x0    /* 0b	[7] */
#define R138_FTDM_OUT0_BYTE_OUT_POS_IC_1_MASK     0x3
#define R138_FTDM_OUT0_BYTE_OUT_POS_IC_1_SHIFT    0
#define R138_FTDM_OUT0_CHANNEL_OUT_POS_IC_1_MASK  0x1C
#define R138_FTDM_OUT0_CHANNEL_OUT_POS_IC_1_SHIFT 2
#define R138_FTDM_OUT0_SERIAL_OUT_SEL_IC_1_MASK   0x20
#define R138_FTDM_OUT0_SERIAL_OUT_SEL_IC_1_SHIFT  5
#define R138_FTDM_OUT0_REVERSE_OUT_BYTE_IC_1_MASK 0x40
#define R138_FTDM_OUT0_REVERSE_OUT_BYTE_IC_1_SHIFT 6
#define R138_FTDM_OUT0_SLOT_ENABLE_OUT_IC_1_MASK  0x80
#define R138_FTDM_OUT0_SLOT_ENABLE_OUT_IC_1_SHIFT 7

/* FTDM_OUT1 (IC 1) */
#define R139_FTDM_OUT1_BYTE_OUT_POS_IC_1          0x0    /* 00b	[1:0] */
#define R139_FTDM_OUT1_CHANNEL_OUT_POS_IC_1       0x0    /* 000b	[4:2] */
#define R139_FTDM_OUT1_SERIAL_OUT_SEL_IC_1        0x0    /* 0b	[5] */
#define R139_FTDM_OUT1_REVERSE_OUT_BYTE_IC_1      0x0    /* 0b	[6] */
#define R139_FTDM_OUT1_SLOT_ENABLE_OUT_IC_1       0x0    /* 0b	[7] */
#define R139_FTDM_OUT1_BYTE_OUT_POS_IC_1_MASK     0x3
#define R139_FTDM_OUT1_BYTE_OUT_POS_IC_1_SHIFT    0
#define R139_FTDM_OUT1_CHANNEL_OUT_POS_IC_1_MASK  0x1C
#define R139_FTDM_OUT1_CHANNEL_OUT_POS_IC_1_SHIFT 2
#define R139_FTDM_OUT1_SERIAL_OUT_SEL_IC_1_MASK   0x20
#define R139_FTDM_OUT1_SERIAL_OUT_SEL_IC_1_SHIFT  5
#define R139_FTDM_OUT1_REVERSE_OUT_BYTE_IC_1_MASK 0x40
#define R139_FTDM_OUT1_REVERSE_OUT_BYTE_IC_1_SHIFT 6
#define R139_FTDM_OUT1_SLOT_ENABLE_OUT_IC_1_MASK  0x80
#define R139_FTDM_OUT1_SLOT_ENABLE_OUT_IC_1_SHIFT 7

/* FTDM_OUT2 (IC 1) */
#define R140_FTDM_OUT2_BYTE_OUT_POS_IC_1          0x0    /* 00b	[1:0] */
#define R140_FTDM_OUT2_CHANNEL_OUT_POS_IC_1       0x0    /* 000b	[4:2] */
#define R140_FTDM_OUT2_SERIAL_OUT_SEL_IC_1        0x0    /* 0b	[5] */
#define R140_FTDM_OUT2_REVERSE_OUT_BYTE_IC_1      0x0    /* 0b	[6] */
#define R140_FTDM_OUT2_SLOT_ENABLE_OUT_IC_1       0x0    /* 0b	[7] */
#define R140_FTDM_OUT2_BYTE_OUT_POS_IC_1_MASK     0x3
#define R140_FTDM_OUT2_BYTE_OUT_POS_IC_1_SHIFT    0
#define R140_FTDM_OUT2_CHANNEL_OUT_POS_IC_1_MASK  0x1C
#define R140_FTDM_OUT2_CHANNEL_OUT_POS_IC_1_SHIFT 2
#define R140_FTDM_OUT2_SERIAL_OUT_SEL_IC_1_MASK   0x20
#define R140_FTDM_OUT2_SERIAL_OUT_SEL_IC_1_SHIFT  5
#define R140_FTDM_OUT2_REVERSE_OUT_BYTE_IC_1_MASK 0x40
#define R140_FTDM_OUT2_REVERSE_OUT_BYTE_IC_1_SHIFT 6
#define R140_FTDM_OUT2_SLOT_ENABLE_OUT_IC_1_MASK  0x80
#define R140_FTDM_OUT2_SLOT_ENABLE_OUT_IC_1_SHIFT 7

/* FTDM_OUT3 (IC 1) */
#define R141_FTDM_OUT3_BYTE_OUT_POS_IC_1          0x0    /* 00b	[1:0] */
#define R141_FTDM_OUT3_CHANNEL_OUT_POS_IC_1       0x0    /* 000b	[4:2] */
#define R141_FTDM_OUT3_SERIAL_OUT_SEL_IC_1        0x0    /* 0b	[5] */
#define R141_FTDM_OUT3_REVERSE_OUT_BYTE_IC_1      0x0    /* 0b	[6] */
#define R141_FTDM_OUT3_SLOT_ENABLE_OUT_IC_1       0x0    /* 0b	[7] */
#define R141_FTDM_OUT3_BYTE_OUT_POS_IC_1_MASK     0x3
#define R141_FTDM_OUT3_BYTE_OUT_POS_IC_1_SHIFT    0
#define R141_FTDM_OUT3_CHANNEL_OUT_POS_IC_1_MASK  0x1C
#define R141_FTDM_OUT3_CHANNEL_OUT_POS_IC_1_SHIFT 2
#define R141_FTDM_OUT3_SERIAL_OUT_SEL_IC_1_MASK   0x20
#define R141_FTDM_OUT3_SERIAL_OUT_SEL_IC_1_SHIFT  5
#define R141_FTDM_OUT3_REVERSE_OUT_BYTE_IC_1_MASK 0x40
#define R141_FTDM_OUT3_REVERSE_OUT_BYTE_IC_1_SHIFT 6
#define R141_FTDM_OUT3_SLOT_ENABLE_OUT_IC_1_MASK  0x80
#define R141_FTDM_OUT3_SLOT_ENABLE_OUT_IC_1_SHIFT 7

/* FTDM_OUT4 (IC 1) */
#define R142_FTDM_OUT4_BYTE_OUT_POS_IC_1          0x0    /* 00b	[1:0] */
#define R142_FTDM_OUT4_CHANNEL_OUT_POS_IC_1       0x0    /* 000b	[4:2] */
#define R142_FTDM_OUT4_SERIAL_OUT_SEL_IC_1        0x0    /* 0b	[5] */
#define R142_FTDM_OUT4_REVERSE_OUT_BYTE_IC_1      0x0    /* 0b	[6] */
#define R142_FTDM_OUT4_SLOT_ENABLE_OUT_IC_1       0x0    /* 0b	[7] */
#define R142_FTDM_OUT4_BYTE_OUT_POS_IC_1_MASK     0x3
#define R142_FTDM_OUT4_BYTE_OUT_POS_IC_1_SHIFT    0
#define R142_FTDM_OUT4_CHANNEL_OUT_POS_IC_1_MASK  0x1C
#define R142_FTDM_OUT4_CHANNEL_OUT_POS_IC_1_SHIFT 2
#define R142_FTDM_OUT4_SERIAL_OUT_SEL_IC_1_MASK   0x20
#define R142_FTDM_OUT4_SERIAL_OUT_SEL_IC_1_SHIFT  5
#define R142_FTDM_OUT4_REVERSE_OUT_BYTE_IC_1_MASK 0x40
#define R142_FTDM_OUT4_REVERSE_OUT_BYTE_IC_1_SHIFT 6
#define R142_FTDM_OUT4_SLOT_ENABLE_OUT_IC_1_MASK  0x80
#define R142_FTDM_OUT4_SLOT_ENABLE_OUT_IC_1_SHIFT 7

/* FTDM_OUT5 (IC 1) */
#define R143_FTDM_OUT5_BYTE_OUT_POS_IC_1          0x0    /* 00b	[1:0] */
#define R143_FTDM_OUT5_CHANNEL_OUT_POS_IC_1       0x0    /* 000b	[4:2] */
#define R143_FTDM_OUT5_SERIAL_OUT_SEL_IC_1        0x0    /* 0b	[5] */
#define R143_FTDM_OUT5_REVERSE_OUT_BYTE_IC_1      0x0    /* 0b	[6] */
#define R143_FTDM_OUT5_SLOT_ENABLE_OUT_IC_1       0x0    /* 0b	[7] */
#define R143_FTDM_OUT5_BYTE_OUT_POS_IC_1_MASK     0x3
#define R143_FTDM_OUT5_BYTE_OUT_POS_IC_1_SHIFT    0
#define R143_FTDM_OUT5_CHANNEL_OUT_POS_IC_1_MASK  0x1C
#define R143_FTDM_OUT5_CHANNEL_OUT_POS_IC_1_SHIFT 2
#define R143_FTDM_OUT5_SERIAL_OUT_SEL_IC_1_MASK   0x20
#define R143_FTDM_OUT5_SERIAL_OUT_SEL_IC_1_SHIFT  5
#define R143_FTDM_OUT5_REVERSE_OUT_BYTE_IC_1_MASK 0x40
#define R143_FTDM_OUT5_REVERSE_OUT_BYTE_IC_1_SHIFT 6
#define R143_FTDM_OUT5_SLOT_ENABLE_OUT_IC_1_MASK  0x80
#define R143_FTDM_OUT5_SLOT_ENABLE_OUT_IC_1_SHIFT 7

/* FTDM_OUT6 (IC 1) */
#define R144_FTDM_OUT6_BYTE_OUT_POS_IC_1          0x0    /* 00b	[1:0] */
#define R144_FTDM_OUT6_CHANNEL_OUT_POS_IC_1       0x0    /* 000b	[4:2] */
#define R144_FTDM_OUT6_SERIAL_OUT_SEL_IC_1        0x0    /* 0b	[5] */
#define R144_FTDM_OUT6_REVERSE_OUT_BYTE_IC_1      0x0    /* 0b	[6] */
#define R144_FTDM_OUT6_SLOT_ENABLE_OUT_IC_1       0x0    /* 0b	[7] */
#define R144_FTDM_OUT6_BYTE_OUT_POS_IC_1_MASK     0x3
#define R144_FTDM_OUT6_BYTE_OUT_POS_IC_1_SHIFT    0
#define R144_FTDM_OUT6_CHANNEL_OUT_POS_IC_1_MASK  0x1C
#define R144_FTDM_OUT6_CHANNEL_OUT_POS_IC_1_SHIFT 2
#define R144_FTDM_OUT6_SERIAL_OUT_SEL_IC_1_MASK   0x20
#define R144_FTDM_OUT6_SERIAL_OUT_SEL_IC_1_SHIFT  5
#define R144_FTDM_OUT6_REVERSE_OUT_BYTE_IC_1_MASK 0x40
#define R144_FTDM_OUT6_REVERSE_OUT_BYTE_IC_1_SHIFT 6
#define R144_FTDM_OUT6_SLOT_ENABLE_OUT_IC_1_MASK  0x80
#define R144_FTDM_OUT6_SLOT_ENABLE_OUT_IC_1_SHIFT 7

/* FTDM_OUT7 (IC 1) */
#define R145_FTDM_OUT7_BYTE_OUT_POS_IC_1          0x0    /* 00b	[1:0] */
#define R145_FTDM_OUT7_CHANNEL_OUT_POS_IC_1       0x0    /* 000b	[4:2] */
#define R145_FTDM_OUT7_SERIAL_OUT_SEL_IC_1        0x0    /* 0b	[5] */
#define R145_FTDM_OUT7_REVERSE_OUT_BYTE_IC_1      0x0    /* 0b	[6] */
#define R145_FTDM_OUT7_SLOT_ENABLE_OUT_IC_1       0x0    /* 0b	[7] */
#define R145_FTDM_OUT7_BYTE_OUT_POS_IC_1_MASK     0x3
#define R145_FTDM_OUT7_BYTE_OUT_POS_IC_1_SHIFT    0
#define R145_FTDM_OUT7_CHANNEL_OUT_POS_IC_1_MASK  0x1C
#define R145_FTDM_OUT7_CHANNEL_OUT_POS_IC_1_SHIFT 2
#define R145_FTDM_OUT7_SERIAL_OUT_SEL_IC_1_MASK   0x20
#define R145_FTDM_OUT7_SERIAL_OUT_SEL_IC_1_SHIFT  5
#define R145_FTDM_OUT7_REVERSE_OUT_BYTE_IC_1_MASK 0x40
#define R145_FTDM_OUT7_REVERSE_OUT_BYTE_IC_1_SHIFT 6
#define R145_FTDM_OUT7_SLOT_ENABLE_OUT_IC_1_MASK  0x80
#define R145_FTDM_OUT7_SLOT_ENABLE_OUT_IC_1_SHIFT 7

/* FTDM_OUT8 (IC 1) */
#define R146_FTDM_OUT8_BYTE_OUT_POS_IC_1          0x0    /* 00b	[1:0] */
#define R146_FTDM_OUT8_CHANNEL_OUT_POS_IC_1       0x0    /* 000b	[4:2] */
#define R146_FTDM_OUT8_SERIAL_OUT_SEL_IC_1        0x0    /* 0b	[5] */
#define R146_FTDM_OUT8_REVERSE_OUT_BYTE_IC_1      0x0    /* 0b	[6] */
#define R146_FTDM_OUT8_SLOT_ENABLE_OUT_IC_1       0x0    /* 0b	[7] */
#define R146_FTDM_OUT8_BYTE_OUT_POS_IC_1_MASK     0x3
#define R146_FTDM_OUT8_BYTE_OUT_POS_IC_1_SHIFT    0
#define R146_FTDM_OUT8_CHANNEL_OUT_POS_IC_1_MASK  0x1C
#define R146_FTDM_OUT8_CHANNEL_OUT_POS_IC_1_SHIFT 2
#define R146_FTDM_OUT8_SERIAL_OUT_SEL_IC_1_MASK   0x20
#define R146_FTDM_OUT8_SERIAL_OUT_SEL_IC_1_SHIFT  5
#define R146_FTDM_OUT8_REVERSE_OUT_BYTE_IC_1_MASK 0x40
#define R146_FTDM_OUT8_REVERSE_OUT_BYTE_IC_1_SHIFT 6
#define R146_FTDM_OUT8_SLOT_ENABLE_OUT_IC_1_MASK  0x80
#define R146_FTDM_OUT8_SLOT_ENABLE_OUT_IC_1_SHIFT 7

/* FTDM_OUT9 (IC 1) */
#define R147_FTDM_OUT9_BYTE_OUT_POS_IC_1          0x0    /* 00b	[1:0] */
#define R147_FTDM_OUT9_CHANNEL_OUT_POS_IC_1       0x0    /* 000b	[4:2] */
#define R147_FTDM_OUT9_SERIAL_OUT_SEL_IC_1        0x0    /* 0b	[5] */
#define R147_FTDM_OUT9_REVERSE_OUT_BYTE_IC_1      0x0    /* 0b	[6] */
#define R147_FTDM_OUT9_SLOT_ENABLE_OUT_IC_1       0x0    /* 0b	[7] */
#define R147_FTDM_OUT9_BYTE_OUT_POS_IC_1_MASK     0x3
#define R147_FTDM_OUT9_BYTE_OUT_POS_IC_1_SHIFT    0
#define R147_FTDM_OUT9_CHANNEL_OUT_POS_IC_1_MASK  0x1C
#define R147_FTDM_OUT9_CHANNEL_OUT_POS_IC_1_SHIFT 2
#define R147_FTDM_OUT9_SERIAL_OUT_SEL_IC_1_MASK   0x20
#define R147_FTDM_OUT9_SERIAL_OUT_SEL_IC_1_SHIFT  5
#define R147_FTDM_OUT9_REVERSE_OUT_BYTE_IC_1_MASK 0x40
#define R147_FTDM_OUT9_REVERSE_OUT_BYTE_IC_1_SHIFT 6
#define R147_FTDM_OUT9_SLOT_ENABLE_OUT_IC_1_MASK  0x80
#define R147_FTDM_OUT9_SLOT_ENABLE_OUT_IC_1_SHIFT 7

/* FTDM_OUT10 (IC 1) */
#define R148_FTDM_OUT10_BYTE_OUT_POS_IC_1         0x0    /* 00b	[1:0] */
#define R148_FTDM_OUT10_CHANNEL_OUT_POS_IC_1      0x0    /* 000b	[4:2] */
#define R148_FTDM_OUT10_SERIAL_OUT_SEL_IC_1       0x0    /* 0b	[5] */
#define R148_FTDM_OUT10_REVERSE_OUT_BYTE_IC_1     0x0    /* 0b	[6] */
#define R148_FTDM_OUT10_SLOT_ENABLE_OUT_IC_1      0x0    /* 0b	[7] */
#define R148_FTDM_OUT10_BYTE_OUT_POS_IC_1_MASK    0x3
#define R148_FTDM_OUT10_BYTE_OUT_POS_IC_1_SHIFT   0
#define R148_FTDM_OUT10_CHANNEL_OUT_POS_IC_1_MASK 0x1C
#define R148_FTDM_OUT10_CHANNEL_OUT_POS_IC_1_SHIFT 2
#define R148_FTDM_OUT10_SERIAL_OUT_SEL_IC_1_MASK  0x20
#define R148_FTDM_OUT10_SERIAL_OUT_SEL_IC_1_SHIFT 5
#define R148_FTDM_OUT10_REVERSE_OUT_BYTE_IC_1_MASK 0x40
#define R148_FTDM_OUT10_REVERSE_OUT_BYTE_IC_1_SHIFT 6
#define R148_FTDM_OUT10_SLOT_ENABLE_OUT_IC_1_MASK 0x80
#define R148_FTDM_OUT10_SLOT_ENABLE_OUT_IC_1_SHIFT 7

/* FTDM_OUT11 (IC 1) */
#define R149_FTDM_OUT11_BYTE_OUT_POS_IC_1         0x0    /* 00b	[1:0] */
#define R149_FTDM_OUT11_CHANNEL_OUT_POS_IC_1      0x0    /* 000b	[4:2] */
#define R149_FTDM_OUT11_SERIAL_OUT_SEL_IC_1       0x0    /* 0b	[5] */
#define R149_FTDM_OUT11_REVERSE_OUT_BYTE_IC_1     0x0    /* 0b	[6] */
#define R149_FTDM_OUT11_SLOT_ENABLE_OUT_IC_1      0x0    /* 0b	[7] */
#define R149_FTDM_OUT11_BYTE_OUT_POS_IC_1_MASK    0x3
#define R149_FTDM_OUT11_BYTE_OUT_POS_IC_1_SHIFT   0
#define R149_FTDM_OUT11_CHANNEL_OUT_POS_IC_1_MASK 0x1C
#define R149_FTDM_OUT11_CHANNEL_OUT_POS_IC_1_SHIFT 2
#define R149_FTDM_OUT11_SERIAL_OUT_SEL_IC_1_MASK  0x20
#define R149_FTDM_OUT11_SERIAL_OUT_SEL_IC_1_SHIFT 5
#define R149_FTDM_OUT11_REVERSE_OUT_BYTE_IC_1_MASK 0x40
#define R149_FTDM_OUT11_REVERSE_OUT_BYTE_IC_1_SHIFT 6
#define R149_FTDM_OUT11_SLOT_ENABLE_OUT_IC_1_MASK 0x80
#define R149_FTDM_OUT11_SLOT_ENABLE_OUT_IC_1_SHIFT 7

/* FTDM_OUT12 (IC 1) */
#define R150_FTDM_OUT12_BYTE_OUT_POS_IC_1         0x0    /* 00b	[1:0] */
#define R150_FTDM_OUT12_CHANNEL_OUT_POS_IC_1      0x0    /* 000b	[4:2] */
#define R150_FTDM_OUT12_SERIAL_OUT_SEL_IC_1       0x0    /* 0b	[5] */
#define R150_FTDM_OUT12_REVERSE_OUT_BYTE_IC_1     0x0    /* 0b	[6] */
#define R150_FTDM_OUT12_SLOT_ENABLE_OUT_IC_1      0x0    /* 0b	[7] */
#define R150_FTDM_OUT12_BYTE_OUT_POS_IC_1_MASK    0x3
#define R150_FTDM_OUT12_BYTE_OUT_POS_IC_1_SHIFT   0
#define R150_FTDM_OUT12_CHANNEL_OUT_POS_IC_1_MASK 0x1C
#define R150_FTDM_OUT12_CHANNEL_OUT_POS_IC_1_SHIFT 2
#define R150_FTDM_OUT12_SERIAL_OUT_SEL_IC_1_MASK  0x20
#define R150_FTDM_OUT12_SERIAL_OUT_SEL_IC_1_SHIFT 5
#define R150_FTDM_OUT12_REVERSE_OUT_BYTE_IC_1_MASK 0x40
#define R150_FTDM_OUT12_REVERSE_OUT_BYTE_IC_1_SHIFT 6
#define R150_FTDM_OUT12_SLOT_ENABLE_OUT_IC_1_MASK 0x80
#define R150_FTDM_OUT12_SLOT_ENABLE_OUT_IC_1_SHIFT 7

/* FTDM_OUT13 (IC 1) */
#define R151_FTDM_OUT13_BYTE_OUT_POS_IC_1         0x0    /* 00b	[1:0] */
#define R151_FTDM_OUT13_CHANNEL_OUT_POS_IC_1      0x0    /* 000b	[4:2] */
#define R151_FTDM_OUT13_SERIAL_OUT_SEL_IC_1       0x0    /* 0b	[5] */
#define R151_FTDM_OUT13_REVERSE_OUT_BYTE_IC_1     0x0    /* 0b	[6] */
#define R151_FTDM_OUT13_SLOT_ENABLE_OUT_IC_1      0x0    /* 0b	[7] */
#define R151_FTDM_OUT13_BYTE_OUT_POS_IC_1_MASK    0x3
#define R151_FTDM_OUT13_BYTE_OUT_POS_IC_1_SHIFT   0
#define R151_FTDM_OUT13_CHANNEL_OUT_POS_IC_1_MASK 0x1C
#define R151_FTDM_OUT13_CHANNEL_OUT_POS_IC_1_SHIFT 2
#define R151_FTDM_OUT13_SERIAL_OUT_SEL_IC_1_MASK  0x20
#define R151_FTDM_OUT13_SERIAL_OUT_SEL_IC_1_SHIFT 5
#define R151_FTDM_OUT13_REVERSE_OUT_BYTE_IC_1_MASK 0x40
#define R151_FTDM_OUT13_REVERSE_OUT_BYTE_IC_1_SHIFT 6
#define R151_FTDM_OUT13_SLOT_ENABLE_OUT_IC_1_MASK 0x80
#define R151_FTDM_OUT13_SLOT_ENABLE_OUT_IC_1_SHIFT 7

/* FTDM_OUT14 (IC 1) */
#define R152_FTDM_OUT14_BYTE_OUT_POS_IC_1         0x0    /* 00b	[1:0] */
#define R152_FTDM_OUT14_CHANNEL_OUT_POS_IC_1      0x0    /* 000b	[4:2] */
#define R152_FTDM_OUT14_SERIAL_OUT_SEL_IC_1       0x0    /* 0b	[5] */
#define R152_FTDM_OUT14_REVERSE_OUT_BYTE_IC_1     0x0    /* 0b	[6] */
#define R152_FTDM_OUT14_SLOT_ENABLE_OUT_IC_1      0x0    /* 0b	[7] */
#define R152_FTDM_OUT14_BYTE_OUT_POS_IC_1_MASK    0x3
#define R152_FTDM_OUT14_BYTE_OUT_POS_IC_1_SHIFT   0
#define R152_FTDM_OUT14_CHANNEL_OUT_POS_IC_1_MASK 0x1C
#define R152_FTDM_OUT14_CHANNEL_OUT_POS_IC_1_SHIFT 2
#define R152_FTDM_OUT14_SERIAL_OUT_SEL_IC_1_MASK  0x20
#define R152_FTDM_OUT14_SERIAL_OUT_SEL_IC_1_SHIFT 5
#define R152_FTDM_OUT14_REVERSE_OUT_BYTE_IC_1_MASK 0x40
#define R152_FTDM_OUT14_REVERSE_OUT_BYTE_IC_1_SHIFT 6
#define R152_FTDM_OUT14_SLOT_ENABLE_OUT_IC_1_MASK 0x80
#define R152_FTDM_OUT14_SLOT_ENABLE_OUT_IC_1_SHIFT 7

/* FTDM_OUT15 (IC 1) */
#define R153_FTDM_OUT15_BYTE_OUT_POS_IC_1         0x0    /* 00b	[1:0] */
#define R153_FTDM_OUT15_CHANNEL_OUT_POS_IC_1      0x0    /* 000b	[4:2] */
#define R153_FTDM_OUT15_SERIAL_OUT_SEL_IC_1       0x0    /* 0b	[5] */
#define R153_FTDM_OUT15_REVERSE_OUT_BYTE_IC_1     0x0    /* 0b	[6] */
#define R153_FTDM_OUT15_SLOT_ENABLE_OUT_IC_1      0x0    /* 0b	[7] */
#define R153_FTDM_OUT15_BYTE_OUT_POS_IC_1_MASK    0x3
#define R153_FTDM_OUT15_BYTE_OUT_POS_IC_1_SHIFT   0
#define R153_FTDM_OUT15_CHANNEL_OUT_POS_IC_1_MASK 0x1C
#define R153_FTDM_OUT15_CHANNEL_OUT_POS_IC_1_SHIFT 2
#define R153_FTDM_OUT15_SERIAL_OUT_SEL_IC_1_MASK  0x20
#define R153_FTDM_OUT15_SERIAL_OUT_SEL_IC_1_SHIFT 5
#define R153_FTDM_OUT15_REVERSE_OUT_BYTE_IC_1_MASK 0x40
#define R153_FTDM_OUT15_REVERSE_OUT_BYTE_IC_1_SHIFT 6
#define R153_FTDM_OUT15_SLOT_ENABLE_OUT_IC_1_MASK 0x80
#define R153_FTDM_OUT15_SLOT_ENABLE_OUT_IC_1_SHIFT 7

/* FTDM_OUT16 (IC 1) */
#define R154_FTDM_OUT16_BYTE_OUT_POS_IC_1         0x0    /* 00b	[1:0] */
#define R154_FTDM_OUT16_CHANNEL_OUT_POS_IC_1      0x0    /* 000b	[4:2] */
#define R154_FTDM_OUT16_SERIAL_OUT_SEL_IC_1       0x0    /* 0b	[5] */
#define R154_FTDM_OUT16_REVERSE_OUT_BYTE_IC_1     0x0    /* 0b	[6] */
#define R154_FTDM_OUT16_SLOT_ENABLE_OUT_IC_1      0x0    /* 0b	[7] */
#define R154_FTDM_OUT16_BYTE_OUT_POS_IC_1_MASK    0x3
#define R154_FTDM_OUT16_BYTE_OUT_POS_IC_1_SHIFT   0
#define R154_FTDM_OUT16_CHANNEL_OUT_POS_IC_1_MASK 0x1C
#define R154_FTDM_OUT16_CHANNEL_OUT_POS_IC_1_SHIFT 2
#define R154_FTDM_OUT16_SERIAL_OUT_SEL_IC_1_MASK  0x20
#define R154_FTDM_OUT16_SERIAL_OUT_SEL_IC_1_SHIFT 5
#define R154_FTDM_OUT16_REVERSE_OUT_BYTE_IC_1_MASK 0x40
#define R154_FTDM_OUT16_REVERSE_OUT_BYTE_IC_1_SHIFT 6
#define R154_FTDM_OUT16_SLOT_ENABLE_OUT_IC_1_MASK 0x80
#define R154_FTDM_OUT16_SLOT_ENABLE_OUT_IC_1_SHIFT 7

/* FTDM_OUT17 (IC 1) */
#define R155_FTDM_OUT17_BYTE_OUT_POS_IC_1         0x0    /* 00b	[1:0] */
#define R155_FTDM_OUT17_CHANNEL_OUT_POS_IC_1      0x0    /* 000b	[4:2] */
#define R155_FTDM_OUT17_SERIAL_OUT_SEL_IC_1       0x0    /* 0b	[5] */
#define R155_FTDM_OUT17_REVERSE_OUT_BYTE_IC_1     0x0    /* 0b	[6] */
#define R155_FTDM_OUT17_SLOT_ENABLE_OUT_IC_1      0x0    /* 0b	[7] */
#define R155_FTDM_OUT17_BYTE_OUT_POS_IC_1_MASK    0x3
#define R155_FTDM_OUT17_BYTE_OUT_POS_IC_1_SHIFT   0
#define R155_FTDM_OUT17_CHANNEL_OUT_POS_IC_1_MASK 0x1C
#define R155_FTDM_OUT17_CHANNEL_OUT_POS_IC_1_SHIFT 2
#define R155_FTDM_OUT17_SERIAL_OUT_SEL_IC_1_MASK  0x20
#define R155_FTDM_OUT17_SERIAL_OUT_SEL_IC_1_SHIFT 5
#define R155_FTDM_OUT17_REVERSE_OUT_BYTE_IC_1_MASK 0x40
#define R155_FTDM_OUT17_REVERSE_OUT_BYTE_IC_1_SHIFT 6
#define R155_FTDM_OUT17_SLOT_ENABLE_OUT_IC_1_MASK 0x80
#define R155_FTDM_OUT17_SLOT_ENABLE_OUT_IC_1_SHIFT 7

/* FTDM_OUT18 (IC 1) */
#define R156_FTDM_OUT18_BYTE_OUT_POS_IC_1         0x0    /* 00b	[1:0] */
#define R156_FTDM_OUT18_CHANNEL_OUT_POS_IC_1      0x0    /* 000b	[4:2] */
#define R156_FTDM_OUT18_SERIAL_OUT_SEL_IC_1       0x0    /* 0b	[5] */
#define R156_FTDM_OUT18_REVERSE_OUT_BYTE_IC_1     0x0    /* 0b	[6] */
#define R156_FTDM_OUT18_SLOT_ENABLE_OUT_IC_1      0x0    /* 0b	[7] */
#define R156_FTDM_OUT18_BYTE_OUT_POS_IC_1_MASK    0x3
#define R156_FTDM_OUT18_BYTE_OUT_POS_IC_1_SHIFT   0
#define R156_FTDM_OUT18_CHANNEL_OUT_POS_IC_1_MASK 0x1C
#define R156_FTDM_OUT18_CHANNEL_OUT_POS_IC_1_SHIFT 2
#define R156_FTDM_OUT18_SERIAL_OUT_SEL_IC_1_MASK  0x20
#define R156_FTDM_OUT18_SERIAL_OUT_SEL_IC_1_SHIFT 5
#define R156_FTDM_OUT18_REVERSE_OUT_BYTE_IC_1_MASK 0x40
#define R156_FTDM_OUT18_REVERSE_OUT_BYTE_IC_1_SHIFT 6
#define R156_FTDM_OUT18_SLOT_ENABLE_OUT_IC_1_MASK 0x80
#define R156_FTDM_OUT18_SLOT_ENABLE_OUT_IC_1_SHIFT 7

/* FTDM_OUT19 (IC 1) */
#define R157_FTDM_OUT19_BYTE_OUT_POS_IC_1         0x0    /* 00b	[1:0] */
#define R157_FTDM_OUT19_CHANNEL_OUT_POS_IC_1      0x0    /* 000b	[4:2] */
#define R157_FTDM_OUT19_SERIAL_OUT_SEL_IC_1       0x0    /* 0b	[5] */
#define R157_FTDM_OUT19_REVERSE_OUT_BYTE_IC_1     0x0    /* 0b	[6] */
#define R157_FTDM_OUT19_SLOT_ENABLE_OUT_IC_1      0x0    /* 0b	[7] */
#define R157_FTDM_OUT19_BYTE_OUT_POS_IC_1_MASK    0x3
#define R157_FTDM_OUT19_BYTE_OUT_POS_IC_1_SHIFT   0
#define R157_FTDM_OUT19_CHANNEL_OUT_POS_IC_1_MASK 0x1C
#define R157_FTDM_OUT19_CHANNEL_OUT_POS_IC_1_SHIFT 2
#define R157_FTDM_OUT19_SERIAL_OUT_SEL_IC_1_MASK  0x20
#define R157_FTDM_OUT19_SERIAL_OUT_SEL_IC_1_SHIFT 5
#define R157_FTDM_OUT19_REVERSE_OUT_BYTE_IC_1_MASK 0x40
#define R157_FTDM_OUT19_REVERSE_OUT_BYTE_IC_1_SHIFT 6
#define R157_FTDM_OUT19_SLOT_ENABLE_OUT_IC_1_MASK 0x80
#define R157_FTDM_OUT19_SLOT_ENABLE_OUT_IC_1_SHIFT 7

/* FTDM_OUT20 (IC 1) */
#define R158_FTDM_OUT20_BYTE_OUT_POS_IC_1         0x0    /* 00b	[1:0] */
#define R158_FTDM_OUT20_CHANNEL_OUT_POS_IC_1      0x0    /* 000b	[4:2] */
#define R158_FTDM_OUT20_SERIAL_OUT_SEL_IC_1       0x0    /* 0b	[5] */
#define R158_FTDM_OUT20_REVERSE_OUT_BYTE_IC_1     0x0    /* 0b	[6] */
#define R158_FTDM_OUT20_SLOT_ENABLE_OUT_IC_1      0x0    /* 0b	[7] */
#define R158_FTDM_OUT20_BYTE_OUT_POS_IC_1_MASK    0x3
#define R158_FTDM_OUT20_BYTE_OUT_POS_IC_1_SHIFT   0
#define R158_FTDM_OUT20_CHANNEL_OUT_POS_IC_1_MASK 0x1C
#define R158_FTDM_OUT20_CHANNEL_OUT_POS_IC_1_SHIFT 2
#define R158_FTDM_OUT20_SERIAL_OUT_SEL_IC_1_MASK  0x20
#define R158_FTDM_OUT20_SERIAL_OUT_SEL_IC_1_SHIFT 5
#define R158_FTDM_OUT20_REVERSE_OUT_BYTE_IC_1_MASK 0x40
#define R158_FTDM_OUT20_REVERSE_OUT_BYTE_IC_1_SHIFT 6
#define R158_FTDM_OUT20_SLOT_ENABLE_OUT_IC_1_MASK 0x80
#define R158_FTDM_OUT20_SLOT_ENABLE_OUT_IC_1_SHIFT 7

/* FTDM_OUT21 (IC 1) */
#define R159_FTDM_OUT21_BYTE_OUT_POS_IC_1         0x0    /* 00b	[1:0] */
#define R159_FTDM_OUT21_CHANNEL_OUT_POS_IC_1      0x0    /* 000b	[4:2] */
#define R159_FTDM_OUT21_SERIAL_OUT_SEL_IC_1       0x0    /* 0b	[5] */
#define R159_FTDM_OUT21_REVERSE_OUT_BYTE_IC_1     0x0    /* 0b	[6] */
#define R159_FTDM_OUT21_SLOT_ENABLE_OUT_IC_1      0x0    /* 0b	[7] */
#define R159_FTDM_OUT21_BYTE_OUT_POS_IC_1_MASK    0x3
#define R159_FTDM_OUT21_BYTE_OUT_POS_IC_1_SHIFT   0
#define R159_FTDM_OUT21_CHANNEL_OUT_POS_IC_1_MASK 0x1C
#define R159_FTDM_OUT21_CHANNEL_OUT_POS_IC_1_SHIFT 2
#define R159_FTDM_OUT21_SERIAL_OUT_SEL_IC_1_MASK  0x20
#define R159_FTDM_OUT21_SERIAL_OUT_SEL_IC_1_SHIFT 5
#define R159_FTDM_OUT21_REVERSE_OUT_BYTE_IC_1_MASK 0x40
#define R159_FTDM_OUT21_REVERSE_OUT_BYTE_IC_1_SHIFT 6
#define R159_FTDM_OUT21_SLOT_ENABLE_OUT_IC_1_MASK 0x80
#define R159_FTDM_OUT21_SLOT_ENABLE_OUT_IC_1_SHIFT 7

/* FTDM_OUT22 (IC 1) */
#define R160_FTDM_OUT22_BYTE_OUT_POS_IC_1         0x0    /* 00b	[1:0] */
#define R160_FTDM_OUT22_CHANNEL_OUT_POS_IC_1      0x0    /* 000b	[4:2] */
#define R160_FTDM_OUT22_SERIAL_OUT_SEL_IC_1       0x0    /* 0b	[5] */
#define R160_FTDM_OUT22_REVERSE_OUT_BYTE_IC_1     0x0    /* 0b	[6] */
#define R160_FTDM_OUT22_SLOT_ENABLE_OUT_IC_1      0x0    /* 0b	[7] */
#define R160_FTDM_OUT22_BYTE_OUT_POS_IC_1_MASK    0x3
#define R160_FTDM_OUT22_BYTE_OUT_POS_IC_1_SHIFT   0
#define R160_FTDM_OUT22_CHANNEL_OUT_POS_IC_1_MASK 0x1C
#define R160_FTDM_OUT22_CHANNEL_OUT_POS_IC_1_SHIFT 2
#define R160_FTDM_OUT22_SERIAL_OUT_SEL_IC_1_MASK  0x20
#define R160_FTDM_OUT22_SERIAL_OUT_SEL_IC_1_SHIFT 5
#define R160_FTDM_OUT22_REVERSE_OUT_BYTE_IC_1_MASK 0x40
#define R160_FTDM_OUT22_REVERSE_OUT_BYTE_IC_1_SHIFT 6
#define R160_FTDM_OUT22_SLOT_ENABLE_OUT_IC_1_MASK 0x80
#define R160_FTDM_OUT22_SLOT_ENABLE_OUT_IC_1_SHIFT 7

/* FTDM_OUT23 (IC 1) */
#define R161_FTDM_OUT23_BYTE_OUT_POS_IC_1         0x0    /* 00b	[1:0] */
#define R161_FTDM_OUT23_CHANNEL_OUT_POS_IC_1      0x0    /* 000b	[4:2] */
#define R161_FTDM_OUT23_SERIAL_OUT_SEL_IC_1       0x0    /* 0b	[5] */
#define R161_FTDM_OUT23_REVERSE_OUT_BYTE_IC_1     0x0    /* 0b	[6] */
#define R161_FTDM_OUT23_SLOT_ENABLE_OUT_IC_1      0x0    /* 0b	[7] */
#define R161_FTDM_OUT23_BYTE_OUT_POS_IC_1_MASK    0x3
#define R161_FTDM_OUT23_BYTE_OUT_POS_IC_1_SHIFT   0
#define R161_FTDM_OUT23_CHANNEL_OUT_POS_IC_1_MASK 0x1C
#define R161_FTDM_OUT23_CHANNEL_OUT_POS_IC_1_SHIFT 2
#define R161_FTDM_OUT23_SERIAL_OUT_SEL_IC_1_MASK  0x20
#define R161_FTDM_OUT23_SERIAL_OUT_SEL_IC_1_SHIFT 5
#define R161_FTDM_OUT23_REVERSE_OUT_BYTE_IC_1_MASK 0x40
#define R161_FTDM_OUT23_REVERSE_OUT_BYTE_IC_1_SHIFT 6
#define R161_FTDM_OUT23_SLOT_ENABLE_OUT_IC_1_MASK 0x80
#define R161_FTDM_OUT23_SLOT_ENABLE_OUT_IC_1_SHIFT 7

/* FTDM_OUT24 (IC 1) */
#define R162_FTDM_OUT24_BYTE_OUT_POS_IC_1         0x0    /* 00b	[1:0] */
#define R162_FTDM_OUT24_CHANNEL_OUT_POS_IC_1      0x0    /* 000b	[4:2] */
#define R162_FTDM_OUT24_SERIAL_OUT_SEL_IC_1       0x0    /* 0b	[5] */
#define R162_FTDM_OUT24_REVERSE_OUT_BYTE_IC_1     0x0    /* 0b	[6] */
#define R162_FTDM_OUT24_SLOT_ENABLE_OUT_IC_1      0x0    /* 0b	[7] */
#define R162_FTDM_OUT24_BYTE_OUT_POS_IC_1_MASK    0x3
#define R162_FTDM_OUT24_BYTE_OUT_POS_IC_1_SHIFT   0
#define R162_FTDM_OUT24_CHANNEL_OUT_POS_IC_1_MASK 0x1C
#define R162_FTDM_OUT24_CHANNEL_OUT_POS_IC_1_SHIFT 2
#define R162_FTDM_OUT24_SERIAL_OUT_SEL_IC_1_MASK  0x20
#define R162_FTDM_OUT24_SERIAL_OUT_SEL_IC_1_SHIFT 5
#define R162_FTDM_OUT24_REVERSE_OUT_BYTE_IC_1_MASK 0x40
#define R162_FTDM_OUT24_REVERSE_OUT_BYTE_IC_1_SHIFT 6
#define R162_FTDM_OUT24_SLOT_ENABLE_OUT_IC_1_MASK 0x80
#define R162_FTDM_OUT24_SLOT_ENABLE_OUT_IC_1_SHIFT 7

/* FTDM_OUT25 (IC 1) */
#define R163_FTDM_OUT25_BYTE_OUT_POS_IC_1         0x0    /* 00b	[1:0] */
#define R163_FTDM_OUT25_CHANNEL_OUT_POS_IC_1      0x0    /* 000b	[4:2] */
#define R163_FTDM_OUT25_SERIAL_OUT_SEL_IC_1       0x0    /* 0b	[5] */
#define R163_FTDM_OUT25_REVERSE_OUT_BYTE_IC_1     0x0    /* 0b	[6] */
#define R163_FTDM_OUT25_SLOT_ENABLE_OUT_IC_1      0x0    /* 0b	[7] */
#define R163_FTDM_OUT25_BYTE_OUT_POS_IC_1_MASK    0x3
#define R163_FTDM_OUT25_BYTE_OUT_POS_IC_1_SHIFT   0
#define R163_FTDM_OUT25_CHANNEL_OUT_POS_IC_1_MASK 0x1C
#define R163_FTDM_OUT25_CHANNEL_OUT_POS_IC_1_SHIFT 2
#define R163_FTDM_OUT25_SERIAL_OUT_SEL_IC_1_MASK  0x20
#define R163_FTDM_OUT25_SERIAL_OUT_SEL_IC_1_SHIFT 5
#define R163_FTDM_OUT25_REVERSE_OUT_BYTE_IC_1_MASK 0x40
#define R163_FTDM_OUT25_REVERSE_OUT_BYTE_IC_1_SHIFT 6
#define R163_FTDM_OUT25_SLOT_ENABLE_OUT_IC_1_MASK 0x80
#define R163_FTDM_OUT25_SLOT_ENABLE_OUT_IC_1_SHIFT 7

/* FTDM_OUT26 (IC 1) */
#define R164_FTDM_OUT26_BYTE_OUT_POS_IC_1         0x0    /* 00b	[1:0] */
#define R164_FTDM_OUT26_CHANNEL_OUT_POS_IC_1      0x0    /* 000b	[4:2] */
#define R164_FTDM_OUT26_SERIAL_OUT_SEL_IC_1       0x0    /* 0b	[5] */
#define R164_FTDM_OUT26_REVERSE_OUT_BYTE_IC_1     0x0    /* 0b	[6] */
#define R164_FTDM_OUT26_SLOT_ENABLE_OUT_IC_1      0x0    /* 0b	[7] */
#define R164_FTDM_OUT26_BYTE_OUT_POS_IC_1_MASK    0x3
#define R164_FTDM_OUT26_BYTE_OUT_POS_IC_1_SHIFT   0
#define R164_FTDM_OUT26_CHANNEL_OUT_POS_IC_1_MASK 0x1C
#define R164_FTDM_OUT26_CHANNEL_OUT_POS_IC_1_SHIFT 2
#define R164_FTDM_OUT26_SERIAL_OUT_SEL_IC_1_MASK  0x20
#define R164_FTDM_OUT26_SERIAL_OUT_SEL_IC_1_SHIFT 5
#define R164_FTDM_OUT26_REVERSE_OUT_BYTE_IC_1_MASK 0x40
#define R164_FTDM_OUT26_REVERSE_OUT_BYTE_IC_1_SHIFT 6
#define R164_FTDM_OUT26_SLOT_ENABLE_OUT_IC_1_MASK 0x80
#define R164_FTDM_OUT26_SLOT_ENABLE_OUT_IC_1_SHIFT 7

/* FTDM_OUT27 (IC 1) */
#define R165_FTDM_OUT27_BYTE_OUT_POS_IC_1         0x0    /* 00b	[1:0] */
#define R165_FTDM_OUT27_CHANNEL_OUT_POS_IC_1      0x0    /* 000b	[4:2] */
#define R165_FTDM_OUT27_SERIAL_OUT_SEL_IC_1       0x0    /* 0b	[5] */
#define R165_FTDM_OUT27_REVERSE_OUT_BYTE_IC_1     0x0    /* 0b	[6] */
#define R165_FTDM_OUT27_SLOT_ENABLE_OUT_IC_1      0x0    /* 0b	[7] */
#define R165_FTDM_OUT27_BYTE_OUT_POS_IC_1_MASK    0x3
#define R165_FTDM_OUT27_BYTE_OUT_POS_IC_1_SHIFT   0
#define R165_FTDM_OUT27_CHANNEL_OUT_POS_IC_1_MASK 0x1C
#define R165_FTDM_OUT27_CHANNEL_OUT_POS_IC_1_SHIFT 2
#define R165_FTDM_OUT27_SERIAL_OUT_SEL_IC_1_MASK  0x20
#define R165_FTDM_OUT27_SERIAL_OUT_SEL_IC_1_SHIFT 5
#define R165_FTDM_OUT27_REVERSE_OUT_BYTE_IC_1_MASK 0x40
#define R165_FTDM_OUT27_REVERSE_OUT_BYTE_IC_1_SHIFT 6
#define R165_FTDM_OUT27_SLOT_ENABLE_OUT_IC_1_MASK 0x80
#define R165_FTDM_OUT27_SLOT_ENABLE_OUT_IC_1_SHIFT 7

/* FTDM_OUT28 (IC 1) */
#define R166_FTDM_OUT28_BYTE_OUT_POS_IC_1         0x0    /* 00b	[1:0] */
#define R166_FTDM_OUT28_CHANNEL_OUT_POS_IC_1      0x0    /* 000b	[4:2] */
#define R166_FTDM_OUT28_SERIAL_OUT_SEL_IC_1       0x0    /* 0b	[5] */
#define R166_FTDM_OUT28_REVERSE_OUT_BYTE_IC_1     0x0    /* 0b	[6] */
#define R166_FTDM_OUT28_SLOT_ENABLE_OUT_IC_1      0x0    /* 0b	[7] */
#define R166_FTDM_OUT28_BYTE_OUT_POS_IC_1_MASK    0x3
#define R166_FTDM_OUT28_BYTE_OUT_POS_IC_1_SHIFT   0
#define R166_FTDM_OUT28_CHANNEL_OUT_POS_IC_1_MASK 0x1C
#define R166_FTDM_OUT28_CHANNEL_OUT_POS_IC_1_SHIFT 2
#define R166_FTDM_OUT28_SERIAL_OUT_SEL_IC_1_MASK  0x20
#define R166_FTDM_OUT28_SERIAL_OUT_SEL_IC_1_SHIFT 5
#define R166_FTDM_OUT28_REVERSE_OUT_BYTE_IC_1_MASK 0x40
#define R166_FTDM_OUT28_REVERSE_OUT_BYTE_IC_1_SHIFT 6
#define R166_FTDM_OUT28_SLOT_ENABLE_OUT_IC_1_MASK 0x80
#define R166_FTDM_OUT28_SLOT_ENABLE_OUT_IC_1_SHIFT 7

/* FTDM_OUT29 (IC 1) */
#define R167_FTDM_OUT29_BYTE_OUT_POS_IC_1         0x0    /* 00b	[1:0] */
#define R167_FTDM_OUT29_CHANNEL_OUT_POS_IC_1      0x0    /* 000b	[4:2] */
#define R167_FTDM_OUT29_SERIAL_OUT_SEL_IC_1       0x0    /* 0b	[5] */
#define R167_FTDM_OUT29_REVERSE_OUT_BYTE_IC_1     0x0    /* 0b	[6] */
#define R167_FTDM_OUT29_SLOT_ENABLE_OUT_IC_1      0x0    /* 0b	[7] */
#define R167_FTDM_OUT29_BYTE_OUT_POS_IC_1_MASK    0x3
#define R167_FTDM_OUT29_BYTE_OUT_POS_IC_1_SHIFT   0
#define R167_FTDM_OUT29_CHANNEL_OUT_POS_IC_1_MASK 0x1C
#define R167_FTDM_OUT29_CHANNEL_OUT_POS_IC_1_SHIFT 2
#define R167_FTDM_OUT29_SERIAL_OUT_SEL_IC_1_MASK  0x20
#define R167_FTDM_OUT29_SERIAL_OUT_SEL_IC_1_SHIFT 5
#define R167_FTDM_OUT29_REVERSE_OUT_BYTE_IC_1_MASK 0x40
#define R167_FTDM_OUT29_REVERSE_OUT_BYTE_IC_1_SHIFT 6
#define R167_FTDM_OUT29_SLOT_ENABLE_OUT_IC_1_MASK 0x80
#define R167_FTDM_OUT29_SLOT_ENABLE_OUT_IC_1_SHIFT 7

/* FTDM_OUT30 (IC 1) */
#define R168_FTDM_OUT30_BYTE_OUT_POS_IC_1         0x0    /* 00b	[1:0] */
#define R168_FTDM_OUT30_CHANNEL_OUT_POS_IC_1      0x0    /* 000b	[4:2] */
#define R168_FTDM_OUT30_SERIAL_OUT_SEL_IC_1       0x0    /* 0b	[5] */
#define R168_FTDM_OUT30_REVERSE_OUT_BYTE_IC_1     0x0    /* 0b	[6] */
#define R168_FTDM_OUT30_SLOT_ENABLE_OUT_IC_1      0x0    /* 0b	[7] */
#define R168_FTDM_OUT30_BYTE_OUT_POS_IC_1_MASK    0x3
#define R168_FTDM_OUT30_BYTE_OUT_POS_IC_1_SHIFT   0
#define R168_FTDM_OUT30_CHANNEL_OUT_POS_IC_1_MASK 0x1C
#define R168_FTDM_OUT30_CHANNEL_OUT_POS_IC_1_SHIFT 2
#define R168_FTDM_OUT30_SERIAL_OUT_SEL_IC_1_MASK  0x20
#define R168_FTDM_OUT30_SERIAL_OUT_SEL_IC_1_SHIFT 5
#define R168_FTDM_OUT30_REVERSE_OUT_BYTE_IC_1_MASK 0x40
#define R168_FTDM_OUT30_REVERSE_OUT_BYTE_IC_1_SHIFT 6
#define R168_FTDM_OUT30_SLOT_ENABLE_OUT_IC_1_MASK 0x80
#define R168_FTDM_OUT30_SLOT_ENABLE_OUT_IC_1_SHIFT 7

/* FTDM_OUT31 (IC 1) */
#define R169_FTDM_OUT31_BYTE_OUT_POS_IC_1         0x0    /* 00b	[1:0] */
#define R169_FTDM_OUT31_CHANNEL_OUT_POS_IC_1      0x0    /* 000b	[4:2] */
#define R169_FTDM_OUT31_SERIAL_OUT_SEL_IC_1       0x0    /* 0b	[5] */
#define R169_FTDM_OUT31_REVERSE_OUT_BYTE_IC_1     0x0    /* 0b	[6] */
#define R169_FTDM_OUT31_SLOT_ENABLE_OUT_IC_1      0x0    /* 0b	[7] */
#define R169_FTDM_OUT31_BYTE_OUT_POS_IC_1_MASK    0x3
#define R169_FTDM_OUT31_BYTE_OUT_POS_IC_1_SHIFT   0
#define R169_FTDM_OUT31_CHANNEL_OUT_POS_IC_1_MASK 0x1C
#define R169_FTDM_OUT31_CHANNEL_OUT_POS_IC_1_SHIFT 2
#define R169_FTDM_OUT31_SERIAL_OUT_SEL_IC_1_MASK  0x20
#define R169_FTDM_OUT31_SERIAL_OUT_SEL_IC_1_SHIFT 5
#define R169_FTDM_OUT31_REVERSE_OUT_BYTE_IC_1_MASK 0x40
#define R169_FTDM_OUT31_REVERSE_OUT_BYTE_IC_1_SHIFT 6
#define R169_FTDM_OUT31_SLOT_ENABLE_OUT_IC_1_MASK 0x80
#define R169_FTDM_OUT31_SLOT_ENABLE_OUT_IC_1_SHIFT 7

/* FTDM_OUT32 (IC 1) */
#define R170_FTDM_OUT32_BYTE_OUT_POS_IC_1         0x0    /* 00b	[1:0] */
#define R170_FTDM_OUT32_CHANNEL_OUT_POS_IC_1      0x0    /* 000b	[4:2] */
#define R170_FTDM_OUT32_SERIAL_OUT_SEL_IC_1       0x0    /* 0b	[5] */
#define R170_FTDM_OUT32_REVERSE_OUT_BYTE_IC_1     0x0    /* 0b	[6] */
#define R170_FTDM_OUT32_SLOT_ENABLE_OUT_IC_1      0x0    /* 0b	[7] */
#define R170_FTDM_OUT32_BYTE_OUT_POS_IC_1_MASK    0x3
#define R170_FTDM_OUT32_BYTE_OUT_POS_IC_1_SHIFT   0
#define R170_FTDM_OUT32_CHANNEL_OUT_POS_IC_1_MASK 0x1C
#define R170_FTDM_OUT32_CHANNEL_OUT_POS_IC_1_SHIFT 2
#define R170_FTDM_OUT32_SERIAL_OUT_SEL_IC_1_MASK  0x20
#define R170_FTDM_OUT32_SERIAL_OUT_SEL_IC_1_SHIFT 5
#define R170_FTDM_OUT32_REVERSE_OUT_BYTE_IC_1_MASK 0x40
#define R170_FTDM_OUT32_REVERSE_OUT_BYTE_IC_1_SHIFT 6
#define R170_FTDM_OUT32_SLOT_ENABLE_OUT_IC_1_MASK 0x80
#define R170_FTDM_OUT32_SLOT_ENABLE_OUT_IC_1_SHIFT 7

/* FTDM_OUT33 (IC 1) */
#define R171_FTDM_OUT33_BYTE_OUT_POS_IC_1         0x0    /* 00b	[1:0] */
#define R171_FTDM_OUT33_CHANNEL_OUT_POS_IC_1      0x0    /* 000b	[4:2] */
#define R171_FTDM_OUT33_SERIAL_OUT_SEL_IC_1       0x0    /* 0b	[5] */
#define R171_FTDM_OUT33_REVERSE_OUT_BYTE_IC_1     0x0    /* 0b	[6] */
#define R171_FTDM_OUT33_SLOT_ENABLE_OUT_IC_1      0x0    /* 0b	[7] */
#define R171_FTDM_OUT33_BYTE_OUT_POS_IC_1_MASK    0x3
#define R171_FTDM_OUT33_BYTE_OUT_POS_IC_1_SHIFT   0
#define R171_FTDM_OUT33_CHANNEL_OUT_POS_IC_1_MASK 0x1C
#define R171_FTDM_OUT33_CHANNEL_OUT_POS_IC_1_SHIFT 2
#define R171_FTDM_OUT33_SERIAL_OUT_SEL_IC_1_MASK  0x20
#define R171_FTDM_OUT33_SERIAL_OUT_SEL_IC_1_SHIFT 5
#define R171_FTDM_OUT33_REVERSE_OUT_BYTE_IC_1_MASK 0x40
#define R171_FTDM_OUT33_REVERSE_OUT_BYTE_IC_1_SHIFT 6
#define R171_FTDM_OUT33_SLOT_ENABLE_OUT_IC_1_MASK 0x80
#define R171_FTDM_OUT33_SLOT_ENABLE_OUT_IC_1_SHIFT 7

/* FTDM_OUT34 (IC 1) */
#define R172_FTDM_OUT34_BYTE_OUT_POS_IC_1         0x0    /* 00b	[1:0] */
#define R172_FTDM_OUT34_CHANNEL_OUT_POS_IC_1      0x0    /* 000b	[4:2] */
#define R172_FTDM_OUT34_SERIAL_OUT_SEL_IC_1       0x0    /* 0b	[5] */
#define R172_FTDM_OUT34_REVERSE_OUT_BYTE_IC_1     0x0    /* 0b	[6] */
#define R172_FTDM_OUT34_SLOT_ENABLE_OUT_IC_1      0x0    /* 0b	[7] */
#define R172_FTDM_OUT34_BYTE_OUT_POS_IC_1_MASK    0x3
#define R172_FTDM_OUT34_BYTE_OUT_POS_IC_1_SHIFT   0
#define R172_FTDM_OUT34_CHANNEL_OUT_POS_IC_1_MASK 0x1C
#define R172_FTDM_OUT34_CHANNEL_OUT_POS_IC_1_SHIFT 2
#define R172_FTDM_OUT34_SERIAL_OUT_SEL_IC_1_MASK  0x20
#define R172_FTDM_OUT34_SERIAL_OUT_SEL_IC_1_SHIFT 5
#define R172_FTDM_OUT34_REVERSE_OUT_BYTE_IC_1_MASK 0x40
#define R172_FTDM_OUT34_REVERSE_OUT_BYTE_IC_1_SHIFT 6
#define R172_FTDM_OUT34_SLOT_ENABLE_OUT_IC_1_MASK 0x80
#define R172_FTDM_OUT34_SLOT_ENABLE_OUT_IC_1_SHIFT 7

/* FTDM_OUT35 (IC 1) */
#define R173_FTDM_OUT35_BYTE_OUT_POS_IC_1         0x0    /* 00b	[1:0] */
#define R173_FTDM_OUT35_CHANNEL_OUT_POS_IC_1      0x0    /* 000b	[4:2] */
#define R173_FTDM_OUT35_SERIAL_OUT_SEL_IC_1       0x0    /* 0b	[5] */
#define R173_FTDM_OUT35_REVERSE_OUT_BYTE_IC_1     0x0    /* 0b	[6] */
#define R173_FTDM_OUT35_SLOT_ENABLE_OUT_IC_1      0x0    /* 0b	[7] */
#define R173_FTDM_OUT35_BYTE_OUT_POS_IC_1_MASK    0x3
#define R173_FTDM_OUT35_BYTE_OUT_POS_IC_1_SHIFT   0
#define R173_FTDM_OUT35_CHANNEL_OUT_POS_IC_1_MASK 0x1C
#define R173_FTDM_OUT35_CHANNEL_OUT_POS_IC_1_SHIFT 2
#define R173_FTDM_OUT35_SERIAL_OUT_SEL_IC_1_MASK  0x20
#define R173_FTDM_OUT35_SERIAL_OUT_SEL_IC_1_SHIFT 5
#define R173_FTDM_OUT35_REVERSE_OUT_BYTE_IC_1_MASK 0x40
#define R173_FTDM_OUT35_REVERSE_OUT_BYTE_IC_1_SHIFT 6
#define R173_FTDM_OUT35_SLOT_ENABLE_OUT_IC_1_MASK 0x80
#define R173_FTDM_OUT35_SLOT_ENABLE_OUT_IC_1_SHIFT 7

/* FTDM_OUT36 (IC 1) */
#define R174_FTDM_OUT36_BYTE_OUT_POS_IC_1         0x0    /* 00b	[1:0] */
#define R174_FTDM_OUT36_CHANNEL_OUT_POS_IC_1      0x0    /* 000b	[4:2] */
#define R174_FTDM_OUT36_SERIAL_OUT_SEL_IC_1       0x0    /* 0b	[5] */
#define R174_FTDM_OUT36_REVERSE_OUT_BYTE_IC_1     0x0    /* 0b	[6] */
#define R174_FTDM_OUT36_SLOT_ENABLE_OUT_IC_1      0x0    /* 0b	[7] */
#define R174_FTDM_OUT36_BYTE_OUT_POS_IC_1_MASK    0x3
#define R174_FTDM_OUT36_BYTE_OUT_POS_IC_1_SHIFT   0
#define R174_FTDM_OUT36_CHANNEL_OUT_POS_IC_1_MASK 0x1C
#define R174_FTDM_OUT36_CHANNEL_OUT_POS_IC_1_SHIFT 2
#define R174_FTDM_OUT36_SERIAL_OUT_SEL_IC_1_MASK  0x20
#define R174_FTDM_OUT36_SERIAL_OUT_SEL_IC_1_SHIFT 5
#define R174_FTDM_OUT36_REVERSE_OUT_BYTE_IC_1_MASK 0x40
#define R174_FTDM_OUT36_REVERSE_OUT_BYTE_IC_1_SHIFT 6
#define R174_FTDM_OUT36_SLOT_ENABLE_OUT_IC_1_MASK 0x80
#define R174_FTDM_OUT36_SLOT_ENABLE_OUT_IC_1_SHIFT 7

/* FTDM_OUT37 (IC 1) */
#define R175_FTDM_OUT37_BYTE_OUT_POS_IC_1         0x0    /* 00b	[1:0] */
#define R175_FTDM_OUT37_CHANNEL_OUT_POS_IC_1      0x0    /* 000b	[4:2] */
#define R175_FTDM_OUT37_SERIAL_OUT_SEL_IC_1       0x0    /* 0b	[5] */
#define R175_FTDM_OUT37_REVERSE_OUT_BYTE_IC_1     0x0    /* 0b	[6] */
#define R175_FTDM_OUT37_SLOT_ENABLE_OUT_IC_1      0x0    /* 0b	[7] */
#define R175_FTDM_OUT37_BYTE_OUT_POS_IC_1_MASK    0x3
#define R175_FTDM_OUT37_BYTE_OUT_POS_IC_1_SHIFT   0
#define R175_FTDM_OUT37_CHANNEL_OUT_POS_IC_1_MASK 0x1C
#define R175_FTDM_OUT37_CHANNEL_OUT_POS_IC_1_SHIFT 2
#define R175_FTDM_OUT37_SERIAL_OUT_SEL_IC_1_MASK  0x20
#define R175_FTDM_OUT37_SERIAL_OUT_SEL_IC_1_SHIFT 5
#define R175_FTDM_OUT37_REVERSE_OUT_BYTE_IC_1_MASK 0x40
#define R175_FTDM_OUT37_REVERSE_OUT_BYTE_IC_1_SHIFT 6
#define R175_FTDM_OUT37_SLOT_ENABLE_OUT_IC_1_MASK 0x80
#define R175_FTDM_OUT37_SLOT_ENABLE_OUT_IC_1_SHIFT 7

/* FTDM_OUT38 (IC 1) */
#define R176_FTDM_OUT38_BYTE_OUT_POS_IC_1         0x0    /* 00b	[1:0] */
#define R176_FTDM_OUT38_CHANNEL_OUT_POS_IC_1      0x0    /* 000b	[4:2] */
#define R176_FTDM_OUT38_SERIAL_OUT_SEL_IC_1       0x0    /* 0b	[5] */
#define R176_FTDM_OUT38_REVERSE_OUT_BYTE_IC_1     0x0    /* 0b	[6] */
#define R176_FTDM_OUT38_SLOT_ENABLE_OUT_IC_1      0x0    /* 0b	[7] */
#define R176_FTDM_OUT38_BYTE_OUT_POS_IC_1_MASK    0x3
#define R176_FTDM_OUT38_BYTE_OUT_POS_IC_1_SHIFT   0
#define R176_FTDM_OUT38_CHANNEL_OUT_POS_IC_1_MASK 0x1C
#define R176_FTDM_OUT38_CHANNEL_OUT_POS_IC_1_SHIFT 2
#define R176_FTDM_OUT38_SERIAL_OUT_SEL_IC_1_MASK  0x20
#define R176_FTDM_OUT38_SERIAL_OUT_SEL_IC_1_SHIFT 5
#define R176_FTDM_OUT38_REVERSE_OUT_BYTE_IC_1_MASK 0x40
#define R176_FTDM_OUT38_REVERSE_OUT_BYTE_IC_1_SHIFT 6
#define R176_FTDM_OUT38_SLOT_ENABLE_OUT_IC_1_MASK 0x80
#define R176_FTDM_OUT38_SLOT_ENABLE_OUT_IC_1_SHIFT 7

/* FTDM_OUT39 (IC 1) */
#define R177_FTDM_OUT39_BYTE_OUT_POS_IC_1         0x0    /* 00b	[1:0] */
#define R177_FTDM_OUT39_CHANNEL_OUT_POS_IC_1      0x0    /* 000b	[4:2] */
#define R177_FTDM_OUT39_SERIAL_OUT_SEL_IC_1       0x0    /* 0b	[5] */
#define R177_FTDM_OUT39_REVERSE_OUT_BYTE_IC_1     0x0    /* 0b	[6] */
#define R177_FTDM_OUT39_SLOT_ENABLE_OUT_IC_1      0x0    /* 0b	[7] */
#define R177_FTDM_OUT39_BYTE_OUT_POS_IC_1_MASK    0x3
#define R177_FTDM_OUT39_BYTE_OUT_POS_IC_1_SHIFT   0
#define R177_FTDM_OUT39_CHANNEL_OUT_POS_IC_1_MASK 0x1C
#define R177_FTDM_OUT39_CHANNEL_OUT_POS_IC_1_SHIFT 2
#define R177_FTDM_OUT39_SERIAL_OUT_SEL_IC_1_MASK  0x20
#define R177_FTDM_OUT39_SERIAL_OUT_SEL_IC_1_SHIFT 5
#define R177_FTDM_OUT39_REVERSE_OUT_BYTE_IC_1_MASK 0x40
#define R177_FTDM_OUT39_REVERSE_OUT_BYTE_IC_1_SHIFT 6
#define R177_FTDM_OUT39_SLOT_ENABLE_OUT_IC_1_MASK 0x80
#define R177_FTDM_OUT39_SLOT_ENABLE_OUT_IC_1_SHIFT 7

/* FTDM_OUT40 (IC 1) */
#define R178_FTDM_OUT40_BYTE_OUT_POS_IC_1         0x0    /* 00b	[1:0] */
#define R178_FTDM_OUT40_CHANNEL_OUT_POS_IC_1      0x0    /* 000b	[4:2] */
#define R178_FTDM_OUT40_SERIAL_OUT_SEL_IC_1       0x0    /* 0b	[5] */
#define R178_FTDM_OUT40_REVERSE_OUT_BYTE_IC_1     0x0    /* 0b	[6] */
#define R178_FTDM_OUT40_SLOT_ENABLE_OUT_IC_1      0x0    /* 0b	[7] */
#define R178_FTDM_OUT40_BYTE_OUT_POS_IC_1_MASK    0x3
#define R178_FTDM_OUT40_BYTE_OUT_POS_IC_1_SHIFT   0
#define R178_FTDM_OUT40_CHANNEL_OUT_POS_IC_1_MASK 0x1C
#define R178_FTDM_OUT40_CHANNEL_OUT_POS_IC_1_SHIFT 2
#define R178_FTDM_OUT40_SERIAL_OUT_SEL_IC_1_MASK  0x20
#define R178_FTDM_OUT40_SERIAL_OUT_SEL_IC_1_SHIFT 5
#define R178_FTDM_OUT40_REVERSE_OUT_BYTE_IC_1_MASK 0x40
#define R178_FTDM_OUT40_REVERSE_OUT_BYTE_IC_1_SHIFT 6
#define R178_FTDM_OUT40_SLOT_ENABLE_OUT_IC_1_MASK 0x80
#define R178_FTDM_OUT40_SLOT_ENABLE_OUT_IC_1_SHIFT 7

/* FTDM_OUT41 (IC 1) */
#define R179_FTDM_OUT41_BYTE_OUT_POS_IC_1         0x0    /* 00b	[1:0] */
#define R179_FTDM_OUT41_CHANNEL_OUT_POS_IC_1      0x0    /* 000b	[4:2] */
#define R179_FTDM_OUT41_SERIAL_OUT_SEL_IC_1       0x0    /* 0b	[5] */
#define R179_FTDM_OUT41_REVERSE_OUT_BYTE_IC_1     0x0    /* 0b	[6] */
#define R179_FTDM_OUT41_SLOT_ENABLE_OUT_IC_1      0x0    /* 0b	[7] */
#define R179_FTDM_OUT41_BYTE_OUT_POS_IC_1_MASK    0x3
#define R179_FTDM_OUT41_BYTE_OUT_POS_IC_1_SHIFT   0
#define R179_FTDM_OUT41_CHANNEL_OUT_POS_IC_1_MASK 0x1C
#define R179_FTDM_OUT41_CHANNEL_OUT_POS_IC_1_SHIFT 2
#define R179_FTDM_OUT41_SERIAL_OUT_SEL_IC_1_MASK  0x20
#define R179_FTDM_OUT41_SERIAL_OUT_SEL_IC_1_SHIFT 5
#define R179_FTDM_OUT41_REVERSE_OUT_BYTE_IC_1_MASK 0x40
#define R179_FTDM_OUT41_REVERSE_OUT_BYTE_IC_1_SHIFT 6
#define R179_FTDM_OUT41_SLOT_ENABLE_OUT_IC_1_MASK 0x80
#define R179_FTDM_OUT41_SLOT_ENABLE_OUT_IC_1_SHIFT 7

/* FTDM_OUT42 (IC 1) */
#define R180_FTDM_OUT42_BYTE_OUT_POS_IC_1         0x0    /* 00b	[1:0] */
#define R180_FTDM_OUT42_CHANNEL_OUT_POS_IC_1      0x0    /* 000b	[4:2] */
#define R180_FTDM_OUT42_SERIAL_OUT_SEL_IC_1       0x0    /* 0b	[5] */
#define R180_FTDM_OUT42_REVERSE_OUT_BYTE_IC_1     0x0    /* 0b	[6] */
#define R180_FTDM_OUT42_SLOT_ENABLE_OUT_IC_1      0x0    /* 0b	[7] */
#define R180_FTDM_OUT42_BYTE_OUT_POS_IC_1_MASK    0x3
#define R180_FTDM_OUT42_BYTE_OUT_POS_IC_1_SHIFT   0
#define R180_FTDM_OUT42_CHANNEL_OUT_POS_IC_1_MASK 0x1C
#define R180_FTDM_OUT42_CHANNEL_OUT_POS_IC_1_SHIFT 2
#define R180_FTDM_OUT42_SERIAL_OUT_SEL_IC_1_MASK  0x20
#define R180_FTDM_OUT42_SERIAL_OUT_SEL_IC_1_SHIFT 5
#define R180_FTDM_OUT42_REVERSE_OUT_BYTE_IC_1_MASK 0x40
#define R180_FTDM_OUT42_REVERSE_OUT_BYTE_IC_1_SHIFT 6
#define R180_FTDM_OUT42_SLOT_ENABLE_OUT_IC_1_MASK 0x80
#define R180_FTDM_OUT42_SLOT_ENABLE_OUT_IC_1_SHIFT 7

/* FTDM_OUT43 (IC 1) */
#define R181_FTDM_OUT43_BYTE_OUT_POS_IC_1         0x0    /* 00b	[1:0] */
#define R181_FTDM_OUT43_CHANNEL_OUT_POS_IC_1      0x0    /* 000b	[4:2] */
#define R181_FTDM_OUT43_SERIAL_OUT_SEL_IC_1       0x0    /* 0b	[5] */
#define R181_FTDM_OUT43_REVERSE_OUT_BYTE_IC_1     0x0    /* 0b	[6] */
#define R181_FTDM_OUT43_SLOT_ENABLE_OUT_IC_1      0x0    /* 0b	[7] */
#define R181_FTDM_OUT43_BYTE_OUT_POS_IC_1_MASK    0x3
#define R181_FTDM_OUT43_BYTE_OUT_POS_IC_1_SHIFT   0
#define R181_FTDM_OUT43_CHANNEL_OUT_POS_IC_1_MASK 0x1C
#define R181_FTDM_OUT43_CHANNEL_OUT_POS_IC_1_SHIFT 2
#define R181_FTDM_OUT43_SERIAL_OUT_SEL_IC_1_MASK  0x20
#define R181_FTDM_OUT43_SERIAL_OUT_SEL_IC_1_SHIFT 5
#define R181_FTDM_OUT43_REVERSE_OUT_BYTE_IC_1_MASK 0x40
#define R181_FTDM_OUT43_REVERSE_OUT_BYTE_IC_1_SHIFT 6
#define R181_FTDM_OUT43_SLOT_ENABLE_OUT_IC_1_MASK 0x80
#define R181_FTDM_OUT43_SLOT_ENABLE_OUT_IC_1_SHIFT 7

/* FTDM_OUT44 (IC 1) */
#define R182_FTDM_OUT44_BYTE_OUT_POS_IC_1         0x0    /* 00b	[1:0] */
#define R182_FTDM_OUT44_CHANNEL_OUT_POS_IC_1      0x0    /* 000b	[4:2] */
#define R182_FTDM_OUT44_SERIAL_OUT_SEL_IC_1       0x0    /* 0b	[5] */
#define R182_FTDM_OUT44_REVERSE_OUT_BYTE_IC_1     0x0    /* 0b	[6] */
#define R182_FTDM_OUT44_SLOT_ENABLE_OUT_IC_1      0x0    /* 0b	[7] */
#define R182_FTDM_OUT44_BYTE_OUT_POS_IC_1_MASK    0x3
#define R182_FTDM_OUT44_BYTE_OUT_POS_IC_1_SHIFT   0
#define R182_FTDM_OUT44_CHANNEL_OUT_POS_IC_1_MASK 0x1C
#define R182_FTDM_OUT44_CHANNEL_OUT_POS_IC_1_SHIFT 2
#define R182_FTDM_OUT44_SERIAL_OUT_SEL_IC_1_MASK  0x20
#define R182_FTDM_OUT44_SERIAL_OUT_SEL_IC_1_SHIFT 5
#define R182_FTDM_OUT44_REVERSE_OUT_BYTE_IC_1_MASK 0x40
#define R182_FTDM_OUT44_REVERSE_OUT_BYTE_IC_1_SHIFT 6
#define R182_FTDM_OUT44_SLOT_ENABLE_OUT_IC_1_MASK 0x80
#define R182_FTDM_OUT44_SLOT_ENABLE_OUT_IC_1_SHIFT 7

/* FTDM_OUT45 (IC 1) */
#define R183_FTDM_OUT45_BYTE_OUT_POS_IC_1         0x0    /* 00b	[1:0] */
#define R183_FTDM_OUT45_CHANNEL_OUT_POS_IC_1      0x0    /* 000b	[4:2] */
#define R183_FTDM_OUT45_SERIAL_OUT_SEL_IC_1       0x0    /* 0b	[5] */
#define R183_FTDM_OUT45_REVERSE_OUT_BYTE_IC_1     0x0    /* 0b	[6] */
#define R183_FTDM_OUT45_SLOT_ENABLE_OUT_IC_1      0x0    /* 0b	[7] */
#define R183_FTDM_OUT45_BYTE_OUT_POS_IC_1_MASK    0x3
#define R183_FTDM_OUT45_BYTE_OUT_POS_IC_1_SHIFT   0
#define R183_FTDM_OUT45_CHANNEL_OUT_POS_IC_1_MASK 0x1C
#define R183_FTDM_OUT45_CHANNEL_OUT_POS_IC_1_SHIFT 2
#define R183_FTDM_OUT45_SERIAL_OUT_SEL_IC_1_MASK  0x20
#define R183_FTDM_OUT45_SERIAL_OUT_SEL_IC_1_SHIFT 5
#define R183_FTDM_OUT45_REVERSE_OUT_BYTE_IC_1_MASK 0x40
#define R183_FTDM_OUT45_REVERSE_OUT_BYTE_IC_1_SHIFT 6
#define R183_FTDM_OUT45_SLOT_ENABLE_OUT_IC_1_MASK 0x80
#define R183_FTDM_OUT45_SLOT_ENABLE_OUT_IC_1_SHIFT 7

/* FTDM_OUT46 (IC 1) */
#define R184_FTDM_OUT46_BYTE_OUT_POS_IC_1         0x0    /* 00b	[1:0] */
#define R184_FTDM_OUT46_CHANNEL_OUT_POS_IC_1      0x0    /* 000b	[4:2] */
#define R184_FTDM_OUT46_SERIAL_OUT_SEL_IC_1       0x0    /* 0b	[5] */
#define R184_FTDM_OUT46_REVERSE_OUT_BYTE_IC_1     0x0    /* 0b	[6] */
#define R184_FTDM_OUT46_SLOT_ENABLE_OUT_IC_1      0x0    /* 0b	[7] */
#define R184_FTDM_OUT46_BYTE_OUT_POS_IC_1_MASK    0x3
#define R184_FTDM_OUT46_BYTE_OUT_POS_IC_1_SHIFT   0
#define R184_FTDM_OUT46_CHANNEL_OUT_POS_IC_1_MASK 0x1C
#define R184_FTDM_OUT46_CHANNEL_OUT_POS_IC_1_SHIFT 2
#define R184_FTDM_OUT46_SERIAL_OUT_SEL_IC_1_MASK  0x20
#define R184_FTDM_OUT46_SERIAL_OUT_SEL_IC_1_SHIFT 5
#define R184_FTDM_OUT46_REVERSE_OUT_BYTE_IC_1_MASK 0x40
#define R184_FTDM_OUT46_REVERSE_OUT_BYTE_IC_1_SHIFT 6
#define R184_FTDM_OUT46_SLOT_ENABLE_OUT_IC_1_MASK 0x80
#define R184_FTDM_OUT46_SLOT_ENABLE_OUT_IC_1_SHIFT 7

/* FTDM_OUT47 (IC 1) */
#define R185_FTDM_OUT47_BYTE_OUT_POS_IC_1         0x0    /* 00b	[1:0] */
#define R185_FTDM_OUT47_CHANNEL_OUT_POS_IC_1      0x0    /* 000b	[4:2] */
#define R185_FTDM_OUT47_SERIAL_OUT_SEL_IC_1       0x0    /* 0b	[5] */
#define R185_FTDM_OUT47_REVERSE_OUT_BYTE_IC_1     0x0    /* 0b	[6] */
#define R185_FTDM_OUT47_SLOT_ENABLE_OUT_IC_1      0x0    /* 0b	[7] */
#define R185_FTDM_OUT47_BYTE_OUT_POS_IC_1_MASK    0x3
#define R185_FTDM_OUT47_BYTE_OUT_POS_IC_1_SHIFT   0
#define R185_FTDM_OUT47_CHANNEL_OUT_POS_IC_1_MASK 0x1C
#define R185_FTDM_OUT47_CHANNEL_OUT_POS_IC_1_SHIFT 2
#define R185_FTDM_OUT47_SERIAL_OUT_SEL_IC_1_MASK  0x20
#define R185_FTDM_OUT47_SERIAL_OUT_SEL_IC_1_SHIFT 5
#define R185_FTDM_OUT47_REVERSE_OUT_BYTE_IC_1_MASK 0x40
#define R185_FTDM_OUT47_REVERSE_OUT_BYTE_IC_1_SHIFT 6
#define R185_FTDM_OUT47_SLOT_ENABLE_OUT_IC_1_MASK 0x80
#define R185_FTDM_OUT47_SLOT_ENABLE_OUT_IC_1_SHIFT 7

/* FTDM_OUT48 (IC 1) */
#define R186_FTDM_OUT48_BYTE_OUT_POS_IC_1         0x0    /* 00b	[1:0] */
#define R186_FTDM_OUT48_CHANNEL_OUT_POS_IC_1      0x0    /* 000b	[4:2] */
#define R186_FTDM_OUT48_SERIAL_OUT_SEL_IC_1       0x0    /* 0b	[5] */
#define R186_FTDM_OUT48_REVERSE_OUT_BYTE_IC_1     0x0    /* 0b	[6] */
#define R186_FTDM_OUT48_SLOT_ENABLE_OUT_IC_1      0x0    /* 0b	[7] */
#define R186_FTDM_OUT48_BYTE_OUT_POS_IC_1_MASK    0x3
#define R186_FTDM_OUT48_BYTE_OUT_POS_IC_1_SHIFT   0
#define R186_FTDM_OUT48_CHANNEL_OUT_POS_IC_1_MASK 0x1C
#define R186_FTDM_OUT48_CHANNEL_OUT_POS_IC_1_SHIFT 2
#define R186_FTDM_OUT48_SERIAL_OUT_SEL_IC_1_MASK  0x20
#define R186_FTDM_OUT48_SERIAL_OUT_SEL_IC_1_SHIFT 5
#define R186_FTDM_OUT48_REVERSE_OUT_BYTE_IC_1_MASK 0x40
#define R186_FTDM_OUT48_REVERSE_OUT_BYTE_IC_1_SHIFT 6
#define R186_FTDM_OUT48_SLOT_ENABLE_OUT_IC_1_MASK 0x80
#define R186_FTDM_OUT48_SLOT_ENABLE_OUT_IC_1_SHIFT 7

/* FTDM_OUT49 (IC 1) */
#define R187_FTDM_OUT49_BYTE_OUT_POS_IC_1         0x0    /* 00b	[1:0] */
#define R187_FTDM_OUT49_CHANNEL_OUT_POS_IC_1      0x0    /* 000b	[4:2] */
#define R187_FTDM_OUT49_SERIAL_OUT_SEL_IC_1       0x0    /* 0b	[5] */
#define R187_FTDM_OUT49_REVERSE_OUT_BYTE_IC_1     0x0    /* 0b	[6] */
#define R187_FTDM_OUT49_SLOT_ENABLE_OUT_IC_1      0x0    /* 0b	[7] */
#define R187_FTDM_OUT49_BYTE_OUT_POS_IC_1_MASK    0x3
#define R187_FTDM_OUT49_BYTE_OUT_POS_IC_1_SHIFT   0
#define R187_FTDM_OUT49_CHANNEL_OUT_POS_IC_1_MASK 0x1C
#define R187_FTDM_OUT49_CHANNEL_OUT_POS_IC_1_SHIFT 2
#define R187_FTDM_OUT49_SERIAL_OUT_SEL_IC_1_MASK  0x20
#define R187_FTDM_OUT49_SERIAL_OUT_SEL_IC_1_SHIFT 5
#define R187_FTDM_OUT49_REVERSE_OUT_BYTE_IC_1_MASK 0x40
#define R187_FTDM_OUT49_REVERSE_OUT_BYTE_IC_1_SHIFT 6
#define R187_FTDM_OUT49_SLOT_ENABLE_OUT_IC_1_MASK 0x80
#define R187_FTDM_OUT49_SLOT_ENABLE_OUT_IC_1_SHIFT 7

/* FTDM_OUT50 (IC 1) */
#define R188_FTDM_OUT50_BYTE_OUT_POS_IC_1         0x0    /* 00b	[1:0] */
#define R188_FTDM_OUT50_CHANNEL_OUT_POS_IC_1      0x0    /* 000b	[4:2] */
#define R188_FTDM_OUT50_SERIAL_OUT_SEL_IC_1       0x0    /* 0b	[5] */
#define R188_FTDM_OUT50_REVERSE_OUT_BYTE_IC_1     0x0    /* 0b	[6] */
#define R188_FTDM_OUT50_SLOT_ENABLE_OUT_IC_1      0x0    /* 0b	[7] */
#define R188_FTDM_OUT50_BYTE_OUT_POS_IC_1_MASK    0x3
#define R188_FTDM_OUT50_BYTE_OUT_POS_IC_1_SHIFT   0
#define R188_FTDM_OUT50_CHANNEL_OUT_POS_IC_1_MASK 0x1C
#define R188_FTDM_OUT50_CHANNEL_OUT_POS_IC_1_SHIFT 2
#define R188_FTDM_OUT50_SERIAL_OUT_SEL_IC_1_MASK  0x20
#define R188_FTDM_OUT50_SERIAL_OUT_SEL_IC_1_SHIFT 5
#define R188_FTDM_OUT50_REVERSE_OUT_BYTE_IC_1_MASK 0x40
#define R188_FTDM_OUT50_REVERSE_OUT_BYTE_IC_1_SHIFT 6
#define R188_FTDM_OUT50_SLOT_ENABLE_OUT_IC_1_MASK 0x80
#define R188_FTDM_OUT50_SLOT_ENABLE_OUT_IC_1_SHIFT 7

/* FTDM_OUT51 (IC 1) */
#define R189_FTDM_OUT51_BYTE_OUT_POS_IC_1         0x0    /* 00b	[1:0] */
#define R189_FTDM_OUT51_CHANNEL_OUT_POS_IC_1      0x0    /* 000b	[4:2] */
#define R189_FTDM_OUT51_SERIAL_OUT_SEL_IC_1       0x0    /* 0b	[5] */
#define R189_FTDM_OUT51_REVERSE_OUT_BYTE_IC_1     0x0    /* 0b	[6] */
#define R189_FTDM_OUT51_SLOT_ENABLE_OUT_IC_1      0x0    /* 0b	[7] */
#define R189_FTDM_OUT51_BYTE_OUT_POS_IC_1_MASK    0x3
#define R189_FTDM_OUT51_BYTE_OUT_POS_IC_1_SHIFT   0
#define R189_FTDM_OUT51_CHANNEL_OUT_POS_IC_1_MASK 0x1C
#define R189_FTDM_OUT51_CHANNEL_OUT_POS_IC_1_SHIFT 2
#define R189_FTDM_OUT51_SERIAL_OUT_SEL_IC_1_MASK  0x20
#define R189_FTDM_OUT51_SERIAL_OUT_SEL_IC_1_SHIFT 5
#define R189_FTDM_OUT51_REVERSE_OUT_BYTE_IC_1_MASK 0x40
#define R189_FTDM_OUT51_REVERSE_OUT_BYTE_IC_1_SHIFT 6
#define R189_FTDM_OUT51_SLOT_ENABLE_OUT_IC_1_MASK 0x80
#define R189_FTDM_OUT51_SLOT_ENABLE_OUT_IC_1_SHIFT 7

/* FTDM_OUT52 (IC 1) */
#define R190_FTDM_OUT52_BYTE_OUT_POS_IC_1         0x0    /* 00b	[1:0] */
#define R190_FTDM_OUT52_CHANNEL_OUT_POS_IC_1      0x0    /* 000b	[4:2] */
#define R190_FTDM_OUT52_SERIAL_OUT_SEL_IC_1       0x0    /* 0b	[5] */
#define R190_FTDM_OUT52_REVERSE_OUT_BYTE_IC_1     0x0    /* 0b	[6] */
#define R190_FTDM_OUT52_SLOT_ENABLE_OUT_IC_1      0x0    /* 0b	[7] */
#define R190_FTDM_OUT52_BYTE_OUT_POS_IC_1_MASK    0x3
#define R190_FTDM_OUT52_BYTE_OUT_POS_IC_1_SHIFT   0
#define R190_FTDM_OUT52_CHANNEL_OUT_POS_IC_1_MASK 0x1C
#define R190_FTDM_OUT52_CHANNEL_OUT_POS_IC_1_SHIFT 2
#define R190_FTDM_OUT52_SERIAL_OUT_SEL_IC_1_MASK  0x20
#define R190_FTDM_OUT52_SERIAL_OUT_SEL_IC_1_SHIFT 5
#define R190_FTDM_OUT52_REVERSE_OUT_BYTE_IC_1_MASK 0x40
#define R190_FTDM_OUT52_REVERSE_OUT_BYTE_IC_1_SHIFT 6
#define R190_FTDM_OUT52_SLOT_ENABLE_OUT_IC_1_MASK 0x80
#define R190_FTDM_OUT52_SLOT_ENABLE_OUT_IC_1_SHIFT 7

/* FTDM_OUT53 (IC 1) */
#define R191_FTDM_OUT53_BYTE_OUT_POS_IC_1         0x0    /* 00b	[1:0] */
#define R191_FTDM_OUT53_CHANNEL_OUT_POS_IC_1      0x0    /* 000b	[4:2] */
#define R191_FTDM_OUT53_SERIAL_OUT_SEL_IC_1       0x0    /* 0b	[5] */
#define R191_FTDM_OUT53_REVERSE_OUT_BYTE_IC_1     0x0    /* 0b	[6] */
#define R191_FTDM_OUT53_SLOT_ENABLE_OUT_IC_1      0x0    /* 0b	[7] */
#define R191_FTDM_OUT53_BYTE_OUT_POS_IC_1_MASK    0x3
#define R191_FTDM_OUT53_BYTE_OUT_POS_IC_1_SHIFT   0
#define R191_FTDM_OUT53_CHANNEL_OUT_POS_IC_1_MASK 0x1C
#define R191_FTDM_OUT53_CHANNEL_OUT_POS_IC_1_SHIFT 2
#define R191_FTDM_OUT53_SERIAL_OUT_SEL_IC_1_MASK  0x20
#define R191_FTDM_OUT53_SERIAL_OUT_SEL_IC_1_SHIFT 5
#define R191_FTDM_OUT53_REVERSE_OUT_BYTE_IC_1_MASK 0x40
#define R191_FTDM_OUT53_REVERSE_OUT_BYTE_IC_1_SHIFT 6
#define R191_FTDM_OUT53_SLOT_ENABLE_OUT_IC_1_MASK 0x80
#define R191_FTDM_OUT53_SLOT_ENABLE_OUT_IC_1_SHIFT 7

/* FTDM_OUT54 (IC 1) */
#define R192_FTDM_OUT54_BYTE_OUT_POS_IC_1         0x0    /* 00b	[1:0] */
#define R192_FTDM_OUT54_CHANNEL_OUT_POS_IC_1      0x0    /* 000b	[4:2] */
#define R192_FTDM_OUT54_SERIAL_OUT_SEL_IC_1       0x0    /* 0b	[5] */
#define R192_FTDM_OUT54_REVERSE_OUT_BYTE_IC_1     0x0    /* 0b	[6] */
#define R192_FTDM_OUT54_SLOT_ENABLE_OUT_IC_1      0x0    /* 0b	[7] */
#define R192_FTDM_OUT54_BYTE_OUT_POS_IC_1_MASK    0x3
#define R192_FTDM_OUT54_BYTE_OUT_POS_IC_1_SHIFT   0
#define R192_FTDM_OUT54_CHANNEL_OUT_POS_IC_1_MASK 0x1C
#define R192_FTDM_OUT54_CHANNEL_OUT_POS_IC_1_SHIFT 2
#define R192_FTDM_OUT54_SERIAL_OUT_SEL_IC_1_MASK  0x20
#define R192_FTDM_OUT54_SERIAL_OUT_SEL_IC_1_SHIFT 5
#define R192_FTDM_OUT54_REVERSE_OUT_BYTE_IC_1_MASK 0x40
#define R192_FTDM_OUT54_REVERSE_OUT_BYTE_IC_1_SHIFT 6
#define R192_FTDM_OUT54_SLOT_ENABLE_OUT_IC_1_MASK 0x80
#define R192_FTDM_OUT54_SLOT_ENABLE_OUT_IC_1_SHIFT 7

/* FTDM_OUT55 (IC 1) */
#define R193_FTDM_OUT55_BYTE_OUT_POS_IC_1         0x0    /* 00b	[1:0] */
#define R193_FTDM_OUT55_CHANNEL_OUT_POS_IC_1      0x0    /* 000b	[4:2] */
#define R193_FTDM_OUT55_SERIAL_OUT_SEL_IC_1       0x0    /* 0b	[5] */
#define R193_FTDM_OUT55_REVERSE_OUT_BYTE_IC_1     0x0    /* 0b	[6] */
#define R193_FTDM_OUT55_SLOT_ENABLE_OUT_IC_1      0x0    /* 0b	[7] */
#define R193_FTDM_OUT55_BYTE_OUT_POS_IC_1_MASK    0x3
#define R193_FTDM_OUT55_BYTE_OUT_POS_IC_1_SHIFT   0
#define R193_FTDM_OUT55_CHANNEL_OUT_POS_IC_1_MASK 0x1C
#define R193_FTDM_OUT55_CHANNEL_OUT_POS_IC_1_SHIFT 2
#define R193_FTDM_OUT55_SERIAL_OUT_SEL_IC_1_MASK  0x20
#define R193_FTDM_OUT55_SERIAL_OUT_SEL_IC_1_SHIFT 5
#define R193_FTDM_OUT55_REVERSE_OUT_BYTE_IC_1_MASK 0x40
#define R193_FTDM_OUT55_REVERSE_OUT_BYTE_IC_1_SHIFT 6
#define R193_FTDM_OUT55_SLOT_ENABLE_OUT_IC_1_MASK 0x80
#define R193_FTDM_OUT55_SLOT_ENABLE_OUT_IC_1_SHIFT 7

/* FTDM_OUT56 (IC 1) */
#define R194_FTDM_OUT56_BYTE_OUT_POS_IC_1         0x0    /* 00b	[1:0] */
#define R194_FTDM_OUT56_CHANNEL_OUT_POS_IC_1      0x0    /* 000b	[4:2] */
#define R194_FTDM_OUT56_SERIAL_OUT_SEL_IC_1       0x0    /* 0b	[5] */
#define R194_FTDM_OUT56_REVERSE_OUT_BYTE_IC_1     0x0    /* 0b	[6] */
#define R194_FTDM_OUT56_SLOT_ENABLE_OUT_IC_1      0x0    /* 0b	[7] */
#define R194_FTDM_OUT56_BYTE_OUT_POS_IC_1_MASK    0x3
#define R194_FTDM_OUT56_BYTE_OUT_POS_IC_1_SHIFT   0
#define R194_FTDM_OUT56_CHANNEL_OUT_POS_IC_1_MASK 0x1C
#define R194_FTDM_OUT56_CHANNEL_OUT_POS_IC_1_SHIFT 2
#define R194_FTDM_OUT56_SERIAL_OUT_SEL_IC_1_MASK  0x20
#define R194_FTDM_OUT56_SERIAL_OUT_SEL_IC_1_SHIFT 5
#define R194_FTDM_OUT56_REVERSE_OUT_BYTE_IC_1_MASK 0x40
#define R194_FTDM_OUT56_REVERSE_OUT_BYTE_IC_1_SHIFT 6
#define R194_FTDM_OUT56_SLOT_ENABLE_OUT_IC_1_MASK 0x80
#define R194_FTDM_OUT56_SLOT_ENABLE_OUT_IC_1_SHIFT 7

/* FTDM_OUT57 (IC 1) */
#define R195_FTDM_OUT57_BYTE_OUT_POS_IC_1         0x0    /* 00b	[1:0] */
#define R195_FTDM_OUT57_CHANNEL_OUT_POS_IC_1      0x0    /* 000b	[4:2] */
#define R195_FTDM_OUT57_SERIAL_OUT_SEL_IC_1       0x0    /* 0b	[5] */
#define R195_FTDM_OUT57_REVERSE_OUT_BYTE_IC_1     0x0    /* 0b	[6] */
#define R195_FTDM_OUT57_SLOT_ENABLE_OUT_IC_1      0x0    /* 0b	[7] */
#define R195_FTDM_OUT57_BYTE_OUT_POS_IC_1_MASK    0x3
#define R195_FTDM_OUT57_BYTE_OUT_POS_IC_1_SHIFT   0
#define R195_FTDM_OUT57_CHANNEL_OUT_POS_IC_1_MASK 0x1C
#define R195_FTDM_OUT57_CHANNEL_OUT_POS_IC_1_SHIFT 2
#define R195_FTDM_OUT57_SERIAL_OUT_SEL_IC_1_MASK  0x20
#define R195_FTDM_OUT57_SERIAL_OUT_SEL_IC_1_SHIFT 5
#define R195_FTDM_OUT57_REVERSE_OUT_BYTE_IC_1_MASK 0x40
#define R195_FTDM_OUT57_REVERSE_OUT_BYTE_IC_1_SHIFT 6
#define R195_FTDM_OUT57_SLOT_ENABLE_OUT_IC_1_MASK 0x80
#define R195_FTDM_OUT57_SLOT_ENABLE_OUT_IC_1_SHIFT 7

/* FTDM_OUT58 (IC 1) */
#define R196_FTDM_OUT58_BYTE_OUT_POS_IC_1         0x0    /* 00b	[1:0] */
#define R196_FTDM_OUT58_CHANNEL_OUT_POS_IC_1      0x0    /* 000b	[4:2] */
#define R196_FTDM_OUT58_SERIAL_OUT_SEL_IC_1       0x0    /* 0b	[5] */
#define R196_FTDM_OUT58_REVERSE_OUT_BYTE_IC_1     0x0    /* 0b	[6] */
#define R196_FTDM_OUT58_SLOT_ENABLE_OUT_IC_1      0x0    /* 0b	[7] */
#define R196_FTDM_OUT58_BYTE_OUT_POS_IC_1_MASK    0x3
#define R196_FTDM_OUT58_BYTE_OUT_POS_IC_1_SHIFT   0
#define R196_FTDM_OUT58_CHANNEL_OUT_POS_IC_1_MASK 0x1C
#define R196_FTDM_OUT58_CHANNEL_OUT_POS_IC_1_SHIFT 2
#define R196_FTDM_OUT58_SERIAL_OUT_SEL_IC_1_MASK  0x20
#define R196_FTDM_OUT58_SERIAL_OUT_SEL_IC_1_SHIFT 5
#define R196_FTDM_OUT58_REVERSE_OUT_BYTE_IC_1_MASK 0x40
#define R196_FTDM_OUT58_REVERSE_OUT_BYTE_IC_1_SHIFT 6
#define R196_FTDM_OUT58_SLOT_ENABLE_OUT_IC_1_MASK 0x80
#define R196_FTDM_OUT58_SLOT_ENABLE_OUT_IC_1_SHIFT 7

/* FTDM_OUT59 (IC 1) */
#define R197_FTDM_OUT59_BYTE_OUT_POS_IC_1         0x0    /* 00b	[1:0] */
#define R197_FTDM_OUT59_CHANNEL_OUT_POS_IC_1      0x0    /* 000b	[4:2] */
#define R197_FTDM_OUT59_SERIAL_OUT_SEL_IC_1       0x0    /* 0b	[5] */
#define R197_FTDM_OUT59_REVERSE_OUT_BYTE_IC_1     0x0    /* 0b	[6] */
#define R197_FTDM_OUT59_SLOT_ENABLE_OUT_IC_1      0x0    /* 0b	[7] */
#define R197_FTDM_OUT59_BYTE_OUT_POS_IC_1_MASK    0x3
#define R197_FTDM_OUT59_BYTE_OUT_POS_IC_1_SHIFT   0
#define R197_FTDM_OUT59_CHANNEL_OUT_POS_IC_1_MASK 0x1C
#define R197_FTDM_OUT59_CHANNEL_OUT_POS_IC_1_SHIFT 2
#define R197_FTDM_OUT59_SERIAL_OUT_SEL_IC_1_MASK  0x20
#define R197_FTDM_OUT59_SERIAL_OUT_SEL_IC_1_SHIFT 5
#define R197_FTDM_OUT59_REVERSE_OUT_BYTE_IC_1_MASK 0x40
#define R197_FTDM_OUT59_REVERSE_OUT_BYTE_IC_1_SHIFT 6
#define R197_FTDM_OUT59_SLOT_ENABLE_OUT_IC_1_MASK 0x80
#define R197_FTDM_OUT59_SLOT_ENABLE_OUT_IC_1_SHIFT 7

/* FTDM_OUT60 (IC 1) */
#define R198_FTDM_OUT60_BYTE_OUT_POS_IC_1         0x0    /* 00b	[1:0] */
#define R198_FTDM_OUT60_CHANNEL_OUT_POS_IC_1      0x0    /* 000b	[4:2] */
#define R198_FTDM_OUT60_SERIAL_OUT_SEL_IC_1       0x0    /* 0b	[5] */
#define R198_FTDM_OUT60_REVERSE_OUT_BYTE_IC_1     0x0    /* 0b	[6] */
#define R198_FTDM_OUT60_SLOT_ENABLE_OUT_IC_1      0x0    /* 0b	[7] */
#define R198_FTDM_OUT60_BYTE_OUT_POS_IC_1_MASK    0x3
#define R198_FTDM_OUT60_BYTE_OUT_POS_IC_1_SHIFT   0
#define R198_FTDM_OUT60_CHANNEL_OUT_POS_IC_1_MASK 0x1C
#define R198_FTDM_OUT60_CHANNEL_OUT_POS_IC_1_SHIFT 2
#define R198_FTDM_OUT60_SERIAL_OUT_SEL_IC_1_MASK  0x20
#define R198_FTDM_OUT60_SERIAL_OUT_SEL_IC_1_SHIFT 5
#define R198_FTDM_OUT60_REVERSE_OUT_BYTE_IC_1_MASK 0x40
#define R198_FTDM_OUT60_REVERSE_OUT_BYTE_IC_1_SHIFT 6
#define R198_FTDM_OUT60_SLOT_ENABLE_OUT_IC_1_MASK 0x80
#define R198_FTDM_OUT60_SLOT_ENABLE_OUT_IC_1_SHIFT 7

/* FTDM_OUT61 (IC 1) */
#define R199_FTDM_OUT61_BYTE_OUT_POS_IC_1         0x0    /* 00b	[1:0] */
#define R199_FTDM_OUT61_CHANNEL_OUT_POS_IC_1      0x0    /* 000b	[4:2] */
#define R199_FTDM_OUT61_SERIAL_OUT_SEL_IC_1       0x0    /* 0b	[5] */
#define R199_FTDM_OUT61_REVERSE_OUT_BYTE_IC_1     0x0    /* 0b	[6] */
#define R199_FTDM_OUT61_SLOT_ENABLE_OUT_IC_1      0x0    /* 0b	[7] */
#define R199_FTDM_OUT61_BYTE_OUT_POS_IC_1_MASK    0x3
#define R199_FTDM_OUT61_BYTE_OUT_POS_IC_1_SHIFT   0
#define R199_FTDM_OUT61_CHANNEL_OUT_POS_IC_1_MASK 0x1C
#define R199_FTDM_OUT61_CHANNEL_OUT_POS_IC_1_SHIFT 2
#define R199_FTDM_OUT61_SERIAL_OUT_SEL_IC_1_MASK  0x20
#define R199_FTDM_OUT61_SERIAL_OUT_SEL_IC_1_SHIFT 5
#define R199_FTDM_OUT61_REVERSE_OUT_BYTE_IC_1_MASK 0x40
#define R199_FTDM_OUT61_REVERSE_OUT_BYTE_IC_1_SHIFT 6
#define R199_FTDM_OUT61_SLOT_ENABLE_OUT_IC_1_MASK 0x80
#define R199_FTDM_OUT61_SLOT_ENABLE_OUT_IC_1_SHIFT 7

/* FTDM_OUT62 (IC 1) */
#define R200_FTDM_OUT62_BYTE_OUT_POS_IC_1         0x0    /* 00b	[1:0] */
#define R200_FTDM_OUT62_CHANNEL_OUT_POS_IC_1      0x0    /* 000b	[4:2] */
#define R200_FTDM_OUT62_SERIAL_OUT_SEL_IC_1       0x0    /* 0b	[5] */
#define R200_FTDM_OUT62_REVERSE_OUT_BYTE_IC_1     0x0    /* 0b	[6] */
#define R200_FTDM_OUT62_SLOT_ENABLE_OUT_IC_1      0x0    /* 0b	[7] */
#define R200_FTDM_OUT62_BYTE_OUT_POS_IC_1_MASK    0x3
#define R200_FTDM_OUT62_BYTE_OUT_POS_IC_1_SHIFT   0
#define R200_FTDM_OUT62_CHANNEL_OUT_POS_IC_1_MASK 0x1C
#define R200_FTDM_OUT62_CHANNEL_OUT_POS_IC_1_SHIFT 2
#define R200_FTDM_OUT62_SERIAL_OUT_SEL_IC_1_MASK  0x20
#define R200_FTDM_OUT62_SERIAL_OUT_SEL_IC_1_SHIFT 5
#define R200_FTDM_OUT62_REVERSE_OUT_BYTE_IC_1_MASK 0x40
#define R200_FTDM_OUT62_REVERSE_OUT_BYTE_IC_1_SHIFT 6
#define R200_FTDM_OUT62_SLOT_ENABLE_OUT_IC_1_MASK 0x80
#define R200_FTDM_OUT62_SLOT_ENABLE_OUT_IC_1_SHIFT 7

/* FTDM_OUT63 (IC 1) */
#define R201_FTDM_OUT63_BYTE_OUT_POS_IC_1         0x0    /* 00b	[1:0] */
#define R201_FTDM_OUT63_CHANNEL_OUT_POS_IC_1      0x0    /* 000b	[4:2] */
#define R201_FTDM_OUT63_SERIAL_OUT_SEL_IC_1       0x0    /* 0b	[5] */
#define R201_FTDM_OUT63_REVERSE_OUT_BYTE_IC_1     0x0    /* 0b	[6] */
#define R201_FTDM_OUT63_SLOT_ENABLE_OUT_IC_1      0x0    /* 0b	[7] */
#define R201_FTDM_OUT63_BYTE_OUT_POS_IC_1_MASK    0x3
#define R201_FTDM_OUT63_BYTE_OUT_POS_IC_1_SHIFT   0
#define R201_FTDM_OUT63_CHANNEL_OUT_POS_IC_1_MASK 0x1C
#define R201_FTDM_OUT63_CHANNEL_OUT_POS_IC_1_SHIFT 2
#define R201_FTDM_OUT63_SERIAL_OUT_SEL_IC_1_MASK  0x20
#define R201_FTDM_OUT63_SERIAL_OUT_SEL_IC_1_SHIFT 5
#define R201_FTDM_OUT63_REVERSE_OUT_BYTE_IC_1_MASK 0x40
#define R201_FTDM_OUT63_REVERSE_OUT_BYTE_IC_1_SHIFT 6
#define R201_FTDM_OUT63_SLOT_ENABLE_OUT_IC_1_MASK 0x80
#define R201_FTDM_OUT63_SLOT_ENABLE_OUT_IC_1_SHIFT 7

/* HIBERNATE (IC 1) */
#define R202_HIBERNATE_HIBERNATE_IC_1             0x0    /* 0b	[0] */
#define R202_HIBERNATE_HIBERNATE_IC_1_MASK        0x1
#define R202_HIBERNATE_HIBERNATE_IC_1_SHIFT       0

/* START_PULSE (IC 1) */
#define R203_START_PULSE_START_PULSE_IC_1         0x2    /* 00010b	[4:0] */
#define R203_START_PULSE_START_PULSE_IC_1_MASK    0x1F
#define R203_START_PULSE_START_PULSE_IC_1_SHIFT   0

/* START_CORE (IC 1) */
#define R204_START_CORE_START_CORE_IC_1           0x1    /* 1b	[0] */
#define R204_START_CORE_START_CORE_IC_1_MASK      0x1
#define R204_START_CORE_START_CORE_IC_1_SHIFT     0

/* KILL_CORE (IC 1) */
#define R205_KILL_CORE_KILL_CORE_IC_1             0x0    /* 0b	[0] */
#define R205_KILL_CORE_KILL_CORE_IC_1_MASK        0x1
#define R205_KILL_CORE_KILL_CORE_IC_1_SHIFT       0

/* START_ADDRESS (IC 1) */
#define R206_START_ADDRESS_START_ADDRESS_IC_1     0x0000 /* 0000000000000000b	[15:0] */
#define R206_START_ADDRESS_START_ADDRESS_IC_1_MASK 0xFFFF
#define R206_START_ADDRESS_START_ADDRESS_IC_1_SHIFT 0

/* CORE_STATUS (IC 1) */
#define R207_CORE_STATUS_CORE_STATUS_IC_1         0x1    /* 001b	[2:0] */
#define R207_CORE_STATUS_CORE_STATUS_IC_1_MASK    0x7
#define R207_CORE_STATUS_CORE_STATUS_IC_1_SHIFT   0

/* DEBUG_MODE (IC 1) */
#define R208_DEBUG_MODE_DEBUG_MODE_IC_1           0x0    /* 0b	[0] */
#define R208_DEBUG_MODE_DEBUG_MODE_IC_1_MASK      0x1
#define R208_DEBUG_MODE_DEBUG_MODE_IC_1_SHIFT     0

/* PANIC_CLEAR (IC 1) */
#define R209_PANIC_CLEAR_PANIC_CLEAR_IC_1         0x0    /* 0b	[0] */
#define R209_PANIC_CLEAR_PANIC_CLEAR_IC_1_MASK    0x1
#define R209_PANIC_CLEAR_PANIC_CLEAR_IC_1_SHIFT   0

/* PANIC_PARITY_MASK (IC 1) */
#define R210_PANIC_PARITY_MASK_ASRC0_MASK_IC_1    0x1    /* 1b	[0] */
#define R210_PANIC_PARITY_MASK_ASRC1_MASK_IC_1    0x1    /* 1b	[1] */
#define R210_PANIC_PARITY_MASK_PM0_MASK_IC_1      0x0    /* 0b	[2] */
#define R210_PANIC_PARITY_MASK_PM1_MASK_IC_1      0x0    /* 0b	[3] */
#define R210_PANIC_PARITY_MASK_DM0_BANK0_MASK_IC_1 0x0   /* 0b	[4] */
#define R210_PANIC_PARITY_MASK_DM0_BANK1_MASK_IC_1 0x0   /* 0b	[5] */
#define R210_PANIC_PARITY_MASK_DM0_BANK2_MASK_IC_1 0x0   /* 0b	[6] */
#define R210_PANIC_PARITY_MASK_DM0_BANK3_MASK_IC_1 0x0   /* 0b	[7] */
#define R210_PANIC_PARITY_MASK_DM1_BANK0_MASK_IC_1 0x0   /* 0b	[8] */
#define R210_PANIC_PARITY_MASK_DM1_BANK1_MASK_IC_1 0x0   /* 0b	[9] */
#define R210_PANIC_PARITY_MASK_DM1_BANK2_MASK_IC_1 0x0   /* 0b	[10] */
#define R210_PANIC_PARITY_MASK_DM1_BANK3_MASK_IC_1 0x0   /* 0b	[11] */
#define R210_PANIC_PARITY_MASK_ASRC0_MASK_IC_1_MASK 0x1
#define R210_PANIC_PARITY_MASK_ASRC0_MASK_IC_1_SHIFT 0
#define R210_PANIC_PARITY_MASK_ASRC1_MASK_IC_1_MASK 0x2
#define R210_PANIC_PARITY_MASK_ASRC1_MASK_IC_1_SHIFT 1
#define R210_PANIC_PARITY_MASK_PM0_MASK_IC_1_MASK 0x4
#define R210_PANIC_PARITY_MASK_PM0_MASK_IC_1_SHIFT 2
#define R210_PANIC_PARITY_MASK_PM1_MASK_IC_1_MASK 0x8
#define R210_PANIC_PARITY_MASK_PM1_MASK_IC_1_SHIFT 3
#define R210_PANIC_PARITY_MASK_DM0_BANK0_MASK_IC_1_MASK 0x10
#define R210_PANIC_PARITY_MASK_DM0_BANK0_MASK_IC_1_SHIFT 4
#define R210_PANIC_PARITY_MASK_DM0_BANK1_MASK_IC_1_MASK 0x20
#define R210_PANIC_PARITY_MASK_DM0_BANK1_MASK_IC_1_SHIFT 5
#define R210_PANIC_PARITY_MASK_DM0_BANK2_MASK_IC_1_MASK 0x40
#define R210_PANIC_PARITY_MASK_DM0_BANK2_MASK_IC_1_SHIFT 6
#define R210_PANIC_PARITY_MASK_DM0_BANK3_MASK_IC_1_MASK 0x80
#define R210_PANIC_PARITY_MASK_DM0_BANK3_MASK_IC_1_SHIFT 7
#define R210_PANIC_PARITY_MASK_DM1_BANK0_MASK_IC_1_MASK 0x100
#define R210_PANIC_PARITY_MASK_DM1_BANK0_MASK_IC_1_SHIFT 8
#define R210_PANIC_PARITY_MASK_DM1_BANK1_MASK_IC_1_MASK 0x200
#define R210_PANIC_PARITY_MASK_DM1_BANK1_MASK_IC_1_SHIFT 9
#define R210_PANIC_PARITY_MASK_DM1_BANK2_MASK_IC_1_MASK 0x400
#define R210_PANIC_PARITY_MASK_DM1_BANK2_MASK_IC_1_SHIFT 10
#define R210_PANIC_PARITY_MASK_DM1_BANK3_MASK_IC_1_MASK 0x800
#define R210_PANIC_PARITY_MASK_DM1_BANK3_MASK_IC_1_SHIFT 11

/* PANIC_SOFTWARE_MASK (IC 1) */
#define R211_PANIC_SOFTWARE_MASK_PANIC_SOFTWARE_IC_1 0x0 /* 0b	[0] */
#define R211_PANIC_SOFTWARE_MASK_PANIC_SOFTWARE_IC_1_MASK 0x1
#define R211_PANIC_SOFTWARE_MASK_PANIC_SOFTWARE_IC_1_SHIFT 0

/* PANIC_WD_MASK (IC 1) */
#define R212_PANIC_WD_MASK_PANIC_WD_IC_1          0x0    /* 0b	[0] */
#define R212_PANIC_WD_MASK_PANIC_WD_IC_1_MASK     0x1
#define R212_PANIC_WD_MASK_PANIC_WD_IC_1_SHIFT    0

/* PANIC_STACK_MASK (IC 1) */
#define R213_PANIC_STACK_MASK_PANIC_STACK_IC_1    0x0    /* 0b	[0] */
#define R213_PANIC_STACK_MASK_PANIC_STACK_IC_1_MASK 0x1
#define R213_PANIC_STACK_MASK_PANIC_STACK_IC_1_SHIFT 0

/* PANIC_LOOP_MASK (IC 1) */
#define R214_PANIC_LOOP_MASK_PANIC_LOOP_IC_1      0x0    /* 0b	[0] */
#define R214_PANIC_LOOP_MASK_PANIC_LOOP_IC_1_MASK 0x1
#define R214_PANIC_LOOP_MASK_PANIC_LOOP_IC_1_SHIFT 0

/* PANIC_FLAG (IC 1) */
#define R215_PANIC_FLAG_PANIC_FLAG_IC_1           0x1    /* 1b	[0] */
#define R215_PANIC_FLAG_PANIC_FLAG_IC_1_MASK      0x1
#define R215_PANIC_FLAG_PANIC_FLAG_IC_1_SHIFT     0

/* PANIC_CODE (IC 1) */
#define R216_PANIC_CODE_ERR_ASRC0_IC_1            0x0    /* 0b	[0] */
#define R216_PANIC_CODE_ERR_ASRC1_IC_1            0x0    /* 0b	[1] */
#define R216_PANIC_CODE_ERR_PM0_IC_1              0x0    /* 0b	[2] */
#define R216_PANIC_CODE_ERR_PM1_IC_1              0x0    /* 0b	[3] */
#define R216_PANIC_CODE_ERR_DM0B0_IC_1            0x0    /* 0b	[4] */
#define R216_PANIC_CODE_ERR_DM0B1_IC_1            0x0    /* 0b	[5] */
#define R216_PANIC_CODE_ERR_DM0B2_IC_1            0x0    /* 0b	[6] */
#define R216_PANIC_CODE_ERR_DM0B3_IC_1            0x1    /* 1b	[7] */
#define R216_PANIC_CODE_ERR_DM1B0_IC_1            0x0    /* 0b	[8] */
#define R216_PANIC_CODE_ERR_DM1B1_IC_1            0x0    /* 0b	[9] */
#define R216_PANIC_CODE_ERR_DM1B2_IC_1            0x0    /* 0b	[10] */
#define R216_PANIC_CODE_ERR_DM1B3_IC_1            0x0    /* 0b	[11] */
#define R216_PANIC_CODE_ERR_WATCHDOG_IC_1         0x0    /* 0b	[12] */
#define R216_PANIC_CODE_ERR_STACK_IC_1            0x0    /* 0b	[13] */
#define R216_PANIC_CODE_ERR_LOOP_IC_1             0x0    /* 0b	[14] */
#define R216_PANIC_CODE_ERR_SOFT_IC_1             0x0    /* 0b	[15] */
#define R216_PANIC_CODE_ERR_ASRC0_IC_1_MASK       0x1
#define R216_PANIC_CODE_ERR_ASRC0_IC_1_SHIFT      0
#define R216_PANIC_CODE_ERR_ASRC1_IC_1_MASK       0x2
#define R216_PANIC_CODE_ERR_ASRC1_IC_1_SHIFT      1
#define R216_PANIC_CODE_ERR_PM0_IC_1_MASK         0x4
#define R216_PANIC_CODE_ERR_PM0_IC_1_SHIFT        2
#define R216_PANIC_CODE_ERR_PM1_IC_1_MASK         0x8
#define R216_PANIC_CODE_ERR_PM1_IC_1_SHIFT        3
#define R216_PANIC_CODE_ERR_DM0B0_IC_1_MASK       0x10
#define R216_PANIC_CODE_ERR_DM0B0_IC_1_SHIFT      4
#define R216_PANIC_CODE_ERR_DM0B1_IC_1_MASK       0x20
#define R216_PANIC_CODE_ERR_DM0B1_IC_1_SHIFT      5
#define R216_PANIC_CODE_ERR_DM0B2_IC_1_MASK       0x40
#define R216_PANIC_CODE_ERR_DM0B2_IC_1_SHIFT      6
#define R216_PANIC_CODE_ERR_DM0B3_IC_1_MASK       0x80
#define R216_PANIC_CODE_ERR_DM0B3_IC_1_SHIFT      7
#define R216_PANIC_CODE_ERR_DM1B0_IC_1_MASK       0x100
#define R216_PANIC_CODE_ERR_DM1B0_IC_1_SHIFT      8
#define R216_PANIC_CODE_ERR_DM1B1_IC_1_MASK       0x200
#define R216_PANIC_CODE_ERR_DM1B1_IC_1_SHIFT      9
#define R216_PANIC_CODE_ERR_DM1B2_IC_1_MASK       0x400
#define R216_PANIC_CODE_ERR_DM1B2_IC_1_SHIFT      10
#define R216_PANIC_CODE_ERR_DM1B3_IC_1_MASK       0x800
#define R216_PANIC_CODE_ERR_DM1B3_IC_1_SHIFT      11
#define R216_PANIC_CODE_ERR_WATCHDOG_IC_1_MASK    0x1000
#define R216_PANIC_CODE_ERR_WATCHDOG_IC_1_SHIFT   12
#define R216_PANIC_CODE_ERR_STACK_IC_1_MASK       0x2000
#define R216_PANIC_CODE_ERR_STACK_IC_1_SHIFT      13
#define R216_PANIC_CODE_ERR_LOOP_IC_1_MASK        0x4000
#define R216_PANIC_CODE_ERR_LOOP_IC_1_SHIFT       14
#define R216_PANIC_CODE_ERR_SOFT_IC_1_MASK        0x8000
#define R216_PANIC_CODE_ERR_SOFT_IC_1_SHIFT       15

/* DECODE_OP0 (IC 1) */
#define R217_DECODE_OP0_DECODE_OP0_IC_1           0x0000 /* 0000000000000000b	[15:0] */
#define R217_DECODE_OP0_DECODE_OP0_IC_1_MASK      0xFFFF
#define R217_DECODE_OP0_DECODE_OP0_IC_1_SHIFT     0

/* DECODE_OP1 (IC 1) */
#define R218_DECODE_OP1_DECODE_OP1_IC_1           0x0000 /* 0000000000000000b	[15:0] */
#define R218_DECODE_OP1_DECODE_OP1_IC_1_MASK      0xFFFF
#define R218_DECODE_OP1_DECODE_OP1_IC_1_SHIFT     0

/* DECODE_OP2 (IC 1) */
#define R219_DECODE_OP2_DECODE_OP2_IC_1           0xFFA8 /* 1111111110101000b	[15:0] */
#define R219_DECODE_OP2_DECODE_OP2_IC_1_MASK      0xFFFF
#define R219_DECODE_OP2_DECODE_OP2_IC_1_SHIFT     0

/* DECODE_OP3 (IC 1) */
#define R220_DECODE_OP3_DECODE_OP3_IC_1           0x0A40 /* 0000101001000000b	[15:0] */
#define R220_DECODE_OP3_DECODE_OP3_IC_1_MASK      0xFFFF
#define R220_DECODE_OP3_DECODE_OP3_IC_1_SHIFT     0

/* EXECUTE_OP0 (IC 1) */
#define R221_EXECUTE_OP0_DECODE_EX0_IC_1          0x0000 /* 0000000000000000b	[15:0] */
#define R221_EXECUTE_OP0_DECODE_EX0_IC_1_MASK     0xFFFF
#define R221_EXECUTE_OP0_DECODE_EX0_IC_1_SHIFT    0

/* EXECUTE_OP1 (IC 1) */
#define R222_EXECUTE_OP1_DECODE_EX1_IC_1          0x0000 /* 0000000000000000b	[15:0] */
#define R222_EXECUTE_OP1_DECODE_EX1_IC_1_MASK     0xFFFF
#define R222_EXECUTE_OP1_DECODE_EX1_IC_1_SHIFT    0

/* EXECUTE_OP2 (IC 1) */
#define R223_EXECUTE_OP2_DECODE_EX2_IC_1          0x0000 /* 0000000000000000b	[15:0] */
#define R223_EXECUTE_OP2_DECODE_EX2_IC_1_MASK     0xFFFF
#define R223_EXECUTE_OP2_DECODE_EX2_IC_1_SHIFT    0

/* EXECUTE_OP3 (IC 1) */
#define R224_EXECUTE_OP3_DECODE_EX3_IC_1          0x0000 /* 0000000000000000b	[15:0] */
#define R224_EXECUTE_OP3_DECODE_EX3_IC_1_MASK     0xFFFF
#define R224_EXECUTE_OP3_DECODE_EX3_IC_1_SHIFT    0

/* DECODE_COUNT (IC 1) */
#define R225_DECODE_COUNT_DECODE_COUNT_IC_1       0xC0FF /* 1100000011111111b	[15:0] */
#define R225_DECODE_COUNT_DECODE_COUNT_IC_1_MASK  0xFFFF
#define R225_DECODE_COUNT_DECODE_COUNT_IC_1_SHIFT 0

/* EXECUTE_COUNT (IC 1) */
#define R226_EXECUTE_COUNT_EXECUTE_COUNT_IC_1     0x0000 /* 0000000000000000b	[15:0] */
#define R226_EXECUTE_COUNT_EXECUTE_COUNT_IC_1_MASK 0xFFFF
#define R226_EXECUTE_COUNT_EXECUTE_COUNT_IC_1_SHIFT 0

/* SOFTWARE_VALUE_0 (IC 1) */
#define R227_SOFTWARE_VALUE_0_SOFTWARE_VALUE_0_IC_1 0x0000 /* 0000000000000000b	[15:0] */
#define R227_SOFTWARE_VALUE_0_SOFTWARE_VALUE_0_IC_1_MASK 0xFFFF
#define R227_SOFTWARE_VALUE_0_SOFTWARE_VALUE_0_IC_1_SHIFT 0

/* SOFTWARE_VALUE_1 (IC 1) */
#define R228_SOFTWARE_VALUE_1_SOFTWARE_VALUE_1_IC_1 0x0000 /* 0000000000000000b	[15:0] */
#define R228_SOFTWARE_VALUE_1_SOFTWARE_VALUE_1_IC_1_MASK 0xFFFF
#define R228_SOFTWARE_VALUE_1_SOFTWARE_VALUE_1_IC_1_SHIFT 0

/* WATCHDOG_MAXCOUNT (IC 1) */
#define R229_WATCHDOG_MAXCOUNT_WD_MAXCOUNT_IC_1   0x000  /* 0000000000000b	[12:0] */
#define R229_WATCHDOG_MAXCOUNT_WD_MAXCOUNT_IC_1_MASK 0x1FFF
#define R229_WATCHDOG_MAXCOUNT_WD_MAXCOUNT_IC_1_SHIFT 0

/* WATCHDOG_PRESCALE (IC 1) */
#define R230_WATCHDOG_PRESCALE_WD_PRESCALE_IC_1   0x0    /* 0000b	[3:0] */
#define R230_WATCHDOG_PRESCALE_WD_PRESCALE_IC_1_MASK 0xF
#define R230_WATCHDOG_PRESCALE_WD_PRESCALE_IC_1_SHIFT 0

/* BLOCKINT_EN (IC 1) */
#define R231_BLOCKINT_EN_BLOCKINT_EN_IC_1         0x0    /* 0b	[0] */
#define R231_BLOCKINT_EN_BLOCKINT_EN_IC_1_MASK    0x1
#define R231_BLOCKINT_EN_BLOCKINT_EN_IC_1_SHIFT   0

/* BLOCKINT_VALUE (IC 1) */
#define R232_BLOCKINT_VALUE_BLOCKINT_VALUE_IC_1   0x0000 /* 0000000000000000b	[15:0] */
#define R232_BLOCKINT_VALUE_BLOCKINT_VALUE_IC_1_MASK 0xFFFF
#define R232_BLOCKINT_VALUE_BLOCKINT_VALUE_IC_1_SHIFT 0

/* PROG_CNTR0 (IC 1) */
#define R233_PROG_CNTR0_PROG_CNTR_MSB_IC_1        0x00   /* 00000000b	[7:0] */
#define R233_PROG_CNTR0_PROG_CNTR_MSB_IC_1_MASK   0xFF
#define R233_PROG_CNTR0_PROG_CNTR_MSB_IC_1_SHIFT  0

/* PROG_CNTR1 (IC 1) */
#define R234_PROG_CNTR1_PROG_CNTR_LSB_IC_1        0x086C /* 0000100001101100b	[15:0] */
#define R234_PROG_CNTR1_PROG_CNTR_LSB_IC_1_MASK   0xFFFF
#define R234_PROG_CNTR1_PROG_CNTR_LSB_IC_1_SHIFT  0

/* PROG_CNTR_CLEAR (IC 1) */
#define R235_PROG_CNTR_CLEAR_PROG_CNTR_CLEAR_IC_1 0x0    /* 0b	[0] */
#define R235_PROG_CNTR_CLEAR_PROG_CNTR_CLEAR_IC_1_MASK 0x1
#define R235_PROG_CNTR_CLEAR_PROG_CNTR_CLEAR_IC_1_SHIFT 0

/* PROG_CNTR_LENGTH0 (IC 1) */
#define R236_PROG_CNTR_LENGTH0_PROG_LENGTH_MSB_IC_1 0x00 /* 00000000b	[7:0] */
#define R236_PROG_CNTR_LENGTH0_PROG_LENGTH_MSB_IC_1_MASK 0xFF
#define R236_PROG_CNTR_LENGTH0_PROG_LENGTH_MSB_IC_1_SHIFT 0

/* PROG_CNTR_LENGTH1 (IC 1) */
#define R237_PROG_CNTR_LENGTH1_PROG_LENGTH_LSB_IC_1 0x066A /* 0000011001101010b	[15:0] */
#define R237_PROG_CNTR_LENGTH1_PROG_LENGTH_LSB_IC_1_MASK 0xFFFF
#define R237_PROG_CNTR_LENGTH1_PROG_LENGTH_LSB_IC_1_SHIFT 0

/* PROG_CNTR_MAXLENGTH0 (IC 1) */
#define R238_PROG_CNTR_MAXLENGTH0_PROG_MAXLENGTH_MSB_IC_1 0x00 /* 00000000b	[7:0] */
#define R238_PROG_CNTR_MAXLENGTH0_PROG_MAXLENGTH_MSB_IC_1_MASK 0xFF
#define R238_PROG_CNTR_MAXLENGTH0_PROG_MAXLENGTH_MSB_IC_1_SHIFT 0

/* PROG_CNTR_MAXLENGTH1 (IC 1) */
#define R239_PROG_CNTR_MAXLENGTH1_PROG_MAXLENGTH_LSB_IC_1 0x120A /* 0001001000001010b	[15:0] */
#define R239_PROG_CNTR_MAXLENGTH1_PROG_MAXLENGTH_LSB_IC_1_MASK 0xFFFF
#define R239_PROG_CNTR_MAXLENGTH1_PROG_MAXLENGTH_LSB_IC_1_SHIFT 0

/* MP0_MODE (IC 1) */
#define R240_MP0_MODE_MP_ENABLE_IC_1              0x1    /* 1b	[0] */
#define R240_MP0_MODE_MP_MODE_IC_1                0x6    /* 110b	[3:1] */
#define R240_MP0_MODE_DEBOUNCE_VALUE_IC_1         0x0    /* 0000b	[7:4] */
#define R240_MP0_MODE_SS_SELECT_IC_1              0x0    /* 000b	[10:8] */
#define R240_MP0_MODE_MP_ENABLE_IC_1_MASK         0x1
#define R240_MP0_MODE_MP_ENABLE_IC_1_SHIFT        0
#define R240_MP0_MODE_MP_MODE_IC_1_MASK           0xE
#define R240_MP0_MODE_MP_MODE_IC_1_SHIFT          1
#define R240_MP0_MODE_DEBOUNCE_VALUE_IC_1_MASK    0xF0
#define R240_MP0_MODE_DEBOUNCE_VALUE_IC_1_SHIFT   4
#define R240_MP0_MODE_SS_SELECT_IC_1_MASK         0x700
#define R240_MP0_MODE_SS_SELECT_IC_1_SHIFT        8

/* MP1_MODE (IC 1) */
#define R241_MP1_MODE_MP_ENABLE_IC_1              0x0    /* 0b	[0] */
#define R241_MP1_MODE_MP_MODE_IC_1                0x0    /* 000b	[3:1] */
#define R241_MP1_MODE_DEBOUNCE_VALUE_IC_1         0x0    /* 0000b	[7:4] */
#define R241_MP1_MODE_SS_SELECT_IC_1              0x0    /* 000b	[10:8] */
#define R241_MP1_MODE_MP_ENABLE_IC_1_MASK         0x1
#define R241_MP1_MODE_MP_ENABLE_IC_1_SHIFT        0
#define R241_MP1_MODE_MP_MODE_IC_1_MASK           0xE
#define R241_MP1_MODE_MP_MODE_IC_1_SHIFT          1
#define R241_MP1_MODE_DEBOUNCE_VALUE_IC_1_MASK    0xF0
#define R241_MP1_MODE_DEBOUNCE_VALUE_IC_1_SHIFT   4
#define R241_MP1_MODE_SS_SELECT_IC_1_MASK         0x700
#define R241_MP1_MODE_SS_SELECT_IC_1_SHIFT        8

/* MP2_MODE (IC 1) */
#define R242_MP2_MODE_MP_ENABLE_IC_1              0x0    /* 0b	[0] */
#define R242_MP2_MODE_MP_MODE_IC_1                0x0    /* 000b	[3:1] */
#define R242_MP2_MODE_DEBOUNCE_VALUE_IC_1         0x0    /* 0000b	[7:4] */
#define R242_MP2_MODE_SS_SELECT_IC_1              0x0    /* 000b	[10:8] */
#define R242_MP2_MODE_MP_ENABLE_IC_1_MASK         0x1
#define R242_MP2_MODE_MP_ENABLE_IC_1_SHIFT        0
#define R242_MP2_MODE_MP_MODE_IC_1_MASK           0xE
#define R242_MP2_MODE_MP_MODE_IC_1_SHIFT          1
#define R242_MP2_MODE_DEBOUNCE_VALUE_IC_1_MASK    0xF0
#define R242_MP2_MODE_DEBOUNCE_VALUE_IC_1_SHIFT   4
#define R242_MP2_MODE_SS_SELECT_IC_1_MASK         0x700
#define R242_MP2_MODE_SS_SELECT_IC_1_SHIFT        8

/* MP3_MODE (IC 1) */
#define R243_MP3_MODE_MP_ENABLE_IC_1              0x0    /* 0b	[0] */
#define R243_MP3_MODE_MP_MODE_IC_1                0x0    /* 000b	[3:1] */
#define R243_MP3_MODE_DEBOUNCE_VALUE_IC_1         0x0    /* 0000b	[7:4] */
#define R243_MP3_MODE_SS_SELECT_IC_1              0x0    /* 000b	[10:8] */
#define R243_MP3_MODE_MP_ENABLE_IC_1_MASK         0x1
#define R243_MP3_MODE_MP_ENABLE_IC_1_SHIFT        0
#define R243_MP3_MODE_MP_MODE_IC_1_MASK           0xE
#define R243_MP3_MODE_MP_MODE_IC_1_SHIFT          1
#define R243_MP3_MODE_DEBOUNCE_VALUE_IC_1_MASK    0xF0
#define R243_MP3_MODE_DEBOUNCE_VALUE_IC_1_SHIFT   4
#define R243_MP3_MODE_SS_SELECT_IC_1_MASK         0x700
#define R243_MP3_MODE_SS_SELECT_IC_1_SHIFT        8

/* MP4_MODE (IC 1) */
#define R244_MP4_MODE_MP_ENABLE_IC_1              0x0    /* 0b	[0] */
#define R244_MP4_MODE_MP_MODE_IC_1                0x0    /* 000b	[3:1] */
#define R244_MP4_MODE_DEBOUNCE_VALUE_IC_1         0x0    /* 0000b	[7:4] */
#define R244_MP4_MODE_SS_SELECT_IC_1              0x0    /* 000b	[10:8] */
#define R244_MP4_MODE_MP_ENABLE_IC_1_MASK         0x1
#define R244_MP4_MODE_MP_ENABLE_IC_1_SHIFT        0
#define R244_MP4_MODE_MP_MODE_IC_1_MASK           0xE
#define R244_MP4_MODE_MP_MODE_IC_1_SHIFT          1
#define R244_MP4_MODE_DEBOUNCE_VALUE_IC_1_MASK    0xF0
#define R244_MP4_MODE_DEBOUNCE_VALUE_IC_1_SHIFT   4
#define R244_MP4_MODE_SS_SELECT_IC_1_MASK         0x700
#define R244_MP4_MODE_SS_SELECT_IC_1_SHIFT        8

/* MP5_MODE (IC 1) */
#define R245_MP5_MODE_MP_ENABLE_IC_1              0x0    /* 0b	[0] */
#define R245_MP5_MODE_MP_MODE_IC_1                0x0    /* 000b	[3:1] */
#define R245_MP5_MODE_DEBOUNCE_VALUE_IC_1         0x0    /* 0000b	[7:4] */
#define R245_MP5_MODE_SS_SELECT_IC_1              0x0    /* 000b	[10:8] */
#define R245_MP5_MODE_MP_ENABLE_IC_1_MASK         0x1
#define R245_MP5_MODE_MP_ENABLE_IC_1_SHIFT        0
#define R245_MP5_MODE_MP_MODE_IC_1_MASK           0xE
#define R245_MP5_MODE_MP_MODE_IC_1_SHIFT          1
#define R245_MP5_MODE_DEBOUNCE_VALUE_IC_1_MASK    0xF0
#define R245_MP5_MODE_DEBOUNCE_VALUE_IC_1_SHIFT   4
#define R245_MP5_MODE_SS_SELECT_IC_1_MASK         0x700
#define R245_MP5_MODE_SS_SELECT_IC_1_SHIFT        8

/* MP6_MODE (IC 1) */
#define R246_MP6_MODE_MP_ENABLE_IC_1              0x0    /* 0b	[0] */
#define R246_MP6_MODE_MP_MODE_IC_1                0x0    /* 000b	[3:1] */
#define R246_MP6_MODE_DEBOUNCE_VALUE_IC_1         0x0    /* 0000b	[7:4] */
#define R246_MP6_MODE_SS_SELECT_IC_1              0x0    /* 000b	[10:8] */
#define R246_MP6_MODE_MP_ENABLE_IC_1_MASK         0x1
#define R246_MP6_MODE_MP_ENABLE_IC_1_SHIFT        0
#define R246_MP6_MODE_MP_MODE_IC_1_MASK           0xE
#define R246_MP6_MODE_MP_MODE_IC_1_SHIFT          1
#define R246_MP6_MODE_DEBOUNCE_VALUE_IC_1_MASK    0xF0
#define R246_MP6_MODE_DEBOUNCE_VALUE_IC_1_SHIFT   4
#define R246_MP6_MODE_SS_SELECT_IC_1_MASK         0x700
#define R246_MP6_MODE_SS_SELECT_IC_1_SHIFT        8

/* MP7_MODE (IC 1) */
#define R247_MP7_MODE_MP_ENABLE_IC_1              0x0    /* 0b	[0] */
#define R247_MP7_MODE_MP_MODE_IC_1                0x0    /* 000b	[3:1] */
#define R247_MP7_MODE_DEBOUNCE_VALUE_IC_1         0x0    /* 0000b	[7:4] */
#define R247_MP7_MODE_SS_SELECT_IC_1              0x0    /* 000b	[10:8] */
#define R247_MP7_MODE_MP_ENABLE_IC_1_MASK         0x1
#define R247_MP7_MODE_MP_ENABLE_IC_1_SHIFT        0
#define R247_MP7_MODE_MP_MODE_IC_1_MASK           0xE
#define R247_MP7_MODE_MP_MODE_IC_1_SHIFT          1
#define R247_MP7_MODE_DEBOUNCE_VALUE_IC_1_MASK    0xF0
#define R247_MP7_MODE_DEBOUNCE_VALUE_IC_1_SHIFT   4
#define R247_MP7_MODE_SS_SELECT_IC_1_MASK         0x700
#define R247_MP7_MODE_SS_SELECT_IC_1_SHIFT        8

/* MP8_MODE (IC 1) */
#define R248_MP8_MODE_MP_ENABLE_IC_1              0x0    /* 0b	[0] */
#define R248_MP8_MODE_MP_MODE_IC_1                0x0    /* 000b	[3:1] */
#define R248_MP8_MODE_DEBOUNCE_VALUE_IC_1         0x0    /* 0000b	[7:4] */
#define R248_MP8_MODE_SS_SELECT_IC_1              0x0    /* 000b	[10:8] */
#define R248_MP8_MODE_MP_ENABLE_IC_1_MASK         0x1
#define R248_MP8_MODE_MP_ENABLE_IC_1_SHIFT        0
#define R248_MP8_MODE_MP_MODE_IC_1_MASK           0xE
#define R248_MP8_MODE_MP_MODE_IC_1_SHIFT          1
#define R248_MP8_MODE_DEBOUNCE_VALUE_IC_1_MASK    0xF0
#define R248_MP8_MODE_DEBOUNCE_VALUE_IC_1_SHIFT   4
#define R248_MP8_MODE_SS_SELECT_IC_1_MASK         0x700
#define R248_MP8_MODE_SS_SELECT_IC_1_SHIFT        8

/* MP9_MODE (IC 1) */
#define R249_MP9_MODE_MP_ENABLE_IC_1              0x0    /* 0b	[0] */
#define R249_MP9_MODE_MP_MODE_IC_1                0x0    /* 000b	[3:1] */
#define R249_MP9_MODE_DEBOUNCE_VALUE_IC_1         0x0    /* 0000b	[7:4] */
#define R249_MP9_MODE_SS_SELECT_IC_1              0x0    /* 000b	[10:8] */
#define R249_MP9_MODE_MP_ENABLE_IC_1_MASK         0x1
#define R249_MP9_MODE_MP_ENABLE_IC_1_SHIFT        0
#define R249_MP9_MODE_MP_MODE_IC_1_MASK           0xE
#define R249_MP9_MODE_MP_MODE_IC_1_SHIFT          1
#define R249_MP9_MODE_DEBOUNCE_VALUE_IC_1_MASK    0xF0
#define R249_MP9_MODE_DEBOUNCE_VALUE_IC_1_SHIFT   4
#define R249_MP9_MODE_SS_SELECT_IC_1_MASK         0x700
#define R249_MP9_MODE_SS_SELECT_IC_1_SHIFT        8

/* MP10_MODE (IC 1) */
#define R250_MP10_MODE_MP_ENABLE_IC_1             0x0    /* 0b	[0] */
#define R250_MP10_MODE_MP_MODE_IC_1               0x0    /* 000b	[3:1] */
#define R250_MP10_MODE_DEBOUNCE_VALUE_IC_1        0x0    /* 0000b	[7:4] */
#define R250_MP10_MODE_SS_SELECT_IC_1             0x0    /* 000b	[10:8] */
#define R250_MP10_MODE_MP_ENABLE_IC_1_MASK        0x1
#define R250_MP10_MODE_MP_ENABLE_IC_1_SHIFT       0
#define R250_MP10_MODE_MP_MODE_IC_1_MASK          0xE
#define R250_MP10_MODE_MP_MODE_IC_1_SHIFT         1
#define R250_MP10_MODE_DEBOUNCE_VALUE_IC_1_MASK   0xF0
#define R250_MP10_MODE_DEBOUNCE_VALUE_IC_1_SHIFT  4
#define R250_MP10_MODE_SS_SELECT_IC_1_MASK        0x700
#define R250_MP10_MODE_SS_SELECT_IC_1_SHIFT       8

/* MP11_MODE (IC 1) */
#define R251_MP11_MODE_MP_ENABLE_IC_1             0x0    /* 0b	[0] */
#define R251_MP11_MODE_MP_MODE_IC_1               0x0    /* 000b	[3:1] */
#define R251_MP11_MODE_DEBOUNCE_VALUE_IC_1        0x0    /* 0000b	[7:4] */
#define R251_MP11_MODE_SS_SELECT_IC_1             0x0    /* 000b	[10:8] */
#define R251_MP11_MODE_MP_ENABLE_IC_1_MASK        0x1
#define R251_MP11_MODE_MP_ENABLE_IC_1_SHIFT       0
#define R251_MP11_MODE_MP_MODE_IC_1_MASK          0xE
#define R251_MP11_MODE_MP_MODE_IC_1_SHIFT         1
#define R251_MP11_MODE_DEBOUNCE_VALUE_IC_1_MASK   0xF0
#define R251_MP11_MODE_DEBOUNCE_VALUE_IC_1_SHIFT  4
#define R251_MP11_MODE_SS_SELECT_IC_1_MASK        0x700
#define R251_MP11_MODE_SS_SELECT_IC_1_SHIFT       8

/* MP12_MODE (IC 1) */
#define R252_MP12_MODE_MP_ENABLE_IC_1             0x0    /* 0b	[0] */
#define R252_MP12_MODE_MP_MODE_IC_1               0x0    /* 000b	[3:1] */
#define R252_MP12_MODE_DEBOUNCE_VALUE_IC_1        0x0    /* 0000b	[7:4] */
#define R252_MP12_MODE_SS_SELECT_IC_1             0x0    /* 000b	[10:8] */
#define R252_MP12_MODE_MP_ENABLE_IC_1_MASK        0x1
#define R252_MP12_MODE_MP_ENABLE_IC_1_SHIFT       0
#define R252_MP12_MODE_MP_MODE_IC_1_MASK          0xE
#define R252_MP12_MODE_MP_MODE_IC_1_SHIFT         1
#define R252_MP12_MODE_DEBOUNCE_VALUE_IC_1_MASK   0xF0
#define R252_MP12_MODE_DEBOUNCE_VALUE_IC_1_SHIFT  4
#define R252_MP12_MODE_SS_SELECT_IC_1_MASK        0x700
#define R252_MP12_MODE_SS_SELECT_IC_1_SHIFT       8

/* MP13_MODE (IC 1) */
#define R253_MP13_MODE_MP_ENABLE_IC_1             0x0    /* 0b	[0] */
#define R253_MP13_MODE_MP_MODE_IC_1               0x0    /* 000b	[3:1] */
#define R253_MP13_MODE_DEBOUNCE_VALUE_IC_1        0x0    /* 0000b	[7:4] */
#define R253_MP13_MODE_SS_SELECT_IC_1             0x0    /* 000b	[10:8] */
#define R253_MP13_MODE_MP_ENABLE_IC_1_MASK        0x1
#define R253_MP13_MODE_MP_ENABLE_IC_1_SHIFT       0
#define R253_MP13_MODE_MP_MODE_IC_1_MASK          0xE
#define R253_MP13_MODE_MP_MODE_IC_1_SHIFT         1
#define R253_MP13_MODE_DEBOUNCE_VALUE_IC_1_MASK   0xF0
#define R253_MP13_MODE_DEBOUNCE_VALUE_IC_1_SHIFT  4
#define R253_MP13_MODE_SS_SELECT_IC_1_MASK        0x700
#define R253_MP13_MODE_SS_SELECT_IC_1_SHIFT       8

/* MP0_WRITE (IC 1) */
#define R254_MP0_WRITE_MP_REG_WRITE_IC_1          0x0    /* 0b	[0] */
#define R254_MP0_WRITE_MP_REG_WRITE_IC_1_MASK     0x1
#define R254_MP0_WRITE_MP_REG_WRITE_IC_1_SHIFT    0

/* MP1_WRITE (IC 1) */
#define R255_MP1_WRITE_MP_REG_WRITE_IC_1          0x0    /* 0b	[0] */
#define R255_MP1_WRITE_MP_REG_WRITE_IC_1_MASK     0x1
#define R255_MP1_WRITE_MP_REG_WRITE_IC_1_SHIFT    0

/* MP2_WRITE (IC 1) */
#define R256_MP2_WRITE_MP_REG_WRITE_IC_1          0x0    /* 0b	[0] */
#define R256_MP2_WRITE_MP_REG_WRITE_IC_1_MASK     0x1
#define R256_MP2_WRITE_MP_REG_WRITE_IC_1_SHIFT    0

/* MP3_WRITE (IC 1) */
#define R257_MP3_WRITE_MP_REG_WRITE_IC_1          0x0    /* 0b	[0] */
#define R257_MP3_WRITE_MP_REG_WRITE_IC_1_MASK     0x1
#define R257_MP3_WRITE_MP_REG_WRITE_IC_1_SHIFT    0

/* MP4_WRITE (IC 1) */
#define R258_MP4_WRITE_MP_REG_WRITE_IC_1          0x0    /* 0b	[0] */
#define R258_MP4_WRITE_MP_REG_WRITE_IC_1_MASK     0x1
#define R258_MP4_WRITE_MP_REG_WRITE_IC_1_SHIFT    0

/* MP5_WRITE (IC 1) */
#define R259_MP5_WRITE_MP_REG_WRITE_IC_1          0x0    /* 0b	[0] */
#define R259_MP5_WRITE_MP_REG_WRITE_IC_1_MASK     0x1
#define R259_MP5_WRITE_MP_REG_WRITE_IC_1_SHIFT    0

/* MP6_WRITE (IC 1) */
#define R260_MP6_WRITE_MP_REG_WRITE_IC_1          0x0    /* 0b	[0] */
#define R260_MP6_WRITE_MP_REG_WRITE_IC_1_MASK     0x1
#define R260_MP6_WRITE_MP_REG_WRITE_IC_1_SHIFT    0

/* MP7_WRITE (IC 1) */
#define R261_MP7_WRITE_MP_REG_WRITE_IC_1          0x0    /* 0b	[0] */
#define R261_MP7_WRITE_MP_REG_WRITE_IC_1_MASK     0x1
#define R261_MP7_WRITE_MP_REG_WRITE_IC_1_SHIFT    0

/* MP8_WRITE (IC 1) */
#define R262_MP8_WRITE_MP_REG_WRITE_IC_1          0x0    /* 0b	[0] */
#define R262_MP8_WRITE_MP_REG_WRITE_IC_1_MASK     0x1
#define R262_MP8_WRITE_MP_REG_WRITE_IC_1_SHIFT    0

/* MP9_WRITE (IC 1) */
#define R263_MP9_WRITE_MP_REG_WRITE_IC_1          0x0    /* 0b	[0] */
#define R263_MP9_WRITE_MP_REG_WRITE_IC_1_MASK     0x1
#define R263_MP9_WRITE_MP_REG_WRITE_IC_1_SHIFT    0

/* MP10_WRITE (IC 1) */
#define R264_MP10_WRITE_MP_REG_WRITE_IC_1         0x0    /* 0b	[0] */
#define R264_MP10_WRITE_MP_REG_WRITE_IC_1_MASK    0x1
#define R264_MP10_WRITE_MP_REG_WRITE_IC_1_SHIFT   0

/* MP11_WRITE (IC 1) */
#define R265_MP11_WRITE_MP_REG_WRITE_IC_1         0x0    /* 0b	[0] */
#define R265_MP11_WRITE_MP_REG_WRITE_IC_1_MASK    0x1
#define R265_MP11_WRITE_MP_REG_WRITE_IC_1_SHIFT   0

/* MP12_WRITE (IC 1) */
#define R266_MP12_WRITE_MP_REG_WRITE_IC_1         0x0    /* 0b	[0] */
#define R266_MP12_WRITE_MP_REG_WRITE_IC_1_MASK    0x1
#define R266_MP12_WRITE_MP_REG_WRITE_IC_1_SHIFT   0

/* MP13_WRITE (IC 1) */
#define R267_MP13_WRITE_MP_REG_WRITE_IC_1         0x0    /* 0b	[0] */
#define R267_MP13_WRITE_MP_REG_WRITE_IC_1_MASK    0x1
#define R267_MP13_WRITE_MP_REG_WRITE_IC_1_SHIFT   0

/* MP0_READ (IC 1) */
#define R268_MP0_READ_MP_REG_READ_IC_1            0x1    /* 1b	[0] */
#define R268_MP0_READ_MP_REG_READ_IC_1_MASK       0x1
#define R268_MP0_READ_MP_REG_READ_IC_1_SHIFT      0

/* MP1_READ (IC 1) */
#define R269_MP1_READ_MP_REG_READ_IC_1            0x0    /* 0b	[0] */
#define R269_MP1_READ_MP_REG_READ_IC_1_MASK       0x1
#define R269_MP1_READ_MP_REG_READ_IC_1_SHIFT      0

/* MP2_READ (IC 1) */
#define R270_MP2_READ_MP_REG_READ_IC_1            0x0    /* 0b	[0] */
#define R270_MP2_READ_MP_REG_READ_IC_1_MASK       0x1
#define R270_MP2_READ_MP_REG_READ_IC_1_SHIFT      0

/* MP3_READ (IC 1) */
#define R271_MP3_READ_MP_REG_READ_IC_1            0x0    /* 0b	[0] */
#define R271_MP3_READ_MP_REG_READ_IC_1_MASK       0x1
#define R271_MP3_READ_MP_REG_READ_IC_1_SHIFT      0

/* MP4_READ (IC 1) */
#define R272_MP4_READ_MP_REG_READ_IC_1            0x0    /* 0b	[0] */
#define R272_MP4_READ_MP_REG_READ_IC_1_MASK       0x1
#define R272_MP4_READ_MP_REG_READ_IC_1_SHIFT      0

/* MP5_READ (IC 1) */
#define R273_MP5_READ_MP_REG_READ_IC_1            0x0    /* 0b	[0] */
#define R273_MP5_READ_MP_REG_READ_IC_1_MASK       0x1
#define R273_MP5_READ_MP_REG_READ_IC_1_SHIFT      0

/* MP6_READ (IC 1) */
#define R274_MP6_READ_MP_REG_READ_IC_1            0x0    /* 0b	[0] */
#define R274_MP6_READ_MP_REG_READ_IC_1_MASK       0x1
#define R274_MP6_READ_MP_REG_READ_IC_1_SHIFT      0

/* MP7_READ (IC 1) */
#define R275_MP7_READ_MP_REG_READ_IC_1            0x0    /* 0b	[0] */
#define R275_MP7_READ_MP_REG_READ_IC_1_MASK       0x1
#define R275_MP7_READ_MP_REG_READ_IC_1_SHIFT      0

/* MP8_READ (IC 1) */
#define R276_MP8_READ_MP_REG_READ_IC_1            0x0    /* 0b	[0] */
#define R276_MP8_READ_MP_REG_READ_IC_1_MASK       0x1
#define R276_MP8_READ_MP_REG_READ_IC_1_SHIFT      0

/* MP9_READ (IC 1) */
#define R277_MP9_READ_MP_REG_READ_IC_1            0x0    /* 0b	[0] */
#define R277_MP9_READ_MP_REG_READ_IC_1_MASK       0x1
#define R277_MP9_READ_MP_REG_READ_IC_1_SHIFT      0

/* MP10_READ (IC 1) */
#define R278_MP10_READ_MP_REG_READ_IC_1           0x0    /* 0b	[0] */
#define R278_MP10_READ_MP_REG_READ_IC_1_MASK      0x1
#define R278_MP10_READ_MP_REG_READ_IC_1_SHIFT     0

/* MP11_READ (IC 1) */
#define R279_MP11_READ_MP_REG_READ_IC_1           0x0    /* 0b	[0] */
#define R279_MP11_READ_MP_REG_READ_IC_1_MASK      0x1
#define R279_MP11_READ_MP_REG_READ_IC_1_SHIFT     0

/* MP12_READ (IC 1) */
#define R280_MP12_READ_MP_REG_READ_IC_1           0x0    /* 0b	[0] */
#define R280_MP12_READ_MP_REG_READ_IC_1_MASK      0x1
#define R280_MP12_READ_MP_REG_READ_IC_1_SHIFT     0

/* MP13_READ (IC 1) */
#define R281_MP13_READ_MP_REG_READ_IC_1           0x0    /* 0b	[0] */
#define R281_MP13_READ_MP_REG_READ_IC_1_MASK      0x1
#define R281_MP13_READ_MP_REG_READ_IC_1_SHIFT     0

/* DMIC_CTRL0 (IC 1) */
#define R282_DMIC_CTRL0_DMIC_EN_IC_1              0x0    /* 0b	[0] */
#define R282_DMIC_CTRL0_DMSW_IC_1                 0x0    /* 0b	[1] */
#define R282_DMIC_CTRL0_DMPOL_IC_1                0x0    /* 0b	[2] */
#define R282_DMIC_CTRL0_HPF_IC_1                  0x0    /* 0b	[3] */
#define R282_DMIC_CTRL0_DMIC_CLK_IC_1             0x0    /* 000b	[6:4] */
#define R282_DMIC_CTRL0_MIC_DATA_SRC_IC_1         0x0    /* 0000b	[11:8] */
#define R282_DMIC_CTRL0_CUTOFF_IC_1               0x4    /* 100b	[14:12] */
#define R282_DMIC_CTRL0_DMIC_EN_IC_1_MASK         0x1
#define R282_DMIC_CTRL0_DMIC_EN_IC_1_SHIFT        0
#define R282_DMIC_CTRL0_DMSW_IC_1_MASK            0x2
#define R282_DMIC_CTRL0_DMSW_IC_1_SHIFT           1
#define R282_DMIC_CTRL0_DMPOL_IC_1_MASK           0x4
#define R282_DMIC_CTRL0_DMPOL_IC_1_SHIFT          2
#define R282_DMIC_CTRL0_HPF_IC_1_MASK             0x8
#define R282_DMIC_CTRL0_HPF_IC_1_SHIFT            3
#define R282_DMIC_CTRL0_DMIC_CLK_IC_1_MASK        0x70
#define R282_DMIC_CTRL0_DMIC_CLK_IC_1_SHIFT       4
#define R282_DMIC_CTRL0_MIC_DATA_SRC_IC_1_MASK    0xF00
#define R282_DMIC_CTRL0_MIC_DATA_SRC_IC_1_SHIFT   8
#define R282_DMIC_CTRL0_CUTOFF_IC_1_MASK          0x7000
#define R282_DMIC_CTRL0_CUTOFF_IC_1_SHIFT         12

/* DMIC_CTRL1 (IC 1) */
#define R283_DMIC_CTRL1_DMIC_EN_IC_1              0x0    /* 0b	[0] */
#define R283_DMIC_CTRL1_DMSW_IC_1                 0x0    /* 0b	[1] */
#define R283_DMIC_CTRL1_DMPOL_IC_1                0x0    /* 0b	[2] */
#define R283_DMIC_CTRL1_HPF_IC_1                  0x0    /* 0b	[3] */
#define R283_DMIC_CTRL1_DMIC_CLK_IC_1             0x0    /* 000b	[6:4] */
#define R283_DMIC_CTRL1_MIC_DATA_SRC_IC_1         0x0    /* 0000b	[11:8] */
#define R283_DMIC_CTRL1_CUTOFF_IC_1               0x4    /* 100b	[14:12] */
#define R283_DMIC_CTRL1_DMIC_EN_IC_1_MASK         0x1
#define R283_DMIC_CTRL1_DMIC_EN_IC_1_SHIFT        0
#define R283_DMIC_CTRL1_DMSW_IC_1_MASK            0x2
#define R283_DMIC_CTRL1_DMSW_IC_1_SHIFT           1
#define R283_DMIC_CTRL1_DMPOL_IC_1_MASK           0x4
#define R283_DMIC_CTRL1_DMPOL_IC_1_SHIFT          2
#define R283_DMIC_CTRL1_HPF_IC_1_MASK             0x8
#define R283_DMIC_CTRL1_HPF_IC_1_SHIFT            3
#define R283_DMIC_CTRL1_DMIC_CLK_IC_1_MASK        0x70
#define R283_DMIC_CTRL1_DMIC_CLK_IC_1_SHIFT       4
#define R283_DMIC_CTRL1_MIC_DATA_SRC_IC_1_MASK    0xF00
#define R283_DMIC_CTRL1_MIC_DATA_SRC_IC_1_SHIFT   8
#define R283_DMIC_CTRL1_CUTOFF_IC_1_MASK          0x7000
#define R283_DMIC_CTRL1_CUTOFF_IC_1_SHIFT         12

/* ASRC_LOCK (IC 1) */
#define R284_ASRC_LOCK_ASRC0L_IC_1                0x1    /* 1b	[0] */
#define R284_ASRC_LOCK_ASRC1L_IC_1                0x0    /* 0b	[1] */
#define R284_ASRC_LOCK_ASRC2L_IC_1                0x0    /* 0b	[2] */
#define R284_ASRC_LOCK_ASRC3L_IC_1                0x0    /* 0b	[3] */
#define R284_ASRC_LOCK_ASRC4L_IC_1                0x0    /* 0b	[4] */
#define R284_ASRC_LOCK_ASRC5L_IC_1                0x0    /* 0b	[5] */
#define R284_ASRC_LOCK_ASRC6L_IC_1                0x0    /* 0b	[6] */
#define R284_ASRC_LOCK_ASRC7L_IC_1                0x0    /* 0b	[7] */
#define R284_ASRC_LOCK_ASRC0L_IC_1_MASK           0x1
#define R284_ASRC_LOCK_ASRC0L_IC_1_SHIFT          0
#define R284_ASRC_LOCK_ASRC1L_IC_1_MASK           0x2
#define R284_ASRC_LOCK_ASRC1L_IC_1_SHIFT          1
#define R284_ASRC_LOCK_ASRC2L_IC_1_MASK           0x4
#define R284_ASRC_LOCK_ASRC2L_IC_1_SHIFT          2
#define R284_ASRC_LOCK_ASRC3L_IC_1_MASK           0x8
#define R284_ASRC_LOCK_ASRC3L_IC_1_SHIFT          3
#define R284_ASRC_LOCK_ASRC4L_IC_1_MASK           0x10
#define R284_ASRC_LOCK_ASRC4L_IC_1_SHIFT          4
#define R284_ASRC_LOCK_ASRC5L_IC_1_MASK           0x20
#define R284_ASRC_LOCK_ASRC5L_IC_1_SHIFT          5
#define R284_ASRC_LOCK_ASRC6L_IC_1_MASK           0x40
#define R284_ASRC_LOCK_ASRC6L_IC_1_SHIFT          6
#define R284_ASRC_LOCK_ASRC7L_IC_1_MASK           0x80
#define R284_ASRC_LOCK_ASRC7L_IC_1_SHIFT          7

/* ASRC_MUTE (IC 1) */
#define R285_ASRC_MUTE_ASRC0M_IC_1                0x0    /* 0b	[0] */
#define R285_ASRC_MUTE_ASRC1M_IC_1                0x0    /* 0b	[1] */
#define R285_ASRC_MUTE_ASRC2M_IC_1                0x0    /* 0b	[2] */
#define R285_ASRC_MUTE_ASRC3M_IC_1                0x0    /* 0b	[3] */
#define R285_ASRC_MUTE_ASRC4M_IC_1                0x0    /* 0b	[4] */
#define R285_ASRC_MUTE_ASRC5M_IC_1                0x0    /* 0b	[5] */
#define R285_ASRC_MUTE_ASRC6M_IC_1                0x0    /* 0b	[6] */
#define R285_ASRC_MUTE_ASRC7M_IC_1                0x0    /* 0b	[7] */
#define R285_ASRC_MUTE_ASRC_RAMP0_IC_1            0x0    /* 0b	[8] */
#define R285_ASRC_MUTE_ASRC_RAMP1_IC_1            0x0    /* 0b	[9] */
#define R285_ASRC_MUTE_LOCKMUTE_IC_1              0x0    /* 0b	[10] */
#define R285_ASRC_MUTE_ASRC0M_IC_1_MASK           0x1
#define R285_ASRC_MUTE_ASRC0M_IC_1_SHIFT          0
#define R285_ASRC_MUTE_ASRC1M_IC_1_MASK           0x2
#define R285_ASRC_MUTE_ASRC1M_IC_1_SHIFT          1
#define R285_ASRC_MUTE_ASRC2M_IC_1_MASK           0x4
#define R285_ASRC_MUTE_ASRC2M_IC_1_SHIFT          2
#define R285_ASRC_MUTE_ASRC3M_IC_1_MASK           0x8
#define R285_ASRC_MUTE_ASRC3M_IC_1_SHIFT          3
#define R285_ASRC_MUTE_ASRC4M_IC_1_MASK           0x10
#define R285_ASRC_MUTE_ASRC4M_IC_1_SHIFT          4
#define R285_ASRC_MUTE_ASRC5M_IC_1_MASK           0x20
#define R285_ASRC_MUTE_ASRC5M_IC_1_SHIFT          5
#define R285_ASRC_MUTE_ASRC6M_IC_1_MASK           0x40
#define R285_ASRC_MUTE_ASRC6M_IC_1_SHIFT          6
#define R285_ASRC_MUTE_ASRC7M_IC_1_MASK           0x80
#define R285_ASRC_MUTE_ASRC7M_IC_1_SHIFT          7
#define R285_ASRC_MUTE_ASRC_RAMP0_IC_1_MASK       0x100
#define R285_ASRC_MUTE_ASRC_RAMP0_IC_1_SHIFT      8
#define R285_ASRC_MUTE_ASRC_RAMP1_IC_1_MASK       0x200
#define R285_ASRC_MUTE_ASRC_RAMP1_IC_1_SHIFT      9
#define R285_ASRC_MUTE_LOCKMUTE_IC_1_MASK         0x400
#define R285_ASRC_MUTE_LOCKMUTE_IC_1_SHIFT        10

/* ASRC0_RATIO (IC 1) */
#define R286_ASRC0_RATIO_ASRC_RATIO_IC_1          0x1000 /* 0001000000000000b	[15:0] */
#define R286_ASRC0_RATIO_ASRC_RATIO_IC_1_MASK     0xFFFF
#define R286_ASRC0_RATIO_ASRC_RATIO_IC_1_SHIFT    0

/* ASRC1_RATIO (IC 1) */
#define R287_ASRC1_RATIO_ASRC_RATIO_IC_1          0x0000 /* 0000000000000000b	[15:0] */
#define R287_ASRC1_RATIO_ASRC_RATIO_IC_1_MASK     0xFFFF
#define R287_ASRC1_RATIO_ASRC_RATIO_IC_1_SHIFT    0

/* ASRC2_RATIO (IC 1) */
#define R288_ASRC2_RATIO_ASRC_RATIO_IC_1          0x0000 /* 0000000000000000b	[15:0] */
#define R288_ASRC2_RATIO_ASRC_RATIO_IC_1_MASK     0xFFFF
#define R288_ASRC2_RATIO_ASRC_RATIO_IC_1_SHIFT    0

/* ASRC3_RATIO (IC 1) */
#define R289_ASRC3_RATIO_ASRC_RATIO_IC_1          0x0000 /* 0000000000000000b	[15:0] */
#define R289_ASRC3_RATIO_ASRC_RATIO_IC_1_MASK     0xFFFF
#define R289_ASRC3_RATIO_ASRC_RATIO_IC_1_SHIFT    0

/* ASRC4_RATIO (IC 1) */
#define R290_ASRC4_RATIO_ASRC_RATIO_IC_1          0x0000 /* 0000000000000000b	[15:0] */
#define R290_ASRC4_RATIO_ASRC_RATIO_IC_1_MASK     0xFFFF
#define R290_ASRC4_RATIO_ASRC_RATIO_IC_1_SHIFT    0

/* ASRC5_RATIO (IC 1) */
#define R291_ASRC5_RATIO_ASRC_RATIO_IC_1          0x0000 /* 0000000000000000b	[15:0] */
#define R291_ASRC5_RATIO_ASRC_RATIO_IC_1_MASK     0xFFFF
#define R291_ASRC5_RATIO_ASRC_RATIO_IC_1_SHIFT    0

/* ASRC6_RATIO (IC 1) */
#define R292_ASRC6_RATIO_ASRC_RATIO_IC_1          0x0000 /* 0000000000000000b	[15:0] */
#define R292_ASRC6_RATIO_ASRC_RATIO_IC_1_MASK     0xFFFF
#define R292_ASRC6_RATIO_ASRC_RATIO_IC_1_SHIFT    0

/* ASRC7_RATIO (IC 1) */
#define R293_ASRC7_RATIO_ASRC_RATIO_IC_1          0x0000 /* 0000000000000000b	[15:0] */
#define R293_ASRC7_RATIO_ASRC_RATIO_IC_1_MASK     0xFFFF
#define R293_ASRC7_RATIO_ASRC_RATIO_IC_1_SHIFT    0

/* ADC_READ0 (IC 1) */
#define R294_ADC_READ0_ADC_VALUE_IC_1             0x0026 /* 0000000000100110b	[15:0] */
#define R294_ADC_READ0_ADC_VALUE_IC_1_MASK        0xFFFF
#define R294_ADC_READ0_ADC_VALUE_IC_1_SHIFT       0

/* ADC_READ1 (IC 1) */
#define R295_ADC_READ1_ADC_VALUE_IC_1             0x0039 /* 0000000000111001b	[15:0] */
#define R295_ADC_READ1_ADC_VALUE_IC_1_MASK        0xFFFF
#define R295_ADC_READ1_ADC_VALUE_IC_1_SHIFT       0

/* ADC_READ2 (IC 1) */
#define R296_ADC_READ2_ADC_VALUE_IC_1             0x00EA /* 0000000011101010b	[15:0] */
#define R296_ADC_READ2_ADC_VALUE_IC_1_MASK        0xFFFF
#define R296_ADC_READ2_ADC_VALUE_IC_1_SHIFT       0

/* ADC_READ3 (IC 1) */
#define R297_ADC_READ3_ADC_VALUE_IC_1             0x00BC /* 0000000010111100b	[15:0] */
#define R297_ADC_READ3_ADC_VALUE_IC_1_MASK        0xFFFF
#define R297_ADC_READ3_ADC_VALUE_IC_1_SHIFT       0

/* ADC_READ4 (IC 1) */
#define R298_ADC_READ4_ADC_VALUE_IC_1             0x011D /* 0000000100011101b	[15:0] */
#define R298_ADC_READ4_ADC_VALUE_IC_1_MASK        0xFFFF
#define R298_ADC_READ4_ADC_VALUE_IC_1_SHIFT       0

/* ADC_READ5 (IC 1) */
#define R299_ADC_READ5_ADC_VALUE_IC_1             0x00E9 /* 0000000011101001b	[15:0] */
#define R299_ADC_READ5_ADC_VALUE_IC_1_MASK        0xFFFF
#define R299_ADC_READ5_ADC_VALUE_IC_1_SHIFT       0

/* SPDIF_LOCK_DET (IC 1) */
#define R300_SPDIF_LOCK_DET_LOCK_IC_1             0x1    /* 1b	[0] */
#define R300_SPDIF_LOCK_DET_LOCK_IC_1_MASK        0x1
#define R300_SPDIF_LOCK_DET_LOCK_IC_1_SHIFT       0

/* SPDIF_RX_CTRL (IC 1) */
#define R301_SPDIF_RX_CTRL_RX_LENGTHCTRL_IC_1     0x3    /* 11b	[1:0] */
#define R301_SPDIF_RX_CTRL_FSOUTSTRENGTH_IC_1     0x0    /* 0b	[2] */
#define R301_SPDIF_RX_CTRL_FASTLOCK_IC_1          0x0    /* 0b	[3] */
#define R301_SPDIF_RX_CTRL_RX_LENGTHCTRL_IC_1_MASK 0x3
#define R301_SPDIF_RX_CTRL_RX_LENGTHCTRL_IC_1_SHIFT 0
#define R301_SPDIF_RX_CTRL_FSOUTSTRENGTH_IC_1_MASK 0x4
#define R301_SPDIF_RX_CTRL_FSOUTSTRENGTH_IC_1_SHIFT 2
#define R301_SPDIF_RX_CTRL_FASTLOCK_IC_1_MASK     0x8
#define R301_SPDIF_RX_CTRL_FASTLOCK_IC_1_SHIFT    3

/* SPDIF_RX_DECODE (IC 1) */
#define R302_SPDIF_RX_DECODE_AUDIO_TYPE_IC_1      0x0    /* 0b	[0] */
#define R302_SPDIF_RX_DECODE_COMPR_TYPE_IC_1      0x0    /* 0b	[1] */
#define R302_SPDIF_RX_DECODE_RX_WORDLENGTH_L_IC_1 0xB    /* 1011b	[5:2] */
#define R302_SPDIF_RX_DECODE_RX_WORDLENGTH_R_IC_1 0xB    /* 1011b	[9:6] */
#define R302_SPDIF_RX_DECODE_AUDIO_TYPE_IC_1_MASK 0x1
#define R302_SPDIF_RX_DECODE_AUDIO_TYPE_IC_1_SHIFT 0
#define R302_SPDIF_RX_DECODE_COMPR_TYPE_IC_1_MASK 0x2
#define R302_SPDIF_RX_DECODE_COMPR_TYPE_IC_1_SHIFT 1
#define R302_SPDIF_RX_DECODE_RX_WORDLENGTH_L_IC_1_MASK 0x3C
#define R302_SPDIF_RX_DECODE_RX_WORDLENGTH_L_IC_1_SHIFT 2
#define R302_SPDIF_RX_DECODE_RX_WORDLENGTH_R_IC_1_MASK 0x3C0
#define R302_SPDIF_RX_DECODE_RX_WORDLENGTH_R_IC_1_SHIFT 6

/* SPDIF_RX_COMPRMODE (IC 1) */
#define R303_SPDIF_RX_COMPRMODE_COMPR_MODE_IC_1   0x0000 /* 0000000000000000b	[15:0] */
#define R303_SPDIF_RX_COMPRMODE_COMPR_MODE_IC_1_MASK 0xFFFF
#define R303_SPDIF_RX_COMPRMODE_COMPR_MODE_IC_1_SHIFT 0

/* SPDIF_RESTART (IC 1) */
#define R304_SPDIF_RESTART_RESTART_AUDIO_IC_1     0x1    /* 1b	[0] */
#define R304_SPDIF_RESTART_RESTART_AUDIO_IC_1_MASK 0x1
#define R304_SPDIF_RESTART_RESTART_AUDIO_IC_1_SHIFT 0

/* SPDIF_LOSS_OF_LOCK (IC 1) */
#define R305_SPDIF_LOSS_OF_LOCK_LOSS_OF_LOCK_IC_1 0x0    /* 0b	[0] */
#define R305_SPDIF_LOSS_OF_LOCK_LOSS_OF_LOCK_IC_1_MASK 0x1
#define R305_SPDIF_LOSS_OF_LOCK_LOSS_OF_LOCK_IC_1_SHIFT 0

/* SPDIF_AUX_EN (IC 1) */
#define R306_SPDIF_AUX_EN_TDMOUT_IC_1             0x0    /* 0000b	[3:0] */
#define R306_SPDIF_AUX_EN_TDMOUT_CLK_IC_1         0x0    /* 0b	[4] */
#define R306_SPDIF_AUX_EN_TDMOUT_IC_1_MASK        0xF
#define R306_SPDIF_AUX_EN_TDMOUT_IC_1_SHIFT       0
#define R306_SPDIF_AUX_EN_TDMOUT_CLK_IC_1_MASK    0x10
#define R306_SPDIF_AUX_EN_TDMOUT_CLK_IC_1_SHIFT   4

/* SPDIF_RX_AUXBIT_READY (IC 1) */
#define R307_SPDIF_RX_AUXBIT_READY_AUXBITS_READY_IC_1 0x1 /* 1b	[0] */
#define R307_SPDIF_RX_AUXBIT_READY_AUXBITS_READY_IC_1_MASK 0x1
#define R307_SPDIF_RX_AUXBIT_READY_AUXBITS_READY_IC_1_SHIFT 0

/* SPDIF_RX_CS_LEFT_0 (IC 1) */
#define R308_SPDIF_RX_CS_LEFT_0_SPDIF_RX_CS_LEFT_IC_1 0x0000 /* 0000000000000000b	[15:0] */
#define R308_SPDIF_RX_CS_LEFT_0_SPDIF_RX_CS_LEFT_IC_1_MASK 0xFFFF
#define R308_SPDIF_RX_CS_LEFT_0_SPDIF_RX_CS_LEFT_IC_1_SHIFT 0

/* SPDIF_RX_CS_LEFT_1 (IC 1) */
#define R309_SPDIF_RX_CS_LEFT_1_SPDIF_RX_CS_LEFT_IC_1 0x0000 /* 0000000000000000b	[15:0] */
#define R309_SPDIF_RX_CS_LEFT_1_SPDIF_RX_CS_LEFT_IC_1_MASK 0xFFFF
#define R309_SPDIF_RX_CS_LEFT_1_SPDIF_RX_CS_LEFT_IC_1_SHIFT 0

/* SPDIF_RX_CS_LEFT_2 (IC 1) */
#define R310_SPDIF_RX_CS_LEFT_2_SPDIF_RX_CS_LEFT_IC_1 0x0000 /* 0000000000000000b	[15:0] */
#define R310_SPDIF_RX_CS_LEFT_2_SPDIF_RX_CS_LEFT_IC_1_MASK 0xFFFF
#define R310_SPDIF_RX_CS_LEFT_2_SPDIF_RX_CS_LEFT_IC_1_SHIFT 0

/* SPDIF_RX_CS_LEFT_3 (IC 1) */
#define R311_SPDIF_RX_CS_LEFT_3_SPDIF_RX_CS_LEFT_IC_1 0x0000 /* 0000000000000000b	[15:0] */
#define R311_SPDIF_RX_CS_LEFT_3_SPDIF_RX_CS_LEFT_IC_1_MASK 0xFFFF
#define R311_SPDIF_RX_CS_LEFT_3_SPDIF_RX_CS_LEFT_IC_1_SHIFT 0

/* SPDIF_RX_CS_LEFT_4 (IC 1) */
#define R312_SPDIF_RX_CS_LEFT_4_SPDIF_RX_CS_LEFT_IC_1 0x0000 /* 0000000000000000b	[15:0] */
#define R312_SPDIF_RX_CS_LEFT_4_SPDIF_RX_CS_LEFT_IC_1_MASK 0xFFFF
#define R312_SPDIF_RX_CS_LEFT_4_SPDIF_RX_CS_LEFT_IC_1_SHIFT 0

/* SPDIF_RX_CS_LEFT_5 (IC 1) */
#define R313_SPDIF_RX_CS_LEFT_5_SPDIF_RX_CS_LEFT_IC_1 0x0000 /* 0000000000000000b	[15:0] */
#define R313_SPDIF_RX_CS_LEFT_5_SPDIF_RX_CS_LEFT_IC_1_MASK 0xFFFF
#define R313_SPDIF_RX_CS_LEFT_5_SPDIF_RX_CS_LEFT_IC_1_SHIFT 0

/* SPDIF_RX_CS_LEFT_6 (IC 1) */
#define R314_SPDIF_RX_CS_LEFT_6_SPDIF_RX_CS_LEFT_IC_1 0x0000 /* 0000000000000000b	[15:0] */
#define R314_SPDIF_RX_CS_LEFT_6_SPDIF_RX_CS_LEFT_IC_1_MASK 0xFFFF
#define R314_SPDIF_RX_CS_LEFT_6_SPDIF_RX_CS_LEFT_IC_1_SHIFT 0

/* SPDIF_RX_CS_LEFT_7 (IC 1) */
#define R315_SPDIF_RX_CS_LEFT_7_SPDIF_RX_CS_LEFT_IC_1 0x0000 /* 0000000000000000b	[15:0] */
#define R315_SPDIF_RX_CS_LEFT_7_SPDIF_RX_CS_LEFT_IC_1_MASK 0xFFFF
#define R315_SPDIF_RX_CS_LEFT_7_SPDIF_RX_CS_LEFT_IC_1_SHIFT 0

/* SPDIF_RX_CS_LEFT_8 (IC 1) */
#define R316_SPDIF_RX_CS_LEFT_8_SPDIF_RX_CS_LEFT_IC_1 0x0000 /* 0000000000000000b	[15:0] */
#define R316_SPDIF_RX_CS_LEFT_8_SPDIF_RX_CS_LEFT_IC_1_MASK 0xFFFF
#define R316_SPDIF_RX_CS_LEFT_8_SPDIF_RX_CS_LEFT_IC_1_SHIFT 0

/* SPDIF_RX_CS_LEFT_9 (IC 1) */
#define R317_SPDIF_RX_CS_LEFT_9_SPDIF_RX_CS_LEFT_IC_1 0x000B /* 0000000000001011b	[15:0] */
#define R317_SPDIF_RX_CS_LEFT_9_SPDIF_RX_CS_LEFT_IC_1_MASK 0xFFFF
#define R317_SPDIF_RX_CS_LEFT_9_SPDIF_RX_CS_LEFT_IC_1_SHIFT 0

/* SPDIF_RX_CS_LEFT_10 (IC 1) */
#define R318_SPDIF_RX_CS_LEFT_10_SPDIF_RX_CS_LEFT_IC_1 0x0210 /* 0000001000010000b	[15:0] */
#define R318_SPDIF_RX_CS_LEFT_10_SPDIF_RX_CS_LEFT_IC_1_MASK 0xFFFF
#define R318_SPDIF_RX_CS_LEFT_10_SPDIF_RX_CS_LEFT_IC_1_SHIFT 0

/* SPDIF_RX_CS_LEFT_11 (IC 1) */
#define R319_SPDIF_RX_CS_LEFT_11_SPDIF_RX_CS_LEFT_IC_1 0x7A04 /* 0111101000000100b	[15:0] */
#define R319_SPDIF_RX_CS_LEFT_11_SPDIF_RX_CS_LEFT_IC_1_MASK 0xFFFF
#define R319_SPDIF_RX_CS_LEFT_11_SPDIF_RX_CS_LEFT_IC_1_SHIFT 0

/* SPDIF_RX_CS_RIGHT_0 (IC 1) */
#define R320_SPDIF_RX_CS_RIGHT_0_SPDIF_RX_CS_RIGHT_IC_1 0x0000 /* 0000000000000000b	[15:0] */
#define R320_SPDIF_RX_CS_RIGHT_0_SPDIF_RX_CS_RIGHT_IC_1_MASK 0xFFFF
#define R320_SPDIF_RX_CS_RIGHT_0_SPDIF_RX_CS_RIGHT_IC_1_SHIFT 0

/* SPDIF_RX_CS_RIGHT_1 (IC 1) */
#define R321_SPDIF_RX_CS_RIGHT_1_SPDIF_RX_CS_RIGHT_IC_1 0x0000 /* 0000000000000000b	[15:0] */
#define R321_SPDIF_RX_CS_RIGHT_1_SPDIF_RX_CS_RIGHT_IC_1_MASK 0xFFFF
#define R321_SPDIF_RX_CS_RIGHT_1_SPDIF_RX_CS_RIGHT_IC_1_SHIFT 0

/* SPDIF_RX_CS_RIGHT_2 (IC 1) */
#define R322_SPDIF_RX_CS_RIGHT_2_SPDIF_RX_CS_RIGHT_IC_1 0x0000 /* 0000000000000000b	[15:0] */
#define R322_SPDIF_RX_CS_RIGHT_2_SPDIF_RX_CS_RIGHT_IC_1_MASK 0xFFFF
#define R322_SPDIF_RX_CS_RIGHT_2_SPDIF_RX_CS_RIGHT_IC_1_SHIFT 0

/* SPDIF_RX_CS_RIGHT_3 (IC 1) */
#define R323_SPDIF_RX_CS_RIGHT_3_SPDIF_RX_CS_RIGHT_IC_1 0x0000 /* 0000000000000000b	[15:0] */
#define R323_SPDIF_RX_CS_RIGHT_3_SPDIF_RX_CS_RIGHT_IC_1_MASK 0xFFFF
#define R323_SPDIF_RX_CS_RIGHT_3_SPDIF_RX_CS_RIGHT_IC_1_SHIFT 0

/* SPDIF_RX_CS_RIGHT_4 (IC 1) */
#define R324_SPDIF_RX_CS_RIGHT_4_SPDIF_RX_CS_RIGHT_IC_1 0x0000 /* 0000000000000000b	[15:0] */
#define R324_SPDIF_RX_CS_RIGHT_4_SPDIF_RX_CS_RIGHT_IC_1_MASK 0xFFFF
#define R324_SPDIF_RX_CS_RIGHT_4_SPDIF_RX_CS_RIGHT_IC_1_SHIFT 0

/* SPDIF_RX_CS_RIGHT_5 (IC 1) */
#define R325_SPDIF_RX_CS_RIGHT_5_SPDIF_RX_CS_RIGHT_IC_1 0x0000 /* 0000000000000000b	[15:0] */
#define R325_SPDIF_RX_CS_RIGHT_5_SPDIF_RX_CS_RIGHT_IC_1_MASK 0xFFFF
#define R325_SPDIF_RX_CS_RIGHT_5_SPDIF_RX_CS_RIGHT_IC_1_SHIFT 0

/* SPDIF_RX_CS_RIGHT_6 (IC 1) */
#define R326_SPDIF_RX_CS_RIGHT_6_SPDIF_RX_CS_RIGHT_IC_1 0x0000 /* 0000000000000000b	[15:0] */
#define R326_SPDIF_RX_CS_RIGHT_6_SPDIF_RX_CS_RIGHT_IC_1_MASK 0xFFFF
#define R326_SPDIF_RX_CS_RIGHT_6_SPDIF_RX_CS_RIGHT_IC_1_SHIFT 0

/* SPDIF_RX_CS_RIGHT_7 (IC 1) */
#define R327_SPDIF_RX_CS_RIGHT_7_SPDIF_RX_CS_RIGHT_IC_1 0x0000 /* 0000000000000000b	[15:0] */
#define R327_SPDIF_RX_CS_RIGHT_7_SPDIF_RX_CS_RIGHT_IC_1_MASK 0xFFFF
#define R327_SPDIF_RX_CS_RIGHT_7_SPDIF_RX_CS_RIGHT_IC_1_SHIFT 0

/* SPDIF_RX_CS_RIGHT_8 (IC 1) */
#define R328_SPDIF_RX_CS_RIGHT_8_SPDIF_RX_CS_RIGHT_IC_1 0x0000 /* 0000000000000000b	[15:0] */
#define R328_SPDIF_RX_CS_RIGHT_8_SPDIF_RX_CS_RIGHT_IC_1_MASK 0xFFFF
#define R328_SPDIF_RX_CS_RIGHT_8_SPDIF_RX_CS_RIGHT_IC_1_SHIFT 0

/* SPDIF_RX_CS_RIGHT_9 (IC 1) */
#define R329_SPDIF_RX_CS_RIGHT_9_SPDIF_RX_CS_RIGHT_IC_1 0x000B /* 0000000000001011b	[15:0] */
#define R329_SPDIF_RX_CS_RIGHT_9_SPDIF_RX_CS_RIGHT_IC_1_MASK 0xFFFF
#define R329_SPDIF_RX_CS_RIGHT_9_SPDIF_RX_CS_RIGHT_IC_1_SHIFT 0

/* SPDIF_RX_CS_RIGHT_10 (IC 1) */
#define R330_SPDIF_RX_CS_RIGHT_10_SPDIF_RX_CS_RIGHT_IC_1 0x0220 /* 0000001000100000b	[15:0] */
#define R330_SPDIF_RX_CS_RIGHT_10_SPDIF_RX_CS_RIGHT_IC_1_MASK 0xFFFF
#define R330_SPDIF_RX_CS_RIGHT_10_SPDIF_RX_CS_RIGHT_IC_1_SHIFT 0

/* SPDIF_RX_CS_RIGHT_11 (IC 1) */
#define R331_SPDIF_RX_CS_RIGHT_11_SPDIF_RX_CS_RIGHT_IC_1 0x7A04 /* 0111101000000100b	[15:0] */
#define R331_SPDIF_RX_CS_RIGHT_11_SPDIF_RX_CS_RIGHT_IC_1_MASK 0xFFFF
#define R331_SPDIF_RX_CS_RIGHT_11_SPDIF_RX_CS_RIGHT_IC_1_SHIFT 0

/* SPDIF_RX_UD_LEFT_0 (IC 1) */
#define R332_SPDIF_RX_UD_LEFT_0_SPDIF_RX_UD_LEFT_IC_1 0x0000 /* 0000000000000000b	[15:0] */
#define R332_SPDIF_RX_UD_LEFT_0_SPDIF_RX_UD_LEFT_IC_1_MASK 0xFFFF
#define R332_SPDIF_RX_UD_LEFT_0_SPDIF_RX_UD_LEFT_IC_1_SHIFT 0

/* SPDIF_RX_UD_LEFT_1 (IC 1) */
#define R333_SPDIF_RX_UD_LEFT_1_SPDIF_RX_UD_LEFT_IC_1 0x0000 /* 0000000000000000b	[15:0] */
#define R333_SPDIF_RX_UD_LEFT_1_SPDIF_RX_UD_LEFT_IC_1_MASK 0xFFFF
#define R333_SPDIF_RX_UD_LEFT_1_SPDIF_RX_UD_LEFT_IC_1_SHIFT 0

/* SPDIF_RX_UD_LEFT_2 (IC 1) */
#define R334_SPDIF_RX_UD_LEFT_2_SPDIF_RX_UD_LEFT_IC_1 0x0000 /* 0000000000000000b	[15:0] */
#define R334_SPDIF_RX_UD_LEFT_2_SPDIF_RX_UD_LEFT_IC_1_MASK 0xFFFF
#define R334_SPDIF_RX_UD_LEFT_2_SPDIF_RX_UD_LEFT_IC_1_SHIFT 0

/* SPDIF_RX_UD_LEFT_3 (IC 1) */
#define R335_SPDIF_RX_UD_LEFT_3_SPDIF_RX_UD_LEFT_IC_1 0x0000 /* 0000000000000000b	[15:0] */
#define R335_SPDIF_RX_UD_LEFT_3_SPDIF_RX_UD_LEFT_IC_1_MASK 0xFFFF
#define R335_SPDIF_RX_UD_LEFT_3_SPDIF_RX_UD_LEFT_IC_1_SHIFT 0

/* SPDIF_RX_UD_LEFT_4 (IC 1) */
#define R336_SPDIF_RX_UD_LEFT_4_SPDIF_RX_UD_LEFT_IC_1 0x0000 /* 0000000000000000b	[15:0] */
#define R336_SPDIF_RX_UD_LEFT_4_SPDIF_RX_UD_LEFT_IC_1_MASK 0xFFFF
#define R336_SPDIF_RX_UD_LEFT_4_SPDIF_RX_UD_LEFT_IC_1_SHIFT 0

/* SPDIF_RX_UD_LEFT_5 (IC 1) */
#define R337_SPDIF_RX_UD_LEFT_5_SPDIF_RX_UD_LEFT_IC_1 0x0000 /* 0000000000000000b	[15:0] */
#define R337_SPDIF_RX_UD_LEFT_5_SPDIF_RX_UD_LEFT_IC_1_MASK 0xFFFF
#define R337_SPDIF_RX_UD_LEFT_5_SPDIF_RX_UD_LEFT_IC_1_SHIFT 0

/* SPDIF_RX_UD_LEFT_6 (IC 1) */
#define R338_SPDIF_RX_UD_LEFT_6_SPDIF_RX_UD_LEFT_IC_1 0x0000 /* 0000000000000000b	[15:0] */
#define R338_SPDIF_RX_UD_LEFT_6_SPDIF_RX_UD_LEFT_IC_1_MASK 0xFFFF
#define R338_SPDIF_RX_UD_LEFT_6_SPDIF_RX_UD_LEFT_IC_1_SHIFT 0

/* SPDIF_RX_UD_LEFT_7 (IC 1) */
#define R339_SPDIF_RX_UD_LEFT_7_SPDIF_RX_UD_LEFT_IC_1 0x0000 /* 0000000000000000b	[15:0] */
#define R339_SPDIF_RX_UD_LEFT_7_SPDIF_RX_UD_LEFT_IC_1_MASK 0xFFFF
#define R339_SPDIF_RX_UD_LEFT_7_SPDIF_RX_UD_LEFT_IC_1_SHIFT 0

/* SPDIF_RX_UD_LEFT_8 (IC 1) */
#define R340_SPDIF_RX_UD_LEFT_8_SPDIF_RX_UD_LEFT_IC_1 0x0000 /* 0000000000000000b	[15:0] */
#define R340_SPDIF_RX_UD_LEFT_8_SPDIF_RX_UD_LEFT_IC_1_MASK 0xFFFF
#define R340_SPDIF_RX_UD_LEFT_8_SPDIF_RX_UD_LEFT_IC_1_SHIFT 0

/* SPDIF_RX_UD_LEFT_9 (IC 1) */
#define R341_SPDIF_RX_UD_LEFT_9_SPDIF_RX_UD_LEFT_IC_1 0x0000 /* 0000000000000000b	[15:0] */
#define R341_SPDIF_RX_UD_LEFT_9_SPDIF_RX_UD_LEFT_IC_1_MASK 0xFFFF
#define R341_SPDIF_RX_UD_LEFT_9_SPDIF_RX_UD_LEFT_IC_1_SHIFT 0

/* SPDIF_RX_UD_LEFT_10 (IC 1) */
#define R342_SPDIF_RX_UD_LEFT_10_SPDIF_RX_UD_LEFT_IC_1 0x0000 /* 0000000000000000b	[15:0] */
#define R342_SPDIF_RX_UD_LEFT_10_SPDIF_RX_UD_LEFT_IC_1_MASK 0xFFFF
#define R342_SPDIF_RX_UD_LEFT_10_SPDIF_RX_UD_LEFT_IC_1_SHIFT 0

/* SPDIF_RX_UD_LEFT_11 (IC 1) */
#define R343_SPDIF_RX_UD_LEFT_11_SPDIF_RX_UD_LEFT_IC_1 0x0000 /* 0000000000000000b	[15:0] */
#define R343_SPDIF_RX_UD_LEFT_11_SPDIF_RX_UD_LEFT_IC_1_MASK 0xFFFF
#define R343_SPDIF_RX_UD_LEFT_11_SPDIF_RX_UD_LEFT_IC_1_SHIFT 0

/* SPDIF_RX_UD_RIGHT_0 (IC 1) */
#define R344_SPDIF_RX_UD_RIGHT_0_SPDIF_RX_UD_RIGHT_IC_1 0x0000 /* 0000000000000000b	[15:0] */
#define R344_SPDIF_RX_UD_RIGHT_0_SPDIF_RX_UD_RIGHT_IC_1_MASK 0xFFFF
#define R344_SPDIF_RX_UD_RIGHT_0_SPDIF_RX_UD_RIGHT_IC_1_SHIFT 0

/* SPDIF_RX_UD_RIGHT_1 (IC 1) */
#define R345_SPDIF_RX_UD_RIGHT_1_SPDIF_RX_UD_RIGHT_IC_1 0x0000 /* 0000000000000000b	[15:0] */
#define R345_SPDIF_RX_UD_RIGHT_1_SPDIF_RX_UD_RIGHT_IC_1_MASK 0xFFFF
#define R345_SPDIF_RX_UD_RIGHT_1_SPDIF_RX_UD_RIGHT_IC_1_SHIFT 0

/* SPDIF_RX_UD_RIGHT_2 (IC 1) */
#define R346_SPDIF_RX_UD_RIGHT_2_SPDIF_RX_UD_RIGHT_IC_1 0x0000 /* 0000000000000000b	[15:0] */
#define R346_SPDIF_RX_UD_RIGHT_2_SPDIF_RX_UD_RIGHT_IC_1_MASK 0xFFFF
#define R346_SPDIF_RX_UD_RIGHT_2_SPDIF_RX_UD_RIGHT_IC_1_SHIFT 0

/* SPDIF_RX_UD_RIGHT_3 (IC 1) */
#define R347_SPDIF_RX_UD_RIGHT_3_SPDIF_RX_UD_RIGHT_IC_1 0x0000 /* 0000000000000000b	[15:0] */
#define R347_SPDIF_RX_UD_RIGHT_3_SPDIF_RX_UD_RIGHT_IC_1_MASK 0xFFFF
#define R347_SPDIF_RX_UD_RIGHT_3_SPDIF_RX_UD_RIGHT_IC_1_SHIFT 0

/* SPDIF_RX_UD_RIGHT_4 (IC 1) */
#define R348_SPDIF_RX_UD_RIGHT_4_SPDIF_RX_UD_RIGHT_IC_1 0x0000 /* 0000000000000000b	[15:0] */
#define R348_SPDIF_RX_UD_RIGHT_4_SPDIF_RX_UD_RIGHT_IC_1_MASK 0xFFFF
#define R348_SPDIF_RX_UD_RIGHT_4_SPDIF_RX_UD_RIGHT_IC_1_SHIFT 0

/* SPDIF_RX_UD_RIGHT_5 (IC 1) */
#define R349_SPDIF_RX_UD_RIGHT_5_SPDIF_RX_UD_RIGHT_IC_1 0x0000 /* 0000000000000000b	[15:0] */
#define R349_SPDIF_RX_UD_RIGHT_5_SPDIF_RX_UD_RIGHT_IC_1_MASK 0xFFFF
#define R349_SPDIF_RX_UD_RIGHT_5_SPDIF_RX_UD_RIGHT_IC_1_SHIFT 0

/* SPDIF_RX_UD_RIGHT_6 (IC 1) */
#define R350_SPDIF_RX_UD_RIGHT_6_SPDIF_RX_UD_RIGHT_IC_1 0x0000 /* 0000000000000000b	[15:0] */
#define R350_SPDIF_RX_UD_RIGHT_6_SPDIF_RX_UD_RIGHT_IC_1_MASK 0xFFFF
#define R350_SPDIF_RX_UD_RIGHT_6_SPDIF_RX_UD_RIGHT_IC_1_SHIFT 0

/* SPDIF_RX_UD_RIGHT_7 (IC 1) */
#define R351_SPDIF_RX_UD_RIGHT_7_SPDIF_RX_UD_RIGHT_IC_1 0x0000 /* 0000000000000000b	[15:0] */
#define R351_SPDIF_RX_UD_RIGHT_7_SPDIF_RX_UD_RIGHT_IC_1_MASK 0xFFFF
#define R351_SPDIF_RX_UD_RIGHT_7_SPDIF_RX_UD_RIGHT_IC_1_SHIFT 0

/* SPDIF_RX_UD_RIGHT_8 (IC 1) */
#define R352_SPDIF_RX_UD_RIGHT_8_SPDIF_RX_UD_RIGHT_IC_1 0x0000 /* 0000000000000000b	[15:0] */
#define R352_SPDIF_RX_UD_RIGHT_8_SPDIF_RX_UD_RIGHT_IC_1_MASK 0xFFFF
#define R352_SPDIF_RX_UD_RIGHT_8_SPDIF_RX_UD_RIGHT_IC_1_SHIFT 0

/* SPDIF_RX_UD_RIGHT_9 (IC 1) */
#define R353_SPDIF_RX_UD_RIGHT_9_SPDIF_RX_UD_RIGHT_IC_1 0x0000 /* 0000000000000000b	[15:0] */
#define R353_SPDIF_RX_UD_RIGHT_9_SPDIF_RX_UD_RIGHT_IC_1_MASK 0xFFFF
#define R353_SPDIF_RX_UD_RIGHT_9_SPDIF_RX_UD_RIGHT_IC_1_SHIFT 0

/* SPDIF_RX_UD_RIGHT_10 (IC 1) */
#define R354_SPDIF_RX_UD_RIGHT_10_SPDIF_RX_UD_RIGHT_IC_1 0x0000 /* 0000000000000000b	[15:0] */
#define R354_SPDIF_RX_UD_RIGHT_10_SPDIF_RX_UD_RIGHT_IC_1_MASK 0xFFFF
#define R354_SPDIF_RX_UD_RIGHT_10_SPDIF_RX_UD_RIGHT_IC_1_SHIFT 0

/* SPDIF_RX_UD_RIGHT_11 (IC 1) */
#define R355_SPDIF_RX_UD_RIGHT_11_SPDIF_RX_UD_RIGHT_IC_1 0x0000 /* 0000000000000000b	[15:0] */
#define R355_SPDIF_RX_UD_RIGHT_11_SPDIF_RX_UD_RIGHT_IC_1_MASK 0xFFFF
#define R355_SPDIF_RX_UD_RIGHT_11_SPDIF_RX_UD_RIGHT_IC_1_SHIFT 0

/* SPDIF_RX_VB_LEFT_0 (IC 1) */
#define R356_SPDIF_RX_VB_LEFT_0_SPDIF_RX_VB_LEFT_IC_1 0x0000 /* 0000000000000000b	[15:0] */
#define R356_SPDIF_RX_VB_LEFT_0_SPDIF_RX_VB_LEFT_IC_1_MASK 0xFFFF
#define R356_SPDIF_RX_VB_LEFT_0_SPDIF_RX_VB_LEFT_IC_1_SHIFT 0

/* SPDIF_RX_VB_LEFT_1 (IC 1) */
#define R357_SPDIF_RX_VB_LEFT_1_SPDIF_RX_VB_LEFT_IC_1 0x0000 /* 0000000000000000b	[15:0] */
#define R357_SPDIF_RX_VB_LEFT_1_SPDIF_RX_VB_LEFT_IC_1_MASK 0xFFFF
#define R357_SPDIF_RX_VB_LEFT_1_SPDIF_RX_VB_LEFT_IC_1_SHIFT 0

/* SPDIF_RX_VB_LEFT_2 (IC 1) */
#define R358_SPDIF_RX_VB_LEFT_2_SPDIF_RX_VB_LEFT_IC_1 0x0000 /* 0000000000000000b	[15:0] */
#define R358_SPDIF_RX_VB_LEFT_2_SPDIF_RX_VB_LEFT_IC_1_MASK 0xFFFF
#define R358_SPDIF_RX_VB_LEFT_2_SPDIF_RX_VB_LEFT_IC_1_SHIFT 0

/* SPDIF_RX_VB_LEFT_3 (IC 1) */
#define R359_SPDIF_RX_VB_LEFT_3_SPDIF_RX_VB_LEFT_IC_1 0x0000 /* 0000000000000000b	[15:0] */
#define R359_SPDIF_RX_VB_LEFT_3_SPDIF_RX_VB_LEFT_IC_1_MASK 0xFFFF
#define R359_SPDIF_RX_VB_LEFT_3_SPDIF_RX_VB_LEFT_IC_1_SHIFT 0

/* SPDIF_RX_VB_LEFT_4 (IC 1) */
#define R360_SPDIF_RX_VB_LEFT_4_SPDIF_RX_VB_LEFT_IC_1 0x0000 /* 0000000000000000b	[15:0] */
#define R360_SPDIF_RX_VB_LEFT_4_SPDIF_RX_VB_LEFT_IC_1_MASK 0xFFFF
#define R360_SPDIF_RX_VB_LEFT_4_SPDIF_RX_VB_LEFT_IC_1_SHIFT 0

/* SPDIF_RX_VB_LEFT_5 (IC 1) */
#define R361_SPDIF_RX_VB_LEFT_5_SPDIF_RX_VB_LEFT_IC_1 0x0000 /* 0000000000000000b	[15:0] */
#define R361_SPDIF_RX_VB_LEFT_5_SPDIF_RX_VB_LEFT_IC_1_MASK 0xFFFF
#define R361_SPDIF_RX_VB_LEFT_5_SPDIF_RX_VB_LEFT_IC_1_SHIFT 0

/* SPDIF_RX_VB_LEFT_6 (IC 1) */
#define R362_SPDIF_RX_VB_LEFT_6_SPDIF_RX_VB_LEFT_IC_1 0x0000 /* 0000000000000000b	[15:0] */
#define R362_SPDIF_RX_VB_LEFT_6_SPDIF_RX_VB_LEFT_IC_1_MASK 0xFFFF
#define R362_SPDIF_RX_VB_LEFT_6_SPDIF_RX_VB_LEFT_IC_1_SHIFT 0

/* SPDIF_RX_VB_LEFT_7 (IC 1) */
#define R363_SPDIF_RX_VB_LEFT_7_SPDIF_RX_VB_LEFT_IC_1 0x0000 /* 0000000000000000b	[15:0] */
#define R363_SPDIF_RX_VB_LEFT_7_SPDIF_RX_VB_LEFT_IC_1_MASK 0xFFFF
#define R363_SPDIF_RX_VB_LEFT_7_SPDIF_RX_VB_LEFT_IC_1_SHIFT 0

/* SPDIF_RX_VB_LEFT_8 (IC 1) */
#define R364_SPDIF_RX_VB_LEFT_8_SPDIF_RX_VB_LEFT_IC_1 0x0000 /* 0000000000000000b	[15:0] */
#define R364_SPDIF_RX_VB_LEFT_8_SPDIF_RX_VB_LEFT_IC_1_MASK 0xFFFF
#define R364_SPDIF_RX_VB_LEFT_8_SPDIF_RX_VB_LEFT_IC_1_SHIFT 0

/* SPDIF_RX_VB_LEFT_9 (IC 1) */
#define R365_SPDIF_RX_VB_LEFT_9_SPDIF_RX_VB_LEFT_IC_1 0x0000 /* 0000000000000000b	[15:0] */
#define R365_SPDIF_RX_VB_LEFT_9_SPDIF_RX_VB_LEFT_IC_1_MASK 0xFFFF
#define R365_SPDIF_RX_VB_LEFT_9_SPDIF_RX_VB_LEFT_IC_1_SHIFT 0

/* SPDIF_RX_VB_LEFT_10 (IC 1) */
#define R366_SPDIF_RX_VB_LEFT_10_SPDIF_RX_VB_LEFT_IC_1 0x0000 /* 0000000000000000b	[15:0] */
#define R366_SPDIF_RX_VB_LEFT_10_SPDIF_RX_VB_LEFT_IC_1_MASK 0xFFFF
#define R366_SPDIF_RX_VB_LEFT_10_SPDIF_RX_VB_LEFT_IC_1_SHIFT 0

/* SPDIF_RX_VB_LEFT_11 (IC 1) */
#define R367_SPDIF_RX_VB_LEFT_11_SPDIF_RX_VB_LEFT_IC_1 0x0000 /* 0000000000000000b	[15:0] */
#define R367_SPDIF_RX_VB_LEFT_11_SPDIF_RX_VB_LEFT_IC_1_MASK 0xFFFF
#define R367_SPDIF_RX_VB_LEFT_11_SPDIF_RX_VB_LEFT_IC_1_SHIFT 0

/* SPDIF_RX_VB_RIGHT_0 (IC 1) */
#define R368_SPDIF_RX_VB_RIGHT_0_SPDIF_RX_VB_RIGHT_IC_1 0x0000 /* 0000000000000000b	[15:0] */
#define R368_SPDIF_RX_VB_RIGHT_0_SPDIF_RX_VB_RIGHT_IC_1_MASK 0xFFFF
#define R368_SPDIF_RX_VB_RIGHT_0_SPDIF_RX_VB_RIGHT_IC_1_SHIFT 0

/* SPDIF_RX_VB_RIGHT_1 (IC 1) */
#define R369_SPDIF_RX_VB_RIGHT_1_SPDIF_RX_VB_RIGHT_IC_1 0x0000 /* 0000000000000000b	[15:0] */
#define R369_SPDIF_RX_VB_RIGHT_1_SPDIF_RX_VB_RIGHT_IC_1_MASK 0xFFFF
#define R369_SPDIF_RX_VB_RIGHT_1_SPDIF_RX_VB_RIGHT_IC_1_SHIFT 0

/* SPDIF_RX_VB_RIGHT_2 (IC 1) */
#define R370_SPDIF_RX_VB_RIGHT_2_SPDIF_RX_VB_RIGHT_IC_1 0x0000 /* 0000000000000000b	[15:0] */
#define R370_SPDIF_RX_VB_RIGHT_2_SPDIF_RX_VB_RIGHT_IC_1_MASK 0xFFFF
#define R370_SPDIF_RX_VB_RIGHT_2_SPDIF_RX_VB_RIGHT_IC_1_SHIFT 0

/* SPDIF_RX_VB_RIGHT_3 (IC 1) */
#define R371_SPDIF_RX_VB_RIGHT_3_SPDIF_RX_VB_RIGHT_IC_1 0x0000 /* 0000000000000000b	[15:0] */
#define R371_SPDIF_RX_VB_RIGHT_3_SPDIF_RX_VB_RIGHT_IC_1_MASK 0xFFFF
#define R371_SPDIF_RX_VB_RIGHT_3_SPDIF_RX_VB_RIGHT_IC_1_SHIFT 0

/* SPDIF_RX_VB_RIGHT_4 (IC 1) */
#define R372_SPDIF_RX_VB_RIGHT_4_SPDIF_RX_VB_RIGHT_IC_1 0x0000 /* 0000000000000000b	[15:0] */
#define R372_SPDIF_RX_VB_RIGHT_4_SPDIF_RX_VB_RIGHT_IC_1_MASK 0xFFFF
#define R372_SPDIF_RX_VB_RIGHT_4_SPDIF_RX_VB_RIGHT_IC_1_SHIFT 0

/* SPDIF_RX_VB_RIGHT_5 (IC 1) */
#define R373_SPDIF_RX_VB_RIGHT_5_SPDIF_RX_VB_RIGHT_IC_1 0x0000 /* 0000000000000000b	[15:0] */
#define R373_SPDIF_RX_VB_RIGHT_5_SPDIF_RX_VB_RIGHT_IC_1_MASK 0xFFFF
#define R373_SPDIF_RX_VB_RIGHT_5_SPDIF_RX_VB_RIGHT_IC_1_SHIFT 0

/* SPDIF_RX_VB_RIGHT_6 (IC 1) */
#define R374_SPDIF_RX_VB_RIGHT_6_SPDIF_RX_VB_RIGHT_IC_1 0x0000 /* 0000000000000000b	[15:0] */
#define R374_SPDIF_RX_VB_RIGHT_6_SPDIF_RX_VB_RIGHT_IC_1_MASK 0xFFFF
#define R374_SPDIF_RX_VB_RIGHT_6_SPDIF_RX_VB_RIGHT_IC_1_SHIFT 0

/* SPDIF_RX_VB_RIGHT_7 (IC 1) */
#define R375_SPDIF_RX_VB_RIGHT_7_SPDIF_RX_VB_RIGHT_IC_1 0x0000 /* 0000000000000000b	[15:0] */
#define R375_SPDIF_RX_VB_RIGHT_7_SPDIF_RX_VB_RIGHT_IC_1_MASK 0xFFFF
#define R375_SPDIF_RX_VB_RIGHT_7_SPDIF_RX_VB_RIGHT_IC_1_SHIFT 0

/* SPDIF_RX_VB_RIGHT_8 (IC 1) */
#define R376_SPDIF_RX_VB_RIGHT_8_SPDIF_RX_VB_RIGHT_IC_1 0x0000 /* 0000000000000000b	[15:0] */
#define R376_SPDIF_RX_VB_RIGHT_8_SPDIF_RX_VB_RIGHT_IC_1_MASK 0xFFFF
#define R376_SPDIF_RX_VB_RIGHT_8_SPDIF_RX_VB_RIGHT_IC_1_SHIFT 0

/* SPDIF_RX_VB_RIGHT_9 (IC 1) */
#define R377_SPDIF_RX_VB_RIGHT_9_SPDIF_RX_VB_RIGHT_IC_1 0x0000 /* 0000000000000000b	[15:0] */
#define R377_SPDIF_RX_VB_RIGHT_9_SPDIF_RX_VB_RIGHT_IC_1_MASK 0xFFFF
#define R377_SPDIF_RX_VB_RIGHT_9_SPDIF_RX_VB_RIGHT_IC_1_SHIFT 0

/* SPDIF_RX_VB_RIGHT_10 (IC 1) */
#define R378_SPDIF_RX_VB_RIGHT_10_SPDIF_RX_VB_RIGHT_IC_1 0x0000 /* 0000000000000000b	[15:0] */
#define R378_SPDIF_RX_VB_RIGHT_10_SPDIF_RX_VB_RIGHT_IC_1_MASK 0xFFFF
#define R378_SPDIF_RX_VB_RIGHT_10_SPDIF_RX_VB_RIGHT_IC_1_SHIFT 0

/* SPDIF_RX_VB_RIGHT_11 (IC 1) */
#define R379_SPDIF_RX_VB_RIGHT_11_SPDIF_RX_VB_RIGHT_IC_1 0x0000 /* 0000000000000000b	[15:0] */
#define R379_SPDIF_RX_VB_RIGHT_11_SPDIF_RX_VB_RIGHT_IC_1_MASK 0xFFFF
#define R379_SPDIF_RX_VB_RIGHT_11_SPDIF_RX_VB_RIGHT_IC_1_SHIFT 0

/* SPDIF_RX_PB_LEFT_0 (IC 1) */
#define R380_SPDIF_RX_PB_LEFT_0_SPDIF_RX_PB_LEFT_IC_1 0x0000 /* 0000000000000000b	[15:0] */
#define R380_SPDIF_RX_PB_LEFT_0_SPDIF_RX_PB_LEFT_IC_1_MASK 0xFFFF
#define R380_SPDIF_RX_PB_LEFT_0_SPDIF_RX_PB_LEFT_IC_1_SHIFT 0

/* SPDIF_RX_PB_LEFT_1 (IC 1) */
#define R381_SPDIF_RX_PB_LEFT_1_SPDIF_RX_PB_LEFT_IC_1 0x0000 /* 0000000000000000b	[15:0] */
#define R381_SPDIF_RX_PB_LEFT_1_SPDIF_RX_PB_LEFT_IC_1_MASK 0xFFFF
#define R381_SPDIF_RX_PB_LEFT_1_SPDIF_RX_PB_LEFT_IC_1_SHIFT 0

/* SPDIF_RX_PB_LEFT_2 (IC 1) */
#define R382_SPDIF_RX_PB_LEFT_2_SPDIF_RX_PB_LEFT_IC_1 0x0000 /* 0000000000000000b	[15:0] */
#define R382_SPDIF_RX_PB_LEFT_2_SPDIF_RX_PB_LEFT_IC_1_MASK 0xFFFF
#define R382_SPDIF_RX_PB_LEFT_2_SPDIF_RX_PB_LEFT_IC_1_SHIFT 0

/* SPDIF_RX_PB_LEFT_3 (IC 1) */
#define R383_SPDIF_RX_PB_LEFT_3_SPDIF_RX_PB_LEFT_IC_1 0x0000 /* 0000000000000000b	[15:0] */
#define R383_SPDIF_RX_PB_LEFT_3_SPDIF_RX_PB_LEFT_IC_1_MASK 0xFFFF
#define R383_SPDIF_RX_PB_LEFT_3_SPDIF_RX_PB_LEFT_IC_1_SHIFT 0

/* SPDIF_RX_PB_LEFT_4 (IC 1) */
#define R384_SPDIF_RX_PB_LEFT_4_SPDIF_RX_PB_LEFT_IC_1 0x0000 /* 0000000000000000b	[15:0] */
#define R384_SPDIF_RX_PB_LEFT_4_SPDIF_RX_PB_LEFT_IC_1_MASK 0xFFFF
#define R384_SPDIF_RX_PB_LEFT_4_SPDIF_RX_PB_LEFT_IC_1_SHIFT 0

/* SPDIF_RX_PB_LEFT_5 (IC 1) */
#define R385_SPDIF_RX_PB_LEFT_5_SPDIF_RX_PB_LEFT_IC_1 0x0000 /* 0000000000000000b	[15:0] */
#define R385_SPDIF_RX_PB_LEFT_5_SPDIF_RX_PB_LEFT_IC_1_MASK 0xFFFF
#define R385_SPDIF_RX_PB_LEFT_5_SPDIF_RX_PB_LEFT_IC_1_SHIFT 0

/* SPDIF_RX_PB_LEFT_6 (IC 1) */
#define R386_SPDIF_RX_PB_LEFT_6_SPDIF_RX_PB_LEFT_IC_1 0x0000 /* 0000000000000000b	[15:0] */
#define R386_SPDIF_RX_PB_LEFT_6_SPDIF_RX_PB_LEFT_IC_1_MASK 0xFFFF
#define R386_SPDIF_RX_PB_LEFT_6_SPDIF_RX_PB_LEFT_IC_1_SHIFT 0

/* SPDIF_RX_PB_LEFT_7 (IC 1) */
#define R387_SPDIF_RX_PB_LEFT_7_SPDIF_RX_PB_LEFT_IC_1 0x0000 /* 0000000000000000b	[15:0] */
#define R387_SPDIF_RX_PB_LEFT_7_SPDIF_RX_PB_LEFT_IC_1_MASK 0xFFFF
#define R387_SPDIF_RX_PB_LEFT_7_SPDIF_RX_PB_LEFT_IC_1_SHIFT 0

/* SPDIF_RX_PB_LEFT_8 (IC 1) */
#define R388_SPDIF_RX_PB_LEFT_8_SPDIF_RX_PB_LEFT_IC_1 0x0000 /* 0000000000000000b	[15:0] */
#define R388_SPDIF_RX_PB_LEFT_8_SPDIF_RX_PB_LEFT_IC_1_MASK 0xFFFF
#define R388_SPDIF_RX_PB_LEFT_8_SPDIF_RX_PB_LEFT_IC_1_SHIFT 0

/* SPDIF_RX_PB_LEFT_9 (IC 1) */
#define R389_SPDIF_RX_PB_LEFT_9_SPDIF_RX_PB_LEFT_IC_1 0x000B /* 0000000000001011b	[15:0] */
#define R389_SPDIF_RX_PB_LEFT_9_SPDIF_RX_PB_LEFT_IC_1_MASK 0xFFFF
#define R389_SPDIF_RX_PB_LEFT_9_SPDIF_RX_PB_LEFT_IC_1_SHIFT 0

/* SPDIF_RX_PB_LEFT_10 (IC 1) */
#define R390_SPDIF_RX_PB_LEFT_10_SPDIF_RX_PB_LEFT_IC_1 0x0210 /* 0000001000010000b	[15:0] */
#define R390_SPDIF_RX_PB_LEFT_10_SPDIF_RX_PB_LEFT_IC_1_MASK 0xFFFF
#define R390_SPDIF_RX_PB_LEFT_10_SPDIF_RX_PB_LEFT_IC_1_SHIFT 0

/* SPDIF_RX_PB_LEFT_11 (IC 1) */
#define R391_SPDIF_RX_PB_LEFT_11_SPDIF_RX_PB_LEFT_IC_1 0x7A04 /* 0111101000000100b	[15:0] */
#define R391_SPDIF_RX_PB_LEFT_11_SPDIF_RX_PB_LEFT_IC_1_MASK 0xFFFF
#define R391_SPDIF_RX_PB_LEFT_11_SPDIF_RX_PB_LEFT_IC_1_SHIFT 0

/* SPDIF_RX_PB_RIGHT_0 (IC 1) */
#define R392_SPDIF_RX_PB_RIGHT_0_SPDIF_RX_PB_RIGHT_IC_1 0x0000 /* 0000000000000000b	[15:0] */
#define R392_SPDIF_RX_PB_RIGHT_0_SPDIF_RX_PB_RIGHT_IC_1_MASK 0xFFFF
#define R392_SPDIF_RX_PB_RIGHT_0_SPDIF_RX_PB_RIGHT_IC_1_SHIFT 0

/* SPDIF_RX_PB_RIGHT_1 (IC 1) */
#define R393_SPDIF_RX_PB_RIGHT_1_SPDIF_RX_PB_RIGHT_IC_1 0x0000 /* 0000000000000000b	[15:0] */
#define R393_SPDIF_RX_PB_RIGHT_1_SPDIF_RX_PB_RIGHT_IC_1_MASK 0xFFFF
#define R393_SPDIF_RX_PB_RIGHT_1_SPDIF_RX_PB_RIGHT_IC_1_SHIFT 0

/* SPDIF_RX_PB_RIGHT_2 (IC 1) */
#define R394_SPDIF_RX_PB_RIGHT_2_SPDIF_RX_PB_RIGHT_IC_1 0x0000 /* 0000000000000000b	[15:0] */
#define R394_SPDIF_RX_PB_RIGHT_2_SPDIF_RX_PB_RIGHT_IC_1_MASK 0xFFFF
#define R394_SPDIF_RX_PB_RIGHT_2_SPDIF_RX_PB_RIGHT_IC_1_SHIFT 0

/* SPDIF_RX_PB_RIGHT_3 (IC 1) */
#define R395_SPDIF_RX_PB_RIGHT_3_SPDIF_RX_PB_RIGHT_IC_1 0x0000 /* 0000000000000000b	[15:0] */
#define R395_SPDIF_RX_PB_RIGHT_3_SPDIF_RX_PB_RIGHT_IC_1_MASK 0xFFFF
#define R395_SPDIF_RX_PB_RIGHT_3_SPDIF_RX_PB_RIGHT_IC_1_SHIFT 0

/* SPDIF_RX_PB_RIGHT_4 (IC 1) */
#define R396_SPDIF_RX_PB_RIGHT_4_SPDIF_RX_PB_RIGHT_IC_1 0x0000 /* 0000000000000000b	[15:0] */
#define R396_SPDIF_RX_PB_RIGHT_4_SPDIF_RX_PB_RIGHT_IC_1_MASK 0xFFFF
#define R396_SPDIF_RX_PB_RIGHT_4_SPDIF_RX_PB_RIGHT_IC_1_SHIFT 0

/* SPDIF_RX_PB_RIGHT_5 (IC 1) */
#define R397_SPDIF_RX_PB_RIGHT_5_SPDIF_RX_PB_RIGHT_IC_1 0x0000 /* 0000000000000000b	[15:0] */
#define R397_SPDIF_RX_PB_RIGHT_5_SPDIF_RX_PB_RIGHT_IC_1_MASK 0xFFFF
#define R397_SPDIF_RX_PB_RIGHT_5_SPDIF_RX_PB_RIGHT_IC_1_SHIFT 0

/* SPDIF_RX_PB_RIGHT_6 (IC 1) */
#define R398_SPDIF_RX_PB_RIGHT_6_SPDIF_RX_PB_RIGHT_IC_1 0x0000 /* 0000000000000000b	[15:0] */
#define R398_SPDIF_RX_PB_RIGHT_6_SPDIF_RX_PB_RIGHT_IC_1_MASK 0xFFFF
#define R398_SPDIF_RX_PB_RIGHT_6_SPDIF_RX_PB_RIGHT_IC_1_SHIFT 0

/* SPDIF_RX_PB_RIGHT_7 (IC 1) */
#define R399_SPDIF_RX_PB_RIGHT_7_SPDIF_RX_PB_RIGHT_IC_1 0x0000 /* 0000000000000000b	[15:0] */
#define R399_SPDIF_RX_PB_RIGHT_7_SPDIF_RX_PB_RIGHT_IC_1_MASK 0xFFFF
#define R399_SPDIF_RX_PB_RIGHT_7_SPDIF_RX_PB_RIGHT_IC_1_SHIFT 0

/* SPDIF_RX_PB_RIGHT_8 (IC 1) */
#define R400_SPDIF_RX_PB_RIGHT_8_SPDIF_RX_PB_RIGHT_IC_1 0x0000 /* 0000000000000000b	[15:0] */
#define R400_SPDIF_RX_PB_RIGHT_8_SPDIF_RX_PB_RIGHT_IC_1_MASK 0xFFFF
#define R400_SPDIF_RX_PB_RIGHT_8_SPDIF_RX_PB_RIGHT_IC_1_SHIFT 0

/* SPDIF_RX_PB_RIGHT_9 (IC 1) */
#define R401_SPDIF_RX_PB_RIGHT_9_SPDIF_RX_PB_RIGHT_IC_1 0x000B /* 0000000000001011b	[15:0] */
#define R401_SPDIF_RX_PB_RIGHT_9_SPDIF_RX_PB_RIGHT_IC_1_MASK 0xFFFF
#define R401_SPDIF_RX_PB_RIGHT_9_SPDIF_RX_PB_RIGHT_IC_1_SHIFT 0

/* SPDIF_RX_PB_RIGHT_10 (IC 1) */
#define R402_SPDIF_RX_PB_RIGHT_10_SPDIF_RX_PB_RIGHT_IC_1 0x0220 /* 0000001000100000b	[15:0] */
#define R402_SPDIF_RX_PB_RIGHT_10_SPDIF_RX_PB_RIGHT_IC_1_MASK 0xFFFF
#define R402_SPDIF_RX_PB_RIGHT_10_SPDIF_RX_PB_RIGHT_IC_1_SHIFT 0

/* SPDIF_RX_PB_RIGHT_11 (IC 1) */
#define R403_SPDIF_RX_PB_RIGHT_11_SPDIF_RX_PB_RIGHT_IC_1 0x7A04 /* 0111101000000100b	[15:0] */
#define R403_SPDIF_RX_PB_RIGHT_11_SPDIF_RX_PB_RIGHT_IC_1_MASK 0xFFFF
#define R403_SPDIF_RX_PB_RIGHT_11_SPDIF_RX_PB_RIGHT_IC_1_SHIFT 0

/* SPDIF_TX_EN (IC 1) */
#define R404_SPDIF_TX_EN_TXEN_IC_1                0x1    /* 1b	[0] */
#define R404_SPDIF_TX_EN_TXEN_IC_1_MASK           0x1
#define R404_SPDIF_TX_EN_TXEN_IC_1_SHIFT          0

/* SPDIF_TX_CTRL (IC 1) */
#define R405_SPDIF_TX_CTRL_TX_LENGTHCTRL_IC_1     0x0    /* 00b	[1:0] */
#define R405_SPDIF_TX_CTRL_TX_LENGTHCTRL_IC_1_MASK 0x3
#define R405_SPDIF_TX_CTRL_TX_LENGTHCTRL_IC_1_SHIFT 0

/* SPDIF_TX_AUXBIT_SOURCE (IC 1) */
#define R406_SPDIF_TX_AUXBIT_SOURCE_TX_AUXBITS_SOURCE_IC_1 0x0 /* 0b	[0] */
#define R406_SPDIF_TX_AUXBIT_SOURCE_TX_AUXBITS_SOURCE_IC_1_MASK 0x1
#define R406_SPDIF_TX_AUXBIT_SOURCE_TX_AUXBITS_SOURCE_IC_1_SHIFT 0

/* SPDIF_TX_CS_LEFT_0 (IC 1) */
#define R407_SPDIF_TX_CS_LEFT_0_SPDIF_TX_CS_LEFT_IC_1 0x0000 /* 0000000000000000b	[15:0] */
#define R407_SPDIF_TX_CS_LEFT_0_SPDIF_TX_CS_LEFT_IC_1_MASK 0xFFFF
#define R407_SPDIF_TX_CS_LEFT_0_SPDIF_TX_CS_LEFT_IC_1_SHIFT 0

/* SPDIF_TX_CS_LEFT_1 (IC 1) */
#define R408_SPDIF_TX_CS_LEFT_1_SPDIF_TX_CS_LEFT_IC_1 0x0000 /* 0000000000000000b	[15:0] */
#define R408_SPDIF_TX_CS_LEFT_1_SPDIF_TX_CS_LEFT_IC_1_MASK 0xFFFF
#define R408_SPDIF_TX_CS_LEFT_1_SPDIF_TX_CS_LEFT_IC_1_SHIFT 0

/* SPDIF_TX_CS_LEFT_2 (IC 1) */
#define R409_SPDIF_TX_CS_LEFT_2_SPDIF_TX_CS_LEFT_IC_1 0x0000 /* 0000000000000000b	[15:0] */
#define R409_SPDIF_TX_CS_LEFT_2_SPDIF_TX_CS_LEFT_IC_1_MASK 0xFFFF
#define R409_SPDIF_TX_CS_LEFT_2_SPDIF_TX_CS_LEFT_IC_1_SHIFT 0

/* SPDIF_TX_CS_LEFT_3 (IC 1) */
#define R410_SPDIF_TX_CS_LEFT_3_SPDIF_TX_CS_LEFT_IC_1 0x0000 /* 0000000000000000b	[15:0] */
#define R410_SPDIF_TX_CS_LEFT_3_SPDIF_TX_CS_LEFT_IC_1_MASK 0xFFFF
#define R410_SPDIF_TX_CS_LEFT_3_SPDIF_TX_CS_LEFT_IC_1_SHIFT 0

/* SPDIF_TX_CS_LEFT_4 (IC 1) */
#define R411_SPDIF_TX_CS_LEFT_4_SPDIF_TX_CS_LEFT_IC_1 0x0000 /* 0000000000000000b	[15:0] */
#define R411_SPDIF_TX_CS_LEFT_4_SPDIF_TX_CS_LEFT_IC_1_MASK 0xFFFF
#define R411_SPDIF_TX_CS_LEFT_4_SPDIF_TX_CS_LEFT_IC_1_SHIFT 0

/* SPDIF_TX_CS_LEFT_5 (IC 1) */
#define R412_SPDIF_TX_CS_LEFT_5_SPDIF_TX_CS_LEFT_IC_1 0x0000 /* 0000000000000000b	[15:0] */
#define R412_SPDIF_TX_CS_LEFT_5_SPDIF_TX_CS_LEFT_IC_1_MASK 0xFFFF
#define R412_SPDIF_TX_CS_LEFT_5_SPDIF_TX_CS_LEFT_IC_1_SHIFT 0

/* SPDIF_TX_CS_LEFT_6 (IC 1) */
#define R413_SPDIF_TX_CS_LEFT_6_SPDIF_TX_CS_LEFT_IC_1 0x0000 /* 0000000000000000b	[15:0] */
#define R413_SPDIF_TX_CS_LEFT_6_SPDIF_TX_CS_LEFT_IC_1_MASK 0xFFFF
#define R413_SPDIF_TX_CS_LEFT_6_SPDIF_TX_CS_LEFT_IC_1_SHIFT 0

/* SPDIF_TX_CS_LEFT_7 (IC 1) */
#define R414_SPDIF_TX_CS_LEFT_7_SPDIF_TX_CS_LEFT_IC_1 0x0000 /* 0000000000000000b	[15:0] */
#define R414_SPDIF_TX_CS_LEFT_7_SPDIF_TX_CS_LEFT_IC_1_MASK 0xFFFF
#define R414_SPDIF_TX_CS_LEFT_7_SPDIF_TX_CS_LEFT_IC_1_SHIFT 0

/* SPDIF_TX_CS_LEFT_8 (IC 1) */
#define R415_SPDIF_TX_CS_LEFT_8_SPDIF_TX_CS_LEFT_IC_1 0x0000 /* 0000000000000000b	[15:0] */
#define R415_SPDIF_TX_CS_LEFT_8_SPDIF_TX_CS_LEFT_IC_1_MASK 0xFFFF
#define R415_SPDIF_TX_CS_LEFT_8_SPDIF_TX_CS_LEFT_IC_1_SHIFT 0

/* SPDIF_TX_CS_LEFT_9 (IC 1) */
#define R416_SPDIF_TX_CS_LEFT_9_SPDIF_TX_CS_LEFT_IC_1 0x0000 /* 0000000000000000b	[15:0] */
#define R416_SPDIF_TX_CS_LEFT_9_SPDIF_TX_CS_LEFT_IC_1_MASK 0xFFFF
#define R416_SPDIF_TX_CS_LEFT_9_SPDIF_TX_CS_LEFT_IC_1_SHIFT 0

/* SPDIF_TX_CS_LEFT_10 (IC 1) */
#define R417_SPDIF_TX_CS_LEFT_10_SPDIF_TX_CS_LEFT_IC_1 0x0000 /* 0000000000000000b	[15:0] */
#define R417_SPDIF_TX_CS_LEFT_10_SPDIF_TX_CS_LEFT_IC_1_MASK 0xFFFF
#define R417_SPDIF_TX_CS_LEFT_10_SPDIF_TX_CS_LEFT_IC_1_SHIFT 0

/* SPDIF_TX_CS_LEFT_11 (IC 1) */
#define R418_SPDIF_TX_CS_LEFT_11_SPDIF_TX_CS_LEFT_IC_1 0x0000 /* 0000000000000000b	[15:0] */
#define R418_SPDIF_TX_CS_LEFT_11_SPDIF_TX_CS_LEFT_IC_1_MASK 0xFFFF
#define R418_SPDIF_TX_CS_LEFT_11_SPDIF_TX_CS_LEFT_IC_1_SHIFT 0

/* SPDIF_TX_CS_RIGHT_0 (IC 1) */
#define R419_SPDIF_TX_CS_RIGHT_0_SPDIF_TX_CS_RIGHT_IC_1 0x0000 /* 0000000000000000b	[15:0] */
#define R419_SPDIF_TX_CS_RIGHT_0_SPDIF_TX_CS_RIGHT_IC_1_MASK 0xFFFF
#define R419_SPDIF_TX_CS_RIGHT_0_SPDIF_TX_CS_RIGHT_IC_1_SHIFT 0

/* SPDIF_TX_CS_RIGHT_1 (IC 1) */
#define R420_SPDIF_TX_CS_RIGHT_1_SPDIF_TX_CS_RIGHT_IC_1 0x0000 /* 0000000000000000b	[15:0] */
#define R420_SPDIF_TX_CS_RIGHT_1_SPDIF_TX_CS_RIGHT_IC_1_MASK 0xFFFF
#define R420_SPDIF_TX_CS_RIGHT_1_SPDIF_TX_CS_RIGHT_IC_1_SHIFT 0

/* SPDIF_TX_CS_RIGHT_2 (IC 1) */
#define R421_SPDIF_TX_CS_RIGHT_2_SPDIF_TX_CS_RIGHT_IC_1 0x0000 /* 0000000000000000b	[15:0] */
#define R421_SPDIF_TX_CS_RIGHT_2_SPDIF_TX_CS_RIGHT_IC_1_MASK 0xFFFF
#define R421_SPDIF_TX_CS_RIGHT_2_SPDIF_TX_CS_RIGHT_IC_1_SHIFT 0

/* SPDIF_TX_CS_RIGHT_3 (IC 1) */
#define R422_SPDIF_TX_CS_RIGHT_3_SPDIF_TX_CS_RIGHT_IC_1 0x0000 /* 0000000000000000b	[15:0] */
#define R422_SPDIF_TX_CS_RIGHT_3_SPDIF_TX_CS_RIGHT_IC_1_MASK 0xFFFF
#define R422_SPDIF_TX_CS_RIGHT_3_SPDIF_TX_CS_RIGHT_IC_1_SHIFT 0

/* SPDIF_TX_CS_RIGHT_4 (IC 1) */
#define R423_SPDIF_TX_CS_RIGHT_4_SPDIF_TX_CS_RIGHT_IC_1 0x0000 /* 0000000000000000b	[15:0] */
#define R423_SPDIF_TX_CS_RIGHT_4_SPDIF_TX_CS_RIGHT_IC_1_MASK 0xFFFF
#define R423_SPDIF_TX_CS_RIGHT_4_SPDIF_TX_CS_RIGHT_IC_1_SHIFT 0

/* SPDIF_TX_CS_RIGHT_5 (IC 1) */
#define R424_SPDIF_TX_CS_RIGHT_5_SPDIF_TX_CS_RIGHT_IC_1 0x0000 /* 0000000000000000b	[15:0] */
#define R424_SPDIF_TX_CS_RIGHT_5_SPDIF_TX_CS_RIGHT_IC_1_MASK 0xFFFF
#define R424_SPDIF_TX_CS_RIGHT_5_SPDIF_TX_CS_RIGHT_IC_1_SHIFT 0

/* SPDIF_TX_CS_RIGHT_6 (IC 1) */
#define R425_SPDIF_TX_CS_RIGHT_6_SPDIF_TX_CS_RIGHT_IC_1 0x0000 /* 0000000000000000b	[15:0] */
#define R425_SPDIF_TX_CS_RIGHT_6_SPDIF_TX_CS_RIGHT_IC_1_MASK 0xFFFF
#define R425_SPDIF_TX_CS_RIGHT_6_SPDIF_TX_CS_RIGHT_IC_1_SHIFT 0

/* SPDIF_TX_CS_RIGHT_7 (IC 1) */
#define R426_SPDIF_TX_CS_RIGHT_7_SPDIF_TX_CS_RIGHT_IC_1 0x0000 /* 0000000000000000b	[15:0] */
#define R426_SPDIF_TX_CS_RIGHT_7_SPDIF_TX_CS_RIGHT_IC_1_MASK 0xFFFF
#define R426_SPDIF_TX_CS_RIGHT_7_SPDIF_TX_CS_RIGHT_IC_1_SHIFT 0

/* SPDIF_TX_CS_RIGHT_8 (IC 1) */
#define R427_SPDIF_TX_CS_RIGHT_8_SPDIF_TX_CS_RIGHT_IC_1 0x0000 /* 0000000000000000b	[15:0] */
#define R427_SPDIF_TX_CS_RIGHT_8_SPDIF_TX_CS_RIGHT_IC_1_MASK 0xFFFF
#define R427_SPDIF_TX_CS_RIGHT_8_SPDIF_TX_CS_RIGHT_IC_1_SHIFT 0

/* SPDIF_TX_CS_RIGHT_9 (IC 1) */
#define R428_SPDIF_TX_CS_RIGHT_9_SPDIF_TX_CS_RIGHT_IC_1 0x0000 /* 0000000000000000b	[15:0] */
#define R428_SPDIF_TX_CS_RIGHT_9_SPDIF_TX_CS_RIGHT_IC_1_MASK 0xFFFF
#define R428_SPDIF_TX_CS_RIGHT_9_SPDIF_TX_CS_RIGHT_IC_1_SHIFT 0

/* SPDIF_TX_CS_RIGHT_10 (IC 1) */
#define R429_SPDIF_TX_CS_RIGHT_10_SPDIF_TX_CS_RIGHT_IC_1 0x0000 /* 0000000000000000b	[15:0] */
#define R429_SPDIF_TX_CS_RIGHT_10_SPDIF_TX_CS_RIGHT_IC_1_MASK 0xFFFF
#define R429_SPDIF_TX_CS_RIGHT_10_SPDIF_TX_CS_RIGHT_IC_1_SHIFT 0

/* SPDIF_TX_CS_RIGHT_11 (IC 1) */
#define R430_SPDIF_TX_CS_RIGHT_11_SPDIF_TX_CS_RIGHT_IC_1 0x0000 /* 0000000000000000b	[15:0] */
#define R430_SPDIF_TX_CS_RIGHT_11_SPDIF_TX_CS_RIGHT_IC_1_MASK 0xFFFF
#define R430_SPDIF_TX_CS_RIGHT_11_SPDIF_TX_CS_RIGHT_IC_1_SHIFT 0

/* SPDIF_TX_UD_LEFT_0 (IC 1) */
#define R431_SPDIF_TX_UD_LEFT_0_SPDIF_TX_UD_LEFT_IC_1 0x0000 /* 0000000000000000b	[15:0] */
#define R431_SPDIF_TX_UD_LEFT_0_SPDIF_TX_UD_LEFT_IC_1_MASK 0xFFFF
#define R431_SPDIF_TX_UD_LEFT_0_SPDIF_TX_UD_LEFT_IC_1_SHIFT 0

/* SPDIF_TX_UD_LEFT_1 (IC 1) */
#define R432_SPDIF_TX_UD_LEFT_1_SPDIF_TX_UD_LEFT_IC_1 0x0000 /* 0000000000000000b	[15:0] */
#define R432_SPDIF_TX_UD_LEFT_1_SPDIF_TX_UD_LEFT_IC_1_MASK 0xFFFF
#define R432_SPDIF_TX_UD_LEFT_1_SPDIF_TX_UD_LEFT_IC_1_SHIFT 0

/* SPDIF_TX_UD_LEFT_2 (IC 1) */
#define R433_SPDIF_TX_UD_LEFT_2_SPDIF_TX_UD_LEFT_IC_1 0x0000 /* 0000000000000000b	[15:0] */
#define R433_SPDIF_TX_UD_LEFT_2_SPDIF_TX_UD_LEFT_IC_1_MASK 0xFFFF
#define R433_SPDIF_TX_UD_LEFT_2_SPDIF_TX_UD_LEFT_IC_1_SHIFT 0

/* SPDIF_TX_UD_LEFT_3 (IC 1) */
#define R434_SPDIF_TX_UD_LEFT_3_SPDIF_TX_UD_LEFT_IC_1 0x0000 /* 0000000000000000b	[15:0] */
#define R434_SPDIF_TX_UD_LEFT_3_SPDIF_TX_UD_LEFT_IC_1_MASK 0xFFFF
#define R434_SPDIF_TX_UD_LEFT_3_SPDIF_TX_UD_LEFT_IC_1_SHIFT 0

/* SPDIF_TX_UD_LEFT_4 (IC 1) */
#define R435_SPDIF_TX_UD_LEFT_4_SPDIF_TX_UD_LEFT_IC_1 0x0000 /* 0000000000000000b	[15:0] */
#define R435_SPDIF_TX_UD_LEFT_4_SPDIF_TX_UD_LEFT_IC_1_MASK 0xFFFF
#define R435_SPDIF_TX_UD_LEFT_4_SPDIF_TX_UD_LEFT_IC_1_SHIFT 0

/* SPDIF_TX_UD_LEFT_5 (IC 1) */
#define R436_SPDIF_TX_UD_LEFT_5_SPDIF_TX_UD_LEFT_IC_1 0x0000 /* 0000000000000000b	[15:0] */
#define R436_SPDIF_TX_UD_LEFT_5_SPDIF_TX_UD_LEFT_IC_1_MASK 0xFFFF
#define R436_SPDIF_TX_UD_LEFT_5_SPDIF_TX_UD_LEFT_IC_1_SHIFT 0

/* SPDIF_TX_UD_LEFT_6 (IC 1) */
#define R437_SPDIF_TX_UD_LEFT_6_SPDIF_TX_UD_LEFT_IC_1 0x0000 /* 0000000000000000b	[15:0] */
#define R437_SPDIF_TX_UD_LEFT_6_SPDIF_TX_UD_LEFT_IC_1_MASK 0xFFFF
#define R437_SPDIF_TX_UD_LEFT_6_SPDIF_TX_UD_LEFT_IC_1_SHIFT 0

/* SPDIF_TX_UD_LEFT_7 (IC 1) */
#define R438_SPDIF_TX_UD_LEFT_7_SPDIF_TX_UD_LEFT_IC_1 0x0000 /* 0000000000000000b	[15:0] */
#define R438_SPDIF_TX_UD_LEFT_7_SPDIF_TX_UD_LEFT_IC_1_MASK 0xFFFF
#define R438_SPDIF_TX_UD_LEFT_7_SPDIF_TX_UD_LEFT_IC_1_SHIFT 0

/* SPDIF_TX_UD_LEFT_8 (IC 1) */
#define R439_SPDIF_TX_UD_LEFT_8_SPDIF_TX_UD_LEFT_IC_1 0x0000 /* 0000000000000000b	[15:0] */
#define R439_SPDIF_TX_UD_LEFT_8_SPDIF_TX_UD_LEFT_IC_1_MASK 0xFFFF
#define R439_SPDIF_TX_UD_LEFT_8_SPDIF_TX_UD_LEFT_IC_1_SHIFT 0

/* SPDIF_TX_UD_LEFT_9 (IC 1) */
#define R440_SPDIF_TX_UD_LEFT_9_SPDIF_TX_UD_LEFT_IC_1 0x0000 /* 0000000000000000b	[15:0] */
#define R440_SPDIF_TX_UD_LEFT_9_SPDIF_TX_UD_LEFT_IC_1_MASK 0xFFFF
#define R440_SPDIF_TX_UD_LEFT_9_SPDIF_TX_UD_LEFT_IC_1_SHIFT 0

/* SPDIF_TX_UD_LEFT_10 (IC 1) */
#define R441_SPDIF_TX_UD_LEFT_10_SPDIF_TX_UD_LEFT_IC_1 0x0000 /* 0000000000000000b	[15:0] */
#define R441_SPDIF_TX_UD_LEFT_10_SPDIF_TX_UD_LEFT_IC_1_MASK 0xFFFF
#define R441_SPDIF_TX_UD_LEFT_10_SPDIF_TX_UD_LEFT_IC_1_SHIFT 0

/* SPDIF_TX_UD_LEFT_11 (IC 1) */
#define R442_SPDIF_TX_UD_LEFT_11_SPDIF_TX_UD_LEFT_IC_1 0x0000 /* 0000000000000000b	[15:0] */
#define R442_SPDIF_TX_UD_LEFT_11_SPDIF_TX_UD_LEFT_IC_1_MASK 0xFFFF
#define R442_SPDIF_TX_UD_LEFT_11_SPDIF_TX_UD_LEFT_IC_1_SHIFT 0

/* SPDIF_TX_UD_RIGHT_0 (IC 1) */
#define R443_SPDIF_TX_UD_RIGHT_0_SPDIF_TX_UD_RIGHT_IC_1 0x0000 /* 0000000000000000b	[15:0] */
#define R443_SPDIF_TX_UD_RIGHT_0_SPDIF_TX_UD_RIGHT_IC_1_MASK 0xFFFF
#define R443_SPDIF_TX_UD_RIGHT_0_SPDIF_TX_UD_RIGHT_IC_1_SHIFT 0

/* SPDIF_TX_UD_RIGHT_1 (IC 1) */
#define R444_SPDIF_TX_UD_RIGHT_1_SPDIF_TX_UD_RIGHT_IC_1 0x0000 /* 0000000000000000b	[15:0] */
#define R444_SPDIF_TX_UD_RIGHT_1_SPDIF_TX_UD_RIGHT_IC_1_MASK 0xFFFF
#define R444_SPDIF_TX_UD_RIGHT_1_SPDIF_TX_UD_RIGHT_IC_1_SHIFT 0

/* SPDIF_TX_UD_RIGHT_2 (IC 1) */
#define R445_SPDIF_TX_UD_RIGHT_2_SPDIF_TX_UD_RIGHT_IC_1 0x0000 /* 0000000000000000b	[15:0] */
#define R445_SPDIF_TX_UD_RIGHT_2_SPDIF_TX_UD_RIGHT_IC_1_MASK 0xFFFF
#define R445_SPDIF_TX_UD_RIGHT_2_SPDIF_TX_UD_RIGHT_IC_1_SHIFT 0

/* SPDIF_TX_UD_RIGHT_3 (IC 1) */
#define R446_SPDIF_TX_UD_RIGHT_3_SPDIF_TX_UD_RIGHT_IC_1 0x0000 /* 0000000000000000b	[15:0] */
#define R446_SPDIF_TX_UD_RIGHT_3_SPDIF_TX_UD_RIGHT_IC_1_MASK 0xFFFF
#define R446_SPDIF_TX_UD_RIGHT_3_SPDIF_TX_UD_RIGHT_IC_1_SHIFT 0

/* SPDIF_TX_UD_RIGHT_4 (IC 1) */
#define R447_SPDIF_TX_UD_RIGHT_4_SPDIF_TX_UD_RIGHT_IC_1 0x0000 /* 0000000000000000b	[15:0] */
#define R447_SPDIF_TX_UD_RIGHT_4_SPDIF_TX_UD_RIGHT_IC_1_MASK 0xFFFF
#define R447_SPDIF_TX_UD_RIGHT_4_SPDIF_TX_UD_RIGHT_IC_1_SHIFT 0

/* SPDIF_TX_UD_RIGHT_5 (IC 1) */
#define R448_SPDIF_TX_UD_RIGHT_5_SPDIF_TX_UD_RIGHT_IC_1 0x0000 /* 0000000000000000b	[15:0] */
#define R448_SPDIF_TX_UD_RIGHT_5_SPDIF_TX_UD_RIGHT_IC_1_MASK 0xFFFF
#define R448_SPDIF_TX_UD_RIGHT_5_SPDIF_TX_UD_RIGHT_IC_1_SHIFT 0

/* SPDIF_TX_UD_RIGHT_6 (IC 1) */
#define R449_SPDIF_TX_UD_RIGHT_6_SPDIF_TX_UD_RIGHT_IC_1 0x0000 /* 0000000000000000b	[15:0] */
#define R449_SPDIF_TX_UD_RIGHT_6_SPDIF_TX_UD_RIGHT_IC_1_MASK 0xFFFF
#define R449_SPDIF_TX_UD_RIGHT_6_SPDIF_TX_UD_RIGHT_IC_1_SHIFT 0

/* SPDIF_TX_UD_RIGHT_7 (IC 1) */
#define R450_SPDIF_TX_UD_RIGHT_7_SPDIF_TX_UD_RIGHT_IC_1 0x0000 /* 0000000000000000b	[15:0] */
#define R450_SPDIF_TX_UD_RIGHT_7_SPDIF_TX_UD_RIGHT_IC_1_MASK 0xFFFF
#define R450_SPDIF_TX_UD_RIGHT_7_SPDIF_TX_UD_RIGHT_IC_1_SHIFT 0

/* SPDIF_TX_UD_RIGHT_8 (IC 1) */
#define R451_SPDIF_TX_UD_RIGHT_8_SPDIF_TX_UD_RIGHT_IC_1 0x0000 /* 0000000000000000b	[15:0] */
#define R451_SPDIF_TX_UD_RIGHT_8_SPDIF_TX_UD_RIGHT_IC_1_MASK 0xFFFF
#define R451_SPDIF_TX_UD_RIGHT_8_SPDIF_TX_UD_RIGHT_IC_1_SHIFT 0

/* SPDIF_TX_UD_RIGHT_9 (IC 1) */
#define R452_SPDIF_TX_UD_RIGHT_9_SPDIF_TX_UD_RIGHT_IC_1 0x0000 /* 0000000000000000b	[15:0] */
#define R452_SPDIF_TX_UD_RIGHT_9_SPDIF_TX_UD_RIGHT_IC_1_MASK 0xFFFF
#define R452_SPDIF_TX_UD_RIGHT_9_SPDIF_TX_UD_RIGHT_IC_1_SHIFT 0

/* SPDIF_TX_UD_RIGHT_10 (IC 1) */
#define R453_SPDIF_TX_UD_RIGHT_10_SPDIF_TX_UD_RIGHT_IC_1 0x0000 /* 0000000000000000b	[15:0] */
#define R453_SPDIF_TX_UD_RIGHT_10_SPDIF_TX_UD_RIGHT_IC_1_MASK 0xFFFF
#define R453_SPDIF_TX_UD_RIGHT_10_SPDIF_TX_UD_RIGHT_IC_1_SHIFT 0

/* SPDIF_TX_UD_RIGHT_11 (IC 1) */
#define R454_SPDIF_TX_UD_RIGHT_11_SPDIF_TX_UD_RIGHT_IC_1 0x0000 /* 0000000000000000b	[15:0] */
#define R454_SPDIF_TX_UD_RIGHT_11_SPDIF_TX_UD_RIGHT_IC_1_MASK 0xFFFF
#define R454_SPDIF_TX_UD_RIGHT_11_SPDIF_TX_UD_RIGHT_IC_1_SHIFT 0

/* SPDIF_TX_VB_LEFT_0 (IC 1) */
#define R455_SPDIF_TX_VB_LEFT_0_SPDIF_TX_VB_LEFT_IC_1 0x0000 /* 0000000000000000b	[15:0] */
#define R455_SPDIF_TX_VB_LEFT_0_SPDIF_TX_VB_LEFT_IC_1_MASK 0xFFFF
#define R455_SPDIF_TX_VB_LEFT_0_SPDIF_TX_VB_LEFT_IC_1_SHIFT 0

/* SPDIF_TX_VB_LEFT_1 (IC 1) */
#define R456_SPDIF_TX_VB_LEFT_1_SPDIF_TX_VB_LEFT_IC_1 0x0000 /* 0000000000000000b	[15:0] */
#define R456_SPDIF_TX_VB_LEFT_1_SPDIF_TX_VB_LEFT_IC_1_MASK 0xFFFF
#define R456_SPDIF_TX_VB_LEFT_1_SPDIF_TX_VB_LEFT_IC_1_SHIFT 0

/* SPDIF_TX_VB_LEFT_2 (IC 1) */
#define R457_SPDIF_TX_VB_LEFT_2_SPDIF_TX_VB_LEFT_IC_1 0x0000 /* 0000000000000000b	[15:0] */
#define R457_SPDIF_TX_VB_LEFT_2_SPDIF_TX_VB_LEFT_IC_1_MASK 0xFFFF
#define R457_SPDIF_TX_VB_LEFT_2_SPDIF_TX_VB_LEFT_IC_1_SHIFT 0

/* SPDIF_TX_VB_LEFT_3 (IC 1) */
#define R458_SPDIF_TX_VB_LEFT_3_SPDIF_TX_VB_LEFT_IC_1 0x0000 /* 0000000000000000b	[15:0] */
#define R458_SPDIF_TX_VB_LEFT_3_SPDIF_TX_VB_LEFT_IC_1_MASK 0xFFFF
#define R458_SPDIF_TX_VB_LEFT_3_SPDIF_TX_VB_LEFT_IC_1_SHIFT 0

/* SPDIF_TX_VB_LEFT_4 (IC 1) */
#define R459_SPDIF_TX_VB_LEFT_4_SPDIF_TX_VB_LEFT_IC_1 0x0000 /* 0000000000000000b	[15:0] */
#define R459_SPDIF_TX_VB_LEFT_4_SPDIF_TX_VB_LEFT_IC_1_MASK 0xFFFF
#define R459_SPDIF_TX_VB_LEFT_4_SPDIF_TX_VB_LEFT_IC_1_SHIFT 0

/* SPDIF_TX_VB_LEFT_5 (IC 1) */
#define R460_SPDIF_TX_VB_LEFT_5_SPDIF_TX_VB_LEFT_IC_1 0x0000 /* 0000000000000000b	[15:0] */
#define R460_SPDIF_TX_VB_LEFT_5_SPDIF_TX_VB_LEFT_IC_1_MASK 0xFFFF
#define R460_SPDIF_TX_VB_LEFT_5_SPDIF_TX_VB_LEFT_IC_1_SHIFT 0

/* SPDIF_TX_VB_LEFT_6 (IC 1) */
#define R461_SPDIF_TX_VB_LEFT_6_SPDIF_TX_VB_LEFT_IC_1 0x0000 /* 0000000000000000b	[15:0] */
#define R461_SPDIF_TX_VB_LEFT_6_SPDIF_TX_VB_LEFT_IC_1_MASK 0xFFFF
#define R461_SPDIF_TX_VB_LEFT_6_SPDIF_TX_VB_LEFT_IC_1_SHIFT 0

/* SPDIF_TX_VB_LEFT_7 (IC 1) */
#define R462_SPDIF_TX_VB_LEFT_7_SPDIF_TX_VB_LEFT_IC_1 0x0000 /* 0000000000000000b	[15:0] */
#define R462_SPDIF_TX_VB_LEFT_7_SPDIF_TX_VB_LEFT_IC_1_MASK 0xFFFF
#define R462_SPDIF_TX_VB_LEFT_7_SPDIF_TX_VB_LEFT_IC_1_SHIFT 0

/* SPDIF_TX_VB_LEFT_8 (IC 1) */
#define R463_SPDIF_TX_VB_LEFT_8_SPDIF_TX_VB_LEFT_IC_1 0x0000 /* 0000000000000000b	[15:0] */
#define R463_SPDIF_TX_VB_LEFT_8_SPDIF_TX_VB_LEFT_IC_1_MASK 0xFFFF
#define R463_SPDIF_TX_VB_LEFT_8_SPDIF_TX_VB_LEFT_IC_1_SHIFT 0

/* SPDIF_TX_VB_LEFT_9 (IC 1) */
#define R464_SPDIF_TX_VB_LEFT_9_SPDIF_TX_VB_LEFT_IC_1 0x0000 /* 0000000000000000b	[15:0] */
#define R464_SPDIF_TX_VB_LEFT_9_SPDIF_TX_VB_LEFT_IC_1_MASK 0xFFFF
#define R464_SPDIF_TX_VB_LEFT_9_SPDIF_TX_VB_LEFT_IC_1_SHIFT 0

/* SPDIF_TX_VB_LEFT_10 (IC 1) */
#define R465_SPDIF_TX_VB_LEFT_10_SPDIF_TX_VB_LEFT_IC_1 0x0000 /* 0000000000000000b	[15:0] */
#define R465_SPDIF_TX_VB_LEFT_10_SPDIF_TX_VB_LEFT_IC_1_MASK 0xFFFF
#define R465_SPDIF_TX_VB_LEFT_10_SPDIF_TX_VB_LEFT_IC_1_SHIFT 0

/* SPDIF_TX_VB_LEFT_11 (IC 1) */
#define R466_SPDIF_TX_VB_LEFT_11_SPDIF_TX_VB_LEFT_IC_1 0x0000 /* 0000000000000000b	[15:0] */
#define R466_SPDIF_TX_VB_LEFT_11_SPDIF_TX_VB_LEFT_IC_1_MASK 0xFFFF
#define R466_SPDIF_TX_VB_LEFT_11_SPDIF_TX_VB_LEFT_IC_1_SHIFT 0

/* SPDIF_TX_VB_RIGHT_0 (IC 1) */
#define R467_SPDIF_TX_VB_RIGHT_0_SPDIF_TX_VB_RIGHT_IC_1 0x0000 /* 0000000000000000b	[15:0] */
#define R467_SPDIF_TX_VB_RIGHT_0_SPDIF_TX_VB_RIGHT_IC_1_MASK 0xFFFF
#define R467_SPDIF_TX_VB_RIGHT_0_SPDIF_TX_VB_RIGHT_IC_1_SHIFT 0

/* SPDIF_TX_VB_RIGHT_1 (IC 1) */
#define R468_SPDIF_TX_VB_RIGHT_1_SPDIF_TX_VB_RIGHT_IC_1 0x0000 /* 0000000000000000b	[15:0] */
#define R468_SPDIF_TX_VB_RIGHT_1_SPDIF_TX_VB_RIGHT_IC_1_MASK 0xFFFF
#define R468_SPDIF_TX_VB_RIGHT_1_SPDIF_TX_VB_RIGHT_IC_1_SHIFT 0

/* SPDIF_TX_VB_RIGHT_2 (IC 1) */
#define R469_SPDIF_TX_VB_RIGHT_2_SPDIF_TX_VB_RIGHT_IC_1 0x0000 /* 0000000000000000b	[15:0] */
#define R469_SPDIF_TX_VB_RIGHT_2_SPDIF_TX_VB_RIGHT_IC_1_MASK 0xFFFF
#define R469_SPDIF_TX_VB_RIGHT_2_SPDIF_TX_VB_RIGHT_IC_1_SHIFT 0

/* SPDIF_TX_VB_RIGHT_3 (IC 1) */
#define R470_SPDIF_TX_VB_RIGHT_3_SPDIF_TX_VB_RIGHT_IC_1 0x0000 /* 0000000000000000b	[15:0] */
#define R470_SPDIF_TX_VB_RIGHT_3_SPDIF_TX_VB_RIGHT_IC_1_MASK 0xFFFF
#define R470_SPDIF_TX_VB_RIGHT_3_SPDIF_TX_VB_RIGHT_IC_1_SHIFT 0

/* SPDIF_TX_VB_RIGHT_4 (IC 1) */
#define R471_SPDIF_TX_VB_RIGHT_4_SPDIF_TX_VB_RIGHT_IC_1 0x0000 /* 0000000000000000b	[15:0] */
#define R471_SPDIF_TX_VB_RIGHT_4_SPDIF_TX_VB_RIGHT_IC_1_MASK 0xFFFF
#define R471_SPDIF_TX_VB_RIGHT_4_SPDIF_TX_VB_RIGHT_IC_1_SHIFT 0

/* SPDIF_TX_VB_RIGHT_5 (IC 1) */
#define R472_SPDIF_TX_VB_RIGHT_5_SPDIF_TX_VB_RIGHT_IC_1 0x0000 /* 0000000000000000b	[15:0] */
#define R472_SPDIF_TX_VB_RIGHT_5_SPDIF_TX_VB_RIGHT_IC_1_MASK 0xFFFF
#define R472_SPDIF_TX_VB_RIGHT_5_SPDIF_TX_VB_RIGHT_IC_1_SHIFT 0

/* SPDIF_TX_VB_RIGHT_6 (IC 1) */
#define R473_SPDIF_TX_VB_RIGHT_6_SPDIF_TX_VB_RIGHT_IC_1 0x0000 /* 0000000000000000b	[15:0] */
#define R473_SPDIF_TX_VB_RIGHT_6_SPDIF_TX_VB_RIGHT_IC_1_MASK 0xFFFF
#define R473_SPDIF_TX_VB_RIGHT_6_SPDIF_TX_VB_RIGHT_IC_1_SHIFT 0

/* SPDIF_TX_VB_RIGHT_7 (IC 1) */
#define R474_SPDIF_TX_VB_RIGHT_7_SPDIF_TX_VB_RIGHT_IC_1 0x0000 /* 0000000000000000b	[15:0] */
#define R474_SPDIF_TX_VB_RIGHT_7_SPDIF_TX_VB_RIGHT_IC_1_MASK 0xFFFF
#define R474_SPDIF_TX_VB_RIGHT_7_SPDIF_TX_VB_RIGHT_IC_1_SHIFT 0

/* SPDIF_TX_VB_RIGHT_8 (IC 1) */
#define R475_SPDIF_TX_VB_RIGHT_8_SPDIF_TX_VB_RIGHT_IC_1 0x0000 /* 0000000000000000b	[15:0] */
#define R475_SPDIF_TX_VB_RIGHT_8_SPDIF_TX_VB_RIGHT_IC_1_MASK 0xFFFF
#define R475_SPDIF_TX_VB_RIGHT_8_SPDIF_TX_VB_RIGHT_IC_1_SHIFT 0

/* SPDIF_TX_VB_RIGHT_9 (IC 1) */
#define R476_SPDIF_TX_VB_RIGHT_9_SPDIF_TX_VB_RIGHT_IC_1 0x0000 /* 0000000000000000b	[15:0] */
#define R476_SPDIF_TX_VB_RIGHT_9_SPDIF_TX_VB_RIGHT_IC_1_MASK 0xFFFF
#define R476_SPDIF_TX_VB_RIGHT_9_SPDIF_TX_VB_RIGHT_IC_1_SHIFT 0

/* SPDIF_TX_VB_RIGHT_10 (IC 1) */
#define R477_SPDIF_TX_VB_RIGHT_10_SPDIF_TX_VB_RIGHT_IC_1 0x0000 /* 0000000000000000b	[15:0] */
#define R477_SPDIF_TX_VB_RIGHT_10_SPDIF_TX_VB_RIGHT_IC_1_MASK 0xFFFF
#define R477_SPDIF_TX_VB_RIGHT_10_SPDIF_TX_VB_RIGHT_IC_1_SHIFT 0

/* SPDIF_TX_VB_RIGHT_11 (IC 1) */
#define R478_SPDIF_TX_VB_RIGHT_11_SPDIF_TX_VB_RIGHT_IC_1 0x0000 /* 0000000000000000b	[15:0] */
#define R478_SPDIF_TX_VB_RIGHT_11_SPDIF_TX_VB_RIGHT_IC_1_MASK 0xFFFF
#define R478_SPDIF_TX_VB_RIGHT_11_SPDIF_TX_VB_RIGHT_IC_1_SHIFT 0

/* SPDIF_TX_PB_LEFT_0 (IC 1) */
#define R479_SPDIF_TX_PB_LEFT_0_SPDIF_TX_PB_LEFT_IC_1 0x0000 /* 0000000000000000b	[15:0] */
#define R479_SPDIF_TX_PB_LEFT_0_SPDIF_TX_PB_LEFT_IC_1_MASK 0xFFFF
#define R479_SPDIF_TX_PB_LEFT_0_SPDIF_TX_PB_LEFT_IC_1_SHIFT 0

/* SPDIF_TX_PB_LEFT_1 (IC 1) */
#define R480_SPDIF_TX_PB_LEFT_1_SPDIF_TX_PB_LEFT_IC_1 0x0000 /* 0000000000000000b	[15:0] */
#define R480_SPDIF_TX_PB_LEFT_1_SPDIF_TX_PB_LEFT_IC_1_MASK 0xFFFF
#define R480_SPDIF_TX_PB_LEFT_1_SPDIF_TX_PB_LEFT_IC_1_SHIFT 0

/* SPDIF_TX_PB_LEFT_2 (IC 1) */
#define R481_SPDIF_TX_PB_LEFT_2_SPDIF_TX_PB_LEFT_IC_1 0x0000 /* 0000000000000000b	[15:0] */
#define R481_SPDIF_TX_PB_LEFT_2_SPDIF_TX_PB_LEFT_IC_1_MASK 0xFFFF
#define R481_SPDIF_TX_PB_LEFT_2_SPDIF_TX_PB_LEFT_IC_1_SHIFT 0

/* SPDIF_TX_PB_LEFT_3 (IC 1) */
#define R482_SPDIF_TX_PB_LEFT_3_SPDIF_TX_PB_LEFT_IC_1 0x0000 /* 0000000000000000b	[15:0] */
#define R482_SPDIF_TX_PB_LEFT_3_SPDIF_TX_PB_LEFT_IC_1_MASK 0xFFFF
#define R482_SPDIF_TX_PB_LEFT_3_SPDIF_TX_PB_LEFT_IC_1_SHIFT 0

/* SPDIF_TX_PB_LEFT_4 (IC 1) */
#define R483_SPDIF_TX_PB_LEFT_4_SPDIF_TX_PB_LEFT_IC_1 0x0000 /* 0000000000000000b	[15:0] */
#define R483_SPDIF_TX_PB_LEFT_4_SPDIF_TX_PB_LEFT_IC_1_MASK 0xFFFF
#define R483_SPDIF_TX_PB_LEFT_4_SPDIF_TX_PB_LEFT_IC_1_SHIFT 0

/* SPDIF_TX_PB_LEFT_5 (IC 1) */
#define R484_SPDIF_TX_PB_LEFT_5_SPDIF_TX_PB_LEFT_IC_1 0x0000 /* 0000000000000000b	[15:0] */
#define R484_SPDIF_TX_PB_LEFT_5_SPDIF_TX_PB_LEFT_IC_1_MASK 0xFFFF
#define R484_SPDIF_TX_PB_LEFT_5_SPDIF_TX_PB_LEFT_IC_1_SHIFT 0

/* SPDIF_TX_PB_LEFT_6 (IC 1) */
#define R485_SPDIF_TX_PB_LEFT_6_SPDIF_TX_PB_LEFT_IC_1 0x0000 /* 0000000000000000b	[15:0] */
#define R485_SPDIF_TX_PB_LEFT_6_SPDIF_TX_PB_LEFT_IC_1_MASK 0xFFFF
#define R485_SPDIF_TX_PB_LEFT_6_SPDIF_TX_PB_LEFT_IC_1_SHIFT 0

/* SPDIF_TX_PB_LEFT_7 (IC 1) */
#define R486_SPDIF_TX_PB_LEFT_7_SPDIF_TX_PB_LEFT_IC_1 0x0000 /* 0000000000000000b	[15:0] */
#define R486_SPDIF_TX_PB_LEFT_7_SPDIF_TX_PB_LEFT_IC_1_MASK 0xFFFF
#define R486_SPDIF_TX_PB_LEFT_7_SPDIF_TX_PB_LEFT_IC_1_SHIFT 0

/* SPDIF_TX_PB_LEFT_8 (IC 1) */
#define R487_SPDIF_TX_PB_LEFT_8_SPDIF_TX_PB_LEFT_IC_1 0x0000 /* 0000000000000000b	[15:0] */
#define R487_SPDIF_TX_PB_LEFT_8_SPDIF_TX_PB_LEFT_IC_1_MASK 0xFFFF
#define R487_SPDIF_TX_PB_LEFT_8_SPDIF_TX_PB_LEFT_IC_1_SHIFT 0

/* SPDIF_TX_PB_LEFT_9 (IC 1) */
#define R488_SPDIF_TX_PB_LEFT_9_SPDIF_TX_PB_LEFT_IC_1 0x0000 /* 0000000000000000b	[15:0] */
#define R488_SPDIF_TX_PB_LEFT_9_SPDIF_TX_PB_LEFT_IC_1_MASK 0xFFFF
#define R488_SPDIF_TX_PB_LEFT_9_SPDIF_TX_PB_LEFT_IC_1_SHIFT 0

/* SPDIF_TX_PB_LEFT_10 (IC 1) */
#define R489_SPDIF_TX_PB_LEFT_10_SPDIF_TX_PB_LEFT_IC_1 0x0000 /* 0000000000000000b	[15:0] */
#define R489_SPDIF_TX_PB_LEFT_10_SPDIF_TX_PB_LEFT_IC_1_MASK 0xFFFF
#define R489_SPDIF_TX_PB_LEFT_10_SPDIF_TX_PB_LEFT_IC_1_SHIFT 0

/* SPDIF_TX_PB_LEFT_11 (IC 1) */
#define R490_SPDIF_TX_PB_LEFT_11_SPDIF_TX_PB_LEFT_IC_1 0x0000 /* 0000000000000000b	[15:0] */
#define R490_SPDIF_TX_PB_LEFT_11_SPDIF_TX_PB_LEFT_IC_1_MASK 0xFFFF
#define R490_SPDIF_TX_PB_LEFT_11_SPDIF_TX_PB_LEFT_IC_1_SHIFT 0

/* SPDIF_TX_PB_RIGHT_0 (IC 1) */
#define R491_SPDIF_TX_PB_RIGHT_0_SPDIF_TX_PB_RIGHT_IC_1 0x0000 /* 0000000000000000b	[15:0] */
#define R491_SPDIF_TX_PB_RIGHT_0_SPDIF_TX_PB_RIGHT_IC_1_MASK 0xFFFF
#define R491_SPDIF_TX_PB_RIGHT_0_SPDIF_TX_PB_RIGHT_IC_1_SHIFT 0

/* SPDIF_TX_PB_RIGHT_1 (IC 1) */
#define R492_SPDIF_TX_PB_RIGHT_1_SPDIF_TX_PB_RIGHT_IC_1 0x0000 /* 0000000000000000b	[15:0] */
#define R492_SPDIF_TX_PB_RIGHT_1_SPDIF_TX_PB_RIGHT_IC_1_MASK 0xFFFF
#define R492_SPDIF_TX_PB_RIGHT_1_SPDIF_TX_PB_RIGHT_IC_1_SHIFT 0

/* SPDIF_TX_PB_RIGHT_2 (IC 1) */
#define R493_SPDIF_TX_PB_RIGHT_2_SPDIF_TX_PB_RIGHT_IC_1 0x0000 /* 0000000000000000b	[15:0] */
#define R493_SPDIF_TX_PB_RIGHT_2_SPDIF_TX_PB_RIGHT_IC_1_MASK 0xFFFF
#define R493_SPDIF_TX_PB_RIGHT_2_SPDIF_TX_PB_RIGHT_IC_1_SHIFT 0

/* SPDIF_TX_PB_RIGHT_3 (IC 1) */
#define R494_SPDIF_TX_PB_RIGHT_3_SPDIF_TX_PB_RIGHT_IC_1 0x0000 /* 0000000000000000b	[15:0] */
#define R494_SPDIF_TX_PB_RIGHT_3_SPDIF_TX_PB_RIGHT_IC_1_MASK 0xFFFF
#define R494_SPDIF_TX_PB_RIGHT_3_SPDIF_TX_PB_RIGHT_IC_1_SHIFT 0

/* SPDIF_TX_PB_RIGHT_4 (IC 1) */
#define R495_SPDIF_TX_PB_RIGHT_4_SPDIF_TX_PB_RIGHT_IC_1 0x0000 /* 0000000000000000b	[15:0] */
#define R495_SPDIF_TX_PB_RIGHT_4_SPDIF_TX_PB_RIGHT_IC_1_MASK 0xFFFF
#define R495_SPDIF_TX_PB_RIGHT_4_SPDIF_TX_PB_RIGHT_IC_1_SHIFT 0

/* SPDIF_TX_PB_RIGHT_5 (IC 1) */
#define R496_SPDIF_TX_PB_RIGHT_5_SPDIF_TX_PB_RIGHT_IC_1 0x0000 /* 0000000000000000b	[15:0] */
#define R496_SPDIF_TX_PB_RIGHT_5_SPDIF_TX_PB_RIGHT_IC_1_MASK 0xFFFF
#define R496_SPDIF_TX_PB_RIGHT_5_SPDIF_TX_PB_RIGHT_IC_1_SHIFT 0

/* SPDIF_TX_PB_RIGHT_6 (IC 1) */
#define R497_SPDIF_TX_PB_RIGHT_6_SPDIF_TX_PB_RIGHT_IC_1 0x0000 /* 0000000000000000b	[15:0] */
#define R497_SPDIF_TX_PB_RIGHT_6_SPDIF_TX_PB_RIGHT_IC_1_MASK 0xFFFF
#define R497_SPDIF_TX_PB_RIGHT_6_SPDIF_TX_PB_RIGHT_IC_1_SHIFT 0

/* SPDIF_TX_PB_RIGHT_7 (IC 1) */
#define R498_SPDIF_TX_PB_RIGHT_7_SPDIF_TX_PB_RIGHT_IC_1 0x0000 /* 0000000000000000b	[15:0] */
#define R498_SPDIF_TX_PB_RIGHT_7_SPDIF_TX_PB_RIGHT_IC_1_MASK 0xFFFF
#define R498_SPDIF_TX_PB_RIGHT_7_SPDIF_TX_PB_RIGHT_IC_1_SHIFT 0

/* SPDIF_TX_PB_RIGHT_8 (IC 1) */
#define R499_SPDIF_TX_PB_RIGHT_8_SPDIF_TX_PB_RIGHT_IC_1 0x0000 /* 0000000000000000b	[15:0] */
#define R499_SPDIF_TX_PB_RIGHT_8_SPDIF_TX_PB_RIGHT_IC_1_MASK 0xFFFF
#define R499_SPDIF_TX_PB_RIGHT_8_SPDIF_TX_PB_RIGHT_IC_1_SHIFT 0

/* SPDIF_TX_PB_RIGHT_9 (IC 1) */
#define R500_SPDIF_TX_PB_RIGHT_9_SPDIF_TX_PB_RIGHT_IC_1 0x0000 /* 0000000000000000b	[15:0] */
#define R500_SPDIF_TX_PB_RIGHT_9_SPDIF_TX_PB_RIGHT_IC_1_MASK 0xFFFF
#define R500_SPDIF_TX_PB_RIGHT_9_SPDIF_TX_PB_RIGHT_IC_1_SHIFT 0

/* SPDIF_TX_PB_RIGHT_10 (IC 1) */
#define R501_SPDIF_TX_PB_RIGHT_10_SPDIF_TX_PB_RIGHT_IC_1 0x0000 /* 0000000000000000b	[15:0] */
#define R501_SPDIF_TX_PB_RIGHT_10_SPDIF_TX_PB_RIGHT_IC_1_MASK 0xFFFF
#define R501_SPDIF_TX_PB_RIGHT_10_SPDIF_TX_PB_RIGHT_IC_1_SHIFT 0

/* SPDIF_TX_PB_RIGHT_11 (IC 1) */
#define R502_SPDIF_TX_PB_RIGHT_11_SPDIF_TX_PB_RIGHT_IC_1 0x0000 /* 0000000000000000b	[15:0] */
#define R502_SPDIF_TX_PB_RIGHT_11_SPDIF_TX_PB_RIGHT_IC_1_MASK 0xFFFF
#define R502_SPDIF_TX_PB_RIGHT_11_SPDIF_TX_PB_RIGHT_IC_1_SHIFT 0

/* BCLK_IN0_PIN (IC 1) */
#define R503_BCLK_IN0_PIN_BCLK_IN_DRIVE_IC_1      0x0    /* 00b	[1:0] */
#define R503_BCLK_IN0_PIN_BCLK_IN_SLEW_IC_1       0x2    /* 10b	[3:2] */
#define R503_BCLK_IN0_PIN_BCLK_IN_PULL_IC_1       0x1    /* 1b	[4] */
#define R503_BCLK_IN0_PIN_BCLK_IN_DRIVE_IC_1_MASK 0x3
#define R503_BCLK_IN0_PIN_BCLK_IN_DRIVE_IC_1_SHIFT 0
#define R503_BCLK_IN0_PIN_BCLK_IN_SLEW_IC_1_MASK  0xC
#define R503_BCLK_IN0_PIN_BCLK_IN_SLEW_IC_1_SHIFT 2
#define R503_BCLK_IN0_PIN_BCLK_IN_PULL_IC_1_MASK  0x10
#define R503_BCLK_IN0_PIN_BCLK_IN_PULL_IC_1_SHIFT 4

/* BCLK_IN1_PIN (IC 1) */
#define R504_BCLK_IN1_PIN_BCLK_IN_DRIVE_IC_1      0x0    /* 00b	[1:0] */
#define R504_BCLK_IN1_PIN_BCLK_IN_SLEW_IC_1       0x2    /* 10b	[3:2] */
#define R504_BCLK_IN1_PIN_BCLK_IN_PULL_IC_1       0x1    /* 1b	[4] */
#define R504_BCLK_IN1_PIN_BCLK_IN_DRIVE_IC_1_MASK 0x3
#define R504_BCLK_IN1_PIN_BCLK_IN_DRIVE_IC_1_SHIFT 0
#define R504_BCLK_IN1_PIN_BCLK_IN_SLEW_IC_1_MASK  0xC
#define R504_BCLK_IN1_PIN_BCLK_IN_SLEW_IC_1_SHIFT 2
#define R504_BCLK_IN1_PIN_BCLK_IN_PULL_IC_1_MASK  0x10
#define R504_BCLK_IN1_PIN_BCLK_IN_PULL_IC_1_SHIFT 4

/* BCLK_IN2_PIN (IC 1) */
#define R505_BCLK_IN2_PIN_BCLK_IN_DRIVE_IC_1      0x0    /* 00b	[1:0] */
#define R505_BCLK_IN2_PIN_BCLK_IN_SLEW_IC_1       0x2    /* 10b	[3:2] */
#define R505_BCLK_IN2_PIN_BCLK_IN_PULL_IC_1       0x1    /* 1b	[4] */
#define R505_BCLK_IN2_PIN_BCLK_IN_DRIVE_IC_1_MASK 0x3
#define R505_BCLK_IN2_PIN_BCLK_IN_DRIVE_IC_1_SHIFT 0
#define R505_BCLK_IN2_PIN_BCLK_IN_SLEW_IC_1_MASK  0xC
#define R505_BCLK_IN2_PIN_BCLK_IN_SLEW_IC_1_SHIFT 2
#define R505_BCLK_IN2_PIN_BCLK_IN_PULL_IC_1_MASK  0x10
#define R505_BCLK_IN2_PIN_BCLK_IN_PULL_IC_1_SHIFT 4

/* BCLK_IN3_PIN (IC 1) */
#define R506_BCLK_IN3_PIN_BCLK_IN_DRIVE_IC_1      0x0    /* 00b	[1:0] */
#define R506_BCLK_IN3_PIN_BCLK_IN_SLEW_IC_1       0x2    /* 10b	[3:2] */
#define R506_BCLK_IN3_PIN_BCLK_IN_PULL_IC_1       0x1    /* 1b	[4] */
#define R506_BCLK_IN3_PIN_BCLK_IN_DRIVE_IC_1_MASK 0x3
#define R506_BCLK_IN3_PIN_BCLK_IN_DRIVE_IC_1_SHIFT 0
#define R506_BCLK_IN3_PIN_BCLK_IN_SLEW_IC_1_MASK  0xC
#define R506_BCLK_IN3_PIN_BCLK_IN_SLEW_IC_1_SHIFT 2
#define R506_BCLK_IN3_PIN_BCLK_IN_PULL_IC_1_MASK  0x10
#define R506_BCLK_IN3_PIN_BCLK_IN_PULL_IC_1_SHIFT 4

/* BCLK_OUT0_PIN (IC 1) */
#define R507_BCLK_OUT0_PIN_BCLK_OUT_DRIVE_IC_1    0x0    /* 00b	[1:0] */
#define R507_BCLK_OUT0_PIN_BCLK_OUT_SLEW_IC_1     0x2    /* 10b	[3:2] */
#define R507_BCLK_OUT0_PIN_BCLK_OUT_PULL_IC_1     0x1    /* 1b	[4] */
#define R507_BCLK_OUT0_PIN_BCLK_OUT_DRIVE_IC_1_MASK 0x3
#define R507_BCLK_OUT0_PIN_BCLK_OUT_DRIVE_IC_1_SHIFT 0
#define R507_BCLK_OUT0_PIN_BCLK_OUT_SLEW_IC_1_MASK 0xC
#define R507_BCLK_OUT0_PIN_BCLK_OUT_SLEW_IC_1_SHIFT 2
#define R507_BCLK_OUT0_PIN_BCLK_OUT_PULL_IC_1_MASK 0x10
#define R507_BCLK_OUT0_PIN_BCLK_OUT_PULL_IC_1_SHIFT 4

/* BCLK_OUT1_PIN (IC 1) */
#define R508_BCLK_OUT1_PIN_BCLK_OUT_DRIVE_IC_1    0x0    /* 00b	[1:0] */
#define R508_BCLK_OUT1_PIN_BCLK_OUT_SLEW_IC_1     0x2    /* 10b	[3:2] */
#define R508_BCLK_OUT1_PIN_BCLK_OUT_PULL_IC_1     0x1    /* 1b	[4] */
#define R508_BCLK_OUT1_PIN_BCLK_OUT_DRIVE_IC_1_MASK 0x3
#define R508_BCLK_OUT1_PIN_BCLK_OUT_DRIVE_IC_1_SHIFT 0
#define R508_BCLK_OUT1_PIN_BCLK_OUT_SLEW_IC_1_MASK 0xC
#define R508_BCLK_OUT1_PIN_BCLK_OUT_SLEW_IC_1_SHIFT 2
#define R508_BCLK_OUT1_PIN_BCLK_OUT_PULL_IC_1_MASK 0x10
#define R508_BCLK_OUT1_PIN_BCLK_OUT_PULL_IC_1_SHIFT 4

/* BCLK_OUT2_PIN (IC 1) */
#define R509_BCLK_OUT2_PIN_BCLK_OUT_DRIVE_IC_1    0x0    /* 00b	[1:0] */
#define R509_BCLK_OUT2_PIN_BCLK_OUT_SLEW_IC_1     0x2    /* 10b	[3:2] */
#define R509_BCLK_OUT2_PIN_BCLK_OUT_PULL_IC_1     0x1    /* 1b	[4] */
#define R509_BCLK_OUT2_PIN_BCLK_OUT_DRIVE_IC_1_MASK 0x3
#define R509_BCLK_OUT2_PIN_BCLK_OUT_DRIVE_IC_1_SHIFT 0
#define R509_BCLK_OUT2_PIN_BCLK_OUT_SLEW_IC_1_MASK 0xC
#define R509_BCLK_OUT2_PIN_BCLK_OUT_SLEW_IC_1_SHIFT 2
#define R509_BCLK_OUT2_PIN_BCLK_OUT_PULL_IC_1_MASK 0x10
#define R509_BCLK_OUT2_PIN_BCLK_OUT_PULL_IC_1_SHIFT 4

/* BCLK_OUT3_PIN (IC 1) */
#define R510_BCLK_OUT3_PIN_BCLK_OUT_DRIVE_IC_1    0x0    /* 00b	[1:0] */
#define R510_BCLK_OUT3_PIN_BCLK_OUT_SLEW_IC_1     0x2    /* 10b	[3:2] */
#define R510_BCLK_OUT3_PIN_BCLK_OUT_PULL_IC_1     0x1    /* 1b	[4] */
#define R510_BCLK_OUT3_PIN_BCLK_OUT_DRIVE_IC_1_MASK 0x3
#define R510_BCLK_OUT3_PIN_BCLK_OUT_DRIVE_IC_1_SHIFT 0
#define R510_BCLK_OUT3_PIN_BCLK_OUT_SLEW_IC_1_MASK 0xC
#define R510_BCLK_OUT3_PIN_BCLK_OUT_SLEW_IC_1_SHIFT 2
#define R510_BCLK_OUT3_PIN_BCLK_OUT_PULL_IC_1_MASK 0x10
#define R510_BCLK_OUT3_PIN_BCLK_OUT_PULL_IC_1_SHIFT 4

/* LRCLK_IN0_PIN (IC 1) */
#define R511_LRCLK_IN0_PIN_LRCLK_IN_DRIVE_IC_1    0x0    /* 00b	[1:0] */
#define R511_LRCLK_IN0_PIN_LRCLK_IN_SLEW_IC_1     0x2    /* 10b	[3:2] */
#define R511_LRCLK_IN0_PIN_LRCLK_IN_PULL_IC_1     0x1    /* 1b	[4] */
#define R511_LRCLK_IN0_PIN_LRCLK_IN_DRIVE_IC_1_MASK 0x3
#define R511_LRCLK_IN0_PIN_LRCLK_IN_DRIVE_IC_1_SHIFT 0
#define R511_LRCLK_IN0_PIN_LRCLK_IN_SLEW_IC_1_MASK 0xC
#define R511_LRCLK_IN0_PIN_LRCLK_IN_SLEW_IC_1_SHIFT 2
#define R511_LRCLK_IN0_PIN_LRCLK_IN_PULL_IC_1_MASK 0x10
#define R511_LRCLK_IN0_PIN_LRCLK_IN_PULL_IC_1_SHIFT 4

/* LRCLK_IN1_PIN (IC 1) */
#define R512_LRCLK_IN1_PIN_LRCLK_IN_DRIVE_IC_1    0x0    /* 00b	[1:0] */
#define R512_LRCLK_IN1_PIN_LRCLK_IN_SLEW_IC_1     0x2    /* 10b	[3:2] */
#define R512_LRCLK_IN1_PIN_LRCLK_IN_PULL_IC_1     0x1    /* 1b	[4] */
#define R512_LRCLK_IN1_PIN_LRCLK_IN_DRIVE_IC_1_MASK 0x3
#define R512_LRCLK_IN1_PIN_LRCLK_IN_DRIVE_IC_1_SHIFT 0
#define R512_LRCLK_IN1_PIN_LRCLK_IN_SLEW_IC_1_MASK 0xC
#define R512_LRCLK_IN1_PIN_LRCLK_IN_SLEW_IC_1_SHIFT 2
#define R512_LRCLK_IN1_PIN_LRCLK_IN_PULL_IC_1_MASK 0x10
#define R512_LRCLK_IN1_PIN_LRCLK_IN_PULL_IC_1_SHIFT 4

/* LRCLK_IN2_PIN (IC 1) */
#define R513_LRCLK_IN2_PIN_LRCLK_IN_DRIVE_IC_1    0x0    /* 00b	[1:0] */
#define R513_LRCLK_IN2_PIN_LRCLK_IN_SLEW_IC_1     0x2    /* 10b	[3:2] */
#define R513_LRCLK_IN2_PIN_LRCLK_IN_PULL_IC_1     0x1    /* 1b	[4] */
#define R513_LRCLK_IN2_PIN_LRCLK_IN_DRIVE_IC_1_MASK 0x3
#define R513_LRCLK_IN2_PIN_LRCLK_IN_DRIVE_IC_1_SHIFT 0
#define R513_LRCLK_IN2_PIN_LRCLK_IN_SLEW_IC_1_MASK 0xC
#define R513_LRCLK_IN2_PIN_LRCLK_IN_SLEW_IC_1_SHIFT 2
#define R513_LRCLK_IN2_PIN_LRCLK_IN_PULL_IC_1_MASK 0x10
#define R513_LRCLK_IN2_PIN_LRCLK_IN_PULL_IC_1_SHIFT 4

/* LRCLK_IN3_PIN (IC 1) */
#define R514_LRCLK_IN3_PIN_LRCLK_IN_DRIVE_IC_1    0x0    /* 00b	[1:0] */
#define R514_LRCLK_IN3_PIN_LRCLK_IN_SLEW_IC_1     0x2    /* 10b	[3:2] */
#define R514_LRCLK_IN3_PIN_LRCLK_IN_PULL_IC_1     0x1    /* 1b	[4] */
#define R514_LRCLK_IN3_PIN_LRCLK_IN_DRIVE_IC_1_MASK 0x3
#define R514_LRCLK_IN3_PIN_LRCLK_IN_DRIVE_IC_1_SHIFT 0
#define R514_LRCLK_IN3_PIN_LRCLK_IN_SLEW_IC_1_MASK 0xC
#define R514_LRCLK_IN3_PIN_LRCLK_IN_SLEW_IC_1_SHIFT 2
#define R514_LRCLK_IN3_PIN_LRCLK_IN_PULL_IC_1_MASK 0x10
#define R514_LRCLK_IN3_PIN_LRCLK_IN_PULL_IC_1_SHIFT 4

/* LRCLK_OUT0_PIN (IC 1) */
#define R515_LRCLK_OUT0_PIN_LRCLK_OUT_DRIVE_IC_1  0x0    /* 00b	[1:0] */
#define R515_LRCLK_OUT0_PIN_LRCLK_OUT_SLEW_IC_1   0x2    /* 10b	[3:2] */
#define R515_LRCLK_OUT0_PIN_LRCLK_OUT_PULL_IC_1   0x1    /* 1b	[4] */
#define R515_LRCLK_OUT0_PIN_LRCLK_OUT_DRIVE_IC_1_MASK 0x3
#define R515_LRCLK_OUT0_PIN_LRCLK_OUT_DRIVE_IC_1_SHIFT 0
#define R515_LRCLK_OUT0_PIN_LRCLK_OUT_SLEW_IC_1_MASK 0xC
#define R515_LRCLK_OUT0_PIN_LRCLK_OUT_SLEW_IC_1_SHIFT 2
#define R515_LRCLK_OUT0_PIN_LRCLK_OUT_PULL_IC_1_MASK 0x10
#define R515_LRCLK_OUT0_PIN_LRCLK_OUT_PULL_IC_1_SHIFT 4

/* LRCLK_OUT1_PIN (IC 1) */
#define R516_LRCLK_OUT1_PIN_LRCLK_OUT_DRIVE_IC_1  0x0    /* 00b	[1:0] */
#define R516_LRCLK_OUT1_PIN_LRCLK_OUT_SLEW_IC_1   0x2    /* 10b	[3:2] */
#define R516_LRCLK_OUT1_PIN_LRCLK_OUT_PULL_IC_1   0x1    /* 1b	[4] */
#define R516_LRCLK_OUT1_PIN_LRCLK_OUT_DRIVE_IC_1_MASK 0x3
#define R516_LRCLK_OUT1_PIN_LRCLK_OUT_DRIVE_IC_1_SHIFT 0
#define R516_LRCLK_OUT1_PIN_LRCLK_OUT_SLEW_IC_1_MASK 0xC
#define R516_LRCLK_OUT1_PIN_LRCLK_OUT_SLEW_IC_1_SHIFT 2
#define R516_LRCLK_OUT1_PIN_LRCLK_OUT_PULL_IC_1_MASK 0x10
#define R516_LRCLK_OUT1_PIN_LRCLK_OUT_PULL_IC_1_SHIFT 4

/* LRCLK_OUT2_PIN (IC 1) */
#define R517_LRCLK_OUT2_PIN_LRCLK_OUT_DRIVE_IC_1  0x0    /* 00b	[1:0] */
#define R517_LRCLK_OUT2_PIN_LRCLK_OUT_SLEW_IC_1   0x2    /* 10b	[3:2] */
#define R517_LRCLK_OUT2_PIN_LRCLK_OUT_PULL_IC_1   0x1    /* 1b	[4] */
#define R517_LRCLK_OUT2_PIN_LRCLK_OUT_DRIVE_IC_1_MASK 0x3
#define R517_LRCLK_OUT2_PIN_LRCLK_OUT_DRIVE_IC_1_SHIFT 0
#define R517_LRCLK_OUT2_PIN_LRCLK_OUT_SLEW_IC_1_MASK 0xC
#define R517_LRCLK_OUT2_PIN_LRCLK_OUT_SLEW_IC_1_SHIFT 2
#define R517_LRCLK_OUT2_PIN_LRCLK_OUT_PULL_IC_1_MASK 0x10
#define R517_LRCLK_OUT2_PIN_LRCLK_OUT_PULL_IC_1_SHIFT 4

/* LRCLK_OUT3_PIN (IC 1) */
#define R518_LRCLK_OUT3_PIN_LRCLK_OUT_DRIVE_IC_1  0x0    /* 00b	[1:0] */
#define R518_LRCLK_OUT3_PIN_LRCLK_OUT_SLEW_IC_1   0x2    /* 10b	[3:2] */
#define R518_LRCLK_OUT3_PIN_LRCLK_OUT_PULL_IC_1   0x1    /* 1b	[4] */
#define R518_LRCLK_OUT3_PIN_LRCLK_OUT_DRIVE_IC_1_MASK 0x3
#define R518_LRCLK_OUT3_PIN_LRCLK_OUT_DRIVE_IC_1_SHIFT 0
#define R518_LRCLK_OUT3_PIN_LRCLK_OUT_SLEW_IC_1_MASK 0xC
#define R518_LRCLK_OUT3_PIN_LRCLK_OUT_SLEW_IC_1_SHIFT 2
#define R518_LRCLK_OUT3_PIN_LRCLK_OUT_PULL_IC_1_MASK 0x10
#define R518_LRCLK_OUT3_PIN_LRCLK_OUT_PULL_IC_1_SHIFT 4

/* SDATA_IN0_PIN (IC 1) */
#define R519_SDATA_IN0_PIN_SDATA_IN_DRIVE_IC_1    0x0    /* 00b	[1:0] */
#define R519_SDATA_IN0_PIN_SDATA_IN_SLEW_IC_1     0x2    /* 10b	[3:2] */
#define R519_SDATA_IN0_PIN_SDATA_IN_PULL_IC_1     0x1    /* 1b	[4] */
#define R519_SDATA_IN0_PIN_SDATA_IN_DRIVE_IC_1_MASK 0x3
#define R519_SDATA_IN0_PIN_SDATA_IN_DRIVE_IC_1_SHIFT 0
#define R519_SDATA_IN0_PIN_SDATA_IN_SLEW_IC_1_MASK 0xC
#define R519_SDATA_IN0_PIN_SDATA_IN_SLEW_IC_1_SHIFT 2
#define R519_SDATA_IN0_PIN_SDATA_IN_PULL_IC_1_MASK 0x10
#define R519_SDATA_IN0_PIN_SDATA_IN_PULL_IC_1_SHIFT 4

/* SDATA_IN1_PIN (IC 1) */
#define R520_SDATA_IN1_PIN_SDATA_IN_DRIVE_IC_1    0x0    /* 00b	[1:0] */
#define R520_SDATA_IN1_PIN_SDATA_IN_SLEW_IC_1     0x2    /* 10b	[3:2] */
#define R520_SDATA_IN1_PIN_SDATA_IN_PULL_IC_1     0x1    /* 1b	[4] */
#define R520_SDATA_IN1_PIN_SDATA_IN_DRIVE_IC_1_MASK 0x3
#define R520_SDATA_IN1_PIN_SDATA_IN_DRIVE_IC_1_SHIFT 0
#define R520_SDATA_IN1_PIN_SDATA_IN_SLEW_IC_1_MASK 0xC
#define R520_SDATA_IN1_PIN_SDATA_IN_SLEW_IC_1_SHIFT 2
#define R520_SDATA_IN1_PIN_SDATA_IN_PULL_IC_1_MASK 0x10
#define R520_SDATA_IN1_PIN_SDATA_IN_PULL_IC_1_SHIFT 4

/* SDATA_IN2_PIN (IC 1) */
#define R521_SDATA_IN2_PIN_SDATA_IN_DRIVE_IC_1    0x0    /* 00b	[1:0] */
#define R521_SDATA_IN2_PIN_SDATA_IN_SLEW_IC_1     0x2    /* 10b	[3:2] */
#define R521_SDATA_IN2_PIN_SDATA_IN_PULL_IC_1     0x1    /* 1b	[4] */
#define R521_SDATA_IN2_PIN_SDATA_IN_DRIVE_IC_1_MASK 0x3
#define R521_SDATA_IN2_PIN_SDATA_IN_DRIVE_IC_1_SHIFT 0
#define R521_SDATA_IN2_PIN_SDATA_IN_SLEW_IC_1_MASK 0xC
#define R521_SDATA_IN2_PIN_SDATA_IN_SLEW_IC_1_SHIFT 2
#define R521_SDATA_IN2_PIN_SDATA_IN_PULL_IC_1_MASK 0x10
#define R521_SDATA_IN2_PIN_SDATA_IN_PULL_IC_1_SHIFT 4

/* SDATA_IN3_PIN (IC 1) */
#define R522_SDATA_IN3_PIN_SDATA_IN_DRIVE_IC_1    0x0    /* 00b	[1:0] */
#define R522_SDATA_IN3_PIN_SDATA_IN_SLEW_IC_1     0x2    /* 10b	[3:2] */
#define R522_SDATA_IN3_PIN_SDATA_IN_PULL_IC_1     0x1    /* 1b	[4] */
#define R522_SDATA_IN3_PIN_SDATA_IN_DRIVE_IC_1_MASK 0x3
#define R522_SDATA_IN3_PIN_SDATA_IN_DRIVE_IC_1_SHIFT 0
#define R522_SDATA_IN3_PIN_SDATA_IN_SLEW_IC_1_MASK 0xC
#define R522_SDATA_IN3_PIN_SDATA_IN_SLEW_IC_1_SHIFT 2
#define R522_SDATA_IN3_PIN_SDATA_IN_PULL_IC_1_MASK 0x10
#define R522_SDATA_IN3_PIN_SDATA_IN_PULL_IC_1_SHIFT 4

/* SDATA_OUT0_PIN (IC 1) */
#define R523_SDATA_OUT0_PIN_SDATA_OUT_DRIVE_IC_1  0x0    /* 00b	[1:0] */
#define R523_SDATA_OUT0_PIN_SDATA_OUT_SLEW_IC_1   0x2    /* 10b	[3:2] */
#define R523_SDATA_OUT0_PIN_SDATA_OUT_PULL_IC_1   0x0    /* 0b	[4] */
#define R523_SDATA_OUT0_PIN_SDATA_OUT_DRIVE_IC_1_MASK 0x3
#define R523_SDATA_OUT0_PIN_SDATA_OUT_DRIVE_IC_1_SHIFT 0
#define R523_SDATA_OUT0_PIN_SDATA_OUT_SLEW_IC_1_MASK 0xC
#define R523_SDATA_OUT0_PIN_SDATA_OUT_SLEW_IC_1_SHIFT 2
#define R523_SDATA_OUT0_PIN_SDATA_OUT_PULL_IC_1_MASK 0x10
#define R523_SDATA_OUT0_PIN_SDATA_OUT_PULL_IC_1_SHIFT 4

/* SDATA_OUT1_PIN (IC 1) */
#define R524_SDATA_OUT1_PIN_SDATA_OUT_DRIVE_IC_1  0x0    /* 00b	[1:0] */
#define R524_SDATA_OUT1_PIN_SDATA_OUT_SLEW_IC_1   0x2    /* 10b	[3:2] */
#define R524_SDATA_OUT1_PIN_SDATA_OUT_PULL_IC_1   0x0    /* 0b	[4] */
#define R524_SDATA_OUT1_PIN_SDATA_OUT_DRIVE_IC_1_MASK 0x3
#define R524_SDATA_OUT1_PIN_SDATA_OUT_DRIVE_IC_1_SHIFT 0
#define R524_SDATA_OUT1_PIN_SDATA_OUT_SLEW_IC_1_MASK 0xC
#define R524_SDATA_OUT1_PIN_SDATA_OUT_SLEW_IC_1_SHIFT 2
#define R524_SDATA_OUT1_PIN_SDATA_OUT_PULL_IC_1_MASK 0x10
#define R524_SDATA_OUT1_PIN_SDATA_OUT_PULL_IC_1_SHIFT 4

/* SDATA_OUT2_PIN (IC 1) */
#define R525_SDATA_OUT2_PIN_SDATA_OUT_DRIVE_IC_1  0x0    /* 00b	[1:0] */
#define R525_SDATA_OUT2_PIN_SDATA_OUT_SLEW_IC_1   0x2    /* 10b	[3:2] */
#define R525_SDATA_OUT2_PIN_SDATA_OUT_PULL_IC_1   0x0    /* 0b	[4] */
#define R525_SDATA_OUT2_PIN_SDATA_OUT_DRIVE_IC_1_MASK 0x3
#define R525_SDATA_OUT2_PIN_SDATA_OUT_DRIVE_IC_1_SHIFT 0
#define R525_SDATA_OUT2_PIN_SDATA_OUT_SLEW_IC_1_MASK 0xC
#define R525_SDATA_OUT2_PIN_SDATA_OUT_SLEW_IC_1_SHIFT 2
#define R525_SDATA_OUT2_PIN_SDATA_OUT_PULL_IC_1_MASK 0x10
#define R525_SDATA_OUT2_PIN_SDATA_OUT_PULL_IC_1_SHIFT 4

/* SDATA_OUT3_PIN (IC 1) */
#define R526_SDATA_OUT3_PIN_SDATA_OUT_DRIVE_IC_1  0x0    /* 00b	[1:0] */
#define R526_SDATA_OUT3_PIN_SDATA_OUT_SLEW_IC_1   0x2    /* 10b	[3:2] */
#define R526_SDATA_OUT3_PIN_SDATA_OUT_PULL_IC_1   0x0    /* 0b	[4] */
#define R526_SDATA_OUT3_PIN_SDATA_OUT_DRIVE_IC_1_MASK 0x3
#define R526_SDATA_OUT3_PIN_SDATA_OUT_DRIVE_IC_1_SHIFT 0
#define R526_SDATA_OUT3_PIN_SDATA_OUT_SLEW_IC_1_MASK 0xC
#define R526_SDATA_OUT3_PIN_SDATA_OUT_SLEW_IC_1_SHIFT 2
#define R526_SDATA_OUT3_PIN_SDATA_OUT_PULL_IC_1_MASK 0x10
#define R526_SDATA_OUT3_PIN_SDATA_OUT_PULL_IC_1_SHIFT 4

/* SPDIF_TX_PIN (IC 1) */
#define R527_SPDIF_TX_PIN_SPDIF_TX_DRIVE_IC_1     0x0    /* 00b	[1:0] */
#define R527_SPDIF_TX_PIN_SPDIF_TX_SLEW_IC_1      0x2    /* 10b	[3:2] */
#define R527_SPDIF_TX_PIN_SPDIF_TX_PULL_IC_1      0x0    /* 0b	[4] */
#define R527_SPDIF_TX_PIN_SPDIF_TX_DRIVE_IC_1_MASK 0x3
#define R527_SPDIF_TX_PIN_SPDIF_TX_DRIVE_IC_1_SHIFT 0
#define R527_SPDIF_TX_PIN_SPDIF_TX_SLEW_IC_1_MASK 0xC
#define R527_SPDIF_TX_PIN_SPDIF_TX_SLEW_IC_1_SHIFT 2
#define R527_SPDIF_TX_PIN_SPDIF_TX_PULL_IC_1_MASK 0x10
#define R527_SPDIF_TX_PIN_SPDIF_TX_PULL_IC_1_SHIFT 4

/* SCLK_SCL_PIN (IC 1) */
#define R528_SCLK_SCL_PIN_SCLK_SCL_DRIVE_IC_1     0x0    /* 00b	[1:0] */
#define R528_SCLK_SCL_PIN_SCLK_SCL_SLEW_IC_1      0x2    /* 10b	[3:2] */
#define R528_SCLK_SCL_PIN_SCLK_SCL_PULL_IC_1      0x0    /* 0b	[4] */
#define R528_SCLK_SCL_PIN_SCLK_SCL_DRIVE_IC_1_MASK 0x3
#define R528_SCLK_SCL_PIN_SCLK_SCL_DRIVE_IC_1_SHIFT 0
#define R528_SCLK_SCL_PIN_SCLK_SCL_SLEW_IC_1_MASK 0xC
#define R528_SCLK_SCL_PIN_SCLK_SCL_SLEW_IC_1_SHIFT 2
#define R528_SCLK_SCL_PIN_SCLK_SCL_PULL_IC_1_MASK 0x10
#define R528_SCLK_SCL_PIN_SCLK_SCL_PULL_IC_1_SHIFT 4

/* MISO_SDA_PIN (IC 1) */
#define R529_MISO_SDA_PIN_MISO_SDA_DRIVE_IC_1     0x0    /* 00b	[1:0] */
#define R529_MISO_SDA_PIN_MISO_SDA_SLEW_IC_1      0x2    /* 10b	[3:2] */
#define R529_MISO_SDA_PIN_MISO_SDA_PULL_IC_1      0x0    /* 0b	[4] */
#define R529_MISO_SDA_PIN_MISO_SDA_DRIVE_IC_1_MASK 0x3
#define R529_MISO_SDA_PIN_MISO_SDA_DRIVE_IC_1_SHIFT 0
#define R529_MISO_SDA_PIN_MISO_SDA_SLEW_IC_1_MASK 0xC
#define R529_MISO_SDA_PIN_MISO_SDA_SLEW_IC_1_SHIFT 2
#define R529_MISO_SDA_PIN_MISO_SDA_PULL_IC_1_MASK 0x10
#define R529_MISO_SDA_PIN_MISO_SDA_PULL_IC_1_SHIFT 4

/* SS_PIN (IC 1) */
#define R530_SS_PIN_SS_DRIVE_IC_1                 0x0    /* 00b	[1:0] */
#define R530_SS_PIN_SS_SLEW_IC_1                  0x2    /* 10b	[3:2] */
#define R530_SS_PIN_SS_PULL_IC_1                  0x1    /* 1b	[4] */
#define R530_SS_PIN_SS_DRIVE_IC_1_MASK            0x3
#define R530_SS_PIN_SS_DRIVE_IC_1_SHIFT           0
#define R530_SS_PIN_SS_SLEW_IC_1_MASK             0xC
#define R530_SS_PIN_SS_SLEW_IC_1_SHIFT            2
#define R530_SS_PIN_SS_PULL_IC_1_MASK             0x10
#define R530_SS_PIN_SS_PULL_IC_1_SHIFT            4

/* MOSI_ADDR1_PIN (IC 1) */
#define R531_MOSI_ADDR1_PIN_MOSI_ADDR1_DRIVE_IC_1 0x0    /* 00b	[1:0] */
#define R531_MOSI_ADDR1_PIN_MOSI_ADDR1_SLEW_IC_1  0x2    /* 10b	[3:2] */
#define R531_MOSI_ADDR1_PIN_MOSI_ADDR1_PULL_IC_1  0x1    /* 1b	[4] */
#define R531_MOSI_ADDR1_PIN_MOSI_ADDR1_DRIVE_IC_1_MASK 0x3
#define R531_MOSI_ADDR1_PIN_MOSI_ADDR1_DRIVE_IC_1_SHIFT 0
#define R531_MOSI_ADDR1_PIN_MOSI_ADDR1_SLEW_IC_1_MASK 0xC
#define R531_MOSI_ADDR1_PIN_MOSI_ADDR1_SLEW_IC_1_SHIFT 2
#define R531_MOSI_ADDR1_PIN_MOSI_ADDR1_PULL_IC_1_MASK 0x10
#define R531_MOSI_ADDR1_PIN_MOSI_ADDR1_PULL_IC_1_SHIFT 4

/* SCLK_SCL_M_PIN (IC 1) */
#define R532_SCLK_SCL_M_PIN_SCLK_SCL_M_DRIVE_IC_1 0x3    /* 11b	[1:0] */
#define R532_SCLK_SCL_M_PIN_SCLK_SCL_M_SLEW_IC_1  0x3    /* 11b	[3:2] */
#define R532_SCLK_SCL_M_PIN_SCLK_SCL_M_PULL_IC_1  0x0    /* 0b	[4] */
#define R532_SCLK_SCL_M_PIN_SCLK_SCL_M_DRIVE_IC_1_MASK 0x3
#define R532_SCLK_SCL_M_PIN_SCLK_SCL_M_DRIVE_IC_1_SHIFT 0
#define R532_SCLK_SCL_M_PIN_SCLK_SCL_M_SLEW_IC_1_MASK 0xC
#define R532_SCLK_SCL_M_PIN_SCLK_SCL_M_SLEW_IC_1_SHIFT 2
#define R532_SCLK_SCL_M_PIN_SCLK_SCL_M_PULL_IC_1_MASK 0x10
#define R532_SCLK_SCL_M_PIN_SCLK_SCL_M_PULL_IC_1_SHIFT 4

/* MISO_SDA_M_PIN (IC 1) */
#define R533_MISO_SDA_M_PIN_MISO_SDA_M_DRIVE_IC_1 0x3    /* 11b	[1:0] */
#define R533_MISO_SDA_M_PIN_MISO_SDA_M_SLEW_IC_1  0x3    /* 11b	[3:2] */
#define R533_MISO_SDA_M_PIN_MISO_SDA_M_PULL_IC_1  0x0    /* 0b	[4] */
#define R533_MISO_SDA_M_PIN_MISO_SDA_M_DRIVE_IC_1_MASK 0x3
#define R533_MISO_SDA_M_PIN_MISO_SDA_M_DRIVE_IC_1_SHIFT 0
#define R533_MISO_SDA_M_PIN_MISO_SDA_M_SLEW_IC_1_MASK 0xC
#define R533_MISO_SDA_M_PIN_MISO_SDA_M_SLEW_IC_1_SHIFT 2
#define R533_MISO_SDA_M_PIN_MISO_SDA_M_PULL_IC_1_MASK 0x10
#define R533_MISO_SDA_M_PIN_MISO_SDA_M_PULL_IC_1_SHIFT 4

/* SS_M_PIN (IC 1) */
#define R534_SS_M_PIN_SS_M_DRIVE_IC_1             0x3    /* 11b	[1:0] */
#define R534_SS_M_PIN_SS_M_SLEW_IC_1              0x3    /* 11b	[3:2] */
#define R534_SS_M_PIN_SS_M_PULL_IC_1              0x0    /* 0b	[4] */
#define R534_SS_M_PIN_SS_M_DRIVE_IC_1_MASK        0x3
#define R534_SS_M_PIN_SS_M_DRIVE_IC_1_SHIFT       0
#define R534_SS_M_PIN_SS_M_SLEW_IC_1_MASK         0xC
#define R534_SS_M_PIN_SS_M_SLEW_IC_1_SHIFT        2
#define R534_SS_M_PIN_SS_M_PULL_IC_1_MASK         0x10
#define R534_SS_M_PIN_SS_M_PULL_IC_1_SHIFT        4

/* MOSI_M_PIN (IC 1) */
#define R535_MOSI_M_PIN_MOSI_M_DRIVE_IC_1         0x3    /* 11b	[1:0] */
#define R535_MOSI_M_PIN_MOSI_M_SLEW_IC_1          0x3    /* 11b	[3:2] */
#define R535_MOSI_M_PIN_MOSI_M_PULL_IC_1          0x0    /* 0b	[4] */
#define R535_MOSI_M_PIN_MOSI_M_DRIVE_IC_1_MASK    0x3
#define R535_MOSI_M_PIN_MOSI_M_DRIVE_IC_1_SHIFT   0
#define R535_MOSI_M_PIN_MOSI_M_SLEW_IC_1_MASK     0xC
#define R535_MOSI_M_PIN_MOSI_M_SLEW_IC_1_SHIFT    2
#define R535_MOSI_M_PIN_MOSI_M_PULL_IC_1_MASK     0x10
#define R535_MOSI_M_PIN_MOSI_M_PULL_IC_1_SHIFT    4

/* MP6_PIN (IC 1) */
#define R536_MP6_PIN_MP6_DRIVE_IC_1               0x0    /* 00b	[1:0] */
#define R536_MP6_PIN_MP6_SLEW_IC_1                0x2    /* 10b	[3:2] */
#define R536_MP6_PIN_MP6_PULL_IC_1                0x1    /* 1b	[4] */
#define R536_MP6_PIN_MP6_DRIVE_IC_1_MASK          0x3
#define R536_MP6_PIN_MP6_DRIVE_IC_1_SHIFT         0
#define R536_MP6_PIN_MP6_SLEW_IC_1_MASK           0xC
#define R536_MP6_PIN_MP6_SLEW_IC_1_SHIFT          2
#define R536_MP6_PIN_MP6_PULL_IC_1_MASK           0x10
#define R536_MP6_PIN_MP6_PULL_IC_1_SHIFT          4

/* MP7_PIN (IC 1) */
#define R537_MP7_PIN_MP7_DRIVE_IC_1               0x0    /* 00b	[1:0] */
#define R537_MP7_PIN_MP7_SLEW_IC_1                0x2    /* 10b	[3:2] */
#define R537_MP7_PIN_MP7_PULL_IC_1                0x1    /* 1b	[4] */
#define R537_MP7_PIN_MP7_DRIVE_IC_1_MASK          0x3
#define R537_MP7_PIN_MP7_DRIVE_IC_1_SHIFT         0
#define R537_MP7_PIN_MP7_SLEW_IC_1_MASK           0xC
#define R537_MP7_PIN_MP7_SLEW_IC_1_SHIFT          2
#define R537_MP7_PIN_MP7_PULL_IC_1_MASK           0x10
#define R537_MP7_PIN_MP7_PULL_IC_1_SHIFT          4

/* CLKOUT_PIN (IC 1) */
#define R538_CLKOUT_PIN_CLKOUT_DRIVE_IC_1         0x0    /* 00b	[1:0] */
#define R538_CLKOUT_PIN_CLKOUT_SLEW_IC_1          0x2    /* 10b	[3:2] */
#define R538_CLKOUT_PIN_CLKOUT_PULL_IC_1          0x0    /* 0b	[4] */
#define R538_CLKOUT_PIN_CLKOUT_DRIVE_IC_1_MASK    0x3
#define R538_CLKOUT_PIN_CLKOUT_DRIVE_IC_1_SHIFT   0
#define R538_CLKOUT_PIN_CLKOUT_SLEW_IC_1_MASK     0xC
#define R538_CLKOUT_PIN_CLKOUT_SLEW_IC_1_SHIFT    2
#define R538_CLKOUT_PIN_CLKOUT_PULL_IC_1_MASK     0x10
#define R538_CLKOUT_PIN_CLKOUT_PULL_IC_1_SHIFT    4

/* SOFT_RESET (IC 1) */
#define R539_SOFTWARE_RESET_IC_1                  0x1    /* 1b	[0] */
#define R539_SOFTWARE_RESET_IC_1_MASK             0x1
#define R539_SOFTWARE_RESET_IC_1_SHIFT            0

#endif
