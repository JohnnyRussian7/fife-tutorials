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

#include "Plane.h"

Plane::Plane()
: normal(Vector3::Zero()), distance(0)
{

}

Plane::Plane(const Vector3& n, const float d)
: normal(n), distance(d)
{

}

Plane::Plane(const Vector3& norm, Vector3& point)
: normal(norm)
{
    distance = -Dot(normal, point);
}

Plane::Plane(const Vector3& point0, const Vector3& point1, const Vector3& point2)
{
    Vector3 edge0 = point1 - point0;
    Vector3 edge1 = point2 - point0;

    normal = Normalize(Cross(edge0, edge1));
    distance = -Dot(normal, point0);
}

Plane Normalize(const Plane& p)
{
    const float tolerance = 0.000001f;

    float length = Magnitude(p.normal);

    if (length < tolerance)
    {
        return p;
    }

    float inverseLength = 1.f/length;

    return Plane(p.normal*inverseLength, p.distance*inverseLength);
}