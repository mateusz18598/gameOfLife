#include "window.h"
static Window window;

void Window::Refresh()
{
    // for(int x = 0; x< window->frame.width; x++)
    // {
    //     for(int y = 0; y< window->frame.height; y++)
    //     {
    //         RGBA col;
    //         col.r = 255;
    //         col.g = 255;
    //         col.b = 255;
    //         col.a = 255;
    //          window->frame.pixels[( window->frame.width * y) + x] = col;
    //     }
    // }
    // cout << " window->frame.width = " <<  window->frame.width << " window->frame.height = " <<  window->frame.height << endl;
    RGBA col;
    col.r = 155;
    col.g = 200;
    col.b = 100;
    col.a = 20;
   // fill(100, 100, 200, 200, col);

    InvalidateRect(hwnd, NULL, FALSE);
    UpdateWindow(hwnd);
}

Window:: Window()
{
    Window* window = this;
    window->bmpInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    window->bmpInfo.bmiHeader.biWidth = 0;
    window->bmpInfo.bmiHeader.biHeight = 0;
    window->bmpInfo.bmiHeader.biPlanes = 1;
    window->bmpInfo.bmiHeader.biBitCount = 32;
    window->bmpInfo.bmiHeader.biCompression = BI_RGB;
    window->bmpInfo.bmiHeader.biSizeImage = 0;
    window->bmpInfo.bmiHeader.biXPelsPerMeter = 0;
    window->bmpInfo.bmiHeader.biYPelsPerMeter = 0;
    window->bmpInfo.bmiHeader.biClrUsed = 0;
    window->bmpInfo.bmiHeader.biClrImportant = 0;

    // Register the window class.
    const char *class_name = "Test";
    const wchar_t CLASS_NAME[] = L"Sample Window Class";

    WNDCLASS wc = {};

    wc.lpfnWndProc = WndProc;
    wc.hInstance = GetModuleHandle(NULL);
    wc.lpszClassName = class_name;
    wc.cbWndExtra = sizeof(Window*);

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
        (void*)window                 // Additional application data
    );

    if (hwnd == NULL)
    {
        cout << "Hwnd = NULL" << endl;
    }
   SetWindowLongPtrA(hwnd, 0, (LONG_PTR)window);
    ShowWindow(hwnd, SW_SHOW);
    UpdateWindow(hwnd);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    Window* window = (Window*)GetWindowLongPtrA(hwnd, 0);
    if (!window) return 0;
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

        if ( window->frame.pixels)
        {
            StretchDIBits(
                hdc,
                0, 0, rect.right, rect.bottom,
                0, 0, rect.right, rect.bottom,
                window->frame.pixels,
                &(window->bmpInfo),
                DIB_RGB_COLORS,
                SRCCOPY);
        }
        else
        {
            cout << "nie ma  window->frame.pixels" << endl;
        }

        EndPaint(hwnd, &ps);

        return 0;
    }
    case WM_SIZE:
    {
        if (window != 0)
        {
            window->frame.width = LOWORD(lParam);
            window->frame.height = HIWORD(lParam);
            // cout << " window->frame.width = " <<  window->frame.width << " window->frame.height = " <<  window->frame.height << endl;

            window->bmpInfo.bmiHeader.biWidth =  window->frame.width;
            window->bmpInfo.bmiHeader.biHeight =  window->frame.height;

            if ( window->frame.pixels)
            {
                delete ( window->frame.pixels);
                cout << "deleting frame.pixels..." << endl;
            }
            window->frame.pixels = new RGBA[ window->frame.width *  window->frame.height];

            window->Refresh();
        }
        return 0;
    }
    default:
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
} 