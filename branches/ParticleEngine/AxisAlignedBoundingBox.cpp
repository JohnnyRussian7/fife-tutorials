
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