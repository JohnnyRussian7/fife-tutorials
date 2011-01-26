/**********************************************************************
*	Filename: ParticleEmitter.h
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
#ifndef PARTICLEEMITTER_H_
#define PARTICLEEMITTER_H_

#include "../StdIncludes.h"

#include "Particle.h"
#include "../math/Vector3.h"
#include "../geometry/AxisAlignedBoundingBox.h"

class IParticleEffect;

class ParticleEmitter
{
public:
	ParticleEmitter(bool enabled, const AxisAlignedBoundingBox& aabb, 
		std::size_t minParticles, std::size_t maxParticles,
		const float minSize, const float maxSize, 
		const float minEnergy, const float maxEnergy,
		const Vector3& velocity);
	~ParticleEmitter();
	void Emit(); 
	void Update(float deltaTime);
	void SetEnabled(bool enabled);
	bool IsEnabled() const;
	void SetFollowEmitter(bool enabled);
	void ClearParticles();
	std::size_t GetNumActiveParticles() const;
	std::size_t GetNumMaxParticles() const;
	const std::vector<Particle>& GetParticles() const;
	const AxisAlignedBoundingBox& GetBoundingBox() const;
	void AddEffect(IParticleEffect* effect);
	void ApplyEffects(float updateRate);
private:
	bool isEnabled;
	std::size_t minParticles;
	std::size_t maxParticles;
	std::size_t activeParticles;
	std::vector<Particle> particles;
	Vector3 position;
	Vector3 velocity;
	float minSize;
	float maxSize;
	float minEnergy;
	float maxEnergy;
	float minEmission;
	float maxEmission;
	AxisAlignedBoundingBox aabb;
	std::vector<IParticleEffect*> effects;
};

#endif
