#include <cstdlib>
#include <cmath>
#include "ExcitationGenerators.h"

float uniformExcitation(float stringLength, float currentPosition)
{
	auto value = (rand() % RAND_MAX) / (float)RAND_MAX;

	return value;
}

float sawtoothExcitation(float stringLength, float currentPosition)
{
	return currentPosition / stringLength;
}

float sineExcitation(float stringLength, float currentPosition)
{
	static constexpr auto fourPi = 4.f * 3.1415926535;
	return sinf(fourPi * currentPosition / stringLength);
}

float noExcitation(float stringLength, float currentPosition)
{
	return 0.f;
}