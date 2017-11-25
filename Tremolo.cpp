#include "Tremolo.h"

Tremolo::Tremolo(const LUTBank& lutBank)
	: m_frequency(1),
	m_amplitude(1),
	m_oscillator(lutBank)
{
}

void Tremolo::setFrequency(float frequency)
{
	m_oscillator.setFrequency(frequency);
}

void Tremolo::setAmplitude(float amplitude)
{
	m_amplitude = amplitude;
}

void Tremolo::setWaveform(LUTBank::Waveform waveform)
{
	m_oscillator.setWaveform(waveform);
}

float Tremolo::process()
{
	return m_amplitude * m_oscillator.generate() / (float)g_outputTypeMax + (1.f-m_amplitude);
}
