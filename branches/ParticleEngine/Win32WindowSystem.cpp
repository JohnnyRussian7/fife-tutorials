
#include <algorithm>

#include "stdint.h"
#include "Win32WindowSystem.h"
#include "IRenderSystem.h"
#include "IWindowSystemEventListener.h"

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
		break;
	}

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
		bool allKeys[256];
	
	case WM_LBUTTONDOWN:
	case WM_RBUTTONDOWN:
	case WM_MBUTTONDOWN:

	case WM_LBUTTONUP:
	case WM_RBUTTONUP:
	case WM_MBUTTONUP:

	case WM_MOUSEMOVE:

	case WM_MOUSEWHEEL:
		break;
	}

	return DefWindowProc(hWnd, message, wParam, lParam);
}

Win32WindowSystem::Win32WindowSystem(const WindowSystemSettings& settings)
: m_settings(settings), m_externalWindow(settings.useExternalWindow), m_hwnd(0), m_quit(false),
  m_shouldResize(false)
{
	
}

Win32WindowSystem::~Win32WindowSystem()
{
	Destroy();
}

void Win32WindowSystem::Init()
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
		int actualWidth = 0;
		int actualHeight = 0;

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
			actualWidth, actualHeight, NULL, NULL, hInstance, this);

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
	int format;
	if ((format = ChoosePixelFormat(m_hdc, &pfd)) != 0)
	{
		SetPixelFormat(m_hdc, format, &pfd);
	}

	m_hglrc = wglCreateContext(m_hdc);

	wglMakeCurrent(m_hdc, m_hglrc);
}

WindowSystemType::Enum Win32WindowSystem::GetWindowSystemType() const
{
	return WindowSystemType::Win32;
}

void Win32WindowSystem::SetWindowTitle(const wchar_t* text)
{
	if (text)
	{
// #if defined(_WIN64) || defined(WIN64)
// 		SetWindowTextW(m_hwnd, text);
// #else
		DWORD result;
		SendMessageTimeout(m_hwnd, WM_SETTEXT, 0, reinterpret_cast<LPARAM>(text),
							SMTO_ABORTIFHUNG, 2000, &result);
//#endif
	}
}

void Win32WindowSystem::Destroy()
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

void Win32WindowSystem::Minimize()
{
	WINDOWPLACEMENT windowPlacement;
	windowPlacement.length = sizeof(WINDOWPLACEMENT);

	GetWindowPlacement(m_hwnd, &windowPlacement);
	windowPlacement.showCmd = SW_SHOWMINIMIZED;
	SetWindowPlacement(m_hwnd, &windowPlacement);
}

void Win32WindowSystem::Maximize()
{
	WINDOWPLACEMENT windowPlacement;
	windowPlacement.length = sizeof(WINDOWPLACEMENT);

	GetWindowPlacement(m_hwnd, &windowPlacement);
	windowPlacement.showCmd = SW_SHOWMAXIMIZED;
	SetWindowPlacement(m_hwnd, &windowPlacement);
}

void Win32WindowSystem::Restore()
{
	WINDOWPLACEMENT windowPlacement;
	windowPlacement.length = sizeof(WINDOWPLACEMENT);

	GetWindowPlacement(m_hwnd, &windowPlacement);
	windowPlacement.showCmd = SW_SHOWNORMAL;
	SetWindowPlacement(m_hwnd, &windowPlacement);
}

void Win32WindowSystem::SetFullScreen(bool fullScreen)
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

bool Win32WindowSystem::IsActive() const
{
	return (GetActiveWindow() == m_hwnd);
}

bool Win32WindowSystem::HasFocus() const
{
	return (GetFocus() == m_hwnd);
}

bool Win32WindowSystem::IsMinimized() const
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

bool Win32WindowSystem::IsMaximized() const
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

void Win32WindowSystem::OnResize()
{
	m_shouldResize = true;
}

bool Win32WindowSystem::Run()
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

void Win32WindowSystem::Update()
{
	// TODO - call SwapBuffers(m_dc)
}

void Win32WindowSystem::SwapBuffers()
{
	::SwapBuffers(m_hdc);
}

void Win32WindowSystem::AddListener(IWindowSystemEventListener* listener)
{
	if (listener)
	{
		m_listeners.push_back(listener);
	}
}

void Win32WindowSystem::RemoveListener(IWindowSystemEventListener* listener)
{
	m_listeners.erase(std::remove(m_listeners.begin(), m_listeners.end(), listener), m_listeners.end());
}

void Win32WindowSystem::Resize()
{
	if (!m_shouldResize || !m_settings.allowResizeable)
	{
		return;
	}

	RECT r;
	GetClientRect(m_hwnd, &r);

	m_shouldResize = false;

	// alert listeners of resize
	for (Listeners::iterator iter = m_listeners.begin(); iter != m_listeners.end(); ++iter)
	{
		if (*iter)
		{
			(*iter)->OnResize(static_cast<uint32_t>(r.right), static_cast<uint32_t>(r.bottom));
		}
	}
}