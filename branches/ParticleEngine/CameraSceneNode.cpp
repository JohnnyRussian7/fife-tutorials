
#include "CameraSceneNode.h"
#include "Camera.h"

CameraSceneNode::CameraSceneNode(const char* name, SceneManager* manager, 
								 const Vector3& position, const Quaternion& rotation)
: SceneNode(name, manager)
{
	m_camera = new Camera(position, rotation);
}