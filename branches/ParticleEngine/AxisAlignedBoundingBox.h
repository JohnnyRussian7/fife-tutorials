
#ifndef AXIS_ALIGNED_BOUNDING_BOX_H_
#define AXIS_ALIGNED_BOUNDING_BOX_H_

#include "Vector.h"

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
