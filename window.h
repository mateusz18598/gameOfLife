#pragma once
#include <iostream>
#include <windows.h>
#include <wingdi.h>

using namespace std;

struct Frame
{
    int x, y;
    DWORD* pixels = 0;
};


static BITMAPINFO bmpInfo;
static HBITMAP bitmap = 0;

static Frame frame;

static LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

static HDC hdc;
static HDC hdc_frame;
static PAINTSTRUCT ps;
static HWND hwnd;

class Window
{
private:
    public:
        Window();
        void Refresh();
};


