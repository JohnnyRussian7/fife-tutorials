
#ifndef MATH_UTIL_H_
#define MATH_UTIL_H_
 
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

#endif
