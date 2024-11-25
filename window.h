 #ifndef WINDOW
 #define WINDOW


#include <iostream>
#include <windows.h>
#include <wingdi.h>
#include <algorithm>
#include "render.h"

using namespace std;



static BITMAPINFO bmpInfo;
static HBITMAP bitmap = 0;
static Frame frame;
static HWND hwnd;

static LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);



class Window
{
private:
public:
    void Init();
    void Refresh();
};
static Window window;

#endif