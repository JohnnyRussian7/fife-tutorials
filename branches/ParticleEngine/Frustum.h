/**********************************************************************
*	Filename: Frustrum.h
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
#ifndef FRUSTRUM_H_
#define FRUSTRUM_H_

#include <vector>

#include "Plane.h"

class AxisAlignedBoundingBox;
class Sphere;

struct FrustrumPlanes
{
    enum Enum
    {
        Near = 0,
        Far,
        Left,
        Right,
        Top,
        Bottom
    };
};

class Frustrum
{
public:
    Frustrum();

    void SetFov(float fov);
    float GetFov() const;
    
    void SetAspectRatio(float aspect);
    float GetAspectRatio() const;

    void SetNearDistance(float nearDistance);
    float GetNearDistance() const;

    void SetFarDistance(float farDistance);
    float GetFarDistance() const;
    
    const Plane& GetPlane(FrustrumPlanes::Enum plane) const;

    bool IsVisible(const AxisAlignedBoundingBox& aabb) const;
    bool IsVisible(const Sphere& sphere) const;

    void Update();

private:
    void MarkDirty();

private:
    std::vector<Plane> m_sides;
    float m_fov;
    float m_aspectRatio;
    float m_nearDistance;
    float m_farDistance;
    bool m_needsUpdate;
};

#endif
