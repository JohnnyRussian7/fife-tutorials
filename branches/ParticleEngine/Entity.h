
#ifndef ENTITY_H_
#define ENTITY_H_

#include <string>

class Entity
{
public:
	Entity(const char* name);
	~Entity();

	const char* GetName() const;

private:
	std::string m_name;
};

#endif