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
    float magInv = 1.f/Magnitude(q);

    return Quaternion(q.x*magInv, q.y*magInv, q.z*magInv, q.w*magInv);
}

Quaternion Conjugate(const Quaternion& q)
{
	return Quaternion(-q.x, -q.y, -q.z, q.w);
}

Quaternion Inverse(const Quaternion& q)
{
    // inverse is defined as: inv = q* / ||q||
	float mag = Magnitude(q);

	if ( mag > 0.0f )
	{
		float invMag = 1.f/mag;
        
        Quaternion inverseQuaternion = Conjugate(q);
        inverseQuaternion.x *= invMag;
        inverseQuaternion.y *= invMag;
        inverseQuaternion.z *= invMag;
        inverseQuaternion.w *= invMag;
        
        return inverseQuaternion;
	}
	else
	{
		// need to signal bad operation, return an invalid quaternion
        assert(false);
		return Quaternion::Zero();
	}
}

float Dot(const Quaternion& q1, const Quaternion& q2)
{
	return ((q1.x*q2.x) + (q1.y*q2.y) + (q1.z*q2.z) + (q1.w*q2.w));
}

Vector3 Rotate(const Quaternion& q, const Vector3& v)
{
	Matrix4 rotMat = ToRotationMatrix(q);
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

Quaternion FromAxes(const Vector3& xAxis, const Vector3& yAxis, const Vector3& zAxis)
{
    // create rotation matrix from x,y,z axis
    Matrix4 m;
    m[0] = xAxis.x;
    m[1] = xAxis.y;
    m[2] = xAxis.z;
    m[3] = 0.f;

    m[4] = yAxis.x;
    m[5] = yAxis.y;
    m[6] = yAxis.z;
    m[7] = 0.f;

    m[8] = zAxis.x;
    m[9] = zAxis.y;
    m[10] = zAxis.z;
    m[11] = 0.f;

    m[12] = 0.f;
    m[13] = 0.f;
    m[14] = 0.f;
    m[15] = 1.f;

    return FromRotationMatrix(m);
}

Matrix4 ToRotationMatrix(const Quaternion& q)
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
	mat[0] = 1.0f - 2.0f*(y2+z2);		// [0][0]
	mat[4] = 2.0f*(xy-wz);				// [0][1]
	mat[8] = 2.0f*(xz+wy);				// [0][2]
	mat[12] = 0.f;						// [0][3]

	mat[1] = 2.0f*(xy+wz);				// [1][0]
	mat[5] = 1.0f - 2.0f*(x2+z2);		// [1][1]
	mat[9] = 2.0f*(yz-wx);				// [1][2]
	mat[13] = 0.f;						// [1][3]

	mat[2] = 2.0f*(xz-wy);				// [2][0]
	mat[6] = 2.0f*(yz+wx);				// [2][1]
	mat[10] = 1.0f - 2.0f*(x2+y2);		// [2][2]
	mat[14] = 0.f;						// [2][3]

	mat[3] = 0.f;						// [3][0]
	mat[7] = 0.f;						// [3][1]
	mat[11] = 0.f;						// [3][2]
	mat[15] = 1.f;						// [3][3]

	return mat;
}

Quaternion FromRotationMatrix(const Matrix4& m)
{
    Quaternion q;

    float trace = m[0] + m[5] + m[10] + 1.f;

    float tolerance = 0.00001f;

    if (trace > tolerance)
    {
        float root = std::sqrt(trace);
        q.w = 0.5f*root;
        root = 0.5f/root;
        q.x = (m[6]-m[9]) * root;
        q.y = (m[8]-m[2]) * root;
        q.z = (m[1]-m[4]) * root;
    }
    else
    {
        if (m[0] > m[5] && m[0] > m[10])
        {
            float root = std::sqrt(m[0] - m[5] - m[10] + 1.f);
            q.x = 0.5f*root;
            root = 0.5f/root;
            q.y = (m[1]-m[4]) * root;
            q.z = (m[8]-m[2]) * root;
            q.w = (m[6]-m[9]) * root;
        }
        else if (m[5] > m[10])
        {
            float root = std::sqrt(m[5] - m[0] - m[10] + 1.f);
            q.y = 0.5f*root;
            root = 0.5f/root;
            q.x = (m[1]-m[4]) * root;
            q.z = (m[6]-m[9]) * root;
            q.w = (m[8]-m[2]) * root;
        }
        else
        {
            float root = std::sqrt(m[10] - m[0] - m[5] + 1.f);
            q.z = 0.5f*root;
            root = 0.5f/root;
            q.x = (m[8]-m[2]) * root;
            q.y = (m[6]-m[9]) * root;
            q.w = (m[1]-m[4]) * root;
        }
    }

    return q;
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

