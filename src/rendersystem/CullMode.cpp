/**********************************************************************
*	Filename: CullMode.cpp
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

#include "CullMode.h"

CullMode::CullMode()
: m_enabled(false), m_cullType(CullType::Back)
{

}

void CullMode::SetEnabled(bool enabled)
{
    m_enabled = enabled;
}

bool CullMode::IsEnabled() const
{
    return m_enabled;
}

void CullMode::SetCullType(CullType::Enum cullType)
{
    m_cullType = cullType;
}

CullType::Enum CullMode::GetCullType() const
{
    return m_cullType;
}

bool operator==(const CullMode& lhs, const CullMode& rhs)
{
    return (lhs.IsEnabled() == rhs.IsEnabled() &&
            lhs.GetCullType() == rhs.GetCullType());
}

bool operator!=(const CullMode& lhs, const CullMode& rhs)
{
    return (lhs.IsEnabled() != rhs.IsEnabled() ||
            lhs.GetCullType() != rhs.GetCullType());
}