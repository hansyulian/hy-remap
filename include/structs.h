#ifndef STRUCTS
#define STRUCTS

#include <string>
#include <vector>
#include <windows.h>
#include <spdlog/spdlog.h>  // Include spdlog
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
        spdlog::info("\t\tid: {}", id);
        spdlog::info("\t\tname: {}", name);
        spdlog::info("\t\tkey: {}", key);
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
        spdlog::info("\t\tid: {}", id);
        spdlog::info("\t\tname: {}", name);
        spdlog::info("\t\ttype: {}", type);
        std::string keysPrint;
        for (size_t i = 0; i < keys.size(); ++i) {
            keysPrint += keys[i];
            if (i < keys.size() - 1) {
                keysPrint += " "; // Add a space between elements
            }
        }
        spdlog::info("\t\tkeys: {}", keysPrint);
    }

};

struct Mapping {
    int triggerId;
    int actionId;

    // Constructor
    Mapping(int triggerId = -1, int actionId = -1)
        : triggerId(triggerId), actionId(actionId) {}

    void print() const {
        spdlog::info("\t\t\ttriggerId: {}\tactionId: {}", triggerId, actionId);
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
        spdlog::info("\t\tid: {}", id);
        spdlog::info("\t\tname: {}", name);
        spdlog::info("\t\tprogramNames: ");
        for (const auto& prog : programNames) {
            spdlog::info("\t\t\t{}", prog);
        }
        spdlog::info("\t\tmapping:");
        for (const auto& m : mapping) {
            m.print();
        }
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
        spdlog::info("Config");
        spdlog::info("\tdefaultProfileId: {}", defaultProfileId);
        spdlog::info("\ttriggers:");
        for (const auto& trigger : triggers) {
            trigger.print();
        }
        spdlog::info("\tactions:");
        for (const auto& action : actions) {
            action.print();
        }
        spdlog::info("\tprofiles:");
        for (const auto& profile : profiles) {
            profile.print();
        }
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
