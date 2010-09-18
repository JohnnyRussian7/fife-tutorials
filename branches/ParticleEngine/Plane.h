/**********************************************************************
*	Filename: Plane.h
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
#ifndef PLANE_H_
#define PLANE_H_

#include "Vector3.h"

class Plane
{
public:
    Plane();
    Plane(const Vector3& n, const float d);
    Plane(const Vector3& norm, Vector3& point);
    Plane(const Vector3& point0, const Vector3& point1, const Vector3& point2);

    Vector3 normal;
    float distance;
};

Plane Normalize(const Plane& p);

#endif