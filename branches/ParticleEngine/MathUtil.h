
#ifndef MATH_UTIL_H_
#define MATH_UTIL_H_

const double pi = 3.1415926535;
const double radtodeg = 180.0/pi;
const double degtorad = pi/180.0;

static double RadToDeg(float rad)
{
	return rad * radtodeg;
}

static double DegToRad(float deg)
{
	return deg * degtorad;
}

#endif
