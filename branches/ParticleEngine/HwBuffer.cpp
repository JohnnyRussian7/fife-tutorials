/**********************************************************************
*	Filename: HwBuffer.cpp
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

#include "HwBuffer.h"

HwBuffer::HwBuffer(uint32_t dataLength, uint32_t dataElementSize, HwBufferUsage::Enum usage)
: m_bufferId(0), m_bufferSize(dataLength*dataElementSize), m_usage(usage)
{

}

HwBuffer::~HwBuffer()
{

}

uint32_t HwBuffer::GetBufferId() const
{
    return m_bufferId;
}

uint32_t HwBuffer::GetBufferSize() const
{
    return m_bufferSize;
}