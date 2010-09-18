
#include <sstream>

#include "Entity.h"
#include "IMaterial.h"

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
}

Entity::~Entity()
{

}

const char* Entity::GetName() const
{
	return m_name.c_str();
}

Renderable* Entity::GetRenderable()
{
    return 0;
}

void Entity::Update()
{

}