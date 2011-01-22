/**********************************************************************
*	Filename: AxisAlignedBoundingBox.cpp
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

#include "AxisAlignedBoundingBox.h"

AxisAlignedBoundingBox::AxisAlignedBoundingBox()
: min(-1, -1, -1), max(1, 1, 1)
{
	// calculate size
	size = max - min;

	// calculate center
	center = size/2;
}

AxisAlignedBoundingBox::AxisAlignedBoundingBox(const Vector3& center, const Vector3& size)
: center(center), size(size)
{
	// calculate half size to get min and max
	Vector3 halfSize = size/2;

	// set min/max based on half size
	min = center - halfSize;
	max = center + halfSize;
}

AxisAlignedBoundingBox::AxisAlignedBoundingBox(const AxisAlignedBoundingBox& rhs)
: center(rhs.center), size(rhs.size), min(rhs.min), max(rhs.max)
{

}

void AxisAlignedBoundingBox::SetMinMax(const Vector3& newMin, const Vector3& newMax)
{
	min = newMin;
	max = newMax;

	// calculate size
	size = max - min;

	// calculate center
	center = size/2;
}

const Vector3& AxisAlignedBoundingBox::GetCenter() const
{
	return center;
}

const Vector3& AxisAlignedBoundingBox::GetMin() const
{
	return min;
}

const Vector3& AxisAlignedBoundingBox::GetMax() const
{
	return max;
}

const Vector3& AxisAlignedBoundingBox::GetExtent() const
{
	return size;
};

bool AxisAlignedBoundingBox::Contains(const Vector3& point)
{
	return (point.x >= min.x && point.x <= max.x
			&& point.y >= min.y && point.y <= max.y
			&& point.z >= min.z && point.z <= max.z);
}	