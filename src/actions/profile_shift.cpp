#include "actions.h"

void performProfileShiftAction(const OptimizedAction& action, const KeyAction& inputTrigger){
  if (inputTrigger.up){
      return;
  }
  keyDownActionIndex[inputTrigger.keyCode] = action.index;
  overrideProfileIndex = action.profileIndex;
  profileShiftButtonHold[inputTrigger.keyCode] = true;
  cout << "Profile Shift " << optimizedProfiles[action.profileIndex].profile->name << endl;
}

void releaseProfileShiftAction(const OptimizedAction& action, int keyCode){
  overrideProfileIndex = NO_PROFILE_FLAG;
  profileShiftButtonHold[keyCode] = false;
  cout << "Profile Shift release back to " << optimizedProfiles[profileCacheIndex].profile->name << endl;  
}