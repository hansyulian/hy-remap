#include "main.h"

INPUT convertKeyCodeToInput(int keyCode, bool isKeyUp){
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
OptimizedAction* getActionByName(const string& name) {
    int index = getActionIndexByName(name);  // Get the index of the action by name
    if (index != -1) {
        return &optimizedActions[index];  // Return the action if found
    }
    return nullptr;  // Return nullptr if the action is not found
}

int getActionIndexByName(const string& name){
  for (int i = 0; i < optimizedActions.size(); i++){
    if (optimizedActions[i].name == name){
      return i;
    }
  }
  return -1;
}