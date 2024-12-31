#ifndef KEY_REMAPPER_H
#define KEY_REMAPPER_H

#include <iostream>
#include <windows.h>
#include <fstream>
#include <string>
#include <vector>
#include <nlohmann/json.hpp>
#include "structs.h"
#include "enums.h"

#define HR_WHEEL_UP 0xF0
#define HR_WHEEL_DOWN 0xF1

using json = nlohmann::json;
using namespace std;

// Global variables
extern HHOOK keyboardHook;
extern HHOOK mouseHook;
extern Config config;
extern map<string,int> keyCodeMap;

extern int overrideProfileIndex;
extern int defaultProfileIndex;
extern string profileCacheWindowName;
extern int profileCacheIndex;
extern int triggerActionIndexMap[256];
extern int keyDownActionIndex[256];

extern vector<OptimizedAction> optimizedActions;
extern vector<OptimizedTrigger> optimizedTriggers;
extern vector<OptimizedProfile> optimizedProfiles;

// Function declarations
void performAction(const OptimizedAction& action,const InputTrigger& inputTrigger);
int getKeyCodeFromString(const string& key);
LRESULT CALLBACK keyboardProc(int nCode, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK mouseProc(int nCode, WPARAM wParam, LPARAM lParam);
void startKeyboardAndMouseHook();
void stopKeyboardAndMouseHook();
OptimizedProfile* getActiveProfile();
string loadConfigString();
void loadConfig();
void calculateOptimizedConfig();
bool handleInput(const InputTrigger& inputTrigger);
void releaseOngoingAction(const InputTrigger& inputTrigger);

void from_json(const json& j, Trigger& t);
void from_json(const json& j, Action& a);
void from_json(const json& j, Mapping& m);
void from_json(const json& j, Profile& p);
void from_json(const json& j, Config& c);

INPUT convertKeyCodeToInput(int keyCode, bool isKeyUp);
OptimizedAction* getActionByName(const string& name);
int getActionIndexByName(const string& name);
OptimizedTrigger* getTriggerByName(const string& name);
int getTriggerIndexByName(const string& name);
OptimizedProfile* getProfileByName(const string& name);
int getProfileIndexByName(const string& name);

// actions
// simple action
void performSimpleAction(const OptimizedAction& action, const InputTrigger& inputTrigger);
// profile shift action
void performProfileShiftAction(const OptimizedAction& action, const InputTrigger& inputTrigger);
void releaseProfileShiftAction(const OptimizedAction& action, const InputTrigger& inputTrigger);

#endif  // KEY_REMAPPER_H

