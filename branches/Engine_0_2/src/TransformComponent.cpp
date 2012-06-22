/**********************************************************************
 *	Filename: TransformComponent.cpp
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

#include "TransformComponent.h"

#include "IEntity.h"

TransformComponent::TransformComponent()
: m_owner(0), m_parent(0), m_dirty(true), m_transformDirty(false), m_position(Vector3::Zero()), m_orientation(Quaternion::Identity()),
m_scale(Vector3(1, 1, 1)), m_relativePosition(Vector3::Zero()), m_relativeOrientation(Quaternion::Identity()), m_relativeScale(Vector3(1, 1, 1))
{
    
}

TransformComponent::~TransformComponent()
{
    if (m_parent)
    {
        // remove ourselves as a listener from our parent if one exists
        m_parent->RemoveTransformChangedListener(this);
    }
}

bool TransformComponent::IsDirty() const
{
    return m_dirty;
}

void TransformComponent::MarkDirty()
{
    m_dirty = true;
}

void TransformComponent::ResetDirty()
{
    m_dirty = false;
}

bool TransformComponent::IsTransformDirty() const
{
    return m_transformDirty;
}

void TransformComponent::MarkTransformDirty()
{
    m_transformDirty = true;
}

void TransformComponent::ResetTransformDirty()
{
    m_transformDirty = false;
}

void TransformComponent::SetParent(TransformComponent* parent)
{
    if (m_parent != parent)
    {
        if (m_parent)
        {
            // remove ourselves from previous parent updates
            m_parent->RemoveTransformChangedListener(this);
        }
        
        // set new parent
        m_parent = parent;
        
        if (m_parent)
        {
            // add ourselves as a listener to new parent
            m_parent->AddTransformChangedListener(this);
        }
        
        // our parent has been changed so assume dirty
        MarkDirty();
    }
}

const Vector3& TransformComponent::GetPosition() const
{
    return m_position;
}

void TransformComponent::SetPosition(const Vector3& position)
{
    m_position = position;
    
    MarkDirty();
}

const Quaternion& TransformComponent::GetOrientation() const
{
    return m_orientation;
}

void TransformComponent::SetOrientation(const Quaternion& orientation)
{
    m_orientation = orientation;
    
    MarkDirty();
}

const Vector3& TransformComponent::GetScale() const
{
    return m_scale;
}

void TransformComponent::SetScale(const Vector3& scale)
{
    m_scale = scale;
    
    MarkDirty();
}

void TransformComponent::Translate(float x, float y, float z)
{
    Translate(Vector3(x, y, z));
}

void TransformComponent::Translate(const Vector3& translation)
{
    // translate in local space
    //m_position += translation;
    m_position += m_orientation * translation;
    std::cout << "Translate: by " << translation << " m_position: " << m_position << std::endl;
    MarkDirty();
}

void TransformComponent::Rotate(const Vector3& axis, float angle)
{
    Rotate(FromAxisAngle(axis, angle));
}

void TransformComponent::Rotate(const Quaternion& rotation)
{
    Quaternion normRotation = Normalize(rotation);
    
    // rotation in local space
    m_orientation = m_orientation * normRotation;
    MarkDirty();
}

const Vector3& TransformComponent::GetRelativePosition() const
{
    return m_relativePosition;
}

const Quaternion& TransformComponent::GetRelativeOrientation() const
{
    return m_relativeOrientation;
}

const Vector3& TransformComponent::GetRelativeScale() const
{
    return m_relativeScale;
}

Matrix4 TransformComponent::GetTransform()
{
    // performs lazy update of transform if needed
    // we do it here so it only gets updated if its actually used
    if (IsTransformDirty())
    {
        m_transform = MakeTransform(m_relativeScale, m_relativePosition, m_relativeOrientation);
        ResetTransformDirty();
    }
    
    return m_transform;
}

std::string TransformComponent::GetName()
{
    return "Transform";
}

void TransformComponent::SetOwner(IEntity* owner)
{
    // changing parent, mark our data as dirty
    if (m_owner && m_owner != owner)
    {
        MarkDirty();
    }
    
    m_owner = owner;
}

void TransformComponent::Update(uint32_t time)
{    
    if (IsDirty())
    {
        if (m_parent)
        {
            m_relativeOrientation = m_parent->GetRelativeOrientation() * m_orientation;
            m_relativeScale = m_parent->GetRelativeScale() * m_scale; 
            
            // calculation relative to parent's position and scale
            m_relativePosition = m_parent->GetRelativeOrientation() * (m_parent->GetRelativeScale() * m_position);
            
            // add to parent's relative position
            m_relativePosition += m_parent->GetRelativePosition();
        }
        else
        {
            m_relativePosition = m_position;
            m_relativeOrientation = m_orientation;
            m_relativeScale = m_scale;
        }
        
        // alert anyone listening that our transform has been modified
        FireTransformChanged();
        
        ResetDirty();
        
        MarkTransformDirty();
    }
}

void TransformComponent::OnTransformChanged()
{
    // parent's transform has changed, mark dirty
    MarkDirty();
}

void TransformComponent::AddTransformChangedListener(TransformChangedListener* listener)
{
    m_listeners.push_back(listener);
}

void TransformComponent::RemoveTransformChangedListener(TransformChangedListener* listener)
{
    TransformListeners::iterator iter;
    for (iter = m_listeners.begin(); iter != m_listeners.end(); ++iter)
    {
        if ((*iter) == listener)
        {
            m_listeners.erase(iter);
            break;
        }
    }
}

void TransformComponent::FireTransformChanged()
{
    TransformListeners::iterator iter;
    for (iter = m_listeners.begin(); iter != m_listeners.end(); ++iter)
    {
        (*iter)->OnTransformChanged();
    }
}


