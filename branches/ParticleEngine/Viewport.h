
#ifndef VIEWPORT_H_
#define VIEWPORT_H_

#include "stdint.h"

class Viewport
{
public:
	Viewport();
	Viewport(int left, int top, int width, int height);
	
	int32_t GetLeft() const;
	int32_t GetTop() const;
	int32_t GetWidth() const;
	int32_t GetHeight() const;

private:
	int32_t m_left;
	int32_t m_top;
	int32_t m_width;
	int32_t m_height;
};

#endif
