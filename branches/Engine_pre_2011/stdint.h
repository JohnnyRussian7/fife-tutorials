
#ifndef STD_INT_H_
#define STD_INT_H_

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