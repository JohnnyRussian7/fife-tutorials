/**********************************************************************
*	Filename: Material.cpp
*	
*	Copyright (C) 2011, FIFE team
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

#include "Material.h"
#include "../graphics/ITexture.h"

Material::Material()
{

}

Material::~Material()
{

}

void Material::SetTexture(const TexturePtr& texture)
{
	m_texture = texture;
}

const TexturePtr& Material::GetTexture() const
{
    return m_texture;
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