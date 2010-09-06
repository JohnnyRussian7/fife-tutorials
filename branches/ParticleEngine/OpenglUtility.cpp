/**********************************************************************
*	Filename: OpenglUtility.cpp
*	
*	Copyright (C) 2010, FIFE team
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

#include "OpenglUtility.h"

namespace opengl { namespace utility {

    GLenum ConvertToOpenglTextureType(TextureType::Enum type)
    {
        switch (type)
        {
        case TextureType::_1d:
            return GL_TEXTURE_1D;
        case TextureType::_2d:
            return GL_TEXTURE_2D;
        case TextureType::_3d:
            return GL_TEXTURE_3D;
        case TextureType::Cube:
            return GL_TEXTURE_CUBE_MAP;
        default:
            return GL_TEXTURE_2D;
        }
    }

    GLenum ConvertToOpenglBufferUsage(HwBufferUsage::Enum usage)
    {
        switch (usage)
        {
        case HwBufferUsage::Static:
            return GL_STATIC_DRAW_ARB;
        case HwBufferUsage::Dynamic:
            return GL_DYNAMIC_DRAW_ARB;
        case HwBufferUsage::Stream:
            return GL_STREAM_DRAW_ARB;
        }

        return GL_DYNAMIC_DRAW_ARB;
    }

    GLenum ConvertToOpenglVertexBufferParamSizeType(VertexParamSizeType::Enum type)
    {
        switch (type)
        {
        case VertexParamSizeType::Float1:
        case VertexParamSizeType::Float2:
        case VertexParamSizeType::Float3:
        case VertexParamSizeType::Float4:
            return GL_FLOAT;
        default:
            return 0;
        }
    }
}}