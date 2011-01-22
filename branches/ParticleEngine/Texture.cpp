/**********************************************************************
*	Filename: Texture.cpp
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
#include "PrecompiledIncludes.h"

#include "Texture.h"

namespace {
    std::string CreateUniqueTextureName()
    {
        // automated counting for name generation, in case the user doesn't provide a name
        static uint32_t uniqueNumber = 0;
        static std::string baseName = "Texture";

        std::ostringstream oss;
        oss << baseName << "_" << uniqueNumber;

        const std::string name = oss.str();
        ++uniqueNumber;

        return name;
    }

}

Texture::Texture(TextureType::Enum type, const char* name)
: m_name(""), m_id(0), m_type(type)
{
    if (!name)
    {
        m_name = CreateUniqueTextureName();
    }
    else
    {
        m_name = std::string(name);
    }
}

std::string Texture::GetName() const
{
    return m_name;
}

uint32_t Texture::GetId() const
{
    return m_id;
}

TextureType::Enum Texture::GetType() const
{
    return m_type;
}