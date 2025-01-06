#include "audio_mixer_control.h"

// Function to get the audio session by process ID
ISimpleAudioVolume* GetAudioSessionByPID(DWORD pid) {
    IMMDeviceEnumerator* deviceEnumerator = nullptr;
    CoCreateInstance(__uuidof(MMDeviceEnumerator), nullptr, CLSCTX_ALL, __uuidof(IMMDeviceEnumerator), (void**)&deviceEnumerator);

    IMMDevice* defaultDevice = nullptr;
    deviceEnumerator->GetDefaultAudioEndpoint(eRender, eConsole, &defaultDevice);

    IAudioSessionManager2* sessionManager = nullptr;
    defaultDevice->Activate(__uuidof(IAudioSessionManager2), CLSCTX_ALL, nullptr, (void**)&sessionManager);

    IAudioSessionEnumerator* sessionEnumerator = nullptr;
    sessionManager->GetSessionEnumerator(&sessionEnumerator);

    int sessionCount = 0;
    sessionEnumerator->GetCount(&sessionCount);

    for (int i = 0; i < sessionCount; ++i) {
        IAudioSessionControl* sessionControl = nullptr;
        sessionEnumerator->GetSession(i, &sessionControl);

        IAudioSessionControl2* sessionControl2 = nullptr;
        sessionControl->QueryInterface(__uuidof(IAudioSessionControl2), (void**)&sessionControl2);

        DWORD sessionPID = 0;
        sessionControl2->GetProcessId(&sessionPID);

        if (sessionPID == pid) {
            ISimpleAudioVolume* simpleAudioVolume = nullptr;
            sessionControl2->QueryInterface(__uuidof(ISimpleAudioVolume), (void**)&simpleAudioVolume);

            sessionControl2->Release();
            sessionControl->Release();
            sessionEnumerator->Release();
            sessionManager->Release();
            defaultDevice->Release();
            deviceEnumerator->Release();

            return simpleAudioVolume; // Return the volume control object
        }

        sessionControl2->Release();
        sessionControl->Release();
    }

    sessionEnumerator->Release();
    sessionManager->Release();
    defaultDevice->Release();
    deviceEnumerator->Release();

    return nullptr; // Return null if no session is found for the PID
}

// Function to get the process ID by process name
DWORD GetPIDByProcessName(const std::wstring& processName) {
    DWORD processes[1024], processCount;
    if (!EnumProcesses(processes, sizeof(processes), &processCount)) {
        return 0; // Failed to enumerate processes
    }

    processCount /= sizeof(DWORD); // Get the number of processes

    for (unsigned int i = 0; i < processCount; ++i) {
        if (processes[i] != 0) {
            HANDLE processHandle = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, processes[i]);
            if (processHandle) {
                WCHAR processNameBuffer[MAX_PATH];
                if (GetModuleBaseName(processHandle, nullptr, processNameBuffer, MAX_PATH)) {
                    if (_wcsicmp(processNameBuffer, processName.c_str()) == 0) {
                        CloseHandle(processHandle);
                        return processes[i]; // Return the PID if the name matches
                    }
                }
                CloseHandle(processHandle);
            }
        }
    }

    return 0; // Return 0 if the process is not found
}

// Function to get the mixer volume for a process
float getMixerVolumeByPID(DWORD pid) {
    CoInitialize(nullptr);

    ISimpleAudioVolume* audioVolume = GetAudioSessionByPID(pid);
    if (!audioVolume) {
        CoUninitialize();
        std::wcerr << L"Could not find audio session for PID: " << pid << std::endl;
        return -1.0f; // Return -1 to indicate an error
    }

    float volume = 0.0f;
    audioVolume->GetMasterVolume(&volume); // Retrieve the current volume
    audioVolume->Release();

    CoUninitialize();
    return volume;
}

void mixerVolumeAddByPID(DWORD pid, float value){
    CoInitialize(nullptr);

    ISimpleAudioVolume* audioVolume = GetAudioSessionByPID(pid);
    if (!audioVolume) {
        CoUninitialize();
        std::wcerr << L"Could not find audio session for PID: " << pid << std::endl;
        return;
    }

    float volume = 0.0f;
    audioVolume->GetMasterVolume(&volume); // Retrieve the current volume
    volume += value;
    if (value > 1.0){
      value = 1.0;
    }
    if (value < 0.0){
      value = 0.0;
    }
    audioVolume->SetMasterVolume(value, nullptr); // Set the volume
    audioVolume->Release();

    CoUninitialize();
}


// Function to get the mixer volume for a process
float getMixerVolumeByName(const std::wstring& processName) {
    DWORD pid = GetPIDByProcessName(processName);
    if (pid == 0) {
        std::wcerr << L"Could not find process: " << processName << std::endl;
        return;
    }

    return getMixerVolumeByPID(pid);
}

// Function to add to the mixer volume for a process by name
void mixerVolumeAddByName(const std::wstring& processName, float value) {
    DWORD pid = GetPIDByProcessName(processName);
    if (pid == 0) {
        std::wcerr << L"Could not find process: " << processName << std::endl;
        return;
    }

    mixerVolumeAddByPID(pid, value);
}

// Function to set the mixer volume for a process by name
void setMixerVolumeByName(const std::wstring& processName, float value) {
    DWORD pid = GetPIDByProcessName(processName);
    if (pid == 0) {
        std::wcerr << L"Could not find process: " << processName << std::endl;
        return;
    }

    setMixerVolumeByPID(pid, value);
}


// Function to set the mixer volume for a process
void setMixerVolumeByPID(DWORD pid, float value) {
    CoInitialize(nullptr);
    if (value > 1.0){
      value = 1.0;
    }
    if (value < 0.0){
      value = 0.0;
    }

    ISimpleAudioVolume* audioVolume = GetAudioSessionByPID(pid);
    if (!audioVolume) {
        CoUninitialize();
        std::wcerr << L"Could not find audio session for PID: " << pid << std::endl;
        return;
    }

    audioVolume->SetMasterVolume(value, nullptr); // Set the volume
    audioVolume->Release();

    CoUninitialize();
}


// Function to mute the audio session for a process by PID
void muteMixerByPID(DWORD pid, bool mute) {
    CoInitialize(nullptr);

    ISimpleAudioVolume* audioVolume = GetAudioSessionByPID(pid);
    if (!audioVolume) {
        CoUninitialize();
        std::wcerr << L"Could not find audio session for PID: " << pid << std::endl;
        return;
    }

    audioVolume->SetMute(mute, nullptr); // Mute or unmute the session
    audioVolume->Release();

    CoUninitialize();
}

// Function to mute the audio session for a process by name
void muteMixerByName(const std::wstring& processName, bool mute) {
    DWORD pid = GetPIDByProcessName(processName);
    if (pid == 0) {
        std::wcerr << L"Could not find process: " << processName << std::endl;
        return;
    }

    muteMixerByPID(pid, mute);
}

// Function to get the mute state for a process by PID
bool isMixerMutedByPID(DWORD pid) {
    CoInitialize(nullptr);

    ISimpleAudioVolume* audioVolume = GetAudioSessionByPID(pid);
    if (!audioVolume) {
        CoUninitialize();
        std::wcerr << L"Could not find audio session for PID: " << pid << std::endl;
        return false;
    }

    BOOL isMuted = FALSE;
    audioVolume->GetMute(&isMuted); // Get the current mute state
    audioVolume->Release();

    CoUninitialize();
    return isMuted;
}
// Function to toggle mute for a process by PID
void toggleMuteMixerByPID(DWORD pid) {
    CoInitialize(nullptr);

    ISimpleAudioVolume* audioVolume = GetAudioSessionByPID(pid);
    if (!audioVolume) {
        CoUninitialize();
        std::wcerr << L"Could not find audio session for PID: " << pid << std::endl;
        return;
    }

    BOOL isMuted = FALSE;
    audioVolume->GetMute(&isMuted); // Get the current mute state

    audioVolume->SetMute(!isMuted, nullptr); // Toggle the mute state
    audioVolume->Release();

    CoUninitialize();

    std::wcout << L"Audio session for PID " << pid 
               << (isMuted ? L" unmuted." : L" muted.") << std::endl;
}

// Function to toggle mute for a process by name
void toggleMuteMixerByName(const std::wstring& processName) {
    DWORD pid = GetPIDByProcessName(processName);
    if (pid == 0) {
        std::wcerr << L"Could not find process: " << processName << std::endl;
        return;
    }

    toggleMuteMixerByPID(pid);
}

// Function to get the mute state for a process by name
bool isMixerMutedByName(const std::wstring& processName) {
    DWORD pid = GetPIDByProcessName(processName);
    if (pid == 0) {
        std::wcerr << L"Could not find process: " << processName << std::endl;
        return false;
    }

    return isMixerMutedByPID(pid);
}