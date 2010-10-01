/**********************************************************************
*	Filename: IMouseListener.h
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
#ifndef IMOUSELISTENER_H_
#define IMOUSELISTENER_H_

#include <string>

class IMouseEvent;

class IMouseListener
{
public:
    virtual ~IMouseListener() { };

    virtual const std::string& GetName() = 0;

    virtual bool OnMouseMoved(const IMouseEvent& event) = 0;
    virtual bool OnMousePressed(const IMouseEvent& event) = 0;
    virtual bool OnMouseReleased(const IMouseEvent& event) = 0;
};

#endif
