/**********************************************************************
*	Filename: OpenglIndexBuffer.cpp
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
#include "OpenglIndexBuffer.h"
#include "OpenglUtility.h"

OpenglIndexBuffer::OpenglIndexBuffer(uint32_t numIndices, IndexBufferDataType::Enum indexType, HwBufferUsage::Enum usage)
: m_numIndices(numIndices), m_indexType(indexType), m_indexSize(IndexBufferDataType::GetIndexDataSize(indexType)), m_usage(usage)
{
    m_bufferSize = m_numIndices*m_indexSize;

    // request buffer allocation
    glGenBuffersARB(1, reinterpret_cast<GLuint*>(&m_bufferId));

    if (!m_bufferId)
    {
        // TODO - report error here
    }

    // bind the buffer
    glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, m_bufferId);

    // set initial size and usage
    glBufferDataARB(GL_ELEMENT_ARRAY_BUFFER_ARB, m_bufferSize, 0, opengl::utility::ConvertToOpenglBufferUsage(m_usage));
}

OpenglIndexBuffer::~OpenglIndexBuffer()
{
    glDeleteBuffersARB(1, reinterpret_cast<GLuint*>(&m_bufferId));
}

uint32_t OpenglIndexBuffer::GetBufferId() const
{
    return m_bufferId;
}

uint32_t OpenglIndexBuffer::GetBufferSize() const
{
    return m_bufferSize;
}

void OpenglIndexBuffer::WriteData(void* data, uint32_t numElements, uint32_t offset)
{
    glBindBufferARB(GL_ARRAY_BUFFER_ARB, m_bufferId);

    if (offset == 0 && (numElements*m_indexSize == m_bufferSize))
    {
        glBufferDataARB(GL_ELEMENT_ARRAY_BUFFER_ARB, m_bufferSize, data, opengl::utility::ConvertToOpenglBufferUsage(m_usage));
    }
    else
    {
        glBufferSubDataARB(GL_ELEMENT_ARRAY_BUFFER_ARB, offset, numElements*m_indexSize, data);
    }
}