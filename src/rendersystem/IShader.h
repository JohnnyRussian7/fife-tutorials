/**********************************************************************
*	Filename: IShader.h
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
#ifndef ISHADER_H_
#define ISHADER_H_

#include "../StdIncludes.h"

#include "ShaderEnums.h"

class IShader
{
public:
    virtual ~IShader() { }

    virtual ShaderType::Enum GetType() const = 0;
    virtual const std::string& GetName() const = 0;
    virtual const uint32_t GetId() const = 0;

    virtual bool Compile() = 0;
    virtual bool IsCompiled() const = 0;

    virtual bool IsAttached() const = 0;
};

#endif
