/**********************************************************************
*	Filename: OpenglShader.cpp
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
#include "PrecompiledIncludes.h"

#include "OpenglShader.h"
#include "../../graphics/opengl/OpenglUtility.h"

OpenglShader::OpenglShader(ShaderType::Enum type, const std::string& name, const std::string& source)
: m_parent(0), m_type(type), m_name(name), m_id(0), m_compiled(false)
{
    m_id = glCreateShader(opengl::utility::ConvertShaderType(type));

    if (m_id)
    {
        const char* data = source.c_str();
        glShaderSource(m_id, 1, &data, 0);
    }
}

OpenglShader::~OpenglShader()
{
    if (m_id)
    {
        glDeleteShader(m_id);
    }
}

ShaderType::Enum OpenglShader::GetType() const
{
    return m_type;
}

const std::string& OpenglShader::GetName() const
{
    return m_name;
}

const uint32_t OpenglShader::GetId() const
{
    return m_id;
}

bool OpenglShader::Compile()
{
    glCompileShader(m_id);

    GLint compiled;
    glGetShaderiv(m_id, GL_COMPILE_STATUS, &compiled);

    if (compiled == GL_TRUE)
    {
        m_compiled = true;
    }
    else
    {
        m_compiled = false;
    }

    return m_compiled;
}

bool OpenglShader::IsCompiled() const
{
    return m_compiled;
}

bool OpenglShader::IsAttached() const
{
    return (m_parent != 0);
}

