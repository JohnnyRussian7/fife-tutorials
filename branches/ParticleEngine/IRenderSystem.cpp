
#include "IRenderSystem.h"
#include "OpenglRenderer.h"

IRenderSystem* CreateRenderSystem(const RenderSystemSettings& settings)
{
	IRenderSystem* renderSystem = 0;

	switch (settings.renderSystemType)
	{
	case RenderSystemType::Opengl:
		renderSystem = new OpenglRenderer(settings);
		break;

	case RenderSystemType::Sdl:
		break;

	default:
		break;
	}

	return renderSystem;
}