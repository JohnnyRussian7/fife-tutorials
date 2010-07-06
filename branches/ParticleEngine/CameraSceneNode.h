
#ifndef CAMERA_SCENE_NODE_H_
#define CAMERA_SCENE_NODE_H_

#include "SceneNode.h"
#include "Vector.h"
#include "Quaternion.h"

class Camera;

class CameraSceneNode : public SceneNode
{
public:
	CameraSceneNode(SceneNode* parent = NULL, 
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
