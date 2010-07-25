
#include "IRenderSystem.h"
#include "OpenglRenderer.h"

IRenderSystem* CreateRenderSystem(RenderSystemType::Enum type)
{
	IRenderSystem* renderSystem = 0;

	switch (type)
	{
	case RenderSystemType::Opengl:
		renderSystem = new OpenglRenderer();
		break;

	case RenderSystemType::Sdl:
		break;

	default:
		break;
	}

	return renderSystem;
}