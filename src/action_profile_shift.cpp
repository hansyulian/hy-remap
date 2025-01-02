#include "main.h"

void performProfileShiftAction(const OptimizedAction& action, const InputTrigger& inputTrigger){
  if (inputTrigger.up){
      return;
  }
  keyDownActionIndex[inputTrigger.keyCode] = action.index;
  overrideProfileIndex = action.profileIndex;
  cout << "Profile Shift " << optimizedProfiles[action.profileIndex].name << endl;
}

void releaseProfileShiftAction(const OptimizedAction& action){
  overrideProfileIndex = -1;
  cout << "Profile Shift release back to " << optimizedProfiles[profileCacheIndex].name << endl;  
}