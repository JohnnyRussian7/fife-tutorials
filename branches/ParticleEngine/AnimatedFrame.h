/**********************************************************************
*	Filename: AnimatedFrame.h
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
#ifndef ANIMATEDFRAME_H_
#define ANIMATEDFRAME_H_

#include <string>

#include "stdint.h"
#include "Rect.h"
#include "IAnimatedFrame.h"

class IAnimation;

class AnimatedFrame : public IAnimatedFrame
{
public:
    AnimatedFrame(IAnimation* owner, char* name, uint32_t frameNumber);
    
    virtual const char* GetName() const;
    virtual uint32_t GetFrameNumber() const;
    virtual ITexture* GetTexture() const;
    virtual const FloatRect& GetTextureCoordinates() const;
    virtual void SetTextureCoordinates(const FloatRect& texCoords);
    virtual void SetTextureCoordinates(float left, float top, float right, float bottom);

private:
    IAnimation* m_owner;
    std::string m_name;
    uint32_t m_frameNumber;
    ITexture* m_texture;
    FloatRect m_textureCoords;
};

#endif
