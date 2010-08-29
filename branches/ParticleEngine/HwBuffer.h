/**********************************************************************
*	Filename: HwBuffer.h
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
#ifndef HWBUFFER_H_
#define HWBUFFER_H_

#include "stdint.h"

struct HwBufferAccess
{
	enum Enum
	{
		ReadOnly = 0,
		WriteOnly,
		ReadWrite
	};
};

struct HwBufferUsage
{
	enum Enum
	{
		Static,
		Dynamic,
		Stream
	};
};

class HwBuffer
{
public:
    HwBuffer(uint32_t dataLength, uint32_t dataElementSize, HwBufferUsage::Enum usage);
    virtual ~HwBuffer();

    uint32_t GetBufferId() const;
    uint32_t GetBufferSize() const;

    virtual void WriteData(void* data, uint32_t numElements, uint32_t offset=0);

protected:
    uint32_t m_bufferId;
    uint32_t m_bufferSize;
    HwBufferUsage::Enum m_usage;
};

#endif
