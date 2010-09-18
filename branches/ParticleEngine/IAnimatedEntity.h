/**********************************************************************
*	Filename: IAnimatedEntity.h
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
#ifndef IANIMATEDENTITY_H_
#define IANIMATEDENTITY_H_

#include "stdint.h"
#include "Image.h"
#include "IEntity.h"

class IAnimatedEntity : public IEntity
{
public:
    virtual ~IAnimatedEntity() { };
    
    virtual uint32_t GetNumFrames() const = 0;
    virtual void SetNumFrames(uint32_t numFrames) = 0;

    virtual uint32_t GetTotalRunTime() const = 0;
    virtual void SetTotalRunTime(uint32_t runTimeInMs) = 0;

    virtual bool IsLooping() const = 0;
    virtual void SetLooping(bool looping) = 0;

    virtual void AddFrame(Image* image, const char* name=0) = 0;
    virtual void RemoveFrame(uint32_t index) = 0;
    virtual void RemoveFrame(const char* name) = 0;

    virtual void Start() = 0;
    virtual void Stop() = 0;
    virtual void Pause() = 0;
    virtual void Reset() = 0;

    virtual void Animate(uint32_t time) = 0;
};

#endif