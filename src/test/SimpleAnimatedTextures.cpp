/**********************************************************************
*	Filename: SimpleAnimatedTextures.cpp
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

// engine include
#include "../Fife.h"

#include "SimpleAnimatedTextures.h"

void CreateSimpleAnimatedTextures(Engine& engine)
{
    SceneManager* sceneManager = engine.GetSceneManager();
    //Camera* camera = sceneManager->CreateCamera();
    //sceneManager->AddCamera(camera);

    //SceneNode* camNode = sceneManager->CreateSceneNode("CamNode");
    //camNode->AddEntity(camera);
    //sceneManager->GetRootSceneNode()->AddChild(camNode);

    BlendingMode blendMode;
    blendMode.SetEnabled(true);
    blendMode.SetSrcBlendMode(SrcBlendMode::SrcAlpha);
    blendMode.SetDestBlendMode(DestBlendMode::OneMinusSrcAlpha);
    sceneManager->GetRootSceneNode()->SetBlendingMode(blendMode);

    //camNode->Translate(Vector3(0, 0, 50));
    //camera->LookAt(Vector3(0, 0, 0));
    //camera->SetFixedYawAxis(true);

    IEntity* e1 = sceneManager->CreateEntity("e1");
    Visual* b1 = sceneManager->CreateBillboard(40, 40);

    e1->SetVisual(b1);
    b1->SetAnimation(sceneManager->CreateAnimatedTexture("..\\..\\data\\torch_animation.png", 1, 24, 24, 2500));

    IMaterial* m1 = new Material();
    b1->GetRenderable()->SetMaterial(m1);

    RenderComponent* renderComponent = new RenderComponent();
    renderComponent->SetMaterial(m1);
    e1->AddComponent(renderComponent);

    SceneNode* torchNode = sceneManager->CreateSceneNode("torch");
    torchNode->AddEntity(e1);
    sceneManager->GetRootSceneNode()->AddChild(torchNode);
    torchNode->Translate(0, 0, 0);

    IEntity* e2 = sceneManager->CreateEntity("e2");
    Visual* b2 = sceneManager->CreateBillboard(40, 40);
    e2->SetVisual(b2);
    b2->SetAnimation(sceneManager->CreateAnimatedTexture("..\\..\\data\\explosions_pot.png", 5, 5, 25, 3000));

    IMaterial* m2 = new Material();
    b2->GetRenderable()->SetMaterial(m2);

    SceneNode* explosionNode = sceneManager->CreateSceneNode("explosions");
    explosionNode->AddEntity(e2);
    sceneManager->GetRootSceneNode()->AddChild(explosionNode);
    explosionNode->Translate(40, 0, 0);

    IEntity* e3 = sceneManager->CreateEntity("e3");
    Visual* b3 = sceneManager->CreateBillboard(40, 40);
    //e3->SetVisual(b3);
    b3->SetAnimation(sceneManager->CreateAnimatedTexture("..\\..\\data\\torch_animation.png", 1, 24, 24, 2500));

    IMaterial* m3 = new Material();
    b3->GetRenderable()->SetMaterial(m3);

    SceneNode* torchNode2 = sceneManager->CreateSceneNode("torchNode2");
    torchNode2->AddEntity(e3);
    sceneManager->GetRootSceneNode()->AddChild(torchNode2);
    torchNode2->Translate(-40, 0, 0);

    //     IEntity* e3 = sceneManager->CreateEntity("e3");
    //     Billboard* b3 = sceneManager->CreateBillboard(4, 4, Vector3(0, 0, 0));
    //     e3->SetVisual(b3);
    //     b3->SetAnimation(sceneManager->CreateAnimatedTexture("..\\data\\finalfantasy5_pot.png", 4, 4, 15, 2000));
    // 
    //     IMaterial* m3 = new Material();
    //     b3->GetRenderable()->SetMaterial(m3);

    //     SceneNode* ffBossNode = sceneManager->CreateSceneNode("ffBoss");
    //     ffBossNode->AddEntity(e3);
    //     sceneManager->GetRootSceneNode()->AddChild(ffBossNode);
    //     ffBossNode->Translate(10, 0, 0);
    // 
    //     IEntity* e4 = sceneManager->CreateEntity("e4");
    //     Billboard* b4 = sceneManager->CreateBillboard(16, 16, Vector3(0, 0, 0));
    //     e4->SetVisual(b4);
    //     IMaterial* m4 = new Material();
    //     if (m4)
    //     {
    //         IAnimation* animation = sceneManager->CreateAnimatedTexture(2000, true);
    // 
    //         if (animation)
    //         {
    //             ImagePtr img = engine.GetImageManager()->CreateImage("..\\data\\animation_1\\000.png");
    //             ImagePtr img2 = engine.GetImageManager()->CreateImage("..\\data\\animation_1\\045.png");
    //             animation->AddFrame(engine.GetTextureManager()->CreateTexture(TextureType::_2d, img));
    //             animation->AddFrame(engine.GetTextureManager()->CreateTexture(TextureType::_2d, img2));
    //             b4->SetAnimation(animation);
    //         }
    //     }
    //     b4->GetRenderable()->SetMaterial(m3);
    // 
    //     SceneNode* maleNode = sceneManager->CreateSceneNode("anim_1");
    //     maleNode->Translate(4, 0, 0);
    //     maleNode->AddEntity(e4);
    //     sceneManager->GetRootSceneNode()->AddChild(maleNode);
}