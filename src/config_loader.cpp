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

void loadConfig(){
  string configString = loadConfigString();
  json configJson = json::parse(configString);

  // Deserialize into Config struct
  config = configJson.get<Config>();
  config.print();

}

void calculateOptimizedConfig(){
  for (auto& trigger: config.triggers){
    OptimizedTrigger optimizedTrigger;
    optimizedTrigger.key = trigger.key;
    optimizedTrigger.keyCode = getKeyCodeFromString(trigger.key);
    optimizedTrigger.name = trigger.name;
    optimizedTrigger.index = optimizedTriggers.size();
    optimizedTriggers.push_back(optimizedTrigger);
  }
  for (auto& action:config.actions){
    OptimizedAction optimizedAction;
    optimizedAction.name = action.name;
    optimizedAction.keys = action.keys;
    optimizedAction.profileName = action.profileName;
    optimizedAction.type = action.type;
    for (auto& key:action.keys){
      auto keyCode = getKeyCodeFromString(key);
      optimizedAction.keyCodes.push_back(keyCode);
    }
    optimizedAction.index = optimizedActions.size();
    optimizedActions.push_back(optimizedAction);
  }
  for (auto& profile:config.profiles){
    OptimizedProfile optimizedProfile;
    optimizedProfile.name = profile.name;
    optimizedProfile.mapping = profile.mapping;
    optimizedProfile.programNames = profile.programNames;
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
  }
  for (auto& optimizedAction:optimizedActions){
    if (!optimizedAction.profileName.empty()){
      optimizedAction.profileIndex = getProfileIndexByName(optimizedAction.profileName);
    }
  }
  defaultProfileIndex = getProfileIndexByName(config.defaultProfileName);
}