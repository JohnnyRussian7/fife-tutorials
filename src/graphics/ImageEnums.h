/**********************************************************************
*	Filename: ImageEnums.h
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
#ifndef IMAGEENUMS_H_
#define IMAGEENUMS_H_

#include "../StdIncludes.h"

struct ColorFormat
{
    enum Enum
    {
        R8G8B8,		// RGB 24-bit 
        R8G8B8A8	// RGBA 32-bit
    };

    static uint32_t GetBitsPerPixel(Enum type)
    {
        switch (type)
        {
        case R8G8B8:
            return 24;

        case R8G8B8A8:
            return 32;

        default:
            return 0;
        }
    }
};

#endif
