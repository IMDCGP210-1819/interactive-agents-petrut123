#include "pch.h"
#include "Random.h"

Random::Random()
{
	srand(time(0));
}

int Random::RandomNumberInRange(int max, int min)
{
	return rand() % (max + 1 - min) + min;
}