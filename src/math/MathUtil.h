/**********************************************************************
*	Filename: MathUtil.h
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
#ifndef MATHUTIL_H_
#define MATHUTIL_H_

#include "../StdIncludes.h"

struct Vector3;
struct Matrix4;
struct Quaternion;

extern const float Pi;

bool IsEqual(float a, float b);
bool IsEqual(uint32_t a, uint32_t b);
bool IsEqual(int32_t a, int32_t b);

// radian/degree conversions
float RadToDeg(float rad);
float DegToRad(float deg);

// determines if a number is a power of 2
template <typename T>
bool IsPowerOf2(T n)
{
    return (n & (n-1)) == 0;
}

// finds next highest power of 2 for an unsigned 32-bit number
uint32_t NextPowerOf2(uint32_t n);

// creates a transform matrix based on scale, position, and orientation
// the applied ordering is (1) scale, (2) orientation, (3) translation
Matrix4 MakeTransform(const Vector3& scale, const Vector3& position, const Quaternion& orientation);

#endif
