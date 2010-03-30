
#include <cmath>

#include "Vector.h"

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

float magnitude(const Vector3& vector)
{
	return std::sqrt(vector.x*vector.x + vector.y*vector.y + vector.z*vector.z);
}

float magnitudeSquare(const Vector3& vector)
{
	return (vector.x*vector.x + vector.y*vector.y + vector.z*vector.z);
}

Vector3 normalize(const Vector3& vector)
{
    const float tolerance = 0.000001f;
    float length = magnitudeSquare(vector);

    if ((length + tolerance >= 0.f) && (length - tolerance <= 0.f))
    {
        return vector;
    }

	float inverseMag = 1/magnitude(vector);
	return Vector3(vector.x*inverseMag, vector.y*inverseMag, vector.z*inverseMag);
}

/*
void normalize(Vector3& vector)
{
	float inverseMag = 1/magnitude(vector);
	vector *= inverseMag;
}
*/

float dot(const Vector3& vector1, const Vector3& vector2)
{
	return (vector1.x*vector2.x + vector1.y*vector2.y + vector1.z*vector2.z);
}

Vector3 cross(const Vector3& vector1, const Vector3& vector2)
{
	return Vector3((vector1.y*vector2.z - vector2.y*vector1.z), 
		(vector1.z*vector2.x - vector2.z-vector1.x),
		(vector1.x*vector2.y - vector2.x*vector1.y));
}