/**********************************************************************
*	Filename: AlphaTestMode.cpp
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

#include "AlphaTestMode.h"
#include "../math/MathUtil.h"

AlphaTestMode::AlphaTestMode()
: m_enabled(false), m_alphaTestType(AlphaTestType::Always), m_value(0.f)
{

}

void AlphaTestMode::SetEnabled(bool enabled)
{
    m_enabled = enabled;
}

void AlphaTestMode::SetType(AlphaTestType::Enum alphaTestType)
{
    m_alphaTestType = alphaTestType;
}

void AlphaTestMode::SetValue(float value)
{
    m_value = value;
}

bool AlphaTestMode::IsEnabled() const
{
    return m_enabled;
}

AlphaTestType::Enum AlphaTestMode::GetType() const
{
    return m_alphaTestType;
}

float AlphaTestMode::GetValue() const
{
    return m_value;
}

bool operator==(const AlphaTestMode& lhs, const AlphaTestMode& rhs)
{
    return (lhs.IsEnabled() == rhs.IsEnabled() &&
            lhs.GetType() == rhs.GetType() &&
            IsEqual(lhs.GetValue(), rhs.GetValue()));
}

bool operator!=(const AlphaTestMode& lhs, const AlphaTestMode& rhs)
{
    return (lhs.IsEnabled() != rhs.IsEnabled() ||
            lhs.GetType() != rhs.GetType() ||
            !IsEqual(lhs.GetValue(), rhs.GetValue()));
}