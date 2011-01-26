/**********************************************************************
*	Filename: InputSystem.h
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
#ifndef INPUTSYSTEM_H_
#define INPUTSYSTEM_H_

#include "StdIncludes.h"

#include "IInputSystem.h"

class InputSystem : public IInputSystem
{
public:
    InputSystem(const InputSystemSettings& settings);

    virtual void AddKeyListener(IKeyListener* listener);
    virtual void AddMouseListener(IMouseListener* listener);

    virtual void RemoveKeyListener(const std::string& listenerName);
    virtual void RemoveKeyListener(const IKeyListener* listener);
    virtual void RemoveAllKeyListeners();

    virtual void RemoveMouseListener(const std::string listenerName);
    virtual void RemoveMouseListener(const IMouseListener* listener);
    virtual void RemoveAllMouseListeners();

    virtual void RemoveAllListeners();

    virtual void InjectKeyEvent(const IKeyEvent& event);
    virtual void InjectMouseEvent(const IMouseEvent& event);

protected:
    virtual void OnKeyPressed(const IKeyEvent& event);
    virtual void OnKeyReleased(const IKeyEvent& event);
 
    virtual void OnMouseMoved(const IMouseEvent& event);
    virtual void OnMousePressed(const IMouseEvent& event);
    virtual void OnMouseReleased(const IMouseEvent& event);
    virtual void OnMouseWheel(const IMouseEvent& event);

private:
    InputSystemSettings m_settings;
    
    typedef std::vector<IKeyListener*> KeyListenerContainer;
    KeyListenerContainer m_keyListeners;

    typedef std::vector<IMouseListener*> MouseListenerContainer;
    MouseListenerContainer m_mouseListeners;
};

#endif