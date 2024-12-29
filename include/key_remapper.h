#ifndef KEY_REMAPPER_H
#define KEY_REMAPPER_H

#include <iostream>
#include <windows.h>
#include <fstream>
#include <string>
#include <vector>
#include <nlohmann/json.hpp>
#include <spdlog/spdlog.h>
#include "structs.h"
#include "enums.h"

#define HR_WHEEL_UP 0xF0
#define HR_WHEEL_DOWN 0xF1

using json = nlohmann::json;
using namespace std;

// Global variables
extern HHOOK keyboardHook;
extern HHOOK mouseHook;
extern Profile* overrideProfile;
extern Config config;
extern map<string,int> keyCodeMap;
extern Profile* defaultProfile;
extern int ongoingActionIds[256];
// Function declarations
bool isActiveWindowMatchingProfile(const vector<string>& programNames);
void performAction(const Action& action,const InputTrigger& inputTrigger);
int getKeyCodeFromString(const string& key);
LRESULT CALLBACK keyboardProc(int nCode, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK mouseProc(int nCode, WPARAM wParam, LPARAM lParam);
void startKeyboardAndMouseHook();
void stopKeyboardAndMouseHook();
Profile* getProfile();
string loadConfigString();
void loadConfig();
bool handleInput(const InputTrigger& inputTrigger);

void from_json(const json& j, Trigger& t);
void from_json(const json& j, Action& a);
void from_json(const json& j, Mapping& m);
void from_json(const json& j, Profile& p);
void from_json(const json& j, Config& c);


#endif  // KEY_REMAPPER_H
