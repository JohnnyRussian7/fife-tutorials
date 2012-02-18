/**********************************************************************
 *	Filename: DepthBufferWriteMode.h
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

#include "DepthBufferWriteMode.h"

DepthBufferWriteMode::DepthBufferWriteMode()
: m_enabled(true)
{
    
}

void DepthBufferWriteMode::SetEnabled(bool enabled)
{
    m_enabled = enabled;
}

bool DepthBufferWriteMode::IsEnabled() const
{
    return m_enabled;
}

bool operator==(const DepthBufferWriteMode& lhs, const DepthBufferWriteMode& rhs)
{
    return (lhs.IsEnabled() == rhs.IsEnabled());
}

bool operator!=(const DepthBufferWriteMode& lhs, const DepthBufferWriteMode& rhs)
{
    return (lhs.IsEnabled() != rhs.IsEnabled());
}

