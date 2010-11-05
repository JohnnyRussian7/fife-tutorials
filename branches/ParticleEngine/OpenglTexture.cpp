
#include <iostream>

#include "Opengltexture.h"
#include "Image.h"
#include "OpenglUtility.h"
#include "MathUtil.h"

#include <windows.h>
#include <gl/gl.h>			// OpenGL headers
#include <gl/glu.h>

OpenglTexture::OpenglTexture(TextureType::Enum type, Image *image)
: m_type(type), m_textureId(0), m_image(image), m_width(0), m_height(0)
{
	if (m_image)
	{
        // TODO - need to check it non-power of 2 is supported
        m_width = m_image->GetWidth();
        if (!IsPowerOf2(m_width))
        {
            m_width = NextPowerOf2(m_width);
        }

        m_height = m_image->GetHeight();
        if (!IsPowerOf2(m_height))
        {
            m_height = NextPowerOf2(m_height);
        }

		glGenTextures(1, reinterpret_cast<GLuint*>(&m_textureId));

        if (m_textureId)
        {
            // push texture to GPU
		    Upload();
        }
	}
}

OpenglTexture::~OpenglTexture()
{
	if (m_textureId)
	{
		glDeleteTextures(1, reinterpret_cast<GLuint*>(&m_textureId));
	}

	delete m_image;
}

uint32_t OpenglTexture::GetId() const
{
	return m_textureId;
}

TextureType::Enum OpenglTexture::GetType() const
{
    return m_type;
}

uint32_t OpenglTexture::GetSourceImageWidth() const
{
    return m_image->GetWidth();
}

uint32_t OpenglTexture::GetSourceImageHeight() const
{
    return m_image->GetHeight();
}

uint32_t OpenglTexture::GetWidth() const
{
    return m_width;
}

uint32_t OpenglTexture::GetHeight() const
{
    return m_height;
}

void OpenglTexture::Upload()
{
	if (m_image)
	{
        GLenum textureType = opengl::utility::ConvertTextureType(m_type);

		// enable texture type and bind to the current texture
		glEnable(textureType);
		glBindTexture(textureType, m_textureId);

		// enable filters
		glTexParameteri(textureType, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(textureType, GL_TEXTURE_MAG_FILTER, GL_LINEAR);      

        bool deleteData = false;
        uint8_t* data = m_image->GetData();

        if (m_width != m_image->GetWidth() || m_height != m_image->GetHeight())
        {
            uint32_t widthDiff = m_width - m_image->GetWidth();
            data = new uint8_t[m_width*m_image->GetStride()];
            memset(&data[0], uint8_t(0), m_width*m_image->GetStride());
            memcpy(&data[0], m_image->GetData(), m_image->GetDataSize());

            deleteData = true;
        }

		if (m_image->GetColorFormat() == ColorFormat::R8G8B8)
		{
			glTexImage2D(textureType, 0, GL_RGB, m_width, m_height,
				0, GL_RGB, GL_UNSIGNED_BYTE, data);
		}
		else if (m_image->GetColorFormat() == ColorFormat::R8G8B8A8)
		{
			glTexImage2D(textureType, 0, GL_RGBA, m_width, m_height,
				0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		}

        if (deleteData)
        {
            delete [] data;
        }
	}
}