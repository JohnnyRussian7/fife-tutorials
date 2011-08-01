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
#include "IComponent.h"

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

Entity::Entity(const char* name, const Vector3& position)
: m_name(""), m_parent(0), m_position(position)
{
	if (name)
	{
		m_name = std::string(name);
	}
    else
    {
        m_name = CreateUniqueEntityName();
    }
}

Entity::~Entity()
{
    // remove and delete all components
    for (ComponentContainer::iterator iter = m_components.begin(); iter != m_components.end(); ++iter)
    {
        delete *iter;
    }
    m_components.clear();
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

IComponent* Entity::GetComponent(std::string name)
{
    // search for a component with the given name
    for (ComponentContainer::iterator iter = m_components.begin(); iter != m_components.end(); ++iter)
    {
        if ((*iter)->GetName() == name)
        {
            // component found return it
            return *iter;
        }
    }

    return 0;
}

void Entity::AddComponent(IComponent* component)
{
    // the component must be valid and have some type of name
    if (component && !component->GetName().empty())
    {
        bool replacedComponent = false;

        // search for a component with the same name
        for (ComponentContainer::iterator iter = m_components.begin(); iter != m_components.end(); ++iter)
        {
            if ((*iter)->GetName() == component->GetName())
            {
                // found identical component, remove
                // existing one before adding new one
                delete *iter;
                component->SetParent(this);
                *iter = component;
                replacedComponent = true;
                break;
            }
        }

        // component with same name was not found
        // so we append to end of component list
        if (!replacedComponent)
        {
            component->SetParent(this);
            m_components.push_back(component);
        }
    }
}

void Entity::RemoveComponent(std::string name)
{
    // search for a component with the same name
    for (ComponentContainer::iterator iter = m_components.begin(); iter != m_components.end(); ++iter)
    {
        if ((*iter)->GetName() == name)
        {
            // component found, delete and remove from list
            delete *iter;
            m_components.erase(iter);
            break;
        }
    }
}

const Vector3& Entity::GetPosition() const
{
    return m_position;
}

void Entity::SetPosition(float x, float y, float z)
{
    SetPosition(Vector3(x,y,z));
}

void Entity::SetPosition(const Vector3& position)
{
    m_position = position;
}

void Entity::Update(uint32_t time)
{
    for (ComponentContainer::iterator iter = m_components.begin(); iter != m_components.end(); ++iter)
    {
        (*iter)->Update(time);
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