/**********************************************************************
*	Filename: Win32WindowSystem.cpp
*	
*	Copyright (C) 2011, FIFE team
*	http://www.fifengine.net
*
*	This file is part of FIFE.
*
*	FIFE is free software: you can redistribute it and/or modify it
*	under the terms of the GNU Lesser General Public License as
*	published by the Free Software Foundation, either version 3 of
*	the License, or any later version.
*
*	FIFE is distributed in the hope that it will be useful,
*	but WITHOUT ANY WARRANTY; without even the implied warranty of
*	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* 	GNU Lesser General Public License for more details.
*
*	You should have received a copy of the GNU Lesser General Public
*	License along with FIFE. If not, see http://www.gnu.org/licenses/.
***********************************************************************/
#include "PrecompiledIncludes.h"

#include "Win32WindowSystem.h"
#include "../IWindowSystemEventListener.h"
#include "../../inputsystem/IInputSystem.h"
#include "../../inputsystem/KeyCodes.h"
#include "../../inputsystem/keyboard/IKeyEvent.h"
#include "../../inputsystem/keyboard/KeyEvent.h"
#include "../../inputsystem/mouse/IMouseEvent.h"
#include "../../inputsystem/mouse/MouseEvent.h"

// these may not be defined, so define them here if not
#ifndef WM_MOUSEWHEEL
#define WM_MOUSEWHEEL 0x020A
#endif
#ifndef WHEEL_DELTA
#define WHEEL_DELTA 120
#endif

// this may not be defined, so define it here if not
#ifndef MAPVK_VSC_TO_VK_EX
#define MAPVK_VSC_TO_VK_EX 3
#endif

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    Win32WindowSystem* window = 0;

	if (message == WM_NCCREATE)
	{
		LPCREATESTRUCT ptr = reinterpret_cast<LPCREATESTRUCT>(lParam);
		SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG_PTR)ptr->lpCreateParams);
	}
	else
	{
        window = reinterpret_cast<Win32WindowSystem*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
	}

	if (!window)
	{
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	switch (message)
	{
// 	case WM_PAINT:
// 		PAINTSTRUCT ps;
// 		BeginPaint(hWnd, &ps);
// 		EndPaint(hWnd, &ps);
// 		return 0;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
		break;

	case WM_SIZE:
		window->OnResize();
		return 0;

	case WM_ACTIVATE:
	{
		bool active = (LOWORD(wParam) != WA_INACTIVE);
		//window->SetFullScreen(active);
		
        return 0;
	}

    case WM_ACTIVATEAPP:
        if (wParam == TRUE)
        {
            // regained focus, recapture mouse if needed
            if (window->IsMouseCaptured())
            {
                SetCapture(hWnd);
            }
        }
        return 0;

	case WM_GETMINMAXINFO:
		// default to a minimum size
		((MINMAXINFO*)lParam)->ptMinTrackSize.x = 100;
		((MINMAXINFO*)lParam)->ptMinTrackSize.y = 100;
		break;

	case WM_CLOSE:
		window->Destroy();
		return 0;

	case WM_KEYDOWN:
	case WM_KEYUP:
    case WM_SYSKEYDOWN:
    case WM_SYSKEYUP:
        BYTE allKeys[256];

        // get current state of keys
        if (GetKeyboardState(allKeys))
        {
            KeyEvent keyEvent;

            // save key pressed state
            keyEvent.SetKeyPressed((message == WM_KEYDOWN || message == WM_SYSKEYDOWN));

            // get current keyboard layout
            HKL layout = GetKeyboardLayout(0);

            KeyCodes::Enum keyCode = static_cast<KeyCodes::Enum>(wParam);
            
            // get the virtual key from the scan code, lParam bits 16-23 contain the scan code
            uint32_t virtualKey = MapVirtualKeyEx((lParam & 0x00FF0000), MAPVK_VSC_TO_VK_EX, layout);

            // save the key scan code
            keyEvent.SetKeyCode(keyCode);

            if (keyCode == KeyCodes::Shift)
            {
                // figure out which shift, lParam bits 16-23 contain scan code
                keyEvent.SetKeyCode(static_cast<KeyCodes::Enum>(virtualKey));
            }
            else if (keyCode == KeyCodes::Ctrl)
            {
                // check the extended key bit (bit 24) 
                if (lParam & 0x01000000)
                {
                    keyEvent.SetKeyCode(KeyCodes::RCtrl);
                }
                else
                {
                    keyEvent.SetKeyCode(static_cast<KeyCodes::Enum>(virtualKey));
                }
            }
            else if (keyCode == KeyCodes::Alt)
            {
                // check the extended key bit (bit 24)
                if (lParam & 0x01000000)
                {
                    keyEvent.SetKeyCode(KeyCodes::RAlt);
                }
                else
                {
                    keyEvent.SetKeyCode(static_cast<KeyCodes::Enum>(virtualKey));
                }
            }

            // save modifiers
            if (allKeys[KeyCodes::Shift] & 0x80)
            {
                keyEvent.SetModifier(KeyModifiers::Shift);
            }

            if (allKeys[KeyCodes::Ctrl] & 0x80)
            {
                keyEvent.SetModifier(KeyModifiers::Ctrl);
            }

            if (allKeys[KeyCodes::Alt] & 0x80)
            {
                keyEvent.SetModifier(KeyModifiers::Alt);
            }

            // translate virtual key to unicode character(s); could be more than 1
            WCHAR characters[3] = {0};
            uint32_t ret = ToUnicodeEx(virtualKey, HIWORD(lParam), allKeys, characters, 3, 0, layout);

            // default the text to nothing
            keyEvent.SetText(0);

            if (ret == 1)
            {
                // single character case
                keyEvent.SetText(characters[0]);
            }
            else if (ret > 1)
            {
                // TODO - support dead keys and multiple characters
            }

            // call into the window class to handle keyboard input
            window->OnKeyboardInput(keyEvent);

            if (message == WM_SYSKEYDOWN || message == WM_SYSKEYUP)
                return DefWindowProc(hWnd, message, wParam, lParam);
            else
                return 0;
        }
        break;
			
	case WM_LBUTTONDOWN:
	case WM_RBUTTONDOWN:
	case WM_MBUTTONDOWN:
	case WM_LBUTTONUP:
	case WM_RBUTTONUP:
	case WM_MBUTTONUP:
	case WM_MOUSEMOVE:
	case WM_MOUSEWHEEL:

        if (message == WM_LBUTTONDOWN ||
            message == WM_RBUTTONDOWN ||
            message == WM_MBUTTONDOWN)
        {
            // capture the mouse 
            SetCapture(hWnd);

            window->SetMouseCaptured(true);
        }
        else if (message == WM_LBUTTONUP ||
                message == WM_RBUTTONUP ||
                message == WM_MBUTTONUP)
        {
            // release the mouse capture
            ReleaseCapture();

            window->SetMouseCaptured(false);
        }

        MouseEvent event;
        event.SetXPos(static_cast<int32_t>(LOWORD(lParam)));
        event.SetYPos(static_cast<int32_t>(HIWORD(lParam)));

        WPARAM mouseState = wParam;
        if (message == WM_MOUSEWHEEL)
        {
            mouseState = GET_KEYSTATE_WPARAM(wParam);
        }

        if (mouseState & MK_LBUTTON)
        {
            event.SetButtonPressed(MouseButtons::LeftButton);
        }
        if (mouseState & MK_RBUTTON)
        {
            event.SetButtonPressed(MouseButtons::RightButton);
        }
        if (mouseState & MK_MBUTTON)
        {
            event.SetButtonPressed(MouseButtons::MiddleButton);
        }
        if (mouseState & MK_XBUTTON1)
        {
            event.SetButtonPressed(MouseButtons::ExtraButton1);
        }
        if (mouseState & MK_XBUTTON2)
        {
            event.SetButtonPressed(MouseButtons::ExtraButton2);
        }

        if (mouseState & MK_CONTROL)
        {
            event.SetModifier(MouseModifiers::Ctrl);
        }
        if (mouseState & MK_SHIFT)
        {
            event.SetModifier(MouseModifiers::Shift);
        }

        if (message == WM_LBUTTONDOWN ||
            message == WM_RBUTTONDOWN ||
            message == WM_MBUTTONDOWN ||
            message == WM_LBUTTONUP ||
            message == WM_RBUTTONUP ||
            message == WM_MBUTTONUP)
        {
            event.SetEventType(MouseEventType::MouseClick);
        }
        else if (message == WM_MOUSEMOVE)
        {
            event.SetEventType(MouseEventType::MouseMoved);
        }
        else if (message == WM_MOUSEWHEEL)

        {
            event.SetEventType(MouseEventType::MouseWheel);

            int16_t wheelValue = GET_WHEEL_DELTA_WPARAM(wParam);
            event.SetWheelDelta(static_cast<float>(wheelValue)/WHEEL_DELTA);
        }
        
        // call into the window class to handle mouse input
        window->OnMouseInput(event);

        return 0;

		break;
	}

	return DefWindowProc(hWnd, message, wParam, lParam);
}

class Win32WindowSystem::Impl
{
public:
    Impl(Win32WindowSystem* parent, const WindowSystemSettings& settings)
    : m_parent(parent), m_settings(settings), m_externalWindow(settings.useExternalWindow), 
      m_hwnd(0), m_quit(false), m_mouseCaptured(false), m_shouldResize(false), m_inputSystem(0)
    {

    }

    ~Impl()
    {
        Destroy();
    }

    void Init()
    {
        if (!m_externalWindow)
        {
            // get handle to current process
            HINSTANCE hInstance = GetModuleHandle(0);

            TCHAR* className = __TEXT("Win32Application");

            // Register Class
            WNDCLASSEX wcex;
            wcex.cbSize			= sizeof(WNDCLASSEX);
            wcex.style			= CS_OWNDC;
            wcex.lpfnWndProc	= WndProc;
            wcex.cbClsExtra		= 0;
            wcex.cbWndExtra		= 0;
            wcex.hInstance		= hInstance;
            wcex.hIcon			= LoadIcon(NULL, IDI_APPLICATION);
            wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
            wcex.hbrBackground	= (HBRUSH)GetStockObject(BLACK_BRUSH); //(HBRUSH)(COLOR_WINDOW+1);
            wcex.lpszMenuName	= 0;
            wcex.lpszClassName	= className;
            wcex.hIconSm		= 0;

            // load icon
            // TODO - may need to load icon at some point
            //wcex.hIcon = (HICON)LoadImage(hInstance, __TEXT("*.ico"), IMAGE_ICON, 0,0, LR_LOADFROMFILE);

            RegisterClassEx(&wcex);

            RECT windowSize;
            windowSize.top = 0;
            windowSize.left = 0;
            windowSize.right = m_settings.width;
            windowSize.bottom = m_settings.height;

            DWORD windowStyle = WS_POPUP;

            // get the width and height of the window RECT
            uint32_t actualWidth = 0;
            uint32_t actualHeight = 0;

            uint32_t windowLeft = 0;
            uint32_t windowTop = 0;

            if (!m_settings.allowFullScreen || (m_settings.allowFullScreen && !m_settings.useFullScreen))
            {
                if (m_settings.allowResizeable)
                {
                    windowStyle = WS_SYSMENU | WS_THICKFRAME | WS_CAPTION | WS_CLIPCHILDREN | WS_CLIPSIBLINGS
                        | WS_MINIMIZEBOX | WS_MAXIMIZEBOX;
                }
                else
                {
                    windowStyle = WS_SYSMENU | WS_BORDER | WS_CAPTION | WS_CLIPCHILDREN | WS_CLIPSIBLINGS;
                }

                AdjustWindowRect(&windowSize, windowStyle, FALSE);

                // get the width and height of the window RECT
                actualWidth = windowSize.right - windowSize.left;
                actualHeight = windowSize.bottom - windowSize.top;

                windowLeft = 0;
                windowTop = 0;

                windowLeft = (GetSystemMetrics(SM_CXSCREEN) - actualWidth) / 2;
                windowTop = (GetSystemMetrics(SM_CYSCREEN) - actualHeight) / 2;

                if (windowLeft < 0)
                {
                    windowLeft = 0;
                }

                if (windowTop < 0)
                {
                    windowTop = 0;
                }
            }
            else
            {
                SetFullScreen(true);
                actualWidth = m_settings.width;
                actualHeight = m_settings.height;
            }

            // create the window
            m_hwnd = CreateWindowEx(NULL, className, __TEXT(""), windowStyle, windowLeft, windowTop, 
                actualWidth, actualHeight, NULL, NULL, hInstance, m_parent);

            ShowWindow(m_hwnd, SW_SHOW);
            UpdateWindow(m_hwnd);

            // force a window repaint on startup
            MoveWindow(m_hwnd, windowLeft, windowTop, actualWidth, actualHeight, TRUE);

            m_shouldResize = true;
        }
        else
        {
            m_hwnd = static_cast<HWND>(m_settings.windowId);
            RECT window;
            GetWindowRect(m_hwnd, &window);
            m_settings.width = window.right - window.left;
            m_settings.height = window.bottom - window.top;
            m_settings.allowFullScreen = false;
        }

        // set this as active window
        SetActiveWindow(m_hwnd);
        SetForegroundWindow(m_hwnd);

        m_hdc = GetDC(m_hwnd);

        PIXELFORMATDESCRIPTOR pfd;
        memset(&pfd, 0, sizeof(PIXELFORMATDESCRIPTOR));
        pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
        pfd.nVersion = 1;
        pfd.cColorBits = 16;
        pfd.cDepthBits = 15;
        pfd.dwFlags = PFD_DRAW_TO_WINDOW|PFD_SUPPORT_OPENGL|PFD_DOUBLEBUFFER;
        pfd.iPixelType = PFD_TYPE_RGBA;

        // if these fail, wglCreateContext will also quietly fail
        int32_t format;
        if ((format = ChoosePixelFormat(m_hdc, &pfd)) != 0)
        {
            SetPixelFormat(m_hdc, format, &pfd);
        }

        m_hglrc = wglCreateContext(m_hdc);

        wglMakeCurrent(m_hdc, m_hglrc);
    }

    WindowSystemType::Enum GetWindowSystemType() const
    {
        return WindowSystemType::Win32;
    }

    void SetWindowTitle(const char* text)
    {
        if (text)
        {
            DWORD result;
#if defined(UNICODE)
            uint32_t length = strlen(text) + 1;
            wchar_t* unicodeStr = (wchar_t*)malloc(length);
            if  (0 != MultiByteToWideChar(CP_ACP, 0, text, length, unicodeStr, length))
            {
                SendMessageTimeout(m_hwnd, WM_SETTEXT, 0, reinterpret_cast<LPARAM>(unicodeStr),
                    SMTO_ABORTIFHUNG, 2000, &result);
            }
            else
            {
                // TODO - report conversion error
                free(unicodeStr);
                unicodeStr = 0;
            }
#else
            SendMessageTimeout(m_hwnd, WM_SETTEXT, 0, reinterpret_cast<LPARAM>(text),
                SMTO_ABORTIFHUNG, 2000, &result);
#endif
            //#endif
        }
    }

    void Destroy()
    {
        if (m_hwnd)
        {
            wglDeleteContext(m_hglrc);
            m_hglrc = 0;

            SetFullScreen(false);
            DestroyWindow(m_hwnd);

            m_hwnd = 0;
            m_hdc = 0;
        }
    }

    void Minimize()
    {
        WINDOWPLACEMENT windowPlacement;
        windowPlacement.length = sizeof(WINDOWPLACEMENT);

        GetWindowPlacement(m_hwnd, &windowPlacement);
        windowPlacement.showCmd = SW_SHOWMINIMIZED;
        SetWindowPlacement(m_hwnd, &windowPlacement);
    }

    void Maximize()
    {
        WINDOWPLACEMENT windowPlacement;
        windowPlacement.length = sizeof(WINDOWPLACEMENT);

        GetWindowPlacement(m_hwnd, &windowPlacement);
        windowPlacement.showCmd = SW_SHOWMAXIMIZED;
        SetWindowPlacement(m_hwnd, &windowPlacement);
    }

    void Restore()
    {
        WINDOWPLACEMENT windowPlacement;
        windowPlacement.length = sizeof(WINDOWPLACEMENT);

        GetWindowPlacement(m_hwnd, &windowPlacement);
        windowPlacement.showCmd = SW_SHOWNORMAL;
        SetWindowPlacement(m_hwnd, &windowPlacement);
    }

    void SetFullScreen(bool fullScreen)
    {
        DWORD style = WS_VISIBLE | WS_CLIPCHILDREN;

        if (!m_settings.allowFullScreen)
        {
            return;
        }

        if (fullScreen == false)
        {
            style |= WS_OVERLAPPEDWINDOW;

            ChangeDisplaySettings(NULL, 0);
            SetWindowLongPtr(m_hwnd, GWL_STYLE, style);
        }
        else
        {
            style |= WS_POPUP;

            DEVMODE dm;
            memset(&dm, 0, sizeof(dm));
            dm.dmSize = sizeof(dm);

            // get current settings
            EnumDisplaySettings(NULL, ENUM_CURRENT_SETTINGS, &dm);

            // modify settings
            dm.dmPelsWidth = m_settings.width;
            dm.dmPelsHeight = m_settings.height;
            dm.dmBitsPerPel = m_settings.bitsPerPixel;
            dm.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT | DM_DISPLAYFREQUENCY;

            if (ChangeDisplaySettings(&dm, CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL)
            { 
                // try without forcing display frequency
                dm.dmFields ^= DM_DISPLAYFREQUENCY;
            }

            ChangeDisplaySettings(&dm, CDS_FULLSCREEN);

            SetWindowLongPtr(m_hwnd, GWL_STYLE, style);
        }
    }

    bool IsActive() const
    {
        return (GetActiveWindow() == m_hwnd);
    }

    bool HasFocus() const
    {
        return (GetFocus() == m_hwnd);
    }

    bool IsMinimized() const
    {
        WINDOWPLACEMENT windowPlacement;
        windowPlacement.length = sizeof(WINDOWPLACEMENT);
        bool ret = false;
        if (GetWindowPlacement(m_hwnd, &windowPlacement))
        {
            ret = (windowPlacement.showCmd & SW_SHOWMINIMIZED) !=0;
        }

        return ret;
    }

    bool IsMaximized() const
    {
        WINDOWPLACEMENT windowPlacement;
        windowPlacement.length = sizeof(WINDOWPLACEMENT);
        bool ret = false;
        if (GetWindowPlacement(m_hwnd, &windowPlacement))
        {
            ret = (windowPlacement.showCmd & SW_SHOWMAXIMIZED) !=0;
        }

        return ret;
    }

    void SetMouseCaptured(bool captured)
    {
        m_mouseCaptured = captured;
    }

    bool IsMouseCaptured()
    {
        return m_mouseCaptured;
    }

    void OnResize()
    {
        m_shouldResize = true;
    }

    void OnKeyboardInput(const IKeyEvent& event)
    {
        if (m_inputSystem)
        {
            m_inputSystem->InjectKeyEvent(event);
        }
    }

    void OnMouseInput(const IMouseEvent& event)
    {
        if (m_inputSystem)
        {
            m_inputSystem->InjectMouseEvent(event);
        }
    }

    bool Run()
    {
        MSG msg;

        while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            if (m_settings.useExternalWindow && msg.hwnd == m_hwnd)
                WndProc(m_hwnd, msg.message, msg.wParam, msg.lParam);
            else
                DispatchMessage(&msg);

            if (msg.message == WM_QUIT)
            {
                m_quit = true;
            }
        }

        if (!m_quit)
        {
            Resize();
        }

        return !m_quit;
    }

    void Update()
    {
        // TODO - call SwapBuffers(m_dc)
    }

    void SwapBuffers()
    {
        ::SwapBuffers(m_hdc);
    }

    void AddListener(IWindowSystemEventListener* listener)
    {
        if (listener)
        {
            m_listeners.push_back(listener);
        }
    }

    void RemoveListener(IWindowSystemEventListener* listener)
    {
        m_listeners.erase(std::remove(m_listeners.begin(), m_listeners.end(), listener), m_listeners.end());
    }

    void Resize()
    {
        if (!m_shouldResize || !m_settings.allowResizeable)
        {
            return;
        }

        RECT r;
        GetClientRect(m_hwnd, &r);

        m_shouldResize = false;

        // only resize if the size is above 1, otherwise this will cause
        // a problem with recalculating the aspect ratio
        if (r.right > 1 || r.bottom > 1)
        {
            // alert listeners of resize
            for (Listeners::iterator iter = m_listeners.begin(); iter != m_listeners.end(); ++iter)
            {
                if (*iter)
                {
                    (*iter)->OnResize(static_cast<uint32_t>(r.right), static_cast<uint32_t>(r.bottom));
                }
            }
        }
    }

    void SetInputSystem(IInputSystem* inputSystem)
    {
        m_inputSystem = inputSystem;
    }

private:
    Win32WindowSystem* m_parent;
    WindowSystemSettings m_settings;
    bool m_externalWindow;
    bool m_fullScreen;
    bool m_shouldResize;
    bool m_quit;
    bool m_mouseCaptured;
    HWND m_hwnd;
    HDC m_hdc;
    HGLRC m_hglrc;

    typedef std::vector<IWindowSystemEventListener*> Listeners;
    Listeners m_listeners;

    IInputSystem* m_inputSystem;
};

Win32WindowSystem::Win32WindowSystem(const WindowSystemSettings& settings)
{
    m_impl = new Impl(this, settings);
    assert(m_impl);
}

Win32WindowSystem::~Win32WindowSystem()
{
	delete m_impl;
    m_impl = 0;
}

void Win32WindowSystem::Init()
{
	m_impl->Init();
}

WindowSystemType::Enum Win32WindowSystem::GetWindowSystemType() const
{
    return m_impl->GetWindowSystemType();
}

void Win32WindowSystem::SetWindowTitle(const char* text)
{
    m_impl->SetWindowTitle(text);
}

void Win32WindowSystem::Destroy()
{
	m_impl->Destroy();
}

void Win32WindowSystem::Minimize()
{
	m_impl->Minimize();
}

void Win32WindowSystem::Maximize()
{
    m_impl->Maximize();
}

void Win32WindowSystem::Restore()
{
	m_impl->Restore();
}

void Win32WindowSystem::SetFullScreen(bool fullScreen)
{
	m_impl->SetFullScreen(fullScreen);
}

bool Win32WindowSystem::IsActive() const
{
	return m_impl->IsActive();
}

bool Win32WindowSystem::HasFocus() const
{
	return m_impl->HasFocus();
}

bool Win32WindowSystem::IsMinimized() const
{
	return m_impl->IsMinimized();
}

bool Win32WindowSystem::IsMaximized() const
{
	return m_impl->IsMaximized();
}

void Win32WindowSystem::SetMouseCaptured(bool captured)
{
    m_impl->SetMouseCaptured(captured);
}

bool Win32WindowSystem::IsMouseCaptured()
{
    return m_impl->IsMouseCaptured();
}

void Win32WindowSystem::OnResize()
{
	m_impl->OnResize();
}

void Win32WindowSystem::OnKeyboardInput(const IKeyEvent& event)
{
    m_impl->OnKeyboardInput(event);
}

void Win32WindowSystem::OnMouseInput(const IMouseEvent& event)
{
    m_impl->OnMouseInput(event);
}

bool Win32WindowSystem::Run()
{
	return m_impl->Run();
}

void Win32WindowSystem::Update()
{
	m_impl->Update();
}

void Win32WindowSystem::SwapBuffers()
{
	m_impl->SwapBuffers();
}

void Win32WindowSystem::AddListener(IWindowSystemEventListener* listener)
{
	m_impl->AddListener(listener);
}

void Win32WindowSystem::RemoveListener(IWindowSystemEventListener* listener)
{
	m_impl->RemoveListener(listener);
}

void Win32WindowSystem::Resize()
{
	m_impl->Resize();
}

void Win32WindowSystem::SetInputSystem(IInputSystem* inputSystem)
{
    m_impl->SetInputSystem(inputSystem);
}