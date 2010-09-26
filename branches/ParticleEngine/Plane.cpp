/**********************************************************************
*	Filename: Plane.cpp
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

#include <cmath>

#include "Plane.h"
#include "AxisAlignedBoundingBox.h"

Plane::Plane()
: m_normal(Vector3::Zero()), m_distance(0)
{

}

Plane::Plane(const Vector3& n, const float d)
: m_normal(n), m_distance(d)
{

}

Plane::Plane(const Vector3& norm, Vector3& point)
: m_normal(norm)
{
    m_distance = -Dot(m_normal, point);
}

Plane::Plane(const Vector3& point0, const Vector3& point1, const Vector3& point2)
{
    Vector3 edge0 = point1 - point0;
    Vector3 edge1 = point2 - point0;

    m_normal = Normalize(Cross(edge0, edge1));
    m_distance = -Dot(m_normal, point0);
}

float Plane::GetDistance(const Vector3& point) const
{
    return (Dot(m_normal, point) + m_distance);   
}

PlaneSide::Enum Plane::GetSide(const Vector3& point) const
{
    float distance = GetDistance(point);
    if (distance < 0.f)
    {
        return PlaneSide::Back;
    }
    else if (distance > 0.f)
    {
        return PlaneSide::Front;
    }

    return PlaneSide::Intersects;
}

PlaneSide::Enum Plane::GetSide(const AxisAlignedBoundingBox& aabb) const
{
    float distance = GetDistance(aabb.GetCenter());
    Vector3& halfSize = aabb.GetExtent() * 0.5f;

    float absNorm = std::abs(halfSize.x*halfSize.x) + std::abs(halfSize.y*halfSize.y) + std::abs(halfSize.z*halfSize.z);

    if (distance < -absNorm)
    {
        return PlaneSide::Back;
    }
    else if (distance > absNorm)
    {
        return PlaneSide::Front;
    }

    return PlaneSide::Intersects;
}

Plane Normalize(const Plane& p)
{
    const float tolerance = 0.000001f;

    float length = Magnitude(p.m_normal);

    if (length < tolerance)
    {
        return p;
    }

    float inverseLength = 1.f/length;

    return Plane(p.m_normal*inverseLength, p.m_distance*inverseLength);
}