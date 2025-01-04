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

#define HR_WHEEL_UP 0xF0
#define HR_WHEEL_DOWN 0xF1
#define HR_TERMINATE_ACTION 0xF2
#define THREAD_SLEEP_SEGMENTATION_MS 5 // this can handle without issue for 200 fps
#define HY_BYPASS_EXECUTION_FLAG 0x01090904

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

