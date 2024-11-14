#include "window.h"

#define UNICODE

int main()
{
    Window wnd = Window();

    MSG msg;
	while(1)
	{
		if (!GetMessage(&msg, NULL, 0, 0)) break;
		DispatchMessage(&msg);
		wnd.Refresh();
	};
}