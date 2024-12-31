#include "main.h"


void releaseProfileShiftAction(const OptimizedAction& action, const InputTrigger& inputTrigger){
  overrideProfileIndex = -1;
  keyDownActionIndex[inputTrigger.keyCode] = -1;
  cout << "profile shift released " << action.profileName << endl;
}
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