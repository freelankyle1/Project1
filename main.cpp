#include "pch.h"
#include "Headers/window.h"
#include "Headers/app.h"



int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	
	try {
		return (int)App{}.Go();
	}

	catch (const parentException& e)
	{
		MessageBox(nullptr, e.what(), e.getType(), MB_OK | MB_ICONEXCLAMATION);
		return 0;
	}
	catch (const std::exception& e)
	{
		MessageBox(nullptr, e.what(), "Standard Exception", MB_OK | MB_ICONEXCLAMATION);
		return 0;
	}
	catch (...)
	{
		MessageBox(nullptr, "No details available", "unknown exception", MB_OK | MB_ICONEXCLAMATION);
		return 0;
	}

}


