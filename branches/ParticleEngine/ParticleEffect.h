
#ifndef PARTICLE_EFFECT_H_
#define PARTICLE_EFFECT_H_

#include "stdint.h"

struct Particle;

class IParticleEffect
{
public:
	virtual void apply(Particle* particles, uint32_t particleCount, float updateRate) = 0;
};

#endif