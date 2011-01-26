/**********************************************************************
*	Filename: Viewport.cpp
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
#include "PrecompiledIncludes.h"

#include "Viewport.h"

Viewport::Viewport()
: m_left(0), m_top(0), m_width(0), m_height(0)
{

}

Viewport::Viewport(int32_t left, int32_t top, int32_t width, int32_t height)
: m_left(left), m_top(top), m_width(width), m_height(height)
{

}

int32_t Viewport::GetLeft() const
{
	return m_left;
}

int32_t Viewport::GetTop() const
{
	return m_top;
}

int32_t Viewport::GetWidth() const
{
	return m_width;
}

int32_t Viewport::GetHeight() const
{
	return m_height;
}