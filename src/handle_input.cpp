#include "key_remapper.h"

bool handleInput(InputTrigger inputTrigger){
  cout << inputTrigger.keyCode << " " << inputTrigger.isUp << endl;
  auto keyCode = inputTrigger.keyCode;
  auto isUp = inputTrigger.isUp;
  auto profile = getProfile(); // profile is guaranteed exist, at least the default profile
  cout << "Current Profile " << profile->id << " " << profile->name << endl;
  Trigger currentTrigger;
  currentTrigger.id = -1;
  for (const auto& trigger: config.triggers){
    if (getKeyCodeFromString(trigger.key) == keyCode){
      currentTrigger = trigger;
      break;
    }
  }
  if (currentTrigger.id == -1){
    return false;
  }
  cout << "Current Trigger: " << currentTrigger.id << " " << currentTrigger.key << endl;
  // Check if a valid profile is found
  // if (!activeProfile.name.empty()) {
  //     std::cout << "Matching profile: " << activeProfile.name << std::endl;

  //     // Iterate through the profile's mappings
  //     for (const auto& mapping : activeProfile.mapping) {
  //         if (mapping.triggerId == ) {
  //             std::cout << "Trigger: " << mapping.triggerId
  //                       << " Action ID: " << mapping.actionId << std::endl;

  //             // Perform the mapped action if found
  //             for (const auto& action : actions) {
  //                 if (action.id == mapping.actionId) {
  //                     performAction(action);  // Perform the mapped action
  //                     return true;  // Skip the original key press
  //                 }
  //             }
  //         }
  //     }
  // }
  
  return false;
}