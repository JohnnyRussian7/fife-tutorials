/**********************************************************************
*	Filename: OpenglRenderer.h
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
#ifndef OPENGLRENDERER_H_
#define OPENGLRENDERER_H_

#include "../IRenderSystem.h"

#include "../RenderEnums.h"
#include "../BlendingMode.h"
#include "../CullMode.h"
#include "../FillMode.h"
#include "../AlphaTestMode.h"
#include "../RenderOperation.h"
#include "../../math/Matrix4.h"
#include "../../scene/Viewport.h"
#include "../../graphics/opengl/OpenglTexture.h"
#include "../../graphics/VertexIndexBufferEnums.h"

class IVertexBuffer;
class IIndexBuffer;
class Renderable;

namespace opengl {
    class OpenglShaderManager;
}

namespace opengl {

    class OpenglRenderer : public IRenderSystem
    {
    public:
	    OpenglRenderer(const RenderSystemSettings& settings);
	    ~OpenglRenderer();

	    virtual RenderSystemType::Enum GetRenderSystemType() const;
	    virtual void SetViewPort(const Viewport& viewport);
	    virtual void SetTransform(TransformType::Enum type, const Matrix4& mat);

	    void EnableTextures(TextureType::Enum type);
	    void DisableTextures(TextureType::Enum type);

	    void SetActiveTexture(OpenglTexture* texture);

        virtual IVertexBuffer* CreateVertexBuffer(uint32_t numVertices, uint32_t vertexSize, HwBufferUsage::Enum usage);
        virtual IIndexBuffer* CreateIndexBuffer(uint32_t numIndices, IndexBufferDataType::Enum indexType, HwBufferUsage::Enum usage);

        virtual void SetClearColor(const Color& color);
        virtual void ClearBuffers(bool colorBuffer=true, bool depthBuffer=true);
	    virtual void Render(const RenderOperation& renderOperation);
        virtual void RenderAxes();
      
    protected:
        virtual void SetBlendingMode(const BlendingMode& BlendingMode);
        virtual void SetCullMode(const CullMode& cullMode);
        virtual void SetPolygonWindingMode(const PolygonWindingMode& windingMode);
        virtual void SetFillMode(const FillMode& fillMode);
        virtual void SetAlphaTestMode(const AlphaTestMode& alphaTestMode);

        void UpdateAxesRenderOperation(const Matrix4& rotation);
        const RenderOperation& GetAxesRenderOperation() const;

    private:
        RenderSystemSettings m_settings;

	    Viewport m_viewport;
	    Matrix4 m_modelMatrix;
	    Matrix4 m_viewMatrix;
	    Matrix4 m_projectionMatrix;

        bool m_modelMatrixUpdate;
        bool m_viewMatrixUpdate;
        bool m_projectionMatrixUpdate;

	    OpenglTexture* m_activeTexture;

        OpenglShaderManager* m_shaderManager;

        Renderable* m_axesRenderable;
        RenderOperation m_axesRenderOperation;

        BlendingMode m_blendingMode;
        CullMode m_cullMode;
        PolygonWindingMode m_windingMode;
        FillMode m_fillMode;
        AlphaTestMode m_alphaTestMode;
        Color m_clearColor;

        bool m_useVbo;
    };
}

#endif
