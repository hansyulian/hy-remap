#include "main.h"

void releaseOngoingAction(int keyCode, bool force){
  // cout << "Release action force" << force << endl;
  auto actionIndex = keyDownActionIndex[keyCode];
  if (actionIndex == -1){
    return;
  }
  // cout << "Action index " << keyCode <<" | keyCode" <<actionIndex << endl;
  auto action = &optimizedActions[actionIndex];
  // cout << "negating key down index "<< keyCode << ":"<<keyDownActionIndex[keyCode] << endl;
  keyDownActionIndex[keyCode] = -1;
  // cout << "releasing " << keyCode << " " <<keyDownActionIndex[keyCode] << endl;
  // cout << "Releasing action " << actionIndex <<  " " << action->name << " " << force << endl;
  switch(action->type){
    case ActionType::SIMPLE:
      releaseSimpleAction(*action);
      return;
    case ActionType::PROFILE_SHIFT:
      // cout << "Releasing profile shift" << endl;
      releaseProfileShiftAction(*action, keyCode);
      return;
    case ActionType::MACRO:
      // cout << "Releasing macro" << endl;
      releaseMacroAction(*action, force);
      return;
    default:
      return;
  }
}