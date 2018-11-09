#pragma once
#include <random>

namespace CommonUtilities
{
	int GenerateRandomNr(int aMinNumber, int aMaxNumber)
	{
		std::random_device rnd;
		std::mt19937 gen(rnd());
		std::uniform_int_distribution<int> dist(aMinNumber, aMaxNumber);
		return dist(gen);
	}
}