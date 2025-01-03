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
