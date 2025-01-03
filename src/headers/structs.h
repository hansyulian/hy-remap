#ifndef STRUCTS
#define STRUCTS

#include <string>
#include <vector>
#include <windows.h>
#include <iostream>  // Don't forget to include the header for cout
#include "enums.h"
using namespace std;

struct MacroItem{
    string key;
    int delayMs;
    bool up;
};

struct OptimizedMacroItem{
    int keyCode;
    string key;
    int delayMs;
    bool up;
    // Default constructor
    OptimizedMacroItem() 
        : keyCode(-1), key(""), delayMs(-1), up(false) {}
};

struct Trigger {
    string name;
    string key;

};

struct OptimizedTrigger{
    int index;
    string name;
    string key;
    int keyCode;
};

struct Action {
    string name;
    ActionType type;
    // for simple
    vector<string> keys;

    // for profile shift
    string profileName;

    // for macro
    vector<MacroItem> macroItems;
    MacroRepeatMode macroRepeatMode;
    int macroRepeatDelayMs;

};

struct OptimizedAction{
    int index;
    string name;
    ActionType type;
    
    // for simple
    vector<string> *keys;
    vector<int> keyCodes;

    // for profile shift
    string profileName;
    int profileIndex;

    // for macro
    // for macro
    vector<MacroItem> *macroItems;
    vector<OptimizedMacroItem> optimizedMacroItems;
    MacroRepeatMode macroRepeatMode;
    int macroRepeatDelayMs;

};

struct Mapping {
    string triggerName;
    string actionName;
};


struct OptimizedMapping{
    int index;
    string triggerName;
    string actionName;
    int triggerIndex;
    int actionIndex;
};

struct Profile {
    string name;
    vector<string> programNames;
    vector<Mapping> mapping;
};

struct OptimizedProfile {
    int index;
    string name;
    vector<string> *programNames;
    vector<string> lowerCaseProgramNames;
    vector<Mapping> *mapping;
    vector<OptimizedMapping> optimizedMapping;
    int actionIdMap[256];
};

struct Config {
    vector<Trigger> triggers;
    vector<Action> actions;
    vector<Profile> profiles;
    string defaultProfileName;

};

struct KeyAction {
    int keyCode;
    bool up;

    // Constructor
    KeyAction(int keyCode = 0, bool up = false)
        : keyCode(keyCode), up(up) {}
};

struct WindowInfo {
    string name;
    string executable;
    HWND hwnd;
    DWORD processId;
};

#endif // STRUCTS
