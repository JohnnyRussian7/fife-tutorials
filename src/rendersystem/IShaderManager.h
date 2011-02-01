/**********************************************************************
*	Filename: IShaderManager.h
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
#ifndef ISHADERMANAGER_H_
#define ISHADERMANAGER_H_

#include "ShaderEnums.h"

class IShader;
class IShaderProgram;

class IShaderManager
{
public:
    virtual ~IShaderManager() { };

    virtual IShader* CreateShader(ShaderType::Enum type, const std::string& fileName, bool compile=true) = 0;
    //virtual IShader* CreateShader(ShaderType::Enum type, const std::string& shaderCode, bool compile=true) = 0;
    //virtual IShader* CreateShader(ShaderType::Enum type, const char* shaderCode, bool compile=true) = 0;

    virtual IShaderProgram* CreateShaderProgram(const std::string& vertexShaderFile, const std::string fragmentShaderFile) = 0;
};

#endif
