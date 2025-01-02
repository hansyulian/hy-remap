  #include "main.h"
#include "chrono"

bool isMacroActionThreadRunning(const OptimizedAction& action){
  return isMacroActionThreadRunnings[action.index];
}
bool isValidMacroExecutionCondition(const OptimizedAction& action, DWORD processId){
  return isMacroActionThreadRunning(action) && processId == windowInfoCache.processId;
}

void executeMacroItem(const OptimizedMacroItem& macroItem, const OptimizedAction& action, DWORD processId){
  if (isValidMacroExecutionCondition(action, processId) && macroItem.keyCode > -1){
    // cout << "macro keycode " << macroItem.keyCode << endl;
    vector<INPUT> inputs;
    inputs.push_back(convertKeyCodeToInput(macroItem.keyCode,macroItem.up));
    executeInputs(inputs);
  }
  if (isValidMacroExecutionCondition(action, processId) && macroItem.delayMs > 0){
    // cout << "macro delay " << macroItem.delayMs << endl;
    auto start = chrono::system_clock::now();
    auto duration = chrono::duration_cast<std::chrono::milliseconds>(chrono::system_clock::now() - start).count();
    while (isValidMacroExecutionCondition(action, processId) && duration < macroItem.delayMs){
      int durationDifference = macroItem.delayMs - duration;
      if (durationDifference > THREAD_SLEEP_SEGMENTATION_MS){
        this_thread::sleep_for(chrono::milliseconds(THREAD_SLEEP_SEGMENTATION_MS));
      } else {
        this_thread::sleep_for(chrono::milliseconds(durationDifference));
      }
      duration = chrono::duration_cast<std::chrono::milliseconds>(chrono::system_clock::now() - start).count();
    }
  }
}

void macroThreadExecution(const OptimizedAction& action){
  // cout << "executing macro thread " << action.index << endl;
  auto index = action.index;
  auto processId = windowInfoCache.processId; // use this to ensure later that if the window name change, then we cancel execution
  // cout << "macro repeat mode " << action.macroRepeatMode << endl;
  if (action.macroRepeatMode == MacroRepeatMode::NONE){

    // cout << "non repeating macro" << endl;
      for (const auto& macroItem: action.optimizedMacroItems){
        executeMacroItem(macroItem, action, processId);
      }
      isMacroActionThreadRunnings[action.index] = false;
      return;
  }
  // cout << "executing repeating macro" << endl;
  int macroItemsLength = action.optimizedMacroItems.size();
  int macroItemIndex = 0;
  int localMacroKeyDownStateIndex[256];
  while(isValidMacroExecutionCondition(action,processId)){
    auto macroItem = &action.optimizedMacroItems[macroItemIndex];
    localMacroKeyDownStateIndex[macroItem->keyCode] = !macroItem->up;
    executeMacroItem(*macroItem, action, processId);
    macroItemIndex = (macroItemIndex + 1) % macroItemsLength;
  }
  isMacroActionThreadRunnings[action.index] = false;
  vector<INPUT> inputClearance;
  for (int i = 0; i < 256; i++){
    if (localMacroKeyDownStateIndex[i]){
      inputClearance.push_back(convertKeyCodeToInput(i,true));
    }
  }
  executeInputs(inputClearance);
}


void stopMacroThread(const OptimizedAction& action){
  // cout << "stopping macro thread " << action.index;
  isMacroActionThreadRunnings[action.index] = false;
  // if (macroActionThreads[action.index].joinable()) {
    // cout << "executing join macro thread " << action.index << endl;
  // }
  // cout << "macro stopping done " << action.index << endl;
}


void startMacroThread(const OptimizedAction& action){
  if (isMacroActionThreadRunnings[action.index]){
  //   cout << "still have previous action thread " << action.index << endl;
    return;
  }
  // cout << "start macro thread " << action.index << endl;
  if (macroActionThreads[action.index].joinable()){
    // cout << "stopping previous action thread " << action.index << endl;
    macroActionThreads[action.index].join();
  }
  isMacroActionThreadRunnings[action.index] = true;
  macroActionThreads[action.index] = thread(macroThreadExecution,action);
  // cout << "macro thread started " << action.index << endl;
}

void performMacroAction(const OptimizedAction& action, const InputTrigger& inputTrigger){
  auto up = inputTrigger.up;
  if (up){
    return;
  }
  auto keyCode = inputTrigger.keyCode;
  switch(action.macroRepeatMode){
    case MacroRepeatMode::NONE:
      // cout << "Executing single macro" << endl;
      startMacroThread(action);
      return;
    case MacroRepeatMode::HOLD:
      // cout << "Executing Hold macro" << endl;
      keyDownActionIndex[inputTrigger.keyCode] = action.index;
      startMacroThread(action);
      return;
    case MacroRepeatMode::TOGGLE:
      if (isMacroActionThreadRunning(action)){
        // cout << "Executing Toggle macro" << endl;
        keyDownActionIndex[inputTrigger.keyCode] = -1;
        stopMacroThread(action);
      } else {        
        // cout << "Stopping Toggle macro" << endl;      
        keyDownActionIndex[inputTrigger.keyCode] = action.index;
        startMacroThread(action);
      }
      return;
  }
}

void releaseMacroAction(const OptimizedAction& action, bool force){
  // cout << "release macro action " << action.index << " " << action.name << " " << force << endl;
  switch(action.macroRepeatMode){
    case MacroRepeatMode::NONE:
      return;
    case MacroRepeatMode::HOLD:   
        // cout << "Stopping Hold macro" << endl;   
      stopMacroThread(action);
      return;
    case MacroRepeatMode::TOGGLE:
      if (force){
        stopMacroThread(action);
      }
      return;
  }  
}