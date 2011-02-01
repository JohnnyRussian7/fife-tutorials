/**********************************************************************
*	Filename: OpenglShader.h
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
#ifndef OPENGLSHADER_H_
#define OPENGLSHADER_H_

#include "../IShader.h"
#include "../ShaderEnums.h"

class OpenglShaderProgram;

class OpenglShader : public IShader
{
public:
    OpenglShader(ShaderType::Enum type, const std::string& name, const std::string& source);
    ~OpenglShader();

    virtual ShaderType::Enum GetType() const;
    virtual const std::string& GetName() const;
    virtual const uint32_t GetId() const;

    virtual bool Compile();
    virtual bool IsCompiled() const;

    virtual bool IsAttached() const;

private:
    OpenglShaderProgram* m_parent;
    ShaderType::Enum m_type;
    std::string m_name;
    uint32_t m_id;
    bool m_compiled;
};

#endif
