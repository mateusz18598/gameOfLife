#pragma once
#include <iostream>
#include <windows.h>

using namespace std;

struct Frame
{
    int x, y;
    DWORD *pixels;
};


static BITMAPINFO bmpinfo;
static HBITMAP bitmap = 0;

static Frame frame;

static LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

static HDC hdc;
static PAINTSTRUCT ps;
static HWND hwnd;

class Window
{
private:
    public:
        Window();
        void Refresh();
};


