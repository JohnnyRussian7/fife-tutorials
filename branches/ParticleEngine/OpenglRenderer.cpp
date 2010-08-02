
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <windows.h>
#include <gl/glu.h>
#include <gl/gl.h>

#include "OpenglRenderer.h"

OpenglRenderer::OpenglRenderer(const RenderSystemSettings& settings)
: m_settings(settings), m_viewport(Viewport()),
  m_modelMatrix(Matrix4::Identity()), m_viewMatrix(Matrix4::Identity()),
  m_projectionMatrix(Matrix4::Identity()), m_activeTexture(0)
{

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

	// TODO - this should be doen elsewhere
	// setup the frustrum
	int aspectRatio = viewport.GetWidth() / viewport.GetHeight();
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-0.5, 0.5, -aspectRatio*0.5, aspectRatio*0.5, 1, 5000);

	// enable scissor testing to clip against viewport
	glScissor(m_viewport.GetLeft(), m_viewport.GetTop(), m_viewport.GetWidth(), m_viewport.GetHeight());

	glMatrixMode(GL_MODELVIEW);
}

void OpenglRenderer::SetTransform(TransformType::Enum type, const Matrix4& mat)
{
	switch (type)
	{
		case TransformType::Model:
		{

		}
		break;
		case TransformType::View:
		{

		}
		break;
		case TransformType::Projection:
		{

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
	//glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0, 0, -10);

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