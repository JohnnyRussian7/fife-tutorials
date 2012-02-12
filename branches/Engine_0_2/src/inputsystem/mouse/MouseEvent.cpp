/**********************************************************************
*	Filename: MouseEvent.cpp
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

#include "MouseEvent.h"

MouseEvent::MouseEvent()
: m_eventType(MouseEventType::Invalid), m_xPos(0), m_yPos(0), 
  m_xRel(0), m_yRel(0), m_wheelDelta(0.f), m_buttonStates(0), m_modifierStates(0)
{

}

MouseEvent::~MouseEvent()
{

}

void MouseEvent::SetEventType(MouseEventType::Enum type)
{
    m_eventType = type;
}

void MouseEvent::SetXPos(int32_t pos)
{
    m_xPos = pos;
}

void MouseEvent::SetYPos(int32_t pos)
{
    m_yPos = pos;
}

void MouseEvent::SetRelativeX(int32_t xRel)
{
    m_xRel = xRel;
}

void MouseEvent::SetRelativeY(int32_t yRel)
{
    m_yRel = yRel;
}

void MouseEvent::SetWheelDelta(float wheelDelta)
{
    m_wheelDelta = wheelDelta;
}

void MouseEvent::SetButtonPressed(MouseButtons::Enum button)
{
    m_buttonStates |= button;
}

void MouseEvent::SetModifier(MouseModifiers::Enum modifier)
{
    m_modifierStates |= modifier;
}

MouseEventType::Enum MouseEvent::GetEventType() const
{
    return m_eventType;
}

int32_t MouseEvent::GetXPos() const
{
    return m_xPos;
}

int32_t MouseEvent::GetYPos() const
{
    return m_yPos;
}

int32_t MouseEvent::GetRelativeX() const
{
    return m_xRel;
}

int32_t MouseEvent::GetRelativeY() const
{
    return m_yRel;
}

float MouseEvent::GetWheelDelta() const
{
    return m_wheelDelta;
}

bool MouseEvent::IsButtonPressed(MouseButtons::Enum button) const
{
    if (button == MouseButtons::Any)
    {
        return (m_buttonStates != 0);
    }

    return (m_buttonStates & button ? true : false);
}

bool MouseEvent::IsModifierEnabled(MouseModifiers::Enum modifier) const
{
    return (m_modifierStates & modifier ? true : false);
}