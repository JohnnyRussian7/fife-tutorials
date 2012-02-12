/**********************************************************************
*	Filename: SceneManager.cpp
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
#include "PrecompiledIncludes.h"

#include "SceneManager.h"
#include "SceneNode.h"
#include "Camera.h"
#include "Billboard.h"
#include "IAnimation.h"
#include "AnimatedTexture.h"
#include "ISpriteSheet.h"
#include "SpriteSheet.h"
#include "../Engine.h"
#include "../IEntity.h"
#include "../rendersystem/IRenderSystem.h"
#include "../rendersystem/RenderOperation.h"
#include "../graphics/ImageFwd.h"
#include "../graphics/TextureManager.h"
#include "../graphics/ImageManager.h"

SceneManager::SceneManager(Engine* engine, const SceneManagerSettings& settings, IRenderSystem* renderSystem)
: m_engine(engine), m_settings(settings), m_rootSceneNode(0), m_renderSystem(renderSystem)
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

void SceneManager::DestroyCamera(Camera* camera)
{
    if (m_camera == camera)
    {
        m_camera = 0;
    }
    
    delete camera;
    camera = 0;
}

void SceneManager::AddCamera(Camera* camera)
{
	m_camera = camera;
}

Camera* SceneManager::GetCamera() const
{
    return m_camera;
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
                parent->RemoveChild(iter->second);
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

IEntity* SceneManager::CreateEntity(const char* name) const
{
	return new Entity(name);
}

void SceneManager::DestroyEntity(IEntity* entity)
{
    delete entity;
}

IAnimation* SceneManager::CreateAnimatedTexture(uint32_t runTimeInMs, bool looping, const char* name)
{
    AnimatedTexture* texture = new AnimatedTexture(name);
    texture->SetTotalRunTime(runTimeInMs);
    texture->SetLooping(looping);

    return texture;
}

IAnimation* SceneManager::CreateAnimatedTexture(ISpriteSheet* spriteSheet, uint32_t runTimeInMs, bool looping, const char* name)
{
    AnimatedTexture* animTexture = 0;
    if (spriteSheet)
    {
        // create texture from sprite sheet image
        ImagePtr image = spriteSheet->GetImage();
        if (image)
        {
            TexturePtr texture = m_engine->GetTextureManager()->CreateTexture(TextureType::_2d, image);
            animTexture = new AnimatedTexture(name, spriteSheet, texture);
            animTexture->SetTotalRunTime(runTimeInMs);
            animTexture->SetLooping(looping);
        }
    }
    else
    {
        animTexture = new AnimatedTexture(name);
        animTexture->SetTotalRunTime(runTimeInMs);
        animTexture->SetLooping(looping);
    }

    return animTexture;
}

IAnimation* SceneManager::CreateAnimatedTexture(const char* imageFile, uint32_t numRows, uint32_t numCols, uint32_t numTiles, uint32_t runTimeInMs, bool looping, const char* name)
{
    AnimatedTexture* animTexture = 0;
    if (imageFile)
    {
        ImagePtr image = m_engine->GetImageManager()->CreateImage(imageFile, name);
        ISpriteSheet* spriteSheet = new SpriteSheet(image);
        TexturePtr texture = m_engine->GetTextureManager()->CreateTexture(TextureType::_2d, image);
        spriteSheet->SetNumRows(numRows);
        spriteSheet->SetNumCols(numCols);
        spriteSheet->SetNumTiles(numTiles);
        animTexture = new AnimatedTexture(name, spriteSheet, texture);
        animTexture->SetTotalRunTime(runTimeInMs);
        animTexture->SetLooping(looping);
    }
    else
    {
        animTexture = new AnimatedTexture(name);
        animTexture->SetTotalRunTime(runTimeInMs);
        animTexture->SetLooping(looping);
    }

    return animTexture;
}

void SceneManager::DestroyAnimatedTexture(IAnimation* animatedTexture)
{
    delete animatedTexture;
    animatedTexture = 0;
}

Billboard* SceneManager::CreateBillboard(uint32_t width, uint32_t height, const Vector3& position, const Color& color, const FloatRect& texCoords)
{
    Billboard* b = new Billboard(this, position);
    b->SetDimensions(width, height);
    b->SetColor(color);
    b->SetTextureCoordinates(texCoords);

    return b;
}

void SceneManager::DestroyBillboard(Billboard* billboard)
{
    delete billboard;
    billboard = 0;
}

IVertexBuffer* SceneManager::CreateVertexBuffer(uint32_t numVertices, uint32_t vertexSize, HwBufferUsage::Enum usage)
{
    return m_renderSystem->CreateVertexBuffer(numVertices, vertexSize, usage);
}

IIndexBuffer* SceneManager::CreateIndexBuffer(uint32_t numIndices, IndexBufferDataType::Enum indexType, HwBufferUsage::Enum usage)
{
    return m_renderSystem->CreateIndexBuffer(numIndices, indexType, usage);
}

void SceneManager::UpdateScene(uint32_t time)
{
    // start the cascading update calls to all scene nodes
    GetRootSceneNode()->Update(time);
}

void SceneManager::RenderScene(uint32_t time)
{
    // update the scene graph information before rendering
    UpdateScene(time);

    // clear the render system buffers to get ready for the next scene render
    m_renderSystem->ClearBuffers();

    // push camera view transform to the render system
    if (m_camera)
    {
        m_renderSystem->SetTransform(TransformType::View, m_camera->GetViewMatrix());
    }

    // get all the render operations in the scene
    std::vector<RenderOperation> renderOperations;
    GetRootSceneNode()->GetRenderOperations(renderOperations);
    
    // pass each render operation to the render system
    std::vector<RenderOperation>::iterator iter;
    for (iter = renderOperations.begin(); iter != renderOperations.end(); ++iter)
    { 
        // render each operation
        m_renderSystem->Render(*iter);
    }

    // render axes last
    m_renderSystem->RenderAxes();
}