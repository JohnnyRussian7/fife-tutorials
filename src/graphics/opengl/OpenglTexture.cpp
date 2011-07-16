/**********************************************************************
*	Filename: OpenglTexture.cpp
*	
*	Copyright (C) 2010, FIFE team
*	http://www.fifengine.net
*
*	This file is part of FIFE.
*
*	FIFE is free software: you can redistribute it and/or modify it
*	under the terms of the GNU Lesser General Public License as
*	published by the Free Software Foundation, either version 3 of
*	the License, or any later version.
*
*	FIFE is distributed in the hope that it will be useful,
*	but WITHOUT ANY WARRANTY; without even the implied warranty of
*	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* 	GNU Lesser General Public License for more details.
*
*	You should have received a copy of the GNU Lesser General Public
*	License along with FIFE. If not, see http://www.gnu.org/licenses/.
***********************************************************************/
#include "PrecompiledIncludes.h"

#include "OpenglUtility.h"
#include "OpenglTexture.h"
#include "../../math/MathUtil.h"
#include "../IImage.h"

OpenglTexture::OpenglTexture(TextureType::Enum type, const ImagePtr& image, const char* name)
: Texture(type, name), m_image(image), m_width(0), m_height(0)
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

		glGenTextures(1, reinterpret_cast<GLuint*>(&m_id));

        if (m_id)
        {
            // push texture to GPU
		    Upload();
        }
	}
}

OpenglTexture::~OpenglTexture()
{
	if (m_id)
	{
		glDeleteTextures(1, reinterpret_cast<GLuint*>(&m_id));
	}
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
		glBindTexture(textureType, m_id);

		// enable filters
		glTexParameteri(textureType, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(textureType, GL_TEXTURE_MAG_FILTER, GL_LINEAR);      

        bool deleteData = false;
        uint8_t* data = m_image->GetData();

        if (m_width != m_image->GetWidth() || m_height != m_image->GetHeight())
        {
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

        // disable texture
        glDisable(textureType);
	}
}