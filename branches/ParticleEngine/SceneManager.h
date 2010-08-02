	
#ifndef SCENE_MANAGER_H_
#define SCENE_MANAGER_H_

#include <map>
#include <string>

#include "Vector.h"
#include "Quaternion.h"

class SceneNode;
class CameraSceneNode;
class Entity;

struct SceneManagerType
{
	enum Enum
	{
		Generic = 0,	// no special spatial information
		QuadTree		// uses quadtree for spatial culling
	};
};

struct SceneManagerSettings
{
	SceneManagerSettings()
	: sceneManagerType(SceneManagerType::Generic), rootNodeName("")
	{

	}

	SceneManagerType::Enum sceneManagerType;
	std::string rootNodeName;
};

class SceneManager
{
public:
	SceneManager(const SceneManagerSettings& settings);
	~SceneManager();

	void AddCamera(const char* name, 
					const Vector3& position=Vector3(), 
					const Quaternion& rotation=Quaternion());

	SceneNode* GetRootSceneNode() const;
	SceneNode* CreateSceneNode(const char* name);
	void DestroySceneNode(const char* name);
	void DestroySceneNode(SceneNode* node);
	SceneNode* GetSceneNode(const char* name) const;

	Entity* CreateEntity(const char* name) const;

private:
	SceneManagerSettings m_settings;
	SceneNode* m_rootSceneNode;
	CameraSceneNode* m_camSceneNode;

	typedef std::map<std::string, SceneNode*> SceneNodeContainer;
	SceneNodeContainer m_sceneNodes;
};

#endif
