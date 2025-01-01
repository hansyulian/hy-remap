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
  auto currentWindowTitle = getCurrentWindowTitle();
  if (profileCacheIndex != -1 && profileCacheWindowTitle == currentWindowTitle){
    return;
  }
  for (int i = 0; i < 256; i++){
      releaseOngoingAction(i, true);
  }
  
  // Iterate over profiles to find a match
  profileCacheIndex = -1;
  for (const auto& profile : optimizedProfiles) {
      if (!profile.programNames) {
          continue; // Skip profiles with null programNames
      }
      auto programNames = profile.programNames;
      for (const auto& programName : *programNames) {
          if (currentWindowTitle.find(programName) != std::string::npos) {
              // Cache the matching profile index and window title
              profileCacheIndex = profile.index;
              profileCacheWindowTitle = currentWindowTitle;
              return;
          }
      }
  }
}