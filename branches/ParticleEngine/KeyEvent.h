/**********************************************************************
*	Filename: KeyEvent.h
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
#ifndef KEYEVENT_H_
#define KEYEVENT_H_

#include "stdint.h"
#include "IKeyEvent.h"
#include "KeyCodes.h"

class KeyEvent : public IKeyEvent
{
public:
    KeyEvent();

    void SetKeyCode(KeyCodes::Enum keyCode);
    void SetText(uint32_t text);
    void SetModifier(KeyModifiers::Enum modifier);
    void SetKeyPressed(bool pressed);

    virtual KeyCodes::Enum GetKeyCode() const;
    virtual uint32_t GetText() const;
    virtual bool IsKeyPressed() const;
    virtual bool IsModifierEnabled(KeyModifiers::Enum modifier) const;

private:
    KeyCodes::Enum m_keyCode;
    uint32_t m_character;
    bool m_keyPressed;
    uint32_t m_modifiers;
};


#endif