#include "main.h"


OptimizedProfile* getActiveProfile() {
    if (overrideProfileIndex != -1){
        return &optimizedProfiles[overrideProfileIndex];
    }
    HWND hwnd = GetForegroundWindow();
    if (!hwnd){
        // if no active window detected, return the default profile
        return &optimizedProfiles[defaultProfileIndex];
    }
    // put the window title
    wchar_t windowTitleW[256]; // Wide-character buffer
    GetWindowTextW(hwnd, windowTitleW, sizeof(windowTitleW) / sizeof(wchar_t));

    // Convert wide string to standard string
    wstring wideTitle(windowTitleW);
    string windowTitleString(wideTitle.begin(), wideTitle.end());

    if (profileCacheIndex != -1 && windowTitleString == profileCacheWindowName){
        return &optimizedProfiles[profileCacheIndex];
    } else {
        profileCacheIndex = -1;
    }
    for (int i = 0; i < optimizedProfiles.size(); i++){
        OptimizedProfile* profile = &optimizedProfiles[i];
        
        for (const auto& programName : profile->programNames) {
            if (windowTitleString.find(programName) != string::npos) {
                profileCacheIndex = profile->index;
                profileCacheWindowName = windowTitleString;
                return profile;
            }
        }
    }
    return &optimizedProfiles[defaultProfileIndex];  // Return a pointer to the default profile
}