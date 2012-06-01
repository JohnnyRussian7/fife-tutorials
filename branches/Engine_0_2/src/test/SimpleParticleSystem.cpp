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

    Vector3 minVelocity = Vector3::Zero();
    Vector3 maxVelocity = Vector3::Zero();
    AxisAlignedBoundingBox aabb = AxisAlignedBoundingBox(Vector3(-10, -10, 0), Vector3(10, 10, 0));
    
    ParticleEmitter* emitter = new ParticleEmitter(70, 80, 5, 10, 2000, 2300, minVelocity, maxVelocity, Color::White(), Color::White(), aabb);
    ParticleSystem* particleSystem = new ParticleSystem(sceneManager, emitter, true);

    IParticleEffect* fadeEffect = new ParticleFadeEffect(2000);
    particleSystem->AddEffect(fadeEffect);

    IParticleEffect* velocityEffect = new ParticleVelocityEffect(Vector3(0, 0.002, 0));
    particleSystem->AddEffect(velocityEffect);

    //IParticleEffect* colorChangeEffect = new ParticleColorChangeEffect(Color::Black(), 300);
    //particleSystem->AddEffect(colorChangeEffect);

    //IParticleEffect* randomColorEffect = new ParticleColorRandomizerEffect(Color::Black(), Color::White());
    //particleSystem->AddEffect(randomColorEffect);

    SceneNode* particleSceneNode = sceneManager->CreateSceneNode("particleNode");
    particleSceneNode->AddEntity(particleSystem);
    
    // disable depth buffer writing for the particle system
    //DepthBufferWriteMode depthBufferWriteMode;
    //depthBufferWriteMode.SetEnabled(false);
    //particleSceneNode->SetDepthBufferWriteMode(depthBufferWriteMode);
    
    sceneManager->GetRootSceneNode()->AddChild(particleSceneNode);

    filesystem::Path path("../../data/smoke_particle.png");
    ImagePtr smokeImage = engine.GetImageManager()->CreateImage(path, "smokeImage");
    if (smokeImage)
    {
        TexturePtr smokeTexture = engine.GetTextureManager()->CreateTexture(TextureType::_2d, smokeImage);

        if (smokeTexture)
        {
            particleSystem->AddTexture(smokeTexture);
        }
    }

    BlendingMode blendMode;
    blendMode.SetEnabled(true);
    blendMode.SetSrcBlendMode(SrcBlendMode::SrcAlpha);
    blendMode.SetDestBlendMode(DestBlendMode::OneMinusSrcAlpha);
    sceneManager->GetRootSceneNode()->SetBlendingMode(blendMode);
}