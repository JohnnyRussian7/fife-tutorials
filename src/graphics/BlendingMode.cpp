/**********************************************************************
*	Filename: BlendingMode.cpp
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

#include "BlendingMode.h"

BlendingMode::BlendingMode()
: m_enabled(false), m_srcBlendMode(SrcBlendMode::One), 
m_destBlendMode(DestBlendMode::Zero), m_constantColor(Color::Black())
{

}

void BlendingMode::SetEnabled(bool enabled)
{
    m_enabled = enabled;
}

void BlendingMode::SetSrcBlendMode(SrcBlendMode::Enum blendMode)
{
    m_srcBlendMode = blendMode;
}

void BlendingMode::SetDestBlendMode(DestBlendMode::Enum blendMode)
{
    m_destBlendMode = blendMode;
}

void BlendingMode::SetConstantColor(const Color& color)
{
    m_constantColor = color;
}

bool BlendingMode::IsEnabled() const
{
    return m_enabled;
}

SrcBlendMode::Enum BlendingMode::GetSrcBlendMode() const
{
    return m_srcBlendMode;
}

DestBlendMode::Enum BlendingMode::GetDestBlendMode() const
{
    return m_destBlendMode;
}

Color BlendingMode::GetConstantColor() const
{
    return m_constantColor;
}

bool operator==(const BlendingMode& lhs, const BlendingMode& rhs)
{
    return (lhs.IsEnabled() == rhs.IsEnabled() &&
            lhs.GetSrcBlendMode() == rhs.GetSrcBlendMode() &&
            lhs.GetDestBlendMode() == rhs.GetDestBlendMode() &&
            lhs.GetConstantColor() == rhs.GetConstantColor());
}

bool operator!=(const BlendingMode& lhs, const BlendingMode& rhs)
{
    return (lhs.IsEnabled() != rhs.IsEnabled() ||
        lhs.GetSrcBlendMode() != rhs.GetSrcBlendMode() ||
        lhs.GetDestBlendMode() != rhs.GetDestBlendMode() ||
        lhs.GetConstantColor() != rhs.GetConstantColor());
}
