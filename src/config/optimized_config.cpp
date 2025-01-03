#include "config.h"

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
    for (const auto& programName :profile.programNames){
      optimizedProfile.lowerCaseProgramNames.push_back(lowerCaseString(programName));
    }
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