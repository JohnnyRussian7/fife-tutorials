/**********************************************************************
*	Filename: IInputSystem.h
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
#ifndef IINPUTSYSTEM_H_
#define IINPUTSYSTEM_H_

#include <string>

class IKeyListener;
class IMouseListener;
class IKeyEvent;
class IMouseEvent;

struct InputSystemSettings
{
    
};

class IInputSystem
{
public:
    virtual ~IInputSystem() = 0 { };

    virtual void AddKeyListener(IKeyListener* listener) = 0;
    virtual void AddMouseListener(IMouseListener* listener) = 0;

    virtual void RemoveKeyListener(const std::string& listenerName) = 0;
    virtual void RemoveKeyListener(const IKeyListener* listener) = 0;
    virtual void RemoveAllKeyListeners() = 0;

    virtual void RemoveMouseListener(const std::string listenerName) = 0;
    virtual void RemoveMouseListener(const IMouseListener* listener) = 0;
    virtual void RemoveAllMouseListeners() = 0;

    virtual void RemoveAllListeners() = 0;
    
    virtual void InjectKeyEvent(const IKeyEvent& event) = 0;
    virtual void InjectMouseEvent(const IMouseEvent& event) = 0;

//     virtual void OnKeyPressed(const IKeyEvent& event) = 0;
//     virtual void OnKeyReleased(const IKeyEvent& event) = 0;
// 
//     virtual void OnMouseMoved(const IMouseEvent& event) = 0;
//     virtual void OnMousePressed(const IMouseEvent& event) = 0;
//     virtual void OnMouseReleased(const IMouseEvent& event) = 0;
};

#endif