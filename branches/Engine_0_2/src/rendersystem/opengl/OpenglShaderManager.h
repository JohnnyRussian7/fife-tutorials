/**********************************************************************
*	Filename: OpenglShaderManager.h
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
#ifndef OPENGLSHADERMANAGER_H_
#define OPENGLSHADERMANAGER_H_

#include "../IShaderManager.h"

class IShader;
class IShaderProgram;
class OpenglShader;

class OpenglShaderManager : public IShaderManager
{
public:
    OpenglShaderManager();
    ~OpenglShaderManager();

    virtual IShader* CreateShader(ShaderType::Enum type, const std::string& fileName, bool compile=true);
    //virtual OpenglShader* CreateShader(ShaderType::Enum type, const std::string& shaderName, const std::string& shaderCode, bool compile=true);
    //virtual OpenglShader* CreateShader(ShaderType::Enum type, const std::string& shaderName, const char* shaderCode, bool compile=true);

    virtual IShaderProgram* CreateShaderProgram(const std::string& vertexShaderFile, const std::string fragmentShaderFile);

private:
    typedef std::map<std::string, OpenglShader*> ShaderContainer;
    ShaderContainer m_shaders;
};

#endif
