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

// TODO - this is temporary
#include <iostream>

#include "glee/GLee.h"
#include "OpenglRenderer.h"
#include "BufferEnums.h"
#include "OpenglUtility.h"
#include "OpenglVertexBuffer.h"
#include "GenericVertexBuffer.h"
#include "OpenglIndexBuffer.h"
#include "GenericIndexBuffer.h"
#include "Renderable.h"
#include "Color.h"


// useful macro to help with offsets in buffer objects
#define BUFFER_OFFSET(i) ((char*)NULL + (i))

// TODO - this is temporary, should be removed
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

OpenglRenderer::OpenglRenderer(const RenderSystemSettings& settings)
: m_settings(settings), m_viewport(Viewport()),
  m_modelMatrix(Matrix4::Identity()), m_viewMatrix(Matrix4::Identity()),
  m_projectionMatrix(Matrix4::Identity()), m_modelMatrixUpdate(false), m_viewMatrixUpdate(false),
  m_projectionMatrixUpdate(false), m_activeTexture(0), m_vboSupport(false)
{
    m_vboSupport = (GLEE_ARB_vertex_buffer_object == GL_TRUE);
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
	// setup the frustrum
	int aspectRatio = viewport.GetWidth() / viewport.GetHeight();
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
            m_modelMatrixUpdate = true;
		}
		break;
		case TransformType::View:
		{
           m_viewMatrix = mat;
           m_viewMatrixUpdate = true;
		}
		break;
		case TransformType::Projection:
		{
            m_projectionMatrix = mat;
            m_projectionMatrixUpdate = true;
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
    if (m_vboSupport)
    {
        return new OpenglVertexBuffer(numVertices, vertexSize, usage);
    }

    return new GenericVertexBuffer(numVertices, vertexSize);
}

IIndexBuffer* OpenglRenderer::CreateIndexBuffer(uint32_t numIndices, IndexBufferDataType::Enum indexType, HwBufferUsage::Enum usage)
{
    if (m_vboSupport)
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
    if (m_projectionMatrixUpdate)
    {
        glMatrixMode(GL_PROJECTION);
        glLoadMatrixf(m_projectionMatrix.matrix);
        m_projectionMatrixUpdate = false;
    }

	glMatrixMode(GL_MODELVIEW);
    if (m_viewMatrixUpdate)
    {
        glLoadMatrixf(m_viewMatrix.matrix);
        m_viewMatrixUpdate = false;
    }

    if (m_modelMatrixUpdate)
    {
        glMultMatrixf(m_modelMatrix.matrix);
        m_modelMatrixUpdate = false;
    }

    IVertexBuffer* vertexBuffer = renderable->GetVertexBuffer();

    if (vertexBuffer)
    {
        if (m_vboSupport)
        {
            glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer->GetBufferId());
        }
        else
        {
            // TODO - implement code for non vbo support
        }

        glVertexPointer(3, 
            opengl::utility::ConvertToOpenglVertexBufferParamSizeType(VertexParamSizeType::Float3), 
            vertexBuffer->GetStride(), 
            BUFFER_OFFSET(vertexBuffer->GetOffset(VertexParamType::Position)));
        glEnableClientState(GL_VERTEX_ARRAY);

        glColorPointer(4, 
            opengl::utility::ConvertToOpenglVertexBufferParamSizeType(VertexParamSizeType::Float4), 
            vertexBuffer->GetStride(), 
            BUFFER_OFFSET(vertexBuffer->GetOffset(VertexParamType::Color)));
        glEnableClientState(GL_COLOR_ARRAY);

        glTexCoordPointer(2, 
            opengl::utility::ConvertToOpenglVertexBufferParamSizeType(VertexParamSizeType::Float2), 
            vertexBuffer->GetStride(), 
            BUFFER_OFFSET(vertexBuffer->GetOffset(VertexParamType::Texture))); 
        glEnableClientState(GL_TEXTURE_COORD_ARRAY);

        glDrawArrays(GL_TRIANGLES, 0, vertexBuffer->GetNumVertices());

        // disable client state
        glDisableClientState(GL_VERTEX_ARRAY);
        glDisableClientState(GL_COLOR_ARRAY);
        glDisableClientState(GL_TEXTURE_COORD_ARRAY);

        if (m_vboSupport)
        {
            // unbind the buffer
            glBindBuffer(GL_ARRAY_BUFFER, 0);
        }
    }

    //DrawBox();
}