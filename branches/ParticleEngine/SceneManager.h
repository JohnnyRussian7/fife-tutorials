
#ifndef SCENE_MANAGER_H_
#define SCENE_MANAGER_H_

#include <map>
#include <string>

#include "stdint.h"
#include "Vector3.h"
#include "Quaternion.h"
#include "Rect.h"
#include "Color.h"
#include "BufferEnums.h"

class SceneNode;
class Camera;
class IEntity;
class IRenderSystem;
class IVertexBuffer;
class IIndexBuffer;
class Billboard;
class AnimatedTexture;
class ISpriteSheet;
class Image;

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

    // scene node functions
    SceneNode* GetRootSceneNode() const;
    SceneNode* CreateSceneNode(const char* name = 0);
    SceneNode* GetSceneNode(const char* name) const;
    void DestroySceneNode(const char* name);
    void DestroySceneNode(SceneNode* node);

    // entity functions
    IEntity* CreateEntity(const char* name = 0) const;
    void DestroyEntity(IEntity* entity);

    AnimatedTexture* CreateAnimatedTexture(uint32_t runTimeInMs=0, bool looping=true, const char* name=0);
    AnimatedTexture* CreateAnimatedTexture(ISpriteSheet* spriteSheet, uint32_t runTimeInMs=0, bool looping=true, const char* name=0);
    AnimatedTexture* CreateAnimatedTexture(Image* image, uint32_t numRows=1, uint32_t numCols=1, uint32_t numTiles=1, uint32_t runTimeInMs=0, bool looping=true, const char* name=0);
    void DestroyAnimatedTexture(AnimatedTexture* animatedTexture);

    Billboard* CreateBillboard(uint32_t width=1, uint32_t height=1, const Vector3& position=Vector3::Zero(), const Color& color=ColorWhite(), const FloatRect& texCoords=FloatRect(0.f, 1.f, 1.f, 0.f));
    void DestroyBillboard(Billboard* billboard);

    // for internal use only
    IVertexBuffer* CreateVertexBuffer(uint32_t numVertices, uint32_t vertexSize, HwBufferUsage::Enum usage);
    IIndexBuffer* CreateIndexBuffer(uint32_t numIndices, IndexBufferDataType::Enum indexType, HwBufferUsage::Enum usage);

    void UpdateScene(uint32_t time);
    void RenderScene(uint32_t time);

private:
    SceneManagerSettings m_settings;
    SceneNode* m_rootSceneNode;
    Camera* m_camera;

    typedef std::map<std::string, SceneNode*> SceneNodeContainer;
    SceneNodeContainer m_sceneNodes;

    IRenderSystem* m_renderSystem;
};

#endif
