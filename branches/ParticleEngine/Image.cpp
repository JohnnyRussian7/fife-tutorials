
#include "Image.h"

Image::Image(ColorFormat::Enum format, unsigned int width, unsigned int height)
: m_width(width), m_height(height), 
  m_bytesPerPixel(ColorFormat::GetBitsPerPixel(format)/8), m_colorFormat(format)
{
	m_stride = m_width * m_bytesPerPixel;

	m_data = new unsigned char[m_width*m_stride];
}

Image::~Image()
{
	delete m_data;
	m_data = 0;
}

unsigned int Image::GetWidth() const
{
	return m_width;
}

unsigned int Image::GetHeight() const
{
	return m_height;
}

unsigned int Image::GetStride() const
{
	return m_stride;
}

ColorFormat::Enum Image::GetColorFormat() const
{
	return m_colorFormat;
}

unsigned char* Image::GetData()
{
	return m_data;
}