#pragma once
#include <glm/glm.hpp>

inline void seedRandom(unsigned int seed)
{
	srand(seed);
}

inline float random01()
{
	return (float)rand() / (float)RAND_MAX;
}

inline float random(float min, float max)
{
	if (min > max)
	{
		std::swap(min, max);
	}

	return (random01() * (max - min + 1) + min);
}