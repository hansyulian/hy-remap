#include "main.h"

void executeInputs(const std::vector<INPUT>& inputs) {
    if (inputs.empty()) {
        return; // Avoid calling SendInput with no inputs
    }
    SendInput(static_cast<UINT>(inputs.size()), const_cast<INPUT*>(inputs.data()), sizeof(INPUT));
}


INPUT convertKeyCodeToInput(int keyCode, bool isKeyUp){
    INPUT input = {};
    input.ki.dwExtraInfo = HY_BYPASS_EXECUTION_FLAG;
    switch (keyCode){
        case VK_LBUTTON:
            input.type = INPUT_MOUSE;
            input.mi.dwFlags = isKeyUp ? MOUSEEVENTF_LEFTUP : MOUSEEVENTF_LEFTDOWN;
            break;
        case VK_RBUTTON:
            input.type = INPUT_MOUSE;
            input.mi.dwFlags = isKeyUp ? MOUSEEVENTF_RIGHTUP : MOUSEEVENTF_RIGHTDOWN;
            break;
        case VK_MBUTTON:
            input.type = INPUT_MOUSE;
            input.mi.dwFlags = isKeyUp ? MOUSEEVENTF_MIDDLEUP : MOUSEEVENTF_MIDDLEDOWN;
            break;
        default: 
            input.type = INPUT_KEYBOARD;
            input.ki.wVk = keyCode;
            if (isKeyUp){
                input.ki.dwFlags = KEYEVENTF_KEYUP;
            }
            break;
    }
    return input;
}