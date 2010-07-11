
#include "OpenglRenderer.h"

OpenglRenderer::OpenglRenderer()
: m_modelMatrix(Matrix4::Identity()), m_viewMatrix(Matrix4::Identity()),
  m_projectionMatrix(Matrix4::Identity()), m_activeTexture(0)
{

}

OpenglRenderer::~OpenglRenderer()
{

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