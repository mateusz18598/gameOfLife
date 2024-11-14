#include "window.h"

Window::Window()
{
    // Register the window class.
    const char* class_name = "Test";
    const wchar_t CLASS_NAME[]  = L"Sample Window Class";

    WNDCLASS wc = { };

    wc.lpfnWndProc   = WndProc;
    wc.hInstance     = GetModuleHandle(NULL);
    wc.lpszClassName = class_name;

    RegisterClass(&wc);

    HWND hwnd = CreateWindowEx(
    0,                              // Optional window styles.
    class_name,                     // Window class
    "Game of Life",    // Window text
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
        cout<<"Hwnd = NULL"<<endl;
    }
    ShowWindow(hwnd, SW_SHOW);
    UpdateWindow(hwnd);
}

static LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {

    case WM_CLOSE:
    {
        cout << "WM_CLOSE" << endl;
        DestroyWindow(hwnd);
        return 0;
    }
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;

    case WM_PAINT:
    {
        static PAINTSTRUCT ps;
        static HDC hdc = BeginPaint(hwnd, &ps);

        // All painting occurs here, between BeginPaint and EndPaint.
        return 0;
    }
    case WM_SIZE:
    {
        frame.x = LOWORD(lParam);
        frame.y = HIWORD(lParam);
        cout<<frame.x<<" "<<frame.y<<endl;
        return 0;
    }

    }

    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}