#include <cmath>
#include "TwoZeroDampingFilter.h"

TwoZeroDampingFilter::TwoZeroDampingFilter()
	: m_previous(0),
	m_pastPrevious(0),
	m_dampingBrightness(-1.f),
	m_dampingCoefficient(1.f),
	m_stringFrequency(440.f)
{
}

void TwoZeroDampingFilter::setDampingCoefficient(float dampingCoefficient)
{
	m_dampingCoefficient = dampingCoefficient;
}

void TwoZeroDampingFilter::setDampingBrightness(float dampingBrightness)
{
	m_dampingBrightness = dampingBrightness;
}

void TwoZeroDampingFilter::setDampedStringFrequency(float frequency)
{
	m_stringFrequency = frequency;
}

void TwoZeroDampingFilter::reset()
{
	m_previous = m_pastPrevious = 0.f;
}

float TwoZeroDampingFilter::process(float input)
{
	float rho = powf(0.001f, 1.f / (m_stringFrequency*m_dampingCoefficient));
	float h0 = 0.5f*(1.f + m_dampingBrightness);
	float h1 = 0.25f*(1.f - m_dampingBrightness);

	auto output = rho*(h0 * m_previous + h1*(input + m_pastPrevious));
	m_pastPrevious = m_previous;
	m_previous = input;

	return output;
}