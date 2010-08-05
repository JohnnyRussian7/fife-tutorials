
#ifndef IRENDER_SYSTEM_H_
#define IRENDER_SYSTEM_H_

#include "RenderSystemTypes.h"
#include "RendererEnums.h"

class Viewport;
struct Matrix4;

struct RenderSystemSettings
{
    RenderSystemSettings()
    : renderSystemType(RenderSystemType::Opengl)
    {

    }

    RenderSystemType::Enum renderSystemType;


};

class IRenderSystem
{
public:
	virtual ~IRenderSystem() = 0 { };

	virtual RenderSystemType::Enum GetRenderSystemType() const = 0;
	virtual void SetViewPort(const Viewport& viewport) = 0;
    virtual void SetTransform(TransformType::Enum type, const Matrix4& mat) = 0;

	virtual void Render() = 0;
};

IRenderSystem* CreateRenderSystem(const RenderSystemSettings& settings);

#endif
