#pragma once
#include "../pch.h"
#include "window.h"
#include "timer.h"

class App
{
public:
	App();

	WPARAM Go();

private:
	void DoFrame();

private:
	window m_Wnd;
	
//check timer.h for this define
#ifdef WINDOWS_TIMER
	windowsTimer timer;
#else
	Timer timer;
#endif

};