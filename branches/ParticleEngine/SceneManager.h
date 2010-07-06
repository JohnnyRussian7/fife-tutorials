
#ifndef SCENE_MANAGER_H_
#define SCENE_MANAGER_H_

#include "Vector.h"
#include "Quaternion.h"

class SceneNode;
class CameraSceneNode;

class SceneManager
{
public:
	SceneManager();
	~SceneManager();

	void AddCamera(SceneNode* parent, 
					const Vector3& position=Vector3(), 
					const Quaternion& rotation=Quaternion());

private:
	CameraSceneNode* m_camSceneNode;
};

#endif
