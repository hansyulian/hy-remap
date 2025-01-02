#include "main.h"

#include <fstream>
#include <sstream>
#include <iostream>

string loadConfigString() {
    string filePath = "./config.json";
    ifstream file(filePath);  // Open the file in read mode
    if (!file.is_open()) {
        cerr << "Error opening file: " << filePath << endl;
        return "";  // Return an empty string if the file can't be opened
    }

    stringstream buffer;
    buffer << file.rdbuf();  // Read the file into the stringstream
    return buffer.str();  // Return the file content as a string
}

void debugTrigger(const Trigger& trigger)  {
  auto name = trigger.name;
  auto key = trigger.key;
  cout << "\t\tname: " << name
        << "\n\t\tkey: " << key
        << "\n" << endl;
}
void debugAction(const Action& action) {
  auto name = action.name;
  auto type = action.type;
  auto profileName = action.profileName;
  auto keys = action.keys;
  auto macroItems = action.macroItems;
  cout << "\t\tname: " << name
        << "\n\t\ttype: " << type;
  switch (type){
      case ActionType::PROFILE_SHIFT:
          cout << "\n\t\tprofileName: " << profileName;
          break;
      case ActionType::SIMPLE:
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
void debugMapping(const Mapping& mapping) {
  auto triggerName = mapping.triggerName;
  auto actionName = mapping.actionName;
  cout << "\t\t\ttriggerName: " << triggerName
        << "\tactionName: " << actionName << endl;
}
void debugProfile(const Profile& profile) {
  auto name = profile.name;
  auto programNames = profile.programNames;
  auto mapping = profile.mapping;
  cout << "\t\tname: " << name
        << "\n\t\tprogramNames: ";
  for (const auto& prog : programNames) {
      cout << "\n\t\t\t" << prog;
  }
  cout << "\n\t\tmapping:\n";
  for (const auto& m : mapping) {
      debugMapping(m);
  }
  cout << "\n" << endl;
}
void debugConfig(){
  cout << "Debug Optimized Config" << endl;
  cout << "------------------------------------------" << endl;
  cout << "\n\tdefaultProfileName: " << config.defaultProfileName
        << "\n\ttriggers:\n";
  for (const auto& trigger : config.triggers) {
      debugTrigger(trigger);
  }
  cout << "\tactions:\n";
  for (const auto& action : config.actions) {
      debugAction(action);
  }
  cout << "\tprofiles:\n";
  for (const auto& profile : config.profiles) {
      debugProfile(profile);
  }
  cout << "\n" << endl;  
}

void loadConfig(){
  string configString = loadConfigString();
  json configJson = json::parse(configString);

  // Deserialize into Config struct
  config = configJson.get<Config>();
}

void debugOptimizedMapping(const OptimizedMapping& mapping) {
  auto triggerName = mapping.triggerName;
  auto actionName = mapping.actionName;
  auto actionIndex = mapping.actionIndex;
  auto triggerIndex = mapping.triggerIndex;
  cout << "\t\t\t" << triggerIndex <<".\t" << triggerName
        << "\t\t" << actionIndex << ".\t" <<actionName << endl;
}
void debugOptimizedProfile(const OptimizedProfile& profile){
  auto name = profile.name;
  auto programNames = profile.programNames;
  auto mapping = profile.mapping;
  auto optimizedMapping = profile.optimizedMapping;
  auto actionIdMap = profile.actionIdMap;
  cout << "\t\tname: " << name
        << "\n\t\tprogramNames: ";
  for (const auto& prog : *programNames) {
      cout << "\n\t\t\t" << prog;
  }
  cout << "\n\t\tmapping:\n";
  for (const auto& m : optimizedMapping) {
      debugOptimizedMapping(m);
  }
  cout << "\n\t\taction code map:\n";
  for (int i = 0; i < 256; i++){
    if (actionIdMap[i] != -1){
      cout << "\t\t\t" <<i << "\t-> " << actionIdMap[i] << endl;
    }
  }
  cout << "\n" << endl;
}

void debugOptimizedAction(const OptimizedAction& action){
  auto index = action.index;
  auto name = action.name;
  auto type = action.type;
  cout << "\t\t" << index << ".\t" << name << "\t" ;
  switch(type){
    case ActionType::SIMPLE:
      cout << type << ". Simple " << "\n\t\t\t";
      for (int i = 0; i < action.keyCodes.size();i++){
        auto keyCode = action.keyCodes[i];
        auto key = (*action.keys)[i];
        cout << key << " (" << keyCode << ")\t";
      }
      cout << endl;
      break;
    case ActionType::PROFILE_SHIFT:
      cout << type << ". Profile Shift " << "\t" << action.profileIndex << ". " << action.profileName << endl;
      break;
    case ActionType::MACRO:
      cout << "\t\t\tMacro \t\t" << action.profileIndex << ". " << endl;
      for (int i = 0; i < action.optimizedMacroItems.size(); i++){
        auto macro = action.optimizedMacroItems[i];
        string upLabel = "DOWN";
        if (macro.up){
          upLabel = "UP";
        }
        cout << "\t\t\t" << macro.key <<"(" << macro.keyCode <<")\t" << upLabel << "\t\t" << macro.delayMs << "ms" << endl;
      }
      cout << endl;
      break;
  }
  cout << endl;
}

void debugOptimizedTrigger(const OptimizedTrigger& trigger){
  auto name = trigger.name;
  auto key = trigger.key;
  auto index = trigger.index;
  auto keyCode = trigger.keyCode;
  cout << "\t\t" << index << ".\t" << name << "\t" << key << " (" << keyCode << ")" <<endl;
}

void debugOptimizedConfig(){
  cout << "Debug Optimized Config" << endl;
  cout << "------------------------------------------" << endl;
  for (const auto& trigger : optimizedTriggers) {
      debugOptimizedTrigger(trigger);
  }
  cout << "\tactions:\n";
  for (const auto& action : optimizedActions) {
      debugOptimizedAction(action);
  }
  cout << "\tprofiles:\n";
  for (const auto& profile : optimizedProfiles) {
      debugOptimizedProfile(profile);
  }
  cout << "\n" << endl;  
  cout << "\n\tdefaultProfileName: " << config.defaultProfileName << endl;
  cout << "\n\tdefaultProfileIndex: " << defaultProfileIndex << endl;
  cout << "------------------------------------------" << endl;
  cout << "------------------------------------------" << endl;
  cout << endl;
}

void calculateOptimizedConfig(){
  cout << "Optimizing Triggers" << endl;
  for (auto& trigger: config.triggers){
    OptimizedTrigger optimizedTrigger;
    optimizedTrigger.key = trigger.key;
    optimizedTrigger.keyCode = getKeyCodeFromString(trigger.key);
    optimizedTrigger.name = trigger.name;
    optimizedTrigger.index = optimizedTriggers.size();
    optimizedTriggers.push_back(optimizedTrigger);
    cout << "Trigger: "<< optimizedTrigger.index << " " << optimizedTrigger.name << endl;
  }
  cout << "Optimizing Actions" << endl;
  for (auto& action:config.actions){
    OptimizedAction optimizedAction;
    optimizedAction.name = action.name;
    optimizedAction.keys = &action.keys;
    optimizedAction.profileName = action.profileName;
    optimizedAction.type = action.type;
    optimizedAction.index = optimizedActions.size();
    switch (optimizedAction.type){
      case ActionType::SIMPLE:
        for (auto& key:action.keys){
          auto keyCode = getKeyCodeFromString(key);
          optimizedAction.keyCodes.push_back(keyCode);
        }
        break;
      case ActionType::PROFILE_SHIFT:
        break;
      case ActionType::MACRO:
        optimizedAction.macroRepeatDelayMs = action.macroRepeatDelayMs;
        optimizedAction.macroRepeatMode = action.macroRepeatMode;
        
        for (auto& macroItem:action.macroItems){
          OptimizedMacroItem optimizedMacroItem = {};
          optimizedMacroItem.key = macroItem.key;
          optimizedMacroItem.up = macroItem.up;
          optimizedMacroItem.delayMs = macroItem.delayMs;
          optimizedMacroItem.keyCode = getKeyCodeFromString(macroItem.key);
          optimizedAction.optimizedMacroItems.push_back(optimizedMacroItem);
        }
        if (optimizedAction.macroRepeatMode != MacroRepeatMode::NONE && optimizedAction.macroRepeatDelayMs > 0){
          OptimizedMacroItem optimizedMacroItem = {};
          optimizedMacroItem.delayMs = optimizedAction.macroRepeatDelayMs;
          optimizedAction.optimizedMacroItems.push_back(optimizedMacroItem);
        }
        break;
    }
    optimizedActions.push_back(optimizedAction);
    cout << "Trigger: "<< optimizedAction.index << " " << optimizedAction.name << endl;
  }
  macroActionThreads.resize(optimizedActions.size());
  isMacroActionThreadRunnings.resize(optimizedActions.size());
  cout << "Optimizing Profiles" << endl;
  for (auto& profile:config.profiles){
    OptimizedProfile optimizedProfile;
    optimizedProfile.name = profile.name;
    optimizedProfile.mapping = &profile.mapping;
    optimizedProfile.programNames = &profile.programNames;
    for (int i = 0; i < 256; i++){
      optimizedProfile.actionIdMap[i] = -1;
    }
    for (auto& mapping: profile.mapping){
      OptimizedMapping optimizedMapping;
      optimizedMapping.actionName = mapping.actionName;
      optimizedMapping.triggerName = mapping.triggerName;
      int triggerIndex = getTriggerIndexByName(mapping.triggerName);
      optimizedMapping.triggerIndex = triggerIndex;
      int actionIndex = getActionIndexByName(mapping.actionName);
      optimizedMapping.actionIndex = actionIndex;
      optimizedProfile.optimizedMapping.push_back(optimizedMapping);
      optimizedProfile.actionIdMap[optimizedTriggers[triggerIndex].keyCode] = actionIndex;
    }
    optimizedProfile.index = optimizedProfiles.size();
    optimizedProfiles.push_back(optimizedProfile);
    cout << "Profile: "<< optimizedProfile.index << " " << optimizedProfile.name << endl;
  }
  for (auto& optimizedAction:optimizedActions){
    if (!optimizedAction.profileName.empty()){
      optimizedAction.profileIndex = getProfileIndexByName(optimizedAction.profileName);
    }
  }
  defaultProfileIndex = getProfileIndexByName(config.defaultProfileName);
  debugOptimizedConfig();
}