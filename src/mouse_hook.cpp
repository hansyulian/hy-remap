#include "key_remapper.h"

LRESULT CALLBACK mouseProc(int nCode, WPARAM wParam, LPARAM lParam) {
    if (nCode >= 0) {
        MSLLHOOKSTRUCT* mouse = (MSLLHOOKSTRUCT*)lParam;

        KeyCode mouseButton = static_cast<KeyCode>(0);
        bool isKeyUp = false;

        // Determine the mouse button and whether it's an "up" or "down" event
        switch (wParam) {
            case WM_LBUTTONDOWN:
                mouseButton = KeyCode::LEFT_CLICK;
                isKeyUp = false;
                break;
            case WM_LBUTTONUP:
                mouseButton = KeyCode::LEFT_CLICK;
                isKeyUp = true;
                break;
            case WM_RBUTTONDOWN:
                mouseButton = KeyCode::RIGHT_CLICK;
                isKeyUp = false;
                break;
            case WM_RBUTTONUP:
                mouseButton = KeyCode::RIGHT_CLICK;
                isKeyUp = true;
                break;
            case WM_MBUTTONDOWN:
                mouseButton = KeyCode::MIDDLE_CLICK;
                isKeyUp = false;
                break;
            case WM_MBUTTONUP:
                mouseButton = KeyCode::MIDDLE_CLICK;
                isKeyUp = true;
                break;
            case WM_XBUTTONDOWN:
                mouseButton = (GET_XBUTTON_WPARAM(mouse->mouseData) == XBUTTON1) ? KeyCode::MFORWARD : KeyCode::MBACK;
                isKeyUp = false;
                break;
            case WM_XBUTTONUP:
                mouseButton = (GET_XBUTTON_WPARAM(mouse->mouseData) == XBUTTON1) ? KeyCode::MFORWARD : KeyCode::MBACK;
                isKeyUp = true;
                break;
            case WM_MOUSEWHEEL: {
                int delta = GET_WHEEL_DELTA_WPARAM(mouse->mouseData);
                mouseButton = (delta > 0) ? KeyCode::WHEEL_UP : KeyCode::WHEEL_DOWN;
                isKeyUp = false;  // Scrolling is a "press-like" event
                break;
            }
            default:
                // No relevant mouse action detected
                mouseButton = static_cast<KeyCode>(0);
                isKeyUp = false;
                break;
        }

        // Output for debugging
        if (mouseButton != static_cast<KeyCode>(0)) {
            std::cout << "Mouse Button: " << mouseButton
                      << (isKeyUp ? " Released" : " Pressed") 
                      << " at (" << mouse->pt.x << ", " << mouse->pt.y << ")" << std::endl;
        }
    }

    return CallNextHookEx(mouseHook, nCode, wParam, lParam);
}
