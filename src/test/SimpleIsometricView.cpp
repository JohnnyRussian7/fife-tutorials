/**********************************************************************
*	Filename: SimpleIsometricView.cpp
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
#include "../Fife.h"

#include "SimpleIsometricView.h"
#include "FpsCameraController.h"

void CreateSimpleIsometricView(Engine& engine, FpsCameraController& fpsCamera)
{
    fpsCamera.move(Vector3(0.f, 0.f, 500));
    
    // store off scene manager locally as it will be used often
    SceneManager* sceneManager = engine.GetSceneManager();

    // create the individual nodes
    SceneNode* grass1Node = sceneManager->CreateSceneNode("grass1");
    SceneNode* grass2Node = sceneManager->CreateSceneNode("grass2");
    SceneNode* grass3Node = sceneManager->CreateSceneNode("grass3");
//     SceneNode* grass4Node = sceneManager->CreateSceneNode("grass4");
//     SceneNode* grass5Node = sceneManager->CreateSceneNode("grass5");


    // position the nodes
    grass3Node->SetPosition(-20, 0, 0);
    grass2Node->SetPosition(20, 0, 0);
    grass1Node->SetPosition(0, 10, 0);

    // add all the nodes to the root scene node
    sceneManager->GetRootSceneNode()->AddChild(grass1Node);
    sceneManager->GetRootSceneNode()->AddChild(grass2Node);
    sceneManager->GetRootSceneNode()->AddChild(grass3Node);

    // load the image
    filesystem::Path path("../../data/grass/45.png");
    ImagePtr grassImage = engine.GetImageManager()->CreateImage(path, "grassImage");

    // create the entity
    IEntity* grass1Entity = sceneManager->CreateEntity("grass1");
    IEntity* grass2Entity = sceneManager->CreateEntity("grass2");
    IEntity* grass3Entity = sceneManager->CreateEntity("grass3");

    // add each entity to its scene node
    grass1Node->AddEntity(grass1Entity);
    grass2Node->AddEntity(grass2Entity);
    grass3Node->AddEntity(grass3Entity);

    // create the visual representation of the entity
    Visual* grass1Visual = sceneManager->CreateBillboard(40, 40);
    Visual* grass2Visual = sceneManager->CreateBillboard(40, 40);
    Visual* grass3Visual = sceneManager->CreateBillboard(40, 40);

    // set each entities visual
    grass1Entity->SetVisual(grass1Visual);
    grass2Entity->SetVisual(grass2Visual);
    grass3Entity->SetVisual(grass3Visual);

    // create the textures for each image, note visual 4 and 5 share the same texture
    TexturePtr grass1Texture = engine.GetTextureManager()->CreateTexture(TextureType::_2d, grassImage);
    TexturePtr grass2Texture = engine.GetTextureManager()->CreateTexture(TextureType::_2d, grassImage);
    TexturePtr grass3Texture = engine.GetTextureManager()->CreateTexture(TextureType::_2d, grassImage);

    // create an empty material for each visual
    IMaterial* grass1Material = new Material();
    IMaterial* grass2Material = new Material();
    IMaterial* grass3Material = new Material();

    RenderComponent* renderComponent1 = new RenderComponent();
    renderComponent1->SetMaterial(grass1Material);
    grass1Entity->AddComponent(renderComponent1);
    
    RenderComponent* renderComponent2 = new RenderComponent();
    renderComponent2->SetMaterial(grass2Material);
    grass2Entity->AddComponent(renderComponent2);
    
    RenderComponent* renderComponent3 = new RenderComponent();
    renderComponent3->SetMaterial(grass3Material);
    grass3Entity->AddComponent(renderComponent3);
    
    // add material to visual
    grass1Visual->GetRenderable()->SetMaterial(grass1Material);
    grass2Visual->GetRenderable()->SetMaterial(grass2Material);
    grass3Visual->GetRenderable()->SetMaterial(grass3Material);

    // set the texture for each renderable
    grass1Visual->GetRenderable()->GetMaterial()->SetTexture(grass1Texture);
    grass2Visual->GetRenderable()->GetMaterial()->SetTexture(grass2Texture);
    grass3Visual->GetRenderable()->GetMaterial()->SetTexture(grass1Texture);

    BlendingMode blendMode;
    blendMode.SetEnabled(true);
    blendMode.SetSrcBlendMode(SrcBlendMode::SrcAlpha);
    blendMode.SetDestBlendMode(DestBlendMode::OneMinusSrcAlpha);
    sceneManager->GetRootSceneNode()->SetBlendingMode(blendMode);
}
