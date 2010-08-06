
#ifndef IMATERIAL_H_
#define IMATERIAL_H_

#include "stdint.h"

struct Color;
class ITexture;

class IMaterial
{
    virtual void SetTexture(ITexture* texture) = 0;
    virtual void SetAmbientColor(const Color& color) = 0;
    virtual void SetDiffuseColor(const Color& color) = 0;
    virtual void SetSpecularColor(const Color& color) = 0;
    virtual void SetShininess(uint8_t shininess) = 0;
    virtual void SetEmissiveColor(const Color& color) = 0;
};

#endif
