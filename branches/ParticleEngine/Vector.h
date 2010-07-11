
#ifndef VECTOR_H_
#define	VECTOR_H_

struct Quaternion;

struct Vector3
{
	Vector3(float x=0, float y=0, float z=0): x(x), y(y), z(z) { }
	Vector3(const Vector3& rhs): x(rhs.x), y(rhs.y), z(rhs.z) { }
	inline Vector3 operator-() const;
	inline Vector3& operator=(const Vector3& rhs);
	inline Vector3& operator+=(const Vector3& rhs);
	inline Vector3& operator-=(const Vector3& rhs);
	inline Vector3& operator*=(float value);
	inline Vector3& operator/=(float value);
	inline bool operator==(const Vector3& rhs) const;

	static Vector3 Zero()
	{
		static Vector3 zero(0.f, 0.f, 0.f);
		return zero;
	}
	static Vector3 UnitX() 
	{ 
		static Vector3 unitX(1.f, 0.f, 0.f);
		return unitX;
	}
	static Vector3 UnitY() 
	{ 
		static Vector3 unitY(0.f, 1.f, 0.f);
		return unitY; 
	}
	static Vector3 UnitZ() 
	{ 
		static Vector3 unitZ(0.f, 0.f, 1.f);
		return unitZ; 
	}

	float x;
	float y;
	float z;
};

Vector3 Vector3::operator-() const
{
	return Vector3(-x, -y, -z);	
}

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

bool Vector3::operator==(const Vector3& rhs) const
{
	return (x == rhs.x && y == rhs.y && z == rhs.z);
}

// free functions for binary vector operators
Vector3 operator+(const Vector3& vector1, const Vector3& vector2);
Vector3 operator-(const Vector3& vector1, const Vector3& vector2);
Vector3 operator*(const Vector3& vector, float value);
Vector3 operator/(const Vector3& vector, float value);

// free functions for vector math
float Magnitude(const Vector3& vector);
float MagnitudeSquare(const Vector3& vector);
Vector3 Normalize(const Vector3& vector);
float Dot(const Vector3& vector1, const Vector3& vector2);
Vector3 cross(const Vector3& vector1, const Vector3& vector2);
Quaternion GetRotationTo(const Vector3& source, const Vector3& dest);


#endif
