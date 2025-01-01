#include "main.h"

void performProfileShiftAction(const OptimizedAction& action, const InputTrigger& inputTrigger){
    if (inputTrigger.up){
        return;
    }
    keyDownActionIndex[inputTrigger.keyCode] = action.index;
    overrideProfileIndex = action.profileIndex;
}

void releaseProfileShiftAction(const OptimizedAction& action, const InputTrigger& inputTrigger){
  overrideProfileIndex = -1;
  keyDownActionIndex[inputTrigger.keyCode] = -1;
}