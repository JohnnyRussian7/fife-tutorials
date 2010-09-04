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
#include "IVertexBuffer.h"
#include "IIndexBuffer.h"

Billboard::Billboard(SceneManager* sceneManager)
: m_sceneManager(sceneManager), m_owner(0), m_width(1), m_height(1),
m_position(Vector3::Zero()), m_color(ColorWhite()), m_verticsGenerated(false)
{
    assert(m_sceneManager);
}

Billboard::Billboard(SceneManager* sceneManager, const Vector3& position)
: m_sceneManager(sceneManager),m_owner(0), m_width(1), m_height(1),
m_position(position), m_color(ColorWhite()), m_verticsGenerated(false)
{
    assert(m_sceneManager);
}

Billboard::Billboard(SceneManager* sceneManager, BillboardGroup* owner, const Vector3& position)
: m_sceneManager(sceneManager), m_owner(owner), m_width(1), m_height(1),
m_position(position), m_color(ColorWhite()), m_verticsGenerated(false)
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
        const float halfWidth = m_width/2.f;
        const float halfHeight = m_height/2.f;

        std::vector<Vertex> vertices;
        vertices.reserve(GetNumberOfVertices());

        // first vertex (0)
        Vector3 position = m_position - Vector3(-halfWidth, halfHeight, 0);
        vertices.push_back(Vertex(m_position, Vector3(0,0,0), m_color, Vector2(m_textureCoords.m_left, m_textureCoords.m_top)));

        // second vertex (1)
        position = m_position - Vector3(halfWidth, halfHeight, 0);
        vertices.push_back(Vertex(m_position, Vector3(0,0,0), m_color, Vector2(m_textureCoords.m_right, m_textureCoords.m_top)));

        // third vertex (2)
        position = m_position - Vector3(-halfWidth, -halfHeight, 0); 
        vertices.push_back(Vertex(m_position, Vector3(0,0,0), m_color, Vector2(m_textureCoords.m_left, m_textureCoords.m_bottom)));

        // fourth vertex (3)
        position = m_position - Vector3(halfWidth, -halfHeight, 0); 
        vertices.push_back(Vertex(m_position, Vector3(0,0,0), m_color, Vector2(m_textureCoords.m_right, m_textureCoords.m_bottom)));

        m_vertexBuffer->WriteData(static_cast<void*>(&vertices[0]), vertices.size());
//         m_vertexBuffer->WriteData(static_cast<void *>(&vertices[0]), 1);
//         m_vertexBuffer->WriteData(static_cast<void*>(&vertices[1]), 1, sizeof(Vertex));
//         m_vertexBuffer->WriteData(static_cast<void*>(&vertices[2]), 1, sizeof(Vertex)*2);
//         m_vertexBuffer->WriteData(static_cast<void*>(&vertices[3]), 1, sizeof(Vertex)*3);
    }

    m_verticsGenerated = true;
}

void Billboard::SetPosition(const Vector3& position)
{
    m_position = position;
}

const Vector3& Billboard::GetPosition() const
{
    return m_position;
}

void Billboard::SetDimensions(uint32_t width, uint32_t height)
{
    SetWidth(width);
    SetHeight(height);
}

void Billboard::SetWidth(uint32_t width)
{
    m_width = width;
}

void Billboard::SetHeight(uint32_t height)
{
    m_height = height;
}

uint32_t Billboard::GetWidth(uint32_t width) const
{
    return m_width;
}

uint32_t Billboard::GetHeight(uint32_t height) const
{
    return m_height;
}

void Billboard::SetColor(const Color& color)
{
    m_color = color;
}

const Color& Billboard::GetColor() const
{
    return m_color;
}

void Billboard::SetTextureCoordinates(const FloatRect& texCoords)
{
    m_textureCoords = texCoords;
}

void Billboard::SetTextureCoordinates(float left, float top, float right, float bottom)
{
    SetTextureCoordinates(FloatRect(left, top, right, bottom));
}

const FloatRect& Billboard::GetTextureCoordinates() const
{
    return m_textureCoords;
}

uint32_t Billboard::GetNumberOfVertices() const
{
    return 4;
}

Renderable* Billboard::GetRenderable()
{
    return this;
}

void Billboard::Update()
{
    if (!m_verticsGenerated)
    {
        GenerateVertices();
    }
}