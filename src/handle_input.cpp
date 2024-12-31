#include "main.h"

bool handleInput(const InputTrigger& inputTrigger){
    releaseOngoingAction(inputTrigger);    
    auto keyCode = inputTrigger.keyCode;
    auto isUp = inputTrigger.isUp;
    auto profile = getActiveProfile(); // profile is guaranteed to exist, at least the default profile
    if (profile == nullptr){
        return false;
    }
    
    auto actionIndex = profile->actionIdMap[keyCode];
    if (actionIndex == -1){
        return false;
    }
    const OptimizedAction* currentAction = &optimizedActions[actionIndex];
    
    if (currentAction == nullptr){        
        return false;
    }
    performAction(*currentAction, inputTrigger);
    return true;
}