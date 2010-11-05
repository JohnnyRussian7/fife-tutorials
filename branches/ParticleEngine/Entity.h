
#ifndef ENTITY_H_
#define ENTITY_H_

#include <string>

#include "stdint.h"
#include "IEntity.h"

class SceneNode;
class Visual;
struct Matrix4;

class Entity : public IEntity
{
public:
	Entity(const char* name=0);
	~Entity();

	const char* GetName() const;

    virtual void SetParent(SceneNode* node);
    virtual SceneNode* GetParent() const;

    virtual void SetVisual(Visual* visual);
    virtual Visual* GetVisual() const;

    virtual void Update(uint32_t time);

    virtual Matrix4 GetTransform();
protected:
	std::string m_name;
    SceneNode* m_parent;
    Visual* m_visual;
};

#endif