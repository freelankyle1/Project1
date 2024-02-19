#pragma once
#include "pch.h"

namespace keys
{
	void Init();
	void ProcessKeyDown(bool prevKeyState, bool transitionState, char keycode);
	void ProcessKeyUp(bool prevKeyState, bool transitionState, char keycode);
	bool IsKeyPressed(char keycode);
	void Shutdown();

	void ButtonDown(bool whichButton);
	void ButtonUp(bool whichButton);
	bool IsButtonPressed(bool whichButton);

	
}