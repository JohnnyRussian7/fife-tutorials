/**********************************************************************
*	Filename: Vector3.h
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
#ifndef VECTOR3_H_
#define VECTOR3_H_

#include "MathUtil.h"

struct Quaternion;

struct Vector3
{
	Vector3(float x=0, float y=0, float z=0): x(x), y(y), z(z) { }
	Vector3(const Vector3& rhs): x(rhs.x), y(rhs.y), z(rhs.z) { }
	inline Vector3 operator-() const;
	inline Vector3& operator=(const Vector3& rhs);
	inline Vector3& operator+=(const Vector3& rhs);
	inline Vector3& operator-=(const Vector3& rhs);
	inline Vector3& operator*=(float value);
	inline Vector3& operator/=(float value);
	inline bool operator==(const Vector3& rhs) const;
    inline bool operator!=(const Vector3& rhs) const;
    
    inline float& operator[](uint32_t index) 
    {
        switch (index)
        {
            case 0:
                return x;
            case 1:
                return y;
            case 2:
                return z;
            default:
                return x;
        }
    };
    
    inline const float& operator[](uint32_t index) const
    {
        switch (index)
        {
            case 0:
                return x;
            case 1:
                return y;
            case 2:
                return z;
            default:
                return x;
        }
    }
    
	static Vector3 Zero()
	{
		static Vector3 zero(0.f, 0.f, 0.f);
		return zero;
	}
	static Vector3 UnitX() 
	{ 
		static Vector3 unitX(1.f, 0.f, 0.f);
		return unitX;
	}
	static Vector3 UnitY() 
	{ 
		static Vector3 unitY(0.f, 1.f, 0.f);
		return unitY; 
	}
	static Vector3 UnitZ() 
	{ 
		static Vector3 unitZ(0.f, 0.f, 1.f);
		return unitZ; 
	}

	float x;
	float y;
	float z;
};

Vector3 Vector3::operator-() const
{
	return Vector3(-x, -y, -z);	
}

Vector3& Vector3::operator=(const Vector3& rhs)
{
	if (this != &rhs)
	{
		x = rhs.x;
		y = rhs.y;
		z = rhs.z;
	}
	
	return *this;
}

Vector3& Vector3::operator+=(const Vector3& rhs)
{
	x += rhs.x;
	y += rhs.y;
	z += rhs.z;

	return *this;
}

Vector3& Vector3::operator-=(const Vector3& rhs)
{
	x -= rhs.x;
	y -= rhs.y;
	z -= rhs.z;

	return *this;
}

Vector3& Vector3::operator*=(float value)
{
	x *= value;
	y *= value;
	z *= value;
	
	return *this;
}

Vector3& Vector3::operator/=(float value)
{
	float inverseValue = 1/value;
	x *= inverseValue;
	y *= inverseValue;
	z *= inverseValue;

	return *this;
}

bool Vector3::operator==(const Vector3& rhs) const
{
	return (IsEqual(x, rhs.x)
            && IsEqual(y, rhs.y)
            && IsEqual(z, rhs.z));
}

bool Vector3::operator!=(const Vector3& rhs) const
{
    return (!IsEqual(x, rhs.x) 
            || !IsEqual(y, rhs.y)
            || !IsEqual(z, rhs.z));
}

// free functions for binary vector operators
Vector3 operator+(const Vector3& vector1, const Vector3& vector2);
Vector3 operator-(const Vector3& vector1, const Vector3& vector2);
Vector3 operator*(const Vector3& vector, float value);
Vector3 operator*(float value, const Vector3& vector);
Vector3 operator*(const Vector3& vector1, const Vector3& vector2);
Vector3 operator/(const Vector3& vector, float value);
Vector3 operator/(const Vector3& v1, const Vector3& v2);

// free functions for vector math
float Magnitude(const Vector3& vector);
float MagnitudeSquare(const Vector3& vector);
Vector3 ElemMult(const Vector3& lhs, const Vector3& rhs);
Vector3 ElemDiv(const Vector3& lhs, const Vector3& rhs);
Vector3 Normalize(const Vector3& vector);
float Dot(const Vector3& vector1, const Vector3& vector2);
Vector3 Cross(const Vector3& vector1, const Vector3& vector2);
Quaternion GetRotationTo(const Vector3& source, const Vector3& dest);


std::ostream& operator<<(std::ostream& os, const Vector3& v);

#endif
