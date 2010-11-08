
#include <cmath>

#include "Vector3.h"
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

Vector3 operator*(const Vector3& vector1, const Vector3& vector2)
{
    return Vector3(vector1.x*vector2.x, vector1.y*vector2.y, vector1.z*vector2.z);
}

Vector3 operator/(const Vector3& vector, float value)
{
	float inverseValue = 1.f/value;
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

Vector3 ElemMult(const Vector3& lhs, const Vector3& rhs)
{
    return Vector3(lhs.x*rhs.x, lhs.y*rhs.y, lhs.z*rhs.z);
}

Vector3 ElemDiv(const Vector3& lhs, const Vector3& rhs)
{
    return Vector3(lhs.x/rhs.x, lhs.y/rhs.y, lhs.z/rhs.z);
}

Vector3 Normalize(const Vector3& vector)
{
    const float tolerance = 0.000001f;
    float length = Magnitude(vector);

    if (length < tolerance)
    {
        return vector;
    }

	float inverseLength = 1.f/length;
	return Vector3(vector.x*inverseLength, vector.y*inverseLength, vector.z*inverseLength);
}

float Dot(const Vector3& vector1, const Vector3& vector2)
{
	return (vector1.x*vector2.x + vector1.y*vector2.y + vector1.z*vector2.z);
}

Vector3 Cross(const Vector3& vector1, const Vector3& vector2)
{
	return Vector3((vector1.y*vector2.z - vector2.y*vector1.z), 
		(vector1.z*vector2.x - vector2.z-vector1.x),
		(vector1.x*vector2.y - vector2.x*vector1.y));
}

Quaternion GetRotationTo(const Vector3& source, const Vector3& dest)
{
    // TODO - see if this could be more efficient
    Vector3 c = Cross(source, dest);
    float d = Dot(source, dest);

    float wValue = std::sqrt(MagnitudeSquare(source) * MagnitudeSquare(dest)) + d;

    Quaternion qnorm(Normalize(Quaternion(c.x, c.y, c.z, wValue)));
	
	return qnorm;
}