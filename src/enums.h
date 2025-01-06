#ifndef ENUMS
#define ENUMS

enum ActionType {
    SIMPLE,
    PROFILE_SHIFT,
    MACRO,
    RUN_PROGRAM,
    AUDIO_MIXER,
};

enum MacroRepeatMode{
    NONE,
    HOLD,
    TOGGLE,
};

enum AudioMixerControlType{
    SET,
    ADD,
    TOGGLE_MUTE,
    MUTE,
    UNMUTE
};

#endif // ENUMS_H
