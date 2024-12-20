#include "window.h"

void Window::Refresh()
{
    // for(int x = 0; x<frame.width; x++)
    // {
    //     for(int y = 0; y<frame.height; y++)
    //     {
    //         RGBA col;
    //         col.r = 255;
    //         col.g = 255;
    //         col.b = 255;
    //         col.a = 255;
    //         frame.pixels[(frame.width * y) + x] = col;
    //     }
    // }
    //cout << "frame.width = " << frame.width << "frame.height = " << frame.height << endl;
    RGBA col;
    col.r = 155;
    col.g = 200;
    col.b = 100;
    col.a = 20;
    fill(100, 100, 200, 200, col);


    InvalidateRect(hwnd, NULL, FALSE);
    UpdateWindow(hwnd);
}


void Window::Init()
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
        frame.width = LOWORD(lParam);
        frame.height = HIWORD(lParam);
        //cout << "frame.width = " << frame.width << "frame.height = " << frame.height << endl;


        bmpInfo.bmiHeader.biWidth = frame.width;
        bmpInfo.bmiHeader.biHeight = frame.height;
         
        if (frame.pixels) delete(frame.pixels);
        frame.pixels = new RGBA[frame.width * frame.height];
        
        window.Refresh();

        return 0;
    }
    default:
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
}