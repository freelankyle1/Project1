#pragma once
#include "pch.h"
#include "window.h"
#include "timer.h"
#include "Rendering/box.h"


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
	
//check timer.h for this define
#ifdef WINDOWS_TIMER
	windowsTimer timer;
#else
	Timer timer;
#endif

};