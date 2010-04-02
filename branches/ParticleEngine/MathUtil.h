
#ifndef MATH_UTIL_H_
#define MATH_UTIL_H_

const double pi = 3.1415926535;

static double rad_2_deg_constant()
{
	static double rad2deg = 180.0/pi;
	return rad2deg;
}

static double deg_2_rad_constant()
{
	static double deg2rad = pi/180.0;
	return deg2rad;
}

static double rad_2_deg(float rad)
{
	return rad * rad_2_deg_constant();
}

static double deg_2_rad(float deg)
{
	return deg * deg_2_rad_constant();
}

#endif
