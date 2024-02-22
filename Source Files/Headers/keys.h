#pragma once
#include "pch.h"

namespace keys
{
	void Init();
	void ProcessKeyDown(bool prevKeyState, bool transitionState, char keyCode);
	void ProcessKeyUp(bool prevKeyState, bool transitionState, char keyCode);
	bool IsKeyPressed(char keyCode);
	void Shutdown();

	void ButtonDown(bool whichButton);
	void ButtonUp(bool whichButton);
	bool IsButtonPressed(bool whichButton);
}