
#ifndef PARTICLE_FADE_OUT_EFFECT_H_
#define PARTICLE_FADE_OUT_EFFECT_H_

#include "stdint.h"
#include "ParticleEffect.h"
#include "Color.h"

struct Particle;

class ParticleFadeOutEffect : public IParticleEffect
{
public:
	ParticleFadeOutEffect(const Color& endColor, float fadeOutTime);

	void apply(Particle* particles, uint32_t particleCount, float updateRate);

private:
	Color endColor;
	float fadeOutTime;
};

#endif
