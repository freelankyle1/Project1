#include "pch.h"
#include "Headers/window.h"



int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	try
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
			while (!w.m_mouse.IsEmpty())
			{
				const auto e = w.m_mouse.Read();
				if (e.GetType() == kMouse::Event::Type::Move)
				{
					std::ostringstream oss;
					oss << "Mouse Position: (" << e.GetPosX() << "," << e.GetPosY() << ")";
					w.SetTitle(oss.str());
				}
			}
			if (w.kbd.KeyIsPressed(VK_SPACE))
			{
				MessageBoxA(nullptr, "Something happon!", "Space Key Was Pressed!", MB_ICONEXCLAMATION);
			}
		}
		
		return msg.wParam;
	}
	catch (const parentException& e)
	{
		MessageBox(nullptr, e.what(), e.getType(), MB_OK | MB_ICONEXCLAMATION);
	}
	catch (const std::exception& e)
	{
		MessageBox(nullptr, e.what(), "Standard Exception", MB_OK | MB_ICONEXCLAMATION);
	}
	catch (...)
	{
		MessageBox(nullptr, "No details available", "unknown exception", MB_OK | MB_ICONEXCLAMATION);
	}
}


