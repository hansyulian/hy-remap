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
#include "structs.h"
#include "enums.h"

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

extern vector<OptimizedAction> optimizedActions;
extern vector<OptimizedTrigger> optimizedTriggers;
extern vector<OptimizedProfile> optimizedProfiles;
extern vector<thread> macroActionThreads;
extern vector<bool> isMacroActionThreadRunnings;

// Function declarations
void performAction(const OptimizedAction& action,const KeyAction& inputTrigger);
int getKeyCodeFromString(const string& key);
LRESULT CALLBACK keyboardProc(int nCode, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK mouseProc(int nCode, WPARAM wParam, LPARAM lParam);
void startKeyboardAndMouseHook();
void stopKeyboardAndMouseHook();
int getActiveProfileIndex();
string loadConfigString();
void loadConfig();
void calculateOptimizedConfig();
bool handleInput(const KeyAction& inputTrigger);
void releaseOngoingAction(int keyCode, bool force);

WindowInfo getCurrentWindowInfo();
void refreshProfileCache();

void from_json(const json& j, Trigger& t);
void from_json(const json& j, Action& a);
void from_json(const json& j, Mapping& m);
void from_json(const json& j, Profile& p);
void from_json(const json& j, Config& c);

INPUT convertKeyCodeToInput(int keyCode, bool isKeyUp);
void executeInputs(const vector<INPUT>& inputs);
OptimizedAction* getActionByName(const string& name);
int getActionIndexByName(const string& name);
OptimizedTrigger* getTriggerByName(const string& name);
int getTriggerIndexByName(const string& name);
OptimizedProfile* getProfileByName(const string& name);
int getProfileIndexByName(const string& name);


// actions
// simple action
void performSimpleAction(const OptimizedAction& action, const KeyAction& inputTrigger);
void releaseSimpleAction(const OptimizedAction& action);
// profile shift action
void performProfileShiftAction(const OptimizedAction& action, const KeyAction& inputTrigger);
void releaseProfileShiftAction(const OptimizedAction& action);
// macro action
void performMacroAction(const OptimizedAction& action, const KeyAction& inputTrigger);
void releaseMacroAction(const OptimizedAction& action, bool force);

#endif  // KEY_REMAPPER_H

