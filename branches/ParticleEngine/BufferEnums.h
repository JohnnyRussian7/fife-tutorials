/**********************************************************************
*	Filename: BufferEnums.h
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
#ifndef BUFFERENUMS_H_
#define BUFFERENUMS_H_

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

struct VertexParamType
{
    enum Enum
    {
        Position,
        Normal,
        Color,
        Texture
    };
};

struct VertexParamSizeType
{
    enum Enum
    {
        Float1,
        Float2,
        Float3,
        Float4,
    };

    static uint32_t GetSize(VertexParamSizeType::Enum type)
    {
        switch (type)
        {
        case Float1:
            return sizeof(float);
        case Float2:
            return sizeof(float) * 2;
        case Float3:
            return sizeof(float) * 3;
        case Float4:
            return sizeof(float) * 4;
        default:
            return 0;
        }
    }
};

struct IndexBufferDataType
{
    enum Enum
    {
        _16bit = 0,
        _32bit
    };

    static uint32_t GetSize(IndexBufferDataType::Enum indexType)
    {
        switch (indexType)
        {
        case IndexBufferDataType::_16bit:
            return sizeof(uint16_t);
        case IndexBufferDataType::_32bit:
            return sizeof(uint32_t);
        }

        return sizeof(uint16_t);
    }
};

#endif
