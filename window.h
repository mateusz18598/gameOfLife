#pragma once
#include <iostream>
#include <windows.h>
#include <wingdi.h>
#include <algorithm>

using namespace std;

struct Frame
{
    int x, y;
    uint8_t *pixels = 0;
};

static BITMAPINFO bmpInfo;
static HBITMAP bitmap = 0;

static Frame frame;

static LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

static HWND hwnd;

class Window
{
private:
public:
    Window();
    void Refresh();
};
