#pragma once
#include <cassert>
#include "IFilter.h"

class FractionalDelayFilter : public IFilter
{
public:
	FractionalDelayFilter() : m_previousOutput(0.f), m_previousInput(0.f), m_delayCoefficient(0.f) {}

	float process(float input) override
	{
		m_previousOutput = m_delayCoefficient * input + m_previousInput - m_delayCoefficient * m_previousOutput;
		m_previousInput = input;

		return m_previousOutput;
	}

	void setSize(float size)
	{
		assert(size >= 0.f && size <= 1.f);
		m_delayCoefficient = (1.f - size) / (1.f + size);
	}

private:
	float m_delayCoefficient;
	float m_previousOutput, m_previousInput;
};