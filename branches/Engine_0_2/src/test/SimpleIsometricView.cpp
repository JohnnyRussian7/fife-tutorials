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

void CreateSimpleIsometricView(Engine& engine)
{
    // store off scene manager locally as it will be used often
    SceneManager* sceneManager = engine.GetSceneManager();

    // setup a simple camera
    Camera* camera = sceneManager->CreateCamera();
    sceneManager->AddCamera(camera);

    // create pitch node
    SceneNode* camPitchNode = sceneManager->CreateSceneNode("camPitchNode");
    // create yaw node
    SceneNode* camYawNode = sceneManager->CreateSceneNode("camYawNode");

    // create translation node
    SceneNode* camNode = sceneManager->CreateSceneNode("CamNode");

    // add yaw node to translation node
    camNode->AddChild(camYawNode);

    // add pitch node to yaw node
    camYawNode->AddChild(camPitchNode);

    // add camera to pitch node
    camPitchNode->AddEntity(camera);
    
    // set the position and look at
    camNode->SetPosition(0, 0, 500);

    // add top level camera node to the scene
    sceneManager->GetRootSceneNode()->AddChild(camNode);

    // create isometric perspective by pitching and yawing camera
    camPitchNode->Pitch(DegToRad(30));
    camYawNode->Yaw(DegToRad(45));

    // create the individual nodes
    SceneNode* grass1Node = sceneManager->CreateSceneNode("grass1");
    SceneNode* grass2Node = sceneManager->CreateSceneNode("grass2");
    SceneNode* grass3Node = sceneManager->CreateSceneNode("grass3");
//     SceneNode* grass4Node = sceneManager->CreateSceneNode("grass4");
//     SceneNode* grass5Node = sceneManager->CreateSceneNode("grass5");


    // position the nodes
    grass1Node->SetPosition(-20, 0, 0);
    grass2Node->SetPosition(20, 0, 0);
    grass3Node->SetPosition(20, 20, 0);
//     grass4Node->SetPosition(0, -40, 0);
//     grass5Node->SetPosition(0, 40, 0);

    // add all the nodes to the root scene node
    sceneManager->GetRootSceneNode()->AddChild(grass1Node);
    sceneManager->GetRootSceneNode()->AddChild(grass2Node);
    sceneManager->GetRootSceneNode()->AddChild(grass3Node);
//     sceneManager->GetRootSceneNode()->AddChild(doom4Node);
//     sceneManager->GetRootSceneNode()->AddChild(doom5Node);

    // load the image
    filesystem::Path path("../../data/grass/45.png");
    ImagePtr grassImage = engine.GetImageManager()->CreateImage(path.GetString(), "grassImage");

    // create the entity
    IEntity* grass1Entity = sceneManager->CreateEntity("grass1");
    IEntity* grass2Entity = sceneManager->CreateEntity("grass2");
    IEntity* grass3Entity = sceneManager->CreateEntity("grass3");

    // add each entity to its scene node
    grass1Node->AddEntity(grass1Entity);
    grass2Node->AddEntity(grass2Entity);
    grass3Node->AddEntity(grass3Entity);
//     doom4Node->AddEntity(doom4Entity);
//     doom5Node->AddEntity(doom5Entity);

    // create the visual representation of the entity
    Visual* grass1Visual = sceneManager->CreateBillboard(40, 40);
    Visual* grass2Visual = sceneManager->CreateBillboard(40, 40);
    Visual* grass3Visual = sceneManager->CreateBillboard(40, 40);
//     Visual* doom4Visual = sceneManager->CreateBillboard(40, 40);
//     Visual* doom5Visual = sceneManager->CreateBillboard(40, 40);

    // set each entities visual
    grass1Entity->SetVisual(grass1Visual);
    grass2Entity->SetVisual(grass2Visual);
    grass3Entity->SetVisual(grass3Visual);
//     doom4Entity->SetVisual(doom4Visual);
//     doom5Entity->SetVisual(doom5Visual);

    // create the textures for each image, note visual 4 and 5 share the same texture
    TexturePtr grass1Texture = engine.GetTextureManager()->CreateTexture(TextureType::_2d, grassImage);
    //TexturePtr grass2Texture = engine.GetTextureManager()->CreateTexture(TextureType::_2d, grassImage);
    //TexturePtr grass3Texture = engine.GetTextureManager()->CreateTexture(TextureType::_2d, grassImage);
    //TexturePtr doom4Texture = engine.GetTextureManager()->CreateTexture(TextureType::_2d, doom4Image);

    // create an empty material for each visual
    IMaterial* grass1Material = new Material();
    IMaterial* grass2Material = new Material();
    IMaterial* grass3Material = new Material();
//     IMaterial* doom4Material = new Material();
//     IMaterial* doom5Material = new Material();

    // add material to visual
    grass1Visual->GetRenderable()->SetMaterial(grass1Material);
    grass2Visual->GetRenderable()->SetMaterial(grass2Material);
    grass3Visual->GetRenderable()->SetMaterial(grass3Material);
//     doom4Visual->GetRenderable()->SetMaterial(doom4Material);
//     doom5Visual->GetRenderable()->SetMaterial(doom5Material);

    // set the texture for each renderable
    grass1Visual->GetRenderable()->GetMaterial()->SetTexture(grass1Texture);
    grass2Visual->GetRenderable()->GetMaterial()->SetTexture(grass1Texture);
    grass3Visual->GetRenderable()->GetMaterial()->SetTexture(grass1Texture);
//     doom4Visual->GetRenderable()->GetMaterial()->SetTexture(doom4Texture);
//     doom5Visual->GetRenderable()->GetMaterial()->SetTexture(doom4Texture);

}
