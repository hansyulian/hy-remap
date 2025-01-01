#include "main.h"

int getActiveProfileIndex() {
    cout << "get active profile index" << endl;
    if (overrideProfileIndex != -1) {
        return overrideProfileIndex; // Return override if set
    }
    auto windowTitleString = getCurrentWindowTitle();
    if (windowTitleString == ""){
        return defaultProfileIndex;
    }
    cout << "window title " << windowTitleString << endl;
    // Check cache for a match
    if (profileCacheIndex != -1 && windowTitleString == profileCacheWindowName) {
        return profileCacheIndex;
    }

    for (int i = 0; i < 256; i++){
        releaseOngoingAction(i);
    }
    // Reset cache if no match
    profileCacheIndex = -1;

    // Iterate over profiles to find a match
    for (const auto& profile : optimizedProfiles) {
        if (!profile.programNames) {
            continue; // Skip profiles with null programNames
        }
        auto programNames = profile.programNames;
        for (const auto& programName : *programNames) {
            if (windowTitleString.find(programName) != std::string::npos) {
                // Cache the matching profile index and window title
                profileCacheIndex = profile.index;
                profileCacheWindowName = windowTitleString;
                return profile.index;
            }
        }
    }

    // Return default profile index if no match found
    return defaultProfileIndex;
}
