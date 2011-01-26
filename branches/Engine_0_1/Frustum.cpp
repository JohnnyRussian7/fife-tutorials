/**********************************************************************
*	Filename: Frustum.cpp
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
#include "PrecompiledIncludes.h"

#include "Frustum.h"
#include "AxisAlignedBoundingBox.h"
#include "Sphere.h"
#include "MathUtil.h"
#include "Matrix4.h"
#include "Plane.h"
#include "Vector3.h"

namespace
{
    const float DefaultAspectRatio = 640.f/480.f;
    const float DefaultNearDistance = 1.f;
    const float DefaultFarDistance = 10000.f;
}

Frustum::Frustum()
: m_sides(FrustumPlanes::Max, Plane()), m_fov(Pi/4.f), m_aspectRatio(DefaultAspectRatio), 
m_nearDistance(DefaultNearDistance), m_farDistance(DefaultFarDistance)
{
    // mark updated needed
    MarkDirty();
}

void Frustum::SetFov(float fov)
{
    m_fov = fov;
    MarkDirty();
}

float Frustum::GetFov() const
{
    return m_fov;
}

void Frustum::SetAspectRatio(float aspect)
{
    m_aspectRatio = aspect;
    MarkDirty();
}

float Frustum::GetAspectRatio() const
{
    return m_aspectRatio;
}

void Frustum::SetNearDistance(float nearDistance)
{
    m_nearDistance = nearDistance;
    MarkDirty();
}

float Frustum::GetNearDistance() const
{
    return m_nearDistance;
}

void Frustum::SetFarDistance(float farDistance)
{
    m_farDistance = farDistance;
    MarkDirty();
}

float Frustum::GetFarDistance() const
{
    return m_farDistance;
}

const Plane& Frustum::GetPlane(FrustumPlanes::Enum plane) const
{
    if (plane > FrustumPlanes::Invalid && plane < FrustumPlanes::Max)
    {
        return m_sides[plane];
    }

    return m_sides[0];
}

bool Frustum::IsVisible(const Sphere& sphere)
{
    // TODO - may need to check if planes are up to date
    //        before performing visibility check

    for (PlaneContainer::size_type i=0; i < m_sides.size(); ++i)
    {
        if (m_sides[i].GetDistance(sphere.GetCenter()) < - sphere.GetRadius())
        {
            return false;
        }
    }

    return true;
}

bool Frustum::IsVisible(const AxisAlignedBoundingBox& aabb)
{
    // TODO - may need to check if planes are up to date
    //        before performing visibility check

    for (PlaneContainer::size_type i=0; i < m_sides.size(); ++i)
    {
        if (m_sides[i].GetSide(aabb) == PlaneSide::Back)
        {
            return false;
        }
    }

    return true;
}

void Frustum::Update(const Matrix4& m)
{
    // exit early if nothing needs to be done
    if (!m_needsUpdate)
    {
        return;
    }

    Vector3 leftNormal(m.matrix[3] + m.matrix[0], 
                        m.matrix[7] + m.matrix[4], 
                        m.matrix[11] + m.matrix[8]);

    Vector3 rightNormal(m.matrix[3] - m.matrix[0],
                        m.matrix[7] - m.matrix[4],
                        m.matrix[11] - m.matrix[8]);

    Vector3 bottomNormal(m.matrix[3] + m.matrix[1],
                            m.matrix[7] + m.matrix[5],
                            m.matrix[11] + m.matrix[9]);

    Vector3 topNormal(m.matrix[3] - m.matrix[1],
                        m.matrix[7] - m.matrix[5],
                        m.matrix[11] - m.matrix[9]);

    Vector3 nearNormal(m.matrix[3] + m.matrix[2],
                        m.matrix[7] + m.matrix[6],
                        m.matrix[11] + m.matrix[10]);

    Vector3 farNormal(m.matrix[3] - m.matrix[2],
                        m.matrix[7] - m.matrix[6],
                        m.matrix[11] - m.matrix[10]);

    m_sides[FrustumPlanes::Left] = Plane(leftNormal, m.matrix[15] + m.matrix[12]);
    m_sides[FrustumPlanes::Right] = Plane(rightNormal, m.matrix[15] - m.matrix[12]);
    m_sides[FrustumPlanes::Bottom] = Plane(bottomNormal, m.matrix[15] + m.matrix[13]);
    m_sides[FrustumPlanes::Top] = Plane(topNormal, m.matrix[15] - m.matrix[13]);
    m_sides[FrustumPlanes::Near] = Plane(nearNormal, m.matrix[15] + m.matrix[14]);
    m_sides[FrustumPlanes::Far] = Plane(farNormal, m.matrix[15] - m.matrix[14]);

    // normalize all planes
    for (PlaneContainer::size_type i=0; i < m_sides.size(); ++i)
    {
        m_sides[i] = Normalize(m_sides[i]);
    }

    // reset dirty flag
    ResetDirty();
}

void Frustum::MarkDirty()
{
    m_needsUpdate = true;
}

void Frustum::ResetDirty()
{
    m_needsUpdate = false;
}

// TODO - need to implement
void Frustum::CalculateProjection()
{
    float tangent = std::tan(m_fov * 0.5f);
    float nearHeight = m_nearDistance * tangent;
    float nearWidth = nearHeight * m_aspectRatio;
    float farHeight = m_farDistance * tangent;
    float farWidth = farHeight * m_aspectRatio;
}