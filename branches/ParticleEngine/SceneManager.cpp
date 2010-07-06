
#include "SceneManager.h"
#include "CameraSceneNode.h"

SceneManager::SceneManager()
{

}

SceneManager::~SceneManager()
{

}

void SceneManager::AddCamera(SceneNode* parent, const Vector3& position, const Quaternion& rotation)
{
	m_camSceneNode = new CameraSceneNode(parent, position, rotation);
}