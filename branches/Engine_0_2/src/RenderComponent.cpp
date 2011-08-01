/**********************************************************************
*	Filename: RenderComponent.cpp
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
#include "PrecompiledIncludes.h"

#include "RenderComponent.h"
#include "IEntity.h"
#include "scene/IMaterial.h"
#include "graphics/IVertexBuffer.h"
#include "graphics/IIndexBuffer.h"

RenderComponent::RenderComponent()
: m_parent(0), m_vertexBuffer(0), m_indexBuffer(0), m_material(0), m_primitiveType(PrimitiveType::Triangles)
{

}

RenderComponent::~RenderComponent()
{

}

std::string RenderComponent::GetName()
{
    return "Render";
}

void RenderComponent::SetParent(IEntity* entity)
{
    m_parent = entity;
}

void RenderComponent::Update(uint32_t time)
{
    // TODO - implement
}

IVertexBuffer* RenderComponent::GetVertexBuffer() const
{
    return m_vertexBuffer;
}

void RenderComponent::SetVertexBuffer(IVertexBuffer* vertexBuffer)
{
    m_vertexBuffer = vertexBuffer;
}

IIndexBuffer* RenderComponent::GetIndexBuffer() const
{
    return m_indexBuffer;
}

void RenderComponent::SetIndexBuffer(IIndexBuffer* indexBuffer)
{
    m_indexBuffer = indexBuffer;
}

IMaterial* RenderComponent::GetMaterial() const
{
    return m_material;
}

void RenderComponent::SetMaterial(IMaterial* material)
{
    m_material = material;
}

void RenderComponent::SetPrimitiveType(PrimitiveType::Enum type)
{
    m_primitiveType = type;
}

PrimitiveType::Enum RenderComponent::GetPrimitiveType() const
{
    return m_primitiveType;
}

Matrix4 RenderComponent::GetTransform()
{
    if (m_parent)
    {
        return m_parent->GetTransform();
    }

    return Matrix4::Identity();
}
