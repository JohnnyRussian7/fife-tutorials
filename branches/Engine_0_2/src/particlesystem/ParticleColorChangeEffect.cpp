/**********************************************************************
*	Filename: ParticleColorChangeEffect.cpp
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

#include "ParticleColorChangeEffect.h"
#include "Particle.h"

ParticleColorChangeEffect::ParticleColorChangeEffect(const Color& endColor, uint32_t time)
: m_endColor(endColor), m_time(time)
{

}

void ParticleColorChangeEffect::apply(Particle* particles, uint32_t particleCount, uint32_t /*time*/)
{
	for (uint32_t i=0; i < particleCount; ++i)
	{
		Particle& particle = particles[i];

		if (particle.m_lifetime < m_time)
		{
			float interpolationScale = (particle.m_lifetime - m_time/2) / m_time;
			particle.m_color = interpolate(particle.m_startColor, m_endColor, interpolationScale);
		}
	}
}