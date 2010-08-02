
#include <sstream>

#include "stdint.h"
#include "SceneNode.h"
#include "SceneManager.h"

namespace
{
	std::string CreateSceneNodeUniqueName()
	{
		// automated counting for scene node name generation, in case the user doesn't provide a name
		static uint32_t uniqueNumber = 0;
		static std::string sceneNodeBaseName = "SceneNode";

		std::ostringstream oss;
		oss << sceneNodeBaseName << "_" << uniqueNumber;
		
		const std::string name = oss.str();
		++uniqueNumber;

		return name;
	}
}

SceneNode::SceneNode(const char* name, SceneManager* manager)
: m_name(""), m_sceneManager(manager), m_parent(0), m_relativeScale(1, 1, 1), m_relativePosition(Vector3::Zero()),
  m_relativeOrientation(Quaternion::Identity())
{
	if (name)
	{
		m_name = std::string(name);
	}
	else
	{
		m_name = CreateSceneNodeUniqueName();
	}

	if (m_parent)
	{
		m_parent->AddChild(this);
	}
}

SceneNode::~SceneNode()
{
	RemoveAllChildren();
}

const char* SceneNode::GetName() const
{
	return m_name.c_str();
}

void SceneNode::SetParent(SceneNode* parent)
{
	if (m_parent != 0)
	{
		// remove child but don't delete it
		// or we would be deleting ourselves
		m_parent->RemoveChild(this, false);
	}

	m_parent = parent;
	
	if (m_parent)
	{
		m_parent->AddChild(this);
	}
}

void SceneNode::SetParent(const char* parentName)
{
	if (m_parent != 0)
	{
		// remove child but don't delete it
		// or we would be deleting ourselves
		m_parent->RemoveChild(this, false);
	}

	m_parent = m_sceneManager->GetSceneNode(parentName);
	
	if (m_parent)
	{
		m_parent->AddChild(this);
	}
}

SceneNode* SceneNode::GetParent() const
{
	return m_parent;
}

void SceneNode::AddChild(SceneNode* child)
{
	if (child)
	{
		m_childNodes.push_back(child);
	}
}

void SceneNode::RemoveChild(SceneNode* child, bool shouldDeleteChild)
{
	if (child)
	{
		std::vector<SceneNode*>::iterator iter = m_childNodes.begin();
		for (; iter != m_childNodes.end(); ++iter)
		{
			if (*iter == child)
			{
				if (shouldDeleteChild)
				{
					delete *iter;
				}
				m_childNodes.erase(iter);
				break;
			}
		}
	}
}

void SceneNode::RemoveAllChildren()
{
	// delete all children
	std::vector<SceneNode*>::iterator iter = m_childNodes.begin();
	for (; iter != m_childNodes.end(); ++iter)
	{
		delete *iter;
	}
	m_childNodes.clear();
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



