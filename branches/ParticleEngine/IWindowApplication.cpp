
#include "IWindowSystem.h"
#include "Win32WindowSystem.h"

IWindowSystem* CreateWindowSystem(const WindowSettings& settings)
{
	IWindowSystem* application = NULL;

	switch (settings.applicationType)
	{
	case WindowSystemType::Win32:
		application = new Win32WindowSystem(settings);
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

	return application;
}