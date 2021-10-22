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

struct tPeqBank
{
  uint16_t addr[MAX_BANDS_PER_PEQBANK];
  float gain[MAX_BANDS_PER_PEQBANK];
  float fc[MAX_BANDS_PER_PEQBANK];
  float Q[MAX_BANDS_PER_PEQBANK];
  bool bypass[MAX_BANDS_PER_PEQBANK];
  uint16_t numBands;
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

extern tInput paramInputs[MAX_NUM_INPUTS];
extern tHPLP paramHP[MAX_NUM_HPS];
extern tShelving paramLshelv[MAX_NUM_LSHELVS];
extern tPeq paramPeq[MAX_NUM_PEQS];
extern tPeqBank paramPeqBank[MAX_NUM_PEQBANKS];
extern tShelving paramHshelv[MAX_NUM_HSHELVS];
extern tHPLP paramLP[MAX_NUM_LPS];
extern tPhase paramPhase[MAX_NUM_PHASES];
extern tDelay paramDelay[MAX_NUM_DELAYS];
extern tGain paramGain[MAX_NUM_GAINS];
extern tCrossover paramCrossover[MAX_NUM_CROSSOVER];
extern tFir paramFir[MAX_NUM_FIRS];
extern tMasterVolume masterVolume;
extern tInputSelector inputSelector;
extern tSpdifOutput spdifOutput;
extern tSpdifOutputSelector spdifOutputSelector;

extern int numInputs;
extern int numOutputs;
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
extern int numPeqBanks;

extern float sampleRate;

extern uint16_t addrVPot;

extern String currentPlugInName;
extern String pluginVersion;

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
