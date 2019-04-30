/*
 * File:           E:\Documents\freeDSP\freeDSP-aurora\SOURCES\SIGMASTUDIO\testproject2\testproject2_IC_1_PARAM.h
 *
 * Created:        Saturday, April 27, 2019 8:13:47 PM
 * Description:    testproject2:IC 1 parameter RAM definitions.
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
 * Copyright ©2019 Analog Devices, Inc. All rights reserved.
 */
#ifndef __TESTPROJECT2_IC_1_PARAM_H__
#define __TESTPROJECT2_IC_1_PARAM_H__


/* Module SafeLoadModule - SafeLoadModule*/
#define MOD_SAFELOADMODULE_COUNT                       7
#define MOD_SAFELOADMODULE_DEVICE                      "IC1"
#define MOD_SAFELOADMODULE_DATA_SAFELOAD0_ADDR         20
#define MOD_SAFELOADMODULE_DATA_SAFELOAD1_ADDR         21
#define MOD_SAFELOADMODULE_DATA_SAFELOAD2_ADDR         22
#define MOD_SAFELOADMODULE_DATA_SAFELOAD3_ADDR         23
#define MOD_SAFELOADMODULE_DATA_SAFELOAD4_ADDR         24
#define MOD_SAFELOADMODULE_ADDRESS_SAFELOAD_ADDR       25
#define MOD_SAFELOADMODULE_NUM_SAFELOAD_ADDR           26

/* Module Tone1 - Sine Tone with Phase and Gain*/
#define MOD_TONE1_COUNT                                4
#define MOD_TONE1_DEVICE                               "IC1"
#define MOD_TONE1_ALG0_SINEPHASEGAINALGS3001GAIN00_ADDR 27
#define MOD_TONE1_ALG0_SINEPHASEGAINALGS3001GAIN00_VALUE SIGMASTUDIOTYPE_8_24_CONVERT(1)
#define MOD_TONE1_ALG0_SINEPHASEGAINALGS3001GAIN00_TYPE SIGMASTUDIOTYPE_8_24
#define MOD_TONE1_ALG0_SINEPHASEGAINALGS3001INDEXFPHI00_ADDR 28
#define MOD_TONE1_ALG0_SINEPHASEGAINALGS3001INDEXFPHI00_FIXPT 0x00000000
#define MOD_TONE1_ALG0_SINEPHASEGAINALGS3001INDEXFPHI00_VALUE SIGMASTUDIOTYPE_INTEGER_CONVERT(0)
#define MOD_TONE1_ALG0_SINEPHASEGAINALGS3001INDEXFPHI00_TYPE SIGMASTUDIOTYPE_INTEGER
#define MOD_TONE1_ALG0_SINEPHASEGAINALGS3001INDEXFPHI01_ADDR 29
#define MOD_TONE1_ALG0_SINEPHASEGAINALGS3001INDEXFPHI01_FIXPT 0x00000000
#define MOD_TONE1_ALG0_SINEPHASEGAINALGS3001INDEXFPHI01_VALUE SIGMASTUDIOTYPE_INTEGER_CONVERT(0)
#define MOD_TONE1_ALG0_SINEPHASEGAINALGS3001INDEXFPHI01_TYPE SIGMASTUDIOTYPE_INTEGER
#define MOD_TONE1_ALG0_INCREMENT_ADDR                  32
#define MOD_TONE1_ALG0_INCREMENT_VALUE                 SIGMASTUDIOTYPE_8_24_CONVERT(0.0416670833333333)
#define MOD_TONE1_ALG0_INCREMENT_TYPE                  SIGMASTUDIOTYPE_8_24

#endif
