#include "main.h"
int getActiveProfileIndex() {
    if (overrideProfileIndex != -1) {
        return overrideProfileIndex; // Return override if set
    }

    HWND hwnd = GetForegroundWindow();
    if (!hwnd) {
        // If no active window detected, return the default profile
        return defaultProfileIndex;
    }

    // Get the window title
    wchar_t windowTitleW[256]; // Wide-character buffer
    if (GetWindowTextW(hwnd, windowTitleW, sizeof(windowTitleW) / sizeof(wchar_t)) == 0) {
        // If unable to retrieve the window title, return the default profile
        return defaultProfileIndex;
    }

    // Convert wide string to standard string
    std::wstring wideTitle(windowTitleW);
    std::string windowTitleString(wideTitle.begin(), wideTitle.end());

    // Check cache for a match
    if (profileCacheIndex != -1 && windowTitleString == profileCacheWindowName) {
        return profileCacheIndex;
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
