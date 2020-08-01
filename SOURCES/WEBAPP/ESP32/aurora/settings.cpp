#include <Arduino.h>
#include "settings.h"

tSettings Settings;

tInput paramInputs[8];
tHPLP paramHP[8];
tShelving paramLshelv[8];
tPeq paramPeq[80];
tShelving paramHshelv[8];
tHPLP paramLP[8];
tPhase paramPhase[8];
tDelay paramDelay[8];
tGain paramGain[8];
tCrossover paramCrossover[8];
tFir paramFir[MAX_NUM_FIRS];
tMasterVolume masterVolume = { 0x0000, -60.0 };
tInputSelector inputSelector;
tSpdifOutput spdifOutput;
tSpdifOutputSelector spdifOutputSelector;

int numInputs = 0;
int numHPs = 0;
int numLShelvs = 0;
int numPEQs = 0;
int numHShelvs = 0;
int numLPs = 0;
int numPhases = 0;
int numDelays = 0;
int numGains = 0;
int numCrossovers = 0;
int numFIRs = 0;

float sampleRate = 48000.0;

uint16_t addrVPot = 0x0000;

String presetUsrparamFile[MAX_NUM_PRESETS] = { "/usrparam.001", "/usrparam.002", "/usrparam.003", "/usrparam.004" };
String presetAddonCfgFile[MAX_NUM_PRESETS] = { "/addoncfg.001", "/addoncfg.002", "/addoncfg.003", "/addoncfg.004" };

uint8_t currentPreset = 0;

byte currentAddOnCfg[3];
