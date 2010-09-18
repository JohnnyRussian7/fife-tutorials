/**********************************************************************
*	Filename: IMaterial.h
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
#ifndef IMATERIAL_H_
#define IMATERIAL_H_

#include "stdint.h"

struct Color;
class ITexture;

class IMaterial
{
public:
    virtual void SetTexture(ITexture* texture) = 0;
    virtual ITexture* GetTexture() const = 0;
    virtual void SetAmbientColor(const Color& color) = 0;
    virtual void SetDiffuseColor(const Color& color) = 0;
    virtual void SetSpecularColor(const Color& color) = 0;
    virtual void SetShininess(uint8_t shininess) = 0;
    virtual void SetEmissiveColor(const Color& color) = 0;
};

#endif