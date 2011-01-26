/**********************************************************************
*	Filename: GenericIndexBuffer.h
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
#ifndef GENERICINDEXBUFFER_H_
#define GENERICINDEXBUFFER_H_

#include "StdIncludes.h"

#include "BufferEnums.h"
#include "IIndexBuffer.h"

class GenericIndexBuffer : public IIndexBuffer
{
public:
    GenericIndexBuffer(uint32_t numIndices, IndexBufferDataType::Enum indexType);
    ~GenericIndexBuffer();

    virtual uint32_t GetBufferId() const;
    virtual uint32_t GetBufferSize() const;
    virtual IndexBufferDataType::Enum GetType() const;
    virtual uint32_t GetStride() const;
    virtual void* GetData(uint32_t offset=0) const;

    virtual void WriteData(void* data, uint32_t numElements, uint32_t offset=0);
private:
    uint8_t* m_data;
    uint32_t m_numIndices;
    IndexBufferDataType::Enum m_indexType;
    uint32_t m_indexSize;
    uint32_t m_bufferSize;
};

#endif