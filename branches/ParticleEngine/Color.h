
#ifndef COLOR_H_
#define COLOR_H_

#include <algorithm>

struct Color
{
	Color(): r(0.f), g(0.f), b(0.f), a(1.f) { };
	Color(float r, float g, float b, float a=1.f): r(r), g(g), b(b), a(a) { };

	float r;
	float g;
	float b;
	float a;
};

inline Color interpolate(const Color& color1, const Color& color2, float scale)
{
	// clamp value in range [0,1] and compute inverse
	float value = (std::min)((std::max)(scale, 0.f), 1.f);
	float inverse = 1.f - value;

	Color retColor;
	retColor.r = color2.r*inverse + color1.r*value;
	retColor.g = color2.g*inverse + color1.g*value;
	retColor.b = color2.b*inverse + color1.b*value;
	retColor.a = color2.a*inverse + color1.a*value;
	return retColor;
}

inline Color ColorBlack()
{
    return Color(0.f, 0.f, 0.f);
}

inline Color ColorWhite()
{
    return Color(1.f, 1.f, 1.f);
}

inline Color ColorRed()
{
    return Color(1.f, 0.f, 0.f);
}

inline Color ColorGreen()
{
    return Color(0.f, 1.f, 0.f);
}

inline Color ColorBlue()
{
    return Color(0.f, 0.f, 1.f);
}

#endif
