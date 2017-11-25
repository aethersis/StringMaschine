#pragma once
#include <cmath>
#include <cstdint>
#include <limits>
#include "Settings.h"
#include "LookupTables.h"

class Oscillator
{
public:
	Oscillator(const LUTBank& lutBank)
		: m_lutBank(lutBank)
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

	void setFrequency(uint16_t frequency)
	{
		m_baseFrequency = frequency;
		m_increment = g_phaseAccumulatorMax / g_sampleRate * frequency;
	}

	uint16_t getFrequency()
	{
		return m_baseFrequency;
	}

	void applyModulation(Sample modulatorOutput, uint16_t frequencyRange)
	{
		auto modulatedFrequency = ((LargeType)modulatorOutput * frequencyRange) / std::numeric_limits<Sample>::max();
		m_increment = g_phaseAccumulatorMax / g_sampleRate * (m_baseFrequency + modulatedFrequency);
	}

	Sample generate()
	{
		m_phaseAccumulator += m_increment;
		return m_lookupTable[m_phaseAccumulator >> (g_phaseAccumulatorBits - g_lookupTableSizeBits)];
	}

private:
	LUTBank::Waveform m_waveform;
	const Sample* m_lookupTable;
	uint16_t m_baseFrequency = 0;

	LargeTypeUnsigned m_increment = 0;
	LargeTypeUnsigned m_phaseAccumulator = 0;
	const LUTBank& m_lutBank;
};