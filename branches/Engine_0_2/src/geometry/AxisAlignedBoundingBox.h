/**********************************************************************
*	Filename: AxisAlignedBoundingBox.h
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
#ifndef AXISALIGNEDBOUNDINGBOX_H_
#define AXISALIGNEDBOUNDINGBOX_H_

#include "../math/Vector3.h"

class AxisAlignedBoundingBox
{
public:
	AxisAlignedBoundingBox();
	AxisAlignedBoundingBox(const Vector3& center, const Vector3& size);
	AxisAlignedBoundingBox(const AxisAlignedBoundingBox& rhs);

	void SetMinMax(const Vector3& min, const Vector3& max);
	const Vector3& GetCenter() const;
	const Vector3& GetMin() const;
	const Vector3& GetMax() const;
	const Vector3& GetExtent() const;

	bool Contains(const Vector3& point);

private:
	Vector3 center;
	Vector3 size;
	Vector3 min;
	Vector3 max;
};

#endif
