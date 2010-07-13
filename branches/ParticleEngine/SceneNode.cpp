
#include "SceneNode.h"

SceneNode::SceneNode(SceneNode* parent)
: m_parent(parent), m_scale(1, 1, 1), m_position(Vector3::Zero()),
  m_orientation(Quaternion::Identity())
{
	if (m_parent)
	{
		m_parent->AddChild(this);
	}
}

SceneNode::~SceneNode()
{
	// delete all children
	std::vector<SceneNode*>::iterator iter = m_childNodes.begin();
	for (; iter != m_childNodes.end(); ++iter)
	{
		delete *iter;
	}
	m_childNodes.clear();
}

void SceneNode::AddChild(SceneNode* child)
{
	if (child)
	{
		m_childNodes.push_back(child);
	}
}

void SceneNode::RemoveChild(SceneNode* child)
{
	if (child)
	{
		std::vector<SceneNode*>::iterator iter = m_childNodes.begin();
		for (; iter != m_childNodes.end(); ++iter)
		{
			if (*iter == child)
			{
				delete *iter;
				m_childNodes.erase(iter);
				break;
			}
		}
	}
}

const Vector3& SceneNode::GetScale() const
{
	return m_scale;
}

const Vector3& SceneNode::GetPosition() const
{
	return m_position;
}

const Quaternion& SceneNode::GetOrientation() const
{
	return m_orientation;
}

void SceneNode::SetScale(const Vector3& scale)
{
	m_scale = scale;
}

void SceneNode::SetScale(float x, float y, float z)
{
	SetScale(Vector3(x,y,z));
}

void SceneNode::SetPosition(const Vector3& position)
{
	m_position = position;
}

void SceneNode::SetPosition(float x, float y, float z)
{
	SetPosition(Vector3(x,y,z));
}

void SceneNode::SetOrientation(const Quaternion& orientation)
{
	m_orientation = Normalize(orientation);
}

void SceneNode::SetOrientation(float x, float y, float z, float w)
{
	SetOrientation(Quaternion(x,y,z,w));
}

