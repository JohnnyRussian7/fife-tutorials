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
#include "../math/Randomizer.h"

ParticleEmitter::ParticleEmitter(uint32_t minParticles, uint32_t maxParticles,
								 const float minSize, const float maxSize, 
								 const float minLifetimeInMs, const float maxLifetimeInMs,
                                 const Vector3& minVelocity, const Vector3& maxVelocity,
                                 const Color& colorRangeStart, const Color& colorRangeEnd,
                                 const AxisAlignedBoundingBox& aabb)
: m_minParticles(minParticles), m_maxParticles(maxParticles), 
m_activeParticles(0), m_particles(maxParticles), m_position(Vector3::Zero()),
m_minSize(minSize), m_maxSize(maxSize), m_minLifetimeInMs(minLifetimeInMs), 
m_maxLifetimeInMs(maxLifetimeInMs), m_minVelocity(minVelocity), m_maxVelocity(maxVelocity),
m_colorRangeStart(colorRangeStart),  m_colorRangeEnd(colorRangeEnd), 
m_aabb(aabb), m_sizeRangeSet(false), m_lifetimeRangeSet(false), m_velocityRangeSet(false),
m_colorRangeSet(false)
{
    if (m_minSize != m_maxSize)
    {
        m_sizeRangeSet = true;
    }

    if (m_minLifetimeInMs != m_maxLifetimeInMs)
    {
        m_lifetimeRangeSet = true;
    }

    if (m_minVelocity != m_maxVelocity)
    {
        m_velocityRangeSet = true;
    }

    if (m_colorRangeStart != m_colorRangeEnd)
    {
        m_colorRangeSet = true;
    }
}

ParticleEmitter::~ParticleEmitter()
{
	
}

void ParticleEmitter::Emit(uint32_t time)
{
    uint32_t maxParticlesAvailable = m_maxParticles - GetNumActiveParticles();
    
    uint32_t minParticlesAvailable = 0;
    if (GetNumActiveParticles() < m_minParticles)
    {
        minParticlesAvailable = m_minParticles - GetNumActiveParticles();
    }
    
    uint32_t amount = uint32_t(Randomizer::randBetween(static_cast<float>(minParticlesAvailable), 
                                                        static_cast<float>(maxParticlesAvailable)));

	if (amount > 0)
	{
		const Vector3& max = m_aabb.GetMax();
		const Vector3& min = m_aabb.GetMin();

		uint32_t index = GetNumActiveParticles();
		m_activeParticles += amount;
		for (; index < m_activeParticles; ++index)
		{
			Particle& particle = m_particles[index];
            particle.m_velocity = Vector3::Zero();
            particle.m_creationTime = time;

			particle.m_position.x = Randomizer::randBetween(min.x, max.x);
			particle.m_position.y = Randomizer::randBetween(min.y, max.y);
			particle.m_position.z = Randomizer::randBetween(min.z, max.z);

            if (m_velocityRangeSet)
            {
                particle.m_velocity.x = Randomizer::randBetween(m_minVelocity.x, m_maxVelocity.x);
                particle.m_velocity.y = Randomizer::randBetween(m_minVelocity.y, m_maxVelocity.y);
                particle.m_velocity.z = Randomizer::randBetween(m_minVelocity.z, m_maxVelocity.z);
            }
            else
            {
                particle.m_velocity = m_minVelocity;
            }

            if (m_colorRangeSet)
            {
                particle.m_color.r = Randomizer::randBetween(m_colorRangeStart.r, m_colorRangeEnd.r);
                particle.m_color.g = Randomizer::randBetween(m_colorRangeStart.g, m_colorRangeEnd.g);
                particle.m_color.b = Randomizer::randBetween(m_colorRangeStart.b, m_colorRangeEnd.b);
                particle.m_color.a = Randomizer::randBetween(m_colorRangeStart.a, m_colorRangeEnd.a);
            }
            else
            {
                particle.m_color = m_colorRangeStart;
            }

            particle.m_startColor = particle.m_color;

            if (m_lifetimeRangeSet)
            {
			    particle.m_lifetime = Randomizer::randBetween(m_minLifetimeInMs, m_maxLifetimeInMs);
            }
            else
            {
                particle.m_lifetime = m_minLifetimeInMs;
            }

            if (m_sizeRangeSet)
            {
                particle.m_size = Randomizer::randBetween(m_minSize, m_maxSize);
            }
            else
            {
                particle.m_size = m_minSize;
            }
		}
	}
}

void ParticleEmitter::Update(uint32_t time)
{
	if (!m_particles.empty())
	{
		//Vector3 minAabb = m_aabb.GetMin();
		//Vector3 maxAabb = m_aabb.GetMax();

		uint32_t index = 0;
        bool particleDead = false;
		while (index < m_activeParticles)
		{
            particleDead = false;

			Particle& particle = m_particles[index];
			
            if ((time-particle.m_creationTime) > particle.m_lifetime)
            {
                particleDead = true;
            }

            if (!particleDead)
            {
			    // update position based on velocity
			    particle.m_position += particle.m_velocity;

			    // particle outside emitter bounds, kill particle
// 			    if (!m_aabb.Contains(particle.m_position))
// 			    {
// 				    particle.m_lifetime -= m_maxLifetimeInMs;
//                     particleDead = true;
// 			    }

            }

            if (particleDead)
            {
                //particle is dead so swap it with the last active particle
				m_particles[index] = m_particles[m_activeParticles-1];

				// decrease active particle count
				--m_activeParticles;
            }
            else
            {
                ++index;
            }

// 			if (particle.m_lifetime < m_minLifetimeInMs)
// 			{
// 				// particle is dead so swap it with the last active particle
// 				m_particles[index] = m_particles[m_activeParticles-1];
// 
// 				// decrease active particle count
// 				--m_activeParticles;
// 			}
// 			else
// 			{
// // 				minAabb.x = std::min(minAabb.x, m_position.x);
// // 				minAabb.y = std::min(minAabb.y, m_position.y);
// // 				minAabb.z = std::min(minAabb.z, m_position.z);
// // 				maxAabb.x = std::max(maxAabb.x, m_position.x);
// // 				maxAabb.y = std::max(maxAabb.y, m_position.y);
// // 				maxAabb.z = std::max(maxAabb.z, m_position.z);
// 
// 				// increment the index to move to next particle
// 				++index;
// 			}
		}

		//m_aabb.SetMinMax(minAabb, maxAabb);
	}
}

void ParticleEmitter::ClearParticles()
{
	m_particles.clear();
}

uint32_t ParticleEmitter::GetNumActiveParticles() const
{
	return m_activeParticles;
}

uint32_t ParticleEmitter::GetNumMaxParticles() const
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

