/**********************************************************************
*	Filename: Sphere.h
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
#ifndef SPHERE_H_
#define SPHERE_H_

#include "Vector3.h"

class Sphere
{
public:
    Sphere();
    Sphere(const Vector3& center, float radius);

    void SetCenter(const Vector3& center);
    const Vector3& GetCenter() const;

    void SetRadius(float radius);
    float GetRadius() const;

private:
    Vector3 m_center;
    float m_radius;
};

#endif
