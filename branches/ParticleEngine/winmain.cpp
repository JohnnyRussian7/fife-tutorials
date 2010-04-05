/* OpenGL Minimum Base Code
   Created on September 2002
   Updated on March 2009

   Downloaded from:
   www.falloutsoftware.com/programming.php4

   Written by: Greg Sidelnikov
   greg.sidelnikov@gmail.com
*/

#include <windows.h>
#include <tchar.h>

#include <gl/gl.h>			// OpenGL headers
#include <gl/glu.h>

#include "winmain.h"
#include "system.h"
#include "glmain.h"

HDC hdc;
HWND hwnd;
HGLRC hglrc;

int screenw = SCRWIDTH;
int screenh = SCRHEIGHT;
int screenmode = 0;

bool quit = false;

int indexPixelFormat = 0;

// CreateWnd: creates either a "full-screen" or a "windowed" window according to the flag - type
//            type = 0: windowed
//			  type = 1: full-screen

void CreateWnd (HINSTANCE &hinst, int width, int height, int depth, int type)
{	
	// center position of the window
	int posx = (GetSystemMetrics(SM_CXSCREEN) / 2) - (width / 2);
	int posy = (GetSystemMetrics(SM_CYSCREEN) / 2) - (height / 2);

	// set up the window for a windowed application by default
	long wndStyle = WS_OVERLAPPEDWINDOW;
	screenmode = WINDOWED;

	if (type == FULLSCREEN)	// create a full-screen application if requested
	{
		wndStyle = WS_POPUP;
		screenmode = FULLSCREEN;

		posx = 0;
		posy = 0;

		// change resolution before the window is created
		SysSetDisplayMode(screenw, screenh, SCRDEPTH);
	}

	// create the window
	hwnd = CreateWindowEx(NULL,
						  _T(WNDCLASSNAME),
						  _T(WNDNAME),
						  wndStyle|WS_CLIPCHILDREN|WS_CLIPSIBLINGS,
						  posx, posy,
						  width, height,
						  NULL,
						  NULL,
						  hinst,
						  NULL);

	// at this point WM_CREATE message is sent/received
	// the WM_CREATE branch inside WinProc function will execute here
}

void SetGLFormat (void)
{
	PIXELFORMATDESCRIPTOR pfd =
	{
		sizeof(PIXELFORMATDESCRIPTOR),
			1,
			PFD_DRAW_TO_WINDOW|PFD_SUPPORT_OPENGL|PFD_DOUBLEBUFFER,
			PFD_TYPE_RGBA,
			SCRDEPTH,
			0,0,0,0,0,0,0,0,0,0,0,0,0, // useles parameters
			16,
			0,0,PFD_MAIN_PLANE,0,0,0,0
	};
	
	// Choose the closest pixel format available
	if (!(indexPixelFormat = ChoosePixelFormat(hdc, &pfd)))
	{
		MessageBox(hwnd, _T("Failed to find pixel format"), _T("Pixel Format Error"), MB_OK);
		SysShutdown();
	}
	
	// Set the pixel format for the provided window DC
	if ( !SetPixelFormat(hdc, indexPixelFormat, &pfd) )
	{
		MessageBox(hwnd, _T("Failed to Set Pixel Format"), _T("Pixel Format Error"), MB_OK);
		SysShutdown();
	}
}

void Resize (int width, int height)
{
	if (height <= 0)
		height = 1;

	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);
	
	glLoadIdentity();

	gluPerspective(45.0f, (float)width/(float)height, 0.2f, 255.0f);

	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();
}

// InitOpenGL: initializes OpenGL; resize projection and other setup

void InitOpenGL (void)
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClearDepth(1.0f);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	glShadeModel(GL_SMOOTH);

	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_FASTEST);
}

//*=====================
//  The event handler
//*=====================

LRESULT CALLBACK WinProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	switch(msg)
	{
		case WM_CREATE:
			{
				if ((hdc = GetDC(hwnd)) == NULL)				// get device context
				{
					MessageBox(hwnd, _T("Failed to Get the Window Device Context"), _T("Device Context Error"), MB_OK);
					SysShutdown();
					break;
				}

				SetGLFormat();					// select pixel format, needed before wglCreateContext call
				
				if ((hglrc = wglCreateContext(hdc)) == NULL)	// create the rendering context
				{
					MessageBox(hwnd, _T("Failed to Create the OpenGL Rendering Context"), _T("OpenGL Rendering Context Error"), MB_OK);
					SysShutdown();
					break;
				}
				
				if ((wglMakeCurrent(hdc, hglrc)) == false)		// make hglrc current rc
				{
					MessageBox(hwnd, _T("Failed to Make OpenGL Rendering Context Current"), _T("OpenGL Rendering Context Error"), MB_OK);
					SysShutdown();					
				}

				Resize(SCRWIDTH, SCRHEIGHT);

				InitOpenGL();					// initialize OpenGL before showing the window

				ShowWindow(hwnd, SW_SHOW);		// everything went OK, show the window
				UpdateWindow(hwnd);

				break;
			}

		case WM_DESTROY:
			{
				SysShutdown();					// release memory and shutdown
				break;
			}
	
		case WM_SIZE:
			{
				// resize the viewport after the window had been resized
				Resize(LOWORD(lparam), HIWORD(lparam));			
				
				screenw = LOWORD(lparam);
				screenh = HIWORD(lparam);
				
				break;
			}
		case WM_KEYDOWN:							// Is A Key Being Held Down?
			{
				keys[wparam] = TRUE;					// If So, Mark It As TRUE
				return 0;								// Jump Back
			}

		case WM_KEYUP:								// Has A Key Been Released?
			{
				keys[wparam] = FALSE;					// If So, Mark It As FALSE
				return 0;								// Jump Back
			}
	}

	return DefWindowProc(hwnd, msg, wparam, lparam);
}

//*=====================
//  WinMain
//*=====================

int WINAPI WinMain(HINSTANCE hinstance, HINSTANCE hprevinstance, LPSTR lpcmdline, int nshowcmd)
{
	MSG msg;
	WNDCLASSEX ex;

	ex.cbSize = sizeof(WNDCLASSEX);
	ex.style = CS_HREDRAW|CS_VREDRAW|CS_OWNDC;
	ex.lpfnWndProc = WinProc;
	ex.cbClsExtra = 0;
	ex.cbWndExtra = 0;
	ex.hInstance = hinstance;
	ex.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	ex.hCursor = LoadCursor(NULL, IDC_ARROW);
	ex.hbrBackground = NULL;
	ex.lpszMenuName = NULL;
	ex.lpszClassName = _T(WNDCLASSNAME);
	ex.hIconSm = NULL;

	if (!RegisterClassEx(&ex))
	{
		MessageBox(NULL, _T("Failed to register the window class"), _T("Window Reg Error"), MB_OK);
		return 1;
	}

	// Create the window
	CreateWnd(hinstance, screenw, screenh, SCRDEPTH, WINDOWED);	

    InitFrame();

	// The message loop
	while (!quit)
	{
		if (PeekMessage(&msg, NULL, NULL, NULL, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
				quit = true;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		RenderFrame();

		SwapBuffers(hdc);

		if (GetAsyncKeyState(VK_ESCAPE))
			SysShutdown();
	}

	return msg.lParam;
}
