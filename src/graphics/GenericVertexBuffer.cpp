/**********************************************************************
*	Filename: GenericVertexBuffer.cpp
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

#include "GenericVertexBuffer.h"


GenericVertexBuffer::GenericVertexBuffer(uint32_t numVertices, uint32_t vertexSize)
: m_data(0), m_numVertices(numVertices), m_vertexSize(vertexSize), m_bufferSize(numVertices*vertexSize)
{
    m_data = static_cast<uint8_t*>(malloc(m_bufferSize));
}

GenericVertexBuffer::~GenericVertexBuffer()
{
    free(m_data);
}

uint32_t GenericVertexBuffer::GetBufferId() const
{
    return 0;
}

uint32_t GenericVertexBuffer::GetBufferSize() const
{
    return m_bufferSize;
}

uint32_t GenericVertexBuffer::GetStride() const
{
    return m_vertexSize;
}

uint32_t GenericVertexBuffer::GetNumVertices() const
{
    return m_numVertices;
}

uint32_t GenericVertexBuffer::GetOffset(VertexParamType::Enum paramType) const
{
    switch(paramType)
    {
    case VertexParamType::Position:
        return 0;
    case VertexParamType::Normal:
        return GetOffset(VertexParamType::Position) + VertexParamSizeType::GetSize(VertexParamSizeType::Float3);
    case VertexParamType::Color:
        return GetOffset(VertexParamType::Normal) + VertexParamSizeType::GetSize(VertexParamSizeType::Float3);
    case VertexParamType::Texture:
        return GetOffset(VertexParamType::Color) + VertexParamSizeType::GetSize(VertexParamSizeType::Float4);
    default:
        return 0;
    }
}

void GenericVertexBuffer::WriteData(void* data, uint32_t numElements, uint32_t offset)
{
    if (offset < m_bufferSize)
    {
        memcpy(m_data+offset, data, numElements*m_vertexSize);
    }
}

void* GenericVertexBuffer::GetData(uint32_t offset) const
{
    if (offset < m_bufferSize)
    {
        return m_data + offset;
    }

    return 0;
}