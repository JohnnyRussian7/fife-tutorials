/**********************************************************************
 *	Filename: OsxWindowSystem.h
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
#ifndef OSXWINDOWSYSTEM_H_
#define OSXWINDOWSYSTEM_H_

#include "StdIncludes.h"

#include "IWindowSystem.h"

class Engine;
class IWindowSystemEventListener;
class IInputSystem;
class IKeyEvent;
class IMouseEvent;

class OsxWindowSystem : public IWindowSystem
    {
    public:
        OsxWindowSystem(const WindowSystemSettings& settings);
        ~OsxWindowSystem();
        
        virtual void Init();
        virtual WindowSystemType::Enum GetWindowSystemType() const;
        virtual void SetWindowTitle(const char* text);
        virtual void Destroy();
        virtual void Minimize();
        virtual void Maximize();
        virtual void Restore();
        virtual void SetFullScreen(bool fullScreen);
        virtual bool IsActive() const;
        virtual bool HasFocus() const;
        virtual bool IsMinimized() const;
        virtual bool IsMaximized() const;
        virtual void OnResize();
        virtual void OnKeyboardInput(const IKeyEvent& event);
        virtual void OnMouseInput(const IMouseEvent& event);
        virtual bool Run();
        virtual void Update();
        virtual void SwapBuffers();
        virtual void AddListener(IWindowSystemEventListener* listener);
        virtual void RemoveListener(IWindowSystemEventListener* listener);
        virtual void SetInputSystem(IInputSystem* inputSystem);
        
        void OnDisplayUpdate();
        void ResizeImpl(uint32_t width, uint32_t height);
        
    private:
        void Resize();
        
    private:
        class Impl;
        Impl* m_impl;
    };

#endif
