/**********************************************************************
*	Filename: Rect.h
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
#ifndef RECT_H_
#define RECT_H_

#include "StdIncludes.h"

template <typename T>
struct Rect
{
    Rect() : m_left(T()), m_top(T()), m_right(T()), m_bottom(T()) { }
    Rect(T left, T top, T right, T bottom)
    : m_left(left), m_top(top), m_right(right), m_bottom(bottom)
    {

    }

    T m_left;
    T m_top;
    T m_right;
    T m_bottom;
};

typedef Rect<float> FloatRect;
typedef Rect<uint32_t> UintRect;
typedef Rect<int32_t> IntRect;

#endif
