/**********************************************************************
*	Filename: InputSystem.cpp
*	
*	Copyright (C) 2010, FIFE team
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

#include "InputSystem.h"
#include "keyboard/IKeyEvent.h"
#include "keyboard/IKeyListener.h"
#include "mouse/IMouseEvent.h"
#include "mouse/IMouseListener.h"


InputSystem::InputSystem(const InputSystemSettings& settings)
: m_settings(settings)
{

}

void InputSystem::AddKeyListener(IKeyListener* listener)
{
    KeyListenerContainer::iterator iter;
    for (iter = m_keyListeners.begin(); iter != m_keyListeners.end(); ++iter)
    {
        if (*iter == listener)
        {
            return;
        }
    }

    m_keyListeners.push_back(listener);
}

void InputSystem::AddMouseListener(IMouseListener* listener)
{
    MouseListenerContainer::iterator iter;
    for (iter = m_mouseListeners.begin(); iter != m_mouseListeners.end(); ++iter)
    {
        if (*iter == listener)
        {
            return;
        }
    }

    m_mouseListeners.push_back(listener);
}

void InputSystem::RemoveKeyListener(const std::string& listenerName)
{
    KeyListenerContainer::iterator iter;
    for (iter = m_keyListeners.begin(); iter != m_keyListeners.end(); ++iter)
    {
        if ((*iter)->GetName() == listenerName)
        {
            m_keyListeners.erase(iter);
            break;
        }
    }
}

void InputSystem::RemoveKeyListener(const IKeyListener* listener)
{
    KeyListenerContainer::iterator iter;
    for (iter = m_keyListeners.begin(); iter != m_keyListeners.end(); ++iter)
    {
        if (*iter == listener)
        {
            m_keyListeners.erase(iter);
            break;
        }
    }
}

void InputSystem::RemoveAllKeyListeners()
{
    m_keyListeners.clear();
}

void InputSystem::RemoveMouseListener(const std::string listenerName)
{
    MouseListenerContainer::iterator iter;
    for (iter = m_mouseListeners.begin(); iter != m_mouseListeners.end(); ++iter)
    {
        if ((*iter)->GetName() == listenerName)
        {
            m_mouseListeners.erase(iter);
            break;
        }
    }
}

void InputSystem::RemoveMouseListener(const IMouseListener* listener)
{
    MouseListenerContainer::iterator iter;
    for (iter = m_mouseListeners.begin(); iter != m_mouseListeners.end(); ++iter)
    {
        if (*iter == listener)
        {
            m_mouseListeners.erase(iter);
        }
    }
}

void InputSystem::RemoveAllMouseListeners()
{
    m_mouseListeners.clear();
}

void InputSystem::RemoveAllListeners()
{
    m_keyListeners.clear();
    m_mouseListeners.clear();
}

void InputSystem::InjectKeyEvent(const IKeyEvent& event)
{
    if (event.IsKeyPressed())
    {
        OnKeyPressed(event);
    }
    else
    {
        OnKeyReleased(event);
    }
}

void InputSystem::InjectMouseEvent(const IMouseEvent& event)
{
    if (event.GetEventType() == MouseEventType::MouseClick)
    {
        if (event.IsButtonPressed(MouseButtons::Any))
        {
            OnMousePressed(event);
        }
        else
        {
            OnMouseReleased(event);
        }
    }
    else if (event.GetEventType() == MouseEventType::MouseMoved)
    {
        OnMouseMoved(event);
    }
    else if (event.GetEventType() == MouseEventType::MouseWheel)
    {
        OnMouseWheel(event);
    }
    else if (event.GetEventType() == MouseEventType::MouseDragged)
    {
        OnMouseDragged(event);
    }
}

void InputSystem::OnKeyPressed(const IKeyEvent& event)
{
    KeyListenerContainer::iterator iter;
    for (iter = m_keyListeners.begin(); iter != m_keyListeners.end(); ++iter)
    {
        if ((*iter)->OnKeyPressed(event))
        {
            // event consumed, do not continue
            break;
        }
    }
}

void InputSystem::OnKeyReleased(const IKeyEvent& event)
{
    KeyListenerContainer::iterator iter;
    for (iter = m_keyListeners.begin(); iter != m_keyListeners.end(); ++iter)
    {
        if ((*iter)->OnKeyReleased(event))
        {
            // event consumed, do not continue
            break;
        }
    }
}

void InputSystem::OnMouseMoved(const IMouseEvent& event)
{
    MouseListenerContainer::iterator iter;
    for (iter = m_mouseListeners.begin(); iter != m_mouseListeners.end(); ++iter)
    {
        if ((*iter)->OnMouseMoved(event))
        {
            // event consumed, do not continue
            break;
        }
    }
}

void InputSystem::OnMousePressed(const IMouseEvent& event)
{
    MouseListenerContainer::iterator iter;
    for (iter = m_mouseListeners.begin(); iter != m_mouseListeners.end(); ++iter)
    {
        if ((*iter)->OnMousePressed(event))
        {
            // event consumed, do not continue
            break;
        }
    }
}

void InputSystem::OnMouseReleased(const IMouseEvent& event)
{
    MouseListenerContainer::iterator iter;
    for (iter = m_mouseListeners.begin(); iter != m_mouseListeners.end(); ++iter)
    {
        if ((*iter)->OnMouseReleased(event))
        {
            // event consumed, do not continue
            break;
        }
    }
}

void InputSystem::OnMouseWheel(const IMouseEvent& event)
{
    MouseListenerContainer::iterator iter;
    for (iter = m_mouseListeners.begin(); iter != m_mouseListeners.end(); ++iter)
    {
        if ((*iter)->OnMouseWheel(event))
        {
            // event consumed, do not continue
            break;
        }
    }
}

void InputSystem::OnMouseDragged(const IMouseEvent& event)
{
    MouseListenerContainer::iterator iter;
    for (iter = m_mouseListeners.begin(); iter != m_mouseListeners.end(); ++iter)
    {
        if ((*iter)->OnMouseDragged(event))
        {
            // event consumed, do not continue
            break;
        }
    }
}