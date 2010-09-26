
#include <sstream>

#include "stdint.h"
#include "Camera.h"
#include "MathUtil.h"

namespace
{
    std::string CreateUniqueCameraName()
    {
        // automated counting for name generation, in case the user doesn't provide a name
        static uint32_t uniqueNumber = 0;
        static std::string baseName = "Camera";

        std::ostringstream oss;
        oss << baseName << "_" << uniqueNumber;

        const std::string name = oss.str();
        ++uniqueNumber;

        return name;
    }
}

Camera::Camera(const char* name, const Vector3& position, const Quaternion& orientation)
: m_position(position), m_orientation(orientation), m_viewMatrix(Matrix4::Identity()), 
  m_needsUpdate(true)
{
    if (name)
    {
        m_name = std::string(name);
    }
    else
    {
        m_name = CreateUniqueCameraName();
    }
}

const char* Camera::GetName() const
{
    return m_name.c_str();
}

const Vector3& Camera::GetPosition() const
{
    return m_position;
}

const Quaternion& Camera::GetOrientation() const
{
    return m_orientation;
}

const Matrix4& Camera::GetViewMatrix()
{
	// update the view matrix
	UpdateView();

	return m_viewMatrix;
}

const Frustum& Camera::GetFrustum()
{
    // update view if needed
    UpdateView();

    return m_frustum;
}

Vector3 Camera::GetUp() const
{
	return m_orientation * Vector3::UnitY();
}

Vector3 Camera::GetRight() const
{
	return m_orientation * Vector3::UnitX();
}

Vector3 Camera::GetLookAt() const
{
	// always looking down the -z axis
	return m_orientation * -Vector3::UnitZ();
}

void Camera::Translate(const Vector3& translation)
{
	// translate in world space
	m_position += translation;

	// TODO - implement translate in local space, using algorithm below 
	//m_position += m_orientation * translation;

    MarkDirty();
}

void Camera::LookAt(const Vector3& target)
{
	Vector3 direction = -(target - m_position);

	// nothing to do if direction is zero vector
	if (direction == Vector3::Zero())
	{
		return;
	}

	// always looking down negative z-axis so need to 
	// negate and normalize direction vector
	Vector3 normDirection = Normalize(-direction);

	// get z-axis of current rotation
	Vector3 zAxis = ZAxis(m_orientation);

	// get shortest rotation arc to direction
	Quaternion rotation = GetRotationTo(zAxis, normDirection);

	m_orientation = rotation * m_orientation;

    MarkDirty();
}

void Camera::Pitch(float angle)
{
	Vector3 xaxis = m_orientation * Vector3::UnitX();
	Rotate(xaxis, angle);

    MarkDirty();
}

void Camera::Yaw(float angle)
{
	Vector3 yaxis = m_orientation * Vector3::UnitY();
	Rotate(yaxis, angle);

    MarkDirty();
}

void Camera::Roll(float angle)
{
	Vector3 zaxis = m_orientation * Vector3::UnitZ();
	Rotate(zaxis, angle);

    MarkDirty();
}

void Camera::Rotate(const Vector3& axis, float angle)
{
	Quaternion rotQ = FromAxisAngle(axis, angle);
	Rotate(rotQ);

    MarkDirty();
}

void Camera::Rotate(const Quaternion& rotation)
{
	Quaternion normQ = Normalize(rotation);
	m_orientation = normQ * m_orientation;

    MarkDirty();
}

void Camera::UpdateView()
{
    if (!m_needsUpdate)
    {
        return;
    }

	// create matrix for position
	Matrix4 posMatrix = Matrix4::Identity();
	posMatrix.matrix[12] = -m_position.x;
	posMatrix.matrix[13] = -m_position.y;
	posMatrix.matrix[14] = -m_position.z;

	// create rotation matrix
	Matrix4 conjRotMatrix = ToMatrix(Conjugate(m_orientation));

	m_viewMatrix = posMatrix * conjRotMatrix;

    // update frustum
    m_frustum.Update(m_viewMatrix);

    // reset dirty flag
    ResetDirty();
}

void Camera::MarkDirty()
{
    m_needsUpdate = true;
}

void Camera::ResetDirty()
{
    m_needsUpdate = false;
}
