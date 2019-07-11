#pragma once
#include <random>
#include <time.h>

static class Random
{
public:
	Random();
	static int RandomNumberInRange(int max, int min);
};

