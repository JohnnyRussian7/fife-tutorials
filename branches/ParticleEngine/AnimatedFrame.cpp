/**********************************************************************
*	Filename: AnimatedFrame.cpp
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

#include "AnimatedFrame.h"
#include "ITexture.h"
#include "IAnimation.h"

AnimatedFrame::AnimatedFrame(IAnimation* owner, char* name, uint32_t frameNumber) 
: m_owner(owner), m_name(""), m_frameNumber(frameNumber), m_textureCoords(FloatRect(0.0, 1.0, 1.0, 0.0)), m_texture(0)
{
    if (name)
    {
        m_name = std::string(name);
    }
}

AnimatedFrame::AnimatedFrame(IAnimation* owner, ITexture* texture, char* name, uint32_t frameNumber)
: m_owner(owner), m_name(""), m_frameNumber(frameNumber), m_textureCoords(FloatRect(0.0, 1.0, 1.0, 0.0)),
  m_texture(texture)
{
    if (name)
    {
        m_name = std::string(name);
    }
}

const char* AnimatedFrame::GetName() const
{
    return m_name.c_str();
}

uint32_t AnimatedFrame::GetFrameNumber() const
{
    return m_frameNumber;
}

void AnimatedFrame::SetTexture(ITexture* texture)
{
    if (m_texture)
    {
        delete m_texture;
        m_texture = 0;
    }

    m_texture = texture;
}

ITexture* AnimatedFrame::GetTexture() const
{
    return m_texture;
}

const FloatRect& AnimatedFrame::GetTextureCoordinates() const
{
    return m_textureCoords;
}

void AnimatedFrame::SetTextureCoordinates(const FloatRect& texCoords)
{
    m_textureCoords = texCoords;
}

void AnimatedFrame::SetTextureCoordinates(float left, float top, float right, float bottom)
{
    SetTextureCoordinates(FloatRect(left, top, right, bottom));
}