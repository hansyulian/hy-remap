#ifndef STRUCTS
#define STRUCTS

#include <string>
#include <vector>
#include <windows.h>
#include <iostream>  // Don't forget to include the header for cout
#include "enums.h"
using namespace std;

struct Trigger {
    int id;
    string name;
    string key;

    // Constructor
    Trigger(int id = -1, const string& name = "", const string& key = "")
        : id(id), name(name), key(key) {}

    void print() const {
        cout << "\t\tid: " << id
             << "\n\t\tname: " << name
             << "\n\t\tkey: " << key
             << "\n" << endl;
    }
};

struct Action {
    int id;
    string name;
    ActionType type;
    vector<string> keys;

    // Constructor
    Action(int id = -1, const string& name = "", const ActionType& type = ActionType::SIMPLE, const vector<string>& keys = {})
        : id(id), name(name), type(type), keys(keys) {}

    void print() const {
        cout << "\t\tid: " << id
             << "\n\t\tname: " << name
             << "\n\t\ttype: " << type
             << "\n\t\tkeys: ";
        for (const auto& key : keys) {
            cout << key << " ";
        }
        cout << "\n\n";
    }
};

struct Mapping {
    int triggerId;
    int actionId;

    // Constructor
    Mapping(int triggerId = -1, int actionId = -1)
        : triggerId(triggerId), actionId(actionId) {}

    void print() const {
        cout << "\t\t\ttriggerId: " << triggerId
             << "\tactionId: " << actionId << endl;
    }
};

struct Profile {
    int id;
    string name;
    vector<string> programNames;
    vector<Mapping> mapping;

    // Constructor
    Profile(int id = -1, const string& name = "", const vector<string>& programNames = {}, const vector<Mapping>& mapping = {})
        : id(id), name(name), programNames(programNames), mapping(mapping) {}

    void print() const {
        cout << "\t\tid: " << id
             << "\n\t\tname: " << name
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

struct Config {
    vector<Trigger> triggers;
    vector<Action> actions;
    vector<Profile> profiles;
    int defaultProfileId;

    // Constructor
    Config(const vector<Trigger>& triggers = {}, const vector<Action>& actions = {}, const vector<Profile>& profiles = {}, int defaultProfileId = -1)
        : triggers(triggers), actions(actions), profiles(profiles), defaultProfileId(defaultProfileId) {}

    void print() const {
        cout << "Config\n\tdefaultProfileId: " << defaultProfileId
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
