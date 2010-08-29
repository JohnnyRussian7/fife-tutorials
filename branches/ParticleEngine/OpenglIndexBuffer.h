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

#include "HwBuffer.h"

struct IndexDataType
{
    enum Enum
    {
        _16bit = 0,
        _32bit
    };
};

class OpenglIndexBuffer : public HwBuffer
{
public:
    OpenglIndexBuffer(uint32_t numIndices, IndexDataType::Enum indexType, HwBufferUsage::Enum usage);
    ~OpenglIndexBuffer();

    virtual void WriteData(void* data, uint32_t numElements, uint32_t offset = 0);

private:
    uint32_t m_numIndices;
    IndexDataType::Enum m_indexType;
    uint32_t m_indexSize;
};

#endif
