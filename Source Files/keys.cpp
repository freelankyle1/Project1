#include "Headers/pch.h"


namespace keys
{
	bool* Keys = new bool[256];

	void Init()
	{
		for (int i = 0; i < 256; i++)
		{
			//Keys.push_back(false);
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