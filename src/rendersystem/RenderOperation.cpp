/**********************************************************************
*	Filename: RenderOperation.cpp
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

#include "RenderOperation.h"

RenderOperation::RenderOperation()
: m_transform(Matrix4::Identity()), m_vertexBuffer(0), m_indexBuffer(0), m_material(0)
{

}

RenderOperation::~RenderOperation()
{

}

void RenderOperation::SetTransform(const Matrix4& transform)
{
    m_transform = transform;
}

const Matrix4& RenderOperation::GetTransform() const
{
    return m_transform;
}

void RenderOperation::SetPrimitiveType(PrimitiveType::Enum type)
{
    m_primitiveType = type;
}

PrimitiveType::Enum RenderOperation::GetPrimitiveType() const
{
    return m_primitiveType;
}

void RenderOperation::SetVertexBuffer(IVertexBuffer* vertexBuffer)
{
    m_vertexBuffer = vertexBuffer;
}


IVertexBuffer* RenderOperation::GetVertexBuffer() const
{
    return m_vertexBuffer;
}

void RenderOperation::SetIndexBuffer(IIndexBuffer* indexBuffer)
{
    m_indexBuffer = indexBuffer;
}


IIndexBuffer* RenderOperation::GetIndexBuffer() const
{
    return m_indexBuffer;
}

void RenderOperation::SetMaterial(IMaterial* material)
{
    m_material = material;
}

IMaterial* RenderOperation::GetMaterial() const
{
    return m_material;
}

void RenderOperation::SetBlendingMode(const BlendingMode& blendingMode)
{
    m_blendingMode = blendingMode;
}

const BlendingMode& RenderOperation::GetBlendingMode() const
{
    return m_blendingMode;
}

void RenderOperation::SetCullMode(const CullMode& cullMode)
{
    m_cullMode = cullMode;
}

const CullMode& RenderOperation::GetCullMode() const
{
    return m_cullMode;
}

void RenderOperation::SetPolygonWindingMode(const PolygonWindingMode& windingMode)
{
    m_windingMode = windingMode;
}

const PolygonWindingMode& RenderOperation::GetPolygonWindingMode() const
{
    return m_windingMode;
}

void RenderOperation::SetFillMode(const FillMode& fillMode)
{
    m_fillMode = fillMode;
}

const FillMode& RenderOperation::GetFillMode() const
{
    return m_fillMode;
}

void RenderOperation::SetAlphaTestMode(const AlphaTestMode& alphaTestMode)
{
    m_alphaTestMode = alphaTestMode;
}

const AlphaTestMode& RenderOperation::GetAlphaTestMode() const
{
    return m_alphaTestMode;
}


void RenderOperation::SetDepthBufferWriteMode(const DepthBufferWriteMode& depthBufferWriteMode)
{
    m_depthBufferWriteMode = depthBufferWriteMode;
}

const DepthBufferWriteMode& RenderOperation::GetDepthBufferWriteMode() const
{
    return m_depthBufferWriteMode;
}
