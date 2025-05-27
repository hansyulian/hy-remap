#include "controllers.h"

void startKeyboardAndMouseHook() {

    // Set up the low-level keyboard hook
    keyboardHook = SetWindowsHookEx(WH_KEYBOARD_LL, keyboardProc, NULL, 0);
    if (keyboardHook == NULL) {
        cerr << "Failed to install keyboard hook!" << endl;
    }

    // Set up the low-level mouse hook
    mouseHook = SetWindowsHookEx(WH_MOUSE_LL, mouseProc, NULL, 0);
    if (mouseHook == NULL) {
        cerr << "Failed to install mouse hook!" << endl;
        if (keyboardHook != NULL) {
            UnhookWindowsHookEx(keyboardHook);
            keyboardHook = NULL;
        }
    }
}

void stopKeyboardAndMouseHook() {
    if (keyboardHook != NULL) {
        UnhookWindowsHookEx(keyboardHook);
        keyboardHook = NULL; // It's good practice to reset the hook after cleaning up
    }
    if (mouseHook != NULL) {
        UnhookWindowsHookEx(mouseHook);
        mouseHook = NULL;
    }
}
