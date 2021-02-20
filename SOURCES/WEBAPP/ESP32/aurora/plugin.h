#ifndef SETTINGS_H_
#define SETTINGS_H_

#include <Arduino.h>
#include "config.h"

/**
 * This file contains the shared variables
 */

struct tSettings
{
  String ssid;
  String password;
  int addonid;
  bool vpot;
  String pwdap;
  String apname;
  int adcsum;
  bool wifiOn;
};

typedef uint8_t tFilterType;

enum tMuxAddr
{
  ADDR_ANALOG,
  ADDR_UAC,
  ADDR_EXP,
  ADDR_ESP,
  ADDR_SPDIF,
  ADDR_OUT
};

struct tInput
{
  uint16_t addrChn[5];
  uint16_t addrPort;
  uint32_t sel;
};

struct tHPLP
{
  uint16_t addr[4];
  float fc;
  tFilterType typ;
  bool bypass;
};

struct tShelving
{
  uint16_t addr;
  float gain;
  float fc;
  float slope;
  bool bypass;
};

struct tPeq
{
  uint16_t addr;
  float gain;
  float fc;
  float Q;
  bool bypass;
};

struct tPhase
{
  uint16_t addr;
  float fc;
  float Q;
  bool inv;
  bool bypass;
};

struct tDelay
{
  uint16_t addr;
  float delay;
  bool bypass;
};

struct tGain
{
  uint16_t addr;
  float gain;
  bool mute;
};

struct tCrossover
{
  uint16_t hp_addr[4];
  float hp_fc;
  tFilterType hp_typ;
  bool hp_bypass;

  uint16_t lp_addr[4];
  float lp_fc;
  tFilterType lp_typ;
  bool lp_bypass;
};

struct tFir
{
  uint16_t addr;
  uint16_t numCoeffs;
  bool bypass;
  float* ir;
};

struct tMasterVolume
{
  uint16_t addr;
  float val;
};

struct tInputSelector
{
  uint16_t analog[8];
  uint16_t spdif[8];
  uint16_t uac[8];
  uint16_t exp[8];
  uint16_t port[8];
};

struct tSpdifOutputSelector
{
  uint16_t addrChnLeft[6];
  uint16_t addrPortLeft;
  uint16_t addrChnRight[6];
  uint16_t addrPortRight;
};

struct tSpdifOutput
{
  uint32_t selectionLeft;
  uint32_t selectionRight;
};

extern tSettings Settings;

extern tInput paramInputs[8];
extern tHPLP paramHP[8];
extern tShelving paramLshelv[8];
extern tPeq paramPeq[80];
extern tShelving paramHshelv[8];
extern tHPLP paramLP[8];
extern tPhase paramPhase[8];
extern tDelay paramDelay[8];
extern tGain paramGain[8];
extern tCrossover paramCrossover[8];
extern tFir paramFir[MAX_NUM_FIRS];
extern tMasterVolume masterVolume;
extern tInputSelector inputSelector;
extern tSpdifOutput spdifOutput;
extern tSpdifOutputSelector spdifOutputSelector;

extern int numInputs;
extern int numHPs;
extern int numLShelvs;
extern int numPEQs;
extern int numHShelvs;
extern int numLPs;
extern int numPhases;
extern int numDelays;
extern int numGains;
extern int numCrossovers;
extern int numFIRs;

extern float sampleRate;

extern uint16_t addrVPot;

extern String currentPlugInName;

extern String presetUsrparamFile[MAX_NUM_PRESETS];
extern String presetAddonCfgFile[MAX_NUM_PRESETS];

extern uint8_t currentPreset;

extern byte currentAddOnCfg[3];

/*! Reads the plugin meta data from JSON file.
 */
void readPluginMeta( void );

/*! Inits the default values for filters etc.
 */
void initUserParams( void );
#endif
