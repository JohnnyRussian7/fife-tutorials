
#include <sstream>

#include "Entity.h"
#include "SceneNode.h"
#include "Visual.h"
#include "Matrix4.h"

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