#pragma once
#include "pch.h"
#include "d3dexception.h"
#include "keyboard.h"
#include "Mouse.h"

class window
{
	class Exception : public parentException
	{
	public:
		Exception(int line, const char* file, HRESULT hr) noexcept;
		const char* what() const noexcept override;
		virtual const char* getType() const noexcept;
		static std::string translateErrorCode(HRESULT hr) noexcept;
		HRESULT getErrorCode() const noexcept;
		std::string getErrorString() const noexcept;

	public:
		HRESULT m_hr;

	};

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
	void SetTitle(const std::string&);

	HWND getHandle() const;
	
private:
	static LRESULT CALLBACK HandleMsgSetup(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
	static LRESULT CALLBACK HandleMsgThunk(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
	LRESULT HandleMsg(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
	
public:
	Keyboard kbd;
	kMouse m_mouse;

private:
	int m_height;
	int m_width;
	const char* m_name;

	HWND m_hWnd;


};

#define parentExcept(hr) window::Exception(__LINE__, __FILE__, hr)
#define parentLastExcept() window::Exception(__LINE__, __FILE__, GetLastError())