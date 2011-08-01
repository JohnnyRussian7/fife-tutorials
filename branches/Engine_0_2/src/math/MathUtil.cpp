/**********************************************************************
*	Filename: MathUtil.cpp
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

#include "MathUtil.h"
#include "Vector3.h"
#include "Matrix4.h"
#include "Quaternion.h"

const float Pi = 3.14159f;
const float Rad2Deg = 180.f/Pi;
const float Deg2Rad = Pi/180.f;
const float fEpsilon = 0.00001f;

bool IsEqual(float a, float b)
{
    if (std::abs(a-b) < fEpsilon)
    {
        return true;
    }

    return false;
}

bool IsEqual(uint32_t a, uint32_t b)
{
    return (a == b);
}

bool IsEqual(int32_t a, int32_t b)
{
    return (a == b);
}

float RadToDeg(float rad)
{
    return rad * Rad2Deg;
}

float DegToRad(float deg)
{
    return deg * Deg2Rad;
}

uint32_t NextPowerOf2(uint32_t n)
{
    --n;
    n |= n >> 16;
    n |= n >> 8;
    n |= n >> 4;
    n |= n >> 2;
    n |= n >> 1;
    ++n;

    return n;
}

Matrix4 MakeTransform(const Vector3& scale, const Vector3& position, const Quaternion& orientation)
{
	// convert orientation to rotation matrix
	Matrix4 rotMatrix = ToRotationMatrix(orientation);

	// no projection, this is currently being done in ToRotationMatrix call above
	//rotMatrix[3] = 0.f;
	//rotMatrix[7] = 0.f;
	//rotMatrix[11] = 0.f;
	//rotMatrix[15] = 1.f;

	// apply scale
	rotMatrix[0] = scale.x * rotMatrix[0];
	rotMatrix[1] = scale.y * rotMatrix[1];
	rotMatrix[2] = scale.z * rotMatrix[2];

	rotMatrix[4] = scale.x * rotMatrix[4];
	rotMatrix[5] = scale.y * rotMatrix[5];
	rotMatrix[6] = scale.z * rotMatrix[6];

	rotMatrix[8] = scale.x * rotMatrix[8];
	rotMatrix[9] = scale.y * rotMatrix[9];
	rotMatrix[10] = scale.z * rotMatrix[10];

	// apply translation
	rotMatrix[12] = position.x;
	rotMatrix[13] = position.y;
	rotMatrix[14] = position.z;

	return rotMatrix;
}

