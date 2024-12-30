#include "main.h"
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

Profile* getProfile() {
    for (int i = 0; i < config.profiles.size(); i++){
        Profile* profile = &config.profiles[i];
        if (isActiveWindowMatchingProfile(profile->programNames)) {
            return profile;  // Return a pointer to the first matching profile
        }
    }
    return defaultProfile;  // Return a pointer to the default profile
}