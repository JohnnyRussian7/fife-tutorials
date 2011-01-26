/**********************************************************************
*	Filename: Visual.h
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
#ifndef VISUAL_H_
#define VISUAL_H_

#include "StdIncludes.h"

class IEntity;
class Renderable;
class IAnimation;
struct Matrix4;

class Visual
{
public:
    Visual(IEntity* entity=0);
    Visual(Renderable* renderable, IAnimation* animation);
    virtual ~Visual();

    virtual void SetParent(IEntity* entity);

    virtual void SetAnimation(IAnimation* animation);
    virtual IAnimation* GetAnimation() const;

    virtual void SetRenderable(Renderable* renderable);
    virtual Renderable* GetRenderable();

    virtual void Update(uint32_t time);

    Matrix4 GetTransform();

protected:
    IEntity* m_parent;
    Renderable* m_renderable;
    IAnimation* m_animation;

};

#endif
