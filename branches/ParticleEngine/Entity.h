
#ifndef ENTITY_H_
#define ENTITY_H_

#include <string>

#include "stdint.h"
#include "IEntity.h"

class Renderable;
class IAnimation;

class Entity : public IEntity
{
public:
	Entity(const char* name=0);
	~Entity();

	const char* GetName() const;

    virtual Renderable* GetRenderable();

    virtual void SetAnimation(IAnimation* animation);
    virtual IAnimation* GetAnimation() const;

    virtual void Update(uint32_t time);

protected:
	std::string m_name;
    IAnimation* m_animation;
};

#endif