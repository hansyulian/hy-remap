#include "controllers.h"
#include <iostream>
#include <vector>
#include <string>

LRESULT CALLBACK keyboardProc(int nCode, WPARAM wParam, LPARAM lParam) {
    refreshProfileCache();
    if (nCode >= 0) {
        // Cast lParam to KBDLLHOOKSTRUCT to get keyboard event details
        KBDLLHOOKSTRUCT* kbd = (KBDLLHOOKSTRUCT*)lParam;
        int keyCode = static_cast<int>(kbd->vkCode);
        bool isKeyUp = false;

        // Determine whether the key is being pressed or released
        if (wParam == WM_KEYDOWN || wParam == WM_SYSKEYDOWN) {
            isKeyUp = false;  // Key is being pressed
        } else if (wParam == WM_KEYUP || wParam == WM_SYSKEYUP) {
            isKeyUp = true;  // Key is being released
        }

        // Create an KeyAction to represent the key event
        KeyAction inputTrigger;
        inputTrigger.up = isKeyUp;
        inputTrigger.keyCode = keyCode;

        // cout << "dwExtraInfo kbd " << inputTrigger.keyCode << " " << kbd->dwExtraInfo << endl;
        // skip macro shift spamming state
        if (keyCode > NO_KEYCODE_FLAG && profileShiftButtonHold[keyCode] && !isKeyUp){
            return 1;
        }
        // Check if the dwExtraInfo does not match the bypass flag
        if (kbd->dwExtraInfo != HY_BYPASS_EXECUTION_FLAG && processInputRemapping(inputTrigger)) {
            // If remapping is prevented, return 1 to stop further processing
            return 1;
        }
    }

    // Call next hook in the chain for further processing of the event
    return CallNextHookEx(keyboardHook, nCode, wParam, lParam);
}
