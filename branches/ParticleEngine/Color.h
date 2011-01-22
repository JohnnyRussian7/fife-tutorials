/**********************************************************************
*	Filename: Color.h
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
#ifndef COLOR_H_
#define COLOR_H_

#include "StdIncludes.h"

struct Color
{
	Color(): r(0.f), g(0.f), b(0.f), a(1.f) { };
	Color(float r, float g, float b, float a=1.f): r(r), g(g), b(b), a(a) { };

    static Color Black()
    {
        return Color(0.f, 0.f, 0.f);
    }

    static Color White()
    {
        return Color(1.f, 1.f, 1.f);
    }

    static Color Red()
    {
        return Color(1.f, 0.f, 0.f);
    }

    static Color Green()
    {
        return Color(0.f, 1.f, 0.f);
    }

    static Color Blue()
    {
        return Color(0.f, 0.f, 1.f);
    }

	float r;
	float g;
	float b;
	float a;
};

inline Color interpolate(const Color& color1, const Color& color2, float scale)
{
	// clamp value in range [0,1] and compute inverse
	float value = (std::min)((std::max)(scale, 0.f), 1.f);
	float inverse = 1.f - value;

	Color retColor;
	retColor.r = color2.r*inverse + color1.r*value;
	retColor.g = color2.g*inverse + color1.g*value;
	retColor.b = color2.b*inverse + color1.b*value;
	retColor.a = color2.a*inverse + color1.a*value;
	return retColor;
}



#endif
