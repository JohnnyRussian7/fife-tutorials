
#ifndef IMAGE_H_
#define IMAGE_H_

struct ColorFormat
{
	enum Enum
	{
		R8G8B8,		// RGB 24-bit 
		R8G8B8A8	// RGBA 32-bit
	};

	static unsigned int GetBitsPerPixel(Enum type)
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
	Image(ColorFormat::Enum format, unsigned int width, unsigned int height);
	~Image();

	unsigned int GetWidth() const;
	unsigned int GetHeight() const;
	unsigned int GetStride() const;
	unsigned int GetBytesPerPixel() const;
	ColorFormat::Enum GetColorFormat() const;

	unsigned char* GetData();

private:
	unsigned int m_width;
	unsigned int m_height;
	unsigned int m_stride;
	unsigned int m_bytesPerPixel;
	ColorFormat::Enum m_colorFormat;

	unsigned char* m_data;
};

#endif
