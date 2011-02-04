/**********************************************************************
*	Filename: OpenglShaderProgram.cpp
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

#include "OpenglShaderProgram.h"
#include "OpenglCapabilities.h"
#include "OpenglShader.h"
#include "../IShader.h"

OpenglShaderProgram::OpenglShaderProgram(IShader* vertexShader, IShader* fragmentShader)
: m_id(0), m_vertexShader(vertexShader), m_fragmentShader(fragmentShader), m_linked(false)
{
    //assert(m_vertexShader && m_fragmentShader);

    Init();
}

OpenglShaderProgram::~OpenglShaderProgram()
{
    Destroy();

}

void OpenglShaderProgram::Init()
{
    if (OpenglCapabilities::Instance()->GetOpenglVersion() >= OpenglVersion::_2_0)
    {
        m_id = glCreateProgram();
    

        if (m_id)
        {
            glAttachShader(m_id, m_vertexShader->GetId());
            glAttachShader(m_id, m_fragmentShader->GetId());

            glLinkProgram(m_id);

            GLint linked;
            glGetShaderiv(m_id, GL_LINK_STATUS, &linked);

            if (linked == GL_TRUE)
            {
                m_linked = true;
            }
            else
            {
                GLint infoLogLength;
                glGetProgramiv(m_id, GL_INFO_LOG_LENGTH, &infoLogLength);

                if (infoLogLength > 0)
                {
                    GLchar *strInfoLog = (GLchar*)malloc(infoLogLength);
                    glGetProgramInfoLog(m_id, infoLogLength, &infoLogLength, strInfoLog);

                    printf("Linker failure: %s\n", strInfoLog);
                    free(strInfoLog);
                }

                //             GLint success;
                //             glValidateProgram(m_id);
                //             glGetProgramiv(m_id, GL_VALIDATE_STATUS, &success);
                //             if (!success)
                //             {
                //                 GLchar infoLog[256];
                //                 glGetProgramInfoLog(m_id, 256, NULL, infoLog);
                //                 fprintf(stderr, "Error in program validation!\n");
                //                 fprintf(stderr, "Info log: %s\n", infoLog);
                //             }

                m_linked = false;
            }
        }
    }
    else
    {
        m_id = glCreateProgramObjectARB();

        if  (m_id)
        {
            glAttachObjectARB(m_id, m_vertexShader->GetId());
            glAttachObjectARB(m_id, m_vertexShader->GetId());

            glLinkProgramARB(m_id);

            GLint linked;
            glGetObjectParameterivARB(m_id, GL_OBJECT_LINK_STATUS_ARB, &linked);

            if (linked == GL_TRUE)
            {
                m_linked = true;
            }
            else
            {
                GLint infoLogLength;
                glGetObjectParameterivARB(m_id, GL_OBJECT_INFO_LOG_LENGTH_ARB, &infoLogLength);

                if (infoLogLength > 0)
                {
                    GLchar *strInfoLog = (GLchar*)malloc(infoLogLength);
                    glGetInfoLogARB(m_id, infoLogLength, &infoLogLength, strInfoLog);

                    printf("Linker failure: %s\n", strInfoLog);
                    free(strInfoLog);
                }

                m_linked = false;
            }
        }
    }
}

void OpenglShaderProgram::Destroy()
{
    if (OpenglCapabilities::Instance()->GetOpenglVersion() >= OpenglVersion::_2_0)
    {
        glDetachShader(m_id, m_vertexShader->GetId());
        glDetachShader(m_id, m_fragmentShader->GetId());
        glDeleteProgram(m_id);
    }
    else
    {
        glDetachObjectARB(m_id, m_vertexShader->GetId());
        glDetachObjectARB(m_id, m_fragmentShader->GetId());
        glDeleteObjectARB(m_id);
    }
}

IShader* OpenglShaderProgram::GetVertexShader() const
{
    return m_vertexShader;
}

void OpenglShaderProgram::SetVertexShader(IShader* shader)
{
    m_vertexShader = shader;
}

IShader* OpenglShaderProgram::GetFragmentShader() const
{
    return m_fragmentShader;
}

void OpenglShaderProgram::SetFragmentShader(IShader* shader)
{
    m_fragmentShader = shader;
}

void OpenglShaderProgram::Enable()
{
    if (1/*IsLinked()*/)
    {
        if (OpenglCapabilities::Instance()->GetOpenglVersion() >= OpenglVersion::_2_0)
        {
            glUseProgram(m_id);
        }
        else
        {
            glUseProgramObjectARB(m_id);
        }
    }
}

void OpenglShaderProgram::Disable()
{
    if (OpenglCapabilities::Instance()->GetOpenglVersion() >= OpenglVersion::_2_0)
    {
        glUseProgram(0);
    }
    else
    {
        glUseProgramObjectARB(0);
    }
}

bool OpenglShaderProgram::IsLinked() const
{
    return m_linked;
}

