#include "Headers/pch.h"
#include "Headers/window.h"

window::windowClass window::windowClass::wndClass;

window::windowClass::windowClass()
	: m_hInstance(GetModuleHandle(nullptr))
{


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
    m_wc.hbrBackground = (HBRUSH)BLACK_BRUSH;
    m_wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    m_wc.lpszClassName = getName();
    m_wc.hIconSm = nullptr;


    // register the window class
    if (!(RegisterClassEx(&m_wc)))
    {
        throw(parentLastExcept());
    }

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

//window stuff
//******************************************************************************************************
//******************************************************************************************************
//******************************************************************************************************


window::window(int width, int height, const char* name)
    : m_width(width), m_height(height), m_name(name), m_hWnd(0)
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


    m_hWnd = CreateWindowA(
        window::windowClass::getName(), name,
        WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU,
        CW_USEDEFAULT, CW_USEDEFAULT, 
        rc.right - rc.left, rc.bottom - rc.top,
        nullptr, nullptr, windowClass::getInstance(), this
    );

    
    if (m_hWnd == nullptr)
        throw parentLastExcept();
       
    ShowWindow(m_hWnd, SW_SHOWDEFAULT);

    m_gfx = std::make_unique<Graphics>(m_hWnd);
}

window::~window()
{
    DestroyWindow(m_hWnd);
}

void window::SetTitle(const std::string& title)
{
    if (SetWindowText(m_hWnd, title.c_str()) == 0)
    {
        throw parentLastExcept();
    }
}

std::optional<int> window::ProcessMessages()
{
    MSG msg = { 0 };

    while (PeekMessageA(&msg, nullptr, 0, 0, PM_REMOVE))
    {
        if (msg.message == WM_QUIT)
        {
            return msg.wParam;
        }

        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
      
    return {};
}

Graphics& window::Gfx()
{
    return *m_gfx;
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
        PostQuitMessage(0);
        return 0;

    case WM_KILLFOCUS:
        kbd.ClearState();
        break;

    case (WM_MOUSEMOVE):
    {
        const POINTS pt = MAKEPOINTS(lParam);

        if (pt.x >= 0 && pt.x < m_width && pt.y >= 0 && pt.y < m_height)
        {
            m_mouse.OnMouseMove(pt.x, pt.y);
            if (!m_mouse.IsInWindow())
            {
                SetCapture(hWnd);
                m_mouse.OnMouseEnter();
            }

        }
        else
        {
            if (wParam & (MK_LBUTTON | MK_RBUTTON))
            {
                m_mouse.OnMouseMove(pt.x, pt.y);
            }
            else
            {
                ReleaseCapture();
                m_mouse.OnMouseLeave();
            }
        }

        break;
    }
    case (WM_LBUTTONDOWN):
    {
        const POINTS pt = MAKEPOINTS(lParam);
        m_mouse.OnLeftPressed(pt.x, pt.y);
        break;
    }
    case (WM_RBUTTONDOWN):
    {
        const POINTS pt = MAKEPOINTS(lParam);
        m_mouse.OnRightPressed(pt.x, pt.y);
        break;
    }
    case (WM_LBUTTONUP):
    {
        const POINTS pt = MAKEPOINTS(lParam);
        m_mouse.OnLeftReleased(pt.x, pt.y);
        break;
    }
    case (WM_RBUTTONUP):
    {
        const POINTS pt = MAKEPOINTS(lParam);
        m_mouse.OnRightReleased(pt.x, pt.y);
        break;
    }
    case (WM_MOUSEWHEEL):
    {
        const POINTS pt = MAKEPOINTS(lParam);
        if (GET_WHEEL_DELTA_WPARAM(wParam) > 0)
        {
            m_mouse.OnWheelUp(pt.x, pt.y);
        }
        else if (GET_WHEEL_DELTA_WPARAM(wParam) < 0)
        {
            m_mouse.OnWheelDown(pt.x, pt.y);
        }
        break;
    }

    
    case(WM_KEYDOWN):

    case(WM_SYSKEYDOWN):
        if (!(lParam & 0x40000000) || kbd.AutorepeatIsEnabled())
        {
            kbd.OnKeyPressed(static_cast<unsigned char>(wParam));
        }
        break;
    case(WM_KEYUP):
    case(WM_SYSKEYUP):
        kbd.OnKeyReleased(static_cast<unsigned char>(wParam));
        break;
    case(WM_CHAR):
        kbd.OnChar(static_cast<unsigned char>(wParam));
        break;
    }
    return DefWindowProc(hWnd, msg, wParam, lParam);
}


HWND window::getHandle() const
{
    return m_hWnd;
}


//window exception stuff
//******************************************************************************************************

window::Exception::Exception(int line, const char* file, HRESULT hr) noexcept
    : parentException(line, file), m_hr(hr)
{}

const char* window::Exception::what() const noexcept
{
    std::ostringstream oss;
    oss << getType() << std::endl
        << "[Error Code] " << getErrorCode() << std::endl
        << "[Description] " << getErrorString() << std::endl
        << getOriginString();
    whatBuffer = oss.str();
    return whatBuffer.c_str();
}

const char* window::Exception::getType() const noexcept
{
    return "My window Exception";
}

std::string window::Exception::translateErrorCode(HRESULT hr) noexcept
{
    char* src = nullptr;

    DWORD msgLen = FormatMessageA(
        FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, nullptr,
        hr, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
        reinterpret_cast<LPSTR> (&src), 0, nullptr);

    
    if (msgLen == 0)
        return "Unidentified error code";

    std::string errorString = src;
    LocalFree(src);
    return errorString;
}

HRESULT window::Exception::getErrorCode() const noexcept
{
    return m_hr;
}

std::string window::Exception::getErrorString() const noexcept
{
    return translateErrorCode(m_hr);
}