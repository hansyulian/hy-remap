#include "main.h"
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

        // Create an InputTrigger to represent the key event
        InputTrigger inputTrigger;
        inputTrigger.up = isKeyUp;
        inputTrigger.keyCode = keyCode;

        // Check if the dwExtraInfo does not match the bypass flag
        if (kbd->dwExtraInfo != HY_BYPASS_EXECUTION_FLAG && handleInput(inputTrigger)) {
            // If remapping is prevented, return 1 to stop further processing
            return 1;
        }
    }

    // Call next hook in the chain for further processing of the event
    return CallNextHookEx(keyboardHook, nCode, wParam, lParam);
}
