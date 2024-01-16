#include "pch.h"
#include "Headers/app.h"
#include "Headers/timer.h"

App::App()
	: m_Wnd(800,600,"Kyles dungeon")
{}

int App::Go()
{
	/*
	MSG msg = { 0 };

	while (msg.message != WM_QUIT)
	{
		while (PeekMessageA(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);

		}
		while (!m_Wnd.m_mouse.IsEmpty())
		{
			const auto e = m_Wnd.m_mouse.Read();
			if (e.GetType() == kMouse::Event::Type::Move)
			{
				std::ostringstream oss;
				oss << "Mouse Position: (" << e.GetPosX() << "," << e.GetPosY() << ")";
				m_Wnd.SetTitle(oss.str());
			}
		}
		DoFrame();
	}
	return msg.wParam;
	*/

	while (true)
	{
		if (const auto ecode = window::ProcessMessages())
		{
			return *ecode;
		}
		DoFrame();
	}
}

void App::DoFrame()
{
	std::ostringstream oss;

	timer.Tick();

	oss << timer.CurrTime();

	std::string t = oss.str();
	const char* t1 = t.c_str();

	OutputDebugString(TEXT(t1));
	OutputDebugString("\n");
	
}
