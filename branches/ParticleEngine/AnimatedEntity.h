/**********************************************************************
*	Filename: AnimatedEntity.h
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
#ifndef ANIMATEDENTITY_H_
#define ANIMATEDENTITY_H_

#include <vector>

#include "stdint.h"
#include "Entity.h"
#include "IAnimation.h"

class ITexture;
class IAnimatedFrame;

class AnimatedEntity : public IAnimation, public Entity
{
public:
    AnimatedEntity();
    ~AnimatedEntity();

    virtual uint32_t GetNumFrames() const;
    virtual void SetNumFrames(uint32_t numFrames);

    virtual uint32_t GetTotalRunTime() const;
    virtual void SetTotalRunTime(uint32_t runTimeInMs);

    virtual bool IsLooping() const;
    virtual void SetLooping(bool looping);

    virtual void AddFrame(ITexture* texture, char* name);
    virtual void RemoveFrame(uint32_t index);

    virtual void Start();
    virtual void Stop();
    virtual void Pause();
    virtual void Reset();

    virtual void Animate(uint32_t time);

private:
    uint32_t m_totalRunTimeInMs;
    bool m_looping;
    uint32_t m_currentIndex;
    bool m_running;
    uint32_t m_lastUpdateTime;
    
    typedef std::vector<IAnimatedFrame*> FrameContainer;
    FrameContainer m_frames;
};

#endif
