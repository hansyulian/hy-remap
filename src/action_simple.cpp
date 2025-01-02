#include "main.h"

void performSimpleAction(const OptimizedAction& action, const InputTrigger& inputTrigger){
    vector<INPUT> inputs;
    auto keyCodes = action.keyCodes;
    auto keyCodeSize = keyCodes.size();
    if (inputTrigger.up){
        for (int i = keyCodeSize-1; i >=0; i--) {
            // Simulate key press (KEYUP) for each key in sequence in reverse
            auto key = keyCodes[i];
            inputs.push_back(convertKeyCodeToInput(key, inputTrigger.up));
        }
    } else {
        for (int i = 0; i < keyCodeSize; i++) {
            // Simulate key press (KEYDOWN) for each key in sequence
            auto key = keyCodes[i];
            inputs.push_back(convertKeyCodeToInput(key, inputTrigger.up));
        }
    }
    if (inputTrigger.keyCode == HR_WHEEL_UP || inputTrigger.keyCode == HR_WHEEL_DOWN){        
        for (int i = keyCodeSize-1; i >=0; i--) {
            // Simulate key press (KEYUP) for each key in sequence in reverse
            auto key = keyCodes[i];
            inputs.push_back(convertKeyCodeToInput(key, true));
        }
    }
    if (!inputTrigger.up){
        cout << "Simple Action " << action.name << endl;
    }
    // Send all inputs
    executeInputs(inputs);
}
