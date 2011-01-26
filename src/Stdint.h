/**********************************************************************
*	Filename: StdInt.h
*	
*	Copyright (C) 2010, FIFE team
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
#ifndef STDINT_H_
#define STDINT_H_

#include "StdIncludes.h"

// defines for variable types for portability and consistency

// 8-bit types
typedef unsigned char uint8_t;
typedef signed char int8_t;

// 16-bit types
typedef unsigned short uint16_t;
typedef signed short int16_t;

// 32-bit types
# if ULONG_MAX == 0xffffffff
typedef long            int32_t;
typedef unsigned long   uint32_t;
# elif UINT_MAX == 0xffffffff
typedef int             int32_t;
typedef unsigned int    uint32_t;
#endif

#endif