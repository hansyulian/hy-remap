#include "main.h"

bool handleInput(const InputTrigger& inputTrigger){
    
    auto keyCode = inputTrigger.keyCode;
    auto isUp = inputTrigger.isUp;
    auto profile = getProfile(); // profile is guaranteed to exist, at least the default profile
    

    const Trigger* currentTrigger = nullptr;
    for (const auto& trigger : config.triggers) {
        if (getKeyCodeFromString(trigger.key) == keyCode) {
            currentTrigger = &trigger;
            break;
        }
    }

    if (currentTrigger == nullptr) {
        
        return false;
    }
    

    const Mapping* currentMapping = nullptr;
    for (const auto& mapping : profile->mapping) {
        if (mapping.triggerId == currentTrigger->id) {
            currentMapping = &mapping;
            break;
        }
    }

    if (currentMapping == nullptr) {
        
        return false;
    }

    
    
    const Action* currentAction = nullptr;
    for (const auto& action: config.actions){
        if (action.id == currentMapping->actionId){
            currentAction = &action;
            break;
        }
    }
    if (currentAction == nullptr){
        
        return false;
    }
    performAction(*currentAction, inputTrigger);
    return true;
}