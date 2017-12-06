#pragma once
#include <cmath>
#include <cstdint>
#include <limits>
#include "LookupTables.h"

class Oscillator
{
public:
	Oscillator(float floatRate, const LUTBank& lutBank)
		: m_lutBank(lutBank)
		, m_sampleRate(floatRate)
	{
		setWaveform(LUTBank::Waveform::Sine);
		setFrequency(1);
	}

	void setWaveform(LUTBank::Waveform waveform)
	{
		m_waveform = waveform;
		m_lookupTable = m_lutBank.getLutPointer(waveform);
	}

	LUTBank::Waveform getWaveform()
	{
		return m_waveform;
	}

	void setFrequency(float frequency)
	{
		m_baseFrequency = frequency;
		m_increment = frequency / m_sampleRate * (float)m_lutBank.lookupTableSize;
	}

	float getFrequency()
	{
		return m_baseFrequency;
	}

	void applyFrequencyModulation(float modulatorOutput, float frequencyRange)
	{
		auto modulatedFrequency = (modulatorOutput * frequencyRange);
		m_increment = m_sampleRate / (m_baseFrequency + modulatedFrequency);
	}

	float generate()
	{
		m_phaseAccumulator = fmod(m_phaseAccumulator + m_increment, (float)m_lutBank.lookupTableSize);
		float integerPart;
		auto fractionalPart = modf(m_phaseAccumulator, &integerPart);

		return (1.f - fractionalPart) * m_lookupTable[(int)m_phaseAccumulator] + (fractionalPart) * m_lookupTable[(int)(m_phaseAccumulator + 1)%m_lutBank.lookupTableSize];
	}

private:
	LUTBank::Waveform m_waveform;
	const float* m_lookupTable;
	float m_baseFrequency = 0;
	float m_sampleRate;

	float m_increment = 0;
	float m_phaseAccumulator = 0;
	const LUTBank& m_lutBank;
};