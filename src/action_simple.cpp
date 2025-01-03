#include "main.h"

void performSimpleAction(const OptimizedAction& action, const KeyAction& inputTrigger){
    // cout << "simple action checking " << keyDownActionIndex[inputTrigger.keyCode] << " -- " << action.index << endl;
    // if (keyDownActionIndex[inputTrigger.keyCode] == action.index){
        // cout << "cancelling " << inputTrigger.keyCode << " " << action.name << ":" << action.index <<" due to already activated" <<  endl;
        // return;
    // }
    // vector<INPUT> inputs;
    auto keyCodes = action.keyCodes;
    auto hwnd = windowInfoCache.hwnd;
    auto keyCodeSize = keyCodes.size();
    
    if (inputTrigger.up){
        for (int i = keyCodeSize-1; i >=0; i--) {
            // Simulate key press (KEYUP) for each key in sequence in reverse
            auto keyCode = keyCodes[i];
            // inputs.push_back(convertKeyCodeToInput(keyCode, inputTrigger.up));
            handleMappedInput(keyCode,inputTrigger.up);
        }
    } else {
        keyDownActionIndex[inputTrigger.keyCode] = action.index;
        for (int i = 0; i < keyCodeSize; i++) {
            // Simulate key press (KEYDOWN) for each key in sequence
            auto keyCode = keyCodes[i];
            // inputs.push_back(convertKeyCodeToInput(keyCode, inputTrigger.up));
            handleMappedInput(keyCode,inputTrigger.up);
        }
        if (inputTrigger.keyCode == HR_WHEEL_UP || inputTrigger.keyCode == HR_WHEEL_DOWN){        
            for (int i = keyCodeSize-1; i >=0; i--) {
                // Simulate key press (KEYUP) for each key in sequence in reverse
                auto keyCode = keyCodes[i];
                handleMappedInput(keyCode,true);
                // inputs.push_back(convertKeyCodeToInput(keyCode, true));
            
            }
            keyDownActionIndex[inputTrigger.keyCode] = -1;
        }
        cout << "Simple Action " << action.name << endl;
    }
}

void releaseSimpleAction(const OptimizedAction& action){
    auto keyCodes = action.keyCodes;
    auto keyCodeSize = keyCodes.size();
    auto hwnd = windowInfoCache.hwnd;
    // vector<INPUT> inputs;
    for (int i = keyCodeSize-1; i >=0; i--) {
        // Simulate key press (KEYUP) for each key in sequence in reverse
        auto keyCode = keyCodes[i];
        handleMappedInput(keyCode,true);
        // inputs.push_back(convertKeyCodeToInput(key, true));
    }
}