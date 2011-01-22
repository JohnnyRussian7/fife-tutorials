/**********************************************************************
*	Filename: KeyEvent.cpp
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

#include "KeyEvent.h"

KeyEvent::KeyEvent()
: m_keyCode(static_cast<KeyCodes::Enum>(0)), m_character(0), m_keyPressed(false), m_modifiers(0)
{

}

void KeyEvent::SetKeyCode(KeyCodes::Enum keyCode)
{
    m_keyCode = keyCode;
}

void KeyEvent::SetText(uint32_t text)
{
    m_character = text;
}

void KeyEvent::SetModifier(KeyModifiers::Enum modifier)
{
    m_modifiers |= modifier;
}

void KeyEvent::SetKeyPressed(bool pressed)
{
    m_keyPressed = pressed;
}

KeyCodes::Enum KeyEvent::GetKeyCode() const
{
    return m_keyCode;
}

uint32_t KeyEvent::GetText() const
{
    return m_character;
}

bool KeyEvent::IsKeyPressed() const
{
    return m_keyPressed;
}

bool KeyEvent::IsModifierEnabled(KeyModifiers::Enum modifier) const
{
    return (m_modifiers & modifier ? true : false);
}
