
#ifndef SCENE_NODE_H_
#define SCENE_NODE_H_

#include <vector>
#include <string>

#include "Vector.h"
#include "Quaternion.h"
#include "Matrix.h"

class SceneManager;
class Entity;

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

    void AddEntity(Entity* entity);
    void RemoveEntity(Entity* entity, bool shouldDeleteEntity = true);
    void RemoveEntity(const char* name, bool shouldDeleteChild);
    void RemoveAllEntities();

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

	Matrix4 GetRelativeTransform() const;
	Matrix4 GetAbsoluteTransform() const;
	
private:
	std::string m_name;
	SceneManager* m_sceneManager;
	SceneNode* m_parent;
	std::vector<SceneNode*> m_childNodes;

    typedef std::vector<Entity*> EntityContainer;
    EntityContainer m_entities;

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
