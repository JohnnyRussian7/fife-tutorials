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

Vector3 Matrix4::GetX() const
{
    return Vector3(m_matrix[0], m_matrix[1], m_matrix[2]);
}

Vector3 Matrix4::GetY() const
{
    return Vector3(m_matrix[4], m_matrix[5], m_matrix[6]);
}

Vector3 Matrix4::GetZ() const
{
    return Vector3(m_matrix[8], m_matrix[9], m_matrix[10]);
}

Matrix4 operator*(const Matrix4& lhs, const Matrix4& rhs)
{
	Matrix4 result;

	result[0] = lhs[0]*rhs[0] + lhs[4]*rhs[1] + lhs[8]*rhs[2] + lhs[12]*rhs[3];
	result[1] = lhs[1]*rhs[0] + lhs[5]*rhs[1] + lhs[9]*rhs[2] + lhs[13]*rhs[3];
	result[2] = lhs[2]*rhs[0] + lhs[6]*rhs[1] + lhs[10]*rhs[2] + lhs[14]*rhs[3];
	result[3] = lhs[3]*rhs[0] + lhs[7]*rhs[1] + lhs[11]*rhs[2] + lhs[15]*rhs[3];
	
	result[4] = lhs[0]*rhs[4] + lhs[4]*rhs[5] + lhs[8]*rhs[6] + lhs[12]*rhs[7];
	result[5] = lhs[1]*rhs[4] + lhs[5]*rhs[5] + lhs[9]*rhs[6] + lhs[13]*rhs[7];
	result[6] = lhs[2]*rhs[4] + lhs[6]*rhs[5] + lhs[10]*rhs[6] + lhs[14]*rhs[7];
	result[7] = lhs[3]*rhs[4] + lhs[7]*rhs[5] + lhs[11]*rhs[6] + lhs[15]*rhs[7];

	result[8] = lhs[0]*rhs[8] + lhs[4]*rhs[9] + lhs[8]*rhs[10] + lhs[12]*rhs[11];
	result[9] = lhs[1]*rhs[8] + lhs[5]*rhs[9] + lhs[9]*rhs[10] + lhs[13]*rhs[11];
	result[10] = lhs[2]*rhs[8] + lhs[6]*rhs[9] + lhs[10]*rhs[10] + lhs[14]*rhs[11];
	result[11] = lhs[3]*rhs[8] + lhs[7]*rhs[9] + lhs[11]*rhs[10] + lhs[15]*rhs[11];

	result[12] = lhs[0]*rhs[12] + lhs[4]*rhs[13] + lhs[8]*rhs[14] + lhs[12]*rhs[15];
	result[13] = lhs[1]*rhs[12] + lhs[5]*rhs[13] + lhs[9]*rhs[14] + lhs[13]*rhs[15];
	result[14] = lhs[2]*rhs[12] + lhs[6]*rhs[13] + lhs[10]*rhs[14] + lhs[14]*rhs[15];
	result[15] = lhs[3]*rhs[12] + lhs[7]*rhs[13] + lhs[11]*rhs[14] + lhs[15]*rhs[15];

	return result;
}

Vector3 operator* (const Matrix4& mat, const Vector3& p)
{
	return Vector3(
		mat[0]*p.x +
		mat[4]*p.y +
		mat[8]*p.z,

		mat[1]*p.x +
		mat[5]*p.y +
		mat[9]*p.z,

		mat[2]*p.x +
		mat[6]*p.y +
		mat[10]*p.z
	);
}

Matrix4 Transpose(const Matrix4& mat)
{
    Matrix4 retMat(mat);

    retMat[1] = mat[4];
    retMat[4] = mat[1];

    retMat[2] = mat[8];
    retMat[8] = mat[2];

    retMat[6] = mat[9];
    retMat[9] = mat[6];

    return retMat;
}

void TransposeRef(Matrix4& mat)
{
    float temp = mat[1];
    mat[1] = mat[4];
    mat[4] = temp;

    temp = mat[2];
    mat[2] = mat[8];
    mat[8] = temp;

    temp = mat[6];
    mat[6] = mat[9];
    mat[9] = temp;
}

std::ostream& operator<<(std::ostream &os, const Matrix4& m)
{
    os  << std::setprecision(3) 
        << std::fixed
        << m[0] << std::setw(10) << m[4] << std::setw(10) << m[8] << std::setw(10) << m[12]    // row 1
        << std::endl
        << m[1] << std::setw(10) << m[5] << std::setw(10) << m[9] << std::setw(10) << m[13]    // row 2
        << std::endl
        << m[2] << std::setw(10) << m[6] << std::setw(10) << m[10] << std::setw(10) << m[14]   // row 3
        << std::endl
        << m[3] << std::setw(10) << m[7] << std::setw(10) << m[11] << std::setw(10) << m[15]    // row 4
        << std::endl;
    
    return os;
}
