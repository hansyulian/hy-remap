#include "utils.h"

OptimizedTrigger* getTriggerByName(const string& name) {
    int index = getTriggerIndexByName(name);  // Get the index of the Trigger by name
    if (index != -1) {
        return &optimizedTriggers[index];  // Return the Trigger if found
    }
    return nullptr;  // Return nullptr if the Trigger is not found
}

int getTriggerIndexByName(const string& name){
  for (int i = 0; i < optimizedTriggers.size(); i++){
    if (optimizedTriggers[i].trigger->name == name){
      return i;
    }
  }
  return -1;
}