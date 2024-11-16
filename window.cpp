#include "window.h"

void Window::Refresh()
{
    if (frame.pixels)
    {
        cout << "bitmapa jest" << endl;
        for(int x=0; x<frame.x/2; x++){
            for(int y=0; y<frame.y/2; y++){
                frame.pixels[y*frame.y*4 + x*4] = 0;
            }
        }
    }
    InvalidateRect(hwnd, NULL, FALSE);
    UpdateWindow(hwnd);
}
Window::Window()
{
    hdc_frame = CreateCompatibleDC(hdc);
    bmpInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    bmpInfo.bmiHeader.biWidth = 0;
    bmpInfo.bmiHeader.biHeight = 0;
    bmpInfo.bmiHeader.biPlanes = 1;
    bmpInfo.bmiHeader.biBitCount = 32;
    bmpInfo.bmiHeader.biCompression = BI_RGB;
    bmpInfo.bmiHeader.biSizeImage = 0;
    bmpInfo.bmiHeader.biXPelsPerMeter = 0;
    bmpInfo.bmiHeader.biYPelsPerMeter = 0;
    bmpInfo.bmiHeader.biClrUsed = 0;
    bmpInfo.bmiHeader.biClrImportant = 0;

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

    // case WM_DESTROY:
    //     DestroyWindow(hwnd);
    //     return 0;

    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        hdc_frame = BeginPaint(hwnd, &ps);
        FillRect(hdc_frame, &ps.rcPaint, (HBRUSH) (COLOR_WINDOW+1));
        BitBlt(hdc, 
                ps.rcPaint.left,
                ps.rcPaint.top,
                ps.rcPaint.right - ps.rcPaint.left,
                ps.rcPaint.bottom -ps.rcPaint.top,
                hdc_frame,
                0,
                0,
                SRCCOPY);

        EndPaint(hwnd, &ps);

        return 0;
    }
    case WM_SIZE:
    {
        frame.x = LOWORD(lParam);
        frame.y = HIWORD(lParam);
        cout<<frame.x<<" "<<frame.y<<endl;

        bmpInfo.bmiHeader.biWidth = frame.x;
        bmpInfo.bmiHeader.biHeight = frame.y;
        static BITMAPINFO bmpinfo;

        if(bitmap) DeleteObject(bitmap);
        bitmap = CreateDIBitmap(NULL, &bmpinfo.bmiHeader, DIB_RGB_COLORS, &frame.pixels, &bmpInfo, DIB_RGB_COLORS);
        SelectObject(hdc_frame, bitmap);

        return 0;
    }

    }

    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}