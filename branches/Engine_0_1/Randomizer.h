/**********************************************************************
*	Filename: Randomizer.h
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
#ifndef RANDOMIZER_H_
#define RANDOMIZER_H_

#include "StdIncludes.h"

class Randomizer
{
public:
	static void seed();
	static int32_t rand();
	static float uniformRand(); 
	static float randBetween(float min, float max);

private:
	static bool initialized;
};

#endif
