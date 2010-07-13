
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

	const Vector3& GetScale() const;
	const Vector3& GetPosition() const;
	const Quaternion& GetOrientation() const;

	void SetScale(const Vector3& scale);
	void SetScale(float x, float y, float z);

	void SetPosition(const Vector3& position);
	void SetPosition(float x, float y, float z);

	void SetOrientation(const Quaternion& orientation);
	void SetOrientation(float x, float y, float z, float w);

private:
	SceneNode* m_parent;
	std::vector<SceneNode*> m_childNodes;

	Vector3 m_scale;
	Vector3 m_position;
	Quaternion m_orientation;

	bool m_updateWorldTransform;
	Matrix4 m_worldTransform;
};

#endif
