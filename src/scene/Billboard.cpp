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
#include "PrecompiledIncludes.h"

#include "Billboard.h"
#include "SceneManager.h"
#include "Camera.h"
#include "IAnimation.h"
#include "IMaterial.h"
#include "../math/Vector2.h"
#include "../graphics/VertexIndexBufferEnums.h"
#include "../graphics/IVertexBuffer.h"
#include "../graphics/IIndexBuffer.h"
#include "../graphics/IndexData.h"

// TODO - temporary
#include "../RenderComponent.h"
#include "../utility/CheckedCast.h"

Billboard::Billboard(SceneManager* sceneManager, BillboardGroup* parent, uint32_t width, uint32_t height, const Vector3& position)
: m_sceneManager(sceneManager), m_parent(parent), m_dirty(true), m_width(width), m_height(height), m_position(position)
{
    InitIndices();
}

Billboard::Billboard(SceneManager* sceneManager)
: m_sceneManager(sceneManager), m_parent(0), m_width(1), m_height(1),
m_position(Vector3::Zero()), m_color(Color::White()), m_buffersGenerated(false)
{
    assert(m_sceneManager);
    
    InitIndices();
}

Billboard::Billboard(SceneManager* sceneManager, const Vector3& position)
: m_sceneManager(sceneManager),m_parent(0), m_width(1), m_height(1),
m_position(position), m_color(Color::White()), m_buffersGenerated(false)
{
    assert(m_sceneManager);
    
    InitIndices();
}

Billboard::Billboard(SceneManager* sceneManager, BillboardGroup* owner, const Vector3& position)
: m_sceneManager(sceneManager), m_parent(owner), m_width(1), m_height(1),
m_position(position), m_color(Color::White()), m_buffersGenerated(false)
{
    assert(m_sceneManager);
    
    InitIndices();
}

void Billboard::InitIndices()
{
    m_indices.reserve(GetNumberOfIndices());
    
    // this would be for using triangle strips
    //m_indices.push_back(0);
    //m_indices.push_back(1);
    //m_indices.push_back(2);
    //m_indices.push_back(3);
    //m_indices.push_back(3);
    
    // indices when using triangles
    m_indices.push_back(0);
    m_indices.push_back(1);
    m_indices.push_back(2);
    m_indices.push_back(2);
    m_indices.push_back(1);
    m_indices.push_back(3);
}

void Billboard::SetPosition(const Vector3& position)
{
    if (m_position != position)
    {
        m_position = position;

        MarkDirty();
    }
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
    if (m_width != width)
    {
        m_width = width;

        MarkDirty();
    }
}

void Billboard::SetHeight(uint32_t height)
{
    if (m_height != height)
    {
        m_height = height;

        MarkDirty();
    }
}

uint32_t Billboard::GetWidth() const
{
    return m_width;
}

uint32_t Billboard::GetHeight() const
{
    return m_height;
}

void Billboard::SetColor(const Color& color)
{
    if (m_color != color)
    {
        m_color = color;

        MarkDirty();
    }
}

const Color& Billboard::GetColor() const
{
    return m_color;
}

void Billboard::SetTextureCoordinates(const FloatRect& texCoords)
{
    if (m_textureCoords != texCoords)
    {
        m_textureCoords = texCoords;

        MarkDirty();
    }
}

void Billboard::SetTextureCoordinates(float left, float top, float right, float bottom)
{
    SetTextureCoordinates(FloatRect(left, top, right, bottom));
}

const FloatRect& Billboard::GetTextureCoordinates() const
{
    return m_textureCoords;
}

void Billboard::FillVertexData(VertexData& vertexData)
{
    if (IsDirty())
    {
        Update();
    }  
    
    vertexData.AddVertices(m_vertexData.GetVertices(), m_vertexData.GetNumVertices());
}

void Billboard::FillIndexData(IndexData& indexData, uint32_t billboardNumber)
{
    for (uint32_t i=0; i < m_indices.size(); ++i)
    {
        // takes 4 indices to fully describe a billboard
        indexData.AddIndex(GetNumberOfVertices() * billboardNumber + m_indices[i]);
    } 
}

uint32_t Billboard::GetNumberOfVertices()
{
    return 4;
}

uint32_t Billboard::GetNumberOfIndices()
{
    return 6;
}

Renderable* Billboard::GetRenderable()
{
    return m_renderable;
}

void Billboard::MarkDirty()
{
    m_dirty = true;
}

void Billboard::ResetDirty()
{
    m_dirty = false;
}

bool Billboard::IsDirty() const
{
    return m_dirty;
}

void Billboard::Update()
{
    // clear out current vertex information
    m_vertexData.Clear();

    const float halfWidth = m_width/2.f;
    const float halfHeight = m_height/2.f;

    Matrix4 transposeView = Matrix4::Identity();
    Camera* m_camera = m_sceneManager->GetCamera();
    if (m_camera)
    {
        transposeView = Transpose(m_camera->GetViewMatrix());
    }

    // 4 vertices per billboard
    // split into 2 triangles with 
    // vertex 1 and 2 shared
    //  (2) ______ (3)
    //     |\     |       
    //     |  \   |
    //     |   \  |
    //  (0)|_____\| (1)

    // first vertex (0)
    //Vector3 position = m_position + Vector3(-halfWidth*transposeView.GetX(), halfHeight*transposeView.GetY(), 0);
    Vector3 position = m_position + (-halfWidth*transposeView.GetX() + halfHeight*transposeView.GetY());
    m_vertexData.AddVertex(Vertex(position, Vector3(0,0,0), m_color, Vector2(m_textureCoords.m_left, m_textureCoords.m_top)));

    // second vertex (1)
    //position = m_position + Vector3(halfWidth, halfHeight, 0);
    position = m_position + (halfWidth*transposeView.GetX() + halfHeight*transposeView.GetY());
    m_vertexData.AddVertex(Vertex(position, Vector3(0,0,0), m_color, Vector2(m_textureCoords.m_right, m_textureCoords.m_top)));

    // third vertex (2)
    //position = m_position + Vector3(-halfWidth*transposeView.GetX(), -halfHeight*transposeView.GetY(), 0); 
    position = m_position + (-halfWidth*transposeView.GetX() - halfHeight*transposeView.GetY());
    m_vertexData.AddVertex(Vertex(position, Vector3(0,0,0), m_color, Vector2(m_textureCoords.m_left, m_textureCoords.m_bottom)));

    // fourth vertex (3)
    //position = m_position + Vector3(halfWidth, -halfHeight, 0);
    position = m_position + (halfWidth*transposeView.GetX() - halfHeight*transposeView.GetY());
    m_vertexData.AddVertex(Vertex(position, Vector3(0,0,0), m_color, Vector2(m_textureCoords.m_right, m_textureCoords.m_bottom)));

    ResetDirty();
}

void Billboard::GenerateBuffers()
{
    // 4 vertices per billboard
    // split into 2 triangles with 
    // vertex 1 and 2 shared
    //  (2) ______ (3)
    //     |\     |       
    //     |  \   |
    //     |   \  |
    //  (0)|_____\| (1)
    
    RenderComponent* renderComponent = 0;
    if (m_owner)
    {
        renderComponent = checked_cast<RenderComponent*>(m_owner->GetComponent("Render"));

        if (renderComponent)
        {
            renderComponent->SetVertexBuffer(m_sceneManager->CreateVertexBuffer(GetNumberOfVertices(), sizeof(Vertex), HwBufferUsage::Dynamic));
        }
    }

    m_renderable->SetVertexBuffer(m_sceneManager->CreateVertexBuffer(GetNumberOfVertices(), sizeof(Vertex), HwBufferUsage::Dynamic));

    IVertexBuffer* vertexBuffer = m_renderable->GetVertexBuffer();

    if (vertexBuffer)
    {
        const float halfWidth = m_width/2.f;
        const float halfHeight = m_height/2.f;

        std::vector<Vertex> vertices;
        vertices.reserve(GetNumberOfVertices());

        // first vertex (0)
        Vector3 position = m_position + Vector3(-halfWidth, -halfHeight, 0); 
        vertices.push_back(Vertex(position, Vector3(0,0,0), m_color, Vector2(m_textureCoords.m_left, m_textureCoords.m_bottom)));

        // second vertex (1)
        position = m_position + Vector3(halfWidth, -halfHeight, 0); 
        vertices.push_back(Vertex(position, Vector3(0,0,0), m_color, Vector2(m_textureCoords.m_right, m_textureCoords.m_bottom)));

        // third vertex (2)
        position = m_position + Vector3(-halfWidth, halfHeight, 0);
        vertices.push_back(Vertex(position, Vector3(0,0,0), m_color, Vector2(m_textureCoords.m_left, m_textureCoords.m_top)));

        // fourth vertex (3)
        position = m_position + Vector3(halfWidth, halfHeight, 0);
        vertices.push_back(Vertex(position, Vector3(0,0,0), m_color, Vector2(m_textureCoords.m_right, m_textureCoords.m_top)));        

        vertexBuffer->WriteData(&vertices[0], vertices.size(), 0);

        if (renderComponent)
        {
            renderComponent->GetVertexBuffer()->WriteData(&vertices[0], vertices.size(), 0);
        }
    }

    if (renderComponent)
    {
        renderComponent->SetIndexBuffer(m_sceneManager->CreateIndexBuffer(6, IndexBufferDataType::_16bit, HwBufferUsage::Static));
    }

    m_renderable->SetIndexBuffer(m_sceneManager->CreateIndexBuffer(6, IndexBufferDataType::_16bit, HwBufferUsage::Static));

    IIndexBuffer* indexBuffer = m_renderable->GetIndexBuffer();

    if (indexBuffer)
    {
        indexBuffer->WriteData(&m_indices[0], GetNumberOfIndices(), 0);

        if (renderComponent)
        {
            renderComponent->GetIndexBuffer()->WriteData(&m_indices[0], GetNumberOfIndices(), 0);
        }
    }

    if (renderComponent)
    {
        renderComponent->SetPrimitiveType(PrimitiveType::Triangles);
    }

    // set the primitive type
    m_renderable->SetPrimitiveType(PrimitiveType::Triangles);

    m_buffersGenerated = true;
}

void Billboard::UpdateBuffers()
{
    IVertexBuffer* vertexBuffer = m_renderable->GetVertexBuffer();

    if (vertexBuffer)
    {
        const float halfWidth = m_width/2.f;
        const float halfHeight = m_height/2.f;

        std::vector<Vertex> vertices;
        vertices.reserve(GetNumberOfVertices());

        // first vertex (0)
        Vector3 position = m_position + Vector3(-halfWidth, -halfHeight, 0); 
        vertices.push_back(Vertex(position, Vector3(0,0,0), m_color, Vector2(m_textureCoords.m_left, m_textureCoords.m_bottom)));
        
        // second vertex (1)
        position = m_position + Vector3(halfWidth, -halfHeight, 0); 
        vertices.push_back(Vertex(position, Vector3(0,0,0), m_color, Vector2(m_textureCoords.m_right, m_textureCoords.m_bottom)));
        
        // third vertex (2)
        position = m_position + Vector3(-halfWidth, halfHeight, 0);
        vertices.push_back(Vertex(position, Vector3(0,0,0), m_color, Vector2(m_textureCoords.m_left, m_textureCoords.m_top)));
        
        // fourth vertex (3)
        position = m_position + Vector3(halfWidth, halfHeight, 0);
        vertices.push_back(Vertex(position, Vector3(0,0,0), m_color, Vector2(m_textureCoords.m_right, m_textureCoords.m_top)));        
        
        vertexBuffer->WriteData(&vertices[0], vertices.size(), 0);

        if (m_owner)
        {
            RenderComponent* renderComponent = checked_cast<RenderComponent*>(m_owner->GetComponent("Render"));

            if (renderComponent)
            {
                renderComponent->GetVertexBuffer()->WriteData(&vertices[0], vertices.size(), 0);
            }
        }

    }
}

void Billboard::Update(uint32_t time)
{
    Visual::Update(time);

    bool animationDirty = false;
    if (m_animation && m_animation->IsDirty())
    {
        if (m_owner)
        {
            RenderComponent* renderComponent = checked_cast<RenderComponent*>(m_owner->GetComponent("Render"));

            if (renderComponent)
            {
                if (renderComponent->GetMaterial())
                {
                    renderComponent->GetMaterial()->SetTexture(m_animation->GetTexture());
                }
            }
        }
        m_renderable->GetMaterial()->SetTexture(m_animation->GetTexture());
        SetTextureCoordinates(m_animation->GetTextureCoords());

        animationDirty = true;
    }

    if (!m_buffersGenerated)
    {
        GenerateBuffers();
    }
    else if (animationDirty)
    {
        UpdateBuffers();
    }
}