
#ifndef IMAGE_H_
#define IMAGE_H_

#include "stdint.h"

struct ColorFormat
{
	enum Enum
	{
		R8G8B8,		// RGB 24-bit 
		R8G8B8A8	// RGBA 32-bit
	};

	static uint32_t GetBitsPerPixel(Enum type)
	{
		switch (type)
		{
		case R8G8B8:
			return 24;

		case R8G8B8A8:
			return 32;

		default:
			return 0;
		}
	}
};

class Image
{
public:
	Image(ColorFormat::Enum format, uint32_t width, uint32_t height);
	Image::Image(const Image& rhs);
	~Image();

	uint32_t GetWidth() const;
	uint32_t GetHeight() const;
	uint32_t GetStride() const;
	uint32_t GetBytesPerPixel() const;
	ColorFormat::Enum GetColorFormat() const;

	uint8_t* GetData();

private:
	uint32_t m_width;
	uint32_t m_height;
	uint32_t m_stride;
	uint32_t m_bytesPerPixel;
	ColorFormat::Enum m_colorFormat;

	uint8_t* m_data;
};

#endif
