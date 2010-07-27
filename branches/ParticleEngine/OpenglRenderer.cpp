
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

	// enable scissor testing to clip against viewport
	glScissor(m_viewport.GetLeft(), m_viewport.GetTop(), m_viewport.GetWidth(), m_viewport.GetHeight());
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