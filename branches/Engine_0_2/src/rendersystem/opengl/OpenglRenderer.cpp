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

void DrawBox()
{
    glBegin(GL_TRIANGLE_STRIP);
    //glColor3f(255, 0, 0);
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

OpenglRenderer::OpenglRenderer(const RenderSystemSettings& settings)
: m_settings(settings), m_viewport(Viewport()),
  m_modelMatrix(Matrix4::Identity()), m_viewMatrix(Matrix4::Identity()),
  m_projectionMatrix(Matrix4::Identity()), m_modelMatrixUpdate(false), m_viewMatrixUpdate(false),
  m_projectionMatrixUpdate(false), m_activeTexture(0), m_vboSupport(false), m_nonPowerOfTwoTextureSupport(false)
{
    m_vboSupport = (GLEE_ARB_vertex_buffer_object == GL_TRUE);
    m_nonPowerOfTwoTextureSupport = (GLEE_ARB_texture_non_power_of_two == GL_TRUE);
}

OpenglRenderer::~OpenglRenderer()
{

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
}

void OpenglRenderer::SetTransform(TransformType::Enum type, const Matrix4& mat)
{
	switch (type)
	{
		case TransformType::Model:
		{
            m_modelMatrix = mat;

            glMatrixMode(GL_MODELVIEW);
            glLoadMatrixf((m_viewMatrix*m_modelMatrix).matrix);
            m_modelMatrix = mat;
		}
		break;
		case TransformType::View:
		{
            m_viewMatrix = mat;

            glMatrixMode(GL_MODELVIEW);
            glLoadMatrixf((m_viewMatrix*m_modelMatrix).matrix);
		}
		break;
		case TransformType::Projection:
		{
            m_projectionMatrix = mat;

            glMatrixMode(GL_PROJECTION);
            glLoadMatrixf(m_projectionMatrix.matrix);
		}
		break;
		default:
		{
            // TODO - print error here
		}
		break;
	}
}
IVertexBuffer* OpenglRenderer::CreateVertexBuffer(uint32_t numVertices, uint32_t vertexSize, HwBufferUsage::Enum usage)
{
    if (m_vboSupport && m_settings.useVbo)
    {
        return new OpenglVertexBuffer(numVertices, vertexSize, usage);
    }

    return new GenericVertexBuffer(numVertices, vertexSize);
}

IIndexBuffer* OpenglRenderer::CreateIndexBuffer(uint32_t numIndices, IndexBufferDataType::Enum indexType, HwBufferUsage::Enum usage)
{
    if (m_vboSupport && m_settings.useVbo)
    {
        return new OpenglIndexBuffer(numIndices, indexType, usage);
    }

    return new GenericIndexBuffer(numIndices, indexType);
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

void OpenglRenderer::Render(Renderable* renderable)
{
    if (!renderable)
    {
        return;
    }

    IMaterial* material = renderable->GetMaterial();

    if (material)
    {
        TexturePtr texture = renderable->GetMaterial()->GetTexture();

        if (texture)
        {
            // TODO - this should be settable outside of renderer
            // enable blending
            glEnable(GL_BLEND); 
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

            glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );
    //         glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST );
    //         glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    //         glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
    //         glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
    // 
    //         glActiveTextureARB(GL_TEXTURE0);
            glEnable(opengl::utility::ConvertTextureType(texture->GetType()));    
            glBindTexture(opengl::utility::ConvertTextureType(texture->GetType()), texture->GetId());
        }
    }

    IVertexBuffer* vertexBuffer = renderable->GetVertexBuffer();
    IIndexBuffer* indexBuffer = renderable->GetIndexBuffer();

    if (vertexBuffer)
    {
        if (m_vboSupport && m_settings.useVbo)
        {
            glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer->GetBufferId());

            glVertexPointer(3, 
                opengl::utility::ConvertVertexBufferParamSizeType(VertexParamSizeType::Float3), 
                vertexBuffer->GetStride(), 
                BUFFER_OFFSET(vertexBuffer->GetOffset(VertexParamType::Position)));
            glEnableClientState(GL_VERTEX_ARRAY);

            glColorPointer(4, 
                opengl::utility::ConvertVertexBufferParamSizeType(VertexParamSizeType::Float4), 
                vertexBuffer->GetStride(), 
                BUFFER_OFFSET(vertexBuffer->GetOffset(VertexParamType::Color)));
            glEnableClientState(GL_COLOR_ARRAY);

            glTexCoordPointer(2, 
                opengl::utility::ConvertVertexBufferParamSizeType(VertexParamSizeType::Float2), 
                vertexBuffer->GetStride(), 
                BUFFER_OFFSET(vertexBuffer->GetOffset(VertexParamType::Texture))); 
            glEnableClientState(GL_TEXTURE_COORD_ARRAY);
        }
        else
        {
            glVertexPointer(3, 
                opengl::utility::ConvertVertexBufferParamSizeType(VertexParamSizeType::Float3), 
                vertexBuffer->GetStride(), 
                vertexBuffer->GetData(vertexBuffer->GetOffset(VertexParamType::Position)));
            glEnableClientState(GL_VERTEX_ARRAY);

            glColorPointer(4, 
                opengl::utility::ConvertVertexBufferParamSizeType(VertexParamSizeType::Float4), 
                vertexBuffer->GetStride(), 
                vertexBuffer->GetData(vertexBuffer->GetOffset(VertexParamType::Color)));
            glEnableClientState(GL_COLOR_ARRAY);

            glTexCoordPointer(2, 
                opengl::utility::ConvertVertexBufferParamSizeType(VertexParamSizeType::Float2), 
                vertexBuffer->GetStride(), 
                vertexBuffer->GetData(vertexBuffer->GetOffset(VertexParamType::Texture))); 
            glEnableClientState(GL_TEXTURE_COORD_ARRAY);
        }

        if (indexBuffer)
        {
            // TODO - this should be programmable
            uint32_t indexStart = 0;
            void *indexData = 0;
            if (m_vboSupport && m_settings.useVbo)
            {
                glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer->GetBufferId());
                indexData = BUFFER_OFFSET(indexStart * indexBuffer->GetStride());
            }
            else
            {
                indexData = indexBuffer->GetData(indexStart);
            }

            //glDrawElements(opengl::utility::ConvertPrimitiveType(renderable->GetPrimitiveType()), indexBuffer->GetBufferSize(), opengl::utility::ConvertIndexBufferType(indexBuffer->GetType()), indexData);
            glDrawRangeElements(opengl::utility::ConvertPrimitiveType(renderable->GetPrimitiveType()), 0, indexBuffer->GetBufferSize()-1, indexBuffer->GetBufferSize(), opengl::utility::ConvertIndexBufferType(indexBuffer->GetType()), indexData); 
        }
        else
        {
            glDrawArrays(opengl::utility::ConvertPrimitiveType(renderable->GetPrimitiveType()), 0, vertexBuffer->GetNumVertices());
        }

        // disable client state
        glDisableClientState(GL_VERTEX_ARRAY);
        glDisableClientState(GL_COLOR_ARRAY);
        glDisableClientState(GL_TEXTURE_COORD_ARRAY);

        if (m_vboSupport && m_settings.useVbo)
        {
            // unbind the buffers
            glBindBuffer(GL_ARRAY_BUFFER, 0);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        }
    }

    //DrawAxes();
    //DrawBox();
}