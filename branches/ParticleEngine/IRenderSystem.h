
#ifndef RENDER_SYSTEM_H_
#define RENDER_SYSTEM_H_

#include "RenderSystemTypes.h"

class IRenderSystem
{
public:
	virtual ~IRenderSystem() = 0 { };

	virtual RenderSystemType::Enum GetRenderSystemType() const = 0;
};

IRenderSystem* CreateRenderSystem(RenderSystemType::Enum type);
#endif
