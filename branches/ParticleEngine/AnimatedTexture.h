/**********************************************************************
*	Filename: AnimatedTexture.h
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
#ifndef ANIMATEDTEXTURE_H_
#define ANIMATEDTEXTURE_H_

#include "StdIncludes.h"

#include "IAnimation.h"
#include "Rect.h"
#include "TextureFwd.h"

class IAnimatedFrame;
class ISpriteSheet;

class AnimatedTexture : public IAnimation
{
public:
    AnimatedTexture(const char* name);
    AnimatedTexture(const char* name, ISpriteSheet* spriteSheet, const TexturePtr& texture, bool autoFillFrames=true);

    ~AnimatedTexture();

    virtual std::string GetName() const;

    virtual IAnimatedFrame* GetFrame(uint32_t index) const;
    virtual uint32_t GetNumFrames() const;

    virtual uint32_t GetTotalRunTime() const;
    virtual void SetTotalRunTime(uint32_t runTimeInMs);

    virtual bool IsLooping() const;
    virtual void SetLooping(bool looping);

    virtual bool IsDirty() const;

    virtual void AddFrame(IAnimatedFrame* frame);
    virtual void AddFrame(const TexturePtr& texture);
    virtual void AddFrame(const TexturePtr& texture, const FloatRect& texCoords);
    virtual void RemoveFrame(uint32_t index);

    virtual void Start();
    virtual void Stop();
    virtual void Pause();
    virtual void Reset();

    virtual void Animate(uint32_t time);

    virtual const TexturePtr& GetTexture() const;
    virtual const FloatRect& GetTextureCoords() const;

private:
    std::string m_name;
    TexturePtr m_texture;
    uint32_t m_totalRunTimeInMs;
    bool m_looping;
    uint32_t m_currentIndex;
    bool m_running;
    uint32_t m_lastUpdateTime;
    uint32_t m_currentRunTime;
    ISpriteSheet* m_spriteSheet;
    bool m_dirty;

    typedef std::vector<IAnimatedFrame*> FrameContainer;
    FrameContainer m_frames;
};

#endif