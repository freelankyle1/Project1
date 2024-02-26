#pragma once
#include "pch.h"
#include "window.h"
#include "timer.h"
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
	Renderer2D* renderer;

	
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