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

// Retrieves the audio session by process ID
ISimpleAudioVolume* GetAudioSessionByPID(DWORD pid);

// Retrieves the process ID by process name
DWORD GetPIDByProcessName(const std::wstring& processName);

// Retrieves the mixer volume for a process by PID
float getMixerVolumeByPID(DWORD pid);

// Adds to the mixer volume for a process by PID
void mixerVolumeAddByPID(DWORD pid, float value);

// Sets the mixer volume for a process by PID
void setMixerVolumeByPID(DWORD pid, float value);

// Retrieves the mixer volume for a process by name
float getMixerVolumeByName(const std::wstring& processName);

// Adds to the mixer volume for a process by name
void mixerVolumeAddByName(const std::wstring& processName, float value);

// Sets the mixer volume for a process by name
void setMixerVolumeByName(const std::wstring& processName, float value);
// Mute or unmute the audio session for a process by PID
void muteMixerByPID(DWORD pid, bool mute);

// Mute or unmute the audio session for a process by name
void muteMixerByName(const std::wstring& processName, bool mute);

// Check if the audio session is muted for a process by PID
bool isMixerMutedByPID(DWORD pid);

// Check if the audio session is muted for a process by name
bool isMixerMutedByName(const std::wstring& processName);
// Toggle mute for a process by PID
void toggleMuteMixerByPID(DWORD pid);

// Toggle mute for a process by name
void toggleMuteMixerByName(const std::wstring& processName);

#endif // AUDIO_MIXER_CONTROL_H
