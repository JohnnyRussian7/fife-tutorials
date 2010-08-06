
#ifndef MATERIAL_H_
#define MATERIAL_H_

#include "stdint.h"
#include "Color.h"

class ITexture;

class Material
{
public:
	Material();
	~Material();

	virtual void SetTexture(ITexture* texture);
	virtual void SetAmbientColor(const Color& color);
	virtual void SetDiffuseColor(const Color& color);
	virtual void SetSpecularColor(const Color& color);
	virtual void SetShininess(uint8_t shininess);
	virtual void SetEmissiveColor(const Color& color);

private:
	ITexture* m_texture;
	Color m_ambient;
	Color m_diffuse;
	Color m_specular;
	uint8_t m_shininess;
	Color m_emissive;
};

#endif