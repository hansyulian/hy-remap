#include "key_remapper.h"

bool isActiveWindowMatchingProfile(const std::vector<std::string>& programNames) {
    HWND hwnd = GetForegroundWindow();
    if (!hwnd) return false;

    char windowTitle[256];
    GetWindowText(hwnd, windowTitle, sizeof(windowTitle));

    for (const auto& programName : programNames) {
        if (std::string(windowTitle).find(programName) != std::string::npos) {
            return true;
        }
    }
    return false;
}

LRESULT CALLBACK keyboardProc(int nCode, WPARAM wParam, LPARAM lParam) {
    if (nCode >= 0 && wParam == WM_KEYDOWN) {
        KBDLLHOOKSTRUCT* kbd = (KBDLLHOOKSTRUCT*)lParam;
        std::string keyName = std::to_string(kbd->vkCode);  // Convert keycode to string for comparison

        for (const auto& profile : profiles) {
            if (isActiveWindowMatchingProfile(profile["programNames"].get<std::vector<std::string>>())) {
                for (const auto& mapping : profile["mapping"]) {
                    if (mapping["key"] == keyName) {
                        for (const auto& action : actions) {
                            if (action["id"] == mapping["actionId"]) {
                                performAction(action);  // Perform the action
                                return 1;  // Skip the original key press
                            }
                        }
                    }
                }
            }
        }
    }
    return CallNextHookEx(keyboardHook, nCode, wParam, lParam);
}

void startKeyboardHook() {
    keyboardHook = SetWindowsHookEx(WH_KEYBOARD_LL, keyboardProc, NULL, 0);
    if (keyboardHook == NULL) {
        std::cerr << "Failed to install keyboard hook!" << std::endl;
    }
}

void stopKeyboardHook() {
    UnhookWindowsHookEx(keyboardHook);
}
