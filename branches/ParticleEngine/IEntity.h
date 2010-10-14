/**********************************************************************
*	Filename: IEntity.h
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
#ifndef IENTITY_H_
#define IENTITY_H_

#include "stdint.h"

class Renderable;
class IAnimation;

class IEntity
{
public:
    virtual ~IEntity() { };

    virtual const char* GetName() const = 0;

    virtual Renderable* GetRenderable() = 0;

    virtual void SetAnimation(IAnimation* animation) = 0;
    virtual IAnimation* GetAnimation() const = 0;

    virtual void Update(uint32_t time) = 0;
};

#endif