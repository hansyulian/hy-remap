#ifndef STRUCTS
#define STRUCTS

#include <string>
#include <vector>
#include <windows.h>
#include <iostream>  // Don't forget to include the header for cout
#include "enums.h"
#include "const.h"
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
        : keyCode(NO_KEYCODE_FLAG), key(""), delayMs(NO_DELAY_FLAG), up(false) {}
};

struct Trigger {
    string name;
    string key;

};

struct OptimizedTrigger{
    int index;
    int keyCode;
    Trigger* trigger;
};

struct SimpleAction{
    vector<string> keys;    
};

struct ProfileShiftAction{
    string profileName;
};

struct MacroAction{
    vector<MacroItem> items;
    MacroRepeatMode repeatMode;
    int repeatDelayMs;
};

struct RunProgramAction{
    string path;
};

struct Action {
    string name;
    ActionType type;
    SimpleAction simple;
    ProfileShiftAction profileShift;
    MacroAction macro;
    RunProgramAction runProgram;
    // for run program
};

struct OptimizedAction{
    int index;
    ActionType type;
    Action* action;
    // for simple
    vector<int> keyCodes;

    // for profile shift
    int profileIndex;

    // for macro
    vector<OptimizedMacroItem> optimizedMacroItems;
    MacroRepeatMode macroRepeatMode;
    int macroRepeatDelayMs;
    // for run program
    string* runProgramPath;
};

struct Mapping {
    string triggerName;
    string actionName;
};


struct OptimizedMapping{
    int index;
    int triggerIndex;
    int actionIndex;
    Mapping* mapping;
};

struct Profile {
    string name;
    string parentName;
    vector<string> programNames;
    vector<Mapping> mapping;
};

struct OptimizedProfile {
    int index;
    vector<string> lowerCaseProgramNames;
    vector<OptimizedMapping> optimizedMapping;
    int actionIdMap[256];
    Profile* profile;
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
