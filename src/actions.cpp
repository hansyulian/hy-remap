#include "key_remapper.h"
#include "iostream"

void performAction(const Action& action) {
    std::cout << "Action: " << action.id << std::endl;
    // if (action.type == "simple") {
    //     if (action["ctrl"].get<bool>()) {
    //         keybd_event(VK_CONTROL, 0, 0, 0);  // Ctrl key down
    //     }
    //     if (action["alt"].get<bool>()) {
    //         keybd_event(VK_MENU, 0, 0, 0);  // Alt key down
    //     }
    //     if (action["shift"].get<bool>()) {
    //         keybd_event(VK_SHIFT, 0, 0, 0);  // Shift key down
    //     }
    //     if (action["win"].get<bool>()) {
    //         keybd_event(VK_LWIN, 0, 0, 0);  // Win key down
    //     }

    //     UINT key = VkKeyScan(action["key"].get<std::string>()[0]);
    //     keybd_event(key, 0, 0, 0);  // Key down
    //     keybd_event(key, 0, KEYEVENTF_KEYUP, 0);  // Key up

    //     if (action["ctrl"].get<bool>()) {
    //         keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);  // Ctrl key up
    //     }
    //     if (action["alt"].get<bool>()) {
    //         keybd_event(VK_MENU, 0, KEYEVENTF_KEYUP, 0);  // Alt key up
    //     }
    //     if (action["shift"].get<bool>()) {
    //         keybd_event(VK_SHIFT, 0, KEYEVENTF_KEYUP, 0);  // Shift key up
    //     }
    //     if (action["win"].get<bool>()) {
    //         keybd_event(VK_LWIN, 0, KEYEVENTF_KEYUP, 0);  // Win key up
    //     }
    // }
}
