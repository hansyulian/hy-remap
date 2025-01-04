#ifndef CONFIG_H
#define CONFIG_H
#include "../main.h"

void debugConfig();
void debugOptimizedConfig();
int getKeyCodeFromString(const string& key);
string loadConfigString();
void loadConfig();
void calculateOptimizedConfig();


void from_json(const json& j, Trigger& t);
void from_json(const json& j, Action& a);
void from_json(const json& j, Mapping& m);
void from_json(const json& j, Profile& p);
void from_json(const json& j, Config& c);


#endif