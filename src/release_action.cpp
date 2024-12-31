#include "main.h"


void releaseOngoingAction(const InputTrigger& inputTrigger){
  if (!inputTrigger.isUp){
    return;
  }
  auto keyDownActionId = keyDownActionIndex[inputTrigger.keyCode];
  if (keyDownActionId == -1){
    return;
  }
  auto action = &optimizedActions[keyDownActionId];
  switch(action->type){
    case ActionType::PROFILE_SHIFT:
      releaseProfileShiftAction(*action,inputTrigger);
      return;
    default:
      return;
  }
}