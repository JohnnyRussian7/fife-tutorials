
#include "Image.h"

#include <memory>

Image::Image(ColorFormat::Enum format, unsigned int width, unsigned int height)
: m_width(width), m_height(height), 
  m_bytesPerPixel(ColorFormat::GetBitsPerPixel(format)/8), m_colorFormat(format)
{
	m_stride = m_width * m_bytesPerPixel;

	m_data = new unsigned char[m_width*m_stride];
}

Image::Image(const Image& rhs)
: m_width(rhs.m_width), m_height(rhs.m_height), m_bytesPerPixel(rhs.m_bytesPerPixel),
  m_colorFormat(rhs.m_colorFormat), m_stride(rhs.m_stride)
{
	m_data = new unsigned char[m_width*m_stride];
	memcpy(m_data, rhs.m_data, sizeof(m_data));
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