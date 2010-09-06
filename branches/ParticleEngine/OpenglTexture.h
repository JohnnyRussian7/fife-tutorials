
#ifndef OPENGL_TEXTURE_H_
#define OPENGL_TEXTURE_H_

#include "stdint.h"
#include "ITexture.h"
#include "TextureEnums.h"

class Image;

class OpenglTexture : public ITexture
{
public:
	OpenglTexture(TextureType::Enum type, Image* image);
	~OpenglTexture();

	virtual uint32_t GetId() const;
    virtual TextureType::Enum GetType() const;
	virtual void Upload();

private:
    TextureType::Enum m_type;
	uint32_t m_textureId;
	Image* m_image;
};

#endif
