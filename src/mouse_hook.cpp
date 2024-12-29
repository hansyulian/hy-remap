#include "key_remapper.h"

LRESULT CALLBACK mouseProc(int nCode, WPARAM wParam, LPARAM lParam) {
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
                mouseButton = (GET_XBUTTON_WPARAM(mouse->mouseData) == XBUTTON1) ? getKeyCodeFromString("MFORWARD") : getKeyCodeFromString("MBACK");
                isKeyUp = false;
                break;
            case WM_XBUTTONUP:
                mouseButton = (GET_XBUTTON_WPARAM(mouse->mouseData) == XBUTTON1) ? getKeyCodeFromString("MFORWARD") : getKeyCodeFromString("MBACK");
                isKeyUp = true;
                break;
            case WM_MOUSEWHEEL: {
                int delta = GET_WHEEL_DELTA_WPARAM(mouse->mouseData);
                mouseButton = (delta > 0) ? getKeyCodeFromString("WHEEL_UP") : getKeyCodeFromString("WHEEL_DOWN");
                isKeyUp = false;  // Scrolling is a "press-like" event
                break;
            }
            default:
                // No relevant mouse action detected
                mouseButton = -1;  // Invalid key
                isKeyUp = false;
                break;
        }

        InputTrigger inputTrigger;
        inputTrigger.isUp = isKeyUp;
        inputTrigger.keyCode = mouseButton;
        if (inputTrigger.keyCode != -1){
            if (handleInput(inputTrigger)){
                return 1;
            }
        }
        // You can process the inputTrigger here or pass it to other parts of your code.
    }

    return CallNextHookEx(mouseHook, nCode, wParam, lParam);
}