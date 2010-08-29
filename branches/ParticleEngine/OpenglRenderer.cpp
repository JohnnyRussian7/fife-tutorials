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

void OpenglRenderer::Render()
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

    if (m_viewMatrixUpdate || m_modelMatrixUpdate)
    {
        glLoadMatrixf(m_viewMatrix.matrix);
        glMultMatrixf(m_modelMatrix.matrix);
    }

    // draw all renderables


    DrawBox();
}