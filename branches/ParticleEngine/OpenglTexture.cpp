
#include "Opengltexture.h"
#include "Image.h"

#include <windows.h>
#include <gl/gl.h>			// OpenGL headers
#include <gl/glu.h>

OpenglTexture::OpenglTexture(TextureType::Enum type, Image *image)
: m_image(image)
{
	if (image)
	{
		glGenTextures(1, &m_textureId);

		// push texture to GPU
		Upload();
	}
}

OpenglTexture::~OpenglTexture()
{
	if (m_textureId)
	{
		glDeleteTextures(1, &m_textureId);
	}

	delete m_image;
}

unsigned int OpenglTexture::GetTextureId() const
{
	return m_textureId;
}

void OpenglTexture::Upload()
{
	if (m_image)
	{
		// enable 2d textures and bind to the current texture
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, m_textureId);

		// enable filters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		if (m_image->GetColorFormat() == ColorFormat::R8G8B8)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_image->GetWidth(), m_image->GetHeight(),
				0, GL_RGB, GL_UNSIGNED_BYTE, m_image->GetData());
		}
		else if (m_image->GetColorFormat() == ColorFormat::R8G8B8A8)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_image->GetWidth(), m_image->GetHeight(),
				0, GL_RGBA, GL_UNSIGNED_BYTE, m_image->GetData());
		}
	}
}