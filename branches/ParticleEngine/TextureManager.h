/**********************************************************************
*	Filename: TextureManager.h
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
#ifndef TEXTUREMANAGER_H_
#define TEXTUREMANAGER_H_

#include "StdIncludes.h"

#include "TextureFwd.h"
#include "TextureEnums.h"
#include "RenderSystemTypes.h"

class Image;

class TextureManager
{
public:
    TextureManager(RenderSystemType::Enum renderSystemType);
    TexturePtr CreateTexture(TextureType::Enum type, Image* image, const char* name=0);
    bool AddTexture(ITexture* texture);
    void RemoveTexture(const char* name);
    void RemoveAllTextures();
    void RemoveUnusedTextures();

private:
    RenderSystemType::Enum m_type;
    typedef std::map<std::string, TexturePtr> TextureContainer;
    TextureContainer m_textures;
};


#endif
