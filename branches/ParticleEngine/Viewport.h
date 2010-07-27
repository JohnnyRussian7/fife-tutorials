
#ifndef VIEWPORT_H_
#define VIEWPORT_H_

class Viewport
{
public:
	Viewport();
	Viewport(int left, int top, int width, int height);
	
	int GetLeft() const;
	int GetTop() const;
	int GetWidth() const;
	int GetHeight() const;

private:
	int m_left;
	int m_top;
	int m_width;
	int m_height;
};

#endif
