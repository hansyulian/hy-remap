#include "main.h"
#include <chrono>

bool handleInput(const KeyAction& inputTrigger){
    if (inputTrigger.up){
        releaseOngoingAction(inputTrigger.keyCode, false);     
    }   
    auto keyCode = inputTrigger.keyCode;
    auto up = inputTrigger.up;
    auto profileIndex = getActiveProfileIndex(); // profile is guaranteed to exist, at least the default profile
    if (profileIndex == -1){
        return false;
    }
    
    auto actionIndex = optimizedProfiles[profileIndex].actionIdMap[keyCode];
    if (actionIndex == -1){
        return false;
    }
    const OptimizedAction action = optimizedActions[actionIndex];
    
    performAction(action, inputTrigger);
    return true;
}