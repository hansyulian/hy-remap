#include <windows.h>
#include <mmdeviceapi.h>
#include <audiopolicy.h>
#include <psapi.h>
#include <iostream>

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

// Function to get the mixer volume for a process
float getMixerVolume(DWORD pid) {
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

// Function to set the mixer volume for a process
void setMixerVolume(DWORD pid, float value) {
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
