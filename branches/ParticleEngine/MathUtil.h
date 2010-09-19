
#ifndef MATH_UTIL_H_
#define MATH_UTIL_H_

#include "stdint.h"

struct Vector3;
struct Matrix4;
struct Quaternion;

extern const float Pi;

// radian/degree conversions
float RadToDeg(float rad);
float DegToRad(float deg);

// determines if a number is a power of 2
template <typename T>
bool IsPowerOf2(T n)
{
    return (n & (n-1)) == 0;
}

// finds next highest power of 2 for an unsigned 32-bit number
uint32_t ComputeNextPowerOf2(uint32_t n);

// creates a transform matrix based on scale, position, and orientation
// the applied ordering is (1) scale, (2) orientation, (3) translation
Matrix4 MakeTransform(const Vector3& scale, const Vector3& position, const Quaternion& orientation);

#endif
