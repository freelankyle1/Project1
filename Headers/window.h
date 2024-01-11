#pragma once
#include "pch.h"



class window
{
	class windowClass
	{
	public:
		static HINSTANCE getInstance();
		static const char* getName() noexcept;

	private:
		windowClass();
		~windowClass();
		static windowClass wndClass;
		static constexpr const char* m_wndClassName = "Kyles Game Window";
		HINSTANCE m_hInstance;
	};

public:
	window(int width, int height, const char* name);
	~window();
	window(const window&) = delete;
	window operator=(const window&) = delete;

	HWND getHandle() const;
	
private:
	static LRESULT CALLBACK HandleMsgSetup(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
	static LRESULT CALLBACK HandleMsgThunk(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
	LRESULT HandleMsg(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
	
private:
	int m_height;
	int m_width;
	const char* m_name;

	HWND m_hWnd;


};