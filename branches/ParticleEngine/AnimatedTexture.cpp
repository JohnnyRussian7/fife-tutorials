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

#include "AnimatedTexture.h"
#include "IAnimatedFrame.h"
#include "AnimatedFrame.h"
#include "ISpriteSheet.h"

AnimatedTexture::AnimatedTexture()
: m_totalRunTimeInMs(0), m_looping(false), m_currentIndex(0), m_running(true), m_lastUpdateTime(0)
{

}

AnimatedTexture::AnimatedTexture(ISpriteSheet* spriteSheet)
: m_totalRunTimeInMs(0), m_looping(false), m_currentIndex(0), m_running(true), m_lastUpdateTime(0)
{
    if (spriteSheet)
    {
        std::string name = "Frame_";
        for (uint32_t i=0; i < spriteSheet->GetNumTiles(); ++i)
        {
            std::ostringstream oss;
            oss << name << i;
            AddFrame((char*)oss.str().c_str(), spriteSheet->GetTileCoords(i));
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
    uint32_t frameNumber = m_frames.size();
    AnimatedFrame* frame = new AnimatedFrame(this, name, frameNumber);
    frame->SetTextureCoordinates(texCoords);

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
    if (m_running)
    {
        uint32_t deltaTime = m_lastUpdateTime - time;

        if (deltaTime > GetTotalRunTime())
        {
            deltaTime -= GetTotalRunTime();
        }

        // compute the animation frame
        m_currentIndex = deltaTime / GetTotalRunTime() * GetNumFrames();

        m_lastUpdateTime = time;
    }
}