#include "config.h"
#include "../utils/utils.h"

OptimizedTrigger *registerOptimizedTrigger(Trigger *trigger)
{
  auto optimizedTrigger = new OptimizedTrigger;
  optimizedTrigger->trigger = trigger;
  optimizedTrigger->keyCode = getKeyCodeFromString(trigger->key);
  optimizedTrigger->index = optimizedTriggers.size();
  optimizedTriggers.push_back(*optimizedTrigger);
  return optimizedTrigger;
}

OptimizedAction *registerOptimizedAction(Action *action)
{
  auto optimizedAction = new OptimizedAction;
  optimizedAction->action = action;
  optimizedAction->type = action->type;
  optimizedAction->index = optimizedActions.size();
  switch (optimizedAction->type)
  {
    case ActionType::SIMPLE:
      for (auto &key : action->simple.keys)
      {
        auto keyCode = getKeyCodeFromString(key);
        optimizedAction->keyCodes.push_back(keyCode);
      }
      break;
    case ActionType::PROFILE_SHIFT:
      break;
    case ActionType::MACRO:
      auto macro = action->macro;
      optimizedAction->macroRepeatDelayMs = macro.repeatDelayMs;
      optimizedAction->macroRepeatMode = macro.repeatMode;

      for (auto &macroItem : macro.items)
      {
        auto optimizedMacroItem = new OptimizedMacroItem;
        optimizedMacroItem->key = macroItem.key;
        optimizedMacroItem->up = macroItem.up;
        optimizedMacroItem->delayMs = macroItem.delayMs;
        optimizedMacroItem->keyCode = getKeyCodeFromString(macroItem.key);
        optimizedAction->optimizedMacroItems.push_back(*optimizedMacroItem);
      }
      if (optimizedAction->macroRepeatMode != MacroRepeatMode::NONE && optimizedAction->macroRepeatDelayMs > 0)
      {
        auto optimizedMacroItem = new OptimizedMacroItem;
        optimizedMacroItem->delayMs = optimizedAction->macroRepeatDelayMs;
        optimizedAction->optimizedMacroItems.push_back(*optimizedMacroItem);
      }
      break;
  }
  optimizedActions.push_back(*optimizedAction);
  return optimizedAction;
}

void optimizeTriggers()
{
  cout << "Optimizing Triggers" << endl;
  for (auto &trigger : config.triggers)
  {
    auto optimizedTrigger = registerOptimizedTrigger(&trigger);
    cout << "Trigger: " << optimizedTrigger->index << " " << optimizedTrigger->trigger->name << endl;
  }
}

void optimizeActions()
{

  cout << "Optimizing Actions" << endl;
  for (auto &action : config.actions)
  {
    auto optimizedAction = registerOptimizedAction(&action);
    cout << "Action: " << optimizedAction->index << " " << optimizedAction->action->name << endl;
  }
  macroActionThreads.resize(optimizedActions.size());
}

void optimizeProfiles()
{
  cout << "Optimizing Profiles" << endl;
  for (auto &profile : config.profiles)
  {
    auto optimizedProfile = new OptimizedProfile;
    optimizedProfile->profile = &profile;
    for (const auto &programName : profile.programNames)
    {
      optimizedProfile->lowerCaseProgramNames.push_back(lowerCaseString(programName));
    }
    for (auto &mapping : profile.mapping)
    {
      auto optimizedMapping = new OptimizedMapping;
      optimizedMapping->mapping = &mapping;
      auto triggerName = mapping.triggerName;
      auto actionName = mapping.actionName;
      int triggerIndex = getTriggerIndexByName(triggerName);
      if (triggerIndex < 0 || triggerIndex > optimizedTriggers.size())
      {
        cout << "Invalid trigger index: " << triggerIndex << " for: " << triggerName << " -> " << actionName << endl;
        continue;
      }
      optimizedMapping->triggerIndex = triggerIndex;
      int actionIndex = getActionIndexByName(actionName);
      if (actionIndex < 0 || actionIndex > optimizedActions.size())
      {
        cout << "Invalid action index: " << actionIndex << " for: " << actionName << " -> " << actionName << endl;
        continue;
      }
      optimizedMapping->actionIndex = actionIndex;
      optimizedProfile->optimizedMapping.push_back(*optimizedMapping);

      cout << mapping.triggerName << " -> " << mapping.actionName << " 7 " << optimizedTriggers[triggerIndex].keyCode << endl;
      optimizedProfile->actionIdMap[optimizedTriggers[triggerIndex].keyCode] = actionIndex;
    }
    optimizedProfile->index = optimizedProfiles.size();
    optimizedProfiles.push_back(*optimizedProfile);
    cout << "Profile: " << optimizedProfile->index << " " << optimizedProfile->profile->name << endl;
  }
}

void registerAutoTriggerAndActions()
{
  for (auto &profile : config.profiles)
  {
    for (auto &mapping : profile.mapping)
    {
      auto triggerIndex = getTriggerIndexByName(mapping.triggerName);
      if (triggerIndex <= NO_TRIGGER_FLAG)
      {
        auto autoKeyCode = getKeyCodeFromString(mapping.triggerName);
        if (autoKeyCode > NO_KEYCODE_FLAG)
        {
          auto trigger = new Trigger;
          trigger->key = mapping.triggerName;
          trigger->name = mapping.triggerName;
          auto optimizedTrigger = registerOptimizedTrigger(trigger);
          cout << "Auto create trigger: " << optimizedTrigger->index << ". " << optimizedTrigger->trigger->name << endl;
        }
      }
      auto actionIndex = getActionIndexByName(mapping.actionName);
      if (actionIndex <= NO_ACTION_FLAG)
      {
        auto autoKeyCode = getKeyCodeFromString(mapping.actionName);
        if (autoKeyCode > NO_KEYCODE_FLAG)
        {
          auto action = new Action;
          action->type = ActionType::SIMPLE;
          action->simple.keys.push_back(mapping.actionName);
          action->name = mapping.actionName;
          auto optimizedAction = registerOptimizedAction(action);
          cout << "Auto create action: " << optimizedAction->index << ". " << optimizedAction->action->name << endl;
        }
      }
    }
  }
}

void optimizeProfileInheritance()
{
  for (auto &optimizedProfile : optimizedProfiles){
    optimizedProfile.parentIndex = getProfileIndexByName(optimizedProfile.profile->parentName);
  }
  for (auto &optimizedProfile : optimizedProfiles)
  {
    // Work directly with the original actionIdMap
    int *profileActionIdMap = optimizedProfile.actionIdMap;
    auto optimizedProfileReference = &optimizedProfile;
    while (optimizedProfileReference->parentIndex != NO_PROFILE_FLAG)
    {
      optimizedProfileReference = &optimizedProfiles[optimizedProfileReference->parentIndex];
      int *currentActionIdMap = optimizedProfileReference->actionIdMap;
      for (int i = 0; i < 256; i++)
      {
        if (profileActionIdMap[i] == TERMINATE_ACTION_FLAG)
        {
          continue;
        }
        if (profileActionIdMap[i] > NO_ACTION_FLAG)
        {
          continue;
        }
        profileActionIdMap[i] = currentActionIdMap[i];
      }
    }
    if (rootProfileIndex != NO_PROFILE_FLAG){
      optimizedProfileReference = &optimizedProfiles[rootProfileIndex];
      int *currentActionIdMap = optimizedProfileReference->actionIdMap;
      for (int i = 0; i < 256; i++)
      {
        if (profileActionIdMap[i] == TERMINATE_ACTION_FLAG)
        {
          continue;
        }
        if (profileActionIdMap[i] > NO_ACTION_FLAG)
        {
          continue;
        }
        profileActionIdMap[i] = currentActionIdMap[i];
      }
    }
  }
}

void optimizeConfig()
{
  optimizeTriggers();
  optimizeActions();
  registerAutoTriggerAndActions();
  optimizeProfiles();
  optimizeProfileInheritance();
  for (auto &optimizedAction : optimizedActions)
  {
    auto profileName = optimizedAction.action->profileShift.profileName;
    if (!profileName.empty())
    {
      optimizedAction.profileIndex = getProfileIndexByName(profileName);
    }
  }
  defaultProfileIndex = getProfileIndexByName(config.defaultProfileName);
  rootProfileIndex = getProfileIndexByName(config.rootProfileName);
  debugOptimizedConfig();
  isMacroActionThreadRunnings.resize(optimizedActions.size());
}