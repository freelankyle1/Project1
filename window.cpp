#include "pch.h"
#include "Headers/window.h"

window::windowClass window::windowClass::wndClass;

window::windowClass::windowClass()
	: m_hInstance(GetModuleHandle(nullptr))
{

    WNDCLASSEX m_wc;


    // clear out the window class for use
    ZeroMemory(&m_wc, sizeof(WNDCLASSEX));

    // fill in the struct with the needed information
    m_wc.cbSize = sizeof(WNDCLASSEX);
    m_wc.style = CS_HREDRAW | CS_VREDRAW;
    m_wc.lpfnWndProc = HandleMsgSetup;
    m_wc.cbClsExtra = 0;
    m_wc.cbWndExtra = 0;
    m_wc.hInstance = getInstance();
    m_wc.hIcon = nullptr;
    m_wc.hbrBackground = nullptr;
    m_wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    m_wc.lpszClassName = getName();
    m_wc.hIconSm = nullptr;


    // register the window class
    RegisterClassEx(&m_wc);

}

window::windowClass::~windowClass()
{
    UnregisterClass(m_wndClassName, getInstance());
}

HINSTANCE window::windowClass::getInstance()
{
    return wndClass.m_hInstance;
}

const char* window::windowClass::getName() noexcept
{
    return m_wndClassName;
}


//******************************************************************************************************
//******************************************************************************************************
//******************************************************************************************************
//******************************************************************************************************
//******************************************************************************************************

window::window(int width, int height, const char* name)
    : m_width(width), m_height(height), m_name(name)
{
    //the rect structure defines a rectangle by the coordinates of its
    //upper left and lower right corners
    RECT rc;

    rc.left = 100;
    rc.top = 100;
    rc.right = rc.left + width;
    rc.bottom = rc.top + height;

    //adjusts the window to how we want it
    //specify the styles...Caption   +  border   +  Minimizebox   No menu
    AdjustWindowRect(&rc, WS_CAPTION | WS_BORDER | WS_MINIMIZEBOX | WS_SYSMENU, FALSE);

    m_hWnd = CreateWindow(
        windowClass::getName(), name,
        WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU,
        CW_USEDEFAULT, CW_USEDEFAULT, 
        rc.right - rc.left, rc.bottom - rc.top,
        nullptr, nullptr, windowClass::getInstance(), this
    );

    ShowWindow(m_hWnd, SW_SHOWDEFAULT);

}

window::~window()
{
    DestroyWindow(m_hWnd);
}

LRESULT CALLBACK window::HandleMsgSetup(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept
{
    // use create parameter passed in from Createwindow() to store window class pointer at WinAPI side
    if (msg == WM_NCCREATE)
    {
        // extract ptr to window class from creation data
        const CREATESTRUCTW* const pCreate = reinterpret_cast<CREATESTRUCTW*>(lParam);
        window* const pWnd = static_cast<window*>(pCreate->lpCreateParams);
        // set WinAPI-managed user data to store ptr to window instance
        SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pWnd));
        // set message proc to normal (non-setup) handler now that setup is finished
        SetWindowLongPtr(hWnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(&window::HandleMsgThunk));
        // forward message to window instance handler
        return pWnd->HandleMsg(hWnd, msg, wParam, lParam);
    }
    // if we get a message before the WM_NCCREATE message, handle with default handler
    return DefWindowProc(hWnd, msg, wParam, lParam);
}

LRESULT CALLBACK window::HandleMsgThunk(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept
{
    // retrieve ptr to window instance
    window* const pWnd = reinterpret_cast<window*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
    // forward message to window instance handler
    return pWnd->HandleMsg(hWnd, msg, wParam, lParam);
}

LRESULT window::HandleMsg(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept
{
    switch (msg)
    {
    case(WM_CLOSE):
    {
        PostQuitMessage(0);
        return 0;

    }break;
    case(WM_KEYDOWN):
    {
        //SetWindowText(hWnd, "pressingdown!");

    }break;
    case(WM_KEYUP):
    {
        //SetWindowText(hWnd, "pressingup!");

    }break;
    case(WM_CHAR):
    {
        
    }break;
    }
    return DefWindowProc(hWnd, msg, wParam, lParam);
}


HWND window::getHandle() const
{
    return m_hWnd;
}
