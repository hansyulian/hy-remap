#include "utils.h"

OptimizedProfile* getProfileByName(const string& name) {
    int index = getProfileIndexByName(name);  // Get the index of the Profile by name
    if (index > NO_PROFILE_FLAG) {
        return &optimizedProfiles[index];  // Return the Profile if found
    }
    return nullptr;  // Return nullptr if the Profile is not found
}

int getProfileIndexByName(const string& name){
  for (int i = 0; i < optimizedProfiles.size(); i++){
    if (optimizedProfiles[i].profile->name == name){
      return i;
    }
  }
  return NO_PROFILE_FLAG;
}