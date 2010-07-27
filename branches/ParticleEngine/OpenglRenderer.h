
#ifndef OPENGL_RENDERER_H_
#define OPENGL_RENDERER_H_

#include "IRenderSystem.h"

#include "RendererEnums.h"
#include "Matrix.h"
#include "Opengltexture.h"

class OpenglRenderer : public IRenderSystem
{
public:
	OpenglRenderer(const RenderSystemSettings& settings);
	~OpenglRenderer();

	RenderSystemType::Enum GetRenderSystemType() const;

	void SetTransform(TransformType::Enum type, const Matrix4& mat);

	void EnableTextures(TextureType::Enum type);
	void DisableTextures(TextureType::Enum type);

	void SetActiveTexture(OpenglTexture* texture);

private:
	void ClearBuffers();

private:
    RenderSystemSettings m_settings;

	Matrix4 m_modelMatrix;
	Matrix4 m_viewMatrix;
	Matrix4 m_projectionMatrix;

	OpenglTexture* m_activeTexture;
};

#endif
