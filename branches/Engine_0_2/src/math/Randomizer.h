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

#include "../StdIncludes.h"

class Randomizer
{
public:
    //!***************************************************************
    //! @details:
    //! initializes the random number generator with a seed value
    //!
    //! @note:
    //! this does not have to be called directly, it gets called
    //! internally
    //!***************************************************************
	static void seed();
    
    //!***************************************************************
    //! @details:
    //! returns a random number based on the seed
    //!***************************************************************
	static int32_t rand();
    
    //!***************************************************************
    //! @details:
    //! provides a uniform distribution random number between [0, 1]
    //!***************************************************************
	static float uniformRand();
    
    //!***************************************************************
    //! @details:
    //! provides a uniform distribution random number between [min, max]
    //!***************************************************************
	static float randBetween(float min, float max);

private:
	static bool initialized;
};

#endif
