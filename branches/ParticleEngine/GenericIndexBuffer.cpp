/**********************************************************************
*	Filename: GenericIndexBuffer.cpp
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

#include "GenericIndexBuffer.h"


GenericIndexBuffer::GenericIndexBuffer(uint32_t numIndices, IndexBufferDataType::Enum indexType)
: m_numIndices(numIndices), m_indexType(indexType), m_indexSize(IndexBufferDataType::GetSize(indexType))
{
    m_bufferSize = m_numIndices * m_indexSize;
}

GenericIndexBuffer::~GenericIndexBuffer()
{

}

uint32_t GenericIndexBuffer::GetBufferId() const
{
    return 0;
}

uint32_t GenericIndexBuffer::GetBufferSize() const
{
    return m_bufferSize;
}

void GenericIndexBuffer::WriteData(void* data, uint32_t numElements, uint32_t offset)
{
    // TODO - implement
}