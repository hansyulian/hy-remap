#ifndef CONFIG_H
#define CONFIG_H
#include "../main.h"

void debugConfig();
void debugOptimizedConfig();
int getKeyCodeFromString(const string& key);
string loadConfigString();
void loadConfig();
void optimizeConfig();


void from_json(const json& j, Trigger& var);
void from_json(const json& j, Action& var);
void from_json(const json& j, Mapping& var);
void from_json(const json& j, Profile& var);
void from_json(const json& j, Config& var);
void from_json(const json& j, SimpleAction& var);
void from_json(const json& j, MacroAction& var);
void from_json(const json& j, ProfileShiftAction& var);
void from_json(const json& j, RunProgramAction& var);
void from_json(const json& j, AudioMixerAction& var);


#endif