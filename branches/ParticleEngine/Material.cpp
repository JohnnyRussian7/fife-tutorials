
#include "Material.h"

Material::Material()
{

}

Material::~Material()
{

}

void Material::SetTexture(ITexture* texture)
{
	m_texture = texture;
}

void Material::SetAmbientColor(const Color& color)
{
	m_ambient = color;
}

void Material::SetDiffuseColor(const Color& color)
{
	m_diffuse = color;
}

void Material::SetSpecularColor(const Color& color)
{
	m_specular = color;
}

void Material::SetShininess(uint8_t shininess)
{
	m_shininess = shininess;
}

void Material::SetEmissiveColor(const Color& color)
{
	m_emissive = color;
}