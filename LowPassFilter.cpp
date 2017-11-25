#include "LowPassFilter.h"

LowpassFilter::LowpassFilter(float sampleRate)
	: m_sampleRate(sampleRate),
	m_previousOutput(0.f)
{
	setFrequency(sampleRate/2.f);
}

float LowpassFilter::process(float input)
{
	m_previousOutput = m_previousOutput + m_alpha * (input - m_previousOutput);
	return m_previousOutput;
}

void LowpassFilter::setFrequency(float cutoff)
{
	constexpr float twoPi = 3.1415926535f * 2.f;
	float filterPeriod = 1.f / (twoPi*cutoff);
	float samplePeriod = 1.f / m_sampleRate;

	m_alpha = samplePeriod / (samplePeriod + filterPeriod); //twoPi * cutoff / m_sampleRate / (twoPi * cutoff / m_sampleRate + 1.f);
}
