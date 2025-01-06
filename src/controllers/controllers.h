#ifndef MODULES_H
#define MODULES_H
#include "../main.h"
#include "../config/config.h"
#include "../utils/utils.h"
// Function declarations
void performAction(const OptimizedAction& action,const KeyAction& inputTrigger);

LRESULT CALLBACK keyboardProc(int nCode, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK mouseProc(int nCode, WPARAM wParam, LPARAM lParam);

void startKeyboardAndMouseHook();
void stopKeyboardAndMouseHook();

int getActiveProfileIndex();

bool processInputRemapping(const KeyAction& inputTrigger);
void releaseOngoingAction(int keyCode, bool force);

void refreshProfileCache();
#endif