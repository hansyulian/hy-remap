#include "config_loader.h"
#include <fstream>
#include <sstream>
#include <iostream>

std::string loadConfigString() {
    std::string filePath = "./config.json";
    std::ifstream file(filePath);  // Open the file in read mode
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filePath << std::endl;
        return "";  // Return an empty string if the file can't be opened
    }

    std::stringstream buffer;
    buffer << file.rdbuf();  // Read the file into the stringstream
    return buffer.str();  // Return the file content as a string
}

Config loadConfig(){
  std::string configString = loadConfigString();
  json configJson = json::parse(configString);

  // Deserialize into Config struct
  Config config = configJson.get<Config>();

  return config;
}