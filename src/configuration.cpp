#include "key_remapper.h"

void loadConfiguration(const std::string& configFilePath) {
    std::cout << "Attempting to open configuration file: " << configFilePath << std::endl;

    std::ifstream file(configFilePath);
    if (!file.is_open()) {
        std::cerr << "Failed to open configuration file: " << configFilePath << std::endl;
        return;
    }

    json config;
    file >> config;
    actions = config["actions"].get<std::vector<json>>();  // Store actions from the config
    profiles = config["profiles"].get<std::vector<json>>();  // Store profiles from the config
}
