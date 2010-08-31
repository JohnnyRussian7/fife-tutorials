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

