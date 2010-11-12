/**********************************************************************
*	Filename: Material.h
*	
*	Copyright (C) 2010, FIFE team
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
#ifndef MATERIAL_H_
#define MATERIAL_H_

#include "stdint.h"
#include "IMaterial.h"
#include "Color.h"
#include "TextureFwd.h"

class Material : public IMaterial
{
public:
	Material();
	~Material();

	virtual void SetTexture(const TexturePtr& texture);
    virtual const TexturePtr& GetTexture() const;
	virtual void SetAmbientColor(const Color& color);
	virtual void SetDiffuseColor(const Color& color);
	virtual void SetSpecularColor(const Color& color);
	virtual void SetShininess(uint8_t shininess);
	virtual void SetEmissiveColor(const Color& color);

private:
	TexturePtr m_texture;
	Color m_ambient;
	Color m_diffuse;
	Color m_specular;
	uint8_t m_shininess;
	Color m_emissive;
};

#endif