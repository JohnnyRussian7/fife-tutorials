
#include "SceneManager.h"
#include "SceneNode.h"
#include "Camera.h"
#include "Entity.h"
#include "IRenderSystem.h"

SceneManager::SceneManager(const SceneManagerSettings& settings, IRenderSystem* renderSystem)
: m_settings(settings), m_rootSceneNode(0), m_renderSystem(renderSystem)
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

Camera* SceneManager::CreateCamera(const char* name, const Vector3& position, const Quaternion& orientation)
{
    return new Camera(name, position, orientation);
}

void SceneManager::AddCamera(Camera* camera)
{
	m_camera = camera;
}

SceneNode* SceneManager::GetRootSceneNode() const
{
	return m_rootSceneNode;
}

SceneNode* SceneManager::CreateSceneNode(const char* name)
{
	SceneNode* node = new SceneNode(name, this);
    std::pair<SceneNodeContainer::iterator, bool> retVal = m_sceneNodes.insert(std::make_pair(node->GetName(), node));

    if (retVal.second)
    {
        return (retVal.first->second);
    }

    return 0;
}

void SceneManager::DestroySceneNode(const char* name)
{	
	if (name)
	{
		SceneNodeContainer::iterator iter = m_sceneNodes.find(name);

		if (iter != m_sceneNodes.end())
		{
            SceneNode* parent = iter->second->GetParent();

            if (parent)
            {
                iter->second->GetParent()->RemoveChild(iter->second);
            }

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

void SceneManager::DestroyEntity(Entity* entity)
{
    delete entity;
}

IVertexBuffer* SceneManager::CreateVertexBuffer(uint32_t numVertices, uint32_t vertexSize, HwBufferUsage::Enum usage)
{
    return m_renderSystem->CreateVertexBuffer(numVertices, vertexSize, usage);
}

IIndexBuffer* SceneManager::CreateIndexBuffer(uint32_t numIndices, IndexBufferDataType::Enum indexType, HwBufferUsage::Enum usage)
{
    return m_renderSystem->CreateIndexBuffer(numIndices, indexType, usage);
}

void SceneManager::UpdateScene()
{
    // start the cascading update calls to all scene nodes
    GetRootSceneNode()->Update();
}

void SceneManager::RenderScene()
{
    // update the scene graph information before rendering
    UpdateScene();

    m_renderSystem->ClearBuffers();

    // push data to render system
    if (m_camera)
    {
        m_renderSystem->SetTransform(TransformType::View, m_camera->GetViewMatrix());
    }

//     SceneNode* node = GetRootSceneNode();
//     while (node)
//     {
//         m_renderSystem->SetTransform(TransformType::Model, node->GetRelativeTransform());
//         m_renderSystem->Render();
// 
//         node = node->
//     }

    // TODO - remove this renderable, and use real ones when ready
    Renderable* renderable;
    //Billboard* b = new Billboard(this, Vector3())

    m_renderSystem->Render(renderable);
}