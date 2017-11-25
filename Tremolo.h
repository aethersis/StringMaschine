#pragma once
#include <functional>
#include "Oscillator.h"

class Tremolo
{
public:
	Tremolo(const LUTBank& lutBank);
	void setFrequency(float frequency);
	void setAmplitude(float amplitude);
	void setWaveform(LUTBank::Waveform waveform);
	float process();

private:
	float m_frequency;
	float m_amplitude;
	Oscillator m_oscillator;
};