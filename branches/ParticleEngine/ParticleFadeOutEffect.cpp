/**********************************************************************
*	Filename: ParticleFadeOutEffect.cpp
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