#include "main.h"

Config config;
vector<OptimizedAction> optimizedActions;
vector<OptimizedTrigger> optimizedTriggers;
vector<OptimizedProfile> optimizedProfiles;
vector<thread> macroActionThreads;
vector<bool> isMacroActionThreadRunnings;
string profileCacheWindowName = "";
int profileCacheIndex = -1;
int overrideProfileIndex = -1;
int defaultProfileIndex = -1;
int triggerActionIndexMap[256];
int keyDownActionIndex[256];

// Define the keyboardHook variable here
HHOOK keyboardHook = NULL;  // Define the keyboardHook variable (this is where memory is allocated)
HHOOK mouseHook = NULL;     // Define the mouseHook variable

int main() {
    // Load configuration from a JSON file
    
    cout << "Loading Config" << endl;
    loadConfig();
    cout << "Optimizing Config" << endl;
    calculateOptimizedConfig();

    cout << "Key remapper is running..." << endl;
    for (int i = 0; i < 256; i++) {
        keyDownActionIndex[i] = -1;
    }
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
