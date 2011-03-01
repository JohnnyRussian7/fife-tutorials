/**********************************************************************
*	Filename: Texture.h
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
#ifndef TEXTURE_H_
#define TEXTURE_H_

#include "StdIncludes.h"

#include "ITexture.h"
#include "TextureEnums.h"

class Texture : public ITexture
{
public:
    Texture(TextureType::Enum type=TextureType::_2d, const char* name=0);

    std::string GetName() const;
    virtual uint32_t GetId() const;
    virtual TextureType::Enum GetType() const;

protected:
    std::string m_name;
    uint32_t  m_id;
    TextureType::Enum m_type;
};

#endif