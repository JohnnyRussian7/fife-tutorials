
#ifndef ITEXTURE_H_
#define ITEXTURE_H_

#include <string>

#include "stdint.h"
#include "TextureEnums.h"
#include "SharedPtr.h"

class ITexture
{
public:
    virtual ~ITexture() { };

    virtual std::string GetName() const = 0;
	virtual uint32_t GetId() const = 0;
    virtual TextureType::Enum GetType() const = 0;
	virtual void Upload() = 0;
};

#endif