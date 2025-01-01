#include "main.h"

void releaseOngoingAction(const InputTrigger& inputTrigger){
  if (!inputTrigger.up){
    return;
  }
  auto actionIndex = keyDownActionIndex[inputTrigger.keyCode];
  if (actionIndex == -1){
    return;
  }
  auto action = &optimizedActions[actionIndex];
  // cout << "Releasing action " << action->index  << endl;
  switch(action->type){
    case ActionType::PROFILE_SHIFT:
      // cout << "Releasing profile shift" << endl;
      releaseProfileShiftAction(*action,inputTrigger);
      return;
    case ActionType::MACRO:
      // cout << "Releasing macro" << endl;
      releaseMacroAction(*action,inputTrigger);
      return;
    default:
      return;
  }
}