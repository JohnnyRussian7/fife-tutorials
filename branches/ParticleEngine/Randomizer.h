
#ifndef RANDOMIZER_H_
#define RANDOMIZER_H_

class Randomizer
{
public:
	static void seed();
	static int rand();
	static float uniformRand(); 
	static float randBetween(float min, float max);

private:
	static bool initialized;
};

#endif
