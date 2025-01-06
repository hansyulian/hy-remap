#ifndef AUDIO_MIXER_CONTROL_H
#define AUDIO_MIXER_CONTROL_H

#include <windows.h>
#include <string>
#include <mmdeviceapi.h>
#include <audiopolicy.h>
#include <psapi.h>
#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
using namespace std;

// Retrieves the audio session by process ID
ISimpleAudioVolume* getAudioSessionByPID(DWORD pid);

// Retrieves the process ID by process name
DWORD getPIDByProcessName(const string& processName);

// Retrieves the mixer volume for a process by PID
float getMixerVolumeByPID(DWORD pid);

// Adds to the mixer volume for a process by PID
void mixerVolumeAddByPID(DWORD pid, float value);

// Sets the mixer volume for a process by PID
void setMixerVolumeByPID(DWORD pid, float value);

// Retrieves the mixer volume for a process by name
float getMixerVolumeByName(const string& processName);

// Adds to the mixer volume for a process by name
void mixerVolumeAddByName(const string& processName, float value);

// Sets the mixer volume for a process by name
void setMixerVolumeByName(const string& processName, float value);
// Mute or unmute the audio session for a process by PID
void muteMixerByPID(DWORD pid, bool mute);

// Mute or unmute the audio session for a process by name
void muteMixerByName(const string& processName, bool mute);

// Check if the audio session is muted for a process by PID
bool isMixerMutedByPID(DWORD pid);

// Check if the audio session is muted for a process by name
bool isMixerMutedByName(const string& processName);
// Toggle mute for a process by PID
void toggleMuteMixerByPID(DWORD pid);

// Toggle mute for a process by name
void toggleMuteMixerByName(const string& processName);

#endif // AUDIO_MIXER_CONTROL_H
