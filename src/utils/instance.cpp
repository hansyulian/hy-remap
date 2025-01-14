// ... existing includes ...
#include "utils.h"
#include <windows.h>
#include <tlhelp32.h>
#include <psapi.h>

// Add this function before main()
void killOtherInstances() {
    DWORD currentPID = GetCurrentProcessId();
    HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (snapshot == INVALID_HANDLE_VALUE) {
        return;
    }

    PROCESSENTRY32W processEntry = { sizeof(processEntry) };
    if (Process32FirstW(snapshot, &processEntry)) {
        do {
            // Skip our own process
            if (processEntry.th32ProcessID == currentPID) {
                continue;
            }

            // Compare process name with "HyRemap.exe"
            if (_wcsicmp(processEntry.szExeFile, L"HyRemap.exe") == 0) {
                HANDLE process = OpenProcess(PROCESS_TERMINATE, FALSE, processEntry.th32ProcessID);
                if (process) {
                    TerminateProcess(process, 0);
                    CloseHandle(process);
                }
            }
        } while (Process32NextW(snapshot, &processEntry));
    }
    CloseHandle(snapshot);
}