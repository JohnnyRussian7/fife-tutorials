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
#include "PrecompiledIncludes.h"

#include "OpenglUtility.h"
#include "../../rendersystem/opengl/OpenglCapabilities.h"

namespace opengl { namespace utility {

    GLenum ConvertPrimitiveType(PrimitiveType::Enum type)
    {
        switch (type)
        {
        case PrimitiveType::Points:
            return GL_POINTS;
        case PrimitiveType::Lines:
            return GL_LINES;
        case PrimitiveType::LineStrip:
            return GL_LINE_STRIP;
        case PrimitiveType::LineLoop:
            return GL_LINE_LOOP;
        case PrimitiveType::Triangles:
            return GL_TRIANGLES;
        case PrimitiveType::TriangleStrip:
            return GL_TRIANGLE_STRIP;
        case PrimitiveType::TriangleFan:
            return GL_TRIANGLE_FAN;
        case PrimitiveType::Quads:
            return GL_QUADS;
        case PrimitiveType::QuadStrip:
            return GL_QUAD_STRIP;
        case PrimitiveType::Polygon:
            return GL_POLYGON;
        default:
            return GL_TRIANGLES;
        }
    }

    GLenum ConvertTextureType(TextureType::Enum type)
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

    GLenum ConvertBufferUsage(HwBufferUsage::Enum usage)
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

    GLenum ConvertVertexBufferParamSizeType(VertexParamSizeType::Enum type)
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

    GLenum ConvertIndexBufferType(IndexBufferDataType::Enum type)
    {
        switch (type)
        {
        case IndexBufferDataType::_8bit:
            return GL_UNSIGNED_BYTE;
        case IndexBufferDataType::_16bit:
            return GL_UNSIGNED_SHORT;
        case IndexBufferDataType::_32bit:
            return GL_UNSIGNED_INT;
        default:
            return GL_UNSIGNED_SHORT;
        }
    }

    GLenum ConvertShaderType(ShaderType::Enum type)
    {
        OpenglVersion::Enum version = OpenglCapabilities::Instance()->GetOpenglVersion();
        switch (type)
        {
        case ShaderType::Vertex:
            if (version >= OpenglVersion::_2_0)
            {
                return GL_VERTEX_SHADER;
            }
            else
            {
                return GL_VERTEX_SHADER_ARB;
            }
        case ShaderType::Fragment:
            if (version >= OpenglVersion::_2_0)
            {
                return GL_FRAGMENT_SHADER;
            }
            else
            {
                return GL_FRAGMENT_SHADER_ARB;
            }
        default:
            // TODO - throw error here
            assert(0);

            if (version >= OpenglVersion::_2_0)
            {
                return GL_VERTEX_SHADER;
            }
            else
            {
                return GL_VERTEX_SHADER_ARB;
            }
        }
    }

    GLenum ConvertSrcBlendMode(SrcBlendMode::Enum mode)
    {
        switch (mode)
        {
        case SrcBlendMode::Zero:
            return GL_ZERO;
        case SrcBlendMode::One:
            return GL_ONE;
        case SrcBlendMode::SrcColor:
            return GL_SRC_COLOR;
        case SrcBlendMode::OneMinusSrcColor:
            return GL_ONE_MINUS_SRC_COLOR;
        case SrcBlendMode::SrcAlpha:
            return GL_SRC_ALPHA;
        case SrcBlendMode::OneMinusSrcAlpha:
            return GL_ONE_MINUS_SRC_ALPHA;
        case SrcBlendMode::DestAlpha:
            return GL_DST_ALPHA;
        case SrcBlendMode::OneMinusDestAlpha:
            return GL_ONE_MINUS_DST_ALPHA;
        case SrcBlendMode::ConstantColor:
            return GL_CONSTANT_COLOR;
        case SrcBlendMode::OneMinusConstantColor:
            return GL_ONE_MINUS_CONSTANT_COLOR;
        case SrcBlendMode::ConstantAlpha:
            return GL_CONSTANT_ALPHA;
        case SrcBlendMode::OneMinusConstantAlpha:
            return GL_ONE_MINUS_CONSTANT_ALPHA;
        case SrcBlendMode::SrcAlphaSaturate:
            return GL_SRC_ALPHA_SATURATE;
        default:
            return GL_ONE;
        }
    }

    GLenum ConvertDestBlendMode(DestBlendMode::Enum mode)
    {
        switch (mode)
        {
        case DestBlendMode::Zero:
            return GL_ZERO;
        case DestBlendMode::One:
            return GL_ONE;
        case DestBlendMode::SrcColor:
            return GL_SRC_COLOR;
        case DestBlendMode::DestColor:
            return GL_DST_COLOR;
        case DestBlendMode::OneMinusDestColor:
            return GL_ONE_MINUS_DST_COLOR;
        case DestBlendMode::SrcAlpha:
            return GL_SRC_ALPHA;
        case DestBlendMode::OneMinusSrcAlpha:
            return GL_ONE_MINUS_SRC_ALPHA;
        case DestBlendMode::DestAlpha:
            return GL_DST_ALPHA;
        case DestBlendMode::OneMinusDestAlpha:
            return GL_ONE_MINUS_DST_ALPHA;
        case DestBlendMode::ConstantColor:
            return GL_CONSTANT_COLOR;
        case DestBlendMode::OneMinusConstantColor:
            return GL_ONE_MINUS_CONSTANT_COLOR;
        case DestBlendMode::ConstantAlpha:
            return GL_CONSTANT_ALPHA;
        case DestBlendMode::OneMinusConstantAlpha:
            return GL_ONE_MINUS_CONSTANT_ALPHA;
        default:
            return GL_ZERO;
        }
    }

    GLenum ConvertCullMode(CullType::Enum cullMode)
    {
        switch (cullMode)
        {
        case CullType::Back:
            return GL_BACK;
        case CullType::Front:
            return GL_FRONT;
        case CullType::Both:
            return GL_FRONT_AND_BACK;
        default:
            return GL_BACK;
        }
    }

    GLenum ConvertPolygonWindingMode(WindingType::Enum windingType)
    {
        switch (windingType)
        {
        case WindingType::Clockwise:
            return GL_CW;
        case WindingType::CounterClockwise:
            return GL_CCW;
        default:
            return GL_CCW;
        }
    }

    GLenum ConvertFillMode(FillType::Enum fillType)
    {
        switch (fillType)
        {
        case FillType::Point:
            return GL_POINT;
        case FillType::Line:
            return GL_LINE;
        case FillType::Fill:
            return GL_FILL;
        default:
            return GL_FILL;
        }
    }

    GLenum ConvertAlphaTestMode(AlphaTestType::Enum alphaTestType)
    {
        switch (alphaTestType)
        {
        case AlphaTestType::Never:
            return GL_NEVER;
        case AlphaTestType::Less:
            return GL_LESS;
        case AlphaTestType::Equal:
            return GL_EQUAL;
        case AlphaTestType::LessEqual:
            return GL_LEQUAL;
        case AlphaTestType::Greater:
            return GL_GREATER;
        case AlphaTestType::NotEqual:
            return GL_NOTEQUAL;
        case AlphaTestType::GreaterEqual:
            return GL_GEQUAL;
        case AlphaTestType::Always:
            return GL_ALWAYS;
        default:
            return GL_ALWAYS;
        }
    }

}}