
#include "Entity.h"

Entity::Entity(const char* name)
: m_name("")
{
	if (name)
	{
		m_name = std::string(name);
	}
}

Entity::~Entity()
{

}

const char* Entity::GetName() const
{
	return m_name.c_str();
}