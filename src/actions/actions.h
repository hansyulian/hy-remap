#ifndef ACTIONS_H
#define ACTIONS_H
#include "../main.h"
#include "../utils/utils.h"

// actions
// simple action
void performSimpleAction(const OptimizedAction& action, const KeyAction& inputTrigger);
void releaseSimpleAction(const OptimizedAction& action);
// profile shift action
void performProfileShiftAction(const OptimizedAction& action, const KeyAction& inputTrigger);
void releaseProfileShiftAction(const OptimizedAction& action, int keyCode);
// macro action
void performMacroAction(const OptimizedAction& action, const KeyAction& inputTrigger);
void releaseMacroAction(const OptimizedAction& action, bool force);
// macro run program
void performRunProgramAction(const OptimizedAction& action, const KeyAction& inputTrigger);
void performAudioMixerAction(const OptimizedAction& action, const KeyAction& inputTrigger);

#endif