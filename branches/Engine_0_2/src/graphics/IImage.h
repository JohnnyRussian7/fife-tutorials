/**********************************************************************
*	Filename: IImage.h
*	
*	Copyright (C) 2011, FIFE team
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
#ifndef IIMAGE_H_
#define IIMAGE_H_

#include "../StdIncludes.h"

#include "ImageEnums.h"

class IImage
{
public:
    virtual ~IImage() { };

    virtual const char* GetName() const = 0;
    virtual uint32_t GetWidth() const = 0;
    virtual uint32_t GetHeight() const = 0;
    virtual uint32_t GetStride() const = 0;
    virtual ColorFormat::Enum GetColorFormat() const = 0;

    virtual uint8_t* GetData() = 0;
    virtual uint32_t GetDataSize() const = 0;
};

#endif
