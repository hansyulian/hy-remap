#include "controllers.h"
#include <chrono>

bool processInputRemapping(const KeyAction& inputTrigger){
    if (inputTrigger.up){
        releaseOngoingAction(inputTrigger.keyCode, false);     
    }   
    auto keyCode = inputTrigger.keyCode;
    auto up = inputTrigger.up;
    auto profileIndex = getActiveProfileIndex(); // profile is guaranteed to exist, at least the default profile
    if (profileIndex <= NO_PROFILE_FLAG){
        return false;
    }
    
    auto actionIndex = optimizedProfiles[profileIndex].actionIdMap[keyCode];
    if (actionIndex == TERMINATE_ACTION_FLAG){
        return true;
    }
    if (actionIndex <= NO_ACTION_FLAG){
        return false;
    }
    const OptimizedAction action = optimizedActions[actionIndex];
    
    performAction(action, inputTrigger);
    return true;
}