#ifndef STRUCTS
#define STRUCTS

#include <string>
#include <vector>
#include <windows.h>
#include <iostream>  // Don't forget to include the header for cout
#include "enums.h"
using namespace std;

struct Trigger {
    string name;
    string key;

    // Constructor
    Trigger(const string& name = "", const string& key = "")
        : name(name), key(key) {}

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
    vector<string> keys;
    string profileName;

    // Constructor
    Action(const string& name = "", const ActionType& type = ActionType::SIMPLE, const vector<string>& keys = {}, const string& profileName = "")
        : name(name), type(type), keys(keys), profileName(profileName) {}

    void print() const {
        cout << "\t\tname: " << name
             << "\n\t\ttype: " << type
             << "\n\t\tprofileName: " << profileName
             << "\n\t\tkeys: ";
        for (const auto& key : keys) {
            cout << key << " ";
        }
        cout << "\n\n";
    }
};

struct OptimizedAction{
    int index;
    string name;
    ActionType type;
    vector<string> keys;
    vector<int> keyCodes;
    string profileName;
    int profileIndex;
};

struct Mapping {
    string triggerName;
    string actionName;

    // Constructor
    Mapping(const string& triggerName = "", const string& actionName = "")
        : triggerName(triggerName), actionName(actionName) {}

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

    // Constructor
    Profile(const string& name = "", const vector<string>& programNames = {}, const vector<Mapping>& mapping = {})
        : name(name), programNames(programNames), mapping(mapping) {}

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
    vector<string> programNames;
    vector<Mapping> mapping;
    vector<OptimizedMapping> optimizedMapping;
    int actionIdMap[256];
};

struct Config {
    vector<Trigger> triggers;
    vector<Action> actions;
    vector<Profile> profiles;
    string defaultProfileName;

    // Constructor
    Config(const vector<Trigger>& triggers = {}, const vector<Action>& actions = {}, const vector<Profile>& profiles = {}, const string& defaultProfileName = "")
        : triggers(triggers), actions(actions), profiles(profiles), defaultProfileName(defaultProfileName) {}

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
    bool isUp;

    // Constructor
    InputTrigger(int keyCode = 0, bool isUp = false)
        : keyCode(keyCode), isUp(isUp) {}
};

#endif // STRUCTS
