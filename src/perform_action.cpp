#include "main.h"
#include "iostream"

void performAction(const OptimizedAction& action, const InputTrigger& inputTrigger) {    
    switch(action.type){
        case ActionType::SIMPLE:
            performSimpleAction(action,inputTrigger);
            break;
        case ActionType::PROFILE_SHIFT:
            performProfileShiftAction(action, inputTrigger);
            break;
    }
}

