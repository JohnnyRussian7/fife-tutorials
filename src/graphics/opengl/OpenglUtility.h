/**********************************************************************
*	Filename: OpenglUtility.h
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
#ifndef OPENGLUTILITY_H_
#define OPENGLUTILITY_H_

#include "StdIncludes.h"

#include "../TextureEnums.h"
#include "../VertexIndexBufferEnums.h"
#include "../../rendersystem/BlendingMode.h"
#include "../../rendersystem/CullMode.h"
#include "../../rendersystem/PolygonWindingMode.h"
#include "../../rendersystem/FillMode.h"
#include "../../rendersystem/AlphaTestMode.h"
#include "../../rendersystem/RenderEnums.h"
#include "../../rendersystem/ShaderEnums.h"

namespace opengl { namespace utility {
    
    GLenum ConvertPrimitiveType(PrimitiveType::Enum type);
    GLenum ConvertTextureType(TextureType::Enum type);
    GLenum ConvertBufferUsage(HwBufferUsage::Enum usage);
    GLenum ConvertVertexBufferParamSizeType(VertexParamSizeType::Enum type);
    GLenum ConvertIndexBufferType(IndexBufferDataType::Enum type);
    GLenum ConvertShaderType(ShaderType::Enum type);
    GLenum ConvertSrcBlendMode(SrcBlendMode::Enum mode);
    GLenum ConvertDestBlendMode(DestBlendMode::Enum mode);
    GLenum ConvertCullMode(CullType::Enum cullType);
    GLenum ConvertPolygonWindingMode(WindingType::Enum polygonWindingType);
    GLenum ConvertFillMode(FillType::Enum fillType);
    GLenum ConvertAlphaTestMode(AlphaTestType::Enum alphaTestType);
}}

#endif