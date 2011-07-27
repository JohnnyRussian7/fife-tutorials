/**********************************************************************
*	Filename: SceneNode.h
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
#ifndef SCENENODE_H_
#define SCENENODE_H_

#include "../StdIncludes.h"

#include "../math/Vector3.h"
#include "../math/Quaternion.h"
#include "../math/Matrix4.h"
#include "../rendersystem/BlendingMode.h"
#include "../rendersystem/CullMode.h"
#include "../rendersystem/PolygonWindingMode.h"
#include "../rendersystem/FillMode.h"
#include "../rendersystem/AlphaTestMode.h"

class SceneManager;
class IEntity;
class RenderOperation;

class SceneNode
{
public:
	SceneNode(const char* name, SceneManager* manager);
	~SceneNode();
	
	const char* GetName() const;

	void SetParent(SceneNode* parent);
	void SetParent(const char* parentName);
	SceneNode* GetParent() const;

	void AddChild(SceneNode* child);
	void RemoveChild(SceneNode* child, bool shouldDeleteChild = true);
	void RemoveAllChildren();

    void AddEntity(IEntity* entity);
    void RemoveEntity(IEntity* entity, bool shouldDeleteEntity = true);
    void RemoveEntity(const char* name, bool shouldDeleteChild);
    void RemoveAllEntities();

    void GetRenderOperations(std::vector<RenderOperation>& renderOperations);

	const Vector3& GetScale() const;
	const Vector3& GetPosition() const;
	const Quaternion& GetOrientation() const;

	const Vector3& GetRelativeScale() const;
	const Vector3& GetRelativePosition() const;
	const Quaternion& GetRelativeOrientation() const;

	void SetScale(const Vector3& scale);
	void SetScale(float x, float y, float z);

	void SetPosition(const Vector3& position);
	void SetPosition(float x, float y, float z);

	void SetOrientation(const Quaternion& orientation);
	void SetOrientation(const Vector3& axis, float angle);

    void SetBlendingMode(const BlendingMode& blendingMode);
    const BlendingMode& GetBlendingMode();

    void SetCullMode(const CullMode& cullMode);
    const CullMode& GetCullMode();

    void SetPolygonWindingMode(const PolygonWindingMode& windingMode);
    const PolygonWindingMode& GetPolygonWindingMode();

    void SetFillMode(const FillMode& fillMode);
    const FillMode& GetFillMode();

    void SetAlphaTestMode(const AlphaTestMode& alphaTestMode);
    const AlphaTestMode& GetAlphaTestMode();

	Matrix4 GetTransform();

    void Translate(const Vector3& translation);
    void Translate(float x, float y, float z);

    void Rotate(const Quaternion& rotation);
    void Rotate(const Vector3& axis, float angle);
	
    void Pitch(float angle);
    void Yaw(float angle);
    void Roll(float angle);

    bool IsDirty();
    bool IsTransformDirty();

    void Update(uint32_t time);

private:
    void MarkDirty(bool setChildren = true);
    void ResetDirty(bool resetChildren = false);
    void MarkTransformDirty(bool setChildren = true);
    void ResetTransformDirty(bool resetChildren = false);

private:
	std::string m_name;
	SceneManager* m_sceneManager;
	SceneNode* m_parent;
	std::vector<SceneNode*> m_childNodes;

    typedef std::vector<IEntity*> EntityContainer;
    EntityContainer m_entities;

	Vector3 m_scale;
	Vector3 m_position;
	Quaternion m_orientation;

	Vector3 m_relativeScale;
	Vector3 m_relativePosition;
	Quaternion m_relativeOrientation;

    BlendingMode m_blendingMode;
    bool m_localBlendingMode;

    CullMode m_cullMode;
    bool m_localCullMode;

    PolygonWindingMode m_windingMode;
    bool m_localWindingMode;

    FillMode m_fillMode;
    bool m_localFillMode;

    AlphaTestMode m_alphaTestMode;
    bool m_localAlphaTestMode;

	bool m_updateTransform;
	Matrix4 m_transform;

    bool m_requiresUpdate;
};

#endif
