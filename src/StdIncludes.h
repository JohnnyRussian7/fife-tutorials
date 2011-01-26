/**********************************************************************
*	Filename: StdIncludes.h
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
#ifndef STDINCLUDES_H_
#define STDINCLUDES_H_

// C standard libs
#include <cstdlib>
#include <cstring>
#include <cassert>
#include <ctime>
#include <cmath>

// misc
#include <algorithm>
#include <functional>
#include <limits>
#include <memory>

//containers
#include <string>
#include <vector>
#include <deque>
#include <list>
#include <set>
#include <map>

// streams
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>

// make sure the proper defines are there for windows
#if defined(_MSC_VER)
    #define NOMINMAX
    #define WIN32_LEAN_AND_MEAN
    #if !defined(WIN32)
        #define WIN32
    #endif
#endif

// takes care of including opengl properly
// on windows, linux, and os x
#include "extern/glee/GLee.h"

// typedefs for commonly used built in types
#include "StdInt.h"

#endif
