/**********************************************************************
*	Filename: Sphere.cpp
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

#include "Sphere.h"

Sphere::Sphere()
: m_center(Vector3::Zero()), m_radius(1.f)
{

}

Sphere::Sphere(const Vector3& center, float radius)
: m_center(center), m_radius(radius)
{

}

void Sphere::SetCenter(const Vector3& center)
{
    m_center = center;
}

const Vector3& Sphere::GetCenter() const
{
    return m_center;
}

void Sphere::SetRadius(float radius)
{
    m_radius = radius;
}

float Sphere::GetRadius() const
{
    return m_radius;
}