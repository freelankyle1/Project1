#pragma once
#include "pch.h"
#include "window.h"
#include "timer.h"
#include "Rendering/box.h"
#include "Rendering/renderable2d.h"


class App
{
public:
	App();

	WPARAM Go();

private:
	void DoFrame();

private:
	window m_Wnd;
	std::vector<std::unique_ptr<class Box>> Boxes;
	std::vector<std::unique_ptr<Renderable2D>> m_Renderables;
	
//check timer.h for this define
#ifdef WINDOWS_TIMER
	windowsTimer timer;
#else
	Timer timer;
#endif

};