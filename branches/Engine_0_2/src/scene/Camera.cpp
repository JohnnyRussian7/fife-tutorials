/**********************************************************************
*	Filename: Camera.cpp
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

#include "Camera.h"
#include "SceneNode.h"
#include "../math/MathUtil.h"

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
: m_orientation(orientation), m_relativeOrientation(Quaternion::Identity()), 
  m_relativePosition(Vector3::Zero()), m_viewMatrix(Matrix4::Identity()), 
  m_needsUpdate(true), m_fixedYaw(false), m_fixedYawAxis(Vector3::UnitY())
{
    if (name)
    {
        m_name = std::string(name);
    }
    else
    {
        m_name = CreateUniqueCameraName();
    }

    m_position = position;
}

void Camera::SetPosition(float x, float y, float z)
{
    SetPosition(Vector3(x,y,z));
}

void Camera::SetPosition(const Vector3& position)
{
    // call base class implementation first
    Entity::SetPosition(position);

    MarkDirty();
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

void Camera::Translate(float x, float y, float z)
{
    Translate(Vector3(x, y, z));
}

void Camera::Translate(const Vector3& translation)
{
	// translate in world space
	//m_position += translation;

	// translate in local space 
	m_position += m_orientation * translation;

    MarkDirty();
}

void Camera::LookAt(float x, float y, float z)
{
    LookAt(Vector3(x, y, z));
}

void Camera::LookAt(const Vector3& target)
{
    // always looking down negative z-axis so negate direction
	Vector3 direction = -(target - m_position);

	// nothing to do if direction is zero vector
	if (direction == Vector3::Zero())
	{
		return;
	}

    // normalize the direction vector
    Vector3 normDirection = Normalize(direction);

    Quaternion orientation;

    if (m_fixedYaw)
    {
        Vector3 right = Normalize(Cross(m_fixedYawAxis, normDirection));
        Vector3 up = Normalize(Cross(normDirection, right));

        orientation = FromAxes(right, up, normDirection);
    }
    else
    {
	    // get z-axis of current rotation
	    Vector3 zAxis = ZAxis(m_orientation);

	    // get shortest rotation arc to direction
	    Quaternion rotation = GetRotationTo(zAxis, normDirection);

	    orientation = rotation * m_orientation;
    }

    if (m_parent)
    {
        // calculate orientation with respect to parent
        m_orientation = Inverse(m_parent->GetRelativeOrientation()) * orientation;
    }
    else
    {
        // no parent just set orientation directly
        m_orientation = orientation;
    }

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
    Vector3 yAxis;

    if  (m_fixedYaw)
    {
        yAxis = m_fixedYawAxis;
    }
    else
    {
        yAxis = m_orientation * Vector3::UnitY();
    }

    Rotate(yAxis, angle);

    MarkDirty();
}

void Camera::Roll(float angle)
{
	Vector3 zaxis = m_orientation * Vector3::UnitZ();
	Rotate(zaxis, angle);

    MarkDirty();
}

bool Camera::IsYawAxisFixed() const
{
    return m_fixedYaw;
}

const Vector3& Camera::GetFixedYawAxis() const
{
    return m_fixedYawAxis;
}

void Camera::SetFixedYawAxis(bool fixedYaw, const Vector3& axis)
{
    m_fixedYaw = fixedYaw;
    m_fixedYawAxis = axis;
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
    if (!IsDirty())
    {
        return;
    }

	// create matrix for position
// 	Matrix4 posMatrix = Matrix4::Identity();
// 	posMatrix[12] = -m_position.x;
// 	posMatrix[13] = -m_position.y;
// 	posMatrix[14] = -m_position.z;
// 
// 	// create rotation matrix
// 	Matrix4 conjRotMatrix = ToRotationMatrix(Conjugate(m_orientation));
//  
//      m_viewMatrix = posMatrix * conjRotMatrix;

/*
// The Following rotates the objects and not the camera
    Matrix4 cameraRotationMatrix = Transpose(ToRotationMatrix(m_orientation));
    Matrix4 cameraPositionMatrix = Matrix4::Identity();
    cameraPositionMatrix[12] = -m_position.x;
    cameraPositionMatrix[13] = -m_position.y;
    cameraPositionMatrix[14] = -m_position.z;
    m_viewMatrix = cameraPositionMatrix * cameraRotationMatrix;
*/
    
    // this causes the camera to rotate about the origin
    Matrix4 rotMatrix = ToRotationMatrix(m_relativeOrientation);
    TransposeRef(rotMatrix);
    
    std::cout << "rotation matrix\n" << rotMatrix << std::endl;

    Matrix4 temp = -rotMatrix;
    temp[3] = 0;
    temp[7] = 0;
    temp[11] = 0;
    temp[15] = 1;
    Vector3 translation = temp * m_relativePosition;
    std::cout  << "translation vector\n" << translation << std::endl;
    
    //Vector3 translation = -rotMatrix * m_position;
    rotMatrix[12] = translation.x;
    rotMatrix[13] = translation.y;
    rotMatrix[14] = translation.z;
    //m_viewMatrix = Matrix4::Identity();
    m_viewMatrix = rotMatrix;
    
    std::cout << "view matrix\n" << m_viewMatrix << std::endl;

//     Vector3 xAxis = Vector3(conjRotMatrix[0], conjRotMatrix[1], conjRotMatrix[2]);
//     Vector3 yAxis = Vector3(conjRotMatrix[4], conjRotMatrix[5], conjRotMatrix[6]);
//     Vector3 zAxis = Vector3(conjRotMatrix[8], conjRotMatrix[9], conjRotMatrix[10]);
// 
//     m_viewMatrix[12] = -Dot(xAxis, m_position);
//     m_viewMatrix[13] = -Dot(yAxis, m_position);
//     m_viewMatrix[14] = -Dot(zAxis, m_position);
// 
//     Matrix4 rotMatrix2 = ToRotationMatrix(m_orientation);
//     Matrix4 transRotMatrix2 = Transpose(rotMatrix2);
//     Vector3 translation2 = -transRotMatrix2 * m_position;
// 
//     rotMatrix2[12] = translation2.x;
//     rotMatrix2[13] = translation2.y;
//     rotMatrix2[14] = translation2.z;
//     rotMatrix2[15] = 1.f;
// 
//     Matrix4 tempViewMatrix = Matrix4::Identity();
//     tempViewMatrix = rotMatrix2;

    // update frustum
    m_frustum.Update(m_viewMatrix);

    // reset dirty flag
    ResetDirty();
}

void Camera::Update(uint32_t /*time*/)
{
    if (m_parent && m_parent->IsDirty())
    {
        m_relativeOrientation = m_parent->GetRelativeOrientation() * m_orientation;
        m_relativePosition = (m_parent->GetRelativeOrientation() * m_position) + m_parent->GetRelativePosition();

        MarkDirty();
    }
}

Matrix4 Camera::GetTransform()
{
    if (m_parent)
    {
        return m_parent->GetTransform();
    }

    return Matrix4::Identity();
}

void Camera::MarkDirty()
{
    m_needsUpdate = true;
}

void Camera::ResetDirty()
{
    m_needsUpdate = false;
}

bool Camera::IsDirty()
{  
    return m_needsUpdate;
}
