/**********************************************************************
*	Filename: IIndexBuffer.h
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
#ifndef IINDEXBUFFER_H_
#define IINDEXBUFFER_H_

#include "stdint.h"
#include "BufferEnums.h"

class IIndexBuffer
{
public:
    virtual ~IIndexBuffer() { }

    virtual uint32_t GetBufferId() const = 0;
    virtual uint32_t GetBufferSize() const = 0;
    virtual IndexBufferDataType::Enum GetType() const = 0;
    virtual uint32_t GetStride() const = 0;
    virtual void* GetData(uint32_t offset=0) const = 0;

    virtual void WriteData(void* data, uint32_t numElements, uint32_t offset=0) = 0;
};

#endif