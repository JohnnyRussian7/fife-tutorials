/**********************************************************************
*	Filename: ParticleEmitter.cpp
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

#include "ParticleEmitter.h"
#include "IParticleEffect.h"
#include "../Color.h"
#include "../math/Randomizer.h"

ParticleEmitter::ParticleEmitter(uint32_t minParticles, uint32_t maxParticles,
								 const float minSize, const float maxSize, 
								 const float minEnergy, const float maxEnergy,
								 const Vector3& velocity,
                                 const AxisAlignedBoundingBox& aabb)
: m_minParticles(minParticles), m_maxParticles(maxParticles), 
m_activeParticles(0), m_position(Vector3::Zero()), m_velocity(velocity), 
m_minSize(minSize), m_maxSize(maxSize), m_minEnergy(minEnergy), 
m_maxEnergy(maxEnergy), m_aabb(aabb)
{
	// preallocate particles
	for (uint32_t i=0; i < maxParticles; ++i)
	{
		Particle particle;
        particle.position = Vector3::Zero();
        particle.color = Color::Black();
        particle.velocity = Vector3::Zero();
		particle.lifetime = 0.f;
		particle.size = 0.f;

		m_particles.push_back(particle);
	}
}

ParticleEmitter::~ParticleEmitter()
{
	
}

void ParticleEmitter::Emit()
{
	std::size_t diffMaxMin = m_maxParticles - m_minParticles;

	int32_t amount = diffMaxMin ? m_minParticles + int32_t(Randomizer::randBetween(0, diffMaxMin)) : m_minParticles;

	if (GetNumActiveParticles() + amount > GetNumMaxParticles())
	{
		amount = GetNumMaxParticles() - GetNumActiveParticles();
	}

	if (amount > 0)
	{
		const Vector3& max = m_aabb.GetMax();
		const Vector3& min = m_aabb.GetMin();

		std::size_t index = GetNumActiveParticles();
		m_activeParticles += amount;
		for (; index < m_activeParticles; ++index)
		{
			Particle& particle = m_particles[index];
			particle.position.x = Randomizer::randBetween(min.x, max.x);
			particle.position.y = Randomizer::randBetween(min.y, max.y);
			particle.position.z = Randomizer::randBetween(min.z, max.z);
			particle.color.r = Randomizer::uniformRand();
			particle.color.g = Randomizer::uniformRand();
			particle.color.b = Randomizer::uniformRand();
			particle.startColor = particle.color;
			particle.velocity.x = Randomizer::randBetween(0.f, m_velocity.x);
			particle.velocity.y = Randomizer::randBetween(0.f, m_velocity.y);
			particle.velocity.z = Randomizer::randBetween(0.f, m_velocity.z);
			particle.lifetime = Randomizer::randBetween(m_minEnergy, m_maxEnergy);
			particle.size = Randomizer::randBetween(m_minSize, m_maxSize);
		}
	}
}

void ParticleEmitter::Update(uint32_t deltaTime)
{
	if (!m_particles.empty())
	{
		//Vector3 minAabb = m_aabb.GetMin();
		//Vector3 maxAabb = m_aabb.GetMax();

		std::size_t index = 0;
		while (index < m_activeParticles)
		{
			Particle& particle = m_particles[index];
			
			// update energy
			--particle.lifetime /*-= deltaTime*/;

			Vector3& position = particle.position;

			// update position based on velocity
			position += particle.velocity;

			// particle outside emitter bounds, kill particle
			if (!m_aabb.Contains(position))
			{
				particle.lifetime -= m_maxEnergy;
			}

			if (particle.lifetime < m_minEnergy)
			{
				// particle is dead so swap it with the last active particle
				m_particles[index] = m_particles[m_activeParticles-1];

				// decrease active particle count
				--m_activeParticles;
			}
			else
			{
// 				minAabb.x = std::min(minAabb.x, m_position.x);
// 				minAabb.y = std::min(minAabb.y, m_position.y);
// 				minAabb.z = std::min(minAabb.z, m_position.z);
// 				maxAabb.x = std::max(maxAabb.x, m_position.x);
// 				maxAabb.y = std::max(maxAabb.y, m_position.y);
// 				maxAabb.z = std::max(maxAabb.z, m_position.z);

				// increment the index to move to next particle
				++index;
			}
		}

		//m_aabb.SetMinMax(minAabb, maxAabb);
	}
}

void ParticleEmitter::ClearParticles()
{
	m_particles.clear();
}

std::size_t ParticleEmitter::GetNumActiveParticles() const
{
	return m_activeParticles;
}

std::size_t ParticleEmitter::GetNumMaxParticles() const
{
	return m_maxParticles;
}

std::vector<Particle>& ParticleEmitter::GetParticles()
{
	return m_particles;
}

const AxisAlignedBoundingBox& ParticleEmitter::GetBoundingBox() const
{
	return m_aabb;
}

