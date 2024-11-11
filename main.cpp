#include <iostream>
#include <windows.h>

#define UNICODE

int main()
{
    // Register the window class.
    const char* class_name = "chuj";
    const wchar_t CLASS_NAME[]  = L"Sample Window Class";

    WNDCLASS wc = { };

    wc.lpfnWndProc   = NULL;
    wc.hInstance     = GetModuleHandle(NULL);
    wc.lpszClassName = class_name;

    RegisterClass(&wc);

    HWND hwnd = CreateWindowEx(
    0,                              // Optional window styles.
    class_name,                     // Window class
    "mammamia",    // Window text
    WS_OVERLAPPEDWINDOW,            // Window style

    // Size and position
    CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,

    NULL,       // Parent window
    NULL,       // Menu
    GetModuleHandle(NULL),  // Instance handle
    NULL        // Additional application data
    );

    if (hwnd == NULL)
    {
        return 0;
    }
    ShowWindow(hwnd, SW_SHOW);
}