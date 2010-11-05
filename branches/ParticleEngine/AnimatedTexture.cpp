/**********************************************************************
*	Filename: AnimatedTexture.cpp
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

#include <string>
#include <sstream>
#include <iostream>
#include <cassert>

#include "AnimatedTexture.h"
#include "IAnimatedFrame.h"
#include "AnimatedFrame.h"
#include "ISpriteSheet.h"

AnimatedTexture::AnimatedTexture()
: m_totalRunTimeInMs(0), m_looping(false), m_currentIndex(0), m_running(true), 
  m_lastUpdateTime(0), m_currentRunTime(0), m_spriteSheet(0), m_dirty(true)
{

}

AnimatedTexture::AnimatedTexture(ISpriteSheet* spriteSheet, bool autoFillFrames)
: m_totalRunTimeInMs(0), m_looping(false), m_currentIndex(0), m_running(true), 
  m_lastUpdateTime(0), m_currentRunTime(0), m_spriteSheet(spriteSheet), m_dirty(true)
{
    if (m_spriteSheet && autoFillFrames)
    {
        for (uint32_t i=0; i < m_spriteSheet->GetNumTiles(); ++i)
        {
            std::ostringstream oss;
            oss << "Frame_" << i;
            AddFrame((char*)oss.str().c_str(), m_spriteSheet->GetTileCoords(i));
        }
    }
}

AnimatedTexture::~AnimatedTexture()
{
    FrameContainer::iterator iter;
    for (iter = m_frames.begin(); iter != m_frames.end(); ++iter)
    {
        delete *iter;
    }
    m_frames.clear();

    if (m_spriteSheet)
    {
        delete m_spriteSheet;
        m_spriteSheet = 0;
    }
}

uint32_t AnimatedTexture::GetNumFrames() const
{
    return m_frames.size();
}

uint32_t AnimatedTexture::GetTotalRunTime() const
{
    return m_totalRunTimeInMs;
}

void AnimatedTexture::SetTotalRunTime(uint32_t runTimeInMs)
{
    m_totalRunTimeInMs = runTimeInMs;
}

bool AnimatedTexture::IsLooping() const
{
    return m_looping;
}

void AnimatedTexture::SetLooping(bool looping)
{
    m_looping = looping;
}

bool AnimatedTexture::IsDirty() const
{
    return m_dirty;
}

void AnimatedTexture::AddFrame(IAnimatedFrame* frame)
{
    m_frames.push_back(frame);
}

void AnimatedTexture::AddFrame(ITexture* texture, char* name)
{
    uint32_t frameNumber = m_frames.size();
    m_frames.push_back(new AnimatedFrame(this, texture, name, frameNumber));
}

void AnimatedTexture::AddFrame(char* name, const FloatRect& texCoords)
{
    assert(m_spriteSheet);

    uint32_t frameNumber = m_frames.size();
    AnimatedFrame* frame = new AnimatedFrame(this, name, frameNumber);
    frame->SetTexture(m_spriteSheet->GetTexture());

    // TODO - move this elsewhere it is opengl specific
    // must invert coordinates for opengl
    FloatRect invertCoords(texCoords.m_right, texCoords.m_top, texCoords.m_left, texCoords.m_bottom);

    frame->SetTextureCoordinates(invertCoords);

    m_frames.push_back(frame);
}

void AnimatedTexture::RemoveFrame(uint32_t index)
{
    if (index < m_frames.size())
    {
        IAnimatedFrame* frame = m_frames[index];
        delete frame;
        frame = 0;

        m_frames.erase(m_frames.begin()+index);
    }
}

void AnimatedTexture::Start()
{
    m_running = true;
}

void AnimatedTexture::Stop()
{
    m_running = false;
    Reset();
}

void AnimatedTexture::Pause()
{
    m_running = false;
}

void AnimatedTexture::Reset()
{
    m_currentIndex = 0;
}

void AnimatedTexture::Animate(uint32_t time)
{
    if (GetNumFrames() <= 1)
    {
        return;
    }

    const uint32_t FrameTimeInMs = GetTotalRunTime()/(GetNumFrames()-1);

    if (m_lastUpdateTime == 0)
    {
        m_dirty = true;
    }
    else
    {
        m_dirty = false;

        if (m_running)
        {
            m_currentRunTime += time - m_lastUpdateTime;

            if (m_currentRunTime >= FrameTimeInMs)
            {
                ++m_currentIndex;
                m_currentRunTime = 0;
                m_dirty = true;
            }

            if (m_currentIndex == GetNumFrames())
            {
                if (IsLooping())
                {
                    m_currentRunTime = 0;
                    m_currentIndex = 0;
                    m_dirty = true;
                }
                else
                {
                    // end of animation and not looping so just show the last frame and pause
                    uint32_t newIndex = GetNumFrames()-1;
                    Pause();

                    if (newIndex != m_currentIndex)
                    {
                        m_currentIndex = newIndex;
                        m_dirty = true;
                    } 
                }
            }
        }
    }

    m_lastUpdateTime = time;
}

ITexture* AnimatedTexture::GetTexture() const
{
    return m_frames[m_currentIndex]->GetTexture();
}

const FloatRect& AnimatedTexture::GetTextureCoords() const
{
    return m_frames[m_currentIndex]->GetTextureCoordinates();
}