#include "main.h"
#include "main.h"
#include <psapi.h>

WindowInfo getCurrentWindowInfo() {  
    HWND hwnd = GetForegroundWindow();
    WindowInfo info = {};  // Initialize the struct with empty/default values
    info.hwnd = hwnd;
    
    if (!hwnd) {
        // If no active window detected, return default (empty) struct
        return info;
    }

    // Get the window title
    wchar_t windowTitleW[256]; // Wide-character buffer
    if (GetWindowTextW(hwnd, windowTitleW, sizeof(windowTitleW) / sizeof(wchar_t)) == 0) {
        // If unable to retrieve the window title, return default struct
        return info;
    }
    wstring wideTitle(windowTitleW);
    info.name = lowerCaseString(string(wideTitle.begin(), wideTitle.end()));

    // Get process ID
    GetWindowThreadProcessId(hwnd, &info.processId);

    // Get the executable file name (.exe)
    HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, info.processId);
    if (hProcess == NULL) {
        // Unable to open the process, return struct with only window name and process ID
        return info;
    }

    // Get the executable path
    char exePath[MAX_PATH];
    if (GetModuleFileNameExA(hProcess, NULL, exePath, MAX_PATH) == 0) {
        // Unable to get executable path, return struct with only window name and process ID
        CloseHandle(hProcess);
        return info;
    }

    // Close the process handle
    CloseHandle(hProcess);

    // Set executable path in struct
    info.executable = lowerCaseString(exePath);

    // Return the populated struct
    return info;
}