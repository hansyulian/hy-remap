#include "key_remapper.h"

bool handleInput(const InputTrigger& inputTrigger){
    cout << "Input Trigger " << inputTrigger.keyCode << " " << inputTrigger.isUp << endl;
    auto keyCode = inputTrigger.keyCode;
    auto isUp = inputTrigger.isUp;
    auto profile = getProfile(); // profile is guaranteed to exist, at least the default profile
    cout << "Current Profile " << profile->id << " " << profile->name << endl;

    const Trigger* currentTrigger = nullptr;
    for (const auto& trigger : config.triggers) {
        if (getKeyCodeFromString(trigger.key) == keyCode) {
            currentTrigger = &trigger;
            break;
        }
    }

    if (currentTrigger == nullptr) {
        cout << "No matching trigger found." << endl;
        return false;
    }
    cout << "Current Trigger: " << currentTrigger->id << " " << currentTrigger->key << endl;

    const Mapping* currentMapping = nullptr;
    for (const auto& mapping : profile->mapping) {
        if (mapping.triggerId == currentTrigger->id) {
            currentMapping = &mapping;
            break;
        }
    }

    if (currentMapping == nullptr) {
        cout << "No matching mapping found." << endl;
        return false;
    }

    cout << "Current Mapping: " << currentMapping->actionId << " " << endl;
    
    const Action* currentAction = nullptr;
    for (const auto& action: config.actions){
        if (action.id == currentMapping->actionId){
            currentAction = &action;
            break;
        }
    }
    if (currentAction == nullptr){
        cout << "No matchin action found." << endl;
        return false;
    }
    performAction(*currentAction, inputTrigger);
    return true;
}