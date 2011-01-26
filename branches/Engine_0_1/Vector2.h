/**********************************************************************
*	Filename: Vector2.h
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
#ifndef VECTOR2_H_
#define VECTOR2_H_

struct Vector2
{
    Vector2(float x=0, float y=0): x(x), y(y) { }
    Vector2(const Vector2& rhs): x(rhs.x), y(rhs.y) { }
    inline Vector2 operator-() const;
    inline Vector2& operator=(const Vector2& rhs);
    inline Vector2& operator+=(const Vector2& rhs);
    inline Vector2& operator-=(const Vector2& rhs);
    inline Vector2& operator*=(float value);
    inline Vector2& operator/=(float value);
    inline bool operator==(const Vector2& rhs) const;

    static Vector2 Zero()
    {
        static Vector2 zero(0.f, 0.f);
        return zero;
    }
    static Vector2 UnitX() 
    { 
        static Vector2 unitX(1.f, 0.f);
        return unitX;
    }
    static Vector2 UnitY() 
    { 
        static Vector2 unitY(0.f, 1.f);
        return unitY; 
    }

    float x;
    float y;
};

Vector2 Vector2::operator-() const
{
    return Vector2(-x, -y);	
}

Vector2& Vector2::operator=(const Vector2& rhs)
{
    if (this != &rhs)
    {
        x = rhs.x;
        y = rhs.y;
    }

    return *this;
}

Vector2& Vector2::operator+=(const Vector2& rhs)
{
    x += rhs.x;
    y += rhs.y;

    return *this;
}

Vector2& Vector2::operator-=(const Vector2& rhs)
{
    x -= rhs.x;
    y -= rhs.y;

    return *this;
}

Vector2& Vector2::operator*=(float value)
{
    x *= value;
    y *= value;

    return *this;
}

Vector2& Vector2::operator/=(float value)
{
    float inverseValue = 1/value;
    x *= inverseValue;
    y *= inverseValue;

    return *this;
}

bool Vector2::operator==(const Vector2& rhs) const
{
    return (x == rhs.x && y == rhs.y);
}

// free functions for binary vector operators
Vector2 operator+(const Vector2& vector1, const Vector2& vector2);
Vector2 operator-(const Vector2& vector1, const Vector2& vector2);
Vector2 operator*(const Vector2& vector, float value);
Vector2 operator*(const Vector2& vector1, const Vector2& vector2);
Vector2 operator/(const Vector2& vector, float value);

// free functions for vector math
float Magnitude(const Vector2& vector);
float MagnitudeSquare(const Vector2& vector);
Vector2 Normalize(const Vector2& vector);
float Dot(const Vector2& vector1, const Vector2& vector2);

#endif