
#ifndef PARTICLE_EFFECT_H_
#define PARTICLE_EFFECT_H_

struct Particle;

class IParticleEffect
{
public:
	virtual void apply(Particle* particles, unsigned int particleCount, float updateRate) = 0;
};

#endif