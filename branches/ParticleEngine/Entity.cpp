
#include <sstream>

#include "Entity.h"
#include "IMaterial.h"

namespace
{
    std::string CreateUniqueEntityName()
    {
        // automated counting for entity name generation, in case the user doesn't provide a name
        static uint32_t uniqueNumber = 0;
        static std::string entityBaseName = "Entity";

        std::ostringstream oss;
        oss << entityBaseName << "_" << uniqueNumber;

        const std::string name = oss.str();
        ++uniqueNumber;

        return name;
    }
}

Entity::Entity(const char* name)
: m_name(""), m_material(0)
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
    // TODO - does this need to be here?
    delete m_material;
    m_material = 0;
}

const char* Entity::GetName() const
{
	return m_name.c_str();
}

void Entity::SetMaterial(IMaterial* material)
{
    m_material = material;
}

IMaterial* Entity::GetMaterial() const
{
    return m_material;
}