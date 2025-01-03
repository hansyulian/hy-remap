#include <windows.h>
#include "utils.h"

void runProgram(const string& path){  
    // Convert string to wstring (wide string)
    wstring widePath(path.begin(), path.end());

    // Convert the wstring to LPWSTR (wchar_t*) for CreateProcess
    const wchar_t* program = widePath.c_str();

    // Initialize the STARTUPINFOW (wide version of STARTUPINFO) and PROCESS_INFORMATION structures
    STARTUPINFOW si = { sizeof(STARTUPINFOW) };  // Use the wide version of STARTUPINFO
    PROCESS_INFORMATION pi;

    // Use CreateProcessW (Unicode version) to handle wide character strings
    if (CreateProcessW(NULL, (LPWSTR)program, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi)) {
        wcout << L"Program opened successfully!" << endl;
        
        // Don't wait for the process to finish. Close handles to clean up.
        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);
    } else {
        wcerr << L"Failed to open the program." << endl;
    }
}