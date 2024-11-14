#pragma once
#include <iostream>
#include <windows.h>

using namespace std;

static LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

class Window
{
private:
    HDC hdc;
    PAINTSTRUCT ps;

    public:
        Window();
};

