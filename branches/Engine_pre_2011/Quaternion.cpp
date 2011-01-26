/**********************************************************************
*	Filename: Quaternion.cpp
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

#include "Quaternion.h"
#include "Vector3.h"
#include "Matrix4.h"
#include "MathUtil.h"

Quaternion operator*(const Quaternion& q1, const Quaternion& q2)
{
	return Quaternion(q1.w*q2.x + q1.x*q2.w + q1.y*q2.z - q1.z*q2.y,
						q1.w*q2.y + q1.y*q2.w + q1.z*q2.x - q1.x*q2.z,
						q1.w*q2.z + q1.z*q2.w + q1.x*q2.y - q1.y*q2.x,
						q1.w*q2.w - q1.x*q2.x - q1.y*q2.y - q1.z*q2.z);
}

Vector3 operator*(const Quaternion& q, const Vector3& v)
{
	Quaternion result = q * Quaternion(v.x, v.y, v.z, 0.f) * Conjugate(q);

	return Vector3(result.x, result.y, result.z);
}

float Magnitude(const Quaternion& q)
{
	return std::sqrt(q.x*q.x + q.y*q.y + q.z*q.z + q.w*q.w);
}

float MagnitudeSquare(const Quaternion& q)
{
	return q.x*q.x + q.y*q.y + q.z*q.z + q.w*q.w;
}

Quaternion Normalize(const Quaternion& q)
{
	const float Tolerance = 0.00001f;

	float magSquared = MagnitudeSquare(q);

	if (magSquared != 0.f && std::abs(magSquared - 1.0f) > Tolerance)
	{
		float mag = 1.f/std::sqrt(magSquared);
		return Quaternion(q.x*mag, q.y*mag, q.z*mag, q.w*mag);
	}

	return q;
}

Quaternion Conjugate(const Quaternion& q)
{
	return Quaternion(-q.x, -q.y, -q.z, q.w);
}

Quaternion Inverse(const Quaternion& q)
{
	float magSqr = MagnitudeSquare(q);

	if ( magSqr > 0.0 )
	{
		float invMag = 1.f/magSqr;
		return Quaternion(-q.x*invMag, -q.y*invMag, -q.z*invMag, q.w*invMag);
	}
	else
	{
		// need to signal bad operation, return an invalid quaternion
		return Quaternion::Zero();
	}
}

float Dot(const Quaternion& q1, const Quaternion& q2)
{
	return ((q1.x*q2.x) + (q1.y*q2.y) + (q1.z*q2.z) + (q1.w*q2.w));
}

Vector3 Rotate(const Quaternion& q, const Vector3& v)
{
	Matrix4 rotMat = ToMatrix(q);
	return rotMat*v;
}

Quaternion FromAxisAngle(const Vector3& v, float angle)
{
	angle *= 0.5f;
	float sinAngle = std::sin(angle);

	Vector3 normVector = Normalize(v);
	
	return Quaternion(normVector.x*sinAngle, 
						normVector.y*sinAngle, 
						normVector.z*sinAngle,				
						std::cos(angle));
}

float ToAxisAngle(const Quaternion& q, Vector3& v)
{
	// The quaternion representing the rotation is
	//   q = cos(A/2)+sin(A/2)*(x*i+y*j+z*k)

	float sqrLength = q.x*q.x + q.y*q.y + q.z*q.z;
	if (sqrLength > 0.0f)
	{
		float invLength = 1.0f/std::sqrt(sqrLength);

		v.x = q.x*invLength;
		v.y = q.y*invLength;
		v.z = q.z*invLength;

		return 2.f*std::acos(q.w);
	}
	else
	{
		// angle is 0 (mod 2*pi), so any axis will do.
		v.x = 1.0f;
		v.y = 0.0f;
		v.z = 0.0f;

		return 0.f;
	}
}

Quaternion FromEuler(float pitch, float yaw, float roll)
{
	float p = DegToRad(pitch) / 2.f;
	float y = DegToRad(yaw) / 2.f;
	float r = DegToRad(roll) / 2.f;

	float sinp = std::sin(p);
	float siny = std::sin(y);
	float sinr = std::sin(r);
	float cosp = std::cos(p);
	float cosy = std::cos(y);
	float cosr = std::cos(r);

	return Normalize(Quaternion(sinr*cosp*cosy - cosr*sinp*siny,
						cosr*sinp*cosy + sinr*cosp*siny,
						cosr*cosp*siny - sinr*sinp*cosy,
						cosr*cosp*cosy + sinr*sinp*siny));
}

Matrix4 ToMatrix(const Quaternion& q)
{
	const float x2 = q.x*q.x;
	const float y2 = q.y*q.y;
	const float z2 = q.z*q.z;
	const float xy = q.x*q.y;
	const float xz = q.x*q.z;
	const float yz = q.y*q.z;
	const float wx = q.w*q.x;
	const float wy = q.w*q.y;
	const float wz = q.w*q.z;

	// filling up row-wise
	Matrix4 mat;
	mat.matrix[0] = 1.0f - 2.0f*(y2+z2);		// [0][0]
	mat.matrix[4] = 2.0f*(xy-wz);				// [0][1]
	mat.matrix[8] = 2.0f*(xz+wy);				// [0][2]
	mat.matrix[12] = 0.f;						// [0][3]

	mat.matrix[1] = 2.0f*(xy+wz);				// [1][0]
	mat.matrix[5] = 1.0f - 2.0f*(x2+z2);		// [1][1]
	mat.matrix[9] = 2.0f*(yz-wx);				// [1][2]
	mat.matrix[13] = 0.f;						// [1][3]

	mat.matrix[2] = 2.0f*(xz-wy);				// [2][0]
	mat.matrix[6] = 2.0f*(yz+wx);				// [2][1]
	mat.matrix[10] = 1.0f - 2.0f*(x2+y2);		// [2][2]
	mat.matrix[14] = 0.f;						// [2][3]

	mat.matrix[3] = 0.f;						// [3][0]
	mat.matrix[7] = 0.f;						// [3][1]
	mat.matrix[11] = 0.f;						// [3][2]
	mat.matrix[15] = 1.f;						// [3][3]

	return mat;
}

Vector3 XAxis(const Quaternion& q)
{
	const float y2 = q.y*q.y;
	const float z2 = q.z*q.z;
	const float xy = q.x*q.y;
	const float xz = q.x*q.z;
	const float wy = q.w*q.y;
	const float wz = q.w*q.z;

	return Vector3(1.0f - 2.0f*(y2+z2), 2.0f*(xy-wz), 2.0f*(xz+wy));
}

Vector3 YAxis(const Quaternion& q)
{
	const float x2 = q.x*q.x;
	const float z2 = q.z*q.z;
	const float xy = q.x*q.y;
	const float yz = q.y*q.z;
	const float wx = q.w*q.x;
	const float wz = q.w*q.z;

	return Vector3(2.0f*(xy+wz), 1.0f - 2.0f*(x2+z2), 2.0f*(yz-wx));
}

Vector3 ZAxis(const Quaternion& q)
{
	const float x2 = q.x*q.x;
	const float y2 = q.y*q.y;
	const float xz = q.x*q.z;
	const float yz = q.y*q.z;
	const float wx = q.w*q.x;
	const float wy = q.w*q.y;

	return Vector3(2.0f*(xz-wy), 2.0f*(yz+wx), 1.0f - 2.0f*(x2+y2));
}

// Interpolates between quaternions using spherical linear interpolation.
// algorithm from: http://www.geometrictools.com
Quaternion Slerp(float t, const Quaternion& p, const Quaternion& q)
{
	Quaternion ret;

	float cs = Dot(p, q);
	float angle = std::acos(cs);

	if (std::abs(angle) > 0.0f)
	{
		float sn = std::sin(angle);
		float invSn = 1.0f/sn;
		float tAngle = t*angle;
		float coeff0 = std::sin(angle - tAngle)*invSn;
		float coeff1 = std::sin(tAngle)*invSn;

		ret.x = coeff0*p.x + coeff1*q.x;
		ret.y = coeff0*p.y + coeff1*q.y;
		ret.z = coeff0*p.z + coeff1*q.z;
		ret.w = coeff0*p.w + coeff1*q.w;
	}
	else
	{
		ret.x = p.x;
		ret.y = p.y;
		ret.z = p.z;
		ret.w = p.w;
	}

	return ret;
}

// Interpolates between quaternions using spherical quadrangle interpolation.
// algorithm from: http://www.geometrictools.com
Quaternion Squad(float t, const Quaternion& q0, const Quaternion& a0, 
				 const Quaternion& a1, const Quaternion& q1)
{
	float slerpT = 2.0f*t*(1.0f - t);
	Quaternion slerpP = Slerp(t, q0, q1);
	Quaternion slerpQ = Slerp(t, a0, a1);
	return Slerp(slerpT, slerpP, slerpQ);
}

