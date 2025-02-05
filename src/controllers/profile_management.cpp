#include "controllers.h"

int getActiveProfileIndex() {
    // cout << "get active profile index" << endl;
    if (overrideProfileIndex > NO_PROFILE_FLAG) {
        return overrideProfileIndex; // Return override if set
    }
    // cout << "window title " << windowTitleString << endl;
    // Check cache for a match
    if (profileCacheIndex > NO_PROFILE_FLAG) {
        return profileCacheIndex;
    }

    // Return default profile index if no match found
    return defaultProfileIndex;
}

void refreshProfileCache(){
  auto currentWindowInfo = getCurrentWindowInfo();
  if (profileCacheIndex != NO_PROFILE_FLAG && windowInfoCache.processId == currentWindowInfo.processId){
    return;
  }
  for (int i = 0; i < 256; i++){
      releaseOngoingAction(i, true);
  }
  
  // Iterate over profiles to find a match
  profileCacheIndex = defaultProfileIndex;
  windowInfoCache = currentWindowInfo;
  for (const auto& optimizedProfile : optimizedProfiles) {
      auto programNames = optimizedProfile.lowerCaseProgramNames;
      for (const auto& programName : programNames) {
            // cout << "debug profile: "<< programName << " | " << currentWindowInfo.executable << " | " << currentWindowInfo.name << endl;
          if (currentWindowInfo.executable.find(programName) != std::string::npos
            || currentWindowInfo.name.find(programName) != std::string::npos) {
              // Cache the matching profile index and window title
              profileCacheIndex = optimizedProfile.index;
              cout << "Profile Change " << optimizedProfile.profile->name << " for window title: '" << windowInfoCache.name << "' matching: " << programName <<  endl;
              return;
          }
      }
  }
  cout << "Profile Default " << endl;
}