
#include "SceneNode.h"

SceneNode::SceneNode(SceneNode* parent)
: m_parent(parent)
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

