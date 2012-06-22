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
#include "../TransformComponent.h"

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

Camera::Camera(const char* name)
: m_viewMatrix(Matrix4::Identity()), m_viewDirty(true), m_needsUpdate(true), 
m_fixedYaw(false), m_fixedYawAxis(Vector3::UnitY())
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

void Camera::SetPosition(float x, float y, float z)
{
    SetPosition(Vector3(x,y,z));
}

void Camera::SetPosition(const Vector3& position)
{
    m_transformComponent->SetPosition(position);

    MarkDirty();
}

const Quaternion& Camera::GetOrientation() const
{
    return m_transformComponent->GetOrientation();
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
	return m_transformComponent->GetOrientation() * Vector3::UnitY();
}

Vector3 Camera::GetRight() const
{
	return m_transformComponent->GetOrientation() * Vector3::UnitX();
}

Vector3 Camera::GetLookAt() const
{
	// always looking down the -z axis
	return m_transformComponent->GetOrientation() * -Vector3::UnitZ();
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
	//m_position += m_orientation * translation;
    m_transformComponent->Translate(translation);
    
    MarkDirty();
}

void Camera::LookAt(float x, float y, float z)
{
    LookAt(Vector3(x, y, z));
}

void Camera::LookAt(const Vector3& target)
{
    // always looking down negative z-axis so negate direction
	Vector3 direction = -(target - m_transformComponent->GetPosition());

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
	    Vector3 zAxis = ZAxis(m_transformComponent->GetOrientation()); 

	    // get shortest rotation arc to direction
	    Quaternion rotation = GetRotationTo(zAxis, normDirection);

	    orientation = rotation * m_transformComponent->GetOrientation();
    }

    if (m_parent)
    {
        // calculate orientation with respect to parent
        m_transformComponent->SetOrientation(Inverse(m_parent->GetRelativeOrientation()) * m_transformComponent->GetOrientation());
    }
    else
    {
        // no parent just set orientation directly
        m_transformComponent->SetOrientation(orientation);
    }

    MarkDirty();
}

void Camera::Pitch(float angle)
{
	Vector3 xaxis = GetRight();
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
        yAxis = GetUp();
    }

    Rotate(yAxis, angle);

    MarkDirty();
}

void Camera::Roll(float angle)
{
	Vector3 zaxis = m_transformComponent->GetOrientation() * Vector3::UnitZ();
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
    m_transformComponent->Rotate(rotation);

    MarkDirty();
}

void Camera::UpdateView()
{
    if (!IsViewDirty())
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
    Matrix4 rotMatrix = ToRotationMatrix(m_transformComponent->GetRelativeOrientation());
    TransposeRef(rotMatrix);

    Matrix4 temp = -rotMatrix;
    temp[3] = 0;
    temp[7] = 0;
    temp[11] = 0;
    temp[15] = 1;
    Vector3 translation = temp * m_transformComponent->GetRelativePosition();
    
    //Vector3 translation = -rotMatrix * m_position;
    rotMatrix[12] = translation.x;
    rotMatrix[13] = translation.y;
    rotMatrix[14] = translation.z;
    m_viewMatrix = rotMatrix;

    // update frustum
    m_frustum.Update(m_viewMatrix);

    //std::cout << "view matrix" << std::endl;
    //std::cout << m_viewMatrix << std::endl;
    // reset dirty flag
    ResetViewDirty();
}

void Camera::Update(uint32_t time)
{
    if (m_transformComponent->IsDirty())
    {        
        MarkViewDirty();
    }
    
    // call base class update, handles all component updates
    Entity::Update(time);
    
    if (m_parent && m_parent->IsDirty())
    {
        //m_relativeOrientation = m_parent->GetRelativeOrientation() * m_orientation;
        //m_relativePosition = (m_parent->GetRelativeOrientation() * m_position) + m_parent->GetRelativePosition();

        MarkDirty();
    }
}

Matrix4 Camera::GetTransform()
{
    return m_transformComponent->GetTransform();
    
    /*
    if (m_parent)
    {
        return m_parent->GetTransform();
    }

    return Matrix4::Identity();
    */
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
    return m_transformComponent->IsDirty();
    //return m_needsUpdate;
}

void Camera::MarkViewDirty()
{
    m_viewDirty = true;
}

void Camera::ResetViewDirty()
{
    m_viewDirty = false;
}

bool Camera::IsViewDirty() const
{
    return m_viewDirty;
}
