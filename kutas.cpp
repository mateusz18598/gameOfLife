#include <iostream>
#include <windows.h>

#define UNICODE

using namespace std;
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_CLOSE:
    	{
    		cout << "WM_CLOSE" << endl;
    		DestroyWindow(hwnd);
    		return 0;
    	}
    case WM_DESTROY:
	    {
	    	cout << "WM_DESTROY" << endl;
	        PostQuitMessage(0);
	        return 0;	    }
    break;
	}
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}



int main()
{
	// Register the window class.
	const char* class_name = "main";

	WNDCLASS wc = { };

	wc.lpfnWndProc   = WindowProc;
	wc.hInstance     = GetModuleHandle(NULL);
	wc.lpszClassName = class_name;

	if (!RegisterClass(&wc)) cout << "Failed to register class" << endl;

	HWND hwnd = CreateWindowEx(
    0,                              // Optional window styles.
    class_name,                     // Window class
    "gra zycia",    // Window text
    WS_OVERLAPPEDWINDOW,            // Window style

    // Size and position
    CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,

    NULL,       // Parent window    
    NULL,       // Menu
    GetModuleHandle(NULL),  // Instance handle
    NULL        // Additional application data
    );
    if (!hwnd) cout << "nie udalo sie" << endl;

	if (hwnd == NULL)
	{
	    return 0;
	}
	ShowWindow(hwnd, SW_SHOW);

	MSG msg;
	while(1)
	{
		if (!GetMessage(&msg, NULL, 0, 0)) break;
		DispatchMessage(&msg);
	};
}