#pragma once

#pragma once

#include <iostream>
#include <windows.h>
#include <wingdi.h>
#include <algorithm>
#include "render.h"


using namespace std;

LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

class Window
{
private:
public:
    Window();
    BITMAPINFO bmpInfo;
    HBITMAP bitmap = 0;
    Frame frame;
    HWND hwnd;

    void Init();
    void Refresh();
};
