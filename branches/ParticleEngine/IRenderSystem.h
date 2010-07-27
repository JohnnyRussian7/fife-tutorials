
#ifndef IRENDER_SYSTEM_H_
#define IRENDER_SYSTEM_H_

#include "RenderSystemTypes.h"

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
};

IRenderSystem* CreateRenderSystem(const RenderSystemSettings& settings);
#endif
