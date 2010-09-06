/**********************************************************************
*	Filename: OpenglVertexBuffer.h
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
#ifndef OPENGLVERTEXBUFFER_H_
#define OPENGLVERTEXBUFFER_H_

#include <vector>

#include "stdint.h"
#include "IVertexBuffer.h"
#include "BufferEnums.h"
#include "Vertex.h"

class OpenglVertexBuffer : public IVertexBuffer
{
public:
    OpenglVertexBuffer(uint32_t numVertices, uint32_t vertexSize, HwBufferUsage::Enum usage);
    ~OpenglVertexBuffer();

    virtual uint32_t GetBufferId() const;
    virtual uint32_t GetBufferSize() const;
    virtual uint32_t GetStride() const;
    virtual uint32_t GetNumVertices() const;
    virtual uint32_t GetOffset(VertexParamType::Enum paramType) const;

    virtual void WriteData(const std::vector<Vertex>& vertices, uint32_t offset=0);
    virtual void WriteData(const Vertex& vertex, uint32_t offset=0);
    virtual void WriteData(void* data, uint32_t numElements, uint32_t offset=0); 

    // virtual void* GetData() const;

private:
    uint32_t m_numVertices;
    uint32_t m_vertexSize;
    uint32_t m_bufferSize;
    HwBufferUsage::Enum m_usage;
    uint32_t m_bufferId;
};

#endif
