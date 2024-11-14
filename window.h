#pragma once
#include <iostream>
#include <windows.h>

using namespace std;

class Window
{
private:
    HDC hdc;
    PAINTSTRUCT ps;
    static LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

    public:
        Window();
};

