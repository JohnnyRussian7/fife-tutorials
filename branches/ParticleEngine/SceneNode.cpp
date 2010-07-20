
#include "SceneNode.h"

SceneNode::SceneNode(SceneNode* parent)
: m_parent(parent), m_relativeScale(1, 1, 1), m_relativePosition(Vector3::Zero()),
  m_relativeOrientation(Quaternion::Identity())
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

const Vector3& SceneNode::GetRelativeScale() const
{
	return m_relativeScale;
}

const Vector3& SceneNode::GetRelativePosition() const
{
	return m_relativePosition;
}

const Quaternion& SceneNode::GetRelativeOrientation() const
{
	return m_relativeOrientation;
}

const Vector3& SceneNode::GetAbsoluteScale() const
{
	return m_absoluteScale;
}

const Vector3& SceneNode::GetAbsolutePosition() const
{
	return m_absolutePosition;
}

const Quaternion& SceneNode::GetAbsoluteOrientation() const
{
	return m_absoluteOrientation;
}

void SceneNode::SetScale(const Vector3& scale)
{
	m_relativeScale = scale;
}

void SceneNode::SetScale(float x, float y, float z)
{
	SetScale(Vector3(x,y,z));
}

void SceneNode::SetPosition(const Vector3& position)
{
	m_relativePosition = position;
}

void SceneNode::SetPosition(float x, float y, float z)
{
	SetPosition(Vector3(x,y,z));
}

void SceneNode::SetOrientation(const Quaternion& orientation)
{
	m_relativeOrientation = Normalize(orientation);
}

void SceneNode::SetOrientation(float x, float y, float z, float w)
{
	SetOrientation(Quaternion(x,y,z,w));
}



