/**********************************************************************
*	Filename: IEntity.h
*	
*	Copyright (C) 2010, FIFE team
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
#ifndef IENTITY_H_
#define IENTITY_H_

#include "StdIncludes.h"

class SceneNode;
class Visual;
struct Matrix4;

class IEntity
{
public:
    virtual ~IEntity() { };

    virtual const char* GetName() const = 0;

    virtual void SetParent(SceneNode* node) = 0;
    virtual SceneNode* GetParent() const = 0;

    virtual void SetVisual(Visual* visual) = 0;
    virtual Visual* GetVisual() const = 0;

    virtual void Update(uint32_t time) = 0;

    virtual Matrix4 GetTransform() = 0;
};

#endif