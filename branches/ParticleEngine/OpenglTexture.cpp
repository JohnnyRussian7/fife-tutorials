
#include "Opengltexture.h"
#include "Image.h"
#include "OpenglUtility.h"

#include <windows.h>
#include <gl/gl.h>			// OpenGL headers
#include <gl/glu.h>

OpenglTexture::OpenglTexture(TextureType::Enum type, Image *image)
: m_type(type), m_textureId(0), m_image(image)
{
	if (image)
	{
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

void OpenglTexture::Upload()
{
	if (m_image)
	{
        GLenum textureType = opengl::utility::ConvertTextureType(m_type);

		// enable 2d textures and bind to the current texture
		glEnable(textureType);
		glBindTexture(textureType, m_textureId);

		// enable filters
		glTexParameteri(textureType, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(textureType, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		if (m_image->GetColorFormat() == ColorFormat::R8G8B8)
		{
			glTexImage2D(textureType, 0, GL_RGB, m_image->GetWidth(), m_image->GetHeight(),
				0, GL_RGB, GL_UNSIGNED_BYTE, m_image->GetData());
		}
		else if (m_image->GetColorFormat() == ColorFormat::R8G8B8A8)
		{
			glTexImage2D(textureType, 0, GL_RGBA, m_image->GetWidth(), m_image->GetHeight(),
				0, GL_RGBA, GL_UNSIGNED_BYTE, m_image->GetData());
		}
	}
}