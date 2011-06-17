/**********************************************************************
*	Filename: Visual.cpp
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
#include "PrecompiledIncludes.h"

#include "Visual.h"
#include "IEntity.h"
#include "math/Matrix4.h"
#include "scene/Renderable.h"
#include "scene/IAnimation.h"

Visual::Visual(IEntity* entity)
: m_parent(entity), m_renderable(0), m_animation(0)
{
    m_renderable = new Renderable(this);
}

Visual::Visual(Renderable* renderable, IAnimation* animation)
: m_renderable(renderable), m_animation(animation)
{

}

Visual::~Visual()
{
    delete m_animation;
    m_animation = 0;

    delete m_renderable;
    m_renderable = 0;
}

void Visual::SetParent(IEntity* entity)
{
    m_parent = entity;
}

void Visual::SetAnimation(IAnimation* animation)
{
    delete m_animation;

    m_animation = animation;
}

IAnimation* Visual::GetAnimation() const
{
    return m_animation;
}

void Visual::SetRenderable(Renderable* renderable)
{
    delete m_renderable;

    m_renderable = renderable;
}

Renderable* Visual::GetRenderable() const
{
    return m_renderable;
}

void Visual::Update(uint32_t time)
{
    if (m_animation)
    {
        m_animation->Animate(time);
    }
}

Matrix4 Visual::GetTransform()
{
    if (m_parent)
    {
        return m_parent->GetTransform();
    }

    return Matrix4::Identity();
}