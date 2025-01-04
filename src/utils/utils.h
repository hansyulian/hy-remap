#ifndef UTILS_H
#define UTILS_H
#include "../main.h"
#include "../config/config.h"

void runProgram(const string& path);
string lowerCaseString(const string& value);
WindowInfo getCurrentWindowInfo();

OptimizedAction* getActionByName(const string& name);
int getActionIndexByName(const string& name);
OptimizedTrigger* getTriggerByName(const string& name);
int getTriggerIndexByName(const string& name);
OptimizedProfile* getProfileByName(const string& name);
int getProfileIndexByName(const string& name);

void handleMappedInput(int keyCode, bool up);
#endif