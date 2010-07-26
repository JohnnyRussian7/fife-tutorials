
#ifndef OPENGL_TEXTURE_H_
#define OPENGL_TEXTURE_H_

#include "RendererEnums.h"

class Image;

class OpenglTexture
{
public:
	OpenglTexture(TextureType::Enum type, Image* image);
	~OpenglTexture();

	unsigned int GetTextureId() const;
	void Upload();

private:
	unsigned int m_textureId;
	Image* m_image;
};

#endif
