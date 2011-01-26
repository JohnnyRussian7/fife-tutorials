/**********************************************************************
*	Filename: Viewport.h
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
#ifndef VIEWPORT_H_
#define VIEWPORT_H_

#include "StdIncludes.h"

class Viewport
{
public:
	Viewport();
	Viewport(int32_t left, int32_t top, int32_t width, int32_t height);
	
	int32_t GetLeft() const;
	int32_t GetTop() const;
	int32_t GetWidth() const;
	int32_t GetHeight() const;

private:
	int32_t m_left;
	int32_t m_top;
	int32_t m_width;
	int32_t m_height;
};

#endif
