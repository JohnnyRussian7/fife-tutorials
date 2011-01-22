/*
 *  StdIncludes.h
 *  ParticleEngine
 *
 *  Created by Jesse Manning on 1/22/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef STD_INCLUDES_H_
#define STD_INCLUDES_H_

#include <cstdlib>
#include <cstring>
#include <cassert>
#include <ctime>
#include <cmath>

#include <string>
#include <algorithm>
#include <functional>
#include <limits>

#include <vector>
#include <deque>
#include <list>
#include <set>
#include <map>

#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <memory>

// make sure the proper defines are there for windows
#if defined(_MSC_VER)
#define NOMINMAX
#if !defined(WIN32)
#define WIN32
#endif

// takes care of including opengl properly
// on windows, linux, and os x
#include "glee/GLee.h"

// typedefs for commonly used built in types
#include "../../../stdint.h"
#endif
