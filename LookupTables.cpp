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

const float* LUTBank::getLutPointer(Waveform waveform) const
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

void LUTBank::generateSineLut(float * lut)
{
	static constexpr auto twoPi = 2.f * 3.1415926535;
	for (auto i = 0U; i < lookupTableSize; ++i)
	{
		lut[i] = static_cast<float>(1.f * sinf(twoPi * i / (float)lookupTableSize));
	}
}

void LUTBank::generateSawtoothLut(float * lut)
{
	for (auto i = 0U; i < lookupTableSize; ++i)
	{
		lut[i] = 2 * (i % lookupTableSize) * (1.f / lookupTableSize) - 1.f;
	}
}

void LUTBank::generateTriangleLut(float * lut)
{
	for (auto i = 0; i < lookupTableSize; ++i)
	{
		lut[i] = 4.f * abs(((i) % lookupTableSize) - lookupTableSize / 2) * (1.f / lookupTableSize) - 1.f;
	}
}

void LUTBank::generateSquareLut(float * lut)
{
	for (auto i = 0U; i < lookupTableSize; ++i)
	{
		lut[i] = (i < lookupTableSize / 2 ? 1.f : std::numeric_limits<float>::min());
	}
}

void LUTBank::generateNoiseLut(float * lut)
{
	std::random_device randomDevice;
	std::mt19937 generator(randomDevice());
	std::uniform_real_distribution<float> distribution(-1.f, 1.f);

	for (auto i = 0U; i < lookupTableSize; ++i)
	{
		lut[i] = distribution(generator);
	}
}

void LUTBank::generateEmptyLut(float * lut)
{
	for (auto i = 0U; i < lookupTableSize; ++i)
	{
		lut[i] = 0;
	}
}
