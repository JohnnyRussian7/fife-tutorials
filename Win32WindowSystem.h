/**********************************************************************
*	Filename: Win32WindowSystem.h
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
#ifndef WIN32WINDOWSYSTEM_H_
#define WIN32WINDOWSYSTEM_H_

#include "StdIncludes.h"

#include "IWindowSystem.h"

class IWindowSystemEventListener;
class IInputSystem;
class IKeyEvent;
class IMouseEvent;

class Win32WindowSystem : public IWindowSystem
{
public:
	Win32WindowSystem(const WindowSystemSettings& settings);
	~Win32WindowSystem();

	virtual void Init();
	virtual WindowSystemType::Enum GetWindowSystemType() const;
	virtual void SetWindowTitle(const wchar_t* text);
	virtual void Destroy();
	virtual void Minimize();
	virtual void Maximize();
	virtual void Restore();
	virtual void SetFullScreen(bool fullScreen);
	virtual bool IsActive() const;
	virtual bool HasFocus() const;
	virtual bool IsMinimized() const;
	virtual bool IsMaximized() const;
    void SetMouseCaptured(bool captured);
    bool IsMouseCaptured();
	virtual void OnResize();
    virtual void OnKeyboardInput(const IKeyEvent& event);
    virtual void OnMouseInput(const IMouseEvent& event);
	virtual bool Run();
	virtual void Update();
	virtual void SwapBuffers();
	virtual void AddListener(IWindowSystemEventListener* listener);
	virtual void RemoveListener(IWindowSystemEventListener* listener);
    virtual void SetInputSystem(IInputSystem* inputSystem);

private:
	void Resize();

private:
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

#endif