#include "HighpassFilter.h"

HighpassFilter::HighpassFilter(float sampleRate)
	: m_sampleRate(sampleRate),
	m_previousOutput(0.f),
	m_previousInput(0.f)
{
	setFrequency(sampleRate/2.f);
}

float HighpassFilter::process(float input)
{
	m_previousOutput = m_alpha * m_previousOutput + m_alpha * (input - m_previousInput);
	m_previousInput = input;
	return m_previousOutput;
}

void HighpassFilter::setFrequency(float cutoff)
{
	constexpr float twoPi = 3.1415926535f * 2.f;
	float filterPeriod = twoPi * cutoff;
	float samplePeriod = 1.f / m_sampleRate;

	m_alpha = 1.f  / (samplePeriod * filterPeriod + 1.f);
}

void HighpassFilter::reset()
{
	m_previousInput = m_previousOutput = 0.f;
}
