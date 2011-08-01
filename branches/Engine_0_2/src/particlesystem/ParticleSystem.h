/**********************************************************************
*	Filename: ParticleSystem.h
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
#ifndef PARTICLESYSTEM_H_
#define PARTICLESYSTEM_H_

#include "../StdIncludes.h"

#include "../math/Vector3.h"
#include "../scene/BillboardGroup.h"
#include "../graphics/TextureFwd.h"

class SceneManager;
class Camera;
class ParticleEmitter;
class IParticleEffect;

class ParticleSystem : public Entity
{
public:
    ParticleSystem(SceneManager* sceneManager, ParticleEmitter* emitter, bool enabled=false, const Vector3& position=Vector3::Zero(), char* name=0);
	~ParticleSystem();

    void AddEffect(IParticleEffect* effect);
	void AddTexture(const TexturePtr& texture);
	void SetEnabled(bool enabled);
	bool IsEnabled() const;
	void Update(uint32_t time);
	void Render(Camera& camera);

private:
    void ApplyEffects(uint32_t time);

private:
    SceneManager* m_sceneManager;
	bool m_enabled;
	ParticleEmitter* m_emitter;
	BillboardGroup m_billboardGroup;
    IVertexBuffer* m_vertexBuffer;
    IMaterial* m_material;

    typedef std::vector<IParticleEffect*> EffectContainer;
    EffectContainer m_effects;
};

#endif
