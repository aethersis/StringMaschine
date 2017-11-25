#pragma once
#include <cassert>
#include "IFilter.h"

class FractionalDelayFilter : public IFilter
{
public:
	FractionalDelayFilter() : m_size(0.f), m_previousOutput(0.f), m_previousInput(0.f), m_delayCoefficient(0.f) {}

	float process(float input) override
	{
		m_previousOutput = (1.f - m_size) * input + m_size * m_previousInput;
		m_previousInput = input;

		return m_previousOutput;
	}

	void setSize(float size)
	{
		assert(m_size >= 0.f && m_size <= 1.f); 
		m_delayCoefficient = (1.f - m_size) / (1.f + m_size);
		m_size = size;
	}

private:
	float m_size;
	float m_delayCoefficient;
	float m_previousOutput, m_previousInput;
};