/**********************************************************************
*	Filename: IRenderSystem.h
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
#ifndef IRENDERSYSTEM_H_
#define IRENDERSYSTEM_H_

#include "../StdIncludes.h"

#include "RenderSystemTypes.h"
#include "RenderEnums.h"
#include "../graphics/VertexIndexBufferEnums.h"

class Viewport;
class IVertexBuffer;
class IIndexBuffer;
class Renderable;
struct Matrix4;

struct RenderSystemSettings
{
    RenderSystemSettings()
    : renderSystemType(RenderSystemType::Opengl), useVbo(true)
    {

    }

    RenderSystemType::Enum renderSystemType;
    bool useVbo;


};

class IRenderSystem
{
public:
	virtual ~IRenderSystem() { };

	virtual RenderSystemType::Enum GetRenderSystemType() const = 0;
	virtual void SetViewPort(const Viewport& viewport) = 0;
    virtual void SetTransform(TransformType::Enum type, const Matrix4& mat) = 0;

    virtual IVertexBuffer* CreateVertexBuffer(uint32_t numVertices, uint32_t vertexSize, HwBufferUsage::Enum usage) = 0;
    virtual IIndexBuffer* CreateIndexBuffer(uint32_t numIndices, IndexBufferDataType::Enum indexType, HwBufferUsage::Enum usage) = 0;

    virtual void ClearBuffers(bool colorBuffer=true, bool depthBuffer=true) = 0;
	virtual void Render(Renderable* renderable) = 0;
};

IRenderSystem* CreateRenderSystem(const RenderSystemSettings& settings);

#endif
