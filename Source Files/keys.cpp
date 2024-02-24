#include "Headers/pch.h"
#include "Headers/keys.h"


namespace keys
{
	bool* Keys = new bool[256];

	void Init()
	{
		for (int i = 0; i < 256; i++)
		{
			Keys[i] = false;
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
		keysdata.translationZ = 0.0f;
		keysdata.rotationY = 0.0f;

		if (keys::IsKeyPressed(65) != false)
			keysdata.translationX = 0.045f;
		if (keys::IsKeyPressed(68) != false)
			keysdata.translationX = -0.045f;
		if (keys::IsKeyPressed(87) != false)
			keysdata.translationZ = -0.020f;
		if (keys::IsKeyPressed(83) != false)
			keysdata.translationZ = 0.020f;
		if (keys::IsButtonPressed(0) == true) //is the left button (index 0) pressed
			keysdata.rotationY = 0.025f;
		if (keys::IsButtonPressed(1) == true) //is the left button (index 0) pressed
			keysdata.rotationY = -0.025f;
	}


	bool* mouse = new bool[2];

	void ButtonDown(bool whichButton)
	{
		mouse[whichButton] = true;
	}
	void ButtonUp(bool whichButton)
	{
		mouse[whichButton] = false;
	}
	bool IsButtonPressed(bool whichButton)
	{
		return mouse[whichButton];
	}


	void Shutdown()
	{
		delete[] Keys;
		delete[] mouse;
	}
}