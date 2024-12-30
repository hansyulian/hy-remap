#include "main.h"
#include <iostream>
#include <vector>
#include <string>

LRESULT CALLBACK keyboardProc(int nCode, WPARAM wParam, LPARAM lParam) {
    if (nCode >= 0) {
        KBDLLHOOKSTRUCT* kbd = (KBDLLHOOKSTRUCT*)lParam;
        int keyCode = static_cast<int>(kbd->vkCode);
        bool isKeyUp = false;

        // Determine whether the key is being pressed or released
        if (wParam == WM_KEYDOWN || wParam == WM_SYSKEYDOWN) {
            isKeyUp = false;  // Key is being pressed
        } else if (wParam == WM_KEYUP || wParam == WM_SYSKEYUP) {
            isKeyUp = true;  // Key is being released
        }

        InputTrigger inputTrigger;
        inputTrigger.isUp = isKeyUp;
        inputTrigger.keyCode = keyCode;
        // Get the active profile

        if (handleInput(inputTrigger)){
            return 1;
        }

    }

    return CallNextHookEx(keyboardHook, nCode, wParam, lParam);
}
