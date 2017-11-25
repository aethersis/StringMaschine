#include <cmath>
#include "OneZeroDampingFilter.h"

OneZeroDampingFilter::OneZeroDampingFilter()
	: m_previous(0),
	m_dampingBrightness(0.f),
	m_dampingCoefficient(1.f),
	m_stringFrequency(440.f)
{
}

void OneZeroDampingFilter::setDampingCoefficient(float dampingCoefficient)
{
	m_dampingCoefficient = dampingCoefficient;
}

void OneZeroDampingFilter::setDampingBrightness(float dampingBrightness)
{
	m_dampingBrightness = dampingBrightness;
}

void OneZeroDampingFilter::setDampedStringFrequency(float frequency)
{
	m_stringFrequency = frequency;
}

float OneZeroDampingFilter::process(float input)
{
	float rho = powf(0.1f, 1.f / (m_stringFrequency*m_dampingCoefficient));
	float b1 = m_dampingBrightness*0.5f;
	float b0 = 1.f - b1;

	auto output = rho*(b0*input + b1*m_previous);
	m_previous = input;
	return output;
}