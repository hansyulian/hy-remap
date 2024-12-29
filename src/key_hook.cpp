#include "key_remapper.h"
#include <iostream>
#include <vector>

std::vector<Profile> g_profiles;
std::vector<Trigger> g_triggers;
std::vector<Action> g_actions;

// Define the keyboardHook variable here
HHOOK keyboardHook = NULL;  // Define the keyboardHook variable (this is where memory is allocated)
HHOOK mouseHook = NULL;     // Define the mouseHook variable

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
        std::cout << "Key Name " << keyName << std::endl;
        for (const auto& profile : g_profiles) {
            if (isActiveWindowMatchingProfile(profile.programNames)) {
                std::cout << "Matching profile: " << profile.name << std::endl;
                for (const auto& mapping : profile.mapping) {
                    if (mapping.triggerId == keyName) {
                        std::cout << "Trigger: " << mapping.triggerId << " Action ID: " << mapping.actionId << std::endl;
                        for (const auto& action : g_actions) {
                            if (action.id == mapping.actionId) {
                                performAction(action);  // Perform the mapped action
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

LRESULT CALLBACK mouseProc(int nCode, WPARAM wParam, LPARAM lParam) {
    if (nCode >= 0) {
        MSLLHOOKSTRUCT* mouse = (MSLLHOOKSTRUCT*)lParam;

        // Handle mouse clicks
        if (wParam == WM_LBUTTONDOWN || wParam == WM_LBUTTONUP) {
            std::cout << "Left Mouse Button: " << (wParam == WM_LBUTTONDOWN ? "Pressed" : "Released") 
                      << " at (" << mouse->pt.x << ", " << mouse->pt.y << ")" << std::endl;
            for (const auto& profile : g_profiles) {
                if (isActiveWindowMatchingProfile(profile.programNames)) {
                    // You can map Left Click to an action here
                }
            }
        }

        if (wParam == WM_RBUTTONDOWN || wParam == WM_RBUTTONUP) {
            std::cout << "Right Mouse Button: " << (wParam == WM_RBUTTONDOWN ? "Pressed" : "Released") 
                      << " at (" << mouse->pt.x << ", " << mouse->pt.y << ")" << std::endl;
            for (const auto& profile : g_profiles) {
                if (isActiveWindowMatchingProfile(profile.programNames)) {
                    // You can map Right Click to an action here
                }
            }
        }

        if (wParam == WM_MBUTTONDOWN || wParam == WM_MBUTTONUP) {
            std::cout << "Middle Mouse Button: " << (wParam == WM_MBUTTONDOWN ? "Pressed" : "Released") 
                      << " at (" << mouse->pt.x << ", " << mouse->pt.y << ")" << std::endl;
            for (const auto& profile : g_profiles) {
                if (isActiveWindowMatchingProfile(profile.programNames)) {
                    // You can map Middle Click to an action here
                }
            }
        }

        // Handle mouse scroll (wheel up/down)
        if (wParam == WM_MOUSEWHEEL) {
            int delta = GET_WHEEL_DELTA_WPARAM(wParam);  // Get the scroll amount
            std::cout << "Mouse Wheel: " << (delta > 0 ? "Up" : "Down") << " at (" 
                      << mouse->pt.x << ", " << mouse->pt.y << ")" << std::endl;
            for (const auto& profile : g_profiles) {
                if (isActiveWindowMatchingProfile(profile.programNames)) {
                    // You can map Mouse Wheel to an action here
                }
            }
        }

        // Handle extra mouse buttons (XButton1, XButton2)
        if (wParam == WM_XBUTTONDOWN || wParam == WM_XBUTTONUP) {
            int button = GET_XBUTTON_WPARAM(wParam);
            std::cout << "Extra Mouse Button: " << (button == XBUTTON1 ? "XButton1" : "XButton2") 
                      << (wParam == WM_XBUTTONDOWN ? " Pressed" : " Released") 
                      << " at (" << mouse->pt.x << ", " << mouse->pt.y << ")" << std::endl;
            for (const auto& profile : g_profiles) {
                if (isActiveWindowMatchingProfile(profile.programNames)) {
                    // You can map Extra Mouse Buttons (XButton1, XButton2) to an action here
                }
            }
        }
    }
    return CallNextHookEx(mouseHook, nCode, wParam, lParam);
}

void startKeyboardAndMouseHook(const Config& config) {
    // Store the loaded config data globally or pass it around as needed
    g_profiles = config.profiles;
    g_triggers = config.triggers;
    g_actions = config.actions;

    // Set up the low-level keyboard hook
    keyboardHook = SetWindowsHookEx(WH_KEYBOARD_LL, keyboardProc, NULL, 0);
    if (keyboardHook == NULL) {
        std::cerr << "Failed to install keyboard hook!" << std::endl;
    }

    // Set up the low-level mouse hook
    mouseHook = SetWindowsHookEx(WH_MOUSE_LL, mouseProc, NULL, 0);
    if (mouseHook == NULL) {
        std::cerr << "Failed to install mouse hook!" << std::endl;
    }
}

void stopKeyboardAndMouseHook() {
    UnhookWindowsHookEx(keyboardHook);
    UnhookWindowsHookEx(mouseHook);
    keyboardHook = NULL; // It's good practice to reset the hook after cleaning up
    mouseHook = NULL;
}
