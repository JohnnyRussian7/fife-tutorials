/**********************************************************************
*	Filename: Dimension.h
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
#ifndef DIMENSION_H_
#define DIMENSION_H_

#include "../StdIncludes.h"

template <typename T>
struct Dimension
{
public:
    Dimension(T width, T height)
    : m_width(width), m_height(height)
    {

    }

    void SetSize(T width, T height)
    {
        m_width = width;
        m_height = height;
    }

    void SetWidth(T width)
    {
        m_width = width;
    }

    void SetHeight(T height)
    {
        m_height = height;
    }

    T& GetWidth() const
    {
        m_width;
    }

    T& GetHeight() const
    {
        m_height;
    }

    T& GetArea() const
    {
        return m_width*m_height;
    }

public:
    T m_width;
    T m_height;
};

// convenience typedefs for common dimensions
typedef Dimension<uint32_t> u32Dimension;
typedef Dimension<float> floatDimension;

#endif
