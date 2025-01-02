#include "main.h"

void performSimpleAction(const OptimizedAction& action, const KeyAction& inputTrigger){
    keyDownActionIndex[inputTrigger.keyCode] = action.index;
    // vector<INPUT> inputs;
    auto keyCodes = action.keyCodes;
    auto hwnd = windowInfoCache.hwnd;
    auto gamingMode = windowInfoCache.gamingMode;
    auto keyCodeSize = keyCodes.size();
    
    if (inputTrigger.up){
        for (int i = keyCodeSize-1; i >=0; i--) {
            // Simulate key press (KEYUP) for each key in sequence in reverse
            auto keyCode = keyCodes[i];
            // inputs.push_back(convertKeyCodeToInput(keyCode, inputTrigger.up));
            handleMappedInput(hwnd,gamingMode,keyCode,inputTrigger.up);
        }
    } else {
        for (int i = 0; i < keyCodeSize; i++) {
            // Simulate key press (KEYDOWN) for each key in sequence
            auto keyCode = keyCodes[i];
            // inputs.push_back(convertKeyCodeToInput(keyCode, inputTrigger.up));
            handleMappedInput(hwnd,gamingMode,keyCode,inputTrigger.up);
        }
        if (inputTrigger.keyCode == HR_WHEEL_UP || inputTrigger.keyCode == HR_WHEEL_DOWN){        
            for (int i = keyCodeSize-1; i >=0; i--) {
                // Simulate key press (KEYUP) for each key in sequence in reverse
                auto keyCode = keyCodes[i];
                handleMappedInput(hwnd,gamingMode,keyCode,true);
                // inputs.push_back(convertKeyCodeToInput(keyCode, true));
            }
        }
        cout << "Simple Action " << action.name << endl;
    }
    // Send all inputs
    // executeInputs(inputs);
}

void releaseSimpleAction(const OptimizedAction& action){
    auto keyCodes = action.keyCodes;
    auto keyCodeSize = keyCodes.size();
    auto hwnd = windowInfoCache.hwnd;
    auto gamingMode = windowInfoCache.gamingMode;
    // vector<INPUT> inputs;
    for (int i = keyCodeSize-1; i >=0; i--) {
        // Simulate key press (KEYUP) for each key in sequence in reverse
        auto keyCode = keyCodes[i];
        handleMappedInput(hwnd,gamingMode,keyCode,true);
        // inputs.push_back(convertKeyCodeToInput(key, true));
    }
    // executeInputs(inputs);
}