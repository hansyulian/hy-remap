#include "key_remapper.h"

#include <fstream>
#include <sstream>
#include <iostream>

string loadConfigString() {
    string filePath = "./config.json";
    ifstream file(filePath);  // Open the file in read mode
    if (!file.is_open()) {
        cerr << "Error opening file: " << filePath << endl;
        return "";  // Return an empty string if the file can't be opened
    }

    stringstream buffer;
    buffer << file.rdbuf();  // Read the file into the stringstream
    return buffer.str();  // Return the file content as a string
}

Config loadConfig(){
  string configString = loadConfigString();
  json configJson = json::parse(configString);

  // Deserialize into Config struct
  Config config = configJson.get<Config>();

  return config;
}