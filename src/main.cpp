#include "key_remapper.h"

int main() {
    // Load configuration from a JSON file
    std::cout << "Loading Config" << std::endl;
    Config config = loadConfig();

    std::cout << "Key remapper is running..." << std::endl;

    // Start listening for keyboard input
    startKeyboardAndMouseHook(config);  // Pass the config here

    // Run the message loop to handle keyboard events
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0) > 0) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    // Clean up before exit
    stopKeyboardAndMouseHook();
    return 0;
}
