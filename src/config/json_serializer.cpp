#include "config.h"

// Define how to deserialize the JSON into the Trigger struct
void from_json(const json& j, Trigger& var) {
    
    j.at("name").get_to(var.name);
    j.at("key").get_to(var.key);
}

void from_json(const json& j, MacroItem& var){
    if (j.contains("key")){
        j.at("key").get_to(var.key);
    }
    if (j.contains("up")){
        j.at("up").get_to(var.up);
    }
    if (j.contains("delayMs")){
        j.at("delayMs").get_to(var.delayMs);
    }
}

void from_json(const json& j, SimpleAction& var){
    j.at("keys").get_to(var.keys);  // Assuming 'keys' is a list of strings

}
void from_json(const json& j, MacroAction& var){
    j.at("items").get_to(var.items);
    j.at("repeatDelayMs").get_to(var.repeatDelayMs);
    string repeatMode = j.at("repeatMode").get<string>();
    if (repeatMode == "none"){
        var.repeatMode = MacroRepeatMode::NONE;
    }
    if (repeatMode == "hold"){
        var.repeatMode = MacroRepeatMode::HOLD;
    }
    if (repeatMode == "toggle"){
        var.repeatMode = MacroRepeatMode::TOGGLE;
    }
}
void from_json(const json& j, ProfileShiftAction& var){    
    j.at("profileName").get_to(var.profileName);
}
void from_json(const json& j, RunProgramAction& var){
    j.at("path").get_to(var.path);
}
void from_json(const json& j, AudioMixerAction& var){
    if (j.contains("processName")){
        j.at("processName").get_to(var.processName);
    }
    if (j.contains("value")){
        j.at("value").get_to(var.value);
    }
    string type = j.at("type").get<string>();
    if (type == "set"){
        var.type = AudioMixerControlType::SET;
    }
    if (type == "add"){
        var.type = AudioMixerControlType::ADD;
    }
    if (type == "toggle"){
        var.type = AudioMixerControlType::TOGGLE_MUTE;
    }
    if (type == "mute"){
        var.type = AudioMixerControlType::MUTE;
    }
    if (type == "unmute"){
        var.type = AudioMixerControlType::UNMUTE;
    }
}

// Define how to deserialize the JSON into the Action struct
void from_json(const json& j, Action& var) {
    
    j.at("name").get_to(var.name);
    
    var.type = ActionType::SIMPLE;
    string typeValue = j.at("type").get<string>();
    if (typeValue == "simple"){        
        var.type = ActionType::SIMPLE;
        j.at("simple").get_to(var.simple); 
    }
    if (typeValue == "profileShift"){
        var.type = ActionType::PROFILE_SHIFT;
        j.at("profileShift").get_to(var.profileShift);
    }
    if (typeValue == "macro"){
        var.type = ActionType::MACRO;
        j.at("macro").get_to(var.macro);
    }
    if (typeValue == "runProgram"){
        var.type = ActionType::RUN_PROGRAM;
        j.at("runProgram").get_to(var.runProgram);
    }
    if (typeValue == "audioMixer"){
        var.type = ActionType::AUDIO_MIXER;
        j.at("audioMixer").get_to(var.audioMixer);
    }
}

// Define how to deserialize the JSON into the Mapping struct
void from_json(const json& j, Mapping& var) {
    j.at("triggerName").get_to(var.triggerName);
    j.at("actionName").get_to(var.actionName);
}

// Define how to deserialize the JSON into the Profile struct
void from_json(const json& j, Profile& var) {
    
    j.at("name").get_to(var.name);
    if (j.contains("parentName")){
        j.at("parentName").get_to(var.parentName);
    }

    // Set programNames to an empty vector if not defined
    if (j.contains("programNames")) {
        j.at("programNames").get_to(var.programNames);
    } else {
        var.programNames = {}; // Assign an empty vector
    }

    // Set mapping to an empty vector if not defined
    if (j.contains("mapping")) {
        j.at("mapping").get_to(var.mapping);
    } else {
        var.mapping = {}; // Assign an empty vector
    }
}

// Define how to deserialize the JSON into the Config struct
void from_json(const json& j, Config& var) {
    j.at("triggers").get_to(var.triggers);
    j.at("actions").get_to(var.actions);
    j.at("profiles").get_to(var.profiles);
    if (j.contains("defaultProfileName")){
        j.at("defaultProfileName").get_to(var.defaultProfileName);
    }
    if (j.contains("rootProfileName")){
        j.at("rootProfileName").get_to(var.rootProfileName);
    }
}
