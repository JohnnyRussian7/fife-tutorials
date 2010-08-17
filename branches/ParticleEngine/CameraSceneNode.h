
#ifndef CAMERA_SCENE_NODE_H_
#define CAMERA_SCENE_NODE_H_

#include "SceneNode.h"
#include "Vector3.h"
#include "Quaternion.h"

class Camera;
class SceneManager;

class CameraSceneNode : public SceneNode
{
public:
	CameraSceneNode(const char* name, SceneManager* manager, 
					const Vector3& position = Vector3(),
					const Quaternion& rotation = Quaternion());
	~CameraSceneNode();

// 	GetViewMatrix();
// 	GetPosition();
// 	GetRotation();
private:
	Camera* m_camera;
};

#endif
