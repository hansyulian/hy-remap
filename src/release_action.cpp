#include "main.h"

void releaseOngoingAction(int keyCode){
  auto actionIndex = keyDownActionIndex[keyCode];
  if (actionIndex == -1){
    return;
  }
  auto action = &optimizedActions[actionIndex];
  keyDownActionIndex[keyCode] = -1;
  cout << "Releasing action " << action->index  << endl;
  switch(action->type){
    case ActionType::PROFILE_SHIFT:
      cout << "Releasing profile shift" << endl;
      releaseProfileShiftAction(*action);
      return;
    case ActionType::MACRO:
      cout << "Releasing macro" << endl;
      releaseMacroAction(*action);
      return;
    default:
      return;
  }
}