#include "main.h"
#include "iostream"

void performAction(const OptimizedAction& action, const KeyAction& inputTrigger) {    
    switch(action.type){
        case ActionType::SIMPLE:
            performSimpleAction(action,inputTrigger);
            break;
        case ActionType::PROFILE_SHIFT:
            performProfileShiftAction(action, inputTrigger);
            break;
        case ActionType::MACRO:
            performMacroAction(action,inputTrigger);
            break;
    }
}

