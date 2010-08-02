
#include "Randomizer.h"

#include <cstdlib>
#include <ctime>

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
