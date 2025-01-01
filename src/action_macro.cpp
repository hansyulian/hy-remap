  #include "main.h"
#include "chrono"

bool isMacroActionThreadRunning(const OptimizedAction& action){
  return isMacroActionThreadRunnings[action.index];
}


void executeMacroItem(const OptimizedMacroItem& macroItem, const OptimizedAction& action){
  if (isMacroActionThreadRunning(action) && macroItem.keyCode > -1){
    // // cout << "macro keycode " << macroItem.keyCode << endl;
    vector<INPUT> inputs;
    inputs.push_back(convertKeyCodeToInput(macroItem.keyCode,macroItem.up));
    executeInputs(inputs);
  }
  if (isMacroActionThreadRunning(action) && macroItem.delayMs > 0){
    // // cout << "macro delay " << macroItem.delayMs << endl;
    auto start = chrono::system_clock::now();
    auto duration = chrono::duration_cast<std::chrono::milliseconds>(chrono::system_clock::now() - start).count();
    while (isMacroActionThreadRunning(action) && duration < macroItem.delayMs){
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
  // cout << "macro repeat mode " << action.macroRepeatMode << endl;
  if (action.macroRepeatMode == MacroRepeatMode::NONE){
    // cout << "non repeating macro" << endl;
      for (const auto& macroItem: action.optimizedMacroItems){
        executeMacroItem(macroItem, action);
      }
      isMacroActionThreadRunnings[action.index] = false;
      return;
  }
  // cout << "executing repeating macro" << endl;
  int macroItemsLength = action.optimizedMacroItems.size();
  int macroItemIndex = 0;
  int localMacroKeyDownStateIndex[256];
  while(isMacroActionThreadRunning(action)){
    auto macroItem = &action.optimizedMacroItems[macroItemIndex];
    localMacroKeyDownStateIndex[macroItem->keyCode] = !macroItem->up;
    executeMacroItem(*macroItem, action);
    macroItemIndex = (macroItemIndex + 1) % macroItemsLength;
  }
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
  if (macroActionThreads[action.index].joinable()) {
    // cout << "executing join macro thread " << action.index << endl;
  }
  // cout << "macro stopping done " << action.index << endl;
}


void startMacroThread(const OptimizedAction& action){
  // cout << "start macro thread " << action.index << endl;
  if (macroActionThreads[action.index].joinable()){
    // cout << "stopping previous action thread " << action.index << endl;
    macroActionThreads[action.index].join();
  }
  if (isMacroActionThreadRunnings[action.index]){
    // cout << "still have previous action thread " << action.index << endl;
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

void releaseMacroAction(const OptimizedAction& action){
  // cout << "release macro action " << action.index << " " << inputTrigger.keyCode << ":" << inputTrigger.up << endl;
  switch(action.macroRepeatMode){
    case MacroRepeatMode::NONE:
      return;
    case MacroRepeatMode::HOLD:   
        // cout << "Stopping Hold macro" << endl;   
      stopMacroThread(action);
      return;
    case MacroRepeatMode::TOGGLE:
      return;
  }  
}