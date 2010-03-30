
#ifndef VECTOR_H_
#define	VECTOR_H_

struct Vector3
{
	Vector3(float x=0, float y=0, float z=0): x(x), y(y), z(z) { }
	Vector3(const Vector3& rhs): x(rhs.x), y(rhs.y), z(rhs.z) { }
	inline Vector3& operator=(const Vector3& rhs);
	inline Vector3& operator+=(const Vector3& rhs);
	inline Vector3& operator-=(const Vector3& rhs);
	inline Vector3& operator*=(float value);
	inline Vector3& operator/=(float value);

	float x;
	float y;
	float z;
};

Vector3& Vector3::operator=(const Vector3& rhs)
{
	if (this != &rhs)
	{
		x = rhs.x;
		y = rhs.y;
		z = rhs.z;
	}
	
	return *this;
}

Vector3& Vector3::operator+=(const Vector3& rhs)
{
	x += rhs.x;
	y += rhs.y;
	z += rhs.z;

	return *this;
}

Vector3& Vector3::operator-=(const Vector3& rhs)
{
	x -= rhs.x;
	y -= rhs.y;
	z -= rhs.z;

	return *this;
}

Vector3& Vector3::operator*=(float value)
{
	x *= value;
	y *= value;
	z *= value;
	
	return *this;
}

Vector3& Vector3::operator/=(float value)
{
	float inverseValue = 1/value;
	x *= inverseValue;
	y *= inverseValue;
	z *= inverseValue;

	return *this;
}

// free functions for binary vector operators
Vector3 operator+(const Vector3& vector1, const Vector3& vector2);
Vector3 operator-(const Vector3& vector1, const Vector3& vector2);
Vector3 operator*(const Vector3& vector, float value);
Vector3 operator/(const Vector3& vector, float value);

// free functions for vector math
float magnitude(const Vector3& vector);
float magnitudeSquare(const Vector3& vector);
Vector3 normalize(const Vector3& vector);
//inline void normalize(Vector3& vector);
float dot(const Vector3& vector1, const Vector3& vector2);
Vector3 cross(const Vector3& vector1, const Vector3& vector2);


#endif
