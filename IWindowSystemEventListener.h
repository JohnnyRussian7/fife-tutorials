/**********************************************************************
*	Filename: IWindowSystemEventListener.h
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
#ifndef IWINDOW_SYSTEM_EVENT_LISTENER_H_
#define IWINDOW_SYSTEM_EVENT_LISTENER_H_

#include "StdIncludes.h"

class IWindowSystemEventListener
{
public:
	virtual void OnResize(uint32_t width, uint32_t height) = 0;
};

#endif
