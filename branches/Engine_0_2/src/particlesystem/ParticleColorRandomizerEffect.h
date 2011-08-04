/**********************************************************************
*	Filename: ParticleColorRandomizerEffect.h
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
#ifndef PARTICLECOLORRANDOMIZEREFFECT_H_
#define PARTICLECOLORRANDOMIZEREFFECT_H_

#include "IParticleEffect.h"
#include "../Color.h"

struct Particle;

class ParticleColorRandomizerEffect : public IParticleEffect
{
public:
    ParticleColorRandomizerEffect(const Color& firstColor=Color::Black(), const Color& secondColor=Color::White());

    void apply(Particle* particles, uint32_t particleCount, uint32_t /*time*/);

private:
    Color m_firstColor;
    Color m_secondColor;

};

#endif
