	
#ifndef SCENE_MANAGER_H_
#define SCENE_MANAGER_H_

#include <map>
#include <string>

#include "Vector3.h"
#include "Quaternion.h"

class SceneNode;
class Camera;
class Entity;
class IRenderSystem;
class IVertexBuffer;
class IIndexBuffer;

#include "BufferEnums.h"

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
	SceneManager(const SceneManagerSettings& settings, IRenderSystem* renderSystem);
	~SceneManager();

    Camera* CreateCamera(const char* name = 0, 
                            const Vector3& position=Vector3::Zero(), 
                            const Quaternion& orientation=Quaternion::Identity());

    void AddCamera(Camera* camera);

	SceneNode* GetRootSceneNode() const;
	SceneNode* CreateSceneNode(const char* name = 0);

	void DestroySceneNode(const char* name);
	void DestroySceneNode(SceneNode* node);

	SceneNode* GetSceneNode(const char* name) const;
	Entity* CreateEntity(const char* name = 0) const;
    
    IVertexBuffer* CreateVertexBuffer(uint32_t numVertices, uint32_t vertexSize, HwBufferUsage::Enum usage);

    IIndexBuffer* CreateIndexBuffer(uint32_t numIndices, IndexBufferDataType::Enum indexType, HwBufferUsage::Enum usage);

    void UpdateScene();
    void RenderScene();

private:
	SceneManagerSettings m_settings;
	SceneNode* m_rootSceneNode;
	Camera* m_camera;

	typedef std::map<std::string, SceneNode*> SceneNodeContainer;
	SceneNodeContainer m_sceneNodes;

    IRenderSystem* m_renderSystem;
};

#endif
