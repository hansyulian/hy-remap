#include "actions.h"

void performRunProgram(const OptimizedAction& action, const KeyAction& inputTrigger) {
    if (inputTrigger.up){
        return;
    }
    runProgram(action.programPath);
}