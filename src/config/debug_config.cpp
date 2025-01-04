#include "config.h"

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
  auto profileName = action.profileShift.profileName;
  auto keys = action.simple.keys;
  auto items = action.macro.items;
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
          for (const auto& macro:items){
              cout << "\n\t\t\t" << macro.key << " " << macro.up << " " << macro.delayMs;
          }
  }
        
  cout << "\n\n";
}
void debugMapping(const Mapping& optimizedMapping) {
  auto triggerName = optimizedMapping.triggerName;
  auto actionName = optimizedMapping.actionName;
  cout << "\t\t\ttriggerName: " << triggerName
        << "\tactionName: " << actionName << endl;
}
void debugProfile(const Profile& profile) {
  auto name = profile.name;
  auto programNames = profile.programNames;
  auto optimizedMapping = profile.mapping;
  auto parentName = profile.parentName;
  cout << "\t\tname: " << name
        << "\n\tparentName" << parentName
        << "\n\t\tprogramNames: ";
  for (const auto& prog : programNames) {
      cout << "\n\t\t\t" << prog;
  }
  cout << "\n\t\tmapping:\n";
  for (const auto& m : optimizedMapping) {
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
  for (const auto& optimizedAction : config.actions) {
      debugAction(optimizedAction);
  }
  cout << "\tprofiles:\n";
  for (const auto& profile : config.profiles) {
      debugProfile(profile);
  }
  cout << "\n" << endl;  
}


void debugOptimizedMapping(const OptimizedMapping& optimizedMapping) {
  auto triggerName = optimizedMapping.mapping->triggerName;
  auto actionName = optimizedMapping.mapping->actionName;
  auto actionIndex = optimizedMapping.actionIndex;
  auto triggerIndex = optimizedMapping.triggerIndex;
  cout << "\t\t\t" << triggerIndex <<".\t" << triggerName
        << "\t\t" << actionIndex << ".\t" <<actionName << endl;
}
void debugOptimizedProfile(const OptimizedProfile& optimizedProfile){
  auto name = optimizedProfile.profile->name;
  auto parentName = optimizedProfile.profile->parentName;
  auto parentIndex = optimizedProfile.parentIndex;
  auto programNames = optimizedProfile.profile->programNames;
  auto optimizedMapping = optimizedProfile.optimizedMapping;
  auto actionIdMap = optimizedProfile.actionIdMap;
  cout << "\t\tname: " << name
        << "\n\tparent name "<< parentName << " (" << parentIndex << ")"
        << "\n\t\tprogramNames: ";
  for (const auto& prog : programNames) {
      cout << "\n\t\t\t" << prog;
  }
  cout << "\n\t\tmapping:\n";
  for (const auto& m : optimizedMapping) {
      debugOptimizedMapping(m);
  }
  cout << "\n\t\taction code map:\n";
  for (int i = 0; i < 256; i++){
    if (actionIdMap[i] != NO_ACTION_FLAG){
      cout << "\t\t\t" <<i << "\t-> " << actionIdMap[i] << endl;
    }
  }
  cout << "\n" << endl;
}

void debugOptimizedAction(const OptimizedAction& optimizedAction){
  auto index = optimizedAction.index;
  auto name = optimizedAction.action->name;
  auto type = optimizedAction.type;
  cout << "\t\t" << index << ".\t" << name << "\t" ;
  switch(type){
    case ActionType::SIMPLE:
      cout << type << ". Simple " << "\n\t\t\t";
      for (int i = 0; i < optimizedAction.keyCodes.size();i++){
        auto keyCode = optimizedAction.keyCodes[i];
        auto key = optimizedAction.action->simple.keys[i];
        cout << key << " (" << keyCode << ")\t";
      }
      cout << endl;
      break;
    case ActionType::PROFILE_SHIFT:
      cout << type << ". Profile Shift " << "\t" << optimizedAction.profileIndex << ". " << optimizedAction.action->profileShift.profileName << endl;
      break;
    case ActionType::MACRO:
      cout << "\t\t\tMacro \t\t" << optimizedAction.profileIndex << ". " << endl;
      for (int i = 0; i < optimizedAction.optimizedMacroItems.size(); i++){
        auto macro = optimizedAction.optimizedMacroItems[i];
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

void debugOptimizedTrigger(const OptimizedTrigger& optimizedTrigger){
  auto name = optimizedTrigger.trigger->name;
  auto key = optimizedTrigger.trigger->key;
  auto index = optimizedTrigger.index;
  auto keyCode = optimizedTrigger.keyCode;
  cout << "\t\t" << index << ".\t" << name << "\t" << key << " (" << keyCode << ")" <<endl;
}

void debugOptimizedConfig(){
  cout << "Debug Optimized Config" << endl;
  cout << "------------------------------------------" << endl;
  for (const auto& trigger : optimizedTriggers) {
      debugOptimizedTrigger(trigger);
  }
  cout << "\tactions:\n";
  for (const auto& optimizedAction : optimizedActions) {
      debugOptimizedAction(optimizedAction);
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
