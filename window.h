#pragma once
#include <iostream>
#include <windows.h>
#include <wingdi.h>
#include <algorithm>
#include "render.h"

using namespace std;

struct Frame
{
    int width, height;
    RGBA *pixels = 0;
};

static BITMAPINFO bmpInfo;
static HBITMAP bitmap = 0;
static Frame frame;
static HWND hwnd;

static LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);



class Window
{
private:
public:
    Window();
    void Refresh();
};
static Window window;