#pragma once
#include "pch.h"
#include "window.h"
#include "timer.h"
#include "Rendering/box.h"
#include "Rendering/renderable2d.h"
#include "Rendering/renderer2d.h"


class App
{
public:
	App();
	~App();

	void Test(float translationX, float translationZ);
	WPARAM Go();

private:
	void DoFrame();

private:
	window m_Wnd;
	std::vector<std::unique_ptr<class Box>> Boxes;
	std::vector<std::unique_ptr<Renderable2D>> m_Renderables;

	Renderer2D* renderer;
	std::shared_ptr<VertexConstant> vconstant;

	
//check timer.h for this define
#ifdef WINDOWS_TIMER
	windowsTimer timer1;
#else
	Timer timer;
#endif
	float currtime = 0.0f;
	float startFrame = 0.0f;
	int frames = 0;

};