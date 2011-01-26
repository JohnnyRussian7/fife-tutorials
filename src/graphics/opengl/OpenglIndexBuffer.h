/**********************************************************************
*	Filename: OpenglIndexBuffer.h
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
#ifndef OPENGLINDEXBUFFER_H_
#define OPENGLINDEXBUFFER_H_

#include "../../StdIncludes.h"

#include "../VertexIndexBufferEnums.h"
#include "../IIndexBuffer.h"

class OpenglIndexBuffer : public IIndexBuffer
{
public:
    OpenglIndexBuffer(uint32_t numIndices, IndexBufferDataType::Enum indexType, HwBufferUsage::Enum usage);
    ~OpenglIndexBuffer();

    virtual uint32_t GetBufferId() const;
    virtual uint32_t GetBufferSize() const;
    virtual IndexBufferDataType::Enum GetType() const;
    virtual uint32_t GetStride() const;
    virtual void* GetData(uint32_t offset=0) const;

    virtual void WriteData(void* data, uint32_t numElements, uint32_t offset = 0);

private:
    uint32_t m_numIndices;
    IndexBufferDataType::Enum m_indexType;
    uint32_t m_indexSize;
    uint32_t m_bufferSize;
    HwBufferUsage::Enum m_usage;
    uint32_t m_bufferId;
};

#endif
