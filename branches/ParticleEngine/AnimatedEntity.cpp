/**********************************************************************
*	Filename: AnimatedEntity.cpp
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

#include "AnimatedEntity.h"
#include "AnimatedFrame.h"


AnimatedEntity::AnimatedEntity()
: m_numFrames(0), m_totalRunTimeInMs(0), m_looping(false), m_currentIndex(0), m_running(true)
{

}

AnimatedEntity::AnimatedEntity(const char* filepath)
{

}

AnimatedEntity::AnimatedEntity(const Image* image)
{

}

AnimatedEntity::~AnimatedEntity()
{
    FrameContainer::iterator iter;
    for (iter = m_frames.begin(); iter != m_frames.end(); ++iter)
    {
        delete *iter;
    }
    m_frames.clear();
}

uint32_t AnimatedEntity::GetNumFrames() const
{
    return m_numFrames;
}

void AnimatedEntity::SetNumFrames(uint32_t numFrames)
{
    m_numFrames = numFrames;
}

uint32_t AnimatedEntity::GetTotalRunTime() const
{
    return m_totalRunTimeInMs;
}

void AnimatedEntity::SetTotalRunTime(uint32_t runTimeInMs)
{
    m_totalRunTimeInMs = runTimeInMs;
}

bool AnimatedEntity::IsLooping() const
{
    return m_looping;
}

void AnimatedEntity::SetLooping(bool looping)
{
    m_looping = looping;
}

void AnimatedEntity::AddFrame(Image* image, const char* name)
{
    uint32_t m_frameNumber = m_frames.size();

    m_frames.push_back(new AnimatedFrame(this, m_frameNumber, name));
}

void AnimatedEntity::RemoveFrame(uint32_t index)
{
    if (index < m_frames.size())
    {
        IAnimatedFrame* frame = m_frames[index];
        delete frame;

        m_frames.erase(m_frames.begin()+index);
    }
}

void AnimatedEntity::RemoveFrame(const char* name)
{
    FrameContainer::iterator iter;
    for (iter = m_frames.begin(); iter != m_frames.end(); ++iter)
    {
        if (strcmp((*iter)->GetName(), name) == 0)
        {
            delete *iter;
            m_frames.erase(iter);
            break;
        }
    }
}

void AnimatedEntity::Start()
{
    m_running = true;
}

void AnimatedEntity::Stop()
{
    m_running = false;
    Reset();
}

void AnimatedEntity::Pause()
{
    m_running = false;
}

void AnimatedEntity::Reset()
{
    m_currentIndex = 0;
}