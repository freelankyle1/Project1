#pragma once
#include "pch.h"

namespace keys
{
	struct KeysData
	{
		float translationX = 0.0f;
		float translationY = 0.0f;
		float translationZ = 0.0f;
		float rotationY = 0.0f;
	};

	void Init();
	void ProcessKeyDown(bool prevKeyState, bool transitionState, char keyCode);
	void ProcessKeyUp(bool prevKeyState, bool transitionState, char keyCode);
	bool IsKeyPressed(char keyCode);
	void Update(KeysData& keysdata);

	void ButtonDown(unsigned short whichButton);
	void ButtonUp(unsigned short whichButton);
	bool IsButtonPressed(unsigned short whichButton);
	void ResetMouseState();

	
	void Shutdown();
}