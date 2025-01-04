#include "utils.h"

OptimizedAction* getActionByName(const string& name) {
    int index = getActionIndexByName(name);  // Get the index of the action by name
    if (index != -1) {
        return &optimizedActions[index];  // Return the action if found
    }
    return nullptr;  // Return nullptr if the action is not found
}

int getActionIndexByName(const string& name){
  for (int i = 0; i < optimizedActions.size(); i++){
    if (optimizedActions[i].action->name == name){
      return i;
    }
  }
  return -1;
}