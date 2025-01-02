#include "main.h"

int getActiveProfileIndex() {
    // cout << "get active profile index" << endl;
    if (overrideProfileIndex != -1) {
        return overrideProfileIndex; // Return override if set
    }
    // cout << "window title " << windowTitleString << endl;
    // Check cache for a match
    if (profileCacheIndex != -1) {
        return profileCacheIndex;
    }

    // Return default profile index if no match found
    return defaultProfileIndex;
}

void refreshProfileCache(){
  auto currentWindowInfo = getCurrentWindowInfo();
  if (profileCacheIndex != -1 && currentWindowInfo.processId == currentWindowInfo.processId){
    return;
  }
  for (int i = 0; i < 256; i++){
      releaseOngoingAction(i, true);
  }
  
  // Iterate over profiles to find a match
  profileCacheIndex = defaultProfileIndex;
  windowInfoCache = currentWindowInfo;
  for (const auto& profile : optimizedProfiles) {
      if (!profile.programNames) {
          continue; // Skip profiles with null programNames
      }
      auto programNames = profile.programNames;
      for (const auto& programName : *programNames) {
          if (programName == currentWindowInfo.executable
            || currentWindowInfo.name.find(programName) != std::string::npos) {
              // Cache the matching profile index and window title
              profileCacheIndex = profile.index;
              cout << "Profile Change " << profile.name << " for window title: '" << windowInfoCache.name << "'" << endl;
              return;
          }
      }
  }
}