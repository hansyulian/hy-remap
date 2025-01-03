#include "utils.h"

INPUT convertKeyCodeToInput(int keyCode, bool up){
    INPUT input = {};
    input.ki.dwExtraInfo = HY_BYPASS_EXECUTION_FLAG;
    input.mi.dwExtraInfo = HY_BYPASS_EXECUTION_FLAG;
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
            input.ki.wScan = MapVirtualKey(keyCode, MAPVK_VK_TO_VSC);  // Get the scan code
            if (up){
                input.ki.dwFlags = KEYEVENTF_KEYUP;
            }
            break;
    }
    return input;
}

void handleMappedInput(int keyCode, bool up){
    auto input = convertKeyCodeToInput(keyCode, up);
    SendInput(1, &input, sizeof(INPUT));
}
