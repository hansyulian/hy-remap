#include "modules.h"
#include <windows.h>

LRESULT CALLBACK mouseProc(int nCode, WPARAM wParam, LPARAM lParam) {
    refreshProfileCache();
    if (nCode >= 0) {
        MSLLHOOKSTRUCT* mouse = (MSLLHOOKSTRUCT*)lParam;

        int keyCode = NO_KEYCODE_FLAG; // Default to invalid value
        bool isKeyUp = false;

        // Determine the mouse button and whether it's an "up" or "down" event
        switch (wParam) {
            case WM_LBUTTONDOWN:
                keyCode = getKeyCodeFromString("LEFT_CLICK");
                isKeyUp = false;
                break;
            case WM_LBUTTONUP:
                keyCode = getKeyCodeFromString("LEFT_CLICK");
                isKeyUp = true;
                break;
            case WM_RBUTTONDOWN:
                keyCode = getKeyCodeFromString("RIGHT_CLICK");
                isKeyUp = false;
                break;
            case WM_RBUTTONUP:
                keyCode = getKeyCodeFromString("RIGHT_CLICK");
                isKeyUp = true;
                break;
            case WM_MBUTTONDOWN:
                keyCode = getKeyCodeFromString("MIDDLE_CLICK");
                isKeyUp = false;
                break;
            case WM_MBUTTONUP:
                keyCode = getKeyCodeFromString("MIDDLE_CLICK");
                isKeyUp = true;
                break;
            case WM_XBUTTONDOWN:
                // Handle extra buttons like "Back" and "Forward" buttons on mice
                keyCode = (GET_XBUTTON_WPARAM(mouse->mouseData) == XBUTTON1) ? getKeyCodeFromString("MBACK") : getKeyCodeFromString("MFORWARD");
                isKeyUp = false;
                break;
            case WM_XBUTTONUP:
                keyCode = (GET_XBUTTON_WPARAM(mouse->mouseData) == XBUTTON1) ? getKeyCodeFromString("MBACK") : getKeyCodeFromString("MFORWARD");
                isKeyUp = true;
                break;
            case WM_MOUSEWHEEL: {
                // Handle mouse wheel scrolling
                int delta = GET_WHEEL_DELTA_WPARAM(mouse->mouseData);
                keyCode = (delta > 0) ? getKeyCodeFromString("WHEEL_UP") : getKeyCodeFromString("WHEEL_DOWN");
                isKeyUp = false;  // Treat scrolling as a "press-like" event
                break;
            }
            default:
                // No relevant mouse action detected
                keyCode = NO_KEYCODE_FLAG;  // Invalid key
                isKeyUp = false;
                break;
        }

        // Create an KeyAction object to hold the current event
        KeyAction inputTrigger;
        inputTrigger.up = isKeyUp;
        inputTrigger.keyCode = keyCode;
        
        if (keyCode > NO_KEYCODE_FLAG && profileShiftButtonHold[keyCode] && !isKeyUp){
            return 1;
        }
        // if (keyCode > NO_KEYCODE_FLAG){
        // cout << "dwExtraInfo mouse " << inputTrigger.keyCode << " " << mouse->dwExtraInfo << endl;
        // }
        // Check if the dwExtraInfo doesn't contain the flag and the key code is valid
        if (mouse->dwExtraInfo != HY_BYPASS_EXECUTION_FLAG && inputTrigger.keyCode != NO_KEYCODE_FLAG && processInputRemapping(inputTrigger)) {
            return 1; // Return 1 to prevent further processing of the event
        }
    }

    // Pass the event to the next hook in the chain
    return CallNextHookEx(mouseHook, nCode, wParam, lParam);
}
