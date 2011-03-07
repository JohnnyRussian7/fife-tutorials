/**********************************************************************
*	Filename: Renderable.cpp
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

#include "Renderable.h"
#include "Visual.h"
#include "IVertexBuffer.h"
#include "IIndexBuffer.h"
#include "Material.h"
#include "Matrix4.h"

Renderable::Renderable(Visual* visual)
: m_parent(visual), m_vertexBuffer(0), m_indexBuffer(0), m_material(0), m_primitiveType(PrimitiveType::Triangles)
{

}

Renderable::~Renderable()
{

}

IVertexBuffer* Renderable::GetVertexBuffer() const
{
    return m_vertexBuffer;
}

void Renderable::SetVertexBuffer(IVertexBuffer* vertexBuffer)
{
    m_vertexBuffer = vertexBuffer;
}

IIndexBuffer* Renderable::GetIndexBuffer() const
{
    return m_indexBuffer;
}

void Renderable::SetIndexBuffer(IIndexBuffer* indexBuffer)
{
    m_indexBuffer = indexBuffer;
}

IMaterial* Renderable::GetMaterial() const
{
    return m_material;
}

void Renderable::SetMaterial(IMaterial* material)
{
    m_material = material;
}

void Renderable::SetPrimitiveType(PrimitiveType::Enum type)
{
    m_primitiveType = type;
}

PrimitiveType::Enum Renderable::GetPrimitiveType() const
{
    return m_primitiveType;
}

Matrix4 Renderable::GetTransform()
{
    if (m_parent)
    {
        return m_parent->GetTransform();
    }

    return Matrix4::Identity();
}