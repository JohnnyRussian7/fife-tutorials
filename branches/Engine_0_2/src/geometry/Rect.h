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

#include "../StdIncludes.h"
#include "../math/MathUtil.h"

namespace fife {
    template <typename T>
    struct Rect
    {
        Rect() : m_left(T(0)), m_top(T(0)), m_right(T(0)), m_bottom(T(0)) { }
        Rect(T left, T top, T right, T bottom)
        : m_left(left), m_top(top), m_right(right), m_bottom(bottom)
        {
            
        }
        
        inline bool operator==(const Rect& rhs);
        inline bool operator!=(const Rect& rhs);
        
        T m_left;
        T m_top;
        T m_right;
        T m_bottom;
    };
    
    template <typename T>
    bool Rect<T>::operator==(const Rect& rhs)
    {
        return (IsEqual(m_left, rhs.m_left)
                && IsEqual(m_top, rhs.m_top)
                && IsEqual(m_right, rhs.m_right)
                && IsEqual(m_bottom, rhs.m_bottom));
    }
    
    template <typename T>
    bool Rect<T>::operator!=(const Rect& rhs)
    {
        return (!IsEqual(m_left, rhs.m_left)
                || !IsEqual(m_top, rhs.m_top)
                || !IsEqual(m_right, rhs.m_right)
                || !IsEqual(m_bottom, rhs.m_bottom));
    }
}

typedef fife::Rect<float> FloatRect;
typedef fife::Rect<uint32_t> UintRect;
typedef fife::Rect<int32_t> IntRect;

#endif
