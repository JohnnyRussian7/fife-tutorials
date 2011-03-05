/**********************************************************************
*	Filename: OpenglTexture.h
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
#ifndef OPENGLTEXTURE_H_
#define OPENGLTEXTURE_H_

#include "../../StdIncludes.h"

#include "../Texture.h"
#include "../TextureEnums.h"
#include "../ImageFwd.h"

class IImage;

class OpenglTexture : public Texture
{
public:
	OpenglTexture(TextureType::Enum type, const ImagePtr& image, const char* name=0);
	~OpenglTexture();

    uint32_t GetSourceImageWidth() const;
    uint32_t GetSourceImageHeight() const;
    uint32_t GetWidth() const;
    uint32_t GetHeight() const;

	virtual void Upload();

private:
	ImagePtr m_image;
    uint32_t m_width;
    uint32_t m_height;
};

#endif
