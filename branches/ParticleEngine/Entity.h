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