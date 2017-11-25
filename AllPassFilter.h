#pragma once
#include "IFilter.h"

class AllPassFilter : public IFilter
{
public:
	AllPassFilter(float gain) : m_gain(gain) {}

	float process(float input) override
	{
		return input * m_gain;
	}

private:
	float m_gain;
};