
#ifndef PARTICLE_H_
#define PARTICLE_H_

#include "Vector.h"
#include "Color.h"

struct Particle
{
	Vector3 position;
	Vector3 prevPosition;
	Vector3 velocity;
	float lifetime;
	float size;
	Color startColor;
	Color color;
};

#endif
