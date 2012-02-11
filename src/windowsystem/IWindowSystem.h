/**********************************************************************
*	Filename: IWindowSystem.h
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
#ifndef IWINDOW_SYSTEM_H_
#define IWINDOW_SYSTEM_H_

#include "StdIncludes.h"

#include "WindowSystemTypes.h"

class Engine;
class IWindowSystemEventListener;
class IInputSystem;

struct WindowSystemSettings
{
	WindowSystemSettings() 
	: windowSystemType(WindowSystemType::Invalid),
	width(800), height(600), bitsPerPixel(16), useExternalWindow(false), 
	allowFullScreen(true), useFullScreen(false), allowResizeable(true), 
    useDisplayLink(true), windowId(0)
	{
#if defined(WINDOWS_OS)
		windowSystemType = WindowSystemType::Win32;
#elif defined(MACOSX_OS)
		windowSystemType = WindowSystemType::MacOsx;
#else
		windowSystemType = WindowSystemType::Linux;
#endif
	}
	
	WindowSystemType::Enum windowSystemType;
	uint32_t width;
	uint32_t height;
	uint32_t bitsPerPixel;
	bool useExternalWindow;
	bool allowFullScreen;
	bool useFullScreen;
	bool allowResizeable;
    bool useDisplayLink;    // OS X only
	void* windowId;
};

class IWindowSystem
{
public:

	virtual ~IWindowSystem() { };

	virtual void Init() = 0;
	virtual WindowSystemType::Enum GetWindowSystemType() const = 0;
	virtual void SetWindowTitle(const char* text) = 0;
	virtual void Destroy() = 0;
	virtual void Minimize() = 0;
	virtual void Maximize() = 0;
	virtual void Restore() = 0;
	virtual void SetFullScreen(bool fullScreen) = 0;
	virtual bool IsActive() const = 0;
	virtual bool HasFocus() const = 0;
	virtual bool IsMinimized() const = 0;
	virtual bool IsMaximized() const = 0;
	virtual void OnResize() = 0;
	virtual bool Run() = 0;
	virtual void Update() = 0;
	virtual void SwapBuffers() = 0;
	virtual void AddListener(IWindowSystemEventListener* listener) = 0;
	virtual void RemoveListener(IWindowSystemEventListener* listener) = 0;
    virtual void SetInputSystem(IInputSystem* inputSystem) = 0;
};

IWindowSystem* CreateWindowSystem(const WindowSystemSettings& settings);

#endif
