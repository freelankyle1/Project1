#include "Headers/pch.h"
#include "Headers/app.h"
#include "Headers/timer.h"
#include "Headers/Rendering/shader.h"
#include "Headers/Rendering/box.h"
#include "Headers/Rendering/triangle2d.h"
#include <random>

#include "Headers/keys.h"


//currently all the bindables are allocated on the stack and thats why we only
//see 1 cube.
//we need to allocate all of the bindables on the heap using unique_ptr

App::App()
	: m_Wnd(SCREEN_WIDTH,SCREEN_HEIGHT,"Kyles dungeon")
{
	/*
	for (int i =0; i < 5; i++)
		Boxes.push_back(std::make_unique<Box>(m_Wnd.Gfx()));
	float fFov = 45.0f;
	float fFovRad = 1.0f / tanf(fFov * 0.5 / 180.0f * 3.14159f);
	*/

	float randomTranslationX = 0.0f;
	float randomTranslationZ = 0.0f;
	for (int i = 0; i < 150; i++)
	{
		std::random_device rd2;
		std::mt19937 mt2(rd2());
		std::uniform_real_distribution<float> distribution2(-20.0f, 15.0f);

		randomTranslationX = distribution2(mt2);

		std::random_device rd3;
		std::mt19937 mt3(rd3());
		std::uniform_real_distribution<float> distribution3(2.5f, 15.0f);


		randomTranslationZ = distribution3(mt3);


		m_Renderables.push_back(std::make_unique<Triangle2D>(m_Wnd.Gfx(), randomTranslationX, 0.0f, randomTranslationZ));
	}

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
std::string trans;

void App::DoFrame()
{
	float translationX = 0.0f;
	float translationZ = 0.0f;
	float rotationY = 0.0f;

	timer.Tick();
	currtime = timer.CurrTime();
	
	m_Wnd.Gfx().ClearBuffer(0.0f, 0.0f, 0.0f);
	
	if (keys::IsKeyPressed(65) != false)
		translationX =  0.045f;
	if (keys::IsKeyPressed(68) != false)
		translationX = -0.045f;
	if (keys::IsKeyPressed(87) != false)
		translationZ = -0.020f;
	if (keys::IsKeyPressed(83) != false)
		translationZ =  0.020f;
	if (keys::IsButtonPressed(0) == true) //is the left button (index 0) pressed
		rotationY =  0.025f;
	if (keys::IsButtonPressed(1) == true) //is the left button (index 0) pressed
		rotationY = -0.025f;

	//TODO: Create a camera interface

	for (const auto& it : m_Renderables)
	{
		it->Bind(m_Wnd.Gfx());
		it->Update(m_Wnd.Gfx(), translationX, translationZ, rotationY);
		m_Wnd.Gfx().DrawIndexed(it->GetIndexCount());
	}

	/*
	for (const auto& it : Boxes)
	{
		it->Update(m_Wnd.Gfx(), currtime);
		it->Draw(m_Wnd.Gfx());
	}
	*/
	m_Wnd.Gfx().EndFrame();

}
