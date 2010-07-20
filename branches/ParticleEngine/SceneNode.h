
#ifndef SCENE_NODE_H_
#define SCENE_NODE_H_

#include <vector>

#include "Vector.h"
#include "Quaternion.h"
#include "Matrix.h"

class SceneNode
{
public:
	SceneNode(SceneNode* parent);
	~SceneNode();
	
	void AddChild(SceneNode* child);
	void RemoveChild(SceneNode* child);

	const Vector3& GetRelativeScale() const;
	const Vector3& GetRelativePosition() const;
	const Quaternion& GetRelativeOrientation() const;

	const Vector3& GetAbsoluteScale() const;
	const Vector3& GetAbsolutePosition() const;
	const Quaternion& GetAbsoluteOrientation() const;

	void SetScale(const Vector3& scale);
	void SetScale(float x, float y, float z);

	void SetPosition(const Vector3& position);
	void SetPosition(float x, float y, float z);

	void SetOrientation(const Quaternion& orientation);
	void SetOrientation(float x, float y, float z, float w);

	const Matrix4& GetRelativeTransform() const;
	const Matrix4& GetAbsoluteTransform() const;
	
private:
	SceneNode* m_parent;
	std::vector<SceneNode*> m_childNodes;

	Vector3 m_relativeScale;
	Vector3 m_relativePosition;
	Quaternion m_relativeOrientation;

	Vector3 m_absoluteScale;
	Vector3 m_absolutePosition;
	Quaternion m_absoluteOrientation;

	bool m_updateTransform;
	Matrix4 m_transform;
};

#endif
