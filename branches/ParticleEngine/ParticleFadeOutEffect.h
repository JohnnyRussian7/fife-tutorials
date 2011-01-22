/**********************************************************************
*	Filename: ParticleFadeOutEffect.h
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
#ifndef PARTICLE_FADE_OUT_EFFECT_H_
#define PARTICLE_FADE_OUT_EFFECT_H_

#include "StdIncludes.h"

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
