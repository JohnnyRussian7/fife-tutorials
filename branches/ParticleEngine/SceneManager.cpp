
#include "SceneManager.h"
#include "SceneNode.h"
#include "CameraSceneNode.h"
#include "Entity.h"

SceneManager::SceneManager(const SceneManagerSettings& settings)
: m_settings(settings), m_rootSceneNode(0)
{
	if (m_settings.rootNodeName == "")
	{
		m_rootSceneNode = CreateSceneNode(settings.rootNodeName.c_str());
	}
	else
	{
		// default the root node to something reasonable and easy to remember
		m_rootSceneNode = CreateSceneNode("RootNode");
	}
}

SceneManager::~SceneManager()
{

}

void SceneManager::AddCamera(const char* name, const Vector3& position, const Quaternion& rotation)
{
	m_camSceneNode = new CameraSceneNode(name, this, position, rotation);
}

SceneNode* SceneManager::GetRootSceneNode() const
{
	return m_rootSceneNode;
}

SceneNode* SceneManager::CreateSceneNode(const char* name)
{
	SceneNode* node = 0;

	if (name)
	{
		// lets make sure the node doesn't already exist before creating it
		SceneNodeContainer::iterator iter = m_sceneNodes.find(name);
		if (iter != m_sceneNodes.end())
		{
			node = new SceneNode(name, this);
			m_sceneNodes.insert(std::make_pair(name, node));
		}
	}

	node = new SceneNode(name, this);
	m_sceneNodes.insert(std::make_pair(name, node));

	return node;
}

void SceneManager::DestroySceneNode(const char* name)
{	
	if (name)
	{
		SceneNodeContainer::iterator iter = m_sceneNodes.find(name);

		if (iter != m_sceneNodes.end())
		{
			iter->second->GetParent()->RemoveChild(iter->second);
			delete iter->second;
			m_sceneNodes.erase(iter);
		}
	}
}

void SceneManager::DestroySceneNode(SceneNode* node)
{
	DestroySceneNode(node->GetName());
}

SceneNode* SceneManager::GetSceneNode(const char* name) const
{
	if (name)
	{
		SceneNodeContainer::const_iterator iter = m_sceneNodes.find(name);

		if (iter != m_sceneNodes.end())
		{
			return iter->second;
		}
	}

	return 0;
}

Entity* SceneManager::CreateEntity(const char* name) const
{
	return new Entity(name);
}