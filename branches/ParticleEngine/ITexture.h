
#ifndef ITEXTURE_H_
#define ITEXTURE_H_

#include "stdint.h"
#include "TextureEnums.h"

class ITexture
{
public:
	virtual uint32_t GetId() const = 0;
    virtual TextureType::Enum GetType() const = 0;
	virtual void Upload() = 0;
};

#endif