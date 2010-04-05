
#ifndef QUATERNION_H_
#define QUATERNION_H_

struct Vector3;
struct Matrix4;

struct Quaternion
{
	Quaternion(float x, float y, float z, float w): x(x), y(y), z(z), w(w) { };
	Quaternion(const Quaternion& rhs): x(rhs.x), y(rhs.y), z(rhs.z), w(rhs.w) { };
	inline Quaternion& operator=(const Quaternion& rhs);
	inline Quaternion& operator*=(const Quaternion& rhs);

	float x;
	float y;
	float z;
	float w;
};

Quaternion& Quaternion::operator=(const Quaternion& rhs)
{
	if (this != & rhs)
	{
		x = rhs.x;
		y = rhs.y;
		z = rhs.z;
		w = rhs.w;
	}

	return *this;
}

Quaternion& Quaternion::operator*=(const Quaternion& rhs)
{
	float tmpx = w*rhs.x + x*rhs.w + y*rhs.z - z*rhs.y;
	float tmpy = w*rhs.y + y*rhs.w + z*rhs.x - x*rhs.z;
	float tmpz = w*rhs.z + z*rhs.w + x*rhs.y - y*rhs.x;
	float tmpw = w*rhs.w - x*rhs.x - y*rhs.y - z*rhs.z;

	x = tmpx;
	y = tmpy;
	z = tmpz;
	w = tmpw;

	return *this;
}

// free function for binary quaternion operators
Quaternion operator*(const Quaternion& q1, const Quaternion& q2);
Vector3 operator*(const Quaternion& q, const Vector3& v);

// free helper functions for quaternion math
float magnitude(const Quaternion& q);
float magnitudeSquare(const Quaternion& q);
Quaternion normalize(const Quaternion& q);
Quaternion conjugate(const Quaternion& q);
Quaternion fromAxisAngle(const Vector3& v, float angle);
float toAxisAngle(const Quaternion& q, Vector3& v);
Quaternion fromEuler(float pitch, float yaw, float roll);
Matrix4 toMatrix(const Quaternion& q);

#endif
