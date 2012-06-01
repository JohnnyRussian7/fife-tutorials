/**********************************************************************
*	Filename: Vector3.cpp
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

#include "Vector3.h"
#include "Quaternion.h"

Vector3 operator+(const Vector3& vector1, const Vector3& vector2)
{
	return Vector3(vector1.x+vector2.x, vector1.y+vector2.y, vector1.z+vector2.z);
}

Vector3 operator-(const Vector3& vector1, const Vector3& vector2)
{
	return Vector3(vector1.x-vector2.x, vector1.y-vector2.y, vector1.z-vector2.z);
}

Vector3 operator*(const Vector3& vector, float value)
{
	return Vector3(vector.x*value, vector.y*value, vector.z*value);
}

Vector3 operator*(float value, const Vector3& vector)
{
	return Vector3(vector.x*value, vector.y*value, vector.z*value);
}

Vector3 operator*(const Vector3& vector1, const Vector3& vector2)
{
    return Vector3(vector1.x*vector2.x, vector1.y*vector2.y, vector1.z*vector2.z);
}

Vector3 operator/(const Vector3& vector, float value)
{
	float inverseValue = 1.f/value;
	return Vector3(vector.x*inverseValue, vector.y*inverseValue, vector.z*inverseValue);
}

Vector3 operator/(const Vector3& v1, const Vector3& v2)
{
    return Vector3(v1.x/v2.x, v1.y/v2.y, v1.z/v2.z);
}

float Magnitude(const Vector3& vector)
{
	return std::sqrt(vector.x*vector.x + vector.y*vector.y + vector.z*vector.z);
}

float MagnitudeSquare(const Vector3& vector)
{
	return (vector.x*vector.x + vector.y*vector.y + vector.z*vector.z);
}

Vector3 ElemMult(const Vector3& lhs, const Vector3& rhs)
{
    return Vector3(lhs.x*rhs.x, lhs.y*rhs.y, lhs.z*rhs.z);
}

Vector3 ElemDiv(const Vector3& lhs, const Vector3& rhs)
{
    return Vector3(lhs.x/rhs.x, lhs.y/rhs.y, lhs.z/rhs.z);
}

Vector3 Normalize(const Vector3& vector)
{
    const float tolerance = 0.000001f;
    float length = Magnitude(vector);

    if (length < tolerance)
    {
        return vector;
    }

	float inverseLength = 1.f/length;
	return Vector3(vector.x*inverseLength, vector.y*inverseLength, vector.z*inverseLength);
}

float Dot(const Vector3& vector1, const Vector3& vector2)
{
	return (vector1.x*vector2.x + vector1.y*vector2.y + vector1.z*vector2.z);
}

Vector3 Cross(const Vector3& vector1, const Vector3& vector2)
{
	return Vector3((vector1.y*vector2.z - vector2.y*vector1.z), 
		(vector1.z*vector2.x - vector2.z-vector1.x),
		(vector1.x*vector2.y - vector2.x*vector1.y));
}

Quaternion GetRotationTo(const Vector3& source, const Vector3& dest)
{
    // TODO - see if this could be more efficient
    Vector3 c = Cross(source, dest);
    float d = Dot(source, dest);

    float wValue = std::sqrt(MagnitudeSquare(source) * MagnitudeSquare(dest)) + d;

    Quaternion qnorm(Normalize(Quaternion(c.x, c.y, c.z, wValue)));
	
	return qnorm;
}

std::ostream& operator<<(std::ostream& os, const Vector3& v)
{
    os  << std::setprecision(3)
        << std::fixed
        << v.x << std::setw(10) << v.y << std::setw(10) << v.z
        << std::endl;
    
    return os;
}