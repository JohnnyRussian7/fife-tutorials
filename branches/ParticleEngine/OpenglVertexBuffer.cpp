/**********************************************************************
*	Filename: OpenglVertexBuffer.cpp
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

#include "glee/GLee.h"
#include "OpenglVertexBuffer.h"
#include "OpenglUtility.h"

OpenglVertexBuffer::OpenglVertexBuffer(uint32_t numVertices, uint32_t vertexSize, HwBufferUsage::Enum usage)
: m_numVertices(numVertices), m_vertexSize(vertexSize), m_bufferSize(numVertices*vertexSize), m_usage(usage)
{
    // request buffer allocation
    glGenBuffersARB(1, reinterpret_cast<GLuint*>(&m_bufferId));

    if (!m_bufferId)
    {
        // TODO - report error here
    }

    // bind the buffer
    glBindBufferARB(GL_ARRAY_BUFFER_ARB, m_bufferId);

    // set the initial size and usage
    glBufferDataARB(GL_ARRAY_BUFFER_ARB, m_bufferSize, 0, opengl::utility::ConvertToOpenglBufferUsage(m_usage));
}

OpenglVertexBuffer::~OpenglVertexBuffer()
{
    if (m_bufferId)
    {
        glDeleteBuffersARB(1, reinterpret_cast<GLuint*>(&m_bufferId));
    }
}

uint32_t OpenglVertexBuffer::GetBufferId() const
{
    return m_bufferId;
}

uint32_t OpenglVertexBuffer::GetBufferSize() const
{
    return m_bufferSize;
}

uint32_t OpenglVertexBuffer::GetStride() const
{
    return m_vertexSize;
}

uint32_t OpenglVertexBuffer::GetNumVertices() const
{
    return m_numVertices;
}

uint32_t OpenglVertexBuffer::GetOffset(VertexParamType::Enum paramType) const
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

void OpenglVertexBuffer::WriteData(const std::vector<Vertex>& vertices, uint32_t offset)
{
    //float position[3];
    //float normal[3];
    //float color[4];
    //float texture[2];
    float values[12] = {0};
    std::vector<Vertex>::const_iterator iter;
    for (iter = vertices.begin(); iter != vertices.end(); ++iter)
    {
        values[0] = iter->m_position.x;
        values[1] = iter->m_position.y;
        values[2] = iter->m_position.z;
        values[3] = iter->m_normal.x;
        values[4] = iter->m_normal.y;
        values[5] = iter->m_normal.z;
        values[6] = iter->m_color.r;
        values[7] = iter->m_color.g;
        values[8] = iter->m_color.b;
        values[9] = iter->m_color.a;
        values[10] = iter->m_texture.x;
        values[11] = iter->m_texture.y;

        WriteData(&values, 12, offset);
    }
}

void OpenglVertexBuffer::WriteData(const Vertex& vertex, uint32_t offset)
{

}

void OpenglVertexBuffer::WriteData(void* data, uint32_t numElements, uint32_t offset)
{
    glBindBufferARB(GL_ARRAY_BUFFER_ARB, m_bufferId);

    if (offset == 0 && (numElements*m_vertexSize == m_bufferSize))
    {
        glBufferDataARB(GL_ARRAY_BUFFER_ARB, m_bufferSize, data, opengl::utility::ConvertToOpenglBufferUsage(m_usage));
    }
    else
    {
        glBufferSubDataARB(GL_ARRAY_BUFFER_ARB, offset, numElements*m_vertexSize, data);
    }
}

