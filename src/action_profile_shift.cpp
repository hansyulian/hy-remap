#include "main.h"

void performProfileShiftAction(const OptimizedAction& action, const InputTrigger& inputTrigger){
    if (inputTrigger.up){
        return;
    }
    keyDownActionIndex[inputTrigger.keyCode] = action.index;
    overrideProfileIndex = action.profileIndex;
}

void releaseProfileShiftAction(const OptimizedAction& action){
  overrideProfileIndex = -1;
  
}