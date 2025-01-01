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

    void print() const {
        cout << "\t\tname: " << name
             << "\n\t\tkey: " << key
             << "\n" << endl;
    }
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

    void print() const {
        cout << "\t\tname: " << name
             << "\n\t\ttype: " << type;
        switch (type){
            case ActionType::SIMPLE:
                cout << "\n\t\tprofileName: " << profileName;
                break;
            case ActionType::PROFILE_SHIFT:
                cout << "\n\t\tkeys: ";
                for (const auto& key : keys) {
                    cout << key << " ";
                }
                break;
            case ActionType::MACRO:
                cout << "\n\t\tmacros:";
                for (const auto& macro:macroItems){
                    cout << "\n\t\t\t" << macro.key << " " << macro.up << " " << macro.delayMs;
                }
        }
             
        cout << "\n\n";
    }
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

    void print() const {
        cout << "\t\t\ttriggerName: " << triggerName
             << "\tactionName: " << actionName << endl;
    }
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

    void print() const {
        cout << "\t\tname: " << name
             << "\n\t\tprogramNames: ";
        for (const auto& prog : programNames) {
            cout << "\n\t\t\t" << prog;
        }
        cout << "\n\t\tmapping:\n";
        for (const auto& m : mapping) {
            m.print();
        }
        cout << "\n" << endl;
    }
};

struct OptimizedProfile {
    int index;
    string name;
    vector<string> *programNames;
    vector<Mapping> *mapping;
    vector<OptimizedMapping> optimizedMapping;
    int actionIdMap[256];
};

struct Config {
    vector<Trigger> triggers;
    vector<Action> actions;
    vector<Profile> profiles;
    string defaultProfileName;

    void print() const {
        cout << "Config\n\tdefaultProfileName: " << defaultProfileName
             << "\n\ttriggers:\n";
        for (const auto& trigger : triggers) {
            trigger.print();
        }
        cout << "\tactions:\n";
        for (const auto& action : actions) {
            action.print();
        }
        cout << "\tprofiles:\n";
        for (const auto& profile : profiles) {
            profile.print();
        }
        cout << "\n" << endl;
    }
};

struct InputTrigger {
    int keyCode;
    bool up;

    // Constructor
    InputTrigger(int keyCode = 0, bool up = false)
        : keyCode(keyCode), up(up) {}
};

#endif // STRUCTS
