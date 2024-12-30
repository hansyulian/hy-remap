#include "main.h"
#include "iostream"

INPUT convertKeyNameToInput(string keyName, bool isKeyUp){
    auto keyCode = getKeyCodeFromString(keyName);
    INPUT input = {};
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

void performSimpleAction(const Action& action, const InputTrigger& inputTrigger){
    vector<INPUT> inputs;
    auto keySize = action.keys.size();
    if (inputTrigger.isUp){
        for (int i = keySize-1; i >=0; i--) {
            // Simulate key press (KEYUP) for each key in sequence in reverse
            auto key = action.keys[i];
            inputs.push_back(convertKeyNameToInput(key, inputTrigger.isUp));
        }
    } else {
        for (int i = 0; i < keySize; i++) {
            // Simulate key press (KEYDOWN) for each key in sequence
            auto key = action.keys[i];
            inputs.push_back(convertKeyNameToInput(key, inputTrigger.isUp));
        }
    }
    if (inputTrigger.keyCode == HR_WHEEL_UP || inputTrigger.keyCode == HR_WHEEL_DOWN){        
        for (int i = keySize-1; i >=0; i--) {
            // Simulate key press (KEYUP) for each key in sequence in reverse
            auto key = action.keys[i];
            inputs.push_back(convertKeyNameToInput(key, true));
        }
    }
    // Send all inputs
    SendInput(static_cast<UINT>(inputs.size()), inputs.data(), sizeof(INPUT));
}

void performAction(const Action& action, const InputTrigger& inputTrigger) {
    
    switch(action.type){
        case ActionType::SIMPLE:
        performSimpleAction(action,inputTrigger);
        break;
    }
}

