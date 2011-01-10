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

TextureManager::TextureManager(RenderSystemType::Enum renderSystemType)
: m_type(renderSystemType)
{

}

TexturePtr TextureManager::CreateTexture(TextureType::Enum type, Image* image, const char* name)
{
    // if a texture already exists with the same name then it will return that texture
    // otherwise it creates a new texture of returns it
    switch(m_type)
    {
        case RenderSystemType::Opengl:
        {
            TexturePtr ptr = make_shared(new OpenglTexture(type, image, name));   
            std::pair<TextureContainer::iterator, bool> retVal = m_textures.insert(std::make_pair(ptr->GetName(), ptr));
            return retVal.first->second;
        }
        case RenderSystemType::Sdl:
        {
            // TODO - fill this out when supported
            return TexturePtr();
        }
        default:
        {
            return TexturePtr();
        }
    }
}

bool TextureManager::AddTexture(ITexture* texture)
{
    if (texture)
    {
        TexturePtr sharedTexture(texture);
        std::pair<TextureContainer::iterator, bool> retVal = m_textures.insert(std::make_pair(sharedTexture->GetName(), sharedTexture));

        return retVal.second;
    }

    return false;
}

void TextureManager::RemoveTexture(const char* name)
{
    if (name)
    {
        TextureContainer::iterator iter = m_textures.find(name);
        if (iter != m_textures.end())
        {
            m_textures.erase(iter);
        } 
    }
}

void TextureManager::RemoveAllTextures()
{
    m_textures.clear();
}

void TextureManager::RemoveUnusedTextures()
{
    TextureContainer::iterator iter = m_textures.begin();
    for (; iter != m_textures.end(); ++iter)
    {
        if (iter->second.Unique())
        {
            m_textures.erase(iter);
        }
    }
}