#include "config.h"
#include "../utils/utils.h"

OptimizedTrigger registerOptimizedTrigger(Trigger *trigger){
    OptimizedTrigger optimizedTrigger;
    optimizedTrigger.trigger = trigger;
    optimizedTrigger.keyCode = getKeyCodeFromString(trigger->key);
    optimizedTrigger.index = optimizedTriggers.size();
    optimizedTriggers.push_back(optimizedTrigger);
    return optimizedTrigger;
}

OptimizedAction registerOptimizedAction(Action *action){  
  OptimizedAction optimizedAction;
  optimizedAction.action = action;
  optimizedAction.runProgramPath = &action->runProgram.path;
  optimizedAction.type = action->type;
  optimizedAction.index = optimizedActions.size();
  switch (optimizedAction.type){
    case ActionType::SIMPLE:
      for (auto& key:action->simple.keys){
        auto keyCode = getKeyCodeFromString(key);
        optimizedAction.keyCodes.push_back(keyCode);
      }
      break;
    case ActionType::PROFILE_SHIFT:
      break;
    case ActionType::MACRO:
      auto macro = action->macro;
      optimizedAction.macroRepeatDelayMs = macro.repeatDelayMs;
      optimizedAction.macroRepeatMode = macro.repeatMode;
      
      for (auto& macroItem:macro.items){
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
  return optimizedAction;
}

void optimizeTriggers(){
  cout << "Optimizing Triggers" << endl;
  for (auto& trigger: config.triggers){
    auto optimizedTrigger = registerOptimizedTrigger(&trigger);
    cout << "Trigger: "<< optimizedTrigger.index << " " << optimizedTrigger.trigger->name << endl;
  }
}

void optimizeActions(){
  
  cout << "Optimizing Actions" << endl;
  for (auto& action:config.actions){
    auto optimizedAction = registerOptimizedAction(&action);
    cout << "Trigger: "<< optimizedAction.index << " " << optimizedAction.action->name << endl;
  }
  macroActionThreads.resize(optimizedActions.size());
}

void optimizeProfiles(){
  
  cout << "Optimizing Profiles" << endl;
  for (auto& profile:config.profiles){
    OptimizedProfile optimizedProfile;
    optimizedProfile.profile = &profile;
    for (const auto& programName :profile.programNames){
      optimizedProfile.lowerCaseProgramNames.push_back(lowerCaseString(programName));
    }
    for (int i = 0; i < 256; i++){
      optimizedProfile.actionIdMap[i] = -1;
    }
    for (auto& mapping: profile.mapping){
      OptimizedMapping optimizedMapping;
      optimizedMapping.mapping = &mapping;
      int triggerIndex = getTriggerIndexByName(mapping.triggerName);
      optimizedMapping.triggerIndex = triggerIndex;
      int actionIndex = getActionIndexByName(mapping.actionName);
      optimizedMapping.actionIndex = actionIndex;
      optimizedProfile.optimizedMapping.push_back(optimizedMapping);
      optimizedProfile.actionIdMap[optimizedTriggers[triggerIndex].keyCode] = actionIndex;
    }
    optimizedProfile.index = optimizedProfiles.size();
    optimizedProfiles.push_back(optimizedProfile);
    cout << "Profile: "<< optimizedProfile.index << " " << optimizedProfile.profile->name << endl;
  }
}

void optimizeTriggerAndActionShortcuts(){
  for (auto& profile: config.profiles){
    for (auto& mapping: profile.mapping){
      auto triggerIndex = getTriggerIndexByName(mapping.triggerName);
      if (triggerIndex == -1){
        OptimizedTrigger optimizedTrigger;
        
        optimizedTriggers.push_back(optimizedTrigger);
      }
      auto actionIndex = getActionIndexByName(mapping.actionName);
      if (actionIndex == -1){

      }
    }
  }
}

void optimizeConfig(){
  optimizeTriggers();
  optimizeActions();
  optimizeTriggerAndActionShortcuts();
  optimizeProfiles();  
  for (auto& optimizedAction:optimizedActions){
    auto profileName = optimizedAction.action->profileShift.profileName;
    if (!profileName.empty()){
      optimizedAction.profileIndex = getProfileIndexByName(profileName);
    }
  }
  defaultProfileIndex = getProfileIndexByName(config.defaultProfileName);
  debugOptimizedConfig();
  isMacroActionThreadRunnings.resize(optimizedActions.size());
  
}