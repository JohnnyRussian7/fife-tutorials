/**********************************************************************
*	Filename: OpenglRenderer.cpp
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

#include "OpenglRenderer.h"
#include "OpenglCapabilities.h"
#include "OpenglShaderManager.h"
#include "../IShaderProgram.h"
#include "../../Color.h"
#include "../../scene/Renderable.h"
#include "../../scene/IMaterial.h"
#include "../../graphics/TextureFwd.h"
#include "../../graphics/VertexIndexBufferEnums.h"
#include "../../graphics/IVertexBuffer.h"
#include "../../graphics/IIndexBuffer.h"
#include "../../graphics/GenericVertexBuffer.h"
#include "../../graphics/GenericIndexBuffer.h"
#include "../../graphics/opengl/OpenglIndexBuffer.h"
#include "../../graphics/opengl/OpenglVertexBuffer.h"
#include "../../graphics/opengl/OpenglUtility.h"

// useful macro to help with offsets in buffer objects
#define BUFFER_OFFSET(i) ((char*)NULL + (i))

// TODO - temporary - lets create the shaders we are going to use
IShaderProgram* shaderProgram;

void DrawBox()
{
    glBegin(GL_TRIANGLE_STRIP);
    glColor3f(255, 0, 0);
    glTexCoord2f(0.0, 0.0);			// left bottom
    glVertex3f(-2.0, -2.0, -2.0);

    glTexCoord2f(1.0, 0.0);			// right bottom
    glVertex3f(2.0, -2.0, -2.0);

    glTexCoord2f(0.0, 1.0);			// top left
    glVertex3f(-2.0, 2.0, -2.0);

    glTexCoord2f(1.0, 1.0);			// top right
    glVertex3f(2.0, 2.0, -2.0);
    glEnd();
}

void DrawAxes()
{
    const Vector3 origin = Vector3::Zero();
    const Vector3 unitx = Vector3::UnitX();
    const Vector3 unity = Vector3::UnitY();
    const Vector3 unitz = Vector3::UnitZ();

    //     glMatrixMode(GL_MODELVIEW);
    //     glTranslatef (-5, -5, -5);
    glLineWidth (2.0);

    glBegin (GL_LINES);
    glColor3f (1,0,0); // X axis is red.
    glVertex3f(origin.x, origin.y, origin.z);
    glVertex3f(unitx.x, unitx.y, unitx.z);
    glColor3f (0,1,0); // Y axis is green.
    glVertex3f(origin.x, origin.y, origin.z);
    glVertex3f(unity.x, unity.y, unity.z);
    glColor3f (0,0,1); // z axis is blue.
    glVertex3f(origin.x, origin.y, origin.z);
    glVertex3f(unitz.x, unitz.y, unitz.z);
    glEnd();
}

namespace opengl {

    OpenglRenderer::OpenglRenderer(const RenderSystemSettings& settings)
    : m_settings(settings), m_viewport(Viewport()),
    m_modelMatrix(Matrix4::Identity()), m_viewMatrix(Matrix4::Identity()),
    m_projectionMatrix(Matrix4::Identity()), m_modelMatrixUpdate(false), m_viewMatrixUpdate(false),
    m_projectionMatrixUpdate(false), m_activeTexture(0), m_shaderManager(new OpenglShaderManager()),
    m_useVbo(false), m_axesRenderable(new Renderable()), m_clearColor(Color::Black())
    {
        m_useVbo = OpenglCapabilities::Instance()->HasVboSupport() && m_settings.useVbo;

        if (OpenglCapabilities::Instance()->HasShaderSupport())
        {
            // TODO - this is temporary, just for testing
            shaderProgram = m_shaderManager->CreateShaderProgram("..\\..\\shaders\\opengl\\simple.vs",
                "..\\..\\shaders\\opengl\\colorinvert.fs");
        }
        else
        {
            std::cout << "Shaders not supported in opengl version: " << OpenglVersion::ToString(OpenglCapabilities::Instance()->GetOpenglVersion()) << std::endl;
        }

        // TODO - figure out where to put this
        // setup the color material properly so that even if lighting
        // is enabled the color for the lines will be specified by the 
        // color set in the vertex array for the axes
        glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
        glEnable(GL_COLOR_MATERIAL);
    }

    OpenglRenderer::~OpenglRenderer()
    {
        delete m_axesRenderable;
        m_axesRenderable = 0;
    }

    RenderSystemType::Enum OpenglRenderer::GetRenderSystemType() const
    {
        return RenderSystemType::Opengl;
    }

    void OpenglRenderer::SetViewPort(const Viewport& viewport)
    {
        m_viewport = viewport;

        // create viewport
        glViewport(m_viewport.GetLeft(), m_viewport.GetTop(), m_viewport.GetWidth(), m_viewport.GetHeight());

        // TODO - this should be done elsewhere
        // setup the frustum
        int32_t aspectRatio = viewport.GetWidth() / viewport.GetHeight();
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glFrustum(-0.5, 0.5, -aspectRatio*0.5, aspectRatio*0.5, 1, 5000);

        // enable scissor testing to clip against viewport
        glScissor(m_viewport.GetLeft(), m_viewport.GetTop(), m_viewport.GetWidth(), m_viewport.GetHeight());
        glEnable(GL_SCISSOR_TEST);
    }

    void OpenglRenderer::SetTransform(TransformType::Enum type, const Matrix4& mat)
    {
        switch (type)
        {
        case TransformType::Model:
            {
                m_modelMatrix = mat;

                glMatrixMode(GL_MODELVIEW);
                glLoadMatrixf((m_viewMatrix*m_modelMatrix).m_matrix);
            }
            break;
        case TransformType::View:
            {
                m_viewMatrix = mat;

                glMatrixMode(GL_MODELVIEW);
                glLoadMatrixf((m_viewMatrix*m_modelMatrix).m_matrix);
            }
            break;
        case TransformType::Projection:
            {
                m_projectionMatrix = mat;

                glMatrixMode(GL_PROJECTION);
                glLoadMatrixf(m_projectionMatrix.m_matrix);
            }
            break;
        default:
            {
                // TODO - print error here
                assert(0);
            }
            break;
        }
    }

    void OpenglRenderer::SetBlendingMode(const BlendingMode& blendingMode)
    {
        if (blendingMode != m_blendingMode)
        {
            if (!blendingMode.IsEnabled())
            {
                glDisable(GL_BLEND);
            }
            else
            {
                glBlendFunc(utility::ConvertSrcBlendMode(blendingMode.GetSrcBlendMode()), 
                            utility::ConvertDestBlendMode(blendingMode.GetDestBlendMode()));

                if (blendingMode.IsEnabled() && !m_blendingMode.IsEnabled())
                {
                    glEnable(GL_BLEND);
                }
            }

            // store blending mode
            m_blendingMode = blendingMode;
        }
    }

    void OpenglRenderer::SetCullMode(const CullMode& cullMode)
    {
        if (cullMode != m_cullMode)
        {
            if (!cullMode.IsEnabled())
            {
                glDisable(GL_CULL_FACE);
            }
            else
            {
                glCullFace(utility::ConvertCullMode(cullMode.GetCullType()));

                if (cullMode.IsEnabled() && !m_cullMode.IsEnabled())
                {
                    glEnable(GL_CULL_FACE);
                }
            }

            // storing cull mode
            m_cullMode = cullMode;
        }
    }

    void OpenglRenderer::SetPolygonWindingMode(const PolygonWindingMode& windingMode)
    {
        if (windingMode != m_windingMode)
        {
            glFrontFace(utility::ConvertPolygonWindingMode(windingMode.GetWindingType()));

            // storing winding mode
            m_windingMode = windingMode;
        }
    }

    void OpenglRenderer::SetFillMode(const FillMode& fillMode)
    {
        if (fillMode != m_fillMode)
        {
            // TODO - should we allow setting polygon mode differently depending on 
            //        side (front/back/both)?
            glPolygonMode(GL_FRONT_AND_BACK, utility::ConvertFillMode(fillMode.GetFillType()));

            m_fillMode = fillMode;
        }
    }

    void OpenglRenderer::SetAlphaTestMode(const AlphaTestMode& alphaTestMode)
    {
        if (alphaTestMode != m_alphaTestMode)
        {
            if (!alphaTestMode.IsEnabled())
            {
                glDisable(GL_ALPHA_TEST);
            }
            else
            {
                glAlphaFunc(utility::ConvertAlphaTestMode(alphaTestMode.GetType()), alphaTestMode.GetValue());

                if (alphaTestMode.IsEnabled() && !m_alphaTestMode.IsEnabled())
                {
                    glEnable(GL_ALPHA_TEST);
                }
            }

            // store alpha test mode
            m_alphaTestMode = alphaTestMode;
        }
    }

    void OpenglRenderer::UpdateAxesRenderOperation(const Matrix4& rotation)
    {
        // 2 vertexes per line and 3 lines (X,Y,Z)
        static const uint32_t NumVertices = 6;

        if (!m_axesRenderable->GetVertexBuffer())
        {
            m_axesRenderable->SetVertexBuffer(CreateVertexBuffer(NumVertices, sizeof(Vertex), HwBufferUsage::Dynamic));
        }

        IVertexBuffer* vertexBuffer = m_axesRenderable->GetVertexBuffer();

        if (vertexBuffer)
        {
            float axesLength = 100;

            std::vector<Vertex> axes;
            axes.reserve(NumVertices);

            Vertex origin;
            origin.m_position = Vector3::Zero();

            // x axis
            origin.m_color = Color::Red();

            Vertex x;
            x.m_position = Normalize(rotation.GetX())*axesLength;
            x.m_color = Color::Red();

            axes.push_back(origin);
            axes.push_back(x);

            // y axis
            origin.m_color = Color::Green();

            Vertex y;
            y.m_position = Normalize(rotation.GetY())*axesLength;
            y.m_color = Color::Green();
            
            axes.push_back(origin);
            axes.push_back(y);

            // z axis
            origin.m_color = Color::Blue();

            Vertex z;
            z.m_position = Normalize(rotation.GetZ())*axesLength;
            z.m_color = Color::Blue();

            axes.push_back(origin);
            axes.push_back(z);

            vertexBuffer->WriteData(&axes[0], axes.size(), 0);

            m_axesRenderable->SetPrimitiveType(PrimitiveType::Lines);

            m_axesRenderOperation.SetVertexBuffer(vertexBuffer);
            m_axesRenderOperation.SetTransform(m_axesRenderable->GetTransform());
            m_axesRenderOperation.SetPrimitiveType(m_axesRenderable->GetPrimitiveType());
        }
    }

    const RenderOperation& OpenglRenderer::GetAxesRenderOperation() const
    {
        return m_axesRenderOperation;
    }

    IVertexBuffer* OpenglRenderer::CreateVertexBuffer(uint32_t numVertices, uint32_t vertexSize, HwBufferUsage::Enum usage)
    {
        if (m_useVbo)
        {
            return new OpenglVertexBuffer(numVertices, vertexSize, usage);
        }

        return new GenericVertexBuffer(numVertices, vertexSize);
    }

    IIndexBuffer* OpenglRenderer::CreateIndexBuffer(uint32_t numIndices, IndexBufferDataType::Enum indexType, HwBufferUsage::Enum usage)
    {
        if (m_useVbo)
        {
            return new OpenglIndexBuffer(numIndices, indexType, usage);
        }

        return new GenericIndexBuffer(numIndices, indexType);
    }

    void OpenglRenderer::SetClearColor(const Color& color)
    {
        if (color != m_clearColor)
        {
            m_clearColor = color;
            glClearColor(m_clearColor.r, m_clearColor.g, m_clearColor.b, m_clearColor.a);
        }
    }

    void OpenglRenderer::ClearBuffers(bool colorBuffer, bool depthBuffer)
    {
        GLbitfield buffers = 0;

        if (colorBuffer)
        {
            buffers |= GL_COLOR_BUFFER_BIT;
        }
        if (depthBuffer)
        {
            buffers |= GL_DEPTH_BUFFER_BIT;
        }

        glClear(buffers);
    }

    void OpenglRenderer::Render(const RenderOperation& renderOperation)
    {
        // set the model transform
        SetTransform(TransformType::Model, renderOperation.GetTransform());

        // set the blending mode
        SetBlendingMode(renderOperation.GetBlendingMode());

        // set the cull mode
        SetCullMode(renderOperation.GetCullMode());

        // set the winding mode
        SetPolygonWindingMode(renderOperation.GetPolygonWindingMode());

        // set the fill mode
        SetFillMode(renderOperation.GetFillMode());

        // set the alpha test mode
        SetAlphaTestMode(renderOperation.GetAlphaTestMode());

        IMaterial* material = renderOperation.GetMaterial();
        if (material)
        {
            TexturePtr texture = material->GetTexture();

            if (texture)
            {
                GLenum textureType = utility::ConvertTextureType(texture->GetType());
                // TODO - should be settable outside of render system
                glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );
                glTexParameteri(textureType, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); 
                glTexParameteri(textureType, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE); 

                //         glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST );
                //         glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
                //         glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
                //         glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
                // 
                //         glActiveTextureARB(GL_TEXTURE0);
                glEnable(textureType);    
                glBindTexture(textureType, texture->GetId());
            }
        }

        IVertexBuffer* vertexBuffer = renderOperation.GetVertexBuffer();
        IIndexBuffer* indexBuffer = renderOperation.GetIndexBuffer();

        if (vertexBuffer)
        {
            if (m_useVbo)
            {
                glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer->GetBufferId());

                glVertexPointer(3, 
                    utility::ConvertVertexBufferParamSizeType(VertexParamSizeType::Float3), 
                    vertexBuffer->GetStride(), 
                    BUFFER_OFFSET(vertexBuffer->GetOffset(VertexParamType::Vertex)));
                glEnableClientState(GL_VERTEX_ARRAY);

                glColorPointer(4, 
                    utility::ConvertVertexBufferParamSizeType(VertexParamSizeType::Float4), 
                    vertexBuffer->GetStride(), 
                    BUFFER_OFFSET(vertexBuffer->GetOffset(VertexParamType::Color)));
                glEnableClientState(GL_COLOR_ARRAY);

                glTexCoordPointer(2, 
                    utility::ConvertVertexBufferParamSizeType(VertexParamSizeType::Float2), 
                    vertexBuffer->GetStride(), 
                    BUFFER_OFFSET(vertexBuffer->GetOffset(VertexParamType::Texture))); 
                glEnableClientState(GL_TEXTURE_COORD_ARRAY);
            }
            else
            {
                glVertexPointer(3, 
                    utility::ConvertVertexBufferParamSizeType(VertexParamSizeType::Float3), 
                    vertexBuffer->GetStride(), 
                    vertexBuffer->GetData(vertexBuffer->GetOffset(VertexParamType::Vertex)));
                glEnableClientState(GL_VERTEX_ARRAY);

                glColorPointer(4, 
                    utility::ConvertVertexBufferParamSizeType(VertexParamSizeType::Float4), 
                    vertexBuffer->GetStride(), 
                    vertexBuffer->GetData(vertexBuffer->GetOffset(VertexParamType::Color)));
                glEnableClientState(GL_COLOR_ARRAY);

                glTexCoordPointer(2, 
                    utility::ConvertVertexBufferParamSizeType(VertexParamSizeType::Float2), 
                    vertexBuffer->GetStride(), 
                    vertexBuffer->GetData(vertexBuffer->GetOffset(VertexParamType::Texture))); 
                glEnableClientState(GL_TEXTURE_COORD_ARRAY);
            }

            if (indexBuffer)
            {
                // TODO - this should be programmable
                uint32_t indexStart = 0;
                void *indexData = 0;
                if (m_useVbo)
                {
                    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer->GetBufferId());
                    indexData = BUFFER_OFFSET(indexStart * indexBuffer->GetStride());
                }
                else
                {
                    indexData = indexBuffer->GetData(indexStart);
                }

                //glDrawElements(utility::ConvertPrimitiveType(renderable->GetPrimitiveType()), indexBuffer->GetBufferSize(), opengl::utility::ConvertIndexBufferType(indexBuffer->GetType()), indexData);
                glDrawRangeElements(utility::ConvertPrimitiveType(renderOperation.GetPrimitiveType()), 0, indexBuffer->GetBufferSize()-1, indexBuffer->GetBufferSize(), utility::ConvertIndexBufferType(indexBuffer->GetType()), indexData); 
            }
            else
            {
                glDrawArrays(utility::ConvertPrimitiveType(renderOperation.GetPrimitiveType()), 0, vertexBuffer->GetNumVertices());
            }

            // disable client state
            glDisableClientState(GL_VERTEX_ARRAY);
            glDisableClientState(GL_COLOR_ARRAY);
            glDisableClientState(GL_TEXTURE_COORD_ARRAY);

            if (m_useVbo)
            {
                // unbind the buffers
                glBindBuffer(GL_ARRAY_BUFFER, 0);
                glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
            }
        }

        if (material)
        {
            TexturePtr texture = material->GetTexture();

            if (texture)
            {
                // disable texture
                glDisable(utility::ConvertTextureType(texture->GetType()));
            }
        }
        
        //DrawAxes();

        //     if (shaderProgram)
        //     {
        //         // use shader program
        //         shaderProgram->Enable();
        //     }
        // 
        //     DrawBox();
        // 
        //     if (shaderProgram)
        //     {
        //         shaderProgram->Disable();
        //     }
    }

    void OpenglRenderer::RenderAxes()
    {
        // current clear color
        Color color = m_clearColor;

        // save current viewport 
        Viewport currentViewport = m_viewport;

        // set new viewport
        //SetViewPort(Viewport(0,0,currentViewport.GetWidth(),currentViewport.GetHeight()));
        SetViewPort(Viewport(currentViewport.GetWidth()-75,0,75,75));

        ClearBuffers();
        
        SetClearColor(color);

        // save current transform
        glPushMatrix();

        // reset model view matrix
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        Matrix4 viewRotation(m_viewMatrix);
        viewRotation[12] = 0;
        viewRotation[13] = 0;
        viewRotation[14] = -300;

        SetTransform(TransformType::Model, Matrix4::Identity());
        SetTransform(TransformType::View, viewRotation);

        // set the line width to 2
        glLineWidth(2.0);

        UpdateAxesRenderOperation(viewRotation);

        Render(GetAxesRenderOperation());

        // remove matrix to restore state
        glPopMatrix();

        // restore viewport
        SetViewPort(currentViewport);
    }
}