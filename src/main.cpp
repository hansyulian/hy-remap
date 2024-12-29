#include "key_remapper.h"

HHOOK keyboardHook;
std::vector<json> actions;
std::vector<json> profiles;

// Example Usage
int main() {
    Config config = loadConfig();

    // Output some data for verification
    for (const auto& trigger : config.triggers) {
        std::cout << "Trigger: " << trigger.id << " - " << trigger.name << std::endl;
    }

    for (const auto& action : config.actions) {
        std::cout << "Action: " << action.id << " - " << action.name << " - Type: " << action.type << std::endl;
    }

    for (const auto& profile : config.profiles) {
        std::cout << "Profile: " << profile.name << std::endl;
        for (const auto& programName : profile.programNames) {
            std::cout << "  Program Name: " << programName << std::endl;
        }
        for (const auto& mapping : profile.mapping) {
            std::cout << "  Mapping: Trigger " << mapping.triggerId << " -> Action " << mapping.actionId << std::endl;
        }
    }

    return 0;
}

// int main() {
//     // Load configuration from a JSON file
//     loadConfiguration("./config.json");

//     std::cout << "Key remapper is running..." << std::endl;

//     // Start listening for keyboard input
//     startKeyboardHook();

//     // Run the message loop to handle keyboard events
//     MSG msg;
//     while (GetMessage(&msg, NULL, 0, 0) > 0) {
//         TranslateMessage(&msg);
//         DispatchMessage(&msg);
//     }

//     // Clean up before exit
//     stopKeyboardHook();
//     return 0;
// }
