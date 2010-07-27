
#include "IWindowSystem.h"
#include "Win32WindowSystem.h"

IWindowSystem* CreateWindowSystem(const WindowSystemSettings& settings)
{
	IWindowSystem* windowSystem = NULL;

	switch (settings.windowSystemType)
	{
	case WindowSystemType::Win32:
		windowSystem = new Win32WindowSystem(settings);
		break;
	case WindowSystemType::MacOsx:
		break;
	case WindowSystemType::Linux:
		break;
	case WindowSystemType::Sdl:
		break;
	default:
		break;
	}

	return windowSystem;
}