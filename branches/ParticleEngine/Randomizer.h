
#ifndef RANDOMIZER_H_
#define RANDOMIZER_H_

#include "stdint.h"

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
