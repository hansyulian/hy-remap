#include <iostream>
#include <windows.h>
#include <fstream>
#include <string>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

HHOOK keyboardHook;
std::vector<json> actions;  // To store actions loaded from JSON
std::vector<json> profiles;  // To store profiles loaded from JSON

// Function to check if the active window matches a program name in the profile
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

// Function to simulate the action defined in the JSON
void performAction(const json& action) {
    if (action["type"] == "simple") {
        if (action["ctrl"].get<bool>()) {
            keybd_event(VK_CONTROL, 0, 0, 0);  // Ctrl key down
        }
        if (action["alt"].get<bool>()) {
            keybd_event(VK_MENU, 0, 0, 0);  // Alt key down
        }
        if (action["shift"].get<bool>()) {
            keybd_event(VK_SHIFT, 0, 0, 0);  // Shift key down
        }
        if (action["win"].get<bool>()) {
            keybd_event(VK_LWIN, 0, 0, 0);  // Win key down
        }

        // Send the action's key press (e.g., 'C' for copy)
        UINT key = VkKeyScan(action["key"].get<std::string>()[0]);
        keybd_event(key, 0, 0, 0);  // Key down
        keybd_event(key, 0, KEYEVENTF_KEYUP, 0);  // Key up

        // Release modifier keys after action
        if (action["ctrl"].get<bool>()) {
            keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);  // Ctrl key up
        }
        if (action["alt"].get<bool>()) {
            keybd_event(VK_MENU, 0, KEYEVENTF_KEYUP, 0);  // Alt key up
        }
        if (action["shift"].get<bool>()) {
            keybd_event(VK_SHIFT, 0, KEYEVENTF_KEYUP, 0);  // Shift key up
        }
        if (action["win"].get<bool>()) {
            keybd_event(VK_LWIN, 0, KEYEVENTF_KEYUP, 0);  // Win key up
        }
    }
}

// Function to process keyboard input and perform the appropriate action
LRESULT CALLBACK keyboardProc(int nCode, WPARAM wParam, LPARAM lParam) {
    if (nCode >= 0 && wParam == WM_KEYDOWN) {
        KBDLLHOOKSTRUCT* kbd = (KBDLLHOOKSTRUCT*)lParam;
        std::string keyName = std::to_string(kbd->vkCode);  // Convert keycode to string for comparison

        // Iterate over all profiles to find active ones
        for (const auto& profile : profiles) {
            // If the active window matches the profile's program names
            if (isActiveWindowMatchingProfile(profile["programNames"].get<std::vector<std::string>>())) {
                // Look through the key mappings for this profile
                for (const auto& mapping : profile["mapping"]) {
                    if (mapping["key"] == keyName) {
                        // Find the action associated with this mapping
                        for (const auto& action : actions) {
                            if (action["id"] == mapping["actionId"]) {
                                performAction(action);  // Perform the action (e.g., Ctrl+C)
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

// Function to load the JSON configuration
void loadConfiguration(const std::string& configFilePath) {
   // Print the file path to the console
    std::cout << "Attempting to open configuration file: " << configFilePath << std::endl;

    std::ifstream file(configFilePath);
    if (!file.is_open()) {
        std::cerr << "Failed to open configuration file: " << configFilePath << std::endl;
        return;
    }

    json config;
    file >> config;
    actions = config["actions"].get<std::vector<json>>();  // Store actions from the config
    profiles = config["profiles"].get<std::vector<json>>();  // Store profiles from the config

}

// Function to start listening to keyboard events
void startKeyboardHook() {
    keyboardHook = SetWindowsHookEx(WH_KEYBOARD_LL, keyboardProc, NULL, 0);
    if (keyboardHook == NULL) {
        std::cerr << "Failed to install keyboard hook!" << std::endl;
    }
}

// Function to stop the keyboard hook
void stopKeyboardHook() {
    UnhookWindowsHookEx(keyboardHook);
}

int main() {
    // Load configuration from a JSON file (provide the path to your config file)
    loadConfiguration("./config.json");

    std::cout << "Key remapper is running..." << std::endl;

    // Start listening for keyboard input
    startKeyboardHook();

    // Run the message loop to keep the program alive and handling keyboard events
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0) > 0) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    // Clean up before exit
    stopKeyboardHook();
    return 0;
}