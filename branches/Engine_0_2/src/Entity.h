/**********************************************************************
*	Filename: Entity.h
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
#ifndef ENTITY_H_
#define ENTITY_H_

#include "StdIncludes.h"

#include "IEntity.h"
#include "math/Vector3.h"

#include "Visual.h"

class SceneNode;
class IComponent;
class Visual;
struct Matrix4;
class TransformComponent;

class Entity : public IEntity
{
public:
    Entity(const char* name=0, const Vector3& position=Vector3::Zero());
	~Entity();

	virtual const char* GetName() const;

    virtual void SetParent(SceneNode* node);
    virtual SceneNode* GetParent() const;

    virtual IComponent* GetComponent(std::string name);
    virtual void AddComponent(IComponent* component);
    virtual void RemoveComponent(std::string name);

    const Vector3& GetPosition() const;
    void SetPosition(float x, float y, float z);
    void SetPosition(const Vector3& position);
    
    const Quaternion& GetOrientation() const;
    void SetOrientation(const Quaternion& rotation);
    void SetOrientation(const Vector3& axis, float angle);

    virtual void Update(uint32_t time);

    virtual Matrix4 GetTransform();

    // TODO - these will be removed once visual is no longer used
    void SetVisual(Visual* visual) { m_visual = visual; m_visual->SetParent(this); };

protected:
	std::string m_name;
    SceneNode* m_parent;
    
    typedef std::vector<IComponent*> ComponentContainer;
    ComponentContainer m_components;

    // convenience variable for accessing the transform
    // associated with this entity
    TransformComponent* m_transformComponent;

    // TODO - remove once visual is no longer used
    Visual* m_visual;
};

#endif