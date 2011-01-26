/**********************************************************************
*	Filename: IWindowSystem.cpp
*	
*	Copyright (C) 2011, FIFE team
*	http://www.fifengine.net
*
*	This file is part of FIFE.
*
*	FIFE is free software: you can redistribute it and/or modify it
*	under the terms of the GNU Lesser General Public License as
*	published by the Free Software Foundation, either version 3 of
*	the License, or any later version.
*
*	FIFE is distributed in the hope that it will be useful,
*	but WITHOUT ANY WARRANTY; without even the implied warranty of
*	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* 	GNU Lesser General Public License for more details.
*
*	You should have received a copy of the GNU Lesser General Public
*	License along with FIFE. If not, see http://www.gnu.org/licenses/.
***********************************************************************/
#include "PrecompiledIncludes.h"

#include "IWindowSystem.h"
#include "win32/Win32WindowSystem.h"

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