#include "key_remapper.h"
// New function to get the active profile
bool isActiveWindowMatchingProfile(const vector<string>& programNames) {
    HWND hwnd = GetForegroundWindow();
    if (!hwnd) return false;

    char windowTitle[256];
    GetWindowText(hwnd, windowTitle, sizeof(windowTitle));

    for (const auto& programName : programNames) {
        if (string(windowTitle).find(programName) != string::npos) {
            return true;
        }
    }
    return false;
}

Profile getProfile() {
    for (const auto& profile : profiles) {
        if (isActiveWindowMatchingProfile(profile.programNames)) {
            return profile;  // Return the first matching profile
        }
    }
    return Profile();  // Return a default empty profile if none matched
}
