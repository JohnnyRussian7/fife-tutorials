/**********************************************************************
*	Filename: MouseEvent.h
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
#ifndef MOUSEEVENT_H_
#define MOUSEEVENT_H_

#include "StdIncludes.h"

#include "IMouseEvent.h"

class MouseEvent : public IMouseEvent
{
public:
    MouseEvent();
    virtual ~MouseEvent();

    void SetEventType(MouseEventType::Enum type);
    void SetXPos(uint32_t pos);
    void SetYPos(uint32_t pos);
    void SetWheelDelta(float wheelDelta);
    void SetButtonPressed(MouseButtons::Enum button);
    void SetModifier(MouseModifiers::Enum modifier);

    virtual MouseEventType::Enum GetEventType() const;
    virtual int32_t GetXPos() const;
    virtual int32_t GetYPos() const;
    virtual float GetWheelDelta() const;
    virtual bool IsButtonPressed(MouseButtons::Enum button) const;
    virtual bool IsModifierEnabled(MouseModifiers::Enum modifier) const;

private:
    MouseEventType::Enum m_eventType;
    int32_t m_xPos;
    int32_t m_yPos;
    float m_wheelDelta;
    uint32_t m_buttonStates;
    uint32_t m_modifierStates;
};

#endif
