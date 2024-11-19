#include "window.h"

void Window::Refresh()
{
    for(int x = 0; x<frame.x; x++)
    {
        for(int y = 0; y<frame.y; y++)
        {
            frame.pixels[x*sizeof(uint8_t) * 4 + y] = 255;
            frame.pixels[x*sizeof(uint8_t) * 4 + (y + 1)] = 255;
            frame.pixels[x*sizeof(uint8_t) * 4 + (y + 2)] = 255;
            frame.pixels[x*sizeof(uint8_t) * 4 + (y + 3)] = 255;
        }
    }


    InvalidateRect(hwnd, NULL, FALSE);
    UpdateWindow(hwnd);
}


Window::Window()
{
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
    const char *class_name = "Test";
    const wchar_t CLASS_NAME[] = L"Sample Window Class";

    WNDCLASS wc = {};

    wc.lpfnWndProc = WndProc;
    wc.hInstance = GetModuleHandle(NULL);
    wc.lpszClassName = class_name;

    RegisterClass(&wc);

    hwnd = CreateWindowEx(
        0,                   // Optional window styles.
        class_name,          // Window class
        "Game of Life",      // Window text
        WS_OVERLAPPEDWINDOW, // Window style

        // Size and position
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,

        NULL,                  // Parent window
        NULL,                  // Menu
        GetModuleHandle(NULL), // Instance handle
        NULL                   // Additional application data
    );

    if (hwnd == NULL)
    {
        cout << "Hwnd = NULL" << endl;
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
        RECT rect;
        GetClientRect(hwnd, &rect);
        HDC hdc = BeginPaint(hwnd, &ps);

        if (frame.pixels)
        {
            StretchDIBits(
                hdc,
                0, 0, rect.right, rect.bottom,
                0, 0, rect.right, rect.bottom,
                frame.pixels,
                &bmpInfo,
                DIB_RGB_COLORS,
                SRCCOPY
            );
        }
        else
        {
            cout << "nie ma frame.pixels" << endl;
        }


        EndPaint(hwnd, &ps);

        return 0;
    }
    case WM_SIZE:
    {
        frame.x = LOWORD(lParam);
        frame.y = HIWORD(lParam);

        bmpInfo.bmiHeader.biWidth = frame.x;
        bmpInfo.bmiHeader.biHeight = frame.y;
         
        if (frame.pixels) delete(frame.pixels);
        frame.pixels = new uint8_t[frame.x * frame.y * 4];
        
        // fill(frame.pixels, frame.x * frame.y, frame.x * frame.y * 4, 255);

        return 0;
    }
    default:
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
}