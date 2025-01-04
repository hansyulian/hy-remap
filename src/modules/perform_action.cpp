#include "modules.h"
#include "iostream"
#include "../actions/actions.h"

void performAction(const OptimizedAction& action, const KeyAction& inputTrigger) {    
    switch(action.type){
        case ActionType::SIMPLE:
            performSimpleAction(action,inputTrigger);
            break;
        case ActionType::PROFILE_SHIFT:
            performProfileShiftAction(action, inputTrigger);
            break;
        case ActionType::MACRO:
            performMacroAction(action, inputTrigger);
            break;
        case ActionType::RUN_PROGRAM:
            performRunProgram(action, inputTrigger);
            break;
    }
}

