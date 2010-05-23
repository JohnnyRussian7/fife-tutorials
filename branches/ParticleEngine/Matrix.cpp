
#include "Matrix.h"

Matrix4 operator*(const Matrix4& lhs, const Matrix4& rhs)
{
	Matrix4 result = Matrix4::Zero();

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

	/*
	for (int i=0; i < 16; ++i)
	{
		for (int j=0; j < 4; ++j)
		{
			result.matrix[i] += rhs.matrix[j+4*i] * lhs.matrix[i+j];
		}
	}
	*/

	return result;
}