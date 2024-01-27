#include "pch.h"
#include "Headers/app.h"
#include "Headers/timer.h"

App::App()
	: m_Wnd(1280,720,"Kyles dungeon")
{}

WPARAM App::Go()
{
	while (true)
	{
		if (const auto ecode = window::ProcessMessages())
		{
			return *ecode;
		}
		DoFrame();
	}

}

std::ostringstream oss;
std::string t;
float rotate = 0.0f;
float moveX = 0.0f;
float moveY = 0.0f;
float moveZ = 0.0f;
void App::DoFrame()
{

	timer.Tick();

	oss << timer.CurrTime();

	t = oss.str();
	const char* t1 = t.c_str();

	oss << "\n";

	const float c = sin(timer.CurrTime()) / 2.0f + 0.5f;
	m_Wnd.Gfx().ClearBuffer(0.0f, 0.0f, 0.0f);


	m_Wnd.Gfx().DrawTestTriangle(rotate, m_Wnd.m_mouse.GetPosX() / (1280.0f / 2) - 1.0f, -m_Wnd.m_mouse.GetPosY() / 360.0f + 1.0f, c);
	m_Wnd.Gfx().EndFrame();

	rotate += 0.005f;
	
}
