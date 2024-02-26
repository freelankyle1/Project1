#include "Headers/pch.h"
#include "Headers/app.h"
#include "Headers/timer.h"
#include "Headers/keys.h"
#include "Headers/Rendering/triangle2d.h"
#include "Headers/Rendering/quad2d.h"
#include <random>


App::App()
	: m_Wnd(SCREEN_WIDTH,SCREEN_HEIGHT,"Kyles dungeon")
{
	m_Wnd.Gfx().SetProjection(DirectX::XMMatrixPerspectiveLH(1.0f, (float)SCREEN_HEIGHT / (float)SCREEN_WIDTH, 0.25f, 100.0f));
	renderer = new Renderer2D(m_Wnd.Gfx());
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
VertexData dataArr[4];


void App::DoFrame()
{
	timer1.Tick();
	startFrame = timer1.CurrTime();
	keys::Update(keysdata);

	renderer->BeginScene();

	for (float y = 5.0f; y > -5.0f; y -= 1.0f)
	{
		for (float x = -10.0f; x < 10.0f; x += 1.0f)
		{
			dataArr[0].pos = DirectX::XMFLOAT3(x,        y,       0.0f);
			dataArr[0].tex = DirectX::XMFLOAT2(0.0f, 1.0f);

			dataArr[1].pos = DirectX::XMFLOAT3(x + 0.95f, y + 0.95f,0.0f);
			dataArr[1].tex = DirectX::XMFLOAT2(1.0f, 0.0f);

			dataArr[2].pos = DirectX::XMFLOAT3(x + 0.95f, y,       0.0f);
			dataArr[2].tex = DirectX::XMFLOAT2(1.0f, 1.0f);

			dataArr[3].pos = DirectX::XMFLOAT3(x,        y + 0.95f,0.0f);
			dataArr[3].tex = DirectX::XMFLOAT2(0.0f, 0.0f);

			renderer->Submit(std::make_shared<Quad2D>(m_Wnd.Gfx(), dataArr));
		}
	}

	
	renderer->Flush();
	renderer->Update(keysdata.translationX, keysdata.translationY, keysdata.translationZ);
	renderer->EndScene();


	keys::ResetMouseState();
	auto [x,y] = renderer->GetStats();
	renderer->EndStats();
	timer1.GetFPS(startFrame, x,y);
}
