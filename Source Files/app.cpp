#include "Headers/pch.h"
#include "Headers/app.h"
#include "Headers/timer.h"
#include "Headers/Rendering/shader.h"
#include "Headers/Rendering/box.h"
#include "Headers/Rendering/triangle2d.h"
#include "Headers/Rendering/quad2d.h"
#include <random>

#include "Headers/keys.h"


//currently all the bindables are allocated on the stack and thats why we only
//see 1 cube.
//we need to allocate all of the bindables on the heap using unique_ptr

App::App()
	: m_Wnd(SCREEN_WIDTH,SCREEN_HEIGHT,"Kyles dungeon")
{
	m_Wnd.Gfx().SetProjection(DirectX::XMMatrixPerspectiveLH(1.0f, (float)SCREEN_HEIGHT / (float)SCREEN_WIDTH, 0.25f, 100.0f));
	renderer = new Renderer2D(m_Wnd.Gfx());

	VertexData dataArr[3];

	for (float y = 5.0f; y > -5.5f; y -= 0.1f)
	{
		for (float x = -10.0f; x < 10.0f; x += 0.1f)
		{
			dataArr[0].pos = DirectX::XMFLOAT3(x,       y,       0.0f);
			dataArr[1].pos = DirectX::XMFLOAT3(x + 0.1, y + 0.1, 0.0f);
			dataArr[2].pos = DirectX::XMFLOAT3(x + 0.1, y,       0.0f);

			renderer->Submit(std::make_shared<Triangle2D>(m_Wnd.Gfx(), dataArr));
		}
	}

	renderer->StartBatch();
}

App::~App()
{
	renderer->Shutdown();
	delete renderer;
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


keys::KeysData keysdata;

void App::DoFrame()
{
	timer1.Tick();
	startFrame = timer1.CurrTime();

	keys::Update(keysdata);

	m_Wnd.Gfx().ClearBuffer(0.0f, 0.0f, 0.0f);
	renderer->Update(keysdata.translationX, 0.0f, keysdata.translationZ);
	renderer->Flush();
	m_Wnd.Gfx().EndFrame();


	//debugging purposes / performance
	int PolyCount = renderer->GetVertexAmount() / 3;

	timer1.GetFPS(startFrame, PolyCount);
}
