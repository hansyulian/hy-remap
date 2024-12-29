#include "key_remapper.h"

Config config;
Profile* defaultProfile = new Profile();

// Define the keyboardHook variable here
HHOOK keyboardHook = NULL;  // Define the keyboardHook variable (this is where memory is allocated)
HHOOK mouseHook = NULL;     // Define the mouseHook variable

int main() {
    // Load configuration from a JSON file
    cout << "Loading Config" << endl;
    loadConfig();

    cout << "Key remapper is running..." << endl;

    // Start listening for keyboard input
    startKeyboardAndMouseHook();  // Pass the config here

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
