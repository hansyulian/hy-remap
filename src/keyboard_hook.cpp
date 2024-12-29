#include "key_remapper.h"
#include <iostream>
#include <vector>
#include <string>

LRESULT CALLBACK keyboardProc(int nCode, WPARAM wParam, LPARAM lParam) {
    if (nCode >= 0) {
        KBDLLHOOKSTRUCT* kbd = (KBDLLHOOKSTRUCT*)lParam;
        KeyCode keyCode = static_cast<KeyCode>(kbd->vkCode);
        bool isKeyUp = false;

        // Determine whether the key is being pressed or released
        if (wParam == WM_KEYDOWN || wParam == WM_SYSKEYDOWN) {
            isKeyUp = false;  // Key is being pressed
        } else if (wParam == WM_KEYUP || wParam == WM_SYSKEYUP) {
            isKeyUp = true;  // Key is being released
        }

        // Debug message to indicate key event
        std::cout << "Key Event: " 
                  << (isKeyUp ? "Released" : "Pressed") 
                  << " KeyCode: " << keyCode 
                  << std::endl;

        // Get the active profile
        Profile activeProfile = getProfile();

        // Check if a valid profile is found
        if (!activeProfile.name.empty()) {
            std::cout << "Matching profile: " << activeProfile.name << std::endl;

            // Iterate through the profile's mappings
            for (const auto& mapping : activeProfile.mapping) {
                if (mapping.triggerId == std::to_string(keyCode)) {
                    std::cout << "Trigger: " << mapping.triggerId
                              << " Action ID: " << mapping.actionId << std::endl;

                    // Perform the mapped action if found
                    for (const auto& action : actions) {
                        if (action.id == mapping.actionId) {
                            performAction(action);  // Perform the mapped action
                            return 1;  // Skip the original key press
                        }
                    }
                }
            }
        }
    }

    return CallNextHookEx(keyboardHook, nCode, wParam, lParam);
}
