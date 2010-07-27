
#include "Viewport.h"

Viewport::Viewport()
: m_left(0), m_top(0), m_width(0), m_height(0)
{

}

Viewport::Viewport(int left, int top, int width, int height)
: m_left(left), m_top(top), m_width(width), m_height(height)
{

}

int Viewport::GetLeft() const
{
	return m_left;
}

int Viewport::GetTop() const
{
	return m_top;
}

int Viewport::GetWidth() const
{
	return m_width;
}

int Viewport::GetHeight() const
{
	return m_height;
}