#include "main.h"

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
            bool isKeyUp = (input.ki.dwFlags & KEYEVENTF_KEYUP) != 0;
            
            // std::cout << "Key Code: " << vkCode 
            //           << " (" << static_cast<char>(vkCode) << ")"
            //           << " - " << (isKeyUp ? "Key UP" : "Key DOWN")
            //           << std::endl;
        }
    }
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