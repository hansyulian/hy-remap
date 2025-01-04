#include "main.h"
#include "config/config.h"
#include "modules/modules.h"

Config config;
vector<OptimizedAction> optimizedActions;
vector<OptimizedTrigger> optimizedTriggers;
vector<OptimizedProfile> optimizedProfiles;
vector<thread> macroActionThreads;
vector<bool> isMacroActionThreadRunnings;
WindowInfo windowInfoCache;
int profileCacheIndex = NO_PROFILE_FLAG;
int overrideProfileIndex = NO_PROFILE_FLAG;
int defaultProfileIndex = NO_PROFILE_FLAG;
int triggerActionIndexMap[256];
int keyDownActionIndex[256];
bool profileShiftButtonHold[256];

// Define the keyboardHook variable here
HHOOK keyboardHook = NULL;  // Define the keyboardHook variable (this is where memory is allocated)
HHOOK mouseHook = NULL;     // Define the mouseHook variable

int main() {
    // Load configuration from a JSON file
    
    cout << "Loading Config" << endl;
    loadConfig();
    cout << "Optimizing Config" << endl;
    optimizeConfig();

    cout << "Key remapper is running..." << endl;
    cout << "Build Date: " << __DATE__ << endl;
    cout << "Build Time: " << __TIME__ << endl;
    for (int i = 0; i < 256; i++) {
        keyDownActionIndex[i] = NO_ACTION_FLAG;
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
