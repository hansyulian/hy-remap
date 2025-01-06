#include "actions.h"

void performRunProgramAction(const OptimizedAction& optimizedAction, const KeyAction& inputTrigger) {
    if (inputTrigger.up){
        return;
    }
    runProgram(optimizedAction.action->runProgram.path);
}