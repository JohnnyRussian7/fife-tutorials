
#ifndef PARTICLE_EMITTER_H_
#define PARTICLE_EMITTER_H_

#include <vector>

#include "Vector3.h"
#include "Particle.h"
#include "AxisAlignedBoundingBox.h"

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
