#include "actions.h"
#include "../modules/audio_mixer_control.h"

void performAudioMixerAction(const OptimizedAction& optimizedAction, const KeyAction& inputTrigger) {
    if (inputTrigger.up){
        return;
    }
    auto value = optimizedAction.action->audioMixer.value;
    auto pid = windowInfoCache.processId;
    if (!optimizedAction.action->audioMixer.processName.empty()){
      pid = getPIDByProcessName(optimizedAction.action->audioMixer.processName);
    }
    if (pid == -1){
      return;
    }
    switch(optimizedAction.action->audioMixer.type){
      case AudioMixerControlType::ADD:
        mixerVolumeAddByPID(pid, value);
        break;
      case AudioMixerControlType::MUTE:
        muteMixerByPID(pid, true);
        break;
      case AudioMixerControlType::UNMUTE:
        muteMixerByPID(pid, false);
        break;
      case AudioMixerControlType::SET:
        setMixerVolumeByPID(pid, value);
        break;
      case AudioMixerControlType::TOGGLE:
        toggleMuteMixerByPID(pid);
        break;
      
    }
}