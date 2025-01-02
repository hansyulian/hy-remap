#include "main.h"

void postInputMessage(HWND hwnd, int keyCode, bool up) {
    // cout << "Post Input Message " << keyCode << " " << up << endl;
    if (keyCode == VK_LBUTTON || keyCode == VK_RBUTTON || keyCode == VK_MBUTTON) {
        // Handle mouse click actions
        POINT p;
        GetCursorPos(&p);  // Get current mouse position
        ScreenToClient(hwnd, &p);  // Convert screen coordinates to client coordinates of the window

        // Define the message based on the mouse button
        UINT msg = 0;
        if (keyCode == VK_LBUTTON) {
            msg = up ? WM_LBUTTONUP : WM_LBUTTONDOWN;
        } else if (keyCode == VK_RBUTTON) {
            msg = up ? WM_RBUTTONUP : WM_RBUTTONDOWN;
        } else if (keyCode == VK_MBUTTON) {
            msg = up ? WM_MBUTTONUP : WM_MBUTTONDOWN;
        }

        // Send the PostMessage for mouse click at the current mouse position
        PostMessage(hwnd, msg, keyCode, MAKELPARAM(p.x, p.y)); // x and y are mouse coordinates
    } else {
        // Handle keyboard actions
        const int scanCode = MapVirtualKey(keyCode, MAPVK_VK_TO_VSC); // Get scan code for key

        // Define the message and flags for PostMessage
        UINT msg = up ? WM_KEYUP : WM_KEYDOWN;
        DWORD lParam = (scanCode << 16) | (up ? (1 << 30) | (1 << 31) : 1); // Key up or down flags

        // Send the PostMessage for key press or release
        PostMessage(hwnd, msg, keyCode, lParam);
    }
}

void executeInput(int keyCode, bool up){
    auto input = convertKeyCodeToInput(keyCode, up);
    SendInput(1, &input, sizeof(INPUT));
}

void executeInputs(const std::vector<INPUT>& inputs) {
    if (inputs.empty()) {
        return; // Avoid calling SendInput with no inputs
    }
    SendInput(static_cast<UINT>(inputs.size()), const_cast<INPUT*>(inputs.data()), sizeof(INPUT));
    
    // Debugging: Iterate through the inputs to log key events
    for (const INPUT& input : inputs) {
        if (input.type == INPUT_KEYBOARD) {
            // Get the virtual key code and the key event (KEYDOWN/KEYUP)
            unsigned short vkCode = input.ki.wVk;
            bool up = (input.ki.dwFlags & KEYEVENTF_KEYUP) != 0;
            
            // std::cout << "Key Code: " << vkCode 
            //           << " (" << static_cast<char>(vkCode) << ")"
            //           << " - " << (up ? "Key UP" : "Key DOWN")
            //           << std::endl;
        }
    }
}


INPUT convertKeyCodeToInput(int keyCode, bool up){
    INPUT input = {};
    input.ki.dwExtraInfo = HY_BYPASS_EXECUTION_FLAG;
    switch (keyCode){
        case VK_LBUTTON:
            input.type = INPUT_MOUSE;
            input.mi.dwFlags = up ? MOUSEEVENTF_LEFTUP : MOUSEEVENTF_LEFTDOWN;
            break;
        case VK_RBUTTON:
            input.type = INPUT_MOUSE;
            input.mi.dwFlags = up ? MOUSEEVENTF_RIGHTUP : MOUSEEVENTF_RIGHTDOWN;
            break;
        case VK_MBUTTON:
            input.type = INPUT_MOUSE;
            input.mi.dwFlags = up ? MOUSEEVENTF_MIDDLEUP : MOUSEEVENTF_MIDDLEDOWN;
            break;
        default: 
            input.type = INPUT_KEYBOARD;
            input.ki.wVk = keyCode;
            if (up){
                input.ki.dwFlags = KEYEVENTF_KEYUP;
            }
            break;
    }
    return input;
}
void handleMappedInput(HWND hwnd, bool gamingMode, int keyCode, bool up){
    // cout << "  handle mapped input " << gamingMode << endl;
    auto calculatedGamingMode = gamingMode;
    switch (keyCode){
        case VK_VOLUME_UP:
        case VK_VOLUME_DOWN:
        case VK_MEDIA_PLAY_PAUSE:
        case VK_MEDIA_STOP:
        case VK_VOLUME_MUTE:
        case VK_MEDIA_NEXT_TRACK:
        case VK_MEDIA_PREV_TRACK:
            calculatedGamingMode = false;
            break;
    }
    if (calculatedGamingMode){
        postInputMessage(hwnd, keyCode, up);
    } else {
        executeInput(keyCode, up);
    }
}
