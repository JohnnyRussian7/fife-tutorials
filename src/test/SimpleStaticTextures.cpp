/**********************************************************************
*	Filename: SimpleStaticTextures.cpp
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

#include "SimpleStaticTextures.h"

void CreateSimpleStaticTextures(Engine& engine)
{
    // store off scene manager locally as it will be used often
    SceneManager* sceneManager = engine.GetSceneManager();

    // setup a simple camera
    Camera* camera = sceneManager->CreateCamera();
    sceneManager->AddCamera(camera);
    SceneNode* camNode = sceneManager->CreateSceneNode("CamNode");
    camNode->AddEntity(camera);
    sceneManager->GetRootSceneNode()->AddChild(camNode);
    camNode->Translate(Vector3(0, 0, 500));
    camera->LookAt(Vector3(0, 0, 0));
    camera->SetFixedYawAxis(true);

    // create the individual nodes
    SceneNode* doom1Node = sceneManager->CreateSceneNode("doom_1");
    SceneNode* doom2Node = sceneManager->CreateSceneNode("doom_2");
    SceneNode* doom3Node = sceneManager->CreateSceneNode("doom_3");
    SceneNode* doom4Node = sceneManager->CreateSceneNode("doom_4");
    SceneNode* doom5Node = sceneManager->CreateSceneNode("doom_5");

    // add all the nodes to the root scene node
    sceneManager->GetRootSceneNode()->AddChild(doom1Node);
    sceneManager->GetRootSceneNode()->AddChild(doom2Node);
    sceneManager->GetRootSceneNode()->AddChild(doom3Node);
    sceneManager->GetRootSceneNode()->AddChild(doom4Node);
    sceneManager->GetRootSceneNode()->AddChild(doom5Node);

    // left wall
    doom1Node->Yaw(DegToRad(75));
    doom1Node->SetPosition(-40, 0, 0);

    // right wall
    doom2Node->Yaw(DegToRad(-75));
    doom2Node->SetPosition(40, 0, 0);

    // middle door
    doom3Node->SetPosition(0, 0, -20);

    // floor
    doom4Node->Pitch(DegToRad(-75));
    doom4Node->SetPosition(0, -40, 0);

    // ceiling
    doom5Node->Pitch(DegToRad(75));
    doom5Node->SetPosition(0, 40, 0);

    PngLoader loader;

    // load the images
    Image* doom1Image = loader.Load("..\\..\\data\\doom_1.png");
    Image* doom2Image = loader.Load("..\\..\\data\\doom_2.png");
    Image* doom3Image = loader.Load("..\\..\\data\\doom_3.png");
    Image* doom4Image = loader.Load("..\\..\\data\\doom_4.png");

    // create the entities
    IEntity* doom1Entity = sceneManager->CreateEntity("doom_1");
    IEntity* doom2Entity = sceneManager->CreateEntity("doom_2");
    IEntity* doom3Entity = sceneManager->CreateEntity("doom_3");
    IEntity* doom4Entity = sceneManager->CreateEntity("doom_4");
    IEntity* doom5Entity = sceneManager->CreateEntity("doom_5");

    // add each entity to its scene node
    doom1Node->AddEntity(doom1Entity);
    doom2Node->AddEntity(doom2Entity);
    doom3Node->AddEntity(doom3Entity);
    doom4Node->AddEntity(doom4Entity);
    doom5Node->AddEntity(doom5Entity);

    // create the visual representation of the entity
    Visual* doom1Visual = sceneManager->CreateBillboard(40, 40);
    Visual* doom2Visual = sceneManager->CreateBillboard(40, 40);
    Visual* doom3Visual = sceneManager->CreateBillboard(40, 40);
    Visual* doom4Visual = sceneManager->CreateBillboard(40, 40);
    Visual* doom5Visual = sceneManager->CreateBillboard(40, 40);

    // set each entities visual
    doom1Entity->SetVisual(doom1Visual);
    doom2Entity->SetVisual(doom2Visual);
    doom3Entity->SetVisual(doom3Visual);
    doom4Entity->SetVisual(doom4Visual);
    doom5Entity->SetVisual(doom5Visual);

    // create the textures for each image, note visual 4 and 5 share the same texture
    TexturePtr doom1Texture = engine.GetTextureManager()->CreateTexture(TextureType::_2d, doom1Image);
    TexturePtr doom2Texture = engine.GetTextureManager()->CreateTexture(TextureType::_2d, doom2Image);
    TexturePtr doom3Texture = engine.GetTextureManager()->CreateTexture(TextureType::_2d, doom3Image);
    TexturePtr doom4Texture = engine.GetTextureManager()->CreateTexture(TextureType::_2d, doom4Image);

    // create an empty material for each visual
    IMaterial* doom1Material = new Material();
    IMaterial* doom2Material = new Material();
    IMaterial* doom3Material = new Material();
    IMaterial* doom4Material = new Material();
    IMaterial* doom5Material = new Material();

    // add material to visual
    doom1Visual->GetRenderable()->SetMaterial(doom1Material);
    doom2Visual->GetRenderable()->SetMaterial(doom2Material);
    doom3Visual->GetRenderable()->SetMaterial(doom3Material);
    doom4Visual->GetRenderable()->SetMaterial(doom4Material);
    doom5Visual->GetRenderable()->SetMaterial(doom5Material);

    // set the texture for each renderable, note renderable 4 and 5 share the same texture
    doom1Visual->GetRenderable()->GetMaterial()->SetTexture(doom1Texture);
    doom2Visual->GetRenderable()->GetMaterial()->SetTexture(doom2Texture);
    doom3Visual->GetRenderable()->GetMaterial()->SetTexture(doom3Texture);
    doom4Visual->GetRenderable()->GetMaterial()->SetTexture(doom4Texture);
    doom5Visual->GetRenderable()->GetMaterial()->SetTexture(doom4Texture);
}