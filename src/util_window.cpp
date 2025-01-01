#include "main.h"


string getCurrentWindowTitle(){  
    HWND hwnd = GetForegroundWindow();
    if (!hwnd) {
        // If no active window detected, return the default profile
        return "";
    }

    // Get the window title
    wchar_t windowTitleW[256]; // Wide-character buffer
    if (GetWindowTextW(hwnd, windowTitleW, sizeof(windowTitleW) / sizeof(wchar_t)) == 0) {
        // If unable to retrieve the window title, return the default profile
        return "";
    }
    wstring wideTitle(windowTitleW);
    string windowTitleString(wideTitle.begin(), wideTitle.end());
    return windowTitleString;
}
