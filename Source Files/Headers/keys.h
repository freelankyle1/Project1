#pragma once
#include "pch.h"

namespace keys
{
	struct KeysData
	{
		float translationX = 0.0f;
		float translationZ = 0.0f;
		float rotationY = 0.0f;
	};

	void Init();
	void ProcessKeyDown(bool prevKeyState, bool transitionState, char keyCode);
	void ProcessKeyUp(bool prevKeyState, bool transitionState, char keyCode);
	bool IsKeyPressed(char keyCode);
	void Update(KeysData& keysdata);

	void ButtonDown(bool whichButton);
	void ButtonUp(bool whichButton);
	bool IsButtonPressed(bool whichButton);
	
	void Shutdown();
}