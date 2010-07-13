
#ifndef MATH_UTIL_H_
#define MATH_UTIL_H_

struct Vector3;
struct Matrix4;
struct Quaternion;

const float pi = 3.14159f;
const float radtodeg = 180.f/pi;
const float degtorad = pi/180.f;

static float RadToDeg(float rad)
{
	return rad * radtodeg;
}

static float DegToRad(float deg)
{
	return deg * degtorad;
}

// creates a transform matrix based on scale, position, and orientation
// the applied ordering is (1) scale, (2) orientation, (3) translation
Matrix4 MakeTransform(const Vector3& scale, const Vector3& position, const Quaternion& orientation);

#endif
