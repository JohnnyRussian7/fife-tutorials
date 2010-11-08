/**********************************************************************
*	Filename: TextureManager.cpp
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

#include "TextureManager.h"
#include "ITexture.h"
#include "OpenglTexture.h"
#include "Image.h"

TextureManager::TextureManager(RenderSystemType::Enum type)
: m_type(type)
{

}

ITexture* TextureManager::CreateTexture(TextureType::Enum type, Image* image, const char* name)
{
    // if a texture already exists with the same name then it will return that texture
    // otherwise it creates a new texture of returns it
    switch(m_type)
    {
        case RenderSystemType::Opengl:
        {
            SharedPtr<ITexture> ptr = make_shared(new OpenglTexture(type, image, name));   
            std::pair<TextureContainer::iterator, bool> retVal = m_textures.insert(std::make_pair(ptr->GetName(), ptr));
            return retVal.first->second.get();
        }
        case RenderSystemType::Sdl:
        {
            // TODO - fill this out when supported
            return 0;
        }
        default:
        {
            return 0;
        }
    }
}

bool TextureManager::AddTexture(ITexture* texture)
{
    if (texture)
    {
        SharedPtr<ITexture> sharedTexture(texture);
        std::pair<TextureContainer::iterator, bool> retVal = m_textures.insert(std::make_pair(sharedTexture->GetName(), sharedTexture));

        return retVal.second;
    }

    return false;
}
