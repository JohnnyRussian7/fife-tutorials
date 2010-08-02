
#include "Viewport.h"

Viewport::Viewport()
: m_left(0), m_top(0), m_width(0), m_height(0)
{

}

Viewport::Viewport(int left, int top, int width, int height)
: m_left(left), m_top(top), m_width(width), m_height(height)
{

}

int32_t Viewport::GetLeft() const
{
	return m_left;
}

int32_t Viewport::GetTop() const
{
	return m_top;
}

int32_t Viewport::GetWidth() const
{
	return m_width;
}

int32_t Viewport::GetHeight() const
{
	return m_height;
}