
#include "ParticleEmitter.h"
#include "Color.h"
#include "Randomizer.h"
#include "ParticleEffect.h"

ParticleEmitter::ParticleEmitter(bool enabled, const AxisAlignedBoundingBox& aabb, 
								 std::size_t minParticles, std::size_t maxParticles,
								 const float minSize, const float maxSize, 
								 const float minEnergy, const float maxEnergy,
								 const Vector3& velocity)
: isEnabled(enabled), aabb(aabb), minParticles(minParticles), 
  maxParticles(maxParticles), activeParticles(0), position(position), 
  velocity(velocity), minSize(minSize), maxSize(maxSize), minEnergy(minEnergy), 
  maxEnergy(maxEnergy)
{
	// preallocate particles
	for (std::size_t i=0; i < maxParticles; ++i)
	{
		Particle particle;
		particle.position = Vector3(0.f, 0.f, 0.f);
		particle.color = ColorBlack();
		particle.velocity = Vector3(0.f, 0.f, 0.f);
		particle.lifetime = 0.f;
		particle.size = 0.f;

		particles.push_back(particle);
	}
}

ParticleEmitter::~ParticleEmitter()
{
	for (std::vector<IParticleEffect*>::iterator iter = effects.begin(); iter != effects.end(); ++iter)
	{
		delete *iter;
	}
	effects.clear();
}

void ParticleEmitter::Emit()
{
	if (isEnabled)
	{	
		std::size_t diffMaxMin = maxParticles - minParticles;

		int amount = diffMaxMin ? minParticles + int(Randomizer::randBetween(0, diffMaxMin)) : minParticles;

		if (GetNumActiveParticles() + amount > GetNumMaxParticles())
		{
			amount = GetNumMaxParticles() - GetNumActiveParticles();
		}

		if (amount > 0)
		{
			const Vector3& max = aabb.GetMax();
			const Vector3& min = aabb.GetMin();

			std::size_t index = GetNumActiveParticles();
			activeParticles += amount;
			for (; index < activeParticles; ++index)
			{
				Particle& particle = particles[index];
				particle.position.x = Randomizer::randBetween(min.x, max.x);
				particle.position.y = Randomizer::randBetween(min.y, max.y);
				particle.position.z = Randomizer::randBetween(min.z, max.z);
				particle.color.r = Randomizer::uniformRand();
				particle.color.g = Randomizer::uniformRand();
				particle.color.b = Randomizer::uniformRand();
				particle.startColor = particle.color;
				particle.velocity.x = Randomizer::randBetween(0.f, velocity.x);
				particle.velocity.y = Randomizer::randBetween(0.f, velocity.y);
				particle.velocity.z = Randomizer::randBetween(0.f, velocity.z);
				particle.lifetime = Randomizer::randBetween(minEnergy, maxEnergy);
				particle.size = Randomizer::randBetween(minSize, maxSize);

				//particles.push_back(particle);
			}
		}
	}
}

void ParticleEmitter::Update(float deltaTime)
{
	if (isEnabled && !particles.empty())
	{
		//Vector3 minAabb = aabb.GetMin();
		//Vector3 maxAabb = aabb.GetMax();

		std::size_t index = 0;
		while (index < activeParticles)
		{
			Particle& particle = particles[index];
			
			// update energy
			--particle.lifetime /*-= deltaTime*/;

			Vector3& position = particle.position;

			// update position based on velocity
			position += particle.velocity;

			// particle outside emitter bounds, kill particle
			if (!aabb.Contains(position))
			{
				particle.lifetime -= maxEnergy;
			}

			if (particle.lifetime < minEnergy)
			{
				// particle is dead so swap it with the last active particle
				particles[index] = particles[activeParticles-1];

				// decrease active particle count
				--activeParticles;
			}
			else
			{
// 				minAabb.x = std::min(minAabb.x, position.x);
// 				minAabb.y = std::min(minAabb.y, position.y);
// 				minAabb.z = std::min(minAabb.z, position.z);
// 				maxAabb.x = std::max(maxAabb.x, position.x);
// 				maxAabb.y = std::max(maxAabb.y, position.y);
// 				maxAabb.z = std::max(maxAabb.z, position.z);

				// increment the index to move to next particle
				++index;
			}
		}

		ApplyEffects(deltaTime);

		//aabb.SetMinMax(minAabb, maxAabb);
	}
}

bool ParticleEmitter::IsEnabled() const
{
	return isEnabled;
}

void ParticleEmitter::SetEnabled(bool enabled)
{
	isEnabled = enabled;
}

void ParticleEmitter::ClearParticles()
{
	particles.clear();
}

std::size_t ParticleEmitter::GetNumActiveParticles() const
{
	return activeParticles;
}

std::size_t ParticleEmitter::GetNumMaxParticles() const
{
	return maxParticles;
}

const std::vector<Particle>& ParticleEmitter::GetParticles() const
{
	return particles;
}

const AxisAlignedBoundingBox& ParticleEmitter::GetBoundingBox() const
{
	return aabb;
}

void ParticleEmitter::AddEffect(IParticleEffect* effect)
{
	effects.push_back(effect);
}

void ParticleEmitter::ApplyEffects(float updateRate)
{
	for (std::vector<IParticleEffect*>::iterator iter = effects.begin(); iter != effects.end(); ++iter)
	{
		(*iter)->apply(&particles[0], GetNumActiveParticles(), updateRate);
	}
}

