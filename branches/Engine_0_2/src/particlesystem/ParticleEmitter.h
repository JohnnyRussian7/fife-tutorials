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
#include "../Color.h"
#include "../math/Vector3.h"
#include "../geometry/AxisAlignedBoundingBox.h"

class IParticleEffect;

class ParticleEmitter
{
public:
	ParticleEmitter(uint32_t minParticles=0, uint32_t maxParticles=0,
        const float minSize=1, const float maxSize=1, 
		const float minEnergy=1, const float maxEnergy=1,
        const Color& color=Color::White(),
        const AxisAlignedBoundingBox& aabb=AxisAlignedBoundingBox());
	~ParticleEmitter();

	void Emit(); 
	void Update(uint32_t time);
	void SetFollowEmitter(bool enabled);
	void ClearParticles();
	uint32_t GetNumActiveParticles() const;
	uint32_t GetNumMaxParticles() const;
	std::vector<Particle>& GetParticles();
	const AxisAlignedBoundingBox& GetBoundingBox() const;

private:
	uint32_t m_minParticles;
	uint32_t m_maxParticles;
	uint32_t m_activeParticles;
	std::vector<Particle> m_particles;
	Vector3 m_position;
	float m_minSize;
	float m_maxSize;
	float m_minEnergy;
	float m_maxEnergy;
    Color m_color;
	AxisAlignedBoundingBox m_aabb;
};

#endif
