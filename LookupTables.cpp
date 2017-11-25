#include "LookupTables.h"

LUTBank::LUTBank()
{
	generateSineLut(&sineLut[0]);
	generateNoiseLut(&noiseLut[0]);
	generateSawtoothLut(&sawtoothLut[0]);
	generateTriangleLut(&triangleLut[0]);
	generateSquareLut(&squareLut[0]);
	generateEmptyLut(&emptyLut[0]);
}

const Sample* LUTBank::getLutPointer(Waveform waveform) const
{
	switch (waveform)
	{
	case Waveform::Sine:
		return &sineLut[0];
	case Waveform::Sawtooth:
		return &sawtoothLut[0];
	case Waveform::Noise:
		return &noiseLut[0];
	case Waveform::Triangle:
		return &triangleLut[0];
	case Waveform::Square:
		return &squareLut[0];
	case Waveform::None:
		return &emptyLut[0];
	}

	return &sineLut[0];
}

void LUTBank::generateSineLut(Sample * lut)
{
	for (auto i = 0U; i < g_lookupTableSize; ++i)
	{
		lut[i] = static_cast<Sample>(std::numeric_limits<Sample>::max() * sinf(2.f * g_pi * i / (float)g_lookupTableSize));
	}
}

void LUTBank::generateSawtoothLut(Sample * lut)
{
	for (auto i = 0U; i < g_lookupTableSize; ++i)
	{
		lut[i] = 2 * (i % g_lookupTableSize) * (std::numeric_limits<Sample>::max() / g_lookupTableSize) - std::numeric_limits<Sample>::min();
	}
}

void LUTBank::generateTriangleLut(Sample * lut)
{
	for (auto i = 0; i < g_lookupTableSize; ++i)
	{
		lut[i] = 4 * abs(((i) % g_lookupTableSize) - g_lookupTableSize / 2) * (std::numeric_limits<Sample>::max() / g_lookupTableSize) - std::numeric_limits<Sample>::max();
	}
}

void LUTBank::generateSquareLut(Sample * lut)
{
	for (auto i = 0U; i < g_lookupTableSize; ++i)
	{
		lut[i] = (i < g_lookupTableSize / 2 ? std::numeric_limits<Sample>::max() : std::numeric_limits<Sample>::min());
	}
}

void LUTBank::generateNoiseLut(Sample * lut)
{
	std::random_device randomDevice;
	std::mt19937 generator(randomDevice());
	std::uniform_int_distribution<int> distribution(std::numeric_limits<Sample>::min(),
		std::numeric_limits<Sample>::max());

	for (auto i = 0U; i < g_lookupTableSize; ++i)
	{
		lut[i] = distribution(generator);
	}
}

void LUTBank::generateEmptyLut(Sample * lut)
{
	for (auto i = 0U; i < g_lookupTableSize; ++i)
	{
		lut[i] = 0;
	}
}
