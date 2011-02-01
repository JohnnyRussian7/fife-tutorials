/**********************************************************************
*	Filename: OpenglShaderManager.cpp
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

#include "OpenglShaderManager.h"
#include "OpenglShaderProgram.h"
#include "OpenglShader.h"

namespace
{
    std::string CreateUniqueShaderName(ShaderType::Enum type)
    {
        // automated counting for name generation, in case the user doesn't provide a name
        static uint32_t uniqueNumber = 0;
        static std::string baseName = ShaderType::ToString(type) + std::string("Shader");

        std::ostringstream oss;
        oss << baseName << "_" << uniqueNumber;

        const std::string name = oss.str();
        ++uniqueNumber;

        return name;
    }
}

OpenglShaderManager::OpenglShaderManager()
{

}

OpenglShaderManager::~OpenglShaderManager()
{
    ShaderContainer::iterator iter;
    for (iter = m_shaders.begin(); iter != m_shaders.end(); ++iter)
    {
        delete iter->second;
    }
    m_shaders.clear();
}

IShader* OpenglShaderManager::CreateShader(ShaderType::Enum type, const std::string& fileName, bool compile)
{
    std::ifstream shaderFile(fileName.c_str());

    if (shaderFile)
    {
        // create name from the shader filename
        std::string::size_type pos = fileName.find_last_of('\\');
        if (pos == std::string::npos)
        {
            // no \ found so look for /
            pos = fileName.find_last_of('/');
        }

        // increment up 1 to avoid grabbing the slash character
        pos += 1;

        std::string shaderName;
        if (pos < fileName.length())
        {
//             std::string::size_type dotPos = fileName.find_last_of('.');
//             if (dotPos != std::string::npos)
//             {
//                 uint32_t count = (fileName.length() - pos) - (fileName.length() - dotPos);
//                 shaderName = fileName.substr(pos, count);
//             }
//             else
//             {
                shaderName = fileName.substr(pos, std::string::npos);
//            }
        }
        else
        {
            shaderName = CreateUniqueShaderName(type);
        }

        if (m_shaders.find(shaderName) != m_shaders.end())
        {
            // TODO - report shader already exists
            return 0;
        }

        // make sure to not skip whitespace
        shaderFile >> std::noskipws;

        // read file contents into 
        std::string shaderCode((std::istreambuf_iterator<std::string::value_type>(shaderFile)),
                                (std::istreambuf_iterator<std::string::value_type>()));
//         std::copy(std::istream_iterator<std::string::value_type>(shaderFile), 
//                     std::istream_iterator<std::string::value_type>(), 
//                     std::back_inserter(shaderCode));

        OpenglShader *shader = new OpenglShader(type, shaderName, shaderCode);
        if (shader)
        {
            if (compile)
            {
                bool success = shader->Compile();

                if (!success)
                {
                    // TODO - report error here
                    return 0;
                }         
            }

            m_shaders.insert(std::make_pair(shader->GetName(), shader)); 

            return shader;
        }
    }

    return 0;
}

IShaderProgram* OpenglShaderManager::CreateShaderProgram(const std::string& vertexShaderFile, const std::string fragmentShaderFile)
{
    IShader* vertexShader = CreateShader(ShaderType::Vertex, vertexShaderFile, true);
    IShader* fragmentShader = CreateShader(ShaderType::Fragment, fragmentShaderFile, true);

    if (!vertexShader)
    {
        // TODO - report error
        return 0;
    }

    if (!fragmentShader)
    {
        // TODO - report error
        return 0;
    }

    return new OpenglShaderProgram(vertexShader, fragmentShader);
}
