#include "window.h"

#define UNICODE

int main()
{
	window.Init();

	MSG msg;
	while (1)
	{
		if (!GetMessage(&msg, NULL, 0, 0))
			break;
		DispatchMessage(&msg);
		window.Refresh();
	};
	delete(frame.pixels);
}