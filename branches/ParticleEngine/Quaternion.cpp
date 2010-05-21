
#include <cmath>

#include "Quaternion.h"
#include "Vector.h"
#include "Matrix.h"
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
	Vector3 normVector = normalize(v);

	Quaternion normVectorQuaternion(normVector.x, normVector.y, normVector.z, 0.f);

	Quaternion result = normVectorQuaternion * conjugate(q);
	//result *= q;
	result = q * result;

	return Vector3(result.x, result.y, result.z);
}

float magnitude(const Quaternion& q)
{
	return std::sqrt(q.x*q.x + q.y*q.y + q.z*q.z + q.w*q.w);
}

float magnitudeSquare(const Quaternion& q)
{
	return q.x*q.x + q.y*q.y + q.z*q.z + q.w*q.w;
}

Quaternion normalize(const Quaternion& q)
{
	const float Tolerance = 0.00001f;

	float magSquared = magnitudeSquare(q);

	if (magSquared != 0.f && std::abs(magSquared - 1.0f) > Tolerance)
	{
		float mag = std::sqrt(magSquared);
		return Quaternion(q.x/mag, q.y/mag, q.z/mag, q.w/mag);
	}

	return q;
}

Quaternion conjugate(const Quaternion& q)
{
	return Quaternion(-q.x, -q.y, -q.z, q.w);
}

Quaternion fromAxisAngle(const Vector3& v, float angle)
{
	angle *= 0.5f;
	float sinAngle = std::sin(angle);

	Vector3 normVector = normalize(v);
	
	return Quaternion(normVector.x*sinAngle, 
						normVector.y*sinAngle, 
						normVector.z*sinAngle,				
						cos(angle));
}

float toAxisAngle(const Quaternion& q, Vector3& v)
{
    Quaternion normQuat(q);
    
    float scale = std::sqrt(1-normQuat.w*normQuat.w);
	
    if (scale < 0.0005)
    {
        scale = 1.f;
    }
    
    v.x = normQuat.x / scale;
    v.y = normQuat.y / scale;
    v.z = normQuat.z / scale;

	return (std::acos(normQuat.w) * 2.0f);
}

/*
* cosy = cos(yaw / 2)
* cosp = cos(pitch / 2)
* cosr = cos(roll / 2)
* siny = sin(yaw / 2)
* sinp = sin(pitch / 2)
* sinr = sin(roll / 2)

* x = siny*sinp*cosr + cosy*cosp*sinr
* y = siny*cosp*cosr + cosy*sinp*sinr
* z = cosy*sinp*cosr - siny*cosp*sinr
* w = cosy*cosp*cosr - siny*sinp*sinr
*/
Quaternion fromEuler(float pitch, float yaw, float roll)
{
	float p = DegToRad(pitch) / 2.0;
	float y = DegToRad(yaw) / 2.0;
	float r = DegToRad(roll) / 2.0;

	float sinp = std::sin(p);
	float siny = std::sin(y);
	float sinr = std::sin(r);
	float cosp = std::cos(p);
	float cosy = std::cos(y);
	float cosr = std::cos(r);

	return normalize(Quaternion(sinr*cosp*cosy - cosr*sinp*siny,
						cosr*sinp*cosy + sinr*cosp*siny,
						cosr*cosp*siny - sinr*sinp*cosy,
						cosr*cosp*cosy + sinr*sinp*siny));
}

Matrix4 toMatrix(const Quaternion& q)
{
	float x2 = q.x*q.x;
	float y2 = q.y*q.y;
	float z2 = q.z*q.z;
	float xy = q.x*q.y;
	float xz = q.x*q.z;
	float yz = q.y*q.z;
	float wx = q.w*q.x;
	float wy = q.w*q.y;
	float wz = q.w*q.z;

// 	return Matrix4(1.0f - 2.0f*(y2+z2), 2.0f*(xy-wz), 2.0f*(xz+wy), 0.0f,
// 					2.0f*(xy+wz), 1.0f - 2.0f*(x2+z2), 2.0f*(yz-wx), 0.0f,
// 					2.0f*(xz-wy), 2.0f*(yz+wx), 1.0f - 2.0f*(x2+y2), 0.0f,
// 					0.0f, 0.0f, 0.0f, 1.0f);

	return Matrix4(1.0f - 2.0f*(y2+z2), 2.0f*(xy-wz), 2.0f*(xz+wy), 0.0f,
		2.0f*(xy+wz), 1.0f - 2.0f*(x2+z2), 2.0f*(yz-wx), 0.0f,
		2.0f*(xz-wy), 2.0f*(yz+wx), 1.0f - 2.0f*(x2+y2), 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f);
}