#include "Headers/pch.h"
#include "Headers/keys.h"


namespace keys
{
	bool* Keys = new bool[256];
	bool* mouse = new bool[4];

	static float mouseWheelDelta = 0.0f;

	void Init()
	{
		for (int i = 0; i < 256; i++)
		{
			Keys[i] = false;
		}
		for (int i = 0; i < 4; i++)
		{
			mouse[i] = false;
		}
	}
	void ProcessKeyDown(bool prevKeyState, bool transitionState, char keyCode)
	{
		Keys[keyCode] = true;
	}
	void ProcessKeyUp(bool prevKeyState, bool transitionState, char keyCode)
	{
		Keys[keyCode] = false;
	}
	bool IsKeyPressed(char keyCode)
	{
		return Keys[keyCode];
	}

	void Update(KeysData& keysdata)
	{
		keysdata.translationX = 0.0f;
		keysdata.translationY = 0.0f;
		keysdata.translationZ = 0.0f;
		keysdata.rotationY = 0.0f;

		if (keys::IsKeyPressed(65) != false)
			keysdata.translationX = 0.045f;
		if (keys::IsKeyPressed(68) != false)
			keysdata.translationX = -0.045f;

		if (keys::IsKeyPressed(87) != false)
			keysdata.translationY = -0.040f;
		if (keys::IsKeyPressed(83) != false)
			keysdata.translationY =  0.040f;

		if (keys::IsButtonPressed(2) != false)
			keysdata.translationZ = -0.25f;

		if (keys::IsButtonPressed(3) != false)
			keysdata.translationZ =  0.25f;
	}


	void ButtonDown(unsigned short whichButton)
	{
		mouse[whichButton] = true;
	}
	void ButtonUp(unsigned short whichButton)
	{
		mouse[whichButton] = false;
	}
	bool IsButtonPressed(unsigned short whichButton)
	{
		return mouse[whichButton];
	}
	void ResetMouseState()
	{
		for (int i = 0; i < 4; i++)
			mouse[i] = false;
	}
	


	void Shutdown()
	{
		delete[] Keys;
		delete[] mouse;
	}
}