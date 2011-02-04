/**********************************************************************
*	Filename: OpenglCapabilities.cpp
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

#include "OpenglCapabilities.h"

namespace
{
    OpenglVersion::Enum openglVersion;
    void QueryOpenglVersion()
    {
        // any newer versions of glee opengl checks need
        // be added at the top of the if/else if chain
        // for this to work properly

        if (GLEE_VERSION_3_0) 
        {
            openglVersion = OpenglVersion::_3_0;
        }
        else if (GLEE_VERSION_2_1)
        {
            openglVersion = OpenglVersion::_2_1;
        }
        else if (GLEE_VERSION_2_0)
        {
            openglVersion = OpenglVersion::_2_0;
        }
        else if (GLEE_VERSION_1_5)
        {
            openglVersion = OpenglVersion::_1_5;
        }
        else if (GLEE_VERSION_1_4)
        {
            openglVersion = OpenglVersion::_1_4;
        }
        else if (GLEE_VERSION_1_3)
        {
            openglVersion = OpenglVersion::_1_3;
        }
        else if (GLEE_VERSION_1_2)
        {
            openglVersion = OpenglVersion::_1_2;
        }
        else
        {
            openglVersion = OpenglVersion::Unknown;
        }
    }
}

std::string OpenglVersion::ToString(OpenglVersion::Enum version)
{
    switch (version)
    {
    case OpenglVersion::_1_2:
        return "1.2";
    case OpenglVersion::_1_3:
        return "1.3";
    case OpenglVersion::_1_4:
        return "1.4";
    case OpenglVersion::_1_5:
        return "1.5";
    case OpenglVersion::_2_0:
        return "2.0";
    case OpenglVersion::_2_1:
        return "2.1";
    case OpenglVersion::_3_0:
        return "3.0";

    // add any new version above here
    case OpenglVersion::Unknown: // fall through the default
    default:
        return "Unknown";
    }
}

OpenglCapabilities::OpenglCapabilities()
{
    QueryOpenglVersion();
}

OpenglCapabilities* OpenglCapabilities::Instance()
{
    static OpenglCapabilities instance;

    return &instance;
}

OpenglVersion::Enum OpenglCapabilities::GetOpenglVersion() const
{
    return openglVersion;
}

GlslVersion::Enum OpenglCapabilities::GetGlslVersion() const
{
    if (HasShaderSupport())   
    {
        // should be in the form: major.minor.release. vender_info_string
        // note release and vendor_info_string are optional
        const GLubyte* glslVersionStr = glGetString(GL_SHADING_LANGUAGE_VERSION);

        if (glGetError() == GL_INVALID_ENUM)
        {
            // version is assumed to be 1.0.51
            return GlslVersion::_1_0;
        }
        else
        {
            // parse the string
            const std::string versionStr((const char*)glslVersionStr);
            std::string::size_type majorDotPos = versionStr.find_first_of('.');
            uint32_t majorVersion = 0;
            uint32_t minorVersion = 0;
            if  (majorDotPos != std::string::npos)
            {
                std::string major = versionStr.substr(0, majorDotPos);

                // need to fix this
//                 std::string::size_type minorDotPos = versionStr.find('.', majorDotPos+1);
// 
//                 if (minorDotPos == std::string::npos)
//                 {
//                     std::string::size_type minorDotPos = versionStr.find(' ', majorDotPos+1);
//                 }
// 
//                 if (minorDotPos != std::string::npos)
//                 {
//                     std::string minor = versionStr.substr(majorDotPos+1, minorDotPos);
// 
//                     // return GlslVersion:: here
//                 }
            }
        }
    }

    return GlslVersion::Unknown;
}

bool OpenglCapabilities::HasVboSupport() const
{
    return (GLEE_ARB_vertex_buffer_object == GL_TRUE);
}

bool OpenglCapabilities::HasNonPow2TextureSupport() const
{
    return (GLEE_ARB_texture_non_power_of_two == GL_TRUE);
}

bool OpenglCapabilities::HasShaderSupport() const
{
    if (!GLEE_ARB_shading_language_100)
    {
        return false;
    }

    return ((GetOpenglVersion() >= OpenglVersion::_2_0) ||
            (GLEE_ARB_vertex_shader == GL_TRUE &&
            GLEE_ARB_fragment_shader == GL_TRUE));
}