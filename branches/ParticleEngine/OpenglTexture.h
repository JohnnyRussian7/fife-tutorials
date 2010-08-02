
#ifndef OPENGL_TEXTURE_H_
#define OPENGL_TEXTURE_H_

#include "stdint.h"
#include "ITexture.h"
#include "RendererEnums.h"

class Image;

class OpenglTexture : public ITexture
{
public:
	OpenglTexture(TextureType::Enum type, Image* image);
	~OpenglTexture();

	uint32_t GetTextureId() const;
	void Upload();

private:
	uint32_t m_textureId;
	Image* m_image;
};

#endif
