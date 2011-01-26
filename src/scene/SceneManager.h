/**********************************************************************
*	Filename: SceneManager.h
*	
*	Copyright (C) 2011, FIFE team
*	http://www.fifengine.net
*
*	This file is part of FIFE.
*
*	FIFE is free software: you can redistribute it and/or modify it
*	under the terms of the GNU Lesser General Public License as
*	published by the Free Software Foundation, either version 3 of
*	the License, or any later version.
*
*	FIFE is distributed in the hope that it will be useful,
*	but WITHOUT ANY WARRANTY; without even the implied warranty of
*	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* 	GNU Lesser General Public License for more details.
*
*	You should have received a copy of the GNU Lesser General Public
*	License along with FIFE. If not, see http://www.gnu.org/licenses/.
***********************************************************************/
#ifndef SCENEMANAGER_H_
#define SCENEMANAGER_H_

#include "../StdIncludes.h"

#include "../Color.h"
#include "../math/Vector3.h"
#include "../math/Quaternion.h"
#include "../geometry/Rect.h"
#include "../graphics/VertexIndexBufferEnums.h"

class Engine;
class SceneNode;
class Camera;
class IEntity;
class IRenderSystem;
class IVertexBuffer;
class IIndexBuffer;
class Billboard;
class IAnimation;
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
    SceneManager(Engine* engine, const SceneManagerSettings& settings, IRenderSystem* renderSystem);
    ~SceneManager();

    Camera* CreateCamera(const char* name = 0, 
        const Vector3& position=Vector3::Zero(), 
        const Quaternion& orientation=Quaternion::Identity());

    void AddCamera(Camera* camera);
    Camera* GetCamera() const;

    // scene node functions
    SceneNode* GetRootSceneNode() const;
    SceneNode* CreateSceneNode(const char* name = 0);
    SceneNode* GetSceneNode(const char* name) const;
    void DestroySceneNode(const char* name);
    void DestroySceneNode(SceneNode* node);

    // entity functions
    IEntity* CreateEntity(const char* name = 0) const;
    void DestroyEntity(IEntity* entity);

    IAnimation* CreateAnimatedTexture(uint32_t runTimeInMs=0, bool looping=true, const char* name=0);
    IAnimation* CreateAnimatedTexture(ISpriteSheet* spriteSheet, uint32_t runTimeInMs=0, bool looping=true, const char* name=0);
    IAnimation* CreateAnimatedTexture(Image* image, uint32_t numRows=1, uint32_t numCols=1, uint32_t numTiles=1, uint32_t runTimeInMs=0, bool looping=true, const char* name=0);
    void DestroyAnimatedTexture(IAnimation* animatedTexture);

    Billboard* CreateBillboard(uint32_t width=1, uint32_t height=1, const Vector3& position=Vector3::Zero(), const Color& color=Color::White(), const FloatRect& texCoords=FloatRect(0.f, 1.f, 1.f, 0.f));
    void DestroyBillboard(Billboard* billboard);

    // for internal use only
    IVertexBuffer* CreateVertexBuffer(uint32_t numVertices, uint32_t vertexSize, HwBufferUsage::Enum usage);
    IIndexBuffer* CreateIndexBuffer(uint32_t numIndices, IndexBufferDataType::Enum indexType, HwBufferUsage::Enum usage);

    void UpdateScene(uint32_t time);
    void RenderScene(uint32_t time);

private:
    Engine* m_engine;
    SceneManagerSettings m_settings;
    SceneNode* m_rootSceneNode;
    Camera* m_camera;

    typedef std::map<std::string, SceneNode*> SceneNodeContainer;
    SceneNodeContainer m_sceneNodes;

    IRenderSystem* m_renderSystem;
};

#endif
