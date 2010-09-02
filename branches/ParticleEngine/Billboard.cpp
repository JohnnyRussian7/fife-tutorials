/**********************************************************************
*	Filename: Billboard.cpp
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

#include <cassert>

#include "Billboard.h"
#include "BufferEnums.h"
#include "SceneManager.h"

Billboard::Billboard(SceneManager* sceneManager)
: m_sceneManager(sceneManager), m_owner(0), m_position(Vector3::Zero())
{
    assert(m_sceneManager);
}

Billboard::Billboard(SceneManager* sceneManager, const Vector3& position)
: m_sceneManager(sceneManager),m_owner(0), m_position(position)
{
    assert(m_sceneManager);
}

Billboard::Billboard(SceneManager* sceneManager, BillboardGroup* owner, const Vector3& position)
: m_sceneManager(sceneManager), m_owner(owner), m_position(position)
{
    assert(m_sceneManager);
}

void Billboard::GenerateVertices()
{
    // 4 vertices per billboard
    // split into 2 triangles with 
    // vertex 1 and 2 shared
    //  (0) ______ (1)
    //     |     /|       
    //     |    / |
    //     |  /   |
    //  (2)|/_____| (3)
    
    m_vertexBuffer = m_sceneManager->CreateVertexBuffer(GetNumberOfVertices(), sizeof(Vertex), HwBufferUsage::Dynamic);

    if (m_vertexBuffer)
    {
        Vertex v0;

    }

}

void Billboard::SetPosition(const Vector3& position)
{
    m_position = position;
}

const Vector3& Billboard::GetPosition() const
{
    return m_position;
}

uint32_t Billboard::GetNumberOfVertices() const
{
    return 4;
}