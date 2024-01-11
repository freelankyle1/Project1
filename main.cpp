#include "pch.h"
#include "Headers/window.h"


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    window w(SCREEN_WIDTH, SCREEN_HEIGHT, "blah");

	MSG msg = { 0 };

	while (msg.message != WM_QUIT)
	{
		while (PeekMessageA(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
	

	//all comments deleted

	return msg.wParam;
}

