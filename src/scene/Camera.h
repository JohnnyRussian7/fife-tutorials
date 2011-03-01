/**********************************************************************
*	Filename: Camera.h
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
#ifndef CAMERA_H_
#define CAMERA_H_

#include "../StdIncludes.h"

#include "Frustum.h"
#include "../IEntity.h"
#include "../math/Vector3.h"
#include "../math/Matrix4.h"
#include "../math/Quaternion.h"

class SceneNode;

class Camera : public IEntity
{
public:
	Camera(const char* name, const Vector3& position = Vector3::Zero(),
            const Quaternion& orientation = Quaternion::Identity());

    const char* GetName() const;

    const Vector3& GetPosition() const;
    void SetPosition(float x, float y, float z);
    void SetPosition(const Vector3& position);

    const Quaternion& GetOrientation() const;
	const Matrix4& GetViewMatrix();
    const Frustum& GetFrustum();

	Vector3 GetUp() const;
	Vector3 GetRight() const;
	Vector3 GetLookAt() const;

    void Translate(float x, float y, float z);
	void Translate(const Vector3& translation);
	void LookAt(const Vector3& target);

	void Pitch(float angle);
	void Yaw(float angle);
	void Roll(float angle);

    bool IsYawAxisFixed() const;
    const Vector3& GetFixedYawAxis() const;
    void SetFixedYawAxis(bool fixedYaw, const Vector3& axis = Vector3::UnitY());

	void Rotate(const Vector3& axis, float angle);
	void Rotate(const Quaternion& rotation);

	void UpdateView();

    virtual void SetParent(SceneNode* node);
    virtual SceneNode* GetParent() const;

    virtual void SetVisual(Visual* visual);
    virtual Visual* GetVisual() const;

    virtual void Update(uint32_t time);

    virtual Matrix4 GetTransform();

private:
    void MarkDirty();
    void ResetDirty();
    bool IsDirty();

private:
    std::string m_name;
	Vector3 m_position;
	Quaternion m_orientation;
    Matrix4 m_viewMatrix;
    Frustum m_frustum;
    bool m_needsUpdate;
    SceneNode* m_parent;
    Visual* m_visual;
    bool m_fixedYaw;
    Vector3 m_fixedYawAxis;
};

#endif
