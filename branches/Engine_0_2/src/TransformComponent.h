/**********************************************************************
 *	Filename: TransformComponent.h
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
#ifndef TRANSFORMCOMPONENT_H_
#define TRANSFORMCOMPONENT_H_

#include "math/Quaternion.h"
#include "math/Vector3.h"
#include "math/Matrix4.h"
#include "IComponent.h"

class TransformChangedListener
{
public:
    virtual void OnTransformChanged() = 0;
};

class TransformComponent : public IComponent, public TransformChangedListener
{
public:
    TransformComponent();
    virtual ~TransformComponent();

    void SetParent(TransformComponent* parent);
    
    const Vector3& GetPosition() const;
    void SetPosition(const Vector3& position);
    
    const Quaternion& GetOrientation() const;
    void SetOrientation(const Quaternion& orientation);
    
    const Vector3& GetScale() const;
    void SetScale(const Vector3& scale);
    
    void Translate(float x, float y, float z);
    void Translate(const Vector3& translation);
    
    void Rotate(const Vector3& axis, float angle);
    void Rotate(const Quaternion& rotation);
    
    // accessor for relative transform components
    const Vector3& GetRelativePosition() const;
    const Quaternion& GetRelativeOrientation() const;
    const Vector3& GetRelativeScale() const;
    
    // accessor for final calculated transform
    Matrix4 GetTransform();
    
    bool IsDirty() const;
    
    // overridden from IComponent
    virtual std::string GetName();
    virtual void SetOwner(IEntity* entity);
    virtual void Update(uint32_t time);
    
    // event listener handling
    void OnTransformChanged();
    void AddTransformChangedListener(TransformChangedListener* listener);
    void RemoveTransformChangedListener(TransformChangedListener* listener);
    
private:
    void MarkDirty();
    void ResetDirty();
    
    bool IsTransformDirty() const;
    void MarkTransformDirty();
    void ResetTransformDirty();
    
    void FireTransformChanged();
    
private:
    IEntity* m_owner;
    TransformComponent* m_parent;
    
    bool m_dirty;
    bool m_transformDirty;
    
    // local transform components
    Vector3 m_position;
    Quaternion m_orientation;
    Vector3 m_scale;
    
    // relative (to parent) transform components
    // these will be the same as local if no parent
    Vector3 m_relativePosition;
    Quaternion m_relativeOrientation;
    Vector3 m_relativeScale;
    
    // combined transform components
    Matrix4 m_transform;
    
    // listeners
    typedef std::vector<TransformChangedListener*> TransformListeners;
    TransformListeners m_listeners;
};

#endif
