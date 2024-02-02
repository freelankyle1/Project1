#include "Headers/pch.h"
#include "Headers/app.h"
#include "Headers/timer.h"
#include "Headers/Rendering/shader.h"
#include "Headers/Rendering/box.h"
#include <random>


//currently all the bindables are allocated on the stack and thats why we only
//see 1 cube.
//we need to allocate all of the bindables on the heap using unique_ptr

App::App()
	: m_Wnd(SCREEN_WIDTH,SCREEN_HEIGHT,"Kyles dungeon")
{
	for (int i =0; i < 5; i++)
		Boxes.push_back(std::make_unique<Box>(m_Wnd.Gfx()));
	float fFov = 90.f;
	float fFovRad = 1.0f / tanf(fFov * 0.5 / 180.0f * 3.14159f);
	m_Wnd.Gfx().SetProjection(DirectX::XMMatrixPerspectiveLH(1.0f, (float)SCREEN_HEIGHT / (float)SCREEN_WIDTH, 0.25f, 100.0f));
	
}

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

float currtime = 0.0f;

void App::DoFrame()
{
	timer.Tick();
	currtime = timer.CurrTime();
	
	m_Wnd.Gfx().ClearBuffer(0.0f, 0.0f, 0.0f);
	
	
	for (const auto& it : Boxes)
	{
		it->Update(m_Wnd.Gfx(), currtime);
		it->Draw(m_Wnd.Gfx());
	}
	m_Wnd.Gfx().EndFrame();

}
