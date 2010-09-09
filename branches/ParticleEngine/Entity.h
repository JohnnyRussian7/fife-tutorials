
#ifndef ENTITY_H_
#define ENTITY_H_

#include <string>

#include "IEntity.h"

class Renderable;

class Entity : public IEntity
{
public:
	Entity(const char* name=0);
	~Entity();

	const char* GetName() const;

    virtual Renderable* GetRenderable();
    virtual void Update();

private:
	std::string m_name;
};

#endif