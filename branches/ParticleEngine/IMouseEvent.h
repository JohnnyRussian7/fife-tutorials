/**********************************************************************
*	Filename: IMouseEvent.h
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
#ifndef IMOUSEEVENT_H_
#define IMOUSEEVENT_H_

#include "stdint.h"
#include "KeyCodes.h"

struct MouseEventType
{
    enum Enum
    {
        ButtonPress = 0,
        MouseMoved,
        MouseWheel,

        Max,
        Invalid = -1
    };
};

class IMouseEvent
{
public:
    virtual ~IMouseEvent() = 0 { };

    virtual MouseEventType::Enum GetEventType() = 0;
    virtual int32_t GetXPos() const = 0;
    virtual int32_t GetYPos() const = 0;
    virtual float GetWheelDelta() const = 0;
    virtual bool IsButtonPressed(MouseButtons::Enum button) const = 0;
    virtual bool IsModifierEnabled(MouseModifiers::Enum modifier) const = 0;
};

#endif
