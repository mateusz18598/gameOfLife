#include "window.h"

void Window::Refresh()
{
    InvalidateRect(hwnd, NULL, FALSE);
    UpdateWindow(hwnd);
}
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

    hwnd = CreateWindowEx(
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
        PostQuitMessage(0);
        return 0;
    }

    case WM_DESTROY:
        DestroyWindow(hwnd);
        return 0;

    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);

        // TODO
        // BitBlt(hdc, 
        //         ps.rcPaint.left,
        //         ps.rcPaint.top,
        //         ps.rcPaint.right - ps.rcPaint.left,
        //         ps.rcPaint.bottom - ps.rcPaint.top,
        //         hdc)


        // All painting occurs here, between BeginPaint and EndPaint.
        FillRect(hdc, &ps.rcPaint, (HBRUSH) (COLOR_WINDOW+1));
        EndPaint(hwnd, &ps);

        return 0;
    }
    case WM_SIZE:
    {
        frame.x = LOWORD(lParam);
        frame.y = HIWORD(lParam);
        cout<<frame.x<<" "<<frame.y<<endl;

        bmpinfo.bmiHeader.biWidth = frame.x;
        bmpinfo.bmiHeader.biHeight = frame.y;
        static BITMAPINFO bmpinfo;

        if(bitmap) DeleteObject(bitmap);
        bitmap = CreateDIBitmap(NULL, &bmpinfo.bmiHeader, DIB_RGB_COLORS, &frame.pixels, 0, 0);
        SelectObject(hdc, bitmap);

        return 0;
    }

    }

    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}