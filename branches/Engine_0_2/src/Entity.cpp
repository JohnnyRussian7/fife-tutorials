/**********************************************************************
*	Filename: Entity.cpp
*	
*	Copyright (C) 2011, FIFE team
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

#include "Entity.h"
#include "Visual.h"
#include "math/Matrix4.h"
#include "scene/SceneNode.h"

namespace
{
    std::string CreateUniqueEntityName()
    {
        // automated counting for name generation, in case the user doesn't provide a name
        static uint32_t uniqueNumber = 0;
        static std::string baseName = "Entity";

        std::ostringstream oss;
        oss << baseName << "_" << uniqueNumber;

        const std::string name = oss.str();
        ++uniqueNumber;

        return name;
    }
}

Entity::Entity(const char* name)
: m_name("")
{
	if (name)
	{
		m_name = std::string(name);
	}
    else
    {
        m_name = CreateUniqueEntityName();
    }

    m_visual = new Visual(this);
}

Entity::~Entity()
{
    delete m_visual;
    m_visual = 0;
}

const char* Entity::GetName() const
{
	return m_name.c_str();
}

void Entity::SetParent(SceneNode* node)
{
    m_parent = node;
}

SceneNode* Entity::GetParent() const
{
    return m_parent;
}

void Entity::SetVisual(Visual* visual)
{
    delete m_visual;

    m_visual = visual;
    
    if (m_visual)
    {
        m_visual->SetParent(this);
    }
}

Visual* Entity::GetVisual() const
{
    return m_visual;
}

void Entity::Update(uint32_t time)
{
    if (m_visual)
    {
        m_visual->Update(time);
    }
}

Matrix4 Entity::GetTransform()
{
    if (m_parent)
    {
        return m_parent->GetTransform();
    }

    return Matrix4::Identity();
}