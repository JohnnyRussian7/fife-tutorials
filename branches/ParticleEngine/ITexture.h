
#ifndef ITEXTURE_H_
#define ITEXTURE_H_

#include "stdint.h"

class ITexture
{
public:
	virtual uint32_t GetTextureId() const = 0;
	virtual void Upload() = 0;
};

#endif