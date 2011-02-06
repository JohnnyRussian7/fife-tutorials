/**********************************************************************
 *	Filename: OsxWindowSystem.cpp
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

#include "OsxWindowSystem.h"
#import "OsxCocoaView.h"

#include "InputSystem.h"

class OsxWindowSystem::Impl
{
public:
    
    Impl(const WindowSystemSettings& settings)
    : m_settings(settings)
    {
        
    }
    
    ~Impl()
    {
        
    }
    
    void Init()
    {
        // make sure the application is initialized
        // before attempting to create or use it
        [NSApplication sharedApplication];
        
        if (!m_settings.useExternalWindow)
        {
            // create our window
            NSRect windowRect = NSMakeRect(0, 0, m_settings.width, m_settings.height);
            
            m_window = [[[NSWindow alloc]
                         initWithContentRect:windowRect 
                         styleMask:NSTitledWindowMask | NSClosableWindowMask 
                         | NSMiniaturizableWindowMask | NSResizableWindowMask 
                         backing:NSBackingStoreBuffered defer:NO] autorelease];
            
            if (m_window)
            {
                m_view = [[[OsxCocoaView alloc] initWithFrame:windowRect] autorelease];
                
                if (m_view)
                {
                    [m_window setContentView:m_view];
                }
                
                SetWindowTitle("Fife Engine");
                
                [m_window makeKeyAndOrderFront:nil];
                [m_window setAcceptsMouseMovedEvents:YES];
            }
        }
        else
        {
            // TODO - implement using existing window
        }
    }
    
    WindowSystemType::Enum GetWindowSystemType() const
    {
        return WindowSystemType::MacOsx;
    }
    
    void SetWindowTitle(const char* text)
    {
        NSString* title = [NSString stringWithUTF8String:text];
        
        [m_window setTitle:title];
    }
    
    void Destroy()
    {
        
    }
    
    void Minimize()
    {
        
    }
    
    void Maximize()
    {
        
    }
    
    void Restore()
    {
        
    }
    
    void SetFullScreen(bool fullScreen)
    {
        
    }
    
    bool IsActive() const
    {
        
    }
    
    bool HasFocus() const
    {
        
    }
    
    bool IsMinimized() const
    {
        // use NSWindow isMiniaturized
    }
    
    bool IsMaximized() const
    {
        // use NSWindow isZoomed
    }
    
    
    void OnResize()
    {
        
    }
    
    void OnKeyboardInput(const IKeyEvent& event)
    {
        
    }
    
    void OnMouseInput(const IMouseEvent& event)
    {
        
    }
    
    bool Run()
    {
        
    }
    
    void Update()
    {
        
    }
    
    void SwapBuffers()
    {
        
    }
    
    void AddListener(IWindowSystemEventListener* listener)
    {
        m_listeners.push_back(listener);
    }
    
    void RemoveListener(IWindowSystemEventListener* listener)
    {
        m_listeners.erase(std::remove(m_listeners.begin(), m_listeners.end(), listener), m_listeners.end());
    }
    
    void SetInputSystem(IInputSystem* inputSystem)
    {
        // remove current input system
        delete m_inputSystem;
        
        m_inputSystem = inputSystem;
    }
    
private:
    WindowSystemSettings m_settings;
    bool m_externalWindow;
    bool m_fullScreen;
    bool m_shouldResize;
    bool m_quit;
    bool m_mouseCaptured;
    
    typedef std::vector<IWindowSystemEventListener*> Listeners;
    Listeners m_listeners;
    
    IInputSystem* m_inputSystem;
    
    NSWindow* m_window;
    OsxCocoaView* m_view;    
};

OsxWindowSystem::OsxWindowSystem(const WindowSystemSettings& settings)
{
    m_impl = new Impl(settings);
    assert(m_impl);
}

OsxWindowSystem::~OsxWindowSystem()
{
    delete m_impl;
}

void OsxWindowSystem::Init()
{
    m_impl->Init();
}

WindowSystemType::Enum OsxWindowSystem::GetWindowSystemType() const
{
    return m_impl->GetWindowSystemType();
}

void OsxWindowSystem::SetWindowTitle(const char* text)
{
    m_impl->SetWindowTitle(text);
}

void OsxWindowSystem::Destroy()
{
    m_impl->Destroy();
}

void OsxWindowSystem::Minimize()
{
    m_impl->Minimize();
}

void OsxWindowSystem::Maximize()
{
    m_impl->Maximize();
}

void OsxWindowSystem::Restore()
{
    m_impl->Restore();
}

void OsxWindowSystem::SetFullScreen(bool fullScreen)
{
    m_impl->SetFullScreen(fullScreen);
}

bool OsxWindowSystem::IsActive() const
{
    return m_impl->IsActive();
}

bool OsxWindowSystem::HasFocus() const
{
    return m_impl->HasFocus();
}

bool OsxWindowSystem::IsMinimized() const
{
    return m_impl->IsMinimized();
}

bool OsxWindowSystem::IsMaximized() const
{
    return m_impl->IsMaximized();
}


void OsxWindowSystem::OnResize()
{
    m_impl->OnResize();
}

void OsxWindowSystem::OnKeyboardInput(const IKeyEvent& event)
{
    m_impl->OnKeyboardInput(event);
}

void OsxWindowSystem::OnMouseInput(const IMouseEvent& event)
{
    m_impl->OnMouseInput(event);
}

bool OsxWindowSystem::Run()
{
    return m_impl->Run();
}

void OsxWindowSystem::Update()
{
    m_impl->Update();
}

void OsxWindowSystem::SwapBuffers()
{
    m_impl->SwapBuffers();
}

void OsxWindowSystem::AddListener(IWindowSystemEventListener* listener)
{
    m_impl->AddListener(listener);
}

void OsxWindowSystem::RemoveListener(IWindowSystemEventListener* listener)
{
    m_impl->RemoveListener(listener);
}

void OsxWindowSystem::SetInputSystem(IInputSystem* inputSystem)
{
    m_impl->SetInputSystem(inputSystem);
}

