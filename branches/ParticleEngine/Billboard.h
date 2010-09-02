/**********************************************************************
*	Filename: Billboard.h
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
#ifndef BILLBOARD_H_
#define BILLBOARD_H_

#include <vector>

#include "stdint.h"
#include "Vector3.h"
#include "Renderable.h"
#include "Vertex.h"

class SceneManager;
class BillboardGroup;

class Billboard : public Renderable
{
public:
    Billboard(SceneManager* sceneManager);
    Billboard(SceneManager* sceneManager, const Vector3& position);
    Billboard(SceneManager* sceneManager, BillboardGroup* owner, const Vector3& position = Vector3::Zero());

    void SetPosition(const Vector3& position);
    const Vector3& GetPosition() const;

    uint32_t GetNumberOfVertices() const;

private:
    void GenerateVertices();
    void GenerateIndices();

private:
    SceneManager* m_sceneManager;
    BillboardGroup* m_owner;
    Vector3 m_position;
    std::vector<Vertex> m_vertices;
};

#endif
