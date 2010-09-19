/**********************************************************************
*	Filename: Frustrum.cpp
*	
*	Copyright (C) 2010, FIFE team
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

#include "Frustrum.h"
#include "AxisAlignedBoundingBox.h"
#include "Sphere.h"
#include "MathUtil.h"

namespace
{
    const float DefaultAspectRatio = 640.f/480.f;
    const float DefaultNearDistance = 1.f;
    const float DefaultFarDistance = 10000.f;
}

Frustrum::Frustrum()
: m_fov(Pi/4.f), m_aspectRatio(DefaultAspectRatio), 
m_nearDistance(DefaultNearDistance), m_farDistance(DefaultFarDistance), m_needsUpdate(true)
{
    Update();
}

void Frustrum::SetFov(float fov)
{
    m_fov = fov;
    MarkDirty();
}

float Frustrum::GetFov() const
{
    return m_fov;
}

void Frustrum::SetAspectRatio(float aspect)
{
    m_aspectRatio = aspect;
    MarkDirty();
}

float Frustrum::GetAspectRatio() const
{
    return m_aspectRatio;
}

void Frustrum::SetNearDistance(float nearDistance)
{
    m_nearDistance = nearDistance;
    MarkDirty();
}

float Frustrum::GetNearDistance() const
{
    return m_nearDistance;
}

void Frustrum::SetFarDistance(float farDistance)
{
    m_farDistance = farDistance;
    MarkDirty();
}

float Frustrum::GetFarDistance() const
{
    return m_farDistance;
}

void Frustrum::Update()
{
    // TODO - need to implement
}

void Frustrum::MarkDirty()
{
    m_needsUpdate = true;
}
