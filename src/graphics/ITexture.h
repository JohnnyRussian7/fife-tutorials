/**********************************************************************
*	Filename: ITexture.h
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
#ifndef ITEXTURE_H_
#define ITEXTURE_H_

#include "../StdIncludes.h"

#include "TextureEnums.h"

class ITexture
{
public:
    virtual ~ITexture() { };

    virtual std::string GetName() const = 0;
	virtual uint32_t GetId() const = 0;
    virtual TextureType::Enum GetType() const = 0;
	virtual void Upload() = 0;
};

#endif