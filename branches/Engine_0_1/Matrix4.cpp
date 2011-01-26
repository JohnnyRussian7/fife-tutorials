/**********************************************************************
*	Filename: Matrix4.cpp
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

#include "Matrix4.h"
#include "Vector3.h"

Matrix4 operator*(const Matrix4& lhs, const Matrix4& rhs)
{
	Matrix4 result;

	result.matrix[0] = lhs.matrix[0]*rhs.matrix[0] + lhs.matrix[4]*rhs.matrix[1] + lhs.matrix[8]*rhs.matrix[2] + lhs.matrix[12]*rhs.matrix[3];
	result.matrix[1] = lhs.matrix[1]*rhs.matrix[0] + lhs.matrix[5]*rhs.matrix[1] + lhs.matrix[9]*rhs.matrix[2] + lhs.matrix[13]*rhs.matrix[3];
	result.matrix[2] = lhs.matrix[2]*rhs.matrix[0] + lhs.matrix[6]*rhs.matrix[1] + lhs.matrix[10]*rhs.matrix[2] + lhs.matrix[14]*rhs.matrix[3];
	result.matrix[3] = lhs.matrix[3]*rhs.matrix[0] + lhs.matrix[7]*rhs.matrix[1] + lhs.matrix[11]*rhs.matrix[2] + lhs.matrix[15]*rhs.matrix[3];
	
	result.matrix[4] = lhs.matrix[0]*rhs.matrix[4] + lhs.matrix[4]*rhs.matrix[5] + lhs.matrix[8]*rhs.matrix[6] + lhs.matrix[12]*rhs.matrix[7];
	result.matrix[5] = lhs.matrix[1]*rhs.matrix[4] + lhs.matrix[5]*rhs.matrix[5] + lhs.matrix[9]*rhs.matrix[6] + lhs.matrix[13]*rhs.matrix[7];
	result.matrix[6] = lhs.matrix[2]*rhs.matrix[4] + lhs.matrix[6]*rhs.matrix[5] + lhs.matrix[10]*rhs.matrix[6] + lhs.matrix[14]*rhs.matrix[7];
	result.matrix[7] = lhs.matrix[3]*rhs.matrix[4] + lhs.matrix[7]*rhs.matrix[5] + lhs.matrix[11]*rhs.matrix[6] + lhs.matrix[15]*rhs.matrix[7];

	result.matrix[8] = lhs.matrix[0]*rhs.matrix[8] + lhs.matrix[4]*rhs.matrix[9] + lhs.matrix[8]*rhs.matrix[10] + lhs.matrix[12]*rhs.matrix[11];
	result.matrix[9] = lhs.matrix[1]*rhs.matrix[8] + lhs.matrix[5]*rhs.matrix[9] + lhs.matrix[9]*rhs.matrix[10] + lhs.matrix[13]*rhs.matrix[11];
	result.matrix[10] = lhs.matrix[2]*rhs.matrix[8] + lhs.matrix[6]*rhs.matrix[9] + lhs.matrix[10]*rhs.matrix[10] + lhs.matrix[14]*rhs.matrix[11];
	result.matrix[11] = lhs.matrix[3]*rhs.matrix[8] + lhs.matrix[7]*rhs.matrix[9] + lhs.matrix[11]*rhs.matrix[10] + lhs.matrix[15]*rhs.matrix[11];

	result.matrix[12] = lhs.matrix[0]*rhs.matrix[12] + lhs.matrix[4]*rhs.matrix[13] + lhs.matrix[8]*rhs.matrix[14] + lhs.matrix[12]*rhs.matrix[15];
	result.matrix[13] = lhs.matrix[1]*rhs.matrix[12] + lhs.matrix[5]*rhs.matrix[13] + lhs.matrix[9]*rhs.matrix[14] + lhs.matrix[13]*rhs.matrix[15];
	result.matrix[14] = lhs.matrix[2]*rhs.matrix[12] + lhs.matrix[6]*rhs.matrix[13] + lhs.matrix[10]*rhs.matrix[14] + lhs.matrix[14]*rhs.matrix[15];
	result.matrix[15] = lhs.matrix[3]*rhs.matrix[12] + lhs.matrix[7]*rhs.matrix[13] + lhs.matrix[11]*rhs.matrix[14] + lhs.matrix[15]*rhs.matrix[15];

	return result;
}

Vector3 operator* (const Matrix4& mat, const Vector3& p)
{
	return Vector3(
		mat.matrix[0]*p.x +
		mat.matrix[4]*p.y +
		mat.matrix[8]*p.z,

		mat.matrix[1]*p.x +
		mat.matrix[5]*p.y +
		mat.matrix[9]*p.z,

		mat.matrix[2]*p.x +
		mat.matrix[6]*p.y +
		mat.matrix[10]*p.z
	);
}
