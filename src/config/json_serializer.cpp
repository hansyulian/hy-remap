#include "config.h"

// Define how to deserialize the JSON into the Trigger struct
void from_json(const json& j, Trigger& t) {
    
    j.at("name").get_to(t.name);
    j.at("key").get_to(t.key);
}

void from_json(const json& j, MacroItem& m){
    if (j.contains("key")){
        j.at("key").get_to(m.key);
    }
    if (j.contains("up")){
        j.at("up").get_to(m.up);
    }
    if (j.contains("delayMs")){
        j.at("delayMs").get_to(m.delayMs);
    }
}
// Define how to deserialize the JSON into the Action struct
void from_json(const json& j, Action& a) {
    
    j.at("name").get_to(a.name);
    
    a.type = ActionType::SIMPLE;
    string typeValue = j.at("type").get<string>();
    if (typeValue == "simple"){        
        a.type = ActionType::SIMPLE;
        j.at("keys").get_to(a.keys);  // Assuming 'keys' is a list of strings
    }
    if (typeValue == "profileShift"){
        a.type = ActionType::PROFILE_SHIFT;
        j.at("profileName").get_to(a.profileName);
    }
    if (typeValue == "macro"){
        a.type = ActionType::MACRO;
        j.at("macroItems").get_to(a.macroItems);
        j.at("macroRepeatDelayMs").get_to(a.macroRepeatDelayMs);
        string repeatMode = j.at("macroRepeatMode").get<string>();
        if (repeatMode == "none"){
            a.macroRepeatMode = MacroRepeatMode::NONE;
        }
        if (repeatMode == "hold"){
            a.macroRepeatMode = MacroRepeatMode::HOLD;
        }
        if (repeatMode == "toggle"){
            a.macroRepeatMode = MacroRepeatMode::TOGGLE;
        }
    }
    if (typeValue == "runProgram"){
        a.type = ActionType::RUN_PROGRAM;
        j.at("programPath").get_to(a.programPath);
    }
}

// Define how to deserialize the JSON into the Mapping struct
void from_json(const json& j, Mapping& m) {
    j.at("triggerName").get_to(m.triggerName);
    j.at("actionName").get_to(m.actionName);
}

// Define how to deserialize the JSON into the Profile struct
void from_json(const json& j, Profile& p) {
    
    j.at("name").get_to(p.name);

    // Set programNames to an empty vector if not defined
    if (j.contains("programNames")) {
        j.at("programNames").get_to(p.programNames);
    } else {
        p.programNames = {}; // Assign an empty vector
    }

    // Set mapping to an empty vector if not defined
    if (j.contains("mapping")) {
        j.at("mapping").get_to(p.mapping);
    } else {
        p.mapping = {}; // Assign an empty vector
    }
}

// Define how to deserialize the JSON into the Config struct
void from_json(const json& j, Config& c) {
    j.at("triggers").get_to(c.triggers);
    j.at("actions").get_to(c.actions);
    j.at("profiles").get_to(c.profiles);
    j.at("defaultProfileName").get_to(c.defaultProfileName);
}
