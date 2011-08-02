/**********************************************************************
*	Filename: SimpleParticleSystem.cpp
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

#include "SimpleParticleSystem.h"

void CreateSimpleParticleSystem(Engine& engine)
{
    // store off scene manager locally as it will be used often
    SceneManager* sceneManager = engine.GetSceneManager();

    // setup a simple camera
    Camera* camera = sceneManager->CreateCamera();
    SceneNode* cameraNode = sceneManager->CreateSceneNode("camera");
    cameraNode->AddEntity(camera);
    cameraNode->Translate(0, 0, 500);
    camera->LookAt(0, 0, 0);
    sceneManager->AddCamera(camera);
    sceneManager->GetRootSceneNode()->AddChild(cameraNode);

    ParticleEmitter* emitter = new ParticleEmitter(1, 1, 40, 60, 8000, 8000, Vector3(0, 20, 0));
    ParticleSystem* particleSystem = new ParticleSystem(sceneManager, emitter, true);

    //ParticleColorChangeEffect* effect = new ParticleColorChangeEffect(Color::Black(), 20);
    //particleSystem->AddEffect(effect);

    SceneNode* particleSceneNode = sceneManager->CreateSceneNode("particleNode");
    particleSceneNode->AddEntity(particleSystem);
    sceneManager->GetRootSceneNode()->AddChild(particleSceneNode);

    // load the image
    //filesystem::Path path("../../data/smoke_animation.png");
    //filesystem::Path path("../../data/grass/45.png");
    //ImagePtr smokeImage = engine.GetImageManager()->CreateImage(path, "fireImage");
//     if (smokeImage)
//     {
//         TexturePtr fireTexture = engine.GetTextureManager()->CreateTexture(TextureType::_2d, smokeImage);
// 
//         if (fireTexture)
//         {
//             particleSystem->AddTexture(fireTexture);
//         }
//     }

    //IAnimation* smokeAnimation = sceneManager->CreateAnimatedTexture("..\\..\\data\\smoke_animation.png", 1, 8, 8, 3000);
    IAnimation* smokeAnimation = sceneManager->CreateAnimatedTexture("..\\..\\data\\torch_animation.png", 5, 5, 25, 3000);
    if (smokeAnimation)
    {
        particleSystem->AddAnimation(smokeAnimation);
    }

    BlendingMode blendMode;
    blendMode.SetEnabled(true);
    blendMode.SetSrcBlendMode(SrcBlendMode::SrcAlpha);
    blendMode.SetDestBlendMode(DestBlendMode::OneMinusSrcAlpha);
    sceneManager->GetRootSceneNode()->SetBlendingMode(blendMode);
}