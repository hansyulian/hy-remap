#include "main.h"

void executeInputs(const std::vector<INPUT>& inputs) {
    if (inputs.empty()) {
        return; // Avoid calling SendInput with no inputs
    }
    SendInput(static_cast<UINT>(inputs.size()), const_cast<INPUT*>(inputs.data()), sizeof(INPUT));
}