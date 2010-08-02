
#include "ParticleFadeOutEffect.h"
#include "Particle.h"

ParticleFadeOutEffect::ParticleFadeOutEffect(const Color& endColor, float fadeOutTime)
: endColor(endColor), fadeOutTime(fadeOutTime)
{

}

void ParticleFadeOutEffect::apply(Particle* particles, uint32_t particleCount, float updateRate)
{
	for (std::size_t i=0; i < particleCount; ++i)
	{
		//Particle& particle = particles[i];

		if (particles[i].lifetime < fadeOutTime)
		{
			float interpolationScale = (particles[i].lifetime - fadeOutTime/2) / fadeOutTime;
			particles[i].color = interpolate(particles[i].startColor, endColor, interpolationScale);
		}
	}
}