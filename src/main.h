#ifndef KEY_REMAPPER_H
#define KEY_REMAPPER_H

#include <iostream>
#include <windows.h>
#include <fstream>
#include <string>
#include <vector>
#include <optional>
#include <nlohmann/json.hpp>
#include <thread>
#include "config/structs.h"
#include "config/enums.h"
#include "config/const.h"

using json = nlohmann::json;
using namespace std;

// Global variables
extern HHOOK keyboardHook;
extern HHOOK mouseHook;
extern Config config;
extern map<string,int> keyCodeMap;

extern int overrideProfileIndex;
extern int defaultProfileIndex;
extern WindowInfo windowInfoCache;
extern int profileCacheIndex;
extern int triggerActionIndexMap[256];
extern int keyDownActionIndex[256];
extern bool profileShiftButtonHold[256];

extern vector<OptimizedAction> optimizedActions;
extern vector<OptimizedTrigger> optimizedTriggers;
extern vector<OptimizedProfile> optimizedProfiles;
extern vector<thread> macroActionThreads;
extern vector<bool> isMacroActionThreadRunnings;



#endif  // KEY_REMAPPER_H

