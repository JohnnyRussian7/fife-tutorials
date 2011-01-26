/**********************************************************************
*	Filename: Randomizer.cpp
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

#include "Randomizer.h"

bool Randomizer::initialized = false;

void Randomizer::seed()
{
	initialized = true;

	std::srand(time(NULL));
}

int32_t Randomizer::rand()
{
	if (!initialized)
	{
		seed();
	}

	return std::rand();
}

float Randomizer::uniformRand()
{
	if (!initialized)
	{
		seed();
	}

	// get random number in range [0,1]
	return (Randomizer::rand()/float(RAND_MAX));
}

float Randomizer::randBetween(float min, float max)
{
	if (!initialized)
	{
		seed();
	}

	// return uniform number between range [min, max]
	return ((max-min) * uniformRand() + min);
}
