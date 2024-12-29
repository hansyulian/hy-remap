#include "key_remapper.h"

void startKeyboardAndMouseHook(const Config& config) {
    // Store the loaded config data globally or pass it around as needed
    profiles = config.profiles;
    triggers = config.triggers;
    actions = config.actions;

    // Set up the low-level keyboard hook
    keyboardHook = SetWindowsHookEx(WH_KEYBOARD_LL, keyboardProc, NULL, 0);
    if (keyboardHook == NULL) {
        cerr << "Failed to install keyboard hook!" << endl;
    }

    // Set up the low-level mouse hook
    mouseHook = SetWindowsHookEx(WH_MOUSE_LL, mouseProc, NULL, 0);
    if (mouseHook == NULL) {
        cerr << "Failed to install mouse hook!" << endl;
    }
}

void stopKeyboardAndMouseHook() {
    UnhookWindowsHookEx(keyboardHook);
    UnhookWindowsHookEx(mouseHook);
    keyboardHook = NULL; // It's good practice to reset the hook after cleaning up
    mouseHook = NULL;
}
