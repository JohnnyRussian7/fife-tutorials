
#include <cmath>

#include "Vector.h"
#include "Quaternion.h"

Vector3 operator+(const Vector3& vector1, const Vector3& vector2)
{
	return Vector3(vector1.x+vector2.x, vector1.y+vector2.y, vector1.z+vector2.z);
}

Vector3 operator-(const Vector3& vector1, const Vector3& vector2)
{
	return Vector3(vector1.x-vector2.x, vector1.y-vector2.y, vector1.z-vector2.z);
}

Vector3 operator*(const Vector3& vector, float value)
{
	return Vector3(vector.x*value, vector.y*value, vector.z*value);
}

Vector3 operator/(const Vector3& vector, float value)
{
	float inverseValue = 1/value;
	return Vector3(vector.x*inverseValue, vector.y*inverseValue, vector.z*inverseValue);
}

float Magnitude(const Vector3& vector)
{
	return std::sqrt(vector.x*vector.x + vector.y*vector.y + vector.z*vector.z);
}

float MagnitudeSquare(const Vector3& vector)
{
	return (vector.x*vector.x + vector.y*vector.y + vector.z*vector.z);
}

Vector3 Normalize(const Vector3& vector)
{
    const float tolerance = 0.000001f;
    float length = MagnitudeSquare(vector);

    if ((length + tolerance >= 0.f) && (length - tolerance <= 0.f))
    {
        return vector;
    }

	float inverseMag = 1.f/Magnitude(vector);
	return Vector3(vector.x*inverseMag, vector.y*inverseMag, vector.z*inverseMag);
}

float Dot(const Vector3& vector1, const Vector3& vector2)
{
	return (vector1.x*vector2.x + vector1.y*vector2.y + vector1.z*vector2.z);
}

Vector3 cross(const Vector3& vector1, const Vector3& vector2)
{
	return Vector3((vector1.y*vector2.z - vector2.y*vector1.z), 
		(vector1.z*vector2.x - vector2.z-vector1.x),
		(vector1.x*vector2.y - vector2.x*vector1.y));
}

// provides shortest rotation arc between 2 vectors
// algorithm from Game Programming Gems 
// Section 2.10 The Shortest Arc Quaternion
// By Stan Melax
Quaternion GetRotationTo(const Vector3& source, const Vector3& dest)
{
// 	Vector3 normSource = Normalize(source);
// 	Vector3 normDest = Normalize(dest);

// 	Vector3 c = cross(source, dest);
// 	float d = Dot(source, dest);
// 	float s = std::sqrt((1+d)*2.f);
// 	float invs = 1.f/s;
//  Quaternion qnorm(Normalize(Quaternion(c.x*invs, c.y*invs, c.z*invs, s*0.5f)));

    // TODO - see if this could be more efficient
    Vector3 c = cross(source, dest);
    float d = Dot(source, dest);

    float wValue = std::sqrt(MagnitudeSquare(source) * MagnitudeSquare(dest)) + d;

    Quaternion qnorm(Normalize(Quaternion(c.x, c.y, c.z, wValue)));
	
	return qnorm;
}