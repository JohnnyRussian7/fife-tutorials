
#include "CameraSceneNode.h"
#include "Camera.h"

CameraSceneNode::CameraSceneNode(SceneNode* parent, const Vector3& position, const Quaternion& rotation)
: SceneNode(parent)
{
	m_camera = new Camera(position, rotation);
}