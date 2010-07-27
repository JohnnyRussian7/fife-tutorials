
#ifndef OPENGL_RENDERER_H_
#define OPENGL_RENDERER_H_

#include "IRenderSystem.h"

#include "RendererEnums.h"
#include "Matrix.h"
#include "Opengltexture.h"
#include "Viewport.h"

class OpenglRenderer : public IRenderSystem
{
public:
	OpenglRenderer(const RenderSystemSettings& settings);
	~OpenglRenderer();

	virtual RenderSystemType::Enum GetRenderSystemType() const;
	virtual void SetViewPort(const Viewport& viewport);

	void SetTransform(TransformType::Enum type, const Matrix4& mat);

	void EnableTextures(TextureType::Enum type);
	void DisableTextures(TextureType::Enum type);

	void SetActiveTexture(OpenglTexture* texture);

private:
	void ClearBuffers();

private:
    RenderSystemSettings m_settings;

	Viewport m_viewport;
	Matrix4 m_modelMatrix;
	Matrix4 m_viewMatrix;
	Matrix4 m_projectionMatrix;

	OpenglTexture* m_activeTexture;
};

#endif
