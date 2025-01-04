#include "utils.h"

// Function to get key code by string
int getKeyCodeFromString(const string &key)
{
  auto it = keyCodeMap.find(key);
  if (it != keyCodeMap.end())
  {
    return it->second;
  }
  else
  {
    return NO_KEYCODE_FLAG;
  }
}