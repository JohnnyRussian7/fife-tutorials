/**********************************************************************
*	Filename: Vector2.cpp
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
#include "PrecompiledIncludes.h"

#include "Vector2.h"

Vector2 operator+(const Vector2& vector1, const Vector2& vector2)
{
    return Vector2(vector1.x+vector2.x, vector1.y+vector2.y);
}

Vector2 operator-(const Vector2& vector1, const Vector2& vector2)
{
    return Vector2(vector1.x-vector2.x, vector1.y-vector2.y);
}

Vector2 operator*(const Vector2& vector, float value)
{
    return Vector2(vector.x*value, vector.y*value);
}

Vector2 operator*(const Vector2& vector1, const Vector2& vector2)
{
    return Vector2(vector1.x*vector2.x, vector1.y*vector2.y);
}

Vector2 operator/(const Vector2& vector, float value)
{
    float inverseValue = 1.f/value;
    return Vector2(vector.x*inverseValue, vector.y*inverseValue);
}

float Magnitude(const Vector2& vector)
{
    return std::sqrt(vector.x*vector.x + vector.y*vector.y);
}

float MagnitudeSquare(const Vector2& vector)
{
    return (vector.x*vector.x + vector.y*vector.y);
}

Vector2 Normalize(const Vector2& vector)
{
    const float tolerance = 0.000001f;
    float length = Magnitude(vector);

    if (length < tolerance)
    {
        return vector;
    }

    float inverseMag = 1.f/length;
    return Vector2(vector.x*inverseMag, vector.y*inverseMag);
}

float Dot(const Vector2& vector1, const Vector2& vector2)
{
    return (vector1.x*vector2.x + vector1.y*vector2.y);
}
