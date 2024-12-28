#include "key_remapper.h"

HHOOK keyboardHook;
std::vector<json> actions;
std::vector<json> profiles;

int main() {
    // Load configuration from a JSON file
    loadConfiguration("./config.json");

    std::cout << "Key remapper is running..." << std::endl;

    // Start listening for keyboard input
    startKeyboardHook();

    // Run the message loop to handle keyboard events
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0) > 0) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    // Clean up before exit
    stopKeyboardHook();
    return 0;
}
