#include <cmath>
#include "DynamicLevelLowpassFilter.h"

DynamicLevelLowpassFilter::DynamicLevelLowpassFilter()
	: m_previousInput(0),
	m_previousOutput(0)
{
	setLevel(1.f);
	setFrequency(20000.f);
}

float DynamicLevelLowpassFilter::process(float input)
{
	// b1 = b0 for this filter, first order lowpass
	m_previousOutput = m_b0 * input + m_b0 * m_previousInput - m_a0 * m_previousOutput;
	m_previousInput = input;

	// make the filter dynamics stronger or weaker depending on the level parameter
	return m_level * m_levelAttenuation * input + (1.f - m_level) * m_previousOutput;
}

void DynamicLevelLowpassFilter::setLevel(float level)
{
	constexpr auto oneThird = 1.f / 3.f;
	m_level = level;
	m_levelAttenuation = powf(level, oneThird);
}

void DynamicLevelLowpassFilter::setFrequency(float frequency)
{
	frequency *= 2.f * 3.1415926535;
	m_b0 = frequency / (frequency + 1.f);
	m_a0 = (frequency - 1.f) / (frequency + 1.f);
}
