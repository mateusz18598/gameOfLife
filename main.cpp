
#include "window.h"
static Window window;
#define UNICODE

int main()
{
	MSG msg;
	while (1)
	{
		if (!GetMessage(&msg, NULL, 0, 0))
			break;
		DispatchMessage(&msg);
		window.Refresh();
	};
}