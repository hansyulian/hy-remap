#include "main.h"
#include <windows.h>

LRESULT CALLBACK mouseProc(int nCode, WPARAM wParam, LPARAM lParam) {
    refreshProfileCache();
    if (nCode >= 0) {
        MSLLHOOKSTRUCT* mouse = (MSLLHOOKSTRUCT*)lParam;

        int mouseButton = -1; // Default to invalid value
        bool isKeyUp = false;

        // Determine the mouse button and whether it's an "up" or "down" event
        switch (wParam) {
            case WM_LBUTTONDOWN:
                mouseButton = getKeyCodeFromString("LEFT_CLICK");
                isKeyUp = false;
                break;
            case WM_LBUTTONUP:
                mouseButton = getKeyCodeFromString("LEFT_CLICK");
                isKeyUp = true;
                break;
            case WM_RBUTTONDOWN:
                mouseButton = getKeyCodeFromString("RIGHT_CLICK");
                isKeyUp = false;
                break;
            case WM_RBUTTONUP:
                mouseButton = getKeyCodeFromString("RIGHT_CLICK");
                isKeyUp = true;
                break;
            case WM_MBUTTONDOWN:
                mouseButton = getKeyCodeFromString("MIDDLE_CLICK");
                isKeyUp = false;
                break;
            case WM_MBUTTONUP:
                mouseButton = getKeyCodeFromString("MIDDLE_CLICK");
                isKeyUp = true;
                break;
            case WM_XBUTTONDOWN:
                // Handle extra buttons like "Back" and "Forward" buttons on mice
                mouseButton = (GET_XBUTTON_WPARAM(mouse->mouseData) == XBUTTON1) ? getKeyCodeFromString("MBACK") : getKeyCodeFromString("MFORWARD");
                isKeyUp = false;
                break;
            case WM_XBUTTONUP:
                mouseButton = (GET_XBUTTON_WPARAM(mouse->mouseData) == XBUTTON1) ? getKeyCodeFromString("MBACK") : getKeyCodeFromString("MFORWARD");
                isKeyUp = true;
                break;
            case WM_MOUSEWHEEL: {
                // Handle mouse wheel scrolling
                int delta = GET_WHEEL_DELTA_WPARAM(mouse->mouseData);
                mouseButton = (delta > 0) ? getKeyCodeFromString("WHEEL_UP") : getKeyCodeFromString("WHEEL_DOWN");
                isKeyUp = false;  // Treat scrolling as a "press-like" event
                break;
            }
            default:
                // No relevant mouse action detected
                mouseButton = -1;  // Invalid key
                isKeyUp = false;
                break;
        }

        // Create an InputTrigger object to hold the current event
        InputTrigger inputTrigger;
        inputTrigger.up = isKeyUp;
        inputTrigger.keyCode = mouseButton;

        // Check if the dwExtraInfo doesn't contain the flag and the key code is valid
        if (mouse->dwExtraInfo != HY_BYPASS_EXECUTION_FLAG && inputTrigger.keyCode != -1 && handleInput(inputTrigger)) {
            return 1; // Return 1 to prevent further processing of the event
        }
    }

    // Pass the event to the next hook in the chain
    return CallNextHookEx(mouseHook, nCode, wParam, lParam);
}
